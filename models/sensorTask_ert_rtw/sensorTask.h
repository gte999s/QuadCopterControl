/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: sensorTask.h
 *
 * Code generated for Simulink model 'sensorTask'.
 *
 * Model version                  : 1.138
 * Simulink Coder version         : 8.11 (R2016b) 25-Aug-2016
 * C/C++ source code generated on : Sun Jan 22 20:23:09 2017
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_sensorTask_h_
#define RTW_HEADER_sensorTask_h_
#include <string.h>
#include <float.h>
#include <stddef.h>
#ifndef sensorTask_COMMON_INCLUDES_
# define sensorTask_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_extmode.h"
#include "sysran_types.h"
#include "dt_info.h"
#include "ext_work.h"
#include "HostLib_Network.h"
#endif                                 /* sensorTask_COMMON_INCLUDES_ */

#include "sensorTask_types.h"

/* Shared type includes */
#include "multiword_types.h"

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
  real32_T TmpSignalConversionAtUDPSendInp[32];
  real32_T readAccelGyroMagSfun_o1[4]; /* '<S6>/readAccelGyroMagSfun' */
  real32_T readAccelGyroMagSfun_o2[4]; /* '<S6>/readAccelGyroMagSfun' */
  real32_T readAccelGyroMagSfun_o3[4]; /* '<S6>/readAccelGyroMagSfun' */
  real32_T readAccelGyroMagSfun_o4[4]; /* '<S6>/readAccelGyroMagSfun' */
  real32_T readAccelGyroMagSfun_o5[4]; /* '<S6>/readAccelGyroMagSfun' */
  real32_T readAccelGyroMagSfun_o6[4]; /* '<S6>/readAccelGyroMagSfun' */
  real32_T readAccelGyroMagSfun_o7[2]; /* '<S6>/readAccelGyroMagSfun' */
  real32_T readAccelGyroMagSfun_o8[2]; /* '<S6>/readAccelGyroMagSfun' */
  real32_T readAccelGyroMagSfun_o9[2]; /* '<S6>/readAccelGyroMagSfun' */
  real32_T readAccelGyroMagSfun_o10;   /* '<S6>/readAccelGyroMagSfun' */
} B_sensorTask_T;

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  real_T readAccelGyroMagSfun_DSTATE;  /* '<S6>/readAccelGyroMagSfun' */
  real_T UDPSend_NetworkLib[137];      /* '<Root>/UDP Send' */
  uint32_T Output_DSTATE;              /* '<S7>/Output' */
} DW_sensorTask_T;

/* Parameters (auto storage) */
struct P_sensorTask_T_ {
  uint32_T WrapToZero_Threshold;       /* Mask Parameter: WrapToZero_Threshold
                                        * Referenced by: '<S10>/FixPt Switch'
                                        */
  uint32_T Constant_Value;             /* Computed Parameter: Constant_Value
                                        * Referenced by: '<S10>/Constant'
                                        */
  uint32_T FixPtConstant_Value;        /* Computed Parameter: FixPtConstant_Value
                                        * Referenced by: '<S9>/FixPt Constant'
                                        */
  uint32_T Output_InitialCondition;    /* Computed Parameter: Output_InitialCondition
                                        * Referenced by: '<S7>/Output'
                                        */
};

/* Real-time Model Data Structure */
struct tag_RTM_sensorTask_T {
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
extern P_sensorTask_T sensorTask_P;

/* Block signals (auto storage) */
extern B_sensorTask_T sensorTask_B;

/* Block states (auto storage) */
extern DW_sensorTask_T sensorTask_DW;

/* Model entry point functions */
extern void sensorTask_initialize(void);
extern void sensorTask_step(void);
extern void sensorTask_terminate(void);

/* Real-time Model object */
extern RT_MODEL_sensorTask_T *const sensorTask_M;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S7>/FixPt Data Type Propagation' : Unused code path elimination
 * Block '<S9>/FixPt Data Type Duplicate' : Unused code path elimination
 * Block '<S10>/FixPt Data Type Duplicate1' : Unused code path elimination
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
 * '<Root>' : 'sensorTask'
 * '<S1>'   : 'sensorTask/For Iterator Subsystem'
 * '<S2>'   : 'sensorTask/For Iterator Subsystem1'
 * '<S3>'   : 'sensorTask/createMatrix'
 * '<S4>'   : 'sensorTask/createMatrix1'
 * '<S5>'   : 'sensorTask/createMatrix2'
 * '<S6>'   : 'sensorTask/readSensors'
 * '<S7>'   : 'sensorTask/readSensors/Counter Free-Running'
 * '<S8>'   : 'sensorTask/readSensors/MATLAB Function'
 * '<S9>'   : 'sensorTask/readSensors/Counter Free-Running/Increment Real World'
 * '<S10>'  : 'sensorTask/readSensors/Counter Free-Running/Wrap To Zero'
 */
#endif                                 /* RTW_HEADER_sensorTask_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
