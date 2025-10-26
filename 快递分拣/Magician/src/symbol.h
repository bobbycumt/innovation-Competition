#pragma once

#define ROBOT_AXIS                          (4)                         // »úÆ÷ÈË¹Ø½ÚÊý
#define SERIALNUM   Serial2
#define DEBUGPRINT  0

//-----------------------------------------------------------------------------
// Robot Profile mode
//-----------------------------------------------------------------------------
#define ROBOT_MODE_NONE                     (0)
#define ROBOT_MODE_SINGLE                   (1)
#define ROBOT_MODE_SINGLEXYZ                (2)
#define ROBOT_MODE_STOP                     (3)
#define ROBOT_MODE_HOME                     (4)
#define ROBOT_MODE_ARC                      (5)
#define ROBOT_MODE_PLAYBACK                 (6)
#define ROBOT_MODE_PLAYBACKWITHL            (7)
#define ROBOT_MODE_LEVELING                 (10)
#define ROBOT_MODE_CONTINUOUS_PATH          (16)

//#define ERROR_INV_CALCU                      (1)
//#define ERROR_INV_LIMIT                      (2)

#define LINE_MIN_DIST           0.0001f

#define LDEGREE                 0.1f
#define INP_MOTION_END          0x50
#define AXIS_SUM                5
//#define INTERP_RECI             (float)50
#define INTERP_RECI             (1/periodTime)
//µã¶¯Ã¶¾Ù×´Ì¬state
enum {
    IDLE,
    AP_DOWN,
    AN_DOWN,
    BP_DOWN,
    BN_DOWN,
    CP_DOWN,
    CN_DOWN,
    DP_DOWN,
    DN_DOWN
};

enum {
    LP_DOWN = 9,
    LN_DOWN,
};

//Á½µã¼äÔË¶¯Ä£Ê½type
enum {
    JUMP_XYZ,//ÃÅÐÍÔË¶¯
    MOVJ_XYZ,//¹Ø½ÚÔË¶¯
    MOVL_XYZ,//Ö±ÏßÔË¶¯
    JUMP_ANGLE,
    MOVJ_ANGLE,
    MOVL_ANGLE,
    MOVJ_INC,
    MOVL_INC,
    MOVJ_XYZ_INC,
    JUMP_MOVL_XYZ,
};

enum {
    PRESEEK_HOME,
    SEEK_HOME,
    BACK_HOME,
    SEEK_Z,
    FINISH_HOME,
    SOFT_HOME,
    MOVE_NEXTPOINT,
    MOVE_NEXTTESTPOINT,
    BACK_FIRSTPOINT,
    BEGIN_FIRSTPOINT,
    DETECTION_RESULT,
    TEST_RESULT
};

