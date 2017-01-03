/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: sensorTask_private.h
 *
 * Code generated for Simulink model 'sensorTask'.
 *
 * Model version                  : 1.133
 * Simulink Coder version         : 8.11 (R2016b) 25-Aug-2016
 * C/C++ source code generated on : Sat Dec 31 21:41:46 2016
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_sensorTask_private_h_
#define RTW_HEADER_sensorTask_private_h_
#include "rtwtypes.h"
#include "multiword_types.h"

/* Private macros used by the generated code to access rtModel */
#ifndef rtmSetTFinal
# define rtmSetTFinal(rtm, val)        ((rtm)->Timing.tFinal = (val))
#endif

#ifndef rtmGetTPtr
# define rtmGetTPtr(rtm)               (&(rtm)->Timing.taskTime0)
#endif

extern void readAccelGryoMag_Outputs_wrapper(real32_T *AccelX,
  real32_T *AccelY,
  real32_T *AccelZ,
  real32_T *GyroX,
  real32_T *GyroY,
  real32_T *GyroZ,
  real32_T *MagX,
  real32_T *MagY,
  real32_T *MagZ,
  real32_T *FIFOCount,
  const real_T *xD);
extern void readAccelGryoMag_Update_wrapper(real32_T *AccelX,
  real32_T *AccelY,
  real32_T *AccelZ,
  real32_T *GyroX,
  real32_T *GyroY,
  real32_T *GyroZ,
  real32_T *MagX,
  real32_T *MagY,
  real32_T *MagZ,
  real32_T *FIFOCount,
  real_T *xD);

#endif                                 /* RTW_HEADER_sensorTask_private_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
