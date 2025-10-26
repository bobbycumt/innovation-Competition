#pragma once
#include "symbol.h"
#include "stdbool.h"
#include <stdint.h>

//-----------------------------------------------------------------------------
// »ù±¾Êý¾ÝÀàÐÍ¶¨Òå
//-----------------------------------------------------------------------------
#ifndef NULL
#define NULL                           ((void*)0)
#endif

#ifndef TRUE
#define TRUE                           (1)
#endif

#ifndef FALSE
#define FALSE                          (0)
#endif

#define POSITIVE                       (1)
#define NEGATIVE                       (-1)

// #ifndef PI
// #define PI                              (3.14159265358979f)
// #endif

#define ZERO                            (0.0001)

typedef union {
    uint8_t  data8[2];
    int16_t  data16;
} TData16;

typedef union {
    uint16_t data16[2];
    int32_t  data32;
} TData32;

typedef union {
    uint16_t data16[4];
    uint32_t data32[2];
    int64_t  data64;
} TData64;

//-----------------------------------------------------------------------------
// TDi
//-----------------------------------------------------------------------------
typedef struct {
    float state;    //×´Ì¬
    float Axise;    //ÖáÔË¶¯Ö¸Áî
    float X; //Ïà¶ÔÎ»ÖÃ
    float Y; //Ïà¶ÔÎ»ÖÃ
    float Z; //Ïà¶ÔÎ»ÖÃ
    float RHead;
    float isGrab;
    float StartVel;//ÆðÊ¼ËÙ¶È
    float EndVel;//½áÊøËÙ¶È
    float MaxVel;    //±¾¶Î×î´óËÙ¶È
} PackageStruct;

typedef struct {
    float X;
    float Y;
    float Z;
    float RHead;//¶æ»ú½Ç¶È
    float isGrab;//ÊÖ×¥ÎüÅÌ×´Ì¬
    float baseAngle;//µ××ù½Ç¶È
    float longArmAngle;//´ó±Û½Ç¶È
    float shortArmAngle;//Ð¡±Û½Ç¶È
    float pawAngle;//ÊÖ×¥½Ç¶È
    float gripperAngle;
} CurrentCoord;

typedef struct {
    float s;//Î»ÒÆ
    float v;//ËÙ¶È
    int dir;
    float t1;//¼ÓËÙÊ±¼ä
    float t2;//ÔÈËÙÊ±¼ä
    float T;//×ÜÊ±¼ä
    float a;//¼ÓËÙ¶È
    bool finishFlag;//ÔË¶¯Íê³É±êÖ¾Î»

} Axis; //¸÷ÖáÖ±Ïß¼Ó¼õËÙ¹æ»®½á¹û

typedef struct {
    int lastSendPulseSum[ROBOT_AXIS];
    float sendPulseSum[ROBOT_AXIS];
    float sendSpeedSum[ROBOT_AXIS];//ËÙ¶È
    int   pulseFPGA[ROBOT_AXIS];
    float angleFPGA[ROBOT_AXIS] ;
    int stepSum[ROBOT_AXIS];
} Pulse;

typedef struct {
    int lastSendPulseSum;
    float sendPulseSum;
    float sendSpeedSum;//ËÙ¶È
    int   pulseFPGA;
    float angleFPGA ;
    int stepSum;
} PulseL;

typedef struct {
    float stepAngle;//²½¾à½Ç
    float subDiv[ROBOT_AXIS];//Ï¸·ÖÊý
    float gearRatio[ROBOT_AXIS];//¼õËÙ±È
    int stepDir[ROBOT_AXIS];
    float stepPerDegree[ROBOT_AXIS];
} Stepper;

typedef struct {
    float stepAngle;//²½¾à½Ç
    float subDiv;//Ï¸·ÖÊý
    float gearRatio;//¼õËÙ±È
    int stepDir;
    float stepPerDegree;
} StepperL;

typedef struct {
    float target[ROBOT_AXIS];//Òªµ½´ïµÄ¾ø¶ÔÎ»ÖÃ
    float stepLast[ROBOT_AXIS];//ÒÑµ½´ïµÄ¸÷ÖáÎ»ÖÃ
    float speed[ROBOT_AXIS];//¸÷ÖáÃ¿ÖÜÆÚ¹æ»®µÄËÙ¶È
} JointMove;

typedef struct {
    float target;//Òªµ½´ïµÄ¾ø¶ÔÎ»ÖÃ
    float stepLast;//ÒÑµ½´ïµÄ¸÷ÖáÎ»ÖÃ
    float speed;//¸÷ÖáÃ¿ÖÜÆÚ¹æ»®µÄËÙ¶È
} JointMoveL;

typedef struct {
    float dir[ROBOT_AXIS];
    float stepLastL;
    float speedLine;
    float speedRot;
    float dirR;
    float stepLastR;
} LineMove;

typedef struct {
    float singleVel;//µ¥ÖáÔË¶¯ËÙ¶È
    float singleVelMax;//µ¥ÖáÔË¶¯×î´óËÙ¶È
    float singleAcc;//µ¥ÖáÔË¶¯¼ÓËÙ¶È
    int lastState;//µã¶¯×´Ì¬
} SingleMove;

typedef struct {
    float theta[ROBOT_AXIS];
} TRobotTheta;

typedef struct {
    float x;                                                // Î»ÖÃX,mm
    float y;                                                // Î»ÖÃY,mm
    float z;                                                // Î»ÖÃZ,mm
    float r;                                                // ×ËÌ¬A,deg
} TCPosition;
typedef struct VECTOR3D_STR
{
    float item01;
    float item02;
    float item03;
}VECTOR3D;

//6*1 vector
typedef struct VECTOR6D_STR
{
    float item01;
    float item02;
    float item03;
    float item04;
    float item05;
    float item06;
}VECTOR6D;


//3*3 matrix
typedef struct MATRIX3D_STR
{
    float item11;
    float item12;
    float item13;
    float item21;
    float item22;
    float item23;
    float item31;
    float item32;
    float item33;
}MATRIX3D;

//4*4 matrix
typedef struct MATRIX4D_STR
{
    float item11;
    float item12;
    float item13;
    float item14;
    float item21;
    float item22;
    float item23;
    float item24;
    float item31;
    float item32;
    float item33;
    float item34;
    float item41;
    float item42;
    float item43;
    float item44;
}MATRIX4D;

typedef struct
{
        MATRIX3D planeRotM;
        VECTOR3D arcCenter;
        VECTOR3D rotAxis;
        float arcRadius;
        float arcAng;
        float rotAng;
}CirlPlanPara;

typedef struct
{
   CirlPlanPara circlePlanPara;

   TCPosition midPos;
   TCPosition endPos;
   TCPosition beginPos;

}CircleMove;

typedef struct DOBOTSTRUCT_STR {
    float joint1ArmLen;
    float joint2ArmLen;
    float baseH;
    float baseV;
    float linkBlockH;
    float linkBlockV;
    float linkBlockY;
} DOBOTSTRUCT;

typedef struct {
    float jointPos[ROBOT_AXIS];
    float jointNeg[ROBOT_AXIS];
    float parallelJoint12Pos;
    float parallelJoint12Neg;
    float crdPos[ROBOT_AXIS];
    float crdNeg[ROBOT_AXIS];
    float disMOVJ;

} SoftLimit;

typedef struct {
    float jointPos;
    float jointNeg;
} SoftLimitL;

typedef struct {
    int homeState;
    float seekHomeSpd;
    float backHomeSpd;
    float findZSpd;
    float homePos;
    int homeDir;
} Home;

typedef struct {
    int motion_stat;
    int motion_stat_E;

    long term_cmd;
    long term_run;
    long term_rem;

    int term_add;
    int term_unfm;
    int term_dec;

    float AT;
    float time_delta;
    float term_length;
    float term_vel;
    float vel;
    float vDelta;
} typ_interp_time;

typedef struct {
    PackageStruct gCode;
    float dist;
    float accelat;
    float axis_vel[3];
    float dist_out[3];

    typ_interp_time interp_time;
    float axis_seg[3];

    float vb;
    float vm;
    float ve;
    float vc;
    float vd;
    float va;
} typ_interp_segment;

typedef struct {
    float interp_length;
    float interp_vel;
    float accelerate_until;                    // The index of the step event on which to stop acceleration
    float decelerate_after;                    // The index of the step event on which to start decelerating
    float nominal_speed;                               // The nominal speed for this block in mm/sec
    float entry_speed;                                 // Entry speed at previous-current junction in mm/sec
    float exit_speed;                             // Maximum allowable junction entry speed in mm/sec
    float millimeters;                                 // The total travel of this block in mm
    float acceleration;                                // acceleration mm/sec^2
    float axis_seg[3];
    float axis_gcode[3];
    float dist_out[3];
} typ_marlin_interp_segment;
/*********************************************************************************************************
** Êý¾Ý½á¹¹µÈ¶¨Òå
*********************************************************************************************************/

/*********************************************************************************************************
** ¹«¹²²¿·Ö
*********************************************************************************************************/
#pragma pack(push)
#pragma pack(1)

/*
 * Pose
 */
typedef struct tagPose {
    float x;
    float y;
    float z;
    float rHead;
    float jointAngle[ROBOT_AXIS];
} Pose __attribute__ ((aligned(4)));



/*
 * Kinematics
 */
typedef struct tagKinematics {
    float velocity;
    float acceleration;
} Kinematics __attribute__ ((aligned(4)));

typedef struct tagHOMEParams {
    uint32_t temp;
} HOMEParams;

typedef struct tagHOMECmd {
    uint32_t temp;
} HOMECmd;

/*
 * HHT
 */
typedef enum tagHHTTrigMode {
    TriggeredOnKeyReleased,
    TriggeredOnPeriodicInterval
} HHTTrigMode;

/*
 * End effector
 */
typedef struct tagEndEffectorParams {
    float xBias;
    float yBias;
    float zBias;
} EndEffectorParams;

/*********************************************************************************************************
** Arm orientation
*********************************************************************************************************/
typedef enum tagArmOrientation {
    LeftyArmOrientation,
    RightyArmOrientation,
} ArmOrientation;

/*********************************************************************************************************
** µã¶¯Ê¾½Ì²¿·Ö
*********************************************************************************************************/
/*
 * µ¥¹Ø½Úµã¶¯Ê¾½Ì²ÎÊý
 */
typedef struct tagJOGJointParams {
    float velocity[4];
    float acceleration[4];
} JOGJointParams __attribute__ ((aligned(4)));

/*
 * µ¥×ø±êÖáµã¶¯Ê¾½Ì²ÎÊý
 */
typedef struct tagJOGCoordinateParams {
    float velocity[4];
    float acceleration[4];
} JOGCoordinateParams __attribute__ ((aligned(4)));

typedef struct tagJOGLParams {
    float velocity;
    float acceleration;
}JOGLParams __attribute__ ((aligned(4)));

/*
 * µã¶¯Ê¾½Ì¹«¹²²ÎÊý
 */
typedef struct tagJOGCommonParams {
    float velocityRatio;
    float accelerationRatio;
} JOGCommonParams __attribute__ ((aligned(4)));

/*
 * µã¶¯Ê¾½ÌËùÓÐ²ÎÊý
 */
typedef struct tagJOGParams {
    JOGJointParams jointParams;
    JOGCoordinateParams coordinateParams;
    JOGLParams lParams;
    JOGCommonParams commonParams;
} JOGParams __attribute__ ((aligned(4)));

/*
 * Jog Cmd
 */
typedef struct tagJOGCmd {
    uint8_t isJoint;
    uint8_t cmd;
} JOGCmd __attribute__ ((aligned(4)));

/*********************************************************************************************************
** ÔÙÏÖÔË¶¯²¿·Ö
*********************************************************************************************************/
/*
 * ÔÙÏÖÔË¶¯²ÎÊý
 */
typedef struct tagPTPJointParams {
    float velocity[4];
    float acceleration[4];
} PTPJointParams __attribute__ ((aligned(4)));

typedef struct tagPTPCoordinateParams {
    float xyzVelocity;
    float rVelocity;
    float xyzAcceleration;
    float rAcceleration;
} PTPCoordinateParams __attribute__ ((aligned(4)));

typedef struct tagPTPLParams {
    float velocity;
    float acceleration;
}PTPLParams __attribute__ ((aligned(4)));

typedef struct tagPTPJumpParams {
    float jumpHeight;
    float zLimit;
} PTPJumpParams __attribute__ ((aligned(4)));

typedef struct tagPTPJump2Params {
    float startJumpHeight;
    float endJumpHeight;
    float zLimit;
} PTPJump2Params __attribute__ ((aligned(4)));

typedef struct tagPTPCommonParams {
    float velocityRatio;
    float accelerationRatio;
} PTPCommonParams __attribute__ ((aligned(4)));

typedef struct tagPTPParams {
    PTPJointParams jointParams;
    PTPCoordinateParams coordinateParams;
    PTPLParams lParams;
    PTPJumpParams jumpParams;
    PTPJump2Params jump2Params;
    PTPCommonParams commonParams;
} PTPParams __attribute__ ((aligned(4)));

typedef struct tagPTPCmd {
    uint8_t ptpMode;
    float x;
    float y;
    float z;
    float rHead;
} PTPCmd __attribute__ ((aligned(4)));

typedef struct tagPTPWithLCmd {
    uint8_t ptpMode;
    float x;
    float y;
    float z;
    float rHead;
    float l;
}PTPWithLCmd __attribute__ ((aligned(4)));

typedef struct tagParallelOutputCmd {
    uint8_t ratio;
    uint16_t address;
    uint8_t level;
}ParallelOutputCmd __attribute__ ((aligned(4)));
typedef struct tagPulseCmd{
   float params[6];
}PulseCmd __attribute__ ((aligned(4)));

/*********************************************************************************************************
** Á¬Ðø¹ì¼££ºContinuous path
*********************************************************************************************************/
/*
 * CP²ÎÊý
 */
typedef struct tagCPParams {
    float planAcc;
    float juncitionVel;
    union {
        float acc;
        float period;
    };
    uint8_t realTimeTrack;
} CPParams __attribute__ ((aligned(4)));

typedef enum tagCPMode {
    CPRelativeMode,
    CPAbsoluteMode
} CPMode __attribute__ ((aligned(4)));

typedef struct tagLookAhead {
    float AT;
    float vd;
    float ve;
    float va;
    float vc;
    float dist;
    float juctionAngle;

    float maxVel;
    float startVel;
    float endVel;
} LookAhead __attribute__ ((aligned(4)));

typedef struct tagMarlin {
    // Fields used by the motion planner to manage acceleration
    // float speed_x, speed_y, speed_z, speed_e;          // Nominal mm/sec for each axis
    float nominal_speed;                               // The nominal speed for this block in mm/sec
    float entry_speed;                                 // Entry speed at previous-current junction in mm/sec
    float max_entry_speed;                             // Maximum allowable junction entry speed in mm/sec
    float millimeters;                                 // The total travel of this block in mm
    float acceleration;                                // acceleration mm/sec^2
    unsigned char recalculate_flag;                    // Planner flag to recalculate trapezoids on entry junction
    unsigned char nominal_length_flag;                 // Planner flag for nominal speed always reached

} Marlin __attribute__ ((aligned(4)));

typedef struct tagCPCmd {
    uint8_t cpMode;
    float x;
    float y;
    float z;
    union {
        float velocity;
        float laserPower;
    };
    uint8_t isLaserEngraving;
    uint8_t laserStartControl;
    float abs_x;
    float abs_y;
    float abs_z;
    LookAhead lookAhead;
    Marlin marlin;
} CPCmd __attribute__ ((aligned(4)));

/*********************************************************************************************************
** Ô²»¡£ºARC
*********************************************************************************************************/
typedef struct tagARCParams {
    float xyzVelocity;
    float rVelocity;
    float xyzAcceleration;
    float rAcceleration;
} ARCParams __attribute__ ((aligned(4)));

typedef struct tagARCCmd {
    struct {
        float x;
        float y;
        float z;
        float rHead;
    } cirPoint;
    struct {
        float x;
        float y;
        float z;
        float rHead;
    } toPoint;
} ARCCmd __attribute__ ((aligned(4)));

typedef struct tagCircleCmd {
    struct {
        float x;
        float y;
        float z;
        float rHead;
    } cirPoint;
    struct {
        float x;
        float y;
        float z;
        float rHead;
    } toPoint;
    uint32_t count;
} CircleCmd __attribute__ ((aligned(4)));

/*********************************************************************************************************
** WAIT cmd
*********************************************************************************************************/
typedef struct tagWAITCmd {
    uint32_t timeout;
} WAITCmd __attribute__ ((aligned(4)));

/*********************************************************************************************************
** TRIG cmd
*********************************************************************************************************/
typedef enum tagTRIGMode {
    TRIGInputIOMode,
    TRIGADCMode
} TRIGMode __attribute__ ((aligned(4)));

typedef enum tagTRIGInputIOCondition {
    TRIGInputIOEqual,
    TRIGInputIONotEqual
} TRIGInputIOCondition __attribute__ ((aligned(4)));

typedef enum tagTRIGADCCondition {
    TRIGADCLT,     //Lower than
    TRIGADCLE,     //Lower than or Equal
    TRIGADCGE,     //Greater than or Equal
    TRIGADCGT      //Greater than
} TRIGADCCondition __attribute__ ((aligned(4)));

typedef struct tagTRIGCmd {
    uint8_t address;
    uint8_t mode;
    uint8_t condition;
    uint16_t threshold;
} TRIGCmd __attribute__ ((aligned(4)));

/*********************************************************************************************************
** ÀàÐÍµÈ¶¨Òå
*********************************************************************************************************/
typedef enum tagQueuedCmdType {
    QueuedCmdMotionType,
    QueuedCmdWaitType,
    QueuedCmdIOType,
    QueuedCmdTrigType,
    QueuedCmdTypeNum
} QueuedCmdType;

typedef enum tagQueuedCmdExecMode {
    QueuedCmdExecOnlineMode,
    QueuedCmdExecOfflineMode
} QueuedCmdExecMode;

typedef enum tagRunOfflineQueuedCmdState {
    RunOfflineQueuedCmdIdleState,
    RunOfflineQueuedCmdRunState
} RunOfflineQueuedCmdState;

typedef struct tagOfflineLoopLine {
    bool isDownloading;
    uint32_t offlineLoop;
    uint32_t offlineLine;
    bool     offlineLoopLineWriteFlag;
    bool     offlineLoopLineReadFlag;
    uint32_t offlineLoopIndex;
    uint32_t offlineLineIndex;
} OfflineLoopLine __attribute__ ((aligned(4)));

/*********************************************************************************************************
** System Information Storage
*********************************************************************************************************/
typedef struct tagEndEffectorGripper {
    bool isEnable;
    bool isGriped;
} EndEffectorGripper __attribute__ ((aligned(4)));
/*********************************************************************************************************
** System Information Storage
*********************************************************************************************************/
typedef struct tagIOConfig {
    uint8_t address;
    uint8_t function;
} IOConfig __attribute__ ((aligned(4)));
/*********************************************************************************************************
** System Information Storage
*********************************************************************************************************/
typedef struct tagEIODO {
    uint8_t address;
    uint8_t value;
} EIODO __attribute__ ((aligned(4)));
/*********************************************************************************************************
** System Information Storage
*********************************************************************************************************/
typedef struct tagEIOPWM {
    uint8_t address;
    float freq;
    float duty;
} EIOPWM __attribute__ ((aligned(4)));
/*********************************************************************************************************
** System Information Storage
*********************************************************************************************************/
typedef struct tagEIODI {
    uint8_t address;
    uint8_t value;
} EIODI __attribute__ ((aligned(4)));
/*********************************************************************************************************
** System Information Storage
*********************************************************************************************************/
typedef struct tagEIOADC {
    uint8_t address;
    uint16_t adc;
} EIOADC ;
/*********************************************************************************************************
** System Information Storage
*********************************************************************************************************/
typedef struct tagEMotor{
    uint8_t address;
    uint8_t enable;
    int32_t speed;
} EMotor __attribute__ ((aligned(4)));
/*********************************************************************************************************
** System Information Storage
*********************************************************************************************************/
typedef struct tagEMotorS{
    uint8_t address;
    uint8_t enable;
    int32_t speed;
    uint32_t deltaPulse;
} EMotorS __attribute__ ((aligned(4)));
/*********************************************************************************************************
** System Information Storage
*********************************************************************************************************/
typedef struct tagIRSwitch{
    uint8_t enable;
    uint8_t port;
    uint8_t value;
} IRSwitch __attribute__ ((aligned(4)));
/*********************************************************************************************************
** System Information Storage
*********************************************************************************************************/
typedef struct tagColorSensor{
    uint8_t enable;
    uint8_t port;
    uint8_t version;
    uint8_t r;
    uint8_t g;
    uint8_t b;
} ColorSensor __attribute__ ((aligned(4)));

#pragma pack(pop)

/*********************************************************************************************************
** System parameter
*********************************************************************************************************/
typedef struct tagSysParams {
    // Device information
    char deviceSN[24];
    char deviceName[65];
    char deviceVersion[3];
    uint32_t deviceID[3];
    uint8_t isWithL;

    // Pose
    Pose pose;
    float poseL;
    Kinematics kinematics;

    // Alarm

    // HOME
    struct {
        HOMEParams params;
        HOMECmd cmd;
    } home;

#ifdef STM32F10X_HD
    // HHT
    HHTTrigMode hhtTrigMode;
    bool hhtTrigOutputEnabled;
    bool hhtTrigOutput;
#endif

    // ARM
    ArmOrientation armOrientation;

    // End effector
    EndEffectorParams endEffectorParams;

    // JOG
    struct {
        JOGParams params;
        JOGCmd cmd;
    } jog;

    // PTP
    struct {
        PTPParams params;
        PTPCmd cmd;
        PTPWithLCmd withLCmd;
    } ptp;

    int parallelOutputCmdCount;
    ParallelOutputCmd parallelOutputCmd[32];
    bool poFinished[32];

    // CP
    struct {
        CPParams params;
        CPCmd cmd;
    } cp;

    // ARC
    struct {
        ARCParams params;
        ARCCmd cmd;
    } arc;
    CircleCmd circleCmd;

    // WAIT
    struct {
        WAITCmd cmd;
        uint32_t initialTick;
    } wait;

    // TRIG
    struct {
        TRIGCmd cmd;
    } trig;

    // EIO
    EMotor eMotor;
    uint8_t colorSensorEnabled;
    uint8_t colorSensorPort;
    IRSwitch  iRSwitch;
    ColorSensor colorSensor;
    
    //LostStepValue
    float lostStepValue;
    // CAL
    float rearArmAngleError;
    float rearArmAngleCoef;
    float frontArmAngleError;
    float frontArmAngleCoef;
    float AngleError[2];
    float AngleCoef[2];
    float RotErr[1];
    float HomeErr;
    //pulse Mode

    // Queued command control
    bool runQueuedCmd;
    // Total loop and line per loop used in offline downloading
    struct {
        bool isDownloading;
        uint32_t totalLoop;
        uint32_t linePerLoop;
        bool     writeFlag;
        bool     readFlag;
        uint32_t loopIndex;
        uint32_t lineIndex;
    } queuedCmdOfflineLoopLine;

    // #Internal use
    QueuedCmdType queuedCmdType;
    bool runOfflineQueuedCmd;
    RunOfflineQueuedCmdState runOfflineQueuedCmdState;

    // Soft
    bool isSoftOffTriggered;
    uint64_t softOffLastIndex;
} SysParams;

/*********************************************************************************************************
** System parameter Storage
*********************************************************************************************************/
typedef struct tagParamStorage {
    uint32_t storeLength;
    float    jogVelocityRatio;
    float    jogAccelerationRatio;
    float    ptpVelocityRatio;
    float    ptpAccelerationRatio;
    float    EndTypeXBias;
} ParamStorage;

/*********************************************************************************************************
** System Information Storage
*********************************************************************************************************/
typedef struct tagInfomationStorage {
    uint32_t storeLength;
    char deviceSN[24] ;
    char deviceName[65];
    uint8_t deviceVersion[3];
    uint32_t devicePowerTime;
} InformationStorage;


