/****************************************Copyright(c)*****************************************************
**                            Shenzhen Yuejiang Technology Co., LTD.
**
**                                 http://www.dobot.cc
**
**--------------File Info---------------------------------------------------------------------------------
** File name:           Command.cpp
** Latest modified Date:2018-7-18
** Latest Version:      V1.1.0
** Descriptions:        Command body
**
**--------------------------------------------------------------------------------------------------------
** Created by:          Edward
** Created date:        2017-8-15
** Version:             V1.0.0
** Descriptions:        Command API
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include <stdio.h>
#include <string.h>
#include <arduino.h>
#include "command.h"
#include "Protocol.h"
#include "ProtocolID.h"
#include "type.h"

bool gIsCmdEchoReceived[ProtocolMax];
static uint64_t gQueuedCmdWriteIndex = 0;
static uint64_t gQueuedCmdCurrentIndex = 0;

static Message gMessage;
static uint32_t gParamsPointer = 0;

static char gPrintBuffer[32];

#define INIT_MESSAGE()\
    memset(&gMessage, 0, sizeof(Message))

/*********************************************************************************************************
** Function name:       WaitCmdEcho
** Descriptions:        Wait the echo of command
** Input parameters:    
** Output parameters:   
** Returned value:      
*********************************************************************************************************/
#define WaitCmdEcho()                                           \
                                                                \
    gParamsPointer = 0;                                         \
    while (1) {                                                 \
        RingBufferClear(&gSerialProtocolHandler.txPacketQueue); \
        RingBufferClear(&gSerialProtocolHandler.rxPacketQueue); \
        RingBufferClear(&gSerialProtocolHandler.txRawByteQueue);\
        RingBufferClear(&gSerialProtocolHandler.rxRawByteQueue);\
                                                                \
        gIsCmdEchoReceived[gMessage.id] = false;                \
        MessageWrite(&gSerialProtocolHandler, &gMessage);       \
                                                                \
        gParamsPointer = ProtocolProcess();                     \
        if (gIsCmdEchoReceived[gMessage.id]) {                  \
            break;                                              \
        }                                                       \
        sprintf(gPrintBuffer, "[ERROR]������Command timeout:0x%02x\r\n", gMessage.id);\
        Serial.print(gPrintBuffer);\
        delay(MESSAGE_TIMEOUT);                                 \
    }                                                           \
    if (gParamsPointer == 0) {                                  \
        Serial.println("Parameter pointer error!!!");           \
        while(1);                                               \
    }                                                           \
    (void)gParamsPointer;

/*********************************************************************************************************
** Function name:       WaitQueuedCmdFinished
** Descriptions:        Wait a queued command to finish
** Input parameters:    
** Output parameters:   
** Returned value:      
*********************************************************************************************************/
void WaitQueuedCmdFinished(void)
{
    while (1) {
        delay(50);
        GetQueuedCmdCurrentIndex();
        if (gQueuedCmdCurrentIndex >= gQueuedCmdWriteIndex) {
            break;
        }
    }
}

/*********************************************************************************************************
** Function name:       GetDeviceID
** Descriptions:        Get device ID
** Input parameters:    
** Output parameters:   
** Returned value:      true
*********************************************************************************************************/
int GetDeviceID(uint32_t *devicetime)
{
    INIT_MESSAGE();
    gMessage.id = ProtocolDeviceID;
    gMessage.rw = false;
    gMessage.isQueued = false;
    gMessage.paramsLen = 0;

    WaitCmdEcho();

    memcpy(devicetime, (void *)gParamsPointer, sizeof(uint32_t));

    return true;
}

/*********************************************************************************************************
** Function name:       GetDeviceTime
** Descriptions:        Get DeviceTime
** Input parameters:    deviceTime, isQueued
** Output parameters:   queuedCmdIndex
** Returned value:      true
*********************************************************************************************************/
int GetDeviceTime(uint32_t *deviceTime)
{
    INIT_MESSAGE();
    gMessage.id = ProtocolDeviceTime;
    gMessage.rw = false;
    gMessage.isQueued = false;
    gMessage.paramsLen = 0;

    WaitCmdEcho();

    memcpy(deviceTime, (void *)gParamsPointer, sizeof(uint32_t));

    return true;
}

/*********************************************************************************************************
** Function name:       SetDeviceWIthL
** Descriptions:        Set end effector parameters
** Input parameters:    endEffectorParams, isQueued
** Output parameters:   queuedCmdIndex
** Returned value:      true
*********************************************************************************************************/
int SetDeviceWIthL(bool isWithL)
{
    INIT_MESSAGE();
    gMessage.id = ProtocolDeviceWithL;
    gMessage.rw = true;
    gMessage.isQueued = false;
    gMessage.paramsLen = sizeof(isWithL);
    gMessage.params[0] = isWithL;

    WaitCmdEcho();

    return true;
}

/*********************************************************************************************************
** Function name:       GetPose
** Descriptions:        Set end effector parameters
** Input parameters:    endEffectorParams, isQueued
** Output parameters:   queuedCmdIndex
** Returned value:      true
*********************************************************************************************************/
int GetPose(Pose *pose)
{
    INIT_MESSAGE();
    gMessage.id = ProtocolGetPose;
    gMessage.rw = false;
    gMessage.isQueued = false;
    gMessage.paramsLen = 0;

    WaitCmdEcho();

    memcpy(pose, (void *)gParamsPointer, sizeof(Pose));

    return true;
}

/*********************************************************************************************************
** Function name:       GetPose
** Descriptions:        Set end effector parameters
** Input parameters:    endEffectorParams, isQueued
** Output parameters:   queuedCmdIndex
** Returned value:      true
*********************************************************************************************************/
int GetPoseL(float *poseL)
{
    INIT_MESSAGE();
    gMessage.id = ProtocolGetPoseL;
    gMessage.rw = false;
    gMessage.isQueued = false;
    gMessage.paramsLen = 0;

    WaitCmdEcho();

    memcpy(poseL, (void *)gParamsPointer, sizeof(float));

    return true;
}

/*********************************************************************************************************
** Function name:       SetHomeCmd
** Descriptions:        Set Hmoe
** Input parameters:     isQueued
** Output parameters:   queuedCmdIndex
** Returned value:      true
*********************************************************************************************************/
int SetHomeCmd()
{
    INIT_MESSAGE();
    gMessage.id = ProtocolHOMECmd;
    gMessage.rw = true;
    gMessage.isQueued = true;
    gMessage.paramsLen = 0;

    WaitCmdEcho();

    memcpy(&gQueuedCmdWriteIndex, (void *)gParamsPointer, sizeof(uint64_t));

    return true;
}

/*********************************************************************************************************
** Function name:       SetHomeCmd
** Descriptions:        Set Hmoe
** Input parameters:     isQueued
** Output parameters:   queuedCmdIndex
** Returned value:      true
*********************************************************************************************************/
int SetHomeParamsCmd(Pose *pose)
{
    INIT_MESSAGE();
    gMessage.id = ProtocolHOMEParams;
    gMessage.rw = true;
    gMessage.isQueued = false;
    gMessage.paramsLen = 0;
    memcpy(gMessage.params, (uint8_t *)pose, gMessage.paramsLen);

    WaitCmdEcho();

    return true;
}

/*********************************************************************************************************
** Function name:       SetEndEffectorParams
** Descriptions:        Set end effector parameters
** Input parameters:    endEffectorParams, isQueued
** Output parameters:   queuedCmdIndex
** Returned value:      true
*********************************************************************************************************/
int SetEndEffectorParams(EndEffectorParams *endEffectorParams)
{
    INIT_MESSAGE();
    gMessage.id = ProtocolEndEffectorParams;
    gMessage.rw = true;
    gMessage.isQueued = false;
    gMessage.paramsLen = sizeof(EndEffectorParams);
    memcpy(gMessage.params, (uint8_t *)endEffectorParams, gMessage.paramsLen);

    WaitCmdEcho();

    return true;
}

/*********************************************************************************************************
** Function name:       SetEndEffectorLaser
** Descriptions:        Set the laser output
** Input parameters:    on,isQueued
** Output parameters:   queuedCmdIndex
** Returned value:      true
*********************************************************************************************************/
int SetEndEffectorLaser(bool ison)
{
    INIT_MESSAGE();
    gMessage.id = ProtocolEndEffectorLaser;
    gMessage.rw = true;
    gMessage.isQueued = false;
    gMessage.paramsLen = sizeof(ison);
    gMessage.params[0] = ison;

    WaitCmdEcho();

    return true;
}

/*********************************************************************************************************
** Function name:       SetEndEffectorSuctionCup
** Descriptions:        Set the suctioncup output
** Input parameters:    suck,isQueued
** Output parameters:   queuedCmdIndex
** Returned value:      true
*********************************************************************************************************/
int SetEndEffectorSuctionCup(bool issuck)
{
    Message gMessage;
    memset(&gMessage, 0, sizeof(Message));
    gMessage.id = ProtocolEndEffectorSuctionCup;
    gMessage.rw = true;
    gMessage.isQueued = false;
    gMessage.paramsLen = 2;
    gMessage.params[0] = issuck;
    gMessage.params[1] = issuck;

    WaitCmdEcho();

    return true;
}

/*********************************************************************************************************
** Function name:       SetEndEffectorGripper
** Descriptions:        Set the gripper output
** Input parameters:    grip,isQueued
** Output parameters:   queuedCmdIndex
** Returned value:      true
*********************************************************************************************************/
int SeEndEffectorGritpper(EndEffectorGripper *endEffectorGripper)
{
    INIT_MESSAGE();
    gMessage.id = ProtocolEndEffectorGripper;
    gMessage.rw = true;
    gMessage.isQueued = false;
    gMessage.paramsLen = sizeof(EndEffectorGripper);
    gMessage.params[0] = endEffectorGripper->isEnable;
    gMessage.params[1] = endEffectorGripper->isGriped;

    WaitCmdEcho();

    return true;
}

/*********************************************************************************************************
** Function name:       SetJOGJointParams
** Descriptions:        Sets the joint jog parameter
** Input parameters:    jogJointParams,isQueued
** Output parameters:   queuedCmdIndex
** Returned value:      true
*********************************************************************************************************/
int SetJOGJointParams(JOGJointParams *jogJointParams)
{
    INIT_MESSAGE();
    gMessage.id = ProtocolJOGJointParams;
    gMessage.rw = true;
    gMessage.isQueued = false;
    gMessage.paramsLen = sizeof(JOGJointParams);
    memcpy(gMessage.params, (uint8_t *)jogJointParams, gMessage.paramsLen);

    WaitCmdEcho();

    return true;
}

/*********************************************************************************************************
** Function name:       SetJOGCoordinateParams
** Descriptions:        Sets the axis jog parameter
** Input parameters:    jogCoordinateParams,isQueued
** Output parameters:   queuedCmdIndex
** Returned value:      true
*********************************************************************************************************/
int SetJOGCoordinateParams(JOGCoordinateParams *jogCoordinateParams)
{
    INIT_MESSAGE();
    gMessage.id = ProtocolJOGCoordinateParams;
    gMessage.rw = true;
    gMessage.isQueued = false;
    gMessage.paramsLen = sizeof(JOGCoordinateParams);
    memcpy(gMessage.params, (uint8_t *)jogCoordinateParams, gMessage.paramsLen);

    WaitCmdEcho();

    return true;
}

/*********************************************************************************************************
** Function name:       SetJOGCommonParams
** Descriptions:        Sets the jog common parameter
** Input parameters:    jogCommonParams,isQueued
** Output parameters:   queuedCmdIndex
** Returned value:      true
*********************************************************************************************************/
int SetJOGCommonParams(JOGCommonParams *jogCommonParams)
{
    INIT_MESSAGE();
    gMessage.id = ProtocolJOGCommonParams;
    gMessage.rw = true;
    gMessage.isQueued = false;
    gMessage.paramsLen = sizeof(JOGCommonParams);
    memcpy(gMessage.params, (uint8_t *)jogCommonParams, gMessage.paramsLen);

    WaitCmdEcho();

    return true;
}

/*********************************************************************************************************
** Function name:       SetJOGCmd
** Descriptions:        Execute the jog function
** Input parameters:    jogCmd,isQueued
** Output parameters:   queuedCmdIndex
** Returned value:      true
*********************************************************************************************************/
int SetJOGCmd(JOGCmd *jogCmd)
{
    INIT_MESSAGE();
    gMessage.id = ProtocolJOGCmd;
    gMessage.rw = true;
    gMessage.isQueued = false;
    gMessage.paramsLen = sizeof(JOGCmd);
    memcpy(gMessage.params, (uint8_t *)jogCmd, gMessage.paramsLen);

    WaitCmdEcho();

    return true;
}

/*********************************************************************************************************
** Function name:       SetPTPJointParams
** Descriptions:        Sets the articulation point parameter
** Input parameters:    ptpJointParams,isQueued
** Output parameters:   queuedCmdIndex
** Returned value:      true
*********************************************************************************************************/
int SetPTPJointParams(PTPJointParams *ptpJointParams)
{
    Message gMessage;
    memset(&gMessage, 0, sizeof(Message));
    gMessage.id = ProtocolPTPJointParams;
    gMessage.rw = true;
    gMessage.isQueued = false;
    gMessage.paramsLen = sizeof(PTPJointParams);
    memcpy(gMessage.params,(uint8_t *)ptpJointParams, gMessage.paramsLen);

    WaitCmdEcho();

    return true;
}

/*********************************************************************************************************
** Function name:       SetPTPCoordinateParams
** Descriptions:        Sets the coordinate position parameter
** Input parameters:    ptpCoordinateParams,isQueued
** Output parameters:   queuedCmdIndex
** Returned value:      true
*********************************************************************************************************/
int SetPTPCoordinateParams(PTPCoordinateParams *ptpCoordinateParams)
{
    INIT_MESSAGE();
    gMessage.id = ProtocolPTPCoordinateParams;
    gMessage.rw = true;
    gMessage.isQueued = false;
    gMessage.paramsLen = sizeof(PTPCoordinateParams);
    memcpy(gMessage.params, (uint8_t *)ptpCoordinateParams, gMessage.paramsLen);

    WaitCmdEcho();

    return true;
}

/*********************************************************************************************************
** Function name:       SetPTPJumpParams
** Descriptions:        Set the gate type parameter
** Input parameters:    ptpJumpParams,isQueued
** Output parameters:   queuedCmdIndex
** Returned value:      true
*********************************************************************************************************/
int SetPTPJumpParams(PTPJumpParams *ptpJumpParams)
{
    INIT_MESSAGE();
    gMessage.id = ProtocolPTPJumpParams;
    gMessage.rw = true;
    gMessage.isQueued = false;
    gMessage.paramsLen = sizeof(PTPJumpParams);
    memcpy(gMessage.params,(uint8_t *)ptpJumpParams, gMessage.paramsLen);

    WaitCmdEcho();

    return true;
}

/*********************************************************************************************************
** Function name:       SetPTPCommonParams
** Descriptions:        Set point common parameters
** Input parameters:    ptpCommonParams,isQueued
** Output parameters:   queuedCmdIndex
** Returned value:      true
*********************************************************************************************************/
int SetPTPCommonParams(PTPCommonParams *ptpCommonParams)
{
    INIT_MESSAGE();
    gMessage.id = ProtocolPTPCommonParams;
    gMessage.rw = true;
    gMessage.isQueued = false;
    gMessage.paramsLen = sizeof(PTPCommonParams);
    memcpy(gMessage.params, (uint8_t *)ptpCommonParams, gMessage.paramsLen);

    WaitCmdEcho();

    return true;
}

/*********************************************************************************************************
** Function name:       SetPTPCommonParams
** Descriptions:        Set point common parameters
** Input parameters:    ptpCommonParams,isQueued
** Output parameters:   queuedCmdIndex
** Returned value:      true
*********************************************************************************************************/
int SetPTPLParams(PTPLParams *ptpLParams)
{
    INIT_MESSAGE();
    gMessage.id = ProtocolPTPLParams;
    gMessage.rw = true;
    gMessage.isQueued = false;
    gMessage.paramsLen = sizeof(PTPLParams);
    memcpy(gMessage.params, (uint8_t *)ptpLParams, gMessage.paramsLen);

    WaitCmdEcho();

    return true;
}

/*********************************************************************************************************
** Function name:       SetPTPCmd
** Descriptions:        Execute the position function
** Input parameters:    ptpCmd,isQueued
** Output parameters:   queuedCmdIndex
** Returned value:      true
*********************************************************************************************************/
int SetPTPCmd(PTPCmd *ptpCmd)
{
    INIT_MESSAGE();
    memset(&gMessage, 0, sizeof(Message));
    gMessage.id = ProtocolPTPCmd;
    gMessage.rw = true;
    gMessage.isQueued = true;
    gMessage.paramsLen = sizeof(PTPCmd);

    memcpy(gMessage.params, (uint8_t *)ptpCmd, gMessage.paramsLen);
    WaitCmdEcho();
    memcpy(&gQueuedCmdWriteIndex, (void *)gParamsPointer, sizeof(uint64_t));

    return true;
}

/*********************************************************************************************************
** Function name:       SetPTPCmd
** Descriptions:        Execute the position function
** Input parameters:    ptpCmd,isQueued
** Output parameters:   queuedCmdIndex
** Returned value:      true
*********************************************************************************************************/
int SetPTPCmdWithL(PTPWithLCmd *ptpWithLCmd)
{
    INIT_MESSAGE();
    gMessage.id = ProtocolPTPWithLCmd;
    gMessage.rw = true;
    gMessage.isQueued = true;
    gMessage.paramsLen = sizeof(PTPWithLCmd);
    memcpy(gMessage.params, (uint8_t *)ptpWithLCmd, gMessage.paramsLen);

    WaitCmdEcho();

    memcpy(&gQueuedCmdWriteIndex, (void *)gParamsPointer, sizeof(uint64_t));

    return true;
}

/*********************************************************************************************************
**
**
**                                          EIO

*********************************************************************************************************/
/*********************************************************************************************************
** Function name:       SetIOMultiplexing
** Descriptions:        SetIOMultiplexing
** Input parameters:    *iOConfig,endEffectorParams, isQueued
** Output parameters:   queuedCmdIndex
** Returned value:      true
*********************************************************************************************************/
int SetIOMultiplexing(IOConfig *iOConfig)
{
    INIT_MESSAGE();
    gMessage.id = ProtocolIOMultiplexing;
    gMessage.rw = true;
    gMessage.isQueued = false;
    gMessage.paramsLen = sizeof(IOConfig);
    memcpy(gMessage.params, (uint8_t *)iOConfig, gMessage.paramsLen);

    WaitCmdEcho();

    return true;
}

/*********************************************************************************************************
** Function name:
** Descriptions:
** Input parameters:     
** Output parameters:   queuedCmdIndex
** Returned value:      true
*********************************************************************************************************/
int SetIODO(EIODO *eIODO)
{
    INIT_MESSAGE();
    gMessage.id = ProtocolIODO;
    gMessage.rw = true;
    gMessage.isQueued = false;
    gMessage.paramsLen = sizeof(eIODO);
    memcpy(gMessage.params, (uint8_t *)eIODO, gMessage.paramsLen);

    WaitCmdEcho();

    return true;
}

/*********************************************************************************************************
** Function name:       SetIOPWM
** Descriptions:
** Input parameters:    
** Output parameters:   queuedCmdIndex
** Returned value:      true
*********************************************************************************************************/
int SetIOPWM(EIOPWM *eIOPWM)
{
    INIT_MESSAGE();
    gMessage.id = ProtocolIOPWM;
    gMessage.rw = true;
    gMessage.isQueued = false;
    gMessage.paramsLen = sizeof(EIOPWM);
    memcpy(gMessage.params, (uint8_t *)eIOPWM, gMessage.paramsLen);

    WaitCmdEcho();

    return true;
}

/*********************************************************************************************************
** Function name:
** Descriptions:
** Input parameters:     
** Output parameters:   queuedCmdIndex
** Returned value:      true
*********************************************************************************************************/
int GetIODI(EIODI *eIODI)
{
    INIT_MESSAGE();
    gMessage.id = ProtocolIODI;
    gMessage.rw = false;
    gMessage.isQueued = false;
    gMessage.paramsLen = sizeof(EIODI);
    memcpy(gMessage.params, (uint8_t *)eIODI, gMessage.paramsLen);

    WaitCmdEcho();

    memcpy(eIODI, (void *)gParamsPointer, sizeof(EIODI));

    return true;
}

/*********************************************************************************************************
** Function name:       GetIOADC
** Descriptions:
** Input parameters:    
** Output parameters:   queuedCmdIndex
** Returned value:      true
*********************************************************************************************************/
int GetIOADC(EIOADC *eIOADC)
{
    INIT_MESSAGE();
    gMessage.id = ProtocolIOADC;
    gMessage.rw = false;
    gMessage.isQueued = false;
    gMessage.paramsLen = sizeof(EIOADC);
    memcpy(gMessage.params, (uint8_t *)eIOADC, gMessage.paramsLen);

    WaitCmdEcho();

    memcpy(eIOADC, (void *)gParamsPointer, sizeof(EIOADC));

    return true;
}

/*********************************************************************************************************
** Function name:       SetEMotor
** Descriptions:
** Input parameters:    
** Output parameters:   queuedCmdIndex
** Returned value:      true
*********************************************************************************************************/
int SetEMotor(EMotor *eMotor)
{
    INIT_MESSAGE();
    gMessage.id = ProtocolEMotor;
    gMessage.rw = true;
    gMessage.isQueued = false;
    gMessage.paramsLen = sizeof(EMotor);
    memcpy(gMessage.params, (uint8_t *)eMotor, gMessage.paramsLen);

    WaitCmdEcho();

    return true;
}

/*********************************************************************************************************
** Function name:       SetEMotorS
** Descriptions:
** Input parameters:    
** Output parameters:   queuedCmdIndex
** Returned value:      true
*********************************************************************************************************/
int SetEMotorS(EMotorS *eMotorS)
{
    INIT_MESSAGE();
    gMessage.id = ProtocolEMotorS;
    gMessage.rw = true;
    gMessage.isQueued = false;
    gMessage.paramsLen = sizeof(EMotorS);
    memcpy(gMessage.params, (uint8_t *)eMotorS, gMessage.paramsLen);

    WaitCmdEcho();

    return true;
}

/*********************************************************************************************************
** Function name:       SetColorSensor
** Descriptions:
** Input parameters:    
** Output parameters:   queuedCmdIndex
** Returned value:      true
*********************************************************************************************************/
int SetColorSensor(ColorSensor *colorSensor)
{
    INIT_MESSAGE();
    gMessage.id = ProtocolColorSensor;
    gMessage.rw = true;
    gMessage.isQueued = false;
    gMessage.paramsLen = sizeof(ColorSensor) - 3;
    memcpy(gMessage.params, (uint8_t *)colorSensor, gMessage.paramsLen);

    WaitCmdEcho();

    return true;
}

/*********************************************************************************************************
** Function name:       GetColorSensor
** Descriptions:
** Input parameters:    
** Output parameters:   queuedCmdIndex
** Returned value:      true
*********************************************************************************************************/
int GetColorSensor(ColorSensor *colorSensor)
{
    INIT_MESSAGE();
    gMessage.id = ProtocolColorSensor;
    gMessage.rw = false;
    gMessage.isQueued = false;
    gMessage.paramsLen = 0;

    WaitCmdEcho();

    memcpy(&colorSensor->r, (void *)gParamsPointer,sizeof(ColorSensor)-3);

    return true;
}
/*********************************************************************************************************
** Function name:       SetIRSwitch
** Descriptions:
** Input parameters:    
** Output parameters:   queuedCmdIndex
** Returned value:      true
*********************************************************************************************************/
int SetIRSwitch(IRSwitch *iRSwitch)
{
    INIT_MESSAGE();
    gMessage.id = ProtocolIRSwitch;
    gMessage.rw = true;
    gMessage.isQueued = false;
    gMessage.paramsLen = sizeof(IRSwitch) - 1;
    memcpy(gMessage.params, (uint8_t *)iRSwitch, gMessage.paramsLen);

    WaitCmdEcho();

    return true;
}

/*********************************************************************************************************
** Function name:
** Descriptions:
** Input parameters:     isQueued
** Output parameters:   queuedCmdIndex
** Returned value:      true
*********************************************************************************************************/
int GetIRSwitch(IRSwitch *iRSwitch)
{
    INIT_MESSAGE();
    gMessage.id = ProtocolIRSwitch;
    gMessage.rw = false;
    gMessage.isQueued = false;
    gMessage.paramsLen = sizeof(iRSwitch->port);
    memcpy(gMessage.params, &iRSwitch->port, gMessage.paramsLen);

    WaitCmdEcho();

    //copy params receive
    memcpy(&iRSwitch->value, (void *)gParamsPointer,sizeof(iRSwitch->value));

    return true;
}

/*********************************************************************************************************
** Function name:
** Descriptions:
** Input parameters:     isQueued
** Output parameters:   queuedCmdIndex
** Returned value:      true
*********************************************************************************************************/
int SetMotorPulse(PulseCmd *pulseCmd)
{
    INIT_MESSAGE();
    gMessage.id = ProtocolFunctionPulseMode;
    gMessage.rw = true;
    gMessage.isQueued = false;
    gMessage.paramsLen = sizeof(PulseCmd);
    memcpy(gMessage.params, pulseCmd, gMessage.paramsLen);

    WaitCmdEcho();

    return true;
}

/*********************************************************************************************************
** Function name:       GetQueuedCmdCurrentIndex
** Descriptions:        check current index
** Input parameters:    noQueued
** Output parameters:   queuedCmdIndex
** Returned value:      true
*********************************************************************************************************/
int GetQueuedCmdCurrentIndex()
{
    INIT_MESSAGE();
    gMessage.id = ProtocolQueuedCmdCurrentIndex;
    gMessage.rw = false;
    gMessage.isQueued = false;
    gMessage.paramsLen = 0;

    WaitCmdEcho();
    memcpy(&gQueuedCmdCurrentIndex, (void *)gParamsPointer,sizeof(uint64_t));

    return true;
}

/*********************************************************************************************************
** Function name:       GetQueuedCmdCurrentIndex
** Descriptions:        check current index
** Input parameters:    noQueued
** Output parameters:   queuedCmdIndex
** Returned value:      true
*********************************************************************************************************/
int SetQueuedCmdStartExec()
{
    INIT_MESSAGE();
    gMessage.id = ProtocolQueuedCmdStartExec;
    gMessage.rw = false;
    gMessage.isQueued = false;
    gMessage.paramsLen = 0;

    WaitCmdEcho();

    return true;
}

/*********************************************************************************************************
** Function name:       GetQueuedCmdCurrentIndex
** Descriptions:        check current index
** Input parameters:    noQueued
** Output parameters:   queuedCmdIndex
** Returned value:      true
*********************************************************************************************************/
int SetQueuedCmdStopExec()
{
    INIT_MESSAGE();
    gMessage.id = ProtocolQueuedCmdStopExec ;
    gMessage.rw = false;
    gMessage.isQueued = false;
    gMessage.paramsLen = 0 ;

    WaitCmdEcho();

    return true;
}
