/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: sensorFusion_data.c
 *
 * Code generated for Simulink model 'sensorFusion'.
 *
 * Model version                  : 1.37
 * Simulink Coder version         : 8.11 (R2016b) 25-Aug-2016
 * C/C++ source code generated on : Sun Jan 22 20:44:38 2017
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "sensorFusion.h"
#include "sensorFusion_private.h"

/* Block parameters (auto storage) */
P_sensorFusion_T sensorFusion_P = {
  /*  Variable: aMean
   * Referenced by: '<S3>/Constant4'
   */
  { -0.038579232696484993, 0.015125405229726172, 0.985264268406069 },

  /*  Variable: aVar
   * Referenced by: '<S3>/Constant2'
   */
  { 5.1253776232526919E-6, 4.2277820138033229E-6, 1.1915659975536502E-5 },

  /*  Variable: mMean
   * Referenced by: '<S3>/Constant5'
   */
  { 47.735714991803668, -38.636009827303312, 87.517185038334446 },

  /*  Variable: mVar
   * Referenced by: '<S3>/Constant3'
   */
  { 39.430756512955334, 40.815922310000467, 35.444708601605633 },
  0.005,                               /* Expression: 1/200
                                        * Referenced by: '<S3>/Constant6'
                                        */

  /*  Computed Parameter: Bias_Bias
   * Referenced by: '<S3>/Bias'
   */
  { 0.00705115916F, -0.00382855488F, -0.0111660259F },

  /*  Expression: single([0 0 0 1])
   * Referenced by: '<S3>/Unit Delay'
   */
  { 0.0F, 0.0F, 0.0F, 1.0F },

  /*  Expression: single(eye(4))
   * Referenced by: '<S3>/Unit Delay1'
   */
  { 1.0F, 0.0F, 0.0F, 0.0F, 0.0F, 1.0F, 0.0F, 0.0F, 0.0F, 0.0F, 1.0F, 0.0F, 0.0F,
    0.0F, 0.0F, 1.0F },
  0.0F,                                /* Computed Parameter: UnitDelay_InitialCondition_i
                                        * Referenced by: '<S4>/Unit Delay'
                                        */
  1,                                   /* Computed Parameter: Constant_Value
                                        * Referenced by: '<S3>/Constant'
                                        */
  2,                                   /* Computed Parameter: Constant1_Value
                                        * Referenced by: '<S3>/Constant1'
                                        */
  4,                                   /* Computed Parameter: ForIterator_IterationLimit
                                        * Referenced by: '<S3>/For Iterator'
                                        */
  2,                                   /* Computed Parameter: Switch_Threshold
                                        * Referenced by: '<S3>/Switch'
                                        */
  0U,                                  /* Computed Parameter: UnitDelay2_InitialCondition
                                        * Referenced by: '<S4>/Unit Delay2'
                                        */
  0U,                                  /* Computed Parameter: UnitDelay1_InitialCondition_d
                                        * Referenced by: '<S4>/Unit Delay1'
                                        */
  1U,                                  /* Computed Parameter: Constant_Value_m
                                        * Referenced by: '<S4>/Constant'
                                        */
  0U                                   /* Computed Parameter: Constant_Value_h
                                        * Referenced by: '<S1>/Constant'
                                        */
};

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
