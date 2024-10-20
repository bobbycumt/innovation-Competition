# -*- coding: utf-8 -*-
from machine import Pin,I2C,ADC
import utime
# from lib import urequests
import ujson
# import ssd1306
from umqtt.simple import MQTTClient
import onewire
from ds18x20 import DS18X20

hj=ADC(34)
level=ADC(35)
pmp1 = Pin(12, Pin.OUT)
pmp2 = Pin(13, Pin.OUT)
motor = Pin(14, Pin.OUT)
OneWirePin = 15
led = Pin(16,Pin.OUT)

# ssid='CU_future'
# psw='13582579999'
ssid = 'LEGOEducation'
psw = 'lego2232888'

SERVER = "bj-2-mqtt.iot-api.com"
PORT = 1883
CLIENT_ID = 'sr6avzfo'
USERNAME = '2dkx0lasne3bi7ak'
PASSWORD = '85mf2Hkk0p'
TOPIC = "attributes"
TOPIC1 = "attributes/push"

f=0
state=0
utime.sleep(2)

def readDS18x20(): 
    # the device is on GPIO22
    dat = Pin(OneWirePin)
    # create the onewire object
    ds = DS18X20(onewire.OneWire(dat))
    # scan for devices on the bus
    roms = ds.scan()# 扫描挂载在单总线上的ds18B20设备
    ds.convert_temp() # 数据转换
    utime.sleep_ms(750)
    values = []   

    for rom in roms:
        values.append(ds.read_temp(rom))
        
    # values.append(u"℃")
#     print(values,r"℃")
    return values

def do_connect():
    import network
    wlan = network.WLAN(network.STA_IF)
    wlan.active(True)
    if not wlan.isconnected():
        print('connecting to network...')
        wlan.connect(ssid, psw)
        while not wlan.isconnected():
             pass
    print('network config:', wlan.ifconfig())

def mqtt_connect():
    client = MQTTClient(CLIENT_ID, SERVER, PORT, USERNAME, PASSWORD)
    client.connect()
    print('Connected to MQTT Broker "{server}"'.format(server = SERVER))
    return client

def on_message(topic, msg):
    global f
    global state
    print("Received '{payload}' from topic '{topic}'\n".format(
        payload = msg.decode(), topic = topic.decode()))
    d=ujson.loads(msg.decode())
    k=list(d.keys())
    if k[0]=="pump1":
        pmp1.value(d["pump1"])
    elif k[0]=='pump2':   
        pmp2.value(d["pump2"])
    elif k[0]=='motor':   
        motor.value(d["motor"])
    elif k[0]=='led':   
        led.value(d["led"])        
def subscribe(client):
    client.set_callback(on_message)
    client.subscribe(TOPIC1)

def main():
    global f
    cnt=0
    do_connect()
    client= mqtt_connect()
    subscribe(client)
    while 1:
        client.check_msg()
        utime.sleep_ms(200)
        t=readDS18x20()[0];
        cnt+=1
        if cnt==50:
            msg_dict = {
                'turbidity': hj.read(),'level': level.read(),'temperature':t
            }
            msg = ujson.dumps(msg_dict)
            result = client.publish(TOPIC, msg)
            cnt=0
#         if f==0:
#             client.check_msg()
#             client.ping()
#             utime.sleep_ms(200)

if __name__=='__main__':
    main()

