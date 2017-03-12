/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: sensorFusion.h
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

#ifndef RTW_HEADER_sensorFusion_h_
#define RTW_HEADER_sensorFusion_h_
#include <math.h>
#include <string.h>
#include <float.h>
#include <stddef.h>
#ifndef sensorFusion_COMMON_INCLUDES_
# define sensorFusion_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "zero_crossing_types.h"
#include "rtw_extmode.h"
#include "sysran_types.h"
#include "dt_info.h"
#include "ext_work.h"
#include "HostLib_Network.h"
#endif                                 /* sensorFusion_COMMON_INCLUDES_ */

#include "sensorFusion_types.h"

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
  creal32_T c_y[36];
  creal32_T H[36];
  creal32_T y[36];
  real_T H_m[24];
  creal32_T K[24];
  creal32_T H_c[24];
  creal32_T H_k[24];
  creal32_T H_cx[24];
  real32_T R[36];
  real_T A[16];
  creal32_T P_apriori[16];
  creal32_T P[16];                     /* '<S3>/MATLAB Function' */
  creal32_T A_b[16];
  creal32_T A_p[16];
  creal32_T A_c[16];
  creal32_T y_f[16];
  creal32_T F[16];
  creal32_T A2[16];
  creal32_T A3[16];
  creal32_T A4[16];
  creal32_T A_g[16];
  creal32_T b_A[16];
  real32_T UDPReceive_o1[32];          /* '<Root>/UDP Receive' */
  creal32_T QqChi[12];
  creal32_T y_g[12];
  real_T d[9];
  creal32_T b_C_n[9];
  creal32_T b[9];
  creal32_T b_C_n_m[9];
  creal32_T s[9];
  real32_T fv0[16];
  real32_T MatrixConcatenate1[12];     /* '<S4>/Matrix Concatenate1' */
  real32_T MatrixConcatenate2[12];     /* '<S4>/Matrix Concatenate2' */
  creal32_T fcv0[6];
  creal32_T fcv1[6];
  creal32_T g[6];
  creal32_T x_apriori[4];
  creal32_T xtemp[4];
  creal32_T x[4];                      /* '<S3>/MATLAB Function' */
  real32_T MathFunction[6];            /* '<S4>/Math Function' */
  real32_T MatrixConcatenate[6];       /* '<S4>/Matrix Concatenate' */
  real32_T fv1[6];
  real32_T fv2[6];
  real32_T g_n[6];
  real32_T accel[3];                   /* '<S3>/Selector' */
  real32_T Bias[3];                    /* '<S3>/Bias' */
  real32_T mag[3];                     /* '<S3>/Selector2' */
  real32_T ComplextoRealImag[4];       /* '<S3>/Complex to Real-Imag' */
  real32_T ComplextoRealImag1[16];     /* '<S3>/Complex to Real-Imag1' */
  real_T y_p;
  uint64m_T r0;
  creal32_T x_apriori_l;
  creal32_T A_j;
  creal32_T A4_d;
  creal32_T F_g;
  creal32_T A4_l;
  creal32_T zNew;
  int8_T ipiv[4];
  real32_T MinMax;                     /* '<S4>/MinMax' */
  real32_T b_dx;
  real32_T rtb_x_im;
  real32_T u1;
  real32_T normA;
  real32_T b_s;
  real32_T brm;
  real32_T bim;
  real32_T sgnbi;
  real32_T temp_re;
  real32_T temp_im;
  real32_T scale;
  real32_T absxk;
  real32_T absxk_d;
  real32_T a;
  real32_T scale_d;
  real32_T absxk_l;
  real32_T t;
  real32_T f0;
  real32_T f1;
  int32_T s3_iter;
  int32_T i;
  int32_T s3_iter_o;
  int32_T i0;
  int32_T b_j;
  int32_T eint;
  int32_T i1;
  int32_T d_b;
  int32_T i2;
  int32_T j;
  int32_T iy;
  int32_T c_ix;
  int32_T d_n;
  int32_T ijA;
  int32_T b_jBcol;
  int32_T b_kAcol;
  int32_T c_i;
  int32_T i3;
  int32_T i4;
  int32_T exponent;
  uint32_T y_b;
  uint32_T u0;
  uint16_T UDPReceive_o2;              /* '<Root>/UDP Receive' */
  boolean_T Compare;                   /* '<S1>/Compare' */
} B_sensorFusion_T;

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  real_T UDPReceive_NetworkLib[137];   /* '<Root>/UDP Receive' */
  struct {
    void *LoggedData[2];
  } Scope3_PWORK;                      /* '<S4>/Scope3' */

  struct {
    void *LoggedData[3];
  } Scope_PWORK;                       /* '<S3>/Scope' */

  struct {
    void *LoggedData;
  } Scope1_PWORK;                      /* '<S3>/Scope1' */

  struct {
    void *LoggedData;
  } Scope2_PWORK;                      /* '<S3>/Scope2' */

  creal32_T UnitDelay_DSTATE[4];       /* '<S3>/Unit Delay' */
  creal32_T UnitDelay1_DSTATE[16];     /* '<S3>/Unit Delay1' */
  real32_T UnitDelay_DSTATE_j;         /* '<S4>/Unit Delay' */
  uint32_T UnitDelay2_DSTATE;          /* '<S4>/Unit Delay2' */
  uint32_T UnitDelay1_DSTATE_k;        /* '<S4>/Unit Delay1' */
  int8_T runSensorFusion_SubsysRanBC;  /* '<Root>/runSensorFusion' */
} DW_sensorFusion_T;

/* Zero-crossing (trigger) state */
typedef struct {
  ZCSigState runSensorFusion_Trig_ZCE; /* '<Root>/runSensorFusion' */
} PrevZCX_sensorFusion_T;

/* Parameters (auto storage) */
struct P_sensorFusion_T_ {
  real_T aMean[3];                     /* Variable: aMean
                                        * Referenced by: '<S3>/Constant4'
                                        */
  real_T aVar[3];                      /* Variable: aVar
                                        * Referenced by: '<S3>/Constant2'
                                        */
  real_T mMean[3];                     /* Variable: mMean
                                        * Referenced by: '<S3>/Constant5'
                                        */
  real_T mVar[3];                      /* Variable: mVar
                                        * Referenced by: '<S3>/Constant3'
                                        */
  real_T Constant6_Value;              /* Expression: 1/200
                                        * Referenced by: '<S3>/Constant6'
                                        */
  real32_T Bias_Bias[3];               /* Computed Parameter: Bias_Bias
                                        * Referenced by: '<S3>/Bias'
                                        */
  real32_T UnitDelay_InitialCondition[4];/* Expression: single([0 0 0 1])
                                          * Referenced by: '<S3>/Unit Delay'
                                          */
  real32_T UnitDelay1_InitialCondition[16];/* Expression: single(eye(4))
                                            * Referenced by: '<S3>/Unit Delay1'
                                            */
  real32_T UnitDelay_InitialCondition_i;/* Computed Parameter: UnitDelay_InitialCondition_i
                                         * Referenced by: '<S4>/Unit Delay'
                                         */
  int32_T Constant_Value;              /* Computed Parameter: Constant_Value
                                        * Referenced by: '<S3>/Constant'
                                        */
  int32_T Constant1_Value;             /* Computed Parameter: Constant1_Value
                                        * Referenced by: '<S3>/Constant1'
                                        */
  int32_T ForIterator_IterationLimit;  /* Computed Parameter: ForIterator_IterationLimit
                                        * Referenced by: '<S3>/For Iterator'
                                        */
  int32_T Switch_Threshold;            /* Computed Parameter: Switch_Threshold
                                        * Referenced by: '<S3>/Switch'
                                        */
  uint32_T UnitDelay2_InitialCondition;/* Computed Parameter: UnitDelay2_InitialCondition
                                        * Referenced by: '<S4>/Unit Delay2'
                                        */
  uint32_T UnitDelay1_InitialCondition_d;/* Computed Parameter: UnitDelay1_InitialCondition_d
                                          * Referenced by: '<S4>/Unit Delay1'
                                          */
  uint32_T Constant_Value_m;           /* Computed Parameter: Constant_Value_m
                                        * Referenced by: '<S4>/Constant'
                                        */
  uint16_T Constant_Value_h;           /* Computed Parameter: Constant_Value_h
                                        * Referenced by: '<S1>/Constant'
                                        */
};

/* Real-time Model Data Structure */
struct tag_RTM_sensorFusion_T {
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
extern P_sensorFusion_T sensorFusion_P;

/* Block signals (auto storage) */
extern B_sensorFusion_T sensorFusion_B;

/* Block states (auto storage) */
extern DW_sensorFusion_T sensorFusion_DW;

/* External data declarations for dependent source files */

/* Zero-crossing (trigger) state */
extern PrevZCX_sensorFusion_T sensorFusion_PrevZCX;

/* Model entry point functions */
extern void sensorFusion_initialize(void);
extern void sensorFusion_step(void);
extern void sensorFusion_terminate(void);

/* Real-time Model object */
extern RT_MODEL_sensorFusion_T *const sensorFusion_M;

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
 * '<Root>' : 'sensorFusion'
 * '<S1>'   : 'sensorFusion/Compare To Zero'
 * '<S2>'   : 'sensorFusion/runSensorFusion'
 * '<S3>'   : 'sensorFusion/runSensorFusion/iterateAlg'
 * '<S4>'   : 'sensorFusion/runSensorFusion/unpackData'
 * '<S5>'   : 'sensorFusion/runSensorFusion/iterateAlg/MATLAB Function'
 * '<S6>'   : 'sensorFusion/runSensorFusion/unpackData/MATLAB Function'
 */
#endif                                 /* RTW_HEADER_sensorFusion_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
