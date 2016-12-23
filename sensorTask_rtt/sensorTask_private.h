/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: sensorTask_private.h
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

#ifndef RTW_HEADER_sensorTask_private_h_
#define RTW_HEADER_sensorTask_private_h_
#include "rtwtypes.h"

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
extern void readAccelGryoMag_Update_wrapper(const real32_T *AccelX,
  const real32_T *AccelY,
  const real32_T *AccelZ,
  const real32_T *GyroX,
  const real32_T *GyroY,
  const real32_T *GyroZ,
  const real32_T *MagX,
  const real32_T *MagY,
  const real32_T *MagZ,
  const real32_T *FIFOCount,
  real_T *xD);

#endif                                 /* RTW_HEADER_sensorTask_private_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
