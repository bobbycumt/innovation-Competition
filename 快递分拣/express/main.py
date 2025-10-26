# -*- coding: utf-8 -*-
from machine import Pin,I2C,ADC
import utime
import ujson
from umqtt.simple import MQTTClient


# hj=ADC(34)
# level=ADC(35)
pmp1 = Pin(14, Pin.OUT)
# pmp2 = Pin(13, Pin.OUT)
# motor = Pin(14, Pin.OUT)
# OneWirePin = 15
# led = Pin(16,Pin.OUT)

# ssid='CU_future'
# psw='13582579999'
ssid = 'LEGOEducation'
psw = 'lego2232888'

SERVER = b"bj-2-mqtt.iot-api.com"
PORT = 1883
CLIENT_ID = "3kw8d3xo"
USERNAME = 'vdqi1n05npsrztn1'
PASSWORD = 'Ex4Z2Cg8cc'
TOPIC = "attributes"
TOPIC1 = "attributes/push"

f=0
state=0
utime.sleep(2)

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
    client = MQTTClient(CLIENT_ID, SERVER, PORT, USERNAME, PASSWORD,keepalive=60)
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
    if d['btn']==1:
        print(111)
        f=1
        pmp1.value(0)
#     elif k[0]=='motor':   
#         motor.value(d["motor"])
#     elif k[0]=='led':   
#         led.value(d["led"])        
def subscribe(client):
    client.set_callback(on_message)
    client.subscribe(TOPIC1)

def main():
    global f
    cnt=0
    pmp1.value(1)
    do_connect()
    client= mqtt_connect()
    subscribe(client)
    client.publish(TOPIC,'{"btn":0}')
    while 1:
        client.check_msg()
        utime.sleep_ms(200)
        if f==1:
            utime.sleep_ms(500)
            client.publish(TOPIC,'{"btn":0}')
            pmp1.value(1)
            utime.sleep_ms(500)
            f=0
        

if __name__=='__main__':
    main()