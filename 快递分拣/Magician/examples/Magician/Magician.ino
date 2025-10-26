
/****************************************Copyright(c)*****************************************************
**                            Shenzhen Yuejiang Technology Co., LTD.
**
**                                 http://www.dobot.cc
**
**--------------File Info---------------------------------------------------------------------------------
** File name:           main.cpp
** Latest modified Date:2016-10-24
** Latest Version:      V2.0.0
** Descriptions:        main body
**
**--------------------------------------------------------------------------------------------------------
** Modify by:           Edward
** Modified date:       2017-4-6
** Version:             V1.1.0
** Descriptions:        Modified,From DobotDemoForSTM32
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include "Dobot.h"


/*********************************************************************************************************
** Function name:       setup
** Descriptions:        Initializes Serial
** Input parameters:    none
** Output parameters:   none
** Returned value:      none
*********************************************************************************************************/
void setup(){
  Dobot_Init();
  }


/*********************************************************************************************************
** Function name:       loop
** Descriptions:        Program entry
** Input parameters:    none
** Output parameters:   none
** Returned value:      none
*********************************************************************************************************/
void loop() 
{
  
    printf("\r\n======Enter demo application======\r\n");
    //Dobot_GetPoseEx(1);
    Pose pose;
    pose.x = 250;
    pose.y = 0;
    pose.z = 0;
    pose.rHead = 10;
    //SetHomeParamsCmd(&pose,true,&gQueuedCmdIndex);

    GetHomeParamsCmd(false, &gQueuedCmdIndex);
    printf("\r\n======Finish demo application======\r\n");
    while(0){
    }
  #if 1 
    Dobot_SetPTPWithLCmdEx(JUMP_XYZ,200,0,0,0,20);
    Dobot_SetPTPCmdEx(JUMP_XYZ,200,0,0,0);

    while(1){
      Dobot_SetEMotorEx(0,1,1000);
//        digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
//        //Dobot_SeEndEffectorGritpperEx(true,true);
//        delay(2000);                       // wait for a second
//        digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
//        //Dobot_SeEndEffectorGritpperEx(true,false);
//        delay(2000);         
    }
    #endif
}

