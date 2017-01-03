/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: flightControl.h
 *
 * Code generated for Simulink model 'flightControl'.
 *
 * Model version                  : 1.187
 * Simulink Coder version         : 8.11 (R2016b) 25-Aug-2016
 * C/C++ source code generated on : Sun Jan 01 15:56:42 2017
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_flightControl_h_
#define RTW_HEADER_flightControl_h_
#include <math.h>
#include <float.h>
#include <string.h>
#include <stddef.h>
#ifndef flightControl_COMMON_INCLUDES_
# define flightControl_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_extmode.h"
#include "sysran_types.h"
#include "dt_info.h"
#include "ext_work.h"
#include "HostLib_Network.h"
#endif                                 /* flightControl_COMMON_INCLUDES_ */

#include "flightControl_types.h"

/* Shared type includes */
#include "multiword_types.h"
#include "rtGetNaN.h"
#include "rt_nonfinite.h"
#include "rtGetInf.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetFinalTime
# define rtmGetFinalTime(rtm)          ((rtm)->Timing.tFinal)
#endif

#ifndef rtmGetRTWExtModeInfo
# define rtmGetRTWExtModeInfo(rtm)     ((rtm)->extModeInfo)
#endif

#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetStopRequested
# define rtmGetStopRequested(rtm)      ((rtm)->Timing.stopRequestedFlag)
#endif

#ifndef rtmSetStopRequested
# define rtmSetStopRequested(rtm, val) ((rtm)->Timing.stopRequestedFlag = (val))
#endif

#ifndef rtmGetStopRequestedPtr
# define rtmGetStopRequestedPtr(rtm)   (&((rtm)->Timing.stopRequestedFlag))
#endif

#ifndef rtmGetT
# define rtmGetT(rtm)                  ((rtm)->Timing.taskTime0)
#endif

#ifndef rtmGetTFinal
# define rtmGetTFinal(rtm)             ((rtm)->Timing.tFinal)
#endif

/* Block signals (auto storage) */
typedef struct {
  real32_T UDPReceive_o1[31];          /* '<Root>/UDP Receive' */
  real32_T fv0[24];
  real32_T Product[12];                /* '<S3>/Product' */
  real32_T magInterp[12];
  real32_T MatrixConcatenate1[12];     /* '<S4>/Matrix Concatenate1' */
  real32_T MatrixConcatenate2[12];     /* '<S4>/Matrix Concatenate2' */
  real32_T cal[12];                    /* '<S5>/calibrate' */
  real32_T c[9];                       /* '<S3>/q2cFcn' */
  real32_T varargin_2[6];
  real32_T MatrixConcatenate[6];       /* '<S4>/Matrix Concatenate' */
  real32_T fv1[6];
  real32_T q[4];                       /* '<S3>/runMahonyUpdate' */
  real32_T Selector[3];                /* '<S3>/Selector' */
  real32_T Selector1[3];               /* '<S3>/Selector1' */
  real32_T Selector2[3];               /* '<S3>/Selector2' */
  real_T r;
  real_T scale;
  real_T absxk;
  real_T t;
  real_T ab_idx_1;
  real_T ab_idx_2;
  real_T ab_idx_3;
  real_T b_idx_3;
  boolean_T c_x[4];
  real32_T q1q2;
  real32_T q1q3;
  int32_T b_k;
  uint16_T UDPReceive_o2;              /* '<Root>/UDP Receive' */
} B_flightControl_T;

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  real_T UDPReceive_NetworkLib[137];   /* '<Root>/UDP Receive' */
  real_T counter;                      /* '<S3>/runMahonyUpdate' */
  struct {
    void *LoggedData;
  } Scope_PWORK;                       /* '<Root>/Scope' */

  struct {
    void *LoggedData[4];
  } Scope_PWORK_k;                     /* '<S3>/Scope' */

  real32_T qLocal[4];                  /* '<S3>/runMahonyUpdate' */
  real32_T bias[3];                    /* '<S5>/calibrate' */
  uint32_T count;                      /* '<S5>/calibrate' */
  int8_T runSensorFusion_SubsysRanBC;  /* '<Root>/runSensorFusion' */
  boolean_T runSensorFusion_MODE;      /* '<Root>/runSensorFusion' */
} DW_flightControl_T;

/* Parameters (auto storage) */
struct P_flightControl_T_ {
  real32_T q_Y0;                       /* Computed Parameter: q_Y0
                                        * Referenced by: '<S2>/q'
                                        */
  real32_T accel_w_Y0;                 /* Computed Parameter: accel_w_Y0
                                        * Referenced by: '<S2>/accel_w'
                                        */
  real32_T w_w_Y0;                     /* Computed Parameter: w_w_Y0
                                        * Referenced by: '<S2>/w_w'
                                        */
  real32_T bortz_w_Y0;                 /* Computed Parameter: bortz_w_Y0
                                        * Referenced by: '<S2>/bortz_w'
                                        */
  real32_T Constant_Value;             /* Computed Parameter: Constant_Value
                                        * Referenced by: '<S5>/Constant'
                                        */
  real32_T Constant2_Value;            /* Computed Parameter: Constant2_Value
                                        * Referenced by: '<S3>/Constant2'
                                        */
  uint16_T Constant_Value_p;           /* Computed Parameter: Constant_Value_p
                                        * Referenced by: '<S1>/Constant'
                                        */
};

/* Real-time Model Data Structure */
struct tag_RTM_flightControl_T {
  const char_T *errorStatus;
  RTWExtModeInfo *extModeInfo;

  /*
   * Sizes:
   * The following substructure contains sizes information
   * for many of the model attributes such as inputs, outputs,
   * dwork, sample times, etc.
   */
  struct {
    uint32_T checksums[4];
  } Sizes;

  /*
   * SpecialInfo:
   * The following substructure contains special information
   * related to other components that are dependent on RTW.
   */
  struct {
    const void *mappingInfo;
  } SpecialInfo;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    time_T taskTime0;
    uint32_T clockTick0;
    time_T stepSize0;
    time_T tFinal;
    boolean_T stopRequestedFlag;
  } Timing;
};

/* Block parameters (auto storage) */
extern P_flightControl_T flightControl_P;

/* Block signals (auto storage) */
extern B_flightControl_T flightControl_B;

/* Block states (auto storage) */
extern DW_flightControl_T flightControl_DW;

/* Model entry point functions */
extern void flightControl_initialize(void);
extern void flightControl_step(void);
extern void flightControl_terminate(void);

/* Real-time Model object */
extern RT_MODEL_flightControl_T *const flightControl_M;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S3>/Product1' : Unused code path elimination
 * Block '<S4>/Reshape' : Reshape block reduction
 * Block '<S4>/Reshape1' : Reshape block reduction
 */

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'flightControl'
 * '<S1>'   : 'flightControl/Compare To Zero'
 * '<S2>'   : 'flightControl/runSensorFusion'
 * '<S3>'   : 'flightControl/runSensorFusion/translateIMUToWorld'
 * '<S4>'   : 'flightControl/runSensorFusion/unpackData'
 * '<S5>'   : 'flightControl/runSensorFusion/translateIMUToWorld/calibrateSensorData'
 * '<S6>'   : 'flightControl/runSensorFusion/translateIMUToWorld/q2bortz'
 * '<S7>'   : 'flightControl/runSensorFusion/translateIMUToWorld/q2cFcn'
 * '<S8>'   : 'flightControl/runSensorFusion/translateIMUToWorld/qinvFcn'
 * '<S9>'   : 'flightControl/runSensorFusion/translateIMUToWorld/runMahonyUpdate'
 * '<S10>'  : 'flightControl/runSensorFusion/translateIMUToWorld/calibrateSensorData/calibrate'
 */
#endif                                 /* RTW_HEADER_flightControl_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
