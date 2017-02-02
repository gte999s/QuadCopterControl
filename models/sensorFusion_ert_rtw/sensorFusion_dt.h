/*
 * sensorFusion_dt.h
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "sensorFusion".
 *
 * Model version              : 1.37
 * Simulink Coder version : 8.11 (R2016b) 25-Aug-2016
 * C source code generated on : Sun Jan 22 20:44:38 2017
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "ext_types.h"

/* data type size table */
static uint_T rtDataTypeSizes[] = {
  sizeof(real_T),
  sizeof(real32_T),
  sizeof(int8_T),
  sizeof(uint8_T),
  sizeof(int16_T),
  sizeof(uint16_T),
  sizeof(int32_T),
  sizeof(uint32_T),
  sizeof(boolean_T),
  sizeof(fcn_call_T),
  sizeof(int_T),
  sizeof(pointer_T),
  sizeof(action_T),
  2*sizeof(uint32_T),
  sizeof(uint64m_T),
  sizeof(int64m_T),
  sizeof(uint64m_T),
  sizeof(int96m_T),
  sizeof(uint96m_T),
  sizeof(int128m_T),
  sizeof(uint128m_T),
  sizeof(int160m_T),
  sizeof(uint160m_T),
  sizeof(int192m_T),
  sizeof(uint192m_T),
  sizeof(int224m_T),
  sizeof(uint224m_T),
  sizeof(int256m_T),
  sizeof(uint256m_T)
};

/* data type name table */
static const char_T * rtDataTypeNames[] = {
  "real_T",
  "real32_T",
  "int8_T",
  "uint8_T",
  "int16_T",
  "uint16_T",
  "int32_T",
  "uint32_T",
  "boolean_T",
  "fcn_call_T",
  "int_T",
  "pointer_T",
  "action_T",
  "timer_uint32_pair_T",
  "uint64m_T",
  "int64m_T",
  "uint64m_T",
  "int96m_T",
  "uint96m_T",
  "int128m_T",
  "uint128m_T",
  "int160m_T",
  "uint160m_T",
  "int192m_T",
  "uint192m_T",
  "int224m_T",
  "uint224m_T",
  "int256m_T",
  "uint256m_T"
};

/* data type transitions for block I/O structure */
static DataTypeTransition rtBTransitions[] = {
  { (char_T *)(&sensorFusion_B.UDPReceive_o1[0]), 1, 0, 32 },

  { (char_T *)(&sensorFusion_B.accel[0]), 1, 0, 29 },

  { (char_T *)(&sensorFusion_B.MinMax), 1, 0, 1 },

  { (char_T *)(&sensorFusion_B.UDPReceive_o2), 5, 0, 1 }
  ,

  { (char_T *)(&sensorFusion_DW.UDPReceive_NetworkLib[0]), 0, 0, 137 },

  { (char_T *)(&sensorFusion_DW.Scope3_PWORK.LoggedData[0]), 11, 0, 7 },

  { (char_T *)(&sensorFusion_DW.UnitDelay_DSTATE[0].re), 1, 1, 40 },

  { (char_T *)(&sensorFusion_DW.UnitDelay_DSTATE_j), 1, 0, 1 },

  { (char_T *)(&sensorFusion_DW.UnitDelay2_DSTATE), 7, 0, 2 },

  { (char_T *)(&sensorFusion_DW.runSensorFusion_SubsysRanBC), 2, 0, 1 }
};

/* data type transition table for block I/O structure */
static DataTypeTransitionTable rtBTransTable = {
  10U,
  rtBTransitions
};

/* data type transitions for Parameters structure */
static DataTypeTransition rtPTransitions[] = {
  { (char_T *)(&sensorFusion_P.aMean[0]), 0, 0, 13 },

  { (char_T *)(&sensorFusion_P.Bias_Bias[0]), 1, 0, 24 },

  { (char_T *)(&sensorFusion_P.Constant_Value), 6, 0, 4 },

  { (char_T *)(&sensorFusion_P.UnitDelay2_InitialCondition), 7, 0, 3 },

  { (char_T *)(&sensorFusion_P.Constant_Value_h), 5, 0, 1 }
};

/* data type transition table for Parameters structure */
static DataTypeTransitionTable rtPTransTable = {
  5U,
  rtPTransitions
};

/* [EOF] sensorFusion_dt.h */
