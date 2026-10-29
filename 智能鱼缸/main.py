# -*- coding: utf-8 -*-
from machine import Pin, ADC
import utime
import ujson
from umqtt.simple import MQTTClient
import onewire
from ds18x20 import DS18X20

hj = ADC(34)
level = ADC(35)
pmp1 = Pin(12, Pin.OUT)
pmp2 = Pin(13, Pin.OUT)
motor = Pin(14, Pin.OUT)
OneWirePin = 15
led = Pin(16, Pin.OUT)

# ssid='CU_future'
# psw='13582579999'
ssid = 'LEGOEducation'
psw = 'lego2232888'

SERVER = "bj-2-mqtt.iot-api.com"
PORT = 1883
CLIENT_ID = 'bk7jilrw'
USERNAME = '0gp3tb236jver79m'
PASSWORD = 'FBtp2IwgGo'
TOPIC = "attributes"
TOPIC1 = "attributes/push"
TOPIC_RESPONSE = "attributes/response"


# 每10秒采集并上传一次；温度转换期间继续接收云端消息。
PUBLISH_INTERVAL_MS = 10000
TEMP_CONVERSION_MS = 750
LOOP_SLEEP_MS = 10


def do_connect():
    import network
    wlan = network.WLAN(network.STA_IF)
    wlan.active(True)
    if not wlan.isconnected():
        print('connecting to network...')
        wlan.connect(ssid, psw)
        while not wlan.isconnected():
            utime.sleep_ms(100)
    print('network config:', wlan.ifconfig())


def mqtt_connect():
    # ThingsCloud要求KeepAlive不低于60秒；正常运行每10秒发布一次。
    client = MQTTClient(CLIENT_ID, SERVER, PORT, USERNAME, PASSWORD, keepalive=60)
    client.connect()
    print('Connected to MQTT Broker "{server}"'.format(server=SERVER))
    return client


def on_message(topic, msg):
    print("Received '{payload}' from topic '{topic}'".format(
        payload=msg.decode(), topic=topic.decode()))
    data = ujson.loads(msg.decode())
    if topic.decode() == TOPIC_RESPONSE:
        if data.get('result') == 1:
            print('[Cloud] Attributes accepted')
        else:
            print('[Cloud] Attributes rejected:', data)
        return
    if topic.decode() != TOPIC1:
        return
    # 独立判断每个属性，同一条消息可同时控制多个设备。
    if 'pump1' in data:
        pmp1.value(data['pump1'])
    if 'pump2' in data:
        pmp2.value(data['pump2'])
    if 'motor' in data:
        motor.value(data['motor'])
    if 'led' in data:
        led.value(data['led'])


def subscribe(client):
    client.set_callback(on_message)
    client.subscribe(TOPIC1)
    client.subscribe(TOPIC_RESPONSE)
    print('[MQTT] Control and upload-response topics subscribed')


def main():
    print('[Main] Fish tank: upload diagnostics v1')
    utime.sleep(2)
    do_connect()
    client = mqtt_connect()
    subscribe(client)

    # 温度探头只初始化、扫描一次，沿用第一个探头的数据。
    ds = DS18X20(onewire.OneWire(Pin(OneWirePin)))
    roms = ds.scan()
    print('[Sensor] Temperature probes:', len(roms))
    rom = roms[0]

    # 启动后立即开始首次采集，之后按采集开始时间每10秒执行。
    last_sample_ms = utime.ticks_add(utime.ticks_ms(), -PUBLISH_INTERVAL_MS)
    conversion_start_ms = 0
    converting = False

    while True:
        client.check_msg()
        now = utime.ticks_ms()

        if not converting and utime.ticks_diff(now, last_sample_ms) >= PUBLISH_INTERVAL_MS:
            print('[Sensor] Starting temperature conversion')
            ds.convert_temp()
            conversion_start_ms = utime.ticks_ms()
            last_sample_ms = conversion_start_ms
            converting = True

        # 不在这里sleep(750)，交回主循环持续处理云端指令。
        if converting and utime.ticks_diff(now, conversion_start_ms) >= TEMP_CONVERSION_MS:
            msg_dict = {
                'turbidity': hj.read(),
                'level': level.read(),
                'temperature': ds.read_temp(rom)
            }
            msg = ujson.dumps(msg_dict)
            print('[Upload] Publishing:', msg)
            client.publish(TOPIC, msg, qos=0)
            print('[Upload] Sent; waiting for cloud response')
            converting = False

        utime.sleep_ms(LOOP_SLEEP_MS)


if __name__ == '__main__':
    main()
