/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: sensorTask.h
 *
 * Code generated for Simulink model 'sensorTask'.
 *
 * Model version                  : 1.120
 * Simulink Coder version         : 8.9 (R2015b) 13-Aug-2015
 * TLC version                    : 8.9 (Jul 31 2015)
 * C/C++ source code generated on : Sat Jul 30 15:32:51 2016
 *
 * Target selection: realtime.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_sensorTask_h_
#define RTW_HEADER_sensorTask_h_
#include <string.h>
#include <stddef.h>
#ifndef sensorTask_COMMON_INCLUDES_
# define sensorTask_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "HostLib_Network.h"
#endif                                 /* sensorTask_COMMON_INCLUDES_ */

#include "sensorTask_types.h"

/* Macros for accessing real-time model data structure */
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

/* Block signals (auto storage) */
typedef struct {
  real32_T TmpSignalConversionAtUDPSendInp[31];
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
} DW_sensorTask_T;

/* Real-time Model Data Structure */
struct tag_RTM_sensorTask_T {
  const char_T * volatile errorStatus;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    boolean_T stopRequestedFlag;
  } Timing;
};

/* Block signals (auto storage) */
extern B_sensorTask_T sensorTask_B;

/* Block states (auto storage) */
extern DW_sensorTask_T sensorTask_DW;

/* Model entry point functions */
extern void sensorTask_initialize(void);
extern void sensorTask_output(void);
extern void sensorTask_update(void);
extern void sensorTask_terminate(void);

/* Real-time Model object */
extern RT_MODEL_sensorTask_T *const sensorTask_M;

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
 */
#endif                                 /* RTW_HEADER_sensorTask_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
