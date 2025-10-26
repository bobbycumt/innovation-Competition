/****************************************Copyright(c)*****************************************************
**                            Shenzhen Yuejiang Technology Co., LTD.
**
**                                 http://www.dobot.cc
**
**--------------File Info---------------------------------------------------------------------------------
** File name:           DobotInit.cpp
** Latest modified Date:2017-8-15
** Latest Version:      V1.0.0
** Descriptions:        Init body
**
**--------------------------------------------------------------------------------------------------------
** Created by:          Edward
** Created date:        2017-8-15
** Version:             V1.0.0
** Descriptions:        Init Dobot
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include "FlexiTimer2.h"
#include "stdio.h"
#include <arduino.h>
#include "HardwareSerial.h"
#include "Protocol.h"
#include "Dobot.h"

/*********************************************************************************************************
** Function name:       Serial_putc
** Descriptions:        Remap Serial to Printf
** Input parametersnone:
** Output parameters:   
** Returned value:       
*********************************************************************************************************/
int Serial_putc(char c, struct __file *)
{
    Serial.write(c);
    return c;
}

/*********************************************************************************************************
** Function name:       printf_begin
** Descriptions:        Initializes Printf
** Input parameters:    
** Output parameters:
** Returned value:      
*********************************************************************************************************/
void printf_begin(void)
{
    fdevopen( &Serial_putc, 0 );
}

/*********************************************************************************************************
** Function name:       Dobot_Init
** Descriptions:        Init Dobot
** Input parameters:    
** Output parameters:
** Returned value:      
*********************************************************************************************************/
void Dobot_Init()
{
    SERIALNUM.begin(115200);
    delay(1000);

    ProtocolInit();

    Serial.println("Dobot Init");
    for(int i = 0; i < 21; i++){
        Dobot_SetIOMultiplexing(i,IOFunctionDI);
    }
    SetQueuedCmdStartExec();
}
