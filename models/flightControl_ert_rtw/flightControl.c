/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: flightControl.c
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

#include "flightControl.h"
#include "flightControl_private.h"
#include "flightControl_dt.h"

/* Block signals (auto storage) */
B_flightControl_T flightControl_B;

/* Block states (auto storage) */
DW_flightControl_T flightControl_DW;

/* Real-time model */
RT_MODEL_flightControl_T flightControl_M_;
RT_MODEL_flightControl_T *const flightControl_M = &flightControl_M_;

/* Forward declaration for local functions */
static real32_T flightControl_norm(const real32_T x[3]);
static real32_T flightControl_norm_l(const real32_T x[4]);

/* Function for MATLAB Function: '<S3>/runMahonyUpdate' */
static real32_T flightControl_norm(const real32_T x[3])
{
  real32_T y;
  real32_T scale;
  real32_T absxk;
  real32_T t;
  scale = 1.17549435E-38F;
  absxk = (real32_T)fabs(x[0]);
  if (absxk > 1.17549435E-38F) {
    y = 1.0F;
    scale = absxk;
  } else {
    t = absxk / 1.17549435E-38F;
    y = t * t;
  }

  absxk = (real32_T)fabs(x[1]);
  if (absxk > scale) {
    t = scale / absxk;
    y = y * t * t + 1.0F;
    scale = absxk;
  } else {
    t = absxk / scale;
    y += t * t;
  }

  absxk = (real32_T)fabs(x[2]);
  if (absxk > scale) {
    t = scale / absxk;
    y = y * t * t + 1.0F;
    scale = absxk;
  } else {
    t = absxk / scale;
    y += t * t;
  }

  return scale * (real32_T)sqrt(y);
}

/* Function for MATLAB Function: '<S3>/runMahonyUpdate' */
static real32_T flightControl_norm_l(const real32_T x[4])
{
  real32_T y;
  real32_T scale;
  real32_T absxk;
  real32_T t;
  scale = 1.17549435E-38F;
  absxk = (real32_T)fabs(x[0]);
  if (absxk > 1.17549435E-38F) {
    y = 1.0F;
    scale = absxk;
  } else {
    t = absxk / 1.17549435E-38F;
    y = t * t;
  }

  absxk = (real32_T)fabs(x[1]);
  if (absxk > scale) {
    t = scale / absxk;
    y = y * t * t + 1.0F;
    scale = absxk;
  } else {
    t = absxk / scale;
    y += t * t;
  }

  absxk = (real32_T)fabs(x[2]);
  if (absxk > scale) {
    t = scale / absxk;
    y = y * t * t + 1.0F;
    scale = absxk;
  } else {
    t = absxk / scale;
    y += t * t;
  }

  absxk = (real32_T)fabs(x[3]);
  if (absxk > scale) {
    t = scale / absxk;
    y = y * t * t + 1.0F;
    scale = absxk;
  } else {
    t = absxk / scale;
    y += t * t;
  }

  return scale * (real32_T)sqrt(y);
}

/* Model step function */
void flightControl_step(void)
{
  char_T *sErr;
  boolean_T b_y;
  boolean_T x[3];
  real32_T q1q0;
  real32_T q2q3;
  real32_T q2q0;
  real32_T q3q0;
  real32_T q1q1;
  real32_T q2q2;
  real32_T q3q3;
  int32_T i;
  int32_T i_0;
  uint32_T qY;
  boolean_T exitg1;
  boolean_T exitg2;
  boolean_T exitg3;

  /* Reset subsysRan breadcrumbs */
  srClearBC(flightControl_DW.runSensorFusion_SubsysRanBC);

  /* S-Function (sdspFromNetwork): '<Root>/UDP Receive' */
  sErr = GetErrorBuffer(&flightControl_DW.UDPReceive_NetworkLib[0U]);
  i = 31;
  LibOutputs_Network(&flightControl_DW.UDPReceive_NetworkLib[0U],
                     &flightControl_B.UDPReceive_o1[0U], &i);
  if (*sErr != 0) {
    rtmSetErrorStatus(flightControl_M, sErr);
    rtmSetStopRequested(flightControl_M, 1);
  }

  flightControl_B.UDPReceive_o2 = (uint16_T)i;

  /* End of S-Function (sdspFromNetwork): '<Root>/UDP Receive' */

  /* Outputs for Enabled SubSystem: '<Root>/runSensorFusion' incorporates:
   *  EnablePort: '<S2>/Enable'
   */
  /* RelationalOperator: '<S1>/Compare' incorporates:
   *  Constant: '<S1>/Constant'
   */
  if (flightControl_B.UDPReceive_o2 > flightControl_P.Constant_Value_p) {
    if (!flightControl_DW.runSensorFusion_MODE) {
      flightControl_DW.runSensorFusion_MODE = true;
    }

    /* Concatenate: '<S4>/Matrix Concatenate1' */
    flightControl_B.MatrixConcatenate1[0] = flightControl_B.UDPReceive_o1[0];
    flightControl_B.MatrixConcatenate1[3] = flightControl_B.UDPReceive_o1[1];
    flightControl_B.MatrixConcatenate1[6] = flightControl_B.UDPReceive_o1[2];
    flightControl_B.MatrixConcatenate1[9] = flightControl_B.UDPReceive_o1[3];
    flightControl_B.MatrixConcatenate1[1] = flightControl_B.UDPReceive_o1[4];
    flightControl_B.MatrixConcatenate1[4] = flightControl_B.UDPReceive_o1[5];
    flightControl_B.MatrixConcatenate1[7] = flightControl_B.UDPReceive_o1[6];
    flightControl_B.MatrixConcatenate1[10] = flightControl_B.UDPReceive_o1[7];
    flightControl_B.MatrixConcatenate1[2] = flightControl_B.UDPReceive_o1[8];
    flightControl_B.MatrixConcatenate1[5] = flightControl_B.UDPReceive_o1[9];
    flightControl_B.MatrixConcatenate1[8] = flightControl_B.UDPReceive_o1[10];
    flightControl_B.MatrixConcatenate1[11] = flightControl_B.UDPReceive_o1[11];

    /* Selector: '<S3>/Selector' */
    flightControl_B.Selector[0] = flightControl_B.MatrixConcatenate1[9];
    flightControl_B.Selector[1] = flightControl_B.MatrixConcatenate1[10];
    flightControl_B.Selector[2] = flightControl_B.MatrixConcatenate1[11];

    /* Concatenate: '<S4>/Matrix Concatenate2' */
    flightControl_B.MatrixConcatenate2[0] = flightControl_B.UDPReceive_o1[12];
    flightControl_B.MatrixConcatenate2[3] = flightControl_B.UDPReceive_o1[13];
    flightControl_B.MatrixConcatenate2[6] = flightControl_B.UDPReceive_o1[14];
    flightControl_B.MatrixConcatenate2[9] = flightControl_B.UDPReceive_o1[15];
    flightControl_B.MatrixConcatenate2[1] = flightControl_B.UDPReceive_o1[16];
    flightControl_B.MatrixConcatenate2[4] = flightControl_B.UDPReceive_o1[17];
    flightControl_B.MatrixConcatenate2[7] = flightControl_B.UDPReceive_o1[18];
    flightControl_B.MatrixConcatenate2[10] = flightControl_B.UDPReceive_o1[19];
    flightControl_B.MatrixConcatenate2[2] = flightControl_B.UDPReceive_o1[20];
    flightControl_B.MatrixConcatenate2[5] = flightControl_B.UDPReceive_o1[21];
    flightControl_B.MatrixConcatenate2[8] = flightControl_B.UDPReceive_o1[22];
    flightControl_B.MatrixConcatenate2[11] = flightControl_B.UDPReceive_o1[23];

    /* MATLAB Function: '<S5>/calibrate' incorporates:
     *  Constant: '<S5>/Constant'
     */
    /* MATLAB Function 'translateIMUToWorld/calibrateSensorData/calibrate': '<S10>:1' */
    /* '<S10>:1:5' if isempty(count) */
    /* '<S10>:1:10' if count>=sampleSize */
    if ((real_T)flightControl_DW.count >= flightControl_P.Constant_Value) {
      /* '<S10>:1:11' cal=raw-[bias bias bias bias]; */
      flightControl_B.cal[0] = flightControl_B.MatrixConcatenate2[0] -
        flightControl_DW.bias[0];
      flightControl_B.cal[3] = flightControl_B.MatrixConcatenate2[3] -
        flightControl_DW.bias[0];
      flightControl_B.cal[6] = flightControl_B.MatrixConcatenate2[6] -
        flightControl_DW.bias[0];
      flightControl_B.cal[9] = flightControl_B.MatrixConcatenate2[9] -
        flightControl_DW.bias[0];
      flightControl_B.cal[1] = flightControl_B.MatrixConcatenate2[1] -
        flightControl_DW.bias[1];
      flightControl_B.cal[4] = flightControl_B.MatrixConcatenate2[4] -
        flightControl_DW.bias[1];
      flightControl_B.cal[7] = flightControl_B.MatrixConcatenate2[7] -
        flightControl_DW.bias[1];
      flightControl_B.cal[10] = flightControl_B.MatrixConcatenate2[10] -
        flightControl_DW.bias[1];
      flightControl_B.cal[2] = flightControl_B.MatrixConcatenate2[2] -
        flightControl_DW.bias[2];
      flightControl_B.cal[5] = flightControl_B.MatrixConcatenate2[5] -
        flightControl_DW.bias[2];
      flightControl_B.cal[8] = flightControl_B.MatrixConcatenate2[8] -
        flightControl_DW.bias[2];
      flightControl_B.cal[11] = flightControl_B.MatrixConcatenate2[11] -
        flightControl_DW.bias[2];
    } else {
      /* '<S10>:1:12' else */
      /* '<S10>:1:13' cal=single(zeros(3,4)); */
      for (i = 0; i < 12; i++) {
        flightControl_B.cal[i] = 0.0F;
      }

      /* '<S10>:1:14' for i=1:4 */
      for (i = 0; i < 4; i++) {
        /* '<S10>:1:15' bias=bias+single((1/sampleSize)).*raw(:,i); */
        flightControl_B.q1q2 = 1.0F / flightControl_P.Constant_Value;
        flightControl_DW.bias[0] += flightControl_B.MatrixConcatenate2[3 * i] *
          flightControl_B.q1q2;
        flightControl_DW.bias[1] += flightControl_B.MatrixConcatenate2[3 * i + 1]
          * flightControl_B.q1q2;
        flightControl_DW.bias[2] += flightControl_B.MatrixConcatenate2[3 * i + 2]
          * flightControl_B.q1q2;

        /* '<S10>:1:16' count=count+1; */
        qY = flightControl_DW.count + /*MW:OvSatOk*/ 1U;
        if (qY < flightControl_DW.count) {
          qY = MAX_uint32_T;
        }

        flightControl_DW.count = qY;
      }
    }

    /* End of MATLAB Function: '<S5>/calibrate' */

    /* Concatenate: '<S4>/Matrix Concatenate' */
    /* '<S10>:1:19' biasOut=bias; */
    flightControl_B.MatrixConcatenate[0] = flightControl_B.UDPReceive_o1[24];
    flightControl_B.MatrixConcatenate[3] = flightControl_B.UDPReceive_o1[25];
    flightControl_B.MatrixConcatenate[1] = flightControl_B.UDPReceive_o1[26];
    flightControl_B.MatrixConcatenate[4] = flightControl_B.UDPReceive_o1[27];
    flightControl_B.MatrixConcatenate[2] = flightControl_B.UDPReceive_o1[28];
    flightControl_B.MatrixConcatenate[5] = flightControl_B.UDPReceive_o1[29];

    /* MATLAB Function: '<S3>/runMahonyUpdate' incorporates:
     *  Constant: '<S3>/Constant2'
     */
    /* MATLAB Function 'translateIMUToWorld/runMahonyUpdate': '<S9>:1' */
    /* '<S9>:1:3' if isempty(qLocal) */
    /* '<S9>:1:7' qIn=qLocal; */
    /* '<S9>:1:10' counter=counter+1; */
    flightControl_DW.counter++;

    /* '<S9>:1:12' if counter>100 */
    /* '<S9>:1:16' magInterp=interp1([1 4],Magnetometer',[1 2 3 4],'linear')'; */
    for (flightControl_B.b_k = 0; flightControl_B.b_k < 3; flightControl_B.b_k++)
    {
      flightControl_B.varargin_2[flightControl_B.b_k << 1] =
        flightControl_B.MatrixConcatenate[flightControl_B.b_k];
      flightControl_B.varargin_2[1 + (flightControl_B.b_k << 1)] =
        flightControl_B.MatrixConcatenate[flightControl_B.b_k + 3];
    }

    for (flightControl_B.b_k = 0; flightControl_B.b_k < 12; flightControl_B.b_k
         ++) {
      flightControl_B.MatrixConcatenate2[flightControl_B.b_k] = (rtNaNF);
    }

    for (i = 0; i < 4; i++) {
      flightControl_B.r = ((real_T)(i + 1) - 1.0) / 3.0;
      if (flightControl_B.r == 0.0) {
        flightControl_B.MatrixConcatenate2[i] = flightControl_B.varargin_2[0];
        flightControl_B.MatrixConcatenate2[i + 4] = flightControl_B.varargin_2[2];
        flightControl_B.MatrixConcatenate2[i + 8] = flightControl_B.varargin_2[4];
      } else if (flightControl_B.r == 1.0) {
        flightControl_B.MatrixConcatenate2[i] = flightControl_B.varargin_2[1];
        flightControl_B.MatrixConcatenate2[i + 4] = flightControl_B.varargin_2[3];
        flightControl_B.MatrixConcatenate2[i + 8] = flightControl_B.varargin_2[5];
      } else {
        if (flightControl_B.varargin_2[0] == flightControl_B.varargin_2[1]) {
          flightControl_B.MatrixConcatenate2[i] = flightControl_B.varargin_2[0];
        } else {
          flightControl_B.MatrixConcatenate2[i] = (real32_T)(1.0 -
            flightControl_B.r) * flightControl_B.varargin_2[0] + (real32_T)
            flightControl_B.r * flightControl_B.varargin_2[1];
        }

        if (flightControl_B.varargin_2[2] == flightControl_B.varargin_2[3]) {
          flightControl_B.MatrixConcatenate2[i + 4] =
            flightControl_B.varargin_2[2];
        } else {
          flightControl_B.MatrixConcatenate2[i + 4] = (real32_T)(1.0 -
            flightControl_B.r) * flightControl_B.varargin_2[2] + (real32_T)
            flightControl_B.r * flightControl_B.varargin_2[3];
        }

        if (flightControl_B.varargin_2[4] == flightControl_B.varargin_2[5]) {
          flightControl_B.MatrixConcatenate2[i + 8] =
            flightControl_B.varargin_2[4];
        } else {
          flightControl_B.MatrixConcatenate2[i + 8] = (real32_T)(1.0 -
            flightControl_B.r) * flightControl_B.varargin_2[4] + (real32_T)
            flightControl_B.r * flightControl_B.varargin_2[5];
        }
      }
    }

    for (flightControl_B.b_k = 0; flightControl_B.b_k < 4; flightControl_B.b_k++)
    {
      flightControl_B.magInterp[3 * flightControl_B.b_k] =
        flightControl_B.MatrixConcatenate2[flightControl_B.b_k];
      flightControl_B.magInterp[1 + 3 * flightControl_B.b_k] =
        flightControl_B.MatrixConcatenate2[flightControl_B.b_k + 4];
      flightControl_B.magInterp[2 + 3 * flightControl_B.b_k] =
        flightControl_B.MatrixConcatenate2[flightControl_B.b_k + 8];
    }

    /* '<S9>:1:18' for i=1:4 */
    for (i = 0; i < 4; i++) {
      /* '<S9>:1:20' q  = runMadwickUpdate(qIn,Accelerometer(:,i),Gyroscope(:,i),magInterp(:,i),Beta); */
      flightControl_B.q1q3 = flightControl_B.MatrixConcatenate1[3 * i];
      q1q0 = flightControl_B.MatrixConcatenate1[3 * i + 1];
      q2q3 = flightControl_B.MatrixConcatenate1[3 * i + 2];
      q2q0 = flightControl_B.magInterp[3 * i];
      q3q0 = flightControl_B.magInterp[3 * i + 1];
      q1q1 = flightControl_B.magInterp[3 * i + 2];

      /* '<S9>:1:28' q=qIn; */
      /* '<S9>:1:29' SamplePeriod=single(5/1000); */
      /*  Normalise accelerometer measurement */
      /* '<S9>:1:32' if ~all(abs(Accelerometer)<.0001) */
      flightControl_B.q1q2 = (real32_T)fabs(flightControl_B.MatrixConcatenate1[3
        * i]);
      q2q2 = (real32_T)fabs(flightControl_B.MatrixConcatenate1[3 * i + 1]);
      q3q3 = (real32_T)fabs(flightControl_B.MatrixConcatenate1[3 * i + 2]);
      x[0] = (flightControl_B.q1q2 < 0.0001);
      x[1] = (q2q2 < 0.0001);
      x[2] = (q3q3 < 0.0001);
      b_y = true;
      flightControl_B.b_k = 0;
      exitg3 = false;
      while ((!exitg3) && (flightControl_B.b_k < 3)) {
        if (!x[flightControl_B.b_k]) {
          b_y = false;
          exitg3 = true;
        } else {
          flightControl_B.b_k++;
        }
      }

      if (!b_y) {
        /* '<S9>:1:33' Accelerometer = Accelerometer / norm(Accelerometer); */
        flightControl_B.q1q2 = flightControl_norm
          (&flightControl_B.MatrixConcatenate1[3 * i]);
        flightControl_B.q1q3 = flightControl_B.MatrixConcatenate1[3 * i] /
          flightControl_B.q1q2;
        q1q0 = flightControl_B.MatrixConcatenate1[3 * i + 1] /
          flightControl_B.q1q2;
        q2q3 = flightControl_B.MatrixConcatenate1[3 * i + 2] /
          flightControl_B.q1q2;

        /*  normalise magnitude */
      }

      /*  Normalise magnetometer measurement */
      /* '<S9>:1:36' if ~all(abs(Magnetometer)<.0001) */
      flightControl_B.q1q2 = (real32_T)fabs(flightControl_B.magInterp[3 * i]);
      q2q2 = (real32_T)fabs(flightControl_B.magInterp[3 * i + 1]);
      q3q3 = (real32_T)fabs(flightControl_B.magInterp[3 * i + 2]);
      x[0] = (flightControl_B.q1q2 < 0.0001);
      x[1] = (q2q2 < 0.0001);
      x[2] = (q3q3 < 0.0001);
      b_y = true;
      flightControl_B.b_k = 0;
      exitg2 = false;
      while ((!exitg2) && (flightControl_B.b_k < 3)) {
        if (!x[flightControl_B.b_k]) {
          b_y = false;
          exitg2 = true;
        } else {
          flightControl_B.b_k++;
        }
      }

      if (!b_y) {
        /* '<S9>:1:37' Magnetometer = Magnetometer / norm(Magnetometer); */
        flightControl_B.q1q2 = flightControl_norm(&flightControl_B.magInterp[3 *
          i]);
        q2q0 = flightControl_B.magInterp[3 * i] / flightControl_B.q1q2;
        q3q0 = flightControl_B.magInterp[3 * i + 1] / flightControl_B.q1q2;
        q1q1 = flightControl_B.magInterp[3 * i + 2] / flightControl_B.q1q2;

        /*  normalise magnitude */
      }

      /*  Reference direction of Earth's magnetic feild */
      /* '<S9>:1:40' h = quaternProd(q, quaternProd([0 Magnetometer'], quaternConj(q))); */
      /* QUATERN2ROTMAT Converts a quaternion to its conjugate */
      /*  */
      /*    qConj = quaternConj(q) */
      /*  */
      /*    Converts a quaternion to its conjugate. */
      /*  */
      /*    For more information see: */
      /*    http://www.x-io.co.uk/node/8#quaternions */
      /*  */
      /* 	Date          Author          Notes */
      /* 	27/09/2011    SOH Madgwick    Initial release */
      /* '<S9>:1:100' qConj = [q(1); -q(2); -q(3); -q(4)]; */
      flightControl_B.q[0] = flightControl_DW.qLocal[0];
      flightControl_B.q[1] = -flightControl_DW.qLocal[1];
      flightControl_B.q[2] = -flightControl_DW.qLocal[2];
      flightControl_B.q[3] = -flightControl_DW.qLocal[3];

      /* '<S9>:1:69' ab=zeros(4,1); */
      /* QUATERNPROD Calculates the quaternion product */
      /*  */
      /*    ab = quaternProd(a, b) */
      /*  */
      /*    Calculates the quaternion product of quaternion a and b. */
      /*  */
      /*    For more information see: */
      /*    http://www.x-io.co.uk/node/8#quaternions */
      /*  */
      /* 	Date          Author          Notes */
      /* 	27/09/2011    SOH Madgwick    Initial release */
      /* '<S9>:1:82' ab(1) = a(1).*b(1)-a(2).*b(2)-a(3).*b(3)-a(4).*b(4); */
      flightControl_B.b_idx_3 = ((0.0F * flightControl_DW.qLocal[0] - q2q0 *
        -flightControl_DW.qLocal[1]) - q3q0 * -flightControl_DW.qLocal[2]) -
        q1q1 * -flightControl_DW.qLocal[3];

      /* '<S9>:1:83' ab(2) = a(1).*b(2)+a(2).*b(1)+a(3).*b(4)-a(4).*b(3); */
      flightControl_B.ab_idx_1 = ((0.0F * -flightControl_DW.qLocal[1] + q2q0 *
        flightControl_DW.qLocal[0]) + q3q0 * -flightControl_DW.qLocal[3]) - q1q1
        * -flightControl_DW.qLocal[2];

      /* '<S9>:1:84' ab(3) = a(1).*b(3)-a(2).*b(4)+a(3).*b(1)+a(4).*b(2); */
      flightControl_B.ab_idx_2 = ((0.0F * -flightControl_DW.qLocal[2] - q2q0 *
        -flightControl_DW.qLocal[3]) + q3q0 * flightControl_DW.qLocal[0]) + q1q1
        * -flightControl_DW.qLocal[1];

      /* '<S9>:1:85' ab(4) = a(1).*b(4)+a(2).*b(3)-a(3).*b(2)+a(4).*b(1); */
      flightControl_B.ab_idx_3 = ((0.0F * -flightControl_DW.qLocal[3] + q2q0 *
        -flightControl_DW.qLocal[2]) - q3q0 * -flightControl_DW.qLocal[1]) +
        q1q1 * flightControl_DW.qLocal[0];

      /* '<S9>:1:69' ab=zeros(4,1); */
      /* QUATERNPROD Calculates the quaternion product */
      /*  */
      /*    ab = quaternProd(a, b) */
      /*  */
      /*    Calculates the quaternion product of quaternion a and b. */
      /*  */
      /*    For more information see: */
      /*    http://www.x-io.co.uk/node/8#quaternions */
      /*  */
      /* 	Date          Author          Notes */
      /* 	27/09/2011    SOH Madgwick    Initial release */
      /* '<S9>:1:82' ab(1) = a(1).*b(1)-a(2).*b(2)-a(3).*b(3)-a(4).*b(4); */
      /* '<S9>:1:83' ab(2) = a(1).*b(2)+a(2).*b(1)+a(3).*b(4)-a(4).*b(3); */
      /* '<S9>:1:84' ab(3) = a(1).*b(3)-a(2).*b(4)+a(3).*b(1)+a(4).*b(2); */
      /* '<S9>:1:85' ab(4) = a(1).*b(4)+a(2).*b(3)-a(3).*b(2)+a(4).*b(1); */
      /* '<S9>:1:41' b = [0 norm([h(2) h(3)]) 0 h(4)]; */
      flightControl_B.scale = 2.2250738585072014E-308;
      flightControl_B.absxk = fabs(((flightControl_DW.qLocal[0] * (real32_T)
        flightControl_B.ab_idx_1 + flightControl_DW.qLocal[1] * (real32_T)
        flightControl_B.b_idx_3) + flightControl_DW.qLocal[2] * (real32_T)
        flightControl_B.ab_idx_3) - flightControl_DW.qLocal[3] * (real32_T)
        flightControl_B.ab_idx_2);
      if (flightControl_B.absxk > 2.2250738585072014E-308) {
        flightControl_B.r = 1.0;
        flightControl_B.scale = flightControl_B.absxk;
      } else {
        flightControl_B.t = flightControl_B.absxk / 2.2250738585072014E-308;
        flightControl_B.r = flightControl_B.t * flightControl_B.t;
      }

      flightControl_B.absxk = fabs(((flightControl_DW.qLocal[0] * (real32_T)
        flightControl_B.ab_idx_2 - flightControl_DW.qLocal[1] * (real32_T)
        flightControl_B.ab_idx_3) + flightControl_DW.qLocal[2] * (real32_T)
        flightControl_B.b_idx_3) + flightControl_DW.qLocal[3] * (real32_T)
        flightControl_B.ab_idx_1);
      if (flightControl_B.absxk > flightControl_B.scale) {
        flightControl_B.t = flightControl_B.scale / flightControl_B.absxk;
        flightControl_B.r = flightControl_B.r * flightControl_B.t *
          flightControl_B.t + 1.0;
        flightControl_B.scale = flightControl_B.absxk;
      } else {
        flightControl_B.t = flightControl_B.absxk / flightControl_B.scale;
        flightControl_B.r += flightControl_B.t * flightControl_B.t;
      }

      flightControl_B.r = flightControl_B.scale * sqrt(flightControl_B.r);
      flightControl_B.b_idx_3 = ((flightControl_DW.qLocal[0] * (real32_T)
        flightControl_B.ab_idx_3 + flightControl_DW.qLocal[1] * (real32_T)
        flightControl_B.ab_idx_2) - flightControl_DW.qLocal[2] * (real32_T)
        flightControl_B.ab_idx_1) + flightControl_DW.qLocal[3] * (real32_T)
        flightControl_B.b_idx_3;

      /*  Gradient decent algorithm corrective step */
      /* '<S9>:1:43' F = [2*(q(2)*q(4) - q(1)*q(3)) - Accelerometer(1) */
      /* '<S9>:1:44'     2*(q(1)*q(2) + q(3)*q(4)) - Accelerometer(2) */
      /* '<S9>:1:45'     2*(0.5 - q(2)^2 - q(3)^2) - Accelerometer(3) */
      /* '<S9>:1:46'     2*b(2)*(0.5 - q(3)^2 - q(4)^2) + 2*b(4)*(q(2)*q(4) - q(1)*q(3)) - Magnetometer(1) */
      /* '<S9>:1:47'     2*b(2)*(q(2)*q(3) - q(1)*q(4)) + 2*b(4)*(q(1)*q(2) + q(3)*q(4)) - Magnetometer(2) */
      /* '<S9>:1:48'     2*b(2)*(q(1)*q(3) + q(2)*q(4)) + 2*b(4)*(0.5 - q(2)^2 - q(3)^2) - Magnetometer(3)]; */
      /* '<S9>:1:49' J = [-2*q(3),                 	2*q(4),                    -2*q(1),                         2*q(2) */
      /* '<S9>:1:50'     2*q(2),                 	2*q(1),                    	2*q(4),                         2*q(3) */
      /* '<S9>:1:51'     0,                         -4*q(2),                    -4*q(3),                         0 */
      /* '<S9>:1:52'     -2*b(4)*q(3),               2*b(4)*q(4),               -4*b(2)*q(3)-2*b(4)*q(1),       -4*b(2)*q(4)+2*b(4)*q(2) */
      /* '<S9>:1:53'     -2*b(2)*q(4)+2*b(4)*q(2),	2*b(2)*q(3)+2*b(4)*q(1),	2*b(2)*q(2)+2*b(4)*q(4),       -2*b(2)*q(1)+2*b(4)*q(3) */
      /* '<S9>:1:54'     2*b(2)*q(3),                2*b(2)*q(4)-4*b(4)*q(2),	2*b(2)*q(1)-4*b(4)*q(3),        2*b(2)*q(2)]; */
      /* '<S9>:1:55' step = (J'*F); */
      flightControl_B.fv0[0] = -2.0F * flightControl_DW.qLocal[2];
      flightControl_B.fv0[1] = 2.0F * flightControl_DW.qLocal[3];
      flightControl_B.fv0[2] = -2.0F * flightControl_DW.qLocal[0];
      flightControl_B.fv0[3] = 2.0F * flightControl_DW.qLocal[1];
      flightControl_B.fv0[4] = 2.0F * flightControl_DW.qLocal[1];
      flightControl_B.fv0[5] = 2.0F * flightControl_DW.qLocal[0];
      flightControl_B.fv0[6] = 2.0F * flightControl_DW.qLocal[3];
      flightControl_B.fv0[7] = 2.0F * flightControl_DW.qLocal[2];
      flightControl_B.fv0[8] = 0.0F;
      flightControl_B.fv0[9] = -4.0F * flightControl_DW.qLocal[1];
      flightControl_B.fv0[10] = -4.0F * flightControl_DW.qLocal[2];
      flightControl_B.fv0[11] = 0.0F;
      flightControl_B.fv0[12] = (real32_T)(-2.0 * flightControl_B.b_idx_3) *
        flightControl_DW.qLocal[2];
      flightControl_B.fv0[13] = (real32_T)(2.0 * flightControl_B.b_idx_3) *
        flightControl_DW.qLocal[3];
      flightControl_B.fv0[14] = (real32_T)(-4.0 * flightControl_B.r) *
        flightControl_DW.qLocal[2] - (real32_T)(2.0 * flightControl_B.b_idx_3) *
        flightControl_DW.qLocal[0];
      flightControl_B.fv0[15] = (real32_T)(-4.0 * flightControl_B.r) *
        flightControl_DW.qLocal[3] + (real32_T)(2.0 * flightControl_B.b_idx_3) *
        flightControl_DW.qLocal[1];
      flightControl_B.fv0[16] = (real32_T)(-2.0 * flightControl_B.r) *
        flightControl_DW.qLocal[3] + (real32_T)(2.0 * flightControl_B.b_idx_3) *
        flightControl_DW.qLocal[1];
      flightControl_B.fv0[17] = (real32_T)(2.0 * flightControl_B.r) *
        flightControl_DW.qLocal[2] + (real32_T)(2.0 * flightControl_B.b_idx_3) *
        flightControl_DW.qLocal[0];
      flightControl_B.fv0[18] = (real32_T)(2.0 * flightControl_B.r) *
        flightControl_DW.qLocal[1] + (real32_T)(2.0 * flightControl_B.b_idx_3) *
        flightControl_DW.qLocal[3];
      flightControl_B.fv0[19] = (real32_T)(-2.0 * flightControl_B.r) *
        flightControl_DW.qLocal[0] + (real32_T)(2.0 * flightControl_B.b_idx_3) *
        flightControl_DW.qLocal[2];
      flightControl_B.fv0[20] = (real32_T)(2.0 * flightControl_B.r) *
        flightControl_DW.qLocal[2];
      flightControl_B.fv0[21] = (real32_T)(2.0 * flightControl_B.r) *
        flightControl_DW.qLocal[3] - (real32_T)(4.0 * flightControl_B.b_idx_3) *
        flightControl_DW.qLocal[1];
      flightControl_B.fv0[22] = (real32_T)(2.0 * flightControl_B.r) *
        flightControl_DW.qLocal[0] - (real32_T)(4.0 * flightControl_B.b_idx_3) *
        flightControl_DW.qLocal[2];
      flightControl_B.fv0[23] = (real32_T)(2.0 * flightControl_B.r) *
        flightControl_DW.qLocal[1];
      flightControl_B.fv1[0] = (flightControl_DW.qLocal[1] *
        flightControl_DW.qLocal[3] - flightControl_DW.qLocal[0] *
        flightControl_DW.qLocal[2]) * 2.0F - flightControl_B.q1q3;
      flightControl_B.fv1[1] = (flightControl_DW.qLocal[0] *
        flightControl_DW.qLocal[1] + flightControl_DW.qLocal[2] *
        flightControl_DW.qLocal[3]) * 2.0F - q1q0;
      flightControl_B.fv1[2] = ((0.5F - flightControl_DW.qLocal[1] *
        flightControl_DW.qLocal[1]) - flightControl_DW.qLocal[2] *
        flightControl_DW.qLocal[2]) * 2.0F - q2q3;
      flightControl_B.fv1[3] = (((0.5F - flightControl_DW.qLocal[2] *
        flightControl_DW.qLocal[2]) - flightControl_DW.qLocal[3] *
        flightControl_DW.qLocal[3]) * (real32_T)(2.0 * flightControl_B.r) +
        (flightControl_DW.qLocal[1] * flightControl_DW.qLocal[3] -
         flightControl_DW.qLocal[0] * flightControl_DW.qLocal[2]) * (real32_T)
        (2.0 * flightControl_B.b_idx_3)) - q2q0;
      flightControl_B.fv1[4] = ((flightControl_DW.qLocal[1] *
        flightControl_DW.qLocal[2] - flightControl_DW.qLocal[0] *
        flightControl_DW.qLocal[3]) * (real32_T)(2.0 * flightControl_B.r) +
        (flightControl_DW.qLocal[0] * flightControl_DW.qLocal[1] +
         flightControl_DW.qLocal[2] * flightControl_DW.qLocal[3]) * (real32_T)
        (2.0 * flightControl_B.b_idx_3)) - q3q0;
      flightControl_B.fv1[5] = (((0.5F - flightControl_DW.qLocal[1] *
        flightControl_DW.qLocal[1]) - flightControl_DW.qLocal[2] *
        flightControl_DW.qLocal[2]) * (real32_T)(2.0 * flightControl_B.b_idx_3)
        + (flightControl_DW.qLocal[0] * flightControl_DW.qLocal[2] +
           flightControl_DW.qLocal[1] * flightControl_DW.qLocal[3]) * (real32_T)
        (2.0 * flightControl_B.r)) - q1q1;
      for (flightControl_B.b_k = 0; flightControl_B.b_k < 4; flightControl_B.b_k
           ++) {
        flightControl_B.q[flightControl_B.b_k] = 0.0F;
        for (i_0 = 0; i_0 < 6; i_0++) {
          flightControl_B.q[flightControl_B.b_k] += flightControl_B.fv0[(i_0 <<
            2) + flightControl_B.b_k] * flightControl_B.fv1[i_0];
        }
      }

      /* '<S9>:1:56' step = step / norm(step); */
      flightControl_B.q1q2 = flightControl_norm_l(flightControl_B.q);
      flightControl_B.q[0] /= flightControl_B.q1q2;
      flightControl_B.q[1] /= flightControl_B.q1q2;
      flightControl_B.q[2] /= flightControl_B.q1q2;

      /*  normalise step magnitude */
      /*  Compute rate of change of quaternion */
      /* '<S9>:1:59' qDot = 0.5 * quaternProd(q, [0; Gyroscope(1); Gyroscope(2); Gyroscope(3)]) - Beta * step; */
      flightControl_B.q1q3 = flightControl_B.cal[3 * i];
      q1q0 = flightControl_B.cal[3 * i + 1];
      q2q3 = flightControl_B.cal[3 * i + 2];

      /* '<S9>:1:69' ab=zeros(4,1); */
      /* QUATERNPROD Calculates the quaternion product */
      /*  */
      /*    ab = quaternProd(a, b) */
      /*  */
      /*    Calculates the quaternion product of quaternion a and b. */
      /*  */
      /*    For more information see: */
      /*    http://www.x-io.co.uk/node/8#quaternions */
      /*  */
      /* 	Date          Author          Notes */
      /* 	27/09/2011    SOH Madgwick    Initial release */
      /* '<S9>:1:82' ab(1) = a(1).*b(1)-a(2).*b(2)-a(3).*b(3)-a(4).*b(4); */
      /* '<S9>:1:83' ab(2) = a(1).*b(2)+a(2).*b(1)+a(3).*b(4)-a(4).*b(3); */
      /* '<S9>:1:84' ab(3) = a(1).*b(3)-a(2).*b(4)+a(3).*b(1)+a(4).*b(2); */
      /* '<S9>:1:85' ab(4) = a(1).*b(4)+a(2).*b(3)-a(3).*b(2)+a(4).*b(1); */
      /*  Integrate to yield quaternion */
      /* '<S9>:1:62' if all(~isnan(qDot)) */
      q2q0 = (real32_T)((((flightControl_DW.qLocal[0] * 0.0F -
                           flightControl_DW.qLocal[1] * flightControl_B.q1q3) -
                          flightControl_DW.qLocal[2] * q1q0) -
                         flightControl_DW.qLocal[3] * q2q3) * 0.5) -
        flightControl_P.Constant2_Value * flightControl_B.q[0];
      flightControl_B.c_x[0] = !rtIsNaNF(q2q0);
      flightControl_B.q[0] = q2q0;
      q2q0 = (real32_T)((((flightControl_DW.qLocal[0] * flightControl_B.q1q3 +
                           flightControl_DW.qLocal[1] * 0.0F) +
                          flightControl_DW.qLocal[2] * q2q3) -
                         flightControl_DW.qLocal[3] * q1q0) * 0.5) -
        flightControl_P.Constant2_Value * flightControl_B.q[1];
      flightControl_B.c_x[1] = !rtIsNaNF(q2q0);
      flightControl_B.q[1] = q2q0;
      q2q0 = (real32_T)((((flightControl_DW.qLocal[0] * q1q0 -
                           flightControl_DW.qLocal[1] * q2q3) +
                          flightControl_DW.qLocal[2] * 0.0F) +
                         flightControl_DW.qLocal[3] * flightControl_B.q1q3) *
                        0.5) - flightControl_P.Constant2_Value *
        flightControl_B.q[2];
      flightControl_B.c_x[2] = !rtIsNaNF(q2q0);
      flightControl_B.q[2] = q2q0;
      q2q0 = (real32_T)((((flightControl_DW.qLocal[0] * q2q3 +
                           flightControl_DW.qLocal[1] * q1q0) -
                          flightControl_DW.qLocal[2] * flightControl_B.q1q3) +
                         flightControl_DW.qLocal[3] * 0.0F) * 0.5) -
        flightControl_B.q[3] / flightControl_B.q1q2 *
        flightControl_P.Constant2_Value;
      flightControl_B.c_x[3] = !rtIsNaNF(q2q0);
      b_y = true;
      flightControl_B.b_k = 0;
      exitg1 = false;
      while ((!exitg1) && (flightControl_B.b_k < 4)) {
        if (!flightControl_B.c_x[flightControl_B.b_k]) {
          b_y = false;
          exitg1 = true;
        } else {
          flightControl_B.b_k++;
        }
      }

      if (b_y) {
        /* '<S9>:1:63' q = q + qDot * SamplePeriod; */
        flightControl_DW.qLocal[0] += flightControl_B.q[0] * 0.005F;
        flightControl_DW.qLocal[1] += flightControl_B.q[1] * 0.005F;
        flightControl_DW.qLocal[2] += flightControl_B.q[2] * 0.005F;
        flightControl_DW.qLocal[3] += q2q0 * 0.005F;

        /* '<S9>:1:64' q = q / norm(q); */
        flightControl_B.q1q2 = flightControl_norm_l(flightControl_DW.qLocal);
        flightControl_DW.qLocal[0] /= flightControl_B.q1q2;
        flightControl_DW.qLocal[1] /= flightControl_B.q1q2;
        flightControl_DW.qLocal[2] /= flightControl_B.q1q2;
        flightControl_DW.qLocal[3] /= flightControl_B.q1q2;

        /*  normalise quaternion */
      }

      flightControl_B.q[0] = flightControl_DW.qLocal[0];
      flightControl_B.q[1] = flightControl_DW.qLocal[1];
      flightControl_B.q[2] = flightControl_DW.qLocal[2];
      flightControl_B.q[3] = flightControl_DW.qLocal[3];

      /* '<S9>:1:21' qIn = q; */
    }

    /* '<S9>:1:25' qLocal=q; */
    flightControl_DW.qLocal[0] = flightControl_B.q[0];
    flightControl_DW.qLocal[1] = flightControl_B.q[1];
    flightControl_DW.qLocal[2] = flightControl_B.q[2];
    flightControl_DW.qLocal[3] = flightControl_B.q[3];

    /* End of MATLAB Function: '<S3>/runMahonyUpdate' */

    /* MATLAB Function: '<S3>/q2cFcn' incorporates:
     *  MATLAB Function: '<S3>/qinvFcn'
     */
    /*  */
    /* MATLAB Function 'translateIMUToWorld/qinvFcn': '<S8>:1' */
    /* '<S8>:1:5' qout=[q(1); */
    /* '<S8>:1:6'       -q(2:4)]; */
    /*  Q2C computes a transformation matrix (c) from the given */
    /*  quaternion (q). */
    /*  */
    /*   usage: c=q2c(q) */
    /*  */
    /*  Transformation matrix is of the form: */
    /*  */
    /*      C = Cbn */
    /*      q = qnb */
    /*  */
    /*      where q(1)   = scalar part */
    /*            q(2-4) = vector part */
    /*  */
    /*     Vb = C * Vn */
    /*     Ib = C'* In * C */
    /*  */
    /* MATLAB Function 'translateIMUToWorld/q2cFcn': '<S7>:1' */
    /* '<S7>:1:19' q0=q(1); */
    /*  scalar part */
    /* '<S7>:1:20' q1=q(2); */
    /* '<S7>:1:21' q2=q(3); */
    /* '<S7>:1:22' q3=q(4); */
    /*  */
    /* '<S7>:1:24' q1q2=q1*q2; */
    flightControl_B.q1q2 = -flightControl_B.q[1] * -flightControl_B.q[2];

    /* '<S7>:1:25' q1q3=q1*q3; */
    flightControl_B.q1q3 = -flightControl_B.q[1] * -flightControl_B.q[3];

    /* '<S7>:1:26' q1q0=q1*q0; */
    q1q0 = -flightControl_B.q[1] * flightControl_B.q[0];

    /* '<S7>:1:27' q2q3=q2*q3; */
    q2q3 = -flightControl_B.q[2] * -flightControl_B.q[3];

    /* '<S7>:1:28' q2q0=q2*q0; */
    q2q0 = -flightControl_B.q[2] * flightControl_B.q[0];

    /* '<S7>:1:29' q3q0=q3*q0; */
    q3q0 = -flightControl_B.q[3] * flightControl_B.q[0];

    /* '<S7>:1:30' q1q1=q1*q1; */
    q1q1 = -flightControl_B.q[1] * -flightControl_B.q[1];

    /* '<S7>:1:31' q2q2=q2*q2; */
    q2q2 = -flightControl_B.q[2] * -flightControl_B.q[2];

    /* '<S7>:1:32' q3q3=q3*q3; */
    q3q3 = -flightControl_B.q[3] * -flightControl_B.q[3];

    /*  */
    /* '<S7>:1:34' c=single(zeros(3,3)); */
    /* '<S7>:1:35' s1=single(1.0); */
    /* '<S7>:1:36' s2=single(2.0); */
    /* '<S7>:1:38' c(1,1)=s1-s2*(q2q2+q3q3); */
    flightControl_B.c[0] = 1.0F - (q2q2 + q3q3) * 2.0F;

    /* '<S7>:1:39' c(1,2)=s2*(q1q2+q3q0); */
    flightControl_B.c[3] = (flightControl_B.q1q2 + q3q0) * 2.0F;

    /* '<S7>:1:40' c(1,3)=s2*(q1q3-q2q0); */
    flightControl_B.c[6] = (flightControl_B.q1q3 - q2q0) * 2.0F;

    /* '<S7>:1:41' c(2,1)=s2*(q1q2-q3q0); */
    flightControl_B.c[1] = (flightControl_B.q1q2 - q3q0) * 2.0F;

    /* '<S7>:1:42' c(2,2)=s1-s2*(q1q1+q3q3); */
    flightControl_B.c[4] = 1.0F - (q1q1 + q3q3) * 2.0F;

    /* '<S7>:1:43' c(2,3)=s2*(q2q3+q1q0); */
    flightControl_B.c[7] = (q2q3 + q1q0) * 2.0F;

    /* '<S7>:1:44' c(3,1)=s2*(q1q3+q2q0); */
    flightControl_B.c[2] = (flightControl_B.q1q3 + q2q0) * 2.0F;

    /* '<S7>:1:45' c(3,2)=s2*(q2q3-q1q0); */
    flightControl_B.c[5] = (q2q3 - q1q0) * 2.0F;

    /* '<S7>:1:46' c(3,3)=s1-s2*(q1q1+q2q2); */
    flightControl_B.c[8] = 1.0F - (q1q1 + q2q2) * 2.0F;
    for (flightControl_B.b_k = 0; flightControl_B.b_k < 3; flightControl_B.b_k++)
    {
      /* Product: '<S3>/Product' */
      for (i_0 = 0; i_0 < 4; i_0++) {
        flightControl_B.Product[flightControl_B.b_k + 3 * i_0] = 0.0F;
        flightControl_B.Product[flightControl_B.b_k + 3 * i_0] +=
          flightControl_B.MatrixConcatenate1[3 * i_0] *
          flightControl_B.c[flightControl_B.b_k];
        flightControl_B.Product[flightControl_B.b_k + 3 * i_0] +=
          flightControl_B.MatrixConcatenate1[3 * i_0 + 1] *
          flightControl_B.c[flightControl_B.b_k + 3];
        flightControl_B.Product[flightControl_B.b_k + 3 * i_0] +=
          flightControl_B.MatrixConcatenate1[3 * i_0 + 2] *
          flightControl_B.c[flightControl_B.b_k + 6];
      }

      /* End of Product: '<S3>/Product' */

      /* Selector: '<S3>/Selector1' */
      flightControl_B.Selector1[flightControl_B.b_k] = flightControl_B.cal[9 +
        flightControl_B.b_k];

      /* Selector: '<S3>/Selector2' */
      flightControl_B.Selector2[flightControl_B.b_k] =
        flightControl_B.MatrixConcatenate[3 + flightControl_B.b_k];
    }

    /*  */
    /*  Q2B converts a quaternion (q) to a Bortz vector (b). */
    /*  */
    /*   usage: b=q2b(q) */
    /*  */
    /*      q = qnb */
    /*  */
    /*      where q(1)   = scalar part */
    /*            q(2-4) = vector part */
    /*  */
    /* MATLAB Function 'translateIMUToWorld/q2bortz': '<S6>:1' */
    /* '<S6>:1:12' b=single(zeros(3,1)); */
    /*  */
    /* '<S6>:1:14' if (q(1) < 0.0) */
    /*  */
    /* '<S6>:1:18' qs=q(1); */
    /* '<S6>:1:19' qv=[q(2);q(3);q(4)]; */
    /*  */
    /* '<S6>:1:21' theta=2*acos(qs); */
    /*  */
    /* '<S6>:1:23' if (theta > 1.0e-20) */
    srUpdateBC(flightControl_DW.runSensorFusion_SubsysRanBC);
  } else {
    if (flightControl_DW.runSensorFusion_MODE) {
      flightControl_DW.runSensorFusion_MODE = false;
    }
  }

  /* End of RelationalOperator: '<S1>/Compare' */
  /* End of Outputs for SubSystem: '<Root>/runSensorFusion' */

  /* External mode */
  rtExtModeUploadCheckTrigger(1);

  {                                    /* Sample time: [0.001s, 0.0s] */
    rtExtModeUpload(0, flightControl_M->Timing.taskTime0);
  }

  /* signal main to stop simulation */
  {                                    /* Sample time: [0.001s, 0.0s] */
    if ((rtmGetTFinal(flightControl_M)!=-1) &&
        !((rtmGetTFinal(flightControl_M)-flightControl_M->Timing.taskTime0) >
          flightControl_M->Timing.taskTime0 * (DBL_EPSILON))) {
      rtmSetErrorStatus(flightControl_M, "Simulation finished");
    }

    if (rtmGetStopRequested(flightControl_M)) {
      rtmSetErrorStatus(flightControl_M, "Simulation finished");
    }
  }

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   */
  flightControl_M->Timing.taskTime0 =
    (++flightControl_M->Timing.clockTick0) * flightControl_M->Timing.stepSize0;
}

/* Model initialize function */
void flightControl_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)flightControl_M, 0,
                sizeof(RT_MODEL_flightControl_T));
  rtmSetTFinal(flightControl_M, -1);
  flightControl_M->Timing.stepSize0 = 0.001;

  /* External mode info */
  flightControl_M->Sizes.checksums[0] = (3343001048U);
  flightControl_M->Sizes.checksums[1] = (732597992U);
  flightControl_M->Sizes.checksums[2] = (3044550061U);
  flightControl_M->Sizes.checksums[3] = (1553496238U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[7];
    flightControl_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    systemRan[1] = (sysRanDType *)&flightControl_DW.runSensorFusion_SubsysRanBC;
    systemRan[2] = (sysRanDType *)&flightControl_DW.runSensorFusion_SubsysRanBC;
    systemRan[3] = (sysRanDType *)&flightControl_DW.runSensorFusion_SubsysRanBC;
    systemRan[4] = (sysRanDType *)&flightControl_DW.runSensorFusion_SubsysRanBC;
    systemRan[5] = (sysRanDType *)&flightControl_DW.runSensorFusion_SubsysRanBC;
    systemRan[6] = (sysRanDType *)&flightControl_DW.runSensorFusion_SubsysRanBC;
    rteiSetModelMappingInfoPtr(flightControl_M->extModeInfo,
      &flightControl_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(flightControl_M->extModeInfo,
                        flightControl_M->Sizes.checksums);
    rteiSetTPtr(flightControl_M->extModeInfo, rtmGetTPtr(flightControl_M));
  }

  /* block I/O */
  (void) memset(((void *) &flightControl_B), 0,
                sizeof(B_flightControl_T));

  /* states (dwork) */
  (void) memset((void *)&flightControl_DW, 0,
                sizeof(DW_flightControl_T));

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    flightControl_M->SpecialInfo.mappingInfo = (&dtInfo);
    dtInfo.numDataTypes = 14;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.BTransTable = &rtBTransTable;

    /* Parameters transition table */
    dtInfo.PTransTable = &rtPTransTable;
  }

  {
    char_T *sErr;
    int32_T i;

    /* Start for S-Function (sdspFromNetwork): '<Root>/UDP Receive' */
    sErr = GetErrorBuffer(&flightControl_DW.UDPReceive_NetworkLib[0U]);
    CreateUDPInterface(&flightControl_DW.UDPReceive_NetworkLib[0U]);
    if (*sErr == 0) {
      LibCreate_Network(&flightControl_DW.UDPReceive_NetworkLib[0U], 0,
                        "0.0.0.0", 25000, "0.0.0.0", -1, 8192, 4, 0);
    }

    if (*sErr == 0) {
      LibStart(&flightControl_DW.UDPReceive_NetworkLib[0U]);
    }

    if (*sErr != 0) {
      DestroyUDPInterface(&flightControl_DW.UDPReceive_NetworkLib[0U]);
      if (*sErr != 0) {
        rtmSetErrorStatus(flightControl_M, sErr);
        rtmSetStopRequested(flightControl_M, 1);
      }
    }

    /* End of Start for S-Function (sdspFromNetwork): '<Root>/UDP Receive' */

    /* SystemInitialize for Enabled SubSystem: '<Root>/runSensorFusion' */
    /* SystemInitialize for MATLAB Function: '<S5>/calibrate' */
    /* '<S10>:1:6' count=uint32(1); */
    flightControl_DW.count = 1U;

    /* '<S10>:1:7' bias=single(zeros(3,1)); */
    flightControl_DW.bias[0] = 0.0F;
    flightControl_DW.bias[1] = 0.0F;
    flightControl_DW.bias[2] = 0.0F;

    /* SystemInitialize for MATLAB Function: '<S3>/runMahonyUpdate' */
    flightControl_DW.qLocal[0] = 1.0F;
    flightControl_DW.qLocal[1] = 0.0F;
    flightControl_DW.qLocal[2] = 0.0F;
    flightControl_DW.qLocal[3] = 0.0F;

    /* '<S9>:1:4' qLocal=single([1 0 0 0]'); */
    /* '<S9>:1:5' counter=0; */
    flightControl_DW.counter = 0.0;

    /* SystemInitialize for Outport: '<S2>/accel_w' */
    for (i = 0; i < 12; i++) {
      flightControl_B.Product[i] = flightControl_P.accel_w_Y0;
    }

    /* End of SystemInitialize for Outport: '<S2>/accel_w' */
    /* End of SystemInitialize for SubSystem: '<Root>/runSensorFusion' */
  }
}

/* Model terminate function */
void flightControl_terminate(void)
{
  char_T *sErr;

  /* Terminate for S-Function (sdspFromNetwork): '<Root>/UDP Receive' */
  sErr = GetErrorBuffer(&flightControl_DW.UDPReceive_NetworkLib[0U]);
  LibTerminate(&flightControl_DW.UDPReceive_NetworkLib[0U]);
  if (*sErr != 0) {
    rtmSetErrorStatus(flightControl_M, sErr);
    rtmSetStopRequested(flightControl_M, 1);
  }

  LibDestroy(&flightControl_DW.UDPReceive_NetworkLib[0U], 0);
  DestroyUDPInterface(&flightControl_DW.UDPReceive_NetworkLib[0U]);

  /* End of Terminate for S-Function (sdspFromNetwork): '<Root>/UDP Receive' */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
