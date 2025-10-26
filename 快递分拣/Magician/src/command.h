/****************************************Copyright(c)*****************************************************
**                            Shenzhen Yuejiang Technology Co., LTD.
**
**                                 http://www.dobot.cc
**
**--------------File Info---------------------------------------------------------------------------------
** File name:           command.h
** Latest modified Date:
** Latest Version:      V1.0.0
** Descriptions:
**
**--------------------------------------------------------------------------------------------------------
** Created by:          Edward
** Created date:        2017-8-15
** Version:             V1.0.0
** Descriptions:        Data definition
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#ifndef COMMAND_H
#define COMMAND_H

#include <stdint.h>
#include "ProtocolID.h"
#include "type.h"

#define MESSAGE_TIMEOUT 50

/*********************************************************************************************************
** Device function
*********************************************************************************************************/
extern int GetDeviceID(uint32_t *devicetime);
extern int GetDeviceTime(uint32_t *deviceTime);
extern int SetDeviceWIthL(bool isWithL);

/*********************************************************************************************************
** Pose
*********************************************************************************************************/
extern int GetPose(Pose *pose);
extern int GetPoseL(float *poseL);

/*********************************************************************************************************
** Home
*********************************************************************************************************/
extern int SetHomeCmd();
extern int SetHomeParamsCmd(Pose *pose);

/*********************************************************************************************************
** End effector function
*********************************************************************************************************/
extern int SetEndEffectorParams(EndEffectorParams *endEffectorParams);
extern int SetEndEffectorLaser(bool ison);
extern int SetEndEffectorSuctionCup(bool issuck);
extern int SeEndEffectorGritpper(EndEffectorGripper *endEffectorGripper);

/*********************************************************************************************************
** jog function
*********************************************************************************************************/
extern int SetJOGJointParams(JOGJointParams *jogJointParams);
extern int SetJOGCommonParams(JOGCommonParams *jogCommonParams);
extern int SetJOGCmd(JOGCmd *jogCmd);
extern int SetJOGCoordinateParams(JOGCoordinateParams *jogCoordinateParams);

/*********************************************************************************************************
** PTP function
*********************************************************************************************************/
extern int SetPTPJointParams(PTPJointParams *ptpJointParams);
extern int SetPTPCoordinateParams(PTPCoordinateParams *ptpCoordinateParams);
extern int SetPTPJumpParams(PTPJumpParams *ptpJumpParams);
extern int SetPTPCommonParams(PTPCommonParams *ptpCommonParams);
extern int SetPTPCmd(PTPCmd *ptpCmd);
extern int SetPTPLParams(PTPLParams *ptpLParams);
extern int SetPTPCmdWithL(PTPWithLCmd *ptpWithLCmd);

/*********************************************************************************************************
** EIO function
*********************************************************************************************************/
extern int SetIOMultiplexing(IOConfig *iOConfig);
extern int SetIODO(EIODO *eIODO);
extern int SetIOPWM(EIOPWM *eIOPWM);
extern int GetIODI(EIODI *eIODI);
extern int GetIOADC(EIOADC *eIOADC);
extern int SetEMotor(EMotor *eMotor);
extern int SetEMotorS(EMotorS *eMotorS);
extern int SetColorSensor(ColorSensor *colorSensor);
extern int GetColorSensor(ColorSensor *colorSensor);
extern int SetIRSwitch(IRSwitch *iRSwitch);
extern int GetIRSwitch(IRSwitch *iRSwitch);

extern int SetMotorPulse(PulseCmd *pulseCmd);

/*********************************************************************************************************
** QueueCmd function
*********************************************************************************************************/
extern int GetQueuedCmdCurrentIndex();
extern int SetQueuedCmdStartExec();
extern int SetQueuedCmdStopExec();
extern void WaitQueuedCmdFinished();

#endif
