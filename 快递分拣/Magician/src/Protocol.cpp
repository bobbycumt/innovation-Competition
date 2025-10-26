/****************************************Copyright(c)*****************************************************
**                            Shenzhen Yuejiang Technology Co., LTD.
**
**                                 http://www.dobot.cc
**
**--------------File Info---------------------------------------------------------------------------------
** File name:           Protocol.cpp
** Latest modified Date:2016-06-01
** Latest Version:      V1.0.0
** Descriptions:        Protocol interface
**
**--------------------------------------------------------------------------------------------------------
** Created by:          Liu Zhufu
** Created date:        2016-03-14
** Version:             V1.0.0
** Descriptions:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include "Protocol.h"
#include <stdio.h>
#include <string.h>
#include <HardwareSerial.h>
#include "ProtocolID.h"
#include "command.h"
#include "symbol.h"
#include "arduino.h"
/*********************************************************************************************************
** Protocol buffer definition
*********************************************************************************************************/
#define RAW_BYTE_BUFFER_SIZE    256
#define PACKET_BUFFER_SIZE  1
#define PRINT_DEBUG_INFO    0
#if PRINT_DEBUG_INFO
static char __gPrintBuffer[16];
#endif

// Serial
uint8_t gSerialTXRawByteBuffer[RAW_BYTE_BUFFER_SIZE];
uint8_t gSerialRXRawByteBuffer[RAW_BYTE_BUFFER_SIZE];
Packet gSerialTXPacketBuffer[PACKET_BUFFER_SIZE];
Packet gSerialRXPacketBuffer[PACKET_BUFFER_SIZE];

ProtocolHandler gSerialProtocolHandler;
extern bool gIsCmdEchoReceived[ProtocolMax];

/*********************************************************************************************************
** Function name:       ProtocolInit
** Descriptions:        Init the protocol buffer etc.
** Input parameters:    None
** Output parameters:   None
** Returned value:      None
*********************************************************************************************************/
void ProtocolInit(void)
{
    // Init Serial protocol
    RingBufferInit(&gSerialProtocolHandler.txRawByteQueue, gSerialTXRawByteBuffer, RAW_BYTE_BUFFER_SIZE, sizeof(uint8_t));
    RingBufferInit(&gSerialProtocolHandler.rxRawByteQueue, gSerialRXRawByteBuffer, RAW_BYTE_BUFFER_SIZE, sizeof(uint8_t));
    RingBufferInit(&gSerialProtocolHandler.txPacketQueue, gSerialTXPacketBuffer, PACKET_BUFFER_SIZE, sizeof(Packet));
    RingBufferInit(&gSerialProtocolHandler.rxPacketQueue, gSerialRXPacketBuffer, PACKET_BUFFER_SIZE, sizeof(Packet));
}

/*********************************************************************************************************
** Function name:       Serialread
** Descriptions:        import data to rxbuffer
** Input parametersnone:
** Output parameters:   
** Returned value:      
*********************************************************************************************************/
void Serialread()
{
#if PRINT_DEBUG_INFO
    bool dataValid = false;
    if (SERIALNUM.available()) {
        Serial.print("[R]");
        dataValid = true;
    }
#endif
    while(SERIALNUM.available()) {
        uint8_t data = SERIALNUM.read();
#if PRINT_DEBUG_INFO
        sprintf(__gPrintBuffer, "0x%02x ", data);
        Serial.print(__gPrintBuffer);
#endif
        if (RingBufferIsFull(&gSerialProtocolHandler.rxRawByteQueue) == false) {
            RingBufferEnqueue(&gSerialProtocolHandler.rxRawByteQueue, &data);
        }
//        Serial.print(data,HEX);
//        Serial.print(" ");
    }
//    Serial.println(" ");
#if PRINT_DEBUG_INFO
    if (dataValid) {
        Serial.println("");
    }
#endif
}

/*********************************************************************************************************
** Function name:       ProtocolProcess
** Descriptions:        Process the protocol
** Input parameters:    None
** Output parameters:   None
** Returned value:      None
*********************************************************************************************************/
uint32_t ProtocolProcess(void)
{
    static Message message;
    // Translate message to raw byte to send
    MessageProcess(&gSerialProtocolHandler);
    // Send the raw bytes!
    if (RingBufferGetCount(&gSerialProtocolHandler.txRawByteQueue)) {
#if PRINT_DEBUG_INFO
        Serial.print("[W]");
#endif
        uint8_t data;
        while (RingBufferIsEmpty(&gSerialProtocolHandler.txRawByteQueue) == false) {
            RingBufferDequeue(&gSerialProtocolHandler.txRawByteQueue, &data);
            SERIALNUM.write(data);
#if PRINT_DEBUG_INFO
            sprintf(__gPrintBuffer, "0x%02x ", data);
            Serial.print(__gPrintBuffer);
#endif
        }
#if PRINT_DEBUG_INFO
        Serial.println("");
#endif
    }
    delay(50);
    do {
        if (SERIALNUM.available()) {
			delay(4);
            break;
        }
        delay(150);
    } while (0);
    Serialread();

    // Translate raw byte to message
    MessageProcess(&gSerialProtocolHandler);

    // Read the message!
    if(MessageRead(&gSerialProtocolHandler, &message)==ProtocolNoError) {
        gIsCmdEchoReceived[message.id] = true;
        return (uint32_t)&message.params;
    } else {
        Serial.println("Failed to read!!!");
    }
    return 0;
}
