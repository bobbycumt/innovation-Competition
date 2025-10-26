/****************************************Copyright(c)*****************************************************
**                            Shenzhen Yuejiang Technology Co., LTD.
**
**                                 http://www.dobot.cc
**
**--------------File Info---------------------------------------------------------------------------------
** File name:           Dobot.cpp
** Latest modified Date:2017-8-15
** Latest Version:      V1.0.0
** Descriptions:        Dobot body
**
**--------------------------------------------------------------------------------------------------------
** Created by:          Edward
** Created date:        2017-8-15
** Version:             V1.0.0
** Descriptions:        Mixly API
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include "command.h"
#include "type.h"
#include "stdio.h"
#include "Dobot.h"
#include "HardwareSerial.h"
#include "arduino.h"

/*********************************************************************************************************
** Function name:       Dobot_GetDeviceTimeEX
** Descriptions:        Get Device Time
** Input parameters:    none
** Output parameters:   none
** Returned value:      none
*********************************************************************************************************/
uint32_t Dobot_GetDeviceTime(void)
{
    uint32_t deviceTime;

    GetDeviceTime(&deviceTime);

    return deviceTime;
}

/*********************************************************************************************************
** Function name:       Dobot_SetDeviceWIthLEX
** Descriptions:        Set L
** Input parameters:    none
** Output parameters:   none
** Returned value:      none
*********************************************************************************************************/
void Dobot_SetDeviceWIthL(bool isWithL)
{
    SetDeviceWIthL(isWithL);
}

/*********************************************************************************************************
** Function name:       Dobot_GetPose
** Descriptions:        Get Pose
** Input parameters:    none
** Output parameters:   none
** Returned value:      Pose
*********************************************************************************************************/
float Dobot_GetPose(uint8_t temp)
{
    static Pose pose;
    static float poseL;

    GetPose(&pose);

    switch(temp){
        case L:
            GetPoseL(&poseL);
            return poseL;
        case X:
            return pose.x;
        break;
        case Y:
            return pose.y;
        break;
        case Z:
            return pose.z;
        break;
        case R:
            return pose.rHead;
        break;
        case JOINT1:
            return pose.jointAngle[0];
        break;
        case JOINT2:
            return pose.jointAngle[1];
        break;
        case JIONT3:
            return pose.jointAngle[2];
        break;
        case JIONT4:
            return pose.jointAngle[3];
        break;
        default:
            return 0;
        break;
    }
    return 0;
}

/*********************************************************************************************************
** Function name:       Dobot_SetHOMECmd
** Descriptions:        SetHome
** Input parameters:    none
** Output parameters:   none
** Returned value:      none
*********************************************************************************************************/
void Dobot_SetHOMECmd(void)
{
    SetHomeCmd();
    WaitQueuedCmdFinished();
}

/*********************************************************************************************************
** Function name:       Dobot_SetEndEffectorParams
** Descriptions:        Set EndEffector Params
** Input parameters:    X,Y,Z
** Output parameters:   none
** Returned value:      none
*********************************************************************************************************/
void Dobot_SetEndEffectorParams(float x, float y, float z)
{
    static EndEffectorParams endEffectorParams;

    endEffectorParams.xBias= x;
    endEffectorParams.yBias = y;
    endEffectorParams.zBias = z;

    SetEndEffectorParams(&endEffectorParams);
}

/*********************************************************************************************************
** Function name:       Dobot_SetEndEffectorLaser
** Descriptions:        Set Laser Statue
** Input parameters:    enable Duty
** Output parameters:   none
** Returned value:      none
*********************************************************************************************************/
void Dobot_SetEndEffectorLaser(uint8_t isEnable, float power)
{
    Dobot_SetIOMultiplexing(4, IOFunctionPWM);
    Dobot_SetIOPWM(4, 40000, power);
    Dobot_SetIOMultiplexing(2, IOFunctionDO);
    Dobot_SetIODO(2, isEnable);
}

/*********************************************************************************************************
** Function name:       Dobot_SetEndEffectorSuctionCup
** Descriptions:        Set SuctionCup
** Input parameters:    issuck
** Output parameters:   none
** Returned value:      none
*********************************************************************************************************/
void Dobot_SetEndEffectorSuctionCup(bool issuck)
{
    SetEndEffectorSuctionCup(issuck);
}

/*********************************************************************************************************
** Function name:       Dobot_SeEndEffectorGritpper
** Descriptions:        Set Gripper
** Input parameters:    isEnable,isGriped
** Output parameters:   none
** Returned value:      none
*********************************************************************************************************/
void Dobot_SetEndEffectorGripper(bool isEnable,bool isGriped)
{
    static EndEffectorGripper endEffectorGripper;

    endEffectorGripper.isEnable = isEnable;
    endEffectorGripper.isGriped = isGriped;

    SeEndEffectorGritpper(&endEffectorGripper);
}

/*********************************************************************************************************
** Function name:       Dobot_SetPTPCommonParams
** Descriptions:        Set PTPMommonParams
** Input parameters:    velocityRatio,accelerationRatio
** Output parameters:   none
** Returned value:      none
*********************************************************************************************************/
void Dobot_SetJOGCommonParams(float velocityRatio,float accelerationRatio)
{
    static JOGCommonParams jogCommonParams;

    jogCommonParams.velocityRatio = velocityRatio;
    jogCommonParams.accelerationRatio = accelerationRatio;

    SetJOGCommonParams(&jogCommonParams);
}

/*********************************************************************************************************
** Function name:       Dobot_SetPTPJointParams
** Descriptions:        Set PTP JointParams
** Input parameters:    Jointvelocity,Jointacceleration
** Output parameters:   none
** Returned value:      none
*********************************************************************************************************/
void Dobot_SetJOGJointParams(float velocityJ1,float accelerationJ1,float velocityJ2,float accelerationJ2,float velocityJ3,float accelerationJ3,float velocityJ4,float accelerationJ4)
{
    static JOGJointParams jogJointParams;

    jogJointParams.velocity[0] = velocityJ1;
    jogJointParams.acceleration[0] = accelerationJ1;
    jogJointParams.velocity[1] = velocityJ2;
    jogJointParams.acceleration[1] = accelerationJ2;
    jogJointParams.velocity[2] = velocityJ3;
    jogJointParams.acceleration[2] = accelerationJ3;
    jogJointParams.velocity[3] = velocityJ4;
    jogJointParams.acceleration[3] = accelerationJ4;

    SetJOGJointParams(&jogJointParams);
}

/*********************************************************************************************************
** Function name:       Dobot_SetJOGCoordinateParams
** Descriptions:        Set PTP CoordinateParams
** Input parameters:    Coordinatevelocity,Coordinateacceleration
** Output parameters:   none
** Returned value:      none
*********************************************************************************************************/
void Dobot_SetJOGCoordinateParams(float velocityX,float accelerationX,float velocityY,float accelerationY,float velocityZ,float accelerationZ,float velocityR,float accelerationR)
{
    static JOGCoordinateParams jogCoordinateParams;

    jogCoordinateParams.velocity[0] = velocityX;
    jogCoordinateParams.acceleration[0] = accelerationX;
    jogCoordinateParams.velocity[1] = velocityY;
    jogCoordinateParams.acceleration[1] = accelerationY;
    jogCoordinateParams.velocity[2] = velocityZ;
    jogCoordinateParams.acceleration[2] = accelerationZ;
    jogCoordinateParams.velocity[3] = velocityR;
    jogCoordinateParams.acceleration[3] = accelerationR;

    SetJOGCoordinateParams(&jogCoordinateParams);
}


/*********************************************************************************************************
** Function name:       Dobot_SetJOGCmd
** Descriptions:        Set JOGCmd
** Input parameters:    model
** Output parameters:   none
** Returned value:      none
*********************************************************************************************************/
void Dobot_SetJOGCmd(uint8_t model)
{
    static JOGCmd jogCmd;

    if(model > 10){
        jogCmd.isJoint = true;
        jogCmd.cmd = model / 10;
    }else{
        jogCmd.isJoint = false;
        jogCmd.cmd = model;
    }

    SetJOGCmd(&jogCmd);
}

/*********************************************************************************************************
** Function name:       Dobot_SetPTPCommonParams
** Descriptions:        Set PTPMommonParams
** Input parameters:    velocityRatio,accelerationRatio
** Output parameters:   none
** Returned value:      none
*********************************************************************************************************/
void Dobot_SetPTPCommonParams(float velocityRatio,float accelerationRatio)
{
    static PTPCommonParams ptpCommonParams;

    ptpCommonParams.velocityRatio = velocityRatio;
    ptpCommonParams.accelerationRatio = accelerationRatio;

    SetPTPCommonParams(&ptpCommonParams);
}

/*********************************************************************************************************
** Function name:       Dobot_SetPTPJointParams
** Descriptions:        Set PTP JointParams
** Input parameters:    Jointvelocity,Jointacceleration
** Output parameters:   none
** Returned value:      none
*********************************************************************************************************/
void Dobot_SetPTPJointParams(float velocityJ1,float accelerationJ1,float velocityJ2,float accelerationJ2,float velocityJ3,float accelerationJ3,float velocityJ4,float accelerationJ4)
{
    static PTPJointParams ptpJointParams;

    ptpJointParams.velocity[0] = velocityJ1;
    ptpJointParams.acceleration[0] = accelerationJ1;
    ptpJointParams.velocity[1] = velocityJ2;
    ptpJointParams.acceleration[10] = accelerationJ2;
    ptpJointParams.velocity[2] = velocityJ3;
    ptpJointParams.acceleration[2] = accelerationJ3;
    ptpJointParams.velocity[3] = velocityJ4;
    ptpJointParams.acceleration[3] = accelerationJ4;

    SetPTPJointParams(&ptpJointParams);
}

/*********************************************************************************************************
** Function name:       Dobot_SetPTPLParams
** Descriptions:        Set L Params
** Input parameters:    velocityRatio,accelerationRatio
** Output parameters:   none
** Returned value:      none
*********************************************************************************************************/
void Dobot_SetPTPLParams(float velocityRatio,float accelerationRatio)
{
    static PTPLParams ptpLParams;

    ptpLParams.velocity = velocityRatio;
    ptpLParams.acceleration = accelerationRatio;

    SetPTPLParams(&ptpLParams);
}

/*********************************************************************************************************
** Function name:       Dobot_SetPTPJumpParams
** Descriptions:        Set Jump Height
** Input parameters:    jumpHeight
** Output parameters:   none
** Returned value:      none
*********************************************************************************************************/
void Dobot_SetPTPJumpParams(float jumpHeight)
{
    static PTPJumpParams ptpJumpParams;

    ptpJumpParams.jumpHeight = jumpHeight;
    ptpJumpParams.zLimit = 100;

    SetPTPJumpParams(&ptpJumpParams);
}

/*********************************************************************************************************
** Function name:       Dobot_SetPTPCmdEX
** Descriptions:        Wait For PTPMove
** Input parameters:    Model,X,Y,Z,R
** Output parameters:   none
** Returned value:      none
*********************************************************************************************************/
void Dobot_SetPTPCmd(uint8_t Model,float x,float y,float z,float r)
{
    static PTPCmd ptpCmd;

    ptpCmd.ptpMode = Model;
    ptpCmd.x = x;
    ptpCmd.y = y;
    ptpCmd.z = z;
    ptpCmd.rHead = r;

    SetPTPCmd(&ptpCmd);
    WaitQueuedCmdFinished();
}

/*********************************************************************************************************
** Function name:       Dobot_SetPTPCmdWithLEX
** Descriptions:        Wait For PTPMove
** Input parameters:    Model,X,Y,Z,R,L
** Output parameters:   none
** Returned value:      none
*********************************************************************************************************/
void Dobot_SetPTPWithLCmd(uint8_t Model,float x,float y,float z,float r,float l)
{
    static PTPWithLCmd ptpWithLCmd;

    ptpWithLCmd.ptpMode = Model;
    ptpWithLCmd.x = x;
    ptpWithLCmd.y = y;
    ptpWithLCmd.z = z;
    ptpWithLCmd.rHead = r;
    ptpWithLCmd.l = l;

    SetPTPCmdWithL(&ptpWithLCmd);
    WaitQueuedCmdFinished();
}

/*********************************************************************************************************
** Function name:       Dobot_SetIOMultiplexingEX
** Descriptions:        Set IO Config
** Input parameters:    address,function
** Output parameters:   none
** Returned value:      none
*********************************************************************************************************/
void Dobot_SetIOMultiplexing(uint8_t address,uint8_t function)
{
    static IOConfig iOConfig;

    iOConfig.address = address;
    iOConfig.function = (IOFunction)function;

    SetIOMultiplexing(&iOConfig);
}

/*********************************************************************************************************
** Function name:       Dobot_SetIODOEX
** Descriptions:        SetIOdo
** Input parameters:    address,value
** Output parameters:   none
** Returned value:      none
*********************************************************************************************************/
void Dobot_SetIODO(uint8_t address,uint8_t value)
{
    static EIODO eIODO;

    eIODO.address = address;
    eIODO.value = value;

    SetIODO(&eIODO);
}

/*********************************************************************************************************
** Function name:       Dobot_SetIOPWMEX
** Descriptions:        SetIOPWM
** Input parameters:    address,freq,duty
** Output parameters:   none
** Returned value:      none
*********************************************************************************************************/
void Dobot_SetIOPWM(uint8_t address,float freq,float duty)
{
    static EIOPWM eIOPWM;

    eIOPWM.address = address;
    eIOPWM.freq = freq;
    eIOPWM.duty = duty;

    SetIOPWM(&eIOPWM);
}

/*********************************************************************************************************
** Function name:       Dobot_GetIODIEX
** Descriptions:        GetIODI
** Input parameters:    address
** Output parameters:   none
** Returned value:      value
*********************************************************************************************************/
uint8_t Dobot_GetIODI(uint8_t address)
{
    static EIODI eIODI;

    eIODI.address = address;

    GetIODI(&eIODI);

    return eIODI.value;
}

/*********************************************************************************************************
** Function name:       Dobot_GetIOADCEX
** Descriptions:        Get IOADC
** Input parameters:    address
** Output parameters:   none
** Returned value:      adc
*********************************************************************************************************/
uint16_t Dobot_GetIOADC(uint8_t address)
{
    static EIOADC eIOADC;

    eIOADC.address = address;

    GetIOADC(&eIOADC);

    return eIOADC.adc;
}

/*********************************************************************************************************
** Function name:       Dobot_SetEMotorEX
** Descriptions:        Set EMotor
** Input parameters:    address,enable,speed
** Output parameters:   none
** Returned value:      none
*********************************************************************************************************/
void Dobot_SetEMotor(uint8_t address,uint8_t enable,int32_t speed)
{
    static EMotor eMotor;

    eMotor.address = address;
    eMotor.enable = enable;
    eMotor.speed = speed;

    SetEMotor(&eMotor);
}

/*********************************************************************************************************
** Function name:       Dobot_SetEMotorSEX
** Descriptions:        Set EMotor
** Input parameters:    address,enable,speed,deltaPluse
** Output parameters:   none
** Returned value:      none
*********************************************************************************************************/
void Dobot_SetEMotorS(uint8_t address,uint8_t enable,int32_t speed,uint32_t deltaPulse)
{
    static EMotorS eMotorS;

    eMotorS.address = address;
    eMotorS.enable = enable;
    eMotorS.speed = speed;
    eMotorS.deltaPulse = deltaPulse;

    SetEMotorS(&eMotorS);
}

/*********************************************************************************************************
** Function name:       Dobot_SetColorSensorEX
** Descriptions:        Set ColorSensor
** Input parameters:    enable,port
** Output parameters:   none
** Returned value:      none
*********************************************************************************************************/
void Dobot_SetColorSensor(uint8_t enable,uint8_t port,uint8_t version)
{
    static ColorSensor colorSensor;

    colorSensor.enable = enable;
    colorSensor.port = port;
    colorSensor.version = version;
    SetColorSensor(&colorSensor);
}

/*********************************************************************************************************
** Function name:       Dobot_GetColorSensorEX
** Descriptions:        Set Color
** Input parameters:    color
** Output parameters:   none
** Returned value:      none
*********************************************************************************************************/
uint8_t Dobot_GetColorSensor(uint8_t color)
{
    static ColorSensor colorSensor;

    GetColorSensor(&colorSensor);

    switch(color){
        case 0:
            return colorSensor.r;
        break;
        case 1:
            return colorSensor.g;
        break;
        case 2:
            return colorSensor.b;
        break;
        default:
        break;
    }
    return 0;
}

/*********************************************************************************************************
** Function name:       Dobot_SetIRSwitchEX
** Descriptions:        Set IR Switch
** Input parameters:    enable,port
** Output parameters:   none
** Returned value:      none
*********************************************************************************************************/
void Dobot_SetIRSwitch(uint8_t enable,uint8_t port)
{
    static IRSwitch iRSwitch;

    iRSwitch.enable = enable;
    iRSwitch.port = port;

    SetIRSwitch(&iRSwitch);
}

/*********************************************************************************************************
** Function name:       GetIRSwitchEX
** Descriptions:        Get IR Switch
** Input parameters:    port
** Output parameters:   none
** Returned value:      value
*********************************************************************************************************/
uint8_t Dobot_GetIRSwitch(uint8_t port)
{
    static IRSwitch iRSwitch;

    iRSwitch.port = port;

    GetIRSwitch(&iRSwitch);

    return iRSwitch.value;
}

void Dobot_SetMotorPulse(float joint0 , float joint1 , float joint2 , float joint3 , float joint_re1 , float joint_re2)
{
    static PulseCmd pulseCmd;

    pulseCmd.params[0] = joint0;
    pulseCmd.params[1] = joint1;
    pulseCmd.params[2] = joint2;
    pulseCmd.params[3] = joint3;
    pulseCmd.params[4] = joint_re1;
    pulseCmd.params[5] = joint_re2;

    SetMotorPulse(&pulseCmd);
}
