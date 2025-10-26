/****************************************Copyright(c)*****************************************************
**                            Shenzhen Yuejiang Technology Co., LTD.
**
**                                 http://www.dobot.cc
**
**--------------File Info---------------------------------------------------------------------------------
** File name:           Dobot.h
** Latest modified Date:2017-8-15
** Latest Version:      V1.0.0
** Descriptions:        
**
**--------------------------------------------------------------------------------------------------------
** Created by:          Edward
** Created date:        2017-8-15
** Version:             V1.0.0
** Descriptions:        Mixly API
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#ifndef DOBOT_H
#define DOBOT_H

#include "type.h"
#include "Command.h"
#include <stdio.h>

typedef enum tagPos{
    L,
    X,
    Y,
    Z,
    R,
    JOINT1,
    JOINT2,
    JIONT3,
    JIONT4
}Pos;

typedef enum tagIOFunction {
    IOFunctionDummy,
    IOFunctionDO,
    IOFunctionPWM,
    IOFunctionDI,
    IOFunctionADC,
    IOFunctionDIPU,
    IOFunctionDIPD,
} IOFunction;

/*********************************************************************************************************
** Device Init
*********************************************************************************************************/
extern void Dobot_Init();

/*********************************************************************************************************
** Device function
*********************************************************************************************************/
extern uint32_t Dobot_GetDeviceTime(void);
extern void Dobot_SetDeviceWIthL(bool isWithL);

/*********************************************************************************************************
** Home function
*********************************************************************************************************/
extern void Dobot_SetHOMECmd(void);
extern float Dobot_GetPose(Pos p);

/*********************************************************************************************************
** EndEffector function
*********************************************************************************************************/
extern void Dobot_SetEndEffectorParams(float x,float y,float z);
extern void Dobot_SetEndEffectorLaser(uint8_t isEnable,float power);
extern void Dobot_SetEndEffectorSuctionCup(bool issuck);
extern void Dobot_SetEndEffectorGripper(bool isEnable,bool isGriped);

/*********************************************************************************************************
** JOG function
*********************************************************************************************************/
extern void Dobot_SetJOGCommonParams(float velocityRatio,float accelerationRatio);
extern void Dobot_SetJOGJointParams(float velocityJ1,float accelerationJ1,float velocityJ2,float accelerationJ2,float velocityJ3,float accelerationJ3,float velocityJ4,float accelerationJ4);
extern void Dobot_SetJOGCoordinateParams(float velocityX,float accelerationX,float velocityY,float accelerationY,float velocityZ,float accelerationZ,float velocityR,float accelerationR);
extern void Dobot_SetJOGCmd(uint8_t model);

/*********************************************************************************************************
** PTP function
*********************************************************************************************************/
extern void Dobot_SetPTPCommonParams(float velocityRatio,float accelerationRatio);
extern void Dobot_SetPTPJointParams(float velocityJ1,float accelerationJ1,float velocityJ2,float accelerationJ2,float velocityJ3,float accelerationJ3,float velocityJ4,float accelerationJ4);
extern void Dobot_SetPTPLParams(float velocityRatio,float accelerationRatio);
extern void Dobot_SetPTPJumpParams(float jumpHeight);
extern void Dobot_SetPTPCmd(uint8_t Model,float x,float y,float z,float r);
extern void Dobot_SetPTPWithLCmd(uint8_t Model,float x,float y,float z,float r,float l);

/*********************************************************************************************************
** EIO function
*********************************************************************************************************/
extern void Dobot_SetIOMultiplexing(uint8_t address,uint8_t function);
extern void Dobot_SetIODO(uint8_t address,uint8_t value);
extern void Dobot_SetIOPWM(uint8_t address,float freq,float duty);
extern uint8_t Dobot_GetIODI(uint8_t address);
extern uint16_t Dobot_GetIOADC(uint8_t address);
extern void Dobot_SetEMotor(uint8_t address,uint8_t enable,int32_t speed);
extern void Dobot_SetEMotorS(uint8_t address,uint8_t enable,int32_t speed,uint32_t deltaPulse);
extern void Dobot_SetColorSensor(uint8_t enable,uint8_t port,uint8_t version);
extern uint8_t Dobot_GetColorSensor(uint8_t color);
extern void Dobot_SetIRSwitch(uint8_t enable,uint8_t port);
extern uint8_t Dobot_GetIRSwitch(uint8_t port);
extern void Dobot_SetMotorPulse(float joint0 , float joint1 , float joint2 , float joint3 , float joint_re1 , float joint_re2);

#endif
