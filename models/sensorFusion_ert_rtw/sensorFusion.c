/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: sensorFusion.c
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
#include "sensorFusion_dt.h"

/* Block signals (auto storage) */
B_sensorFusion_T sensorFusion_B;

/* Block states (auto storage) */
DW_sensorFusion_T sensorFusion_DW;

/* Previous zero-crossings (trigger) states */
PrevZCX_sensorFusion_T sensorFusion_PrevZCX;

/* Real-time model */
RT_MODEL_sensorFusion_T sensorFusion_M_;
RT_MODEL_sensorFusion_T *const sensorFusion_M = &sensorFusion_M_;

/* Forward declaration for local functions */
static real32_T sensorFusion_rt_hypotf_snf(real32_T u0, real32_T u1);
static real32_T sensorFusion_rt_powf_snf(real32_T u0, real32_T u1);
static void sensorFusion_mldivide(const creal32_T A[16], creal32_T B[16]);
static void sensorF_PadeApproximantOfDegree(const creal32_T A[16], uint8_T m,
  creal32_T F[16]);
static void sensorFusion_expm(creal32_T A[16], creal32_T F[16]);
static real32_T sensorFusion_norm(const creal32_T x[4]);
static void sensorFusion_getC(const creal32_T q[4], creal32_T C[9]);
static void sensorFusion_mrdivide(creal32_T A[24], const creal32_T B[36]);
static real32_T sensorFusion_eps(const creal32_T x);
static void sensorFusion_measurementFcn(const creal32_T x[4], const real_T g[3],
  const real_T h[3], creal32_T zNew[6]);
static void sensorFusion_stateUpdateFcn(real_T Ts, const creal32_T x[4], const
  real32_T w[3], boolean_T doJacobian, creal32_T xNew[4]);
real32_T uMultiWordSingle(const uint32_T u1[], int32_T n1, int32_T e1)
{
  real32_T y;
  int32_T i;
  int32_T exp_0;
  y = 0.0F;
  exp_0 = e1;
  for (i = 0; i < n1; i++) {
    y += (real32_T)ldexp((real32_T)u1[i], exp_0);
    exp_0 += 32;
  }

  return y;
}

void uMultiWordMul(const uint32_T u1[], int32_T n1, const uint32_T u2[], int32_T
                   n2, uint32_T y[], int32_T n)
{
  int32_T i;
  int32_T j;
  int32_T k;
  int32_T nj;
  uint32_T u1i;
  uint32_T yk;
  uint32_T a1;
  uint32_T a0;
  uint32_T b1;
  uint32_T w10;
  uint32_T w01;
  uint32_T cb;

  /* Initialize output to zero */
  for (k = 0; k < n; k++) {
    y[k] = 0U;
  }

  for (i = 0; i < n1; i++) {
    cb = 0U;
    u1i = u1[i];
    a1 = u1i >> 16U;
    a0 = u1i & 65535U;
    k = n - i;
    nj = n2 <= k ? n2 : k;
    k = i;
    for (j = 0; j < nj; j++) {
      yk = y[k];
      u1i = u2[j];
      b1 = u1i >> 16U;
      u1i &= 65535U;
      w10 = a1 * u1i;
      w01 = a0 * b1;
      yk += cb;
      cb = (uint32_T)(yk < cb);
      u1i *= a0;
      yk += u1i;
      cb += (yk < u1i);
      u1i = w10 << 16U;
      yk += u1i;
      cb += (yk < u1i);
      u1i = w01 << 16U;
      yk += u1i;
      cb += (yk < u1i);
      y[k] = yk;
      cb += w10 >> 16U;
      cb += w01 >> 16U;
      cb += a1 * b1;
      k++;
    }

    if (k < n) {
      y[k] = cb;
    }
  }
}

static real32_T sensorFusion_rt_hypotf_snf(real32_T u0, real32_T u1)
{
  real32_T y;
  sensorFusion_B.a = (real32_T)fabs(u0);
  y = (real32_T)fabs(u1);
  if (sensorFusion_B.a < y) {
    sensorFusion_B.a /= y;
    y *= (real32_T)sqrt(sensorFusion_B.a * sensorFusion_B.a + 1.0F);
  } else if (sensorFusion_B.a > y) {
    y /= sensorFusion_B.a;
    y = (real32_T)sqrt(y * y + 1.0F) * sensorFusion_B.a;
  } else {
    if (!rtIsNaNF(y)) {
      y = sensorFusion_B.a * 1.41421354F;
    }
  }

  return y;
}

static real32_T sensorFusion_rt_powf_snf(real32_T u0, real32_T u1)
{
  real32_T y;
  if (rtIsNaNF(u0) || rtIsNaNF(u1)) {
    y = (rtNaNF);
  } else {
    sensorFusion_B.f0 = (real32_T)fabs(u0);
    sensorFusion_B.f1 = (real32_T)fabs(u1);
    if (rtIsInfF(u1)) {
      if (sensorFusion_B.f0 == 1.0F) {
        y = (rtNaNF);
      } else if (sensorFusion_B.f0 > 1.0F) {
        if (u1 > 0.0F) {
          y = (rtInfF);
        } else {
          y = 0.0F;
        }
      } else if (u1 > 0.0F) {
        y = 0.0F;
      } else {
        y = (rtInfF);
      }
    } else if (sensorFusion_B.f1 == 0.0F) {
      y = 1.0F;
    } else if (sensorFusion_B.f1 == 1.0F) {
      if (u1 > 0.0F) {
        y = u0;
      } else {
        y = 1.0F / u0;
      }
    } else if (u1 == 2.0F) {
      y = u0 * u0;
    } else if ((u1 == 0.5F) && (u0 >= 0.0F)) {
      y = (real32_T)sqrt(u0);
    } else if ((u0 < 0.0F) && (u1 > (real32_T)floor(u1))) {
      y = (rtNaNF);
    } else {
      y = (real32_T)pow(u0, u1);
    }
  }

  return y;
}

/* Function for MATLAB Function: '<S3>/MATLAB Function' */
static void sensorFusion_mldivide(const creal32_T A[16], creal32_T B[16])
{
  memcpy(&sensorFusion_B.b_A[0], &A[0], sizeof(creal32_T) << 4U);
  sensorFusion_B.ipiv[0] = 1;
  sensorFusion_B.ipiv[1] = 2;
  sensorFusion_B.ipiv[2] = 3;
  sensorFusion_B.ipiv[3] = 4;
  for (sensorFusion_B.j = 0; sensorFusion_B.j < 3; sensorFusion_B.j++) {
    sensorFusion_B.b_jBcol = sensorFusion_B.j * 5;
    sensorFusion_B.iy = 0;
    sensorFusion_B.b_kAcol = sensorFusion_B.b_jBcol;
    sensorFusion_B.temp_re = (real32_T)fabs
      (sensorFusion_B.b_A[sensorFusion_B.b_jBcol].re) + (real32_T)fabs
      (sensorFusion_B.b_A[sensorFusion_B.b_jBcol].im);
    sensorFusion_B.c_i = 2;
    while (sensorFusion_B.c_i <= 4 - sensorFusion_B.j) {
      sensorFusion_B.b_kAcol++;
      sensorFusion_B.brm = (real32_T)fabs
        (sensorFusion_B.b_A[sensorFusion_B.b_kAcol].re) + (real32_T)fabs
        (sensorFusion_B.b_A[sensorFusion_B.b_kAcol].im);
      if (sensorFusion_B.brm > sensorFusion_B.temp_re) {
        sensorFusion_B.iy = sensorFusion_B.c_i - 1;
        sensorFusion_B.temp_re = sensorFusion_B.brm;
      }

      sensorFusion_B.c_i++;
    }

    if ((sensorFusion_B.b_A[sensorFusion_B.b_jBcol + sensorFusion_B.iy].re !=
         0.0F) || (sensorFusion_B.b_A[sensorFusion_B.b_jBcol + sensorFusion_B.iy]
                   .im != 0.0F)) {
      if (sensorFusion_B.iy != 0) {
        sensorFusion_B.ipiv[sensorFusion_B.j] = (int8_T)((sensorFusion_B.j +
          sensorFusion_B.iy) + 1);
        sensorFusion_B.iy += sensorFusion_B.j;
        sensorFusion_B.temp_re = sensorFusion_B.b_A[sensorFusion_B.j].re;
        sensorFusion_B.temp_im = sensorFusion_B.b_A[sensorFusion_B.j].im;
        sensorFusion_B.b_A[sensorFusion_B.j] =
          sensorFusion_B.b_A[sensorFusion_B.iy];
        sensorFusion_B.b_A[sensorFusion_B.iy].re = sensorFusion_B.temp_re;
        sensorFusion_B.b_A[sensorFusion_B.iy].im = sensorFusion_B.temp_im;
        sensorFusion_B.b_kAcol = sensorFusion_B.j + 4;
        sensorFusion_B.iy += 4;
        sensorFusion_B.temp_re = sensorFusion_B.b_A[sensorFusion_B.b_kAcol].re;
        sensorFusion_B.temp_im = sensorFusion_B.b_A[sensorFusion_B.b_kAcol].im;
        sensorFusion_B.b_A[sensorFusion_B.b_kAcol] =
          sensorFusion_B.b_A[sensorFusion_B.iy];
        sensorFusion_B.b_A[sensorFusion_B.iy].re = sensorFusion_B.temp_re;
        sensorFusion_B.b_A[sensorFusion_B.iy].im = sensorFusion_B.temp_im;
        sensorFusion_B.b_kAcol += 4;
        sensorFusion_B.iy += 4;
        sensorFusion_B.temp_re = sensorFusion_B.b_A[sensorFusion_B.b_kAcol].re;
        sensorFusion_B.temp_im = sensorFusion_B.b_A[sensorFusion_B.b_kAcol].im;
        sensorFusion_B.b_A[sensorFusion_B.b_kAcol] =
          sensorFusion_B.b_A[sensorFusion_B.iy];
        sensorFusion_B.b_A[sensorFusion_B.iy].re = sensorFusion_B.temp_re;
        sensorFusion_B.b_A[sensorFusion_B.iy].im = sensorFusion_B.temp_im;
        sensorFusion_B.b_kAcol += 4;
        sensorFusion_B.iy += 4;
        sensorFusion_B.temp_re = sensorFusion_B.b_A[sensorFusion_B.b_kAcol].re;
        sensorFusion_B.temp_im = sensorFusion_B.b_A[sensorFusion_B.b_kAcol].im;
        sensorFusion_B.b_A[sensorFusion_B.b_kAcol] =
          sensorFusion_B.b_A[sensorFusion_B.iy];
        sensorFusion_B.b_A[sensorFusion_B.iy].re = sensorFusion_B.temp_re;
        sensorFusion_B.b_A[sensorFusion_B.iy].im = sensorFusion_B.temp_im;
      }

      sensorFusion_B.iy = (sensorFusion_B.b_jBcol - sensorFusion_B.j) + 4;
      sensorFusion_B.b_kAcol = sensorFusion_B.b_jBcol + 1;
      while (sensorFusion_B.b_kAcol + 1 <= sensorFusion_B.iy) {
        sensorFusion_B.temp_re = sensorFusion_B.b_A[sensorFusion_B.b_kAcol].re;
        sensorFusion_B.temp_im = sensorFusion_B.b_A[sensorFusion_B.b_jBcol].re;
        if (sensorFusion_B.b_A[sensorFusion_B.b_jBcol].im == 0.0F) {
          if (sensorFusion_B.b_A[sensorFusion_B.b_kAcol].im == 0.0F) {
            sensorFusion_B.b_A[sensorFusion_B.b_kAcol].re /=
              sensorFusion_B.b_A[sensorFusion_B.b_jBcol].re;
            sensorFusion_B.b_A[sensorFusion_B.b_kAcol].im = 0.0F;
          } else if (sensorFusion_B.b_A[sensorFusion_B.b_kAcol].re == 0.0F) {
            sensorFusion_B.b_A[sensorFusion_B.b_kAcol].re = 0.0F;
            sensorFusion_B.b_A[sensorFusion_B.b_kAcol].im /=
              sensorFusion_B.temp_im;
          } else {
            sensorFusion_B.b_A[sensorFusion_B.b_kAcol].re /=
              sensorFusion_B.b_A[sensorFusion_B.b_jBcol].re;
            sensorFusion_B.b_A[sensorFusion_B.b_kAcol].im /=
              sensorFusion_B.temp_im;
          }
        } else if (sensorFusion_B.b_A[sensorFusion_B.b_jBcol].re == 0.0F) {
          if (sensorFusion_B.b_A[sensorFusion_B.b_kAcol].re == 0.0F) {
            sensorFusion_B.b_A[sensorFusion_B.b_kAcol].re =
              sensorFusion_B.b_A[sensorFusion_B.b_kAcol].im /
              sensorFusion_B.b_A[sensorFusion_B.b_jBcol].im;
            sensorFusion_B.b_A[sensorFusion_B.b_kAcol].im = 0.0F;
          } else if (sensorFusion_B.b_A[sensorFusion_B.b_kAcol].im == 0.0F) {
            sensorFusion_B.b_A[sensorFusion_B.b_kAcol].re = 0.0F;
            sensorFusion_B.b_A[sensorFusion_B.b_kAcol].im =
              -(sensorFusion_B.temp_re /
                sensorFusion_B.b_A[sensorFusion_B.b_jBcol].im);
          } else {
            sensorFusion_B.b_A[sensorFusion_B.b_kAcol].re =
              sensorFusion_B.b_A[sensorFusion_B.b_kAcol].im /
              sensorFusion_B.b_A[sensorFusion_B.b_jBcol].im;
            sensorFusion_B.b_A[sensorFusion_B.b_kAcol].im =
              -(sensorFusion_B.temp_re /
                sensorFusion_B.b_A[sensorFusion_B.b_jBcol].im);
          }
        } else {
          sensorFusion_B.brm = (real32_T)fabs
            (sensorFusion_B.b_A[sensorFusion_B.b_jBcol].re);
          sensorFusion_B.bim = (real32_T)fabs
            (sensorFusion_B.b_A[sensorFusion_B.b_jBcol].im);
          if (sensorFusion_B.brm > sensorFusion_B.bim) {
            sensorFusion_B.brm = sensorFusion_B.b_A[sensorFusion_B.b_jBcol].im /
              sensorFusion_B.b_A[sensorFusion_B.b_jBcol].re;
            sensorFusion_B.bim = sensorFusion_B.brm *
              sensorFusion_B.b_A[sensorFusion_B.b_jBcol].im +
              sensorFusion_B.b_A[sensorFusion_B.b_jBcol].re;
            sensorFusion_B.b_A[sensorFusion_B.b_kAcol].re = (sensorFusion_B.brm *
              sensorFusion_B.b_A[sensorFusion_B.b_kAcol].im +
              sensorFusion_B.b_A[sensorFusion_B.b_kAcol].re) /
              sensorFusion_B.bim;
            sensorFusion_B.b_A[sensorFusion_B.b_kAcol].im =
              (sensorFusion_B.b_A[sensorFusion_B.b_kAcol].im -
               sensorFusion_B.brm * sensorFusion_B.temp_re) / sensorFusion_B.bim;
          } else if (sensorFusion_B.bim == sensorFusion_B.brm) {
            sensorFusion_B.bim = sensorFusion_B.b_A[sensorFusion_B.b_jBcol].re >
              0.0F ? 0.5F : -0.5F;
            sensorFusion_B.sgnbi = sensorFusion_B.b_A[sensorFusion_B.b_jBcol].im
              > 0.0F ? 0.5F : -0.5F;
            sensorFusion_B.b_A[sensorFusion_B.b_kAcol].re =
              (sensorFusion_B.b_A[sensorFusion_B.b_kAcol].re *
               sensorFusion_B.bim + sensorFusion_B.b_A[sensorFusion_B.b_kAcol].
               im * sensorFusion_B.sgnbi) / sensorFusion_B.brm;
            sensorFusion_B.b_A[sensorFusion_B.b_kAcol].im =
              (sensorFusion_B.b_A[sensorFusion_B.b_kAcol].im *
               sensorFusion_B.bim - sensorFusion_B.temp_re *
               sensorFusion_B.sgnbi) / sensorFusion_B.brm;
          } else {
            sensorFusion_B.brm = sensorFusion_B.b_A[sensorFusion_B.b_jBcol].re /
              sensorFusion_B.b_A[sensorFusion_B.b_jBcol].im;
            sensorFusion_B.bim = sensorFusion_B.brm *
              sensorFusion_B.b_A[sensorFusion_B.b_jBcol].re +
              sensorFusion_B.b_A[sensorFusion_B.b_jBcol].im;
            sensorFusion_B.b_A[sensorFusion_B.b_kAcol].re = (sensorFusion_B.brm *
              sensorFusion_B.b_A[sensorFusion_B.b_kAcol].re +
              sensorFusion_B.b_A[sensorFusion_B.b_kAcol].im) /
              sensorFusion_B.bim;
            sensorFusion_B.b_A[sensorFusion_B.b_kAcol].im = (sensorFusion_B.brm *
              sensorFusion_B.b_A[sensorFusion_B.b_kAcol].im -
              sensorFusion_B.temp_re) / sensorFusion_B.bim;
          }
        }

        sensorFusion_B.b_kAcol++;
      }
    }

    sensorFusion_B.iy = sensorFusion_B.b_jBcol;
    sensorFusion_B.b_kAcol = sensorFusion_B.b_jBcol + 4;
    sensorFusion_B.c_i = 1;
    while (sensorFusion_B.c_i <= 3 - sensorFusion_B.j) {
      if ((sensorFusion_B.b_A[sensorFusion_B.b_kAcol].re != 0.0F) ||
          (sensorFusion_B.b_A[sensorFusion_B.b_kAcol].im != 0.0F)) {
        sensorFusion_B.temp_re = -sensorFusion_B.b_A[sensorFusion_B.b_kAcol].re
          - sensorFusion_B.b_A[sensorFusion_B.b_kAcol].im * 0.0F;
        sensorFusion_B.temp_im = sensorFusion_B.b_A[sensorFusion_B.b_kAcol].re *
          0.0F + -sensorFusion_B.b_A[sensorFusion_B.b_kAcol].im;
        sensorFusion_B.c_ix = sensorFusion_B.b_jBcol + 1;
        sensorFusion_B.d_n = (sensorFusion_B.iy - sensorFusion_B.j) + 8;
        sensorFusion_B.ijA = 5 + sensorFusion_B.iy;
        while (sensorFusion_B.ijA + 1 <= sensorFusion_B.d_n) {
          sensorFusion_B.brm = sensorFusion_B.b_A[sensorFusion_B.c_ix].re *
            sensorFusion_B.temp_im + sensorFusion_B.b_A[sensorFusion_B.c_ix].im *
            sensorFusion_B.temp_re;
          sensorFusion_B.b_A[sensorFusion_B.ijA].re +=
            sensorFusion_B.b_A[sensorFusion_B.c_ix].re * sensorFusion_B.temp_re
            - sensorFusion_B.b_A[sensorFusion_B.c_ix].im *
            sensorFusion_B.temp_im;
          sensorFusion_B.b_A[sensorFusion_B.ijA].im += sensorFusion_B.brm;
          sensorFusion_B.c_ix++;
          sensorFusion_B.ijA++;
        }
      }

      sensorFusion_B.b_kAcol += 4;
      sensorFusion_B.iy += 4;
      sensorFusion_B.c_i++;
    }
  }

  for (sensorFusion_B.j = 0; sensorFusion_B.j < 3; sensorFusion_B.j++) {
    if (sensorFusion_B.j + 1 != sensorFusion_B.ipiv[sensorFusion_B.j]) {
      sensorFusion_B.b_jBcol = sensorFusion_B.ipiv[sensorFusion_B.j] - 1;
      sensorFusion_B.temp_re = B[sensorFusion_B.j].re;
      sensorFusion_B.temp_im = B[sensorFusion_B.j].im;
      B[sensorFusion_B.j] = B[sensorFusion_B.b_jBcol];
      B[sensorFusion_B.b_jBcol].re = sensorFusion_B.temp_re;
      B[sensorFusion_B.b_jBcol].im = sensorFusion_B.temp_im;
      sensorFusion_B.temp_re = B[sensorFusion_B.j + 4].re;
      sensorFusion_B.temp_im = B[sensorFusion_B.j + 4].im;
      B[sensorFusion_B.j + 4] = B[sensorFusion_B.b_jBcol + 4];
      B[sensorFusion_B.b_jBcol + 4].re = sensorFusion_B.temp_re;
      B[sensorFusion_B.b_jBcol + 4].im = sensorFusion_B.temp_im;
      sensorFusion_B.temp_re = B[sensorFusion_B.j + 8].re;
      sensorFusion_B.temp_im = B[sensorFusion_B.j + 8].im;
      B[sensorFusion_B.j + 8] = B[sensorFusion_B.b_jBcol + 8];
      B[sensorFusion_B.b_jBcol + 8].re = sensorFusion_B.temp_re;
      B[sensorFusion_B.b_jBcol + 8].im = sensorFusion_B.temp_im;
      sensorFusion_B.temp_re = B[sensorFusion_B.j + 12].re;
      sensorFusion_B.temp_im = B[sensorFusion_B.j + 12].im;
      B[sensorFusion_B.j + 12] = B[sensorFusion_B.b_jBcol + 12];
      B[sensorFusion_B.b_jBcol + 12].re = sensorFusion_B.temp_re;
      B[sensorFusion_B.b_jBcol + 12].im = sensorFusion_B.temp_im;
    }
  }

  for (sensorFusion_B.j = 0; sensorFusion_B.j < 4; sensorFusion_B.j++) {
    sensorFusion_B.b_jBcol = sensorFusion_B.j << 2;
    if ((B[sensorFusion_B.b_jBcol].re != 0.0F) || (B[sensorFusion_B.b_jBcol].im
         != 0.0F)) {
      sensorFusion_B.c_i = 1;
      while (sensorFusion_B.c_i + 1 < 5) {
        sensorFusion_B.temp_im = B[sensorFusion_B.b_jBcol].re *
          sensorFusion_B.b_A[sensorFusion_B.c_i].im + B[sensorFusion_B.b_jBcol].
          im * sensorFusion_B.b_A[sensorFusion_B.c_i].re;
        B[sensorFusion_B.c_i + sensorFusion_B.b_jBcol].re -=
          B[sensorFusion_B.b_jBcol].re * sensorFusion_B.b_A[sensorFusion_B.c_i].
          re - B[sensorFusion_B.b_jBcol].im *
          sensorFusion_B.b_A[sensorFusion_B.c_i].im;
        B[sensorFusion_B.c_i + sensorFusion_B.b_jBcol].im -=
          sensorFusion_B.temp_im;
        sensorFusion_B.c_i++;
      }
    }

    if ((B[1 + sensorFusion_B.b_jBcol].re != 0.0F) || (B[1 +
         sensorFusion_B.b_jBcol].im != 0.0F)) {
      sensorFusion_B.c_i = 2;
      while (sensorFusion_B.c_i + 1 < 5) {
        sensorFusion_B.temp_im = B[1 + sensorFusion_B.b_jBcol].re *
          sensorFusion_B.b_A[sensorFusion_B.c_i + 4].im + B[1 +
          sensorFusion_B.b_jBcol].im * sensorFusion_B.b_A[sensorFusion_B.c_i + 4]
          .re;
        B[sensorFusion_B.c_i + sensorFusion_B.b_jBcol].re -= B[1 +
          sensorFusion_B.b_jBcol].re * sensorFusion_B.b_A[sensorFusion_B.c_i + 4]
          .re - B[1 + sensorFusion_B.b_jBcol].im *
          sensorFusion_B.b_A[sensorFusion_B.c_i + 4].im;
        B[sensorFusion_B.c_i + sensorFusion_B.b_jBcol].im -=
          sensorFusion_B.temp_im;
        sensorFusion_B.c_i++;
      }
    }

    if ((B[2 + sensorFusion_B.b_jBcol].re != 0.0F) || (B[2 +
         sensorFusion_B.b_jBcol].im != 0.0F)) {
      sensorFusion_B.c_i = 3;
      while (sensorFusion_B.c_i + 1 < 5) {
        sensorFusion_B.temp_im = B[2 + sensorFusion_B.b_jBcol].re *
          sensorFusion_B.b_A[sensorFusion_B.c_i + 8].im + B[2 +
          sensorFusion_B.b_jBcol].im * sensorFusion_B.b_A[sensorFusion_B.c_i + 8]
          .re;
        B[sensorFusion_B.c_i + sensorFusion_B.b_jBcol].re -= B[2 +
          sensorFusion_B.b_jBcol].re * sensorFusion_B.b_A[sensorFusion_B.c_i + 8]
          .re - B[2 + sensorFusion_B.b_jBcol].im *
          sensorFusion_B.b_A[sensorFusion_B.c_i + 8].im;
        B[sensorFusion_B.c_i + sensorFusion_B.b_jBcol].im -=
          sensorFusion_B.temp_im;
        sensorFusion_B.c_i++;
      }
    }
  }

  for (sensorFusion_B.j = 0; sensorFusion_B.j < 4; sensorFusion_B.j++) {
    sensorFusion_B.b_jBcol = sensorFusion_B.j << 2;
    if ((B[3 + sensorFusion_B.b_jBcol].re != 0.0F) || (B[3 +
         sensorFusion_B.b_jBcol].im != 0.0F)) {
      sensorFusion_B.temp_re = B[3 + sensorFusion_B.b_jBcol].re;
      sensorFusion_B.temp_im = B[3 + sensorFusion_B.b_jBcol].im;
      if (sensorFusion_B.b_A[15].im == 0.0F) {
        if (sensorFusion_B.temp_im == 0.0F) {
          B[3 + sensorFusion_B.b_jBcol].re = sensorFusion_B.temp_re /
            sensorFusion_B.b_A[15].re;
          B[3 + sensorFusion_B.b_jBcol].im = 0.0F;
        } else if (sensorFusion_B.temp_re == 0.0F) {
          B[3 + sensorFusion_B.b_jBcol].re = 0.0F;
          B[3 + sensorFusion_B.b_jBcol].im = sensorFusion_B.temp_im /
            sensorFusion_B.b_A[15].re;
        } else {
          B[3 + sensorFusion_B.b_jBcol].re = sensorFusion_B.temp_re /
            sensorFusion_B.b_A[15].re;
          B[3 + sensorFusion_B.b_jBcol].im = sensorFusion_B.temp_im /
            sensorFusion_B.b_A[15].re;
        }
      } else if (sensorFusion_B.b_A[15].re == 0.0F) {
        if (sensorFusion_B.temp_re == 0.0F) {
          B[3 + sensorFusion_B.b_jBcol].re = sensorFusion_B.temp_im /
            sensorFusion_B.b_A[15].im;
          B[3 + sensorFusion_B.b_jBcol].im = 0.0F;
        } else if (sensorFusion_B.temp_im == 0.0F) {
          B[3 + sensorFusion_B.b_jBcol].re = 0.0F;
          B[3 + sensorFusion_B.b_jBcol].im = -(sensorFusion_B.temp_re /
            sensorFusion_B.b_A[15].im);
        } else {
          B[3 + sensorFusion_B.b_jBcol].re = sensorFusion_B.temp_im /
            sensorFusion_B.b_A[15].im;
          B[3 + sensorFusion_B.b_jBcol].im = -(sensorFusion_B.temp_re /
            sensorFusion_B.b_A[15].im);
        }
      } else {
        sensorFusion_B.brm = (real32_T)fabs(sensorFusion_B.b_A[15].re);
        sensorFusion_B.bim = (real32_T)fabs(sensorFusion_B.b_A[15].im);
        if (sensorFusion_B.brm > sensorFusion_B.bim) {
          sensorFusion_B.brm = sensorFusion_B.b_A[15].im / sensorFusion_B.b_A[15]
            .re;
          sensorFusion_B.bim = sensorFusion_B.brm * sensorFusion_B.b_A[15].im +
            sensorFusion_B.b_A[15].re;
          B[3 + sensorFusion_B.b_jBcol].re = (sensorFusion_B.brm *
            sensorFusion_B.temp_im + sensorFusion_B.temp_re) /
            sensorFusion_B.bim;
          B[3 + sensorFusion_B.b_jBcol].im = (sensorFusion_B.temp_im -
            sensorFusion_B.brm * sensorFusion_B.temp_re) / sensorFusion_B.bim;
        } else if (sensorFusion_B.bim == sensorFusion_B.brm) {
          sensorFusion_B.bim = sensorFusion_B.b_A[15].re > 0.0F ? 0.5F : -0.5F;
          sensorFusion_B.sgnbi = sensorFusion_B.b_A[15].im > 0.0F ? 0.5F : -0.5F;
          B[3 + sensorFusion_B.b_jBcol].re = (sensorFusion_B.temp_re *
            sensorFusion_B.bim + sensorFusion_B.temp_im * sensorFusion_B.sgnbi) /
            sensorFusion_B.brm;
          B[3 + sensorFusion_B.b_jBcol].im = (sensorFusion_B.temp_im *
            sensorFusion_B.bim - sensorFusion_B.temp_re * sensorFusion_B.sgnbi) /
            sensorFusion_B.brm;
        } else {
          sensorFusion_B.brm = sensorFusion_B.b_A[15].re / sensorFusion_B.b_A[15]
            .im;
          sensorFusion_B.bim = sensorFusion_B.brm * sensorFusion_B.b_A[15].re +
            sensorFusion_B.b_A[15].im;
          B[3 + sensorFusion_B.b_jBcol].re = (sensorFusion_B.brm *
            sensorFusion_B.temp_re + sensorFusion_B.temp_im) /
            sensorFusion_B.bim;
          B[3 + sensorFusion_B.b_jBcol].im = (sensorFusion_B.brm *
            sensorFusion_B.temp_im - sensorFusion_B.temp_re) /
            sensorFusion_B.bim;
        }
      }

      sensorFusion_B.c_i = 0;
      while (sensorFusion_B.c_i + 1 <= 3) {
        sensorFusion_B.temp_im = B[3 + sensorFusion_B.b_jBcol].re *
          sensorFusion_B.b_A[sensorFusion_B.c_i + 12].im + B[3 +
          sensorFusion_B.b_jBcol].im * sensorFusion_B.b_A[sensorFusion_B.c_i +
          12].re;
        B[sensorFusion_B.c_i + sensorFusion_B.b_jBcol].re -= B[3 +
          sensorFusion_B.b_jBcol].re * sensorFusion_B.b_A[sensorFusion_B.c_i +
          12].re - B[3 + sensorFusion_B.b_jBcol].im *
          sensorFusion_B.b_A[sensorFusion_B.c_i + 12].im;
        B[sensorFusion_B.c_i + sensorFusion_B.b_jBcol].im -=
          sensorFusion_B.temp_im;
        sensorFusion_B.c_i++;
      }
    }

    if ((B[2 + sensorFusion_B.b_jBcol].re != 0.0F) || (B[2 +
         sensorFusion_B.b_jBcol].im != 0.0F)) {
      sensorFusion_B.temp_re = B[2 + sensorFusion_B.b_jBcol].re;
      sensorFusion_B.temp_im = B[2 + sensorFusion_B.b_jBcol].im;
      if (sensorFusion_B.b_A[10].im == 0.0F) {
        if (sensorFusion_B.temp_im == 0.0F) {
          B[2 + sensorFusion_B.b_jBcol].re = sensorFusion_B.temp_re /
            sensorFusion_B.b_A[10].re;
          B[2 + sensorFusion_B.b_jBcol].im = 0.0F;
        } else if (sensorFusion_B.temp_re == 0.0F) {
          B[2 + sensorFusion_B.b_jBcol].re = 0.0F;
          B[2 + sensorFusion_B.b_jBcol].im = sensorFusion_B.temp_im /
            sensorFusion_B.b_A[10].re;
        } else {
          B[2 + sensorFusion_B.b_jBcol].re = sensorFusion_B.temp_re /
            sensorFusion_B.b_A[10].re;
          B[2 + sensorFusion_B.b_jBcol].im = sensorFusion_B.temp_im /
            sensorFusion_B.b_A[10].re;
        }
      } else if (sensorFusion_B.b_A[10].re == 0.0F) {
        if (sensorFusion_B.temp_re == 0.0F) {
          B[2 + sensorFusion_B.b_jBcol].re = sensorFusion_B.temp_im /
            sensorFusion_B.b_A[10].im;
          B[2 + sensorFusion_B.b_jBcol].im = 0.0F;
        } else if (sensorFusion_B.temp_im == 0.0F) {
          B[2 + sensorFusion_B.b_jBcol].re = 0.0F;
          B[2 + sensorFusion_B.b_jBcol].im = -(sensorFusion_B.temp_re /
            sensorFusion_B.b_A[10].im);
        } else {
          B[2 + sensorFusion_B.b_jBcol].re = sensorFusion_B.temp_im /
            sensorFusion_B.b_A[10].im;
          B[2 + sensorFusion_B.b_jBcol].im = -(sensorFusion_B.temp_re /
            sensorFusion_B.b_A[10].im);
        }
      } else {
        sensorFusion_B.brm = (real32_T)fabs(sensorFusion_B.b_A[10].re);
        sensorFusion_B.bim = (real32_T)fabs(sensorFusion_B.b_A[10].im);
        if (sensorFusion_B.brm > sensorFusion_B.bim) {
          sensorFusion_B.brm = sensorFusion_B.b_A[10].im / sensorFusion_B.b_A[10]
            .re;
          sensorFusion_B.bim = sensorFusion_B.brm * sensorFusion_B.b_A[10].im +
            sensorFusion_B.b_A[10].re;
          B[2 + sensorFusion_B.b_jBcol].re = (sensorFusion_B.brm *
            sensorFusion_B.temp_im + sensorFusion_B.temp_re) /
            sensorFusion_B.bim;
          B[2 + sensorFusion_B.b_jBcol].im = (sensorFusion_B.temp_im -
            sensorFusion_B.brm * sensorFusion_B.temp_re) / sensorFusion_B.bim;
        } else if (sensorFusion_B.bim == sensorFusion_B.brm) {
          sensorFusion_B.bim = sensorFusion_B.b_A[10].re > 0.0F ? 0.5F : -0.5F;
          sensorFusion_B.sgnbi = sensorFusion_B.b_A[10].im > 0.0F ? 0.5F : -0.5F;
          B[2 + sensorFusion_B.b_jBcol].re = (sensorFusion_B.temp_re *
            sensorFusion_B.bim + sensorFusion_B.temp_im * sensorFusion_B.sgnbi) /
            sensorFusion_B.brm;
          B[2 + sensorFusion_B.b_jBcol].im = (sensorFusion_B.temp_im *
            sensorFusion_B.bim - sensorFusion_B.temp_re * sensorFusion_B.sgnbi) /
            sensorFusion_B.brm;
        } else {
          sensorFusion_B.brm = sensorFusion_B.b_A[10].re / sensorFusion_B.b_A[10]
            .im;
          sensorFusion_B.bim = sensorFusion_B.brm * sensorFusion_B.b_A[10].re +
            sensorFusion_B.b_A[10].im;
          B[2 + sensorFusion_B.b_jBcol].re = (sensorFusion_B.brm *
            sensorFusion_B.temp_re + sensorFusion_B.temp_im) /
            sensorFusion_B.bim;
          B[2 + sensorFusion_B.b_jBcol].im = (sensorFusion_B.brm *
            sensorFusion_B.temp_im - sensorFusion_B.temp_re) /
            sensorFusion_B.bim;
        }
      }

      sensorFusion_B.c_i = 0;
      while (sensorFusion_B.c_i + 1 <= 2) {
        sensorFusion_B.temp_im = B[2 + sensorFusion_B.b_jBcol].re *
          sensorFusion_B.b_A[sensorFusion_B.c_i + 8].im + B[2 +
          sensorFusion_B.b_jBcol].im * sensorFusion_B.b_A[sensorFusion_B.c_i + 8]
          .re;
        B[sensorFusion_B.c_i + sensorFusion_B.b_jBcol].re -= B[2 +
          sensorFusion_B.b_jBcol].re * sensorFusion_B.b_A[sensorFusion_B.c_i + 8]
          .re - B[2 + sensorFusion_B.b_jBcol].im *
          sensorFusion_B.b_A[sensorFusion_B.c_i + 8].im;
        B[sensorFusion_B.c_i + sensorFusion_B.b_jBcol].im -=
          sensorFusion_B.temp_im;
        sensorFusion_B.c_i++;
      }
    }

    if ((B[1 + sensorFusion_B.b_jBcol].re != 0.0F) || (B[1 +
         sensorFusion_B.b_jBcol].im != 0.0F)) {
      sensorFusion_B.temp_re = B[1 + sensorFusion_B.b_jBcol].re;
      sensorFusion_B.temp_im = B[1 + sensorFusion_B.b_jBcol].im;
      if (sensorFusion_B.b_A[5].im == 0.0F) {
        if (sensorFusion_B.temp_im == 0.0F) {
          B[1 + sensorFusion_B.b_jBcol].re = sensorFusion_B.temp_re /
            sensorFusion_B.b_A[5].re;
          B[1 + sensorFusion_B.b_jBcol].im = 0.0F;
        } else if (sensorFusion_B.temp_re == 0.0F) {
          B[1 + sensorFusion_B.b_jBcol].re = 0.0F;
          B[1 + sensorFusion_B.b_jBcol].im = sensorFusion_B.temp_im /
            sensorFusion_B.b_A[5].re;
        } else {
          B[1 + sensorFusion_B.b_jBcol].re = sensorFusion_B.temp_re /
            sensorFusion_B.b_A[5].re;
          B[1 + sensorFusion_B.b_jBcol].im = sensorFusion_B.temp_im /
            sensorFusion_B.b_A[5].re;
        }
      } else if (sensorFusion_B.b_A[5].re == 0.0F) {
        if (sensorFusion_B.temp_re == 0.0F) {
          B[1 + sensorFusion_B.b_jBcol].re = sensorFusion_B.temp_im /
            sensorFusion_B.b_A[5].im;
          B[1 + sensorFusion_B.b_jBcol].im = 0.0F;
        } else if (sensorFusion_B.temp_im == 0.0F) {
          B[1 + sensorFusion_B.b_jBcol].re = 0.0F;
          B[1 + sensorFusion_B.b_jBcol].im = -(sensorFusion_B.temp_re /
            sensorFusion_B.b_A[5].im);
        } else {
          B[1 + sensorFusion_B.b_jBcol].re = sensorFusion_B.temp_im /
            sensorFusion_B.b_A[5].im;
          B[1 + sensorFusion_B.b_jBcol].im = -(sensorFusion_B.temp_re /
            sensorFusion_B.b_A[5].im);
        }
      } else {
        sensorFusion_B.brm = (real32_T)fabs(sensorFusion_B.b_A[5].re);
        sensorFusion_B.bim = (real32_T)fabs(sensorFusion_B.b_A[5].im);
        if (sensorFusion_B.brm > sensorFusion_B.bim) {
          sensorFusion_B.brm = sensorFusion_B.b_A[5].im / sensorFusion_B.b_A[5].
            re;
          sensorFusion_B.bim = sensorFusion_B.brm * sensorFusion_B.b_A[5].im +
            sensorFusion_B.b_A[5].re;
          B[1 + sensorFusion_B.b_jBcol].re = (sensorFusion_B.brm *
            sensorFusion_B.temp_im + sensorFusion_B.temp_re) /
            sensorFusion_B.bim;
          B[1 + sensorFusion_B.b_jBcol].im = (sensorFusion_B.temp_im -
            sensorFusion_B.brm * sensorFusion_B.temp_re) / sensorFusion_B.bim;
        } else if (sensorFusion_B.bim == sensorFusion_B.brm) {
          sensorFusion_B.bim = sensorFusion_B.b_A[5].re > 0.0F ? 0.5F : -0.5F;
          sensorFusion_B.sgnbi = sensorFusion_B.b_A[5].im > 0.0F ? 0.5F : -0.5F;
          B[1 + sensorFusion_B.b_jBcol].re = (sensorFusion_B.temp_re *
            sensorFusion_B.bim + sensorFusion_B.temp_im * sensorFusion_B.sgnbi) /
            sensorFusion_B.brm;
          B[1 + sensorFusion_B.b_jBcol].im = (sensorFusion_B.temp_im *
            sensorFusion_B.bim - sensorFusion_B.temp_re * sensorFusion_B.sgnbi) /
            sensorFusion_B.brm;
        } else {
          sensorFusion_B.brm = sensorFusion_B.b_A[5].re / sensorFusion_B.b_A[5].
            im;
          sensorFusion_B.bim = sensorFusion_B.brm * sensorFusion_B.b_A[5].re +
            sensorFusion_B.b_A[5].im;
          B[1 + sensorFusion_B.b_jBcol].re = (sensorFusion_B.brm *
            sensorFusion_B.temp_re + sensorFusion_B.temp_im) /
            sensorFusion_B.bim;
          B[1 + sensorFusion_B.b_jBcol].im = (sensorFusion_B.brm *
            sensorFusion_B.temp_im - sensorFusion_B.temp_re) /
            sensorFusion_B.bim;
        }
      }

      sensorFusion_B.c_i = 0;
      while (sensorFusion_B.c_i + 1 <= 1) {
        sensorFusion_B.temp_im = B[1 + sensorFusion_B.b_jBcol].re *
          sensorFusion_B.b_A[sensorFusion_B.c_i + 4].im + B[1 +
          sensorFusion_B.b_jBcol].im * sensorFusion_B.b_A[sensorFusion_B.c_i + 4]
          .re;
        B[sensorFusion_B.c_i + sensorFusion_B.b_jBcol].re -= B[1 +
          sensorFusion_B.b_jBcol].re * sensorFusion_B.b_A[sensorFusion_B.c_i + 4]
          .re - B[1 + sensorFusion_B.b_jBcol].im *
          sensorFusion_B.b_A[sensorFusion_B.c_i + 4].im;
        B[sensorFusion_B.c_i + sensorFusion_B.b_jBcol].im -=
          sensorFusion_B.temp_im;
        sensorFusion_B.c_i++;
      }
    }

    if ((B[sensorFusion_B.b_jBcol].re != 0.0F) || (B[sensorFusion_B.b_jBcol].im
         != 0.0F)) {
      sensorFusion_B.temp_re = B[sensorFusion_B.b_jBcol].re;
      sensorFusion_B.temp_im = B[sensorFusion_B.b_jBcol].im;
      if (sensorFusion_B.b_A[0].im == 0.0F) {
        if (sensorFusion_B.temp_im == 0.0F) {
          B[sensorFusion_B.b_jBcol].re = sensorFusion_B.temp_re /
            sensorFusion_B.b_A[0].re;
          B[sensorFusion_B.b_jBcol].im = 0.0F;
        } else if (sensorFusion_B.temp_re == 0.0F) {
          B[sensorFusion_B.b_jBcol].re = 0.0F;
          B[sensorFusion_B.b_jBcol].im = sensorFusion_B.temp_im /
            sensorFusion_B.b_A[0].re;
        } else {
          B[sensorFusion_B.b_jBcol].re = sensorFusion_B.temp_re /
            sensorFusion_B.b_A[0].re;
          B[sensorFusion_B.b_jBcol].im = sensorFusion_B.temp_im /
            sensorFusion_B.b_A[0].re;
        }
      } else if (sensorFusion_B.b_A[0].re == 0.0F) {
        if (sensorFusion_B.temp_re == 0.0F) {
          B[sensorFusion_B.b_jBcol].re = sensorFusion_B.temp_im /
            sensorFusion_B.b_A[0].im;
          B[sensorFusion_B.b_jBcol].im = 0.0F;
        } else if (sensorFusion_B.temp_im == 0.0F) {
          B[sensorFusion_B.b_jBcol].re = 0.0F;
          B[sensorFusion_B.b_jBcol].im = -(sensorFusion_B.temp_re /
            sensorFusion_B.b_A[0].im);
        } else {
          B[sensorFusion_B.b_jBcol].re = sensorFusion_B.temp_im /
            sensorFusion_B.b_A[0].im;
          B[sensorFusion_B.b_jBcol].im = -(sensorFusion_B.temp_re /
            sensorFusion_B.b_A[0].im);
        }
      } else {
        sensorFusion_B.brm = (real32_T)fabs(sensorFusion_B.b_A[0].re);
        sensorFusion_B.bim = (real32_T)fabs(sensorFusion_B.b_A[0].im);
        if (sensorFusion_B.brm > sensorFusion_B.bim) {
          sensorFusion_B.brm = sensorFusion_B.b_A[0].im / sensorFusion_B.b_A[0].
            re;
          sensorFusion_B.bim = sensorFusion_B.brm * sensorFusion_B.b_A[0].im +
            sensorFusion_B.b_A[0].re;
          B[sensorFusion_B.b_jBcol].re = (sensorFusion_B.brm *
            sensorFusion_B.temp_im + sensorFusion_B.temp_re) /
            sensorFusion_B.bim;
          B[sensorFusion_B.b_jBcol].im = (sensorFusion_B.temp_im -
            sensorFusion_B.brm * sensorFusion_B.temp_re) / sensorFusion_B.bim;
        } else if (sensorFusion_B.bim == sensorFusion_B.brm) {
          sensorFusion_B.bim = sensorFusion_B.b_A[0].re > 0.0F ? 0.5F : -0.5F;
          sensorFusion_B.sgnbi = sensorFusion_B.b_A[0].im > 0.0F ? 0.5F : -0.5F;
          B[sensorFusion_B.b_jBcol].re = (sensorFusion_B.temp_re *
            sensorFusion_B.bim + sensorFusion_B.temp_im * sensorFusion_B.sgnbi) /
            sensorFusion_B.brm;
          B[sensorFusion_B.b_jBcol].im = (sensorFusion_B.temp_im *
            sensorFusion_B.bim - sensorFusion_B.temp_re * sensorFusion_B.sgnbi) /
            sensorFusion_B.brm;
        } else {
          sensorFusion_B.brm = sensorFusion_B.b_A[0].re / sensorFusion_B.b_A[0].
            im;
          sensorFusion_B.bim = sensorFusion_B.brm * sensorFusion_B.b_A[0].re +
            sensorFusion_B.b_A[0].im;
          B[sensorFusion_B.b_jBcol].re = (sensorFusion_B.brm *
            sensorFusion_B.temp_re + sensorFusion_B.temp_im) /
            sensorFusion_B.bim;
          B[sensorFusion_B.b_jBcol].im = (sensorFusion_B.brm *
            sensorFusion_B.temp_im - sensorFusion_B.temp_re) /
            sensorFusion_B.bim;
        }
      }
    }
  }
}

/* Function for MATLAB Function: '<S3>/MATLAB Function' */
static void sensorF_PadeApproximantOfDegree(const creal32_T A[16], uint8_T m,
  creal32_T F[16])
{
  for (sensorFusion_B.d_b = 0; sensorFusion_B.d_b < 4; sensorFusion_B.d_b++) {
    for (sensorFusion_B.i2 = 0; sensorFusion_B.i2 < 4; sensorFusion_B.i2++) {
      sensorFusion_B.A2[sensorFusion_B.i2 + (sensorFusion_B.d_b << 2)].re = 0.0F;
      sensorFusion_B.A2[sensorFusion_B.i2 + (sensorFusion_B.d_b << 2)].im = 0.0F;
      sensorFusion_B.A2[sensorFusion_B.i2 + (sensorFusion_B.d_b << 2)].re +=
        A[sensorFusion_B.d_b << 2].re * A[sensorFusion_B.i2].re -
        A[sensorFusion_B.d_b << 2].im * A[sensorFusion_B.i2].im;
      sensorFusion_B.A2[sensorFusion_B.i2 + (sensorFusion_B.d_b << 2)].im +=
        A[sensorFusion_B.d_b << 2].im * A[sensorFusion_B.i2].re +
        A[sensorFusion_B.d_b << 2].re * A[sensorFusion_B.i2].im;
      sensorFusion_B.A2[sensorFusion_B.i2 + (sensorFusion_B.d_b << 2)].re += A
        [(sensorFusion_B.d_b << 2) + 1].re * A[sensorFusion_B.i2 + 4].re - A
        [(sensorFusion_B.d_b << 2) + 1].im * A[sensorFusion_B.i2 + 4].im;
      sensorFusion_B.A2[sensorFusion_B.i2 + (sensorFusion_B.d_b << 2)].im += A
        [(sensorFusion_B.d_b << 2) + 1].im * A[sensorFusion_B.i2 + 4].re + A
        [(sensorFusion_B.d_b << 2) + 1].re * A[sensorFusion_B.i2 + 4].im;
      sensorFusion_B.A2[sensorFusion_B.i2 + (sensorFusion_B.d_b << 2)].re += A
        [(sensorFusion_B.d_b << 2) + 2].re * A[sensorFusion_B.i2 + 8].re - A
        [(sensorFusion_B.d_b << 2) + 2].im * A[sensorFusion_B.i2 + 8].im;
      sensorFusion_B.A2[sensorFusion_B.i2 + (sensorFusion_B.d_b << 2)].im += A
        [(sensorFusion_B.d_b << 2) + 2].im * A[sensorFusion_B.i2 + 8].re + A
        [(sensorFusion_B.d_b << 2) + 2].re * A[sensorFusion_B.i2 + 8].im;
      sensorFusion_B.A2[sensorFusion_B.i2 + (sensorFusion_B.d_b << 2)].re += A
        [(sensorFusion_B.d_b << 2) + 3].re * A[sensorFusion_B.i2 + 12].re - A
        [(sensorFusion_B.d_b << 2) + 3].im * A[sensorFusion_B.i2 + 12].im;
      sensorFusion_B.A2[sensorFusion_B.i2 + (sensorFusion_B.d_b << 2)].im += A
        [(sensorFusion_B.d_b << 2) + 3].im * A[sensorFusion_B.i2 + 12].re + A
        [(sensorFusion_B.d_b << 2) + 3].re * A[sensorFusion_B.i2 + 12].im;
    }
  }

  if (m == 3) {
    memcpy(&F[0], &sensorFusion_B.A2[0], sizeof(creal32_T) << 4U);
    F[0].re += 60.0F;
    F[5].re += 60.0F;
    F[10].re += 60.0F;
    F[15].re += 60.0F;
    for (sensorFusion_B.d_b = 0; sensorFusion_B.d_b < 4; sensorFusion_B.d_b++) {
      for (sensorFusion_B.i2 = 0; sensorFusion_B.i2 < 4; sensorFusion_B.i2++) {
        sensorFusion_B.A_g[sensorFusion_B.i2 + (sensorFusion_B.d_b << 2)].re =
          0.0F;
        sensorFusion_B.A_g[sensorFusion_B.i2 + (sensorFusion_B.d_b << 2)].im =
          0.0F;
        sensorFusion_B.A_g[sensorFusion_B.i2 + (sensorFusion_B.d_b << 2)].re +=
          F[sensorFusion_B.d_b << 2].re * A[sensorFusion_B.i2].re -
          F[sensorFusion_B.d_b << 2].im * A[sensorFusion_B.i2].im;
        sensorFusion_B.A_g[sensorFusion_B.i2 + (sensorFusion_B.d_b << 2)].im +=
          F[sensorFusion_B.d_b << 2].im * A[sensorFusion_B.i2].re +
          F[sensorFusion_B.d_b << 2].re * A[sensorFusion_B.i2].im;
        sensorFusion_B.A_g[sensorFusion_B.i2 + (sensorFusion_B.d_b << 2)].re +=
          F[(sensorFusion_B.d_b << 2) + 1].re * A[sensorFusion_B.i2 + 4].re - F
          [(sensorFusion_B.d_b << 2) + 1].im * A[sensorFusion_B.i2 + 4].im;
        sensorFusion_B.A_g[sensorFusion_B.i2 + (sensorFusion_B.d_b << 2)].im +=
          F[(sensorFusion_B.d_b << 2) + 1].im * A[sensorFusion_B.i2 + 4].re + F
          [(sensorFusion_B.d_b << 2) + 1].re * A[sensorFusion_B.i2 + 4].im;
        sensorFusion_B.A_g[sensorFusion_B.i2 + (sensorFusion_B.d_b << 2)].re +=
          F[(sensorFusion_B.d_b << 2) + 2].re * A[sensorFusion_B.i2 + 8].re - F
          [(sensorFusion_B.d_b << 2) + 2].im * A[sensorFusion_B.i2 + 8].im;
        sensorFusion_B.A_g[sensorFusion_B.i2 + (sensorFusion_B.d_b << 2)].im +=
          F[(sensorFusion_B.d_b << 2) + 2].im * A[sensorFusion_B.i2 + 8].re + F
          [(sensorFusion_B.d_b << 2) + 2].re * A[sensorFusion_B.i2 + 8].im;
        sensorFusion_B.A_g[sensorFusion_B.i2 + (sensorFusion_B.d_b << 2)].re +=
          F[(sensorFusion_B.d_b << 2) + 3].re * A[sensorFusion_B.i2 + 12].re -
          F[(sensorFusion_B.d_b << 2) + 3].im * A[sensorFusion_B.i2 + 12].im;
        sensorFusion_B.A_g[sensorFusion_B.i2 + (sensorFusion_B.d_b << 2)].im +=
          F[(sensorFusion_B.d_b << 2) + 3].im * A[sensorFusion_B.i2 + 12].re +
          F[(sensorFusion_B.d_b << 2) + 3].re * A[sensorFusion_B.i2 + 12].im;
      }
    }

    for (sensorFusion_B.d_b = 0; sensorFusion_B.d_b < 4; sensorFusion_B.d_b++) {
      F[sensorFusion_B.d_b << 2] = sensorFusion_B.A_g[sensorFusion_B.d_b << 2];
      F[1 + (sensorFusion_B.d_b << 2)] = sensorFusion_B.A_g[(sensorFusion_B.d_b <<
        2) + 1];
      F[2 + (sensorFusion_B.d_b << 2)] = sensorFusion_B.A_g[(sensorFusion_B.d_b <<
        2) + 2];
      F[3 + (sensorFusion_B.d_b << 2)] = sensorFusion_B.A_g[(sensorFusion_B.d_b <<
        2) + 3];
    }

    for (sensorFusion_B.d_b = 0; sensorFusion_B.d_b < 16; sensorFusion_B.d_b++)
    {
      sensorFusion_B.A4[sensorFusion_B.d_b].re = 12.0F *
        sensorFusion_B.A2[sensorFusion_B.d_b].re;
      sensorFusion_B.A4[sensorFusion_B.d_b].im = 12.0F *
        sensorFusion_B.A2[sensorFusion_B.d_b].im;
    }

    sensorFusion_B.d_b = 120;
  } else {
    for (sensorFusion_B.d_b = 0; sensorFusion_B.d_b < 4; sensorFusion_B.d_b++) {
      for (sensorFusion_B.i2 = 0; sensorFusion_B.i2 < 4; sensorFusion_B.i2++) {
        sensorFusion_B.A3[sensorFusion_B.i2 + (sensorFusion_B.d_b << 2)].re =
          0.0F;
        sensorFusion_B.A3[sensorFusion_B.i2 + (sensorFusion_B.d_b << 2)].im =
          0.0F;
        sensorFusion_B.A3[sensorFusion_B.i2 + (sensorFusion_B.d_b << 2)].re +=
          sensorFusion_B.A2[sensorFusion_B.d_b << 2].re *
          sensorFusion_B.A2[sensorFusion_B.i2].re -
          sensorFusion_B.A2[sensorFusion_B.d_b << 2].im *
          sensorFusion_B.A2[sensorFusion_B.i2].im;
        sensorFusion_B.A3[sensorFusion_B.i2 + (sensorFusion_B.d_b << 2)].im +=
          sensorFusion_B.A2[sensorFusion_B.d_b << 2].im *
          sensorFusion_B.A2[sensorFusion_B.i2].re +
          sensorFusion_B.A2[sensorFusion_B.d_b << 2].re *
          sensorFusion_B.A2[sensorFusion_B.i2].im;
        sensorFusion_B.A3[sensorFusion_B.i2 + (sensorFusion_B.d_b << 2)].re +=
          sensorFusion_B.A2[(sensorFusion_B.d_b << 2) + 1].re *
          sensorFusion_B.A2[sensorFusion_B.i2 + 4].re - sensorFusion_B.A2
          [(sensorFusion_B.d_b << 2) + 1].im *
          sensorFusion_B.A2[sensorFusion_B.i2 + 4].im;
        sensorFusion_B.A3[sensorFusion_B.i2 + (sensorFusion_B.d_b << 2)].im +=
          sensorFusion_B.A2[(sensorFusion_B.d_b << 2) + 1].im *
          sensorFusion_B.A2[sensorFusion_B.i2 + 4].re + sensorFusion_B.A2
          [(sensorFusion_B.d_b << 2) + 1].re *
          sensorFusion_B.A2[sensorFusion_B.i2 + 4].im;
        sensorFusion_B.A3[sensorFusion_B.i2 + (sensorFusion_B.d_b << 2)].re +=
          sensorFusion_B.A2[(sensorFusion_B.d_b << 2) + 2].re *
          sensorFusion_B.A2[sensorFusion_B.i2 + 8].re - sensorFusion_B.A2
          [(sensorFusion_B.d_b << 2) + 2].im *
          sensorFusion_B.A2[sensorFusion_B.i2 + 8].im;
        sensorFusion_B.A3[sensorFusion_B.i2 + (sensorFusion_B.d_b << 2)].im +=
          sensorFusion_B.A2[(sensorFusion_B.d_b << 2) + 2].im *
          sensorFusion_B.A2[sensorFusion_B.i2 + 8].re + sensorFusion_B.A2
          [(sensorFusion_B.d_b << 2) + 2].re *
          sensorFusion_B.A2[sensorFusion_B.i2 + 8].im;
        sensorFusion_B.A3[sensorFusion_B.i2 + (sensorFusion_B.d_b << 2)].re +=
          sensorFusion_B.A2[(sensorFusion_B.d_b << 2) + 3].re *
          sensorFusion_B.A2[sensorFusion_B.i2 + 12].re - sensorFusion_B.A2
          [(sensorFusion_B.d_b << 2) + 3].im *
          sensorFusion_B.A2[sensorFusion_B.i2 + 12].im;
        sensorFusion_B.A3[sensorFusion_B.i2 + (sensorFusion_B.d_b << 2)].im +=
          sensorFusion_B.A2[(sensorFusion_B.d_b << 2) + 3].im *
          sensorFusion_B.A2[sensorFusion_B.i2 + 12].re + sensorFusion_B.A2
          [(sensorFusion_B.d_b << 2) + 3].re *
          sensorFusion_B.A2[sensorFusion_B.i2 + 12].im;
      }
    }

    if (m == 5) {
      for (sensorFusion_B.d_b = 0; sensorFusion_B.d_b < 16; sensorFusion_B.d_b++)
      {
        F[sensorFusion_B.d_b].re = 420.0F * sensorFusion_B.A2[sensorFusion_B.d_b]
          .re + sensorFusion_B.A3[sensorFusion_B.d_b].re;
        F[sensorFusion_B.d_b].im = 420.0F * sensorFusion_B.A2[sensorFusion_B.d_b]
          .im + sensorFusion_B.A3[sensorFusion_B.d_b].im;
      }

      F[0].re += 15120.0F;
      F[5].re += 15120.0F;
      F[10].re += 15120.0F;
      F[15].re += 15120.0F;
      for (sensorFusion_B.d_b = 0; sensorFusion_B.d_b < 4; sensorFusion_B.d_b++)
      {
        for (sensorFusion_B.i2 = 0; sensorFusion_B.i2 < 4; sensorFusion_B.i2++)
        {
          sensorFusion_B.A_g[sensorFusion_B.i2 + (sensorFusion_B.d_b << 2)].re =
            0.0F;
          sensorFusion_B.A_g[sensorFusion_B.i2 + (sensorFusion_B.d_b << 2)].im =
            0.0F;
          sensorFusion_B.A_g[sensorFusion_B.i2 + (sensorFusion_B.d_b << 2)].re +=
            F[sensorFusion_B.d_b << 2].re * A[sensorFusion_B.i2].re -
            F[sensorFusion_B.d_b << 2].im * A[sensorFusion_B.i2].im;
          sensorFusion_B.A_g[sensorFusion_B.i2 + (sensorFusion_B.d_b << 2)].im +=
            F[sensorFusion_B.d_b << 2].im * A[sensorFusion_B.i2].re +
            F[sensorFusion_B.d_b << 2].re * A[sensorFusion_B.i2].im;
          sensorFusion_B.A_g[sensorFusion_B.i2 + (sensorFusion_B.d_b << 2)].re +=
            F[(sensorFusion_B.d_b << 2) + 1].re * A[sensorFusion_B.i2 + 4].re -
            F[(sensorFusion_B.d_b << 2) + 1].im * A[sensorFusion_B.i2 + 4].im;
          sensorFusion_B.A_g[sensorFusion_B.i2 + (sensorFusion_B.d_b << 2)].im +=
            F[(sensorFusion_B.d_b << 2) + 1].im * A[sensorFusion_B.i2 + 4].re +
            F[(sensorFusion_B.d_b << 2) + 1].re * A[sensorFusion_B.i2 + 4].im;
          sensorFusion_B.A_g[sensorFusion_B.i2 + (sensorFusion_B.d_b << 2)].re +=
            F[(sensorFusion_B.d_b << 2) + 2].re * A[sensorFusion_B.i2 + 8].re -
            F[(sensorFusion_B.d_b << 2) + 2].im * A[sensorFusion_B.i2 + 8].im;
          sensorFusion_B.A_g[sensorFusion_B.i2 + (sensorFusion_B.d_b << 2)].im +=
            F[(sensorFusion_B.d_b << 2) + 2].im * A[sensorFusion_B.i2 + 8].re +
            F[(sensorFusion_B.d_b << 2) + 2].re * A[sensorFusion_B.i2 + 8].im;
          sensorFusion_B.A_g[sensorFusion_B.i2 + (sensorFusion_B.d_b << 2)].re +=
            F[(sensorFusion_B.d_b << 2) + 3].re * A[sensorFusion_B.i2 + 12].re -
            F[(sensorFusion_B.d_b << 2) + 3].im * A[sensorFusion_B.i2 + 12].im;
          sensorFusion_B.A_g[sensorFusion_B.i2 + (sensorFusion_B.d_b << 2)].im +=
            F[(sensorFusion_B.d_b << 2) + 3].im * A[sensorFusion_B.i2 + 12].re +
            F[(sensorFusion_B.d_b << 2) + 3].re * A[sensorFusion_B.i2 + 12].im;
        }
      }

      for (sensorFusion_B.d_b = 0; sensorFusion_B.d_b < 4; sensorFusion_B.d_b++)
      {
        F[sensorFusion_B.d_b << 2] = sensorFusion_B.A_g[sensorFusion_B.d_b << 2];
        F[1 + (sensorFusion_B.d_b << 2)] = sensorFusion_B.A_g
          [(sensorFusion_B.d_b << 2) + 1];
        F[2 + (sensorFusion_B.d_b << 2)] = sensorFusion_B.A_g
          [(sensorFusion_B.d_b << 2) + 2];
        F[3 + (sensorFusion_B.d_b << 2)] = sensorFusion_B.A_g
          [(sensorFusion_B.d_b << 2) + 3];
      }

      for (sensorFusion_B.d_b = 0; sensorFusion_B.d_b < 16; sensorFusion_B.d_b++)
      {
        sensorFusion_B.A4[sensorFusion_B.d_b].re = 30.0F *
          sensorFusion_B.A3[sensorFusion_B.d_b].re + 3360.0F *
          sensorFusion_B.A2[sensorFusion_B.d_b].re;
        sensorFusion_B.A4[sensorFusion_B.d_b].im = 30.0F *
          sensorFusion_B.A3[sensorFusion_B.d_b].im + 3360.0F *
          sensorFusion_B.A2[sensorFusion_B.d_b].im;
      }

      sensorFusion_B.d_b = 30240;
    } else {
      for (sensorFusion_B.d_b = 0; sensorFusion_B.d_b < 4; sensorFusion_B.d_b++)
      {
        for (sensorFusion_B.i2 = 0; sensorFusion_B.i2 < 4; sensorFusion_B.i2++)
        {
          sensorFusion_B.A4[sensorFusion_B.i2 + (sensorFusion_B.d_b << 2)].re =
            0.0F;
          sensorFusion_B.A4[sensorFusion_B.i2 + (sensorFusion_B.d_b << 2)].im =
            0.0F;
          sensorFusion_B.A4[sensorFusion_B.i2 + (sensorFusion_B.d_b << 2)].re +=
            sensorFusion_B.A2[sensorFusion_B.d_b << 2].re *
            sensorFusion_B.A3[sensorFusion_B.i2].re -
            sensorFusion_B.A2[sensorFusion_B.d_b << 2].im *
            sensorFusion_B.A3[sensorFusion_B.i2].im;
          sensorFusion_B.A4[sensorFusion_B.i2 + (sensorFusion_B.d_b << 2)].im +=
            sensorFusion_B.A2[sensorFusion_B.d_b << 2].im *
            sensorFusion_B.A3[sensorFusion_B.i2].re +
            sensorFusion_B.A2[sensorFusion_B.d_b << 2].re *
            sensorFusion_B.A3[sensorFusion_B.i2].im;
          sensorFusion_B.A4[sensorFusion_B.i2 + (sensorFusion_B.d_b << 2)].re +=
            sensorFusion_B.A2[(sensorFusion_B.d_b << 2) + 1].re *
            sensorFusion_B.A3[sensorFusion_B.i2 + 4].re - sensorFusion_B.A2
            [(sensorFusion_B.d_b << 2) + 1].im *
            sensorFusion_B.A3[sensorFusion_B.i2 + 4].im;
          sensorFusion_B.A4[sensorFusion_B.i2 + (sensorFusion_B.d_b << 2)].im +=
            sensorFusion_B.A2[(sensorFusion_B.d_b << 2) + 1].im *
            sensorFusion_B.A3[sensorFusion_B.i2 + 4].re + sensorFusion_B.A2
            [(sensorFusion_B.d_b << 2) + 1].re *
            sensorFusion_B.A3[sensorFusion_B.i2 + 4].im;
          sensorFusion_B.A4[sensorFusion_B.i2 + (sensorFusion_B.d_b << 2)].re +=
            sensorFusion_B.A2[(sensorFusion_B.d_b << 2) + 2].re *
            sensorFusion_B.A3[sensorFusion_B.i2 + 8].re - sensorFusion_B.A2
            [(sensorFusion_B.d_b << 2) + 2].im *
            sensorFusion_B.A3[sensorFusion_B.i2 + 8].im;
          sensorFusion_B.A4[sensorFusion_B.i2 + (sensorFusion_B.d_b << 2)].im +=
            sensorFusion_B.A2[(sensorFusion_B.d_b << 2) + 2].im *
            sensorFusion_B.A3[sensorFusion_B.i2 + 8].re + sensorFusion_B.A2
            [(sensorFusion_B.d_b << 2) + 2].re *
            sensorFusion_B.A3[sensorFusion_B.i2 + 8].im;
          sensorFusion_B.A4[sensorFusion_B.i2 + (sensorFusion_B.d_b << 2)].re +=
            sensorFusion_B.A2[(sensorFusion_B.d_b << 2) + 3].re *
            sensorFusion_B.A3[sensorFusion_B.i2 + 12].re - sensorFusion_B.A2
            [(sensorFusion_B.d_b << 2) + 3].im *
            sensorFusion_B.A3[sensorFusion_B.i2 + 12].im;
          sensorFusion_B.A4[sensorFusion_B.i2 + (sensorFusion_B.d_b << 2)].im +=
            sensorFusion_B.A2[(sensorFusion_B.d_b << 2) + 3].im *
            sensorFusion_B.A3[sensorFusion_B.i2 + 12].re + sensorFusion_B.A2
            [(sensorFusion_B.d_b << 2) + 3].re *
            sensorFusion_B.A3[sensorFusion_B.i2 + 12].im;
        }
      }

      for (sensorFusion_B.d_b = 0; sensorFusion_B.d_b < 16; sensorFusion_B.d_b++)
      {
        F[sensorFusion_B.d_b].re = (1512.0F *
          sensorFusion_B.A3[sensorFusion_B.d_b].re +
          sensorFusion_B.A4[sensorFusion_B.d_b].re) + 277200.0F *
          sensorFusion_B.A2[sensorFusion_B.d_b].re;
        F[sensorFusion_B.d_b].im = (1512.0F *
          sensorFusion_B.A3[sensorFusion_B.d_b].im +
          sensorFusion_B.A4[sensorFusion_B.d_b].im) + 277200.0F *
          sensorFusion_B.A2[sensorFusion_B.d_b].im;
      }

      F[0].re += 8.64864E+6F;
      F[5].re += 8.64864E+6F;
      F[10].re += 8.64864E+6F;
      F[15].re += 8.64864E+6F;
      for (sensorFusion_B.d_b = 0; sensorFusion_B.d_b < 4; sensorFusion_B.d_b++)
      {
        for (sensorFusion_B.i2 = 0; sensorFusion_B.i2 < 4; sensorFusion_B.i2++)
        {
          sensorFusion_B.A_g[sensorFusion_B.i2 + (sensorFusion_B.d_b << 2)].re =
            0.0F;
          sensorFusion_B.A_g[sensorFusion_B.i2 + (sensorFusion_B.d_b << 2)].im =
            0.0F;
          sensorFusion_B.A_g[sensorFusion_B.i2 + (sensorFusion_B.d_b << 2)].re +=
            F[sensorFusion_B.d_b << 2].re * A[sensorFusion_B.i2].re -
            F[sensorFusion_B.d_b << 2].im * A[sensorFusion_B.i2].im;
          sensorFusion_B.A_g[sensorFusion_B.i2 + (sensorFusion_B.d_b << 2)].im +=
            F[sensorFusion_B.d_b << 2].im * A[sensorFusion_B.i2].re +
            F[sensorFusion_B.d_b << 2].re * A[sensorFusion_B.i2].im;
          sensorFusion_B.A_g[sensorFusion_B.i2 + (sensorFusion_B.d_b << 2)].re +=
            F[(sensorFusion_B.d_b << 2) + 1].re * A[sensorFusion_B.i2 + 4].re -
            F[(sensorFusion_B.d_b << 2) + 1].im * A[sensorFusion_B.i2 + 4].im;
          sensorFusion_B.A_g[sensorFusion_B.i2 + (sensorFusion_B.d_b << 2)].im +=
            F[(sensorFusion_B.d_b << 2) + 1].im * A[sensorFusion_B.i2 + 4].re +
            F[(sensorFusion_B.d_b << 2) + 1].re * A[sensorFusion_B.i2 + 4].im;
          sensorFusion_B.A_g[sensorFusion_B.i2 + (sensorFusion_B.d_b << 2)].re +=
            F[(sensorFusion_B.d_b << 2) + 2].re * A[sensorFusion_B.i2 + 8].re -
            F[(sensorFusion_B.d_b << 2) + 2].im * A[sensorFusion_B.i2 + 8].im;
          sensorFusion_B.A_g[sensorFusion_B.i2 + (sensorFusion_B.d_b << 2)].im +=
            F[(sensorFusion_B.d_b << 2) + 2].im * A[sensorFusion_B.i2 + 8].re +
            F[(sensorFusion_B.d_b << 2) + 2].re * A[sensorFusion_B.i2 + 8].im;
          sensorFusion_B.A_g[sensorFusion_B.i2 + (sensorFusion_B.d_b << 2)].re +=
            F[(sensorFusion_B.d_b << 2) + 3].re * A[sensorFusion_B.i2 + 12].re -
            F[(sensorFusion_B.d_b << 2) + 3].im * A[sensorFusion_B.i2 + 12].im;
          sensorFusion_B.A_g[sensorFusion_B.i2 + (sensorFusion_B.d_b << 2)].im +=
            F[(sensorFusion_B.d_b << 2) + 3].im * A[sensorFusion_B.i2 + 12].re +
            F[(sensorFusion_B.d_b << 2) + 3].re * A[sensorFusion_B.i2 + 12].im;
        }
      }

      for (sensorFusion_B.d_b = 0; sensorFusion_B.d_b < 4; sensorFusion_B.d_b++)
      {
        F[sensorFusion_B.d_b << 2] = sensorFusion_B.A_g[sensorFusion_B.d_b << 2];
        F[1 + (sensorFusion_B.d_b << 2)] = sensorFusion_B.A_g
          [(sensorFusion_B.d_b << 2) + 1];
        F[2 + (sensorFusion_B.d_b << 2)] = sensorFusion_B.A_g
          [(sensorFusion_B.d_b << 2) + 2];
        F[3 + (sensorFusion_B.d_b << 2)] = sensorFusion_B.A_g
          [(sensorFusion_B.d_b << 2) + 3];
      }

      for (sensorFusion_B.d_b = 0; sensorFusion_B.d_b < 16; sensorFusion_B.d_b++)
      {
        sensorFusion_B.A4_l.re = (56.0F * sensorFusion_B.A4[sensorFusion_B.d_b].
          re + 25200.0F * sensorFusion_B.A3[sensorFusion_B.d_b].re) +
          1.99584E+6F * sensorFusion_B.A2[sensorFusion_B.d_b].re;
        sensorFusion_B.A4_l.im = (56.0F * sensorFusion_B.A4[sensorFusion_B.d_b].
          im + 25200.0F * sensorFusion_B.A3[sensorFusion_B.d_b].im) +
          1.99584E+6F * sensorFusion_B.A2[sensorFusion_B.d_b].im;
        sensorFusion_B.A4[sensorFusion_B.d_b] = sensorFusion_B.A4_l;
      }

      sensorFusion_B.d_b = 17297280;
    }
  }

  sensorFusion_B.A4[0].re += (real32_T)sensorFusion_B.d_b;
  sensorFusion_B.A4[5].re += (real32_T)sensorFusion_B.d_b;
  sensorFusion_B.A4[10].re += (real32_T)sensorFusion_B.d_b;
  sensorFusion_B.A4[15].re += (real32_T)sensorFusion_B.d_b;
  for (sensorFusion_B.d_b = 0; sensorFusion_B.d_b < 16; sensorFusion_B.d_b++) {
    sensorFusion_B.A4_d.re = sensorFusion_B.A4[sensorFusion_B.d_b].re -
      F[sensorFusion_B.d_b].re;
    sensorFusion_B.A4_d.im = sensorFusion_B.A4[sensorFusion_B.d_b].im -
      F[sensorFusion_B.d_b].im;
    sensorFusion_B.F_g.re = 2.0F * F[sensorFusion_B.d_b].re;
    sensorFusion_B.F_g.im = 2.0F * F[sensorFusion_B.d_b].im;
    sensorFusion_B.A4[sensorFusion_B.d_b] = sensorFusion_B.A4_d;
    F[sensorFusion_B.d_b] = sensorFusion_B.F_g;
  }

  sensorFusion_mldivide(sensorFusion_B.A4, F);
  F[0].re++;
  F[5].re++;
  F[10].re++;
  F[15].re++;
}

/* Function for MATLAB Function: '<S3>/MATLAB Function' */
static void sensorFusion_expm(creal32_T A[16], creal32_T F[16])
{
  static const real32_T theta[3] = { 0.425873F, 1.8801527F, 3.92572474F };

  boolean_T exitg1;
  boolean_T exitg2;
  sensorFusion_B.normA = 0.0F;
  sensorFusion_B.b_j = 0;
  exitg2 = false;
  while ((!exitg2) && (sensorFusion_B.b_j < 4)) {
    sensorFusion_B.b_s = ((sensorFusion_rt_hypotf_snf(A[(sensorFusion_B.b_j << 2)
      + 1].re, A[(sensorFusion_B.b_j << 2) + 1].im) + sensorFusion_rt_hypotf_snf
      (A[sensorFusion_B.b_j << 2].re, A[sensorFusion_B.b_j << 2].im)) +
                          sensorFusion_rt_hypotf_snf(A[(sensorFusion_B.b_j << 2)
      + 2].re, A[(sensorFusion_B.b_j << 2) + 2].im)) +
      sensorFusion_rt_hypotf_snf(A[(sensorFusion_B.b_j << 2) + 3].re, A
      [(sensorFusion_B.b_j << 2) + 3].im);
    if (rtIsNaNF(sensorFusion_B.b_s)) {
      sensorFusion_B.normA = (rtNaNF);
      exitg2 = true;
    } else {
      if (sensorFusion_B.b_s > sensorFusion_B.normA) {
        sensorFusion_B.normA = sensorFusion_B.b_s;
      }

      sensorFusion_B.b_j++;
    }
  }

  if (sensorFusion_B.normA <= 3.92572474F) {
    sensorFusion_B.b_j = 0;
    exitg1 = false;
    while ((!exitg1) && (sensorFusion_B.b_j < 3)) {
      if (sensorFusion_B.normA <= theta[sensorFusion_B.b_j]) {
        sensorF_PadeApproximantOfDegree(A, (uint8_T)((sensorFusion_B.b_j << 1) +
          3), F);
        exitg1 = true;
      } else {
        sensorFusion_B.b_j++;
      }
    }
  } else {
    sensorFusion_B.b_s = sensorFusion_B.normA / 3.92572474F;
    if ((!rtIsInfF(sensorFusion_B.b_s)) && (!rtIsNaNF(sensorFusion_B.b_s))) {
      sensorFusion_B.b_s = (real32_T)frexp(sensorFusion_B.b_s,
        &sensorFusion_B.eint);
      sensorFusion_B.normA = (real32_T)sensorFusion_B.eint;
    } else {
      sensorFusion_B.normA = 0.0F;
    }

    if (sensorFusion_B.b_s == 0.5F) {
      sensorFusion_B.normA--;
    }

    sensorFusion_B.b_s = sensorFusion_rt_powf_snf(2.0F, sensorFusion_B.normA);
    for (sensorFusion_B.eint = 0; sensorFusion_B.eint < 16; sensorFusion_B.eint
         ++) {
      if (A[sensorFusion_B.eint].im == 0.0F) {
        sensorFusion_B.A_j.re = A[sensorFusion_B.eint].re / sensorFusion_B.b_s;
        sensorFusion_B.A_j.im = 0.0F;
      } else if (A[sensorFusion_B.eint].re == 0.0F) {
        sensorFusion_B.A_j.re = 0.0F;
        sensorFusion_B.A_j.im = A[sensorFusion_B.eint].im / sensorFusion_B.b_s;
      } else {
        sensorFusion_B.A_j.re = A[sensorFusion_B.eint].re / sensorFusion_B.b_s;
        sensorFusion_B.A_j.im = A[sensorFusion_B.eint].im / sensorFusion_B.b_s;
      }

      A[sensorFusion_B.eint] = sensorFusion_B.A_j;
    }

    sensorF_PadeApproximantOfDegree(A, 7U, F);
    sensorFusion_B.b_j = 0;
    while (sensorFusion_B.b_j <= (int32_T)sensorFusion_B.normA - 1) {
      for (sensorFusion_B.eint = 0; sensorFusion_B.eint < 4; sensorFusion_B.eint
           ++) {
        for (sensorFusion_B.i1 = 0; sensorFusion_B.i1 < 4; sensorFusion_B.i1++)
        {
          sensorFusion_B.F[sensorFusion_B.eint + (sensorFusion_B.i1 << 2)].re =
            0.0F;
          sensorFusion_B.F[sensorFusion_B.eint + (sensorFusion_B.i1 << 2)].im =
            0.0F;
          sensorFusion_B.F[sensorFusion_B.eint + (sensorFusion_B.i1 << 2)].re +=
            F[sensorFusion_B.i1 << 2].re * F[sensorFusion_B.eint].re -
            F[sensorFusion_B.i1 << 2].im * F[sensorFusion_B.eint].im;
          sensorFusion_B.F[sensorFusion_B.eint + (sensorFusion_B.i1 << 2)].im +=
            F[sensorFusion_B.i1 << 2].im * F[sensorFusion_B.eint].re +
            F[sensorFusion_B.i1 << 2].re * F[sensorFusion_B.eint].im;
          sensorFusion_B.F[sensorFusion_B.eint + (sensorFusion_B.i1 << 2)].re +=
            F[(sensorFusion_B.i1 << 2) + 1].re * F[sensorFusion_B.eint + 4].re -
            F[(sensorFusion_B.i1 << 2) + 1].im * F[sensorFusion_B.eint + 4].im;
          sensorFusion_B.F[sensorFusion_B.eint + (sensorFusion_B.i1 << 2)].im +=
            F[(sensorFusion_B.i1 << 2) + 1].im * F[sensorFusion_B.eint + 4].re +
            F[(sensorFusion_B.i1 << 2) + 1].re * F[sensorFusion_B.eint + 4].im;
          sensorFusion_B.F[sensorFusion_B.eint + (sensorFusion_B.i1 << 2)].re +=
            F[(sensorFusion_B.i1 << 2) + 2].re * F[sensorFusion_B.eint + 8].re -
            F[(sensorFusion_B.i1 << 2) + 2].im * F[sensorFusion_B.eint + 8].im;
          sensorFusion_B.F[sensorFusion_B.eint + (sensorFusion_B.i1 << 2)].im +=
            F[(sensorFusion_B.i1 << 2) + 2].im * F[sensorFusion_B.eint + 8].re +
            F[(sensorFusion_B.i1 << 2) + 2].re * F[sensorFusion_B.eint + 8].im;
          sensorFusion_B.F[sensorFusion_B.eint + (sensorFusion_B.i1 << 2)].re +=
            F[(sensorFusion_B.i1 << 2) + 3].re * F[sensorFusion_B.eint + 12].re
            - F[(sensorFusion_B.i1 << 2) + 3].im * F[sensorFusion_B.eint + 12].
            im;
          sensorFusion_B.F[sensorFusion_B.eint + (sensorFusion_B.i1 << 2)].im +=
            F[(sensorFusion_B.i1 << 2) + 3].im * F[sensorFusion_B.eint + 12].re
            + F[(sensorFusion_B.i1 << 2) + 3].re * F[sensorFusion_B.eint + 12].
            im;
        }
      }

      for (sensorFusion_B.eint = 0; sensorFusion_B.eint < 4; sensorFusion_B.eint
           ++) {
        F[sensorFusion_B.eint << 2] = sensorFusion_B.F[sensorFusion_B.eint << 2];
        F[1 + (sensorFusion_B.eint << 2)] = sensorFusion_B.F
          [(sensorFusion_B.eint << 2) + 1];
        F[2 + (sensorFusion_B.eint << 2)] = sensorFusion_B.F
          [(sensorFusion_B.eint << 2) + 2];
        F[3 + (sensorFusion_B.eint << 2)] = sensorFusion_B.F
          [(sensorFusion_B.eint << 2) + 3];
      }

      sensorFusion_B.b_j++;
    }
  }
}

/* Function for MATLAB Function: '<S3>/MATLAB Function' */
static real32_T sensorFusion_norm(const creal32_T x[4])
{
  real32_T y;
  sensorFusion_B.scale_d = 1.17549435E-38F;
  sensorFusion_B.absxk_l = (real32_T)fabs(x[0].re);
  if (sensorFusion_B.absxk_l > 1.17549435E-38F) {
    y = 1.0F;
    sensorFusion_B.scale_d = sensorFusion_B.absxk_l;
  } else {
    sensorFusion_B.t = sensorFusion_B.absxk_l / 1.17549435E-38F;
    y = sensorFusion_B.t * sensorFusion_B.t;
  }

  sensorFusion_B.absxk_l = (real32_T)fabs(x[0].im);
  if (sensorFusion_B.absxk_l > sensorFusion_B.scale_d) {
    sensorFusion_B.t = sensorFusion_B.scale_d / sensorFusion_B.absxk_l;
    y = y * sensorFusion_B.t * sensorFusion_B.t + 1.0F;
    sensorFusion_B.scale_d = sensorFusion_B.absxk_l;
  } else {
    sensorFusion_B.t = sensorFusion_B.absxk_l / sensorFusion_B.scale_d;
    y += sensorFusion_B.t * sensorFusion_B.t;
  }

  sensorFusion_B.absxk_l = (real32_T)fabs(x[1].re);
  if (sensorFusion_B.absxk_l > sensorFusion_B.scale_d) {
    sensorFusion_B.t = sensorFusion_B.scale_d / sensorFusion_B.absxk_l;
    y = y * sensorFusion_B.t * sensorFusion_B.t + 1.0F;
    sensorFusion_B.scale_d = sensorFusion_B.absxk_l;
  } else {
    sensorFusion_B.t = sensorFusion_B.absxk_l / sensorFusion_B.scale_d;
    y += sensorFusion_B.t * sensorFusion_B.t;
  }

  sensorFusion_B.absxk_l = (real32_T)fabs(x[1].im);
  if (sensorFusion_B.absxk_l > sensorFusion_B.scale_d) {
    sensorFusion_B.t = sensorFusion_B.scale_d / sensorFusion_B.absxk_l;
    y = y * sensorFusion_B.t * sensorFusion_B.t + 1.0F;
    sensorFusion_B.scale_d = sensorFusion_B.absxk_l;
  } else {
    sensorFusion_B.t = sensorFusion_B.absxk_l / sensorFusion_B.scale_d;
    y += sensorFusion_B.t * sensorFusion_B.t;
  }

  sensorFusion_B.absxk_l = (real32_T)fabs(x[2].re);
  if (sensorFusion_B.absxk_l > sensorFusion_B.scale_d) {
    sensorFusion_B.t = sensorFusion_B.scale_d / sensorFusion_B.absxk_l;
    y = y * sensorFusion_B.t * sensorFusion_B.t + 1.0F;
    sensorFusion_B.scale_d = sensorFusion_B.absxk_l;
  } else {
    sensorFusion_B.t = sensorFusion_B.absxk_l / sensorFusion_B.scale_d;
    y += sensorFusion_B.t * sensorFusion_B.t;
  }

  sensorFusion_B.absxk_l = (real32_T)fabs(x[2].im);
  if (sensorFusion_B.absxk_l > sensorFusion_B.scale_d) {
    sensorFusion_B.t = sensorFusion_B.scale_d / sensorFusion_B.absxk_l;
    y = y * sensorFusion_B.t * sensorFusion_B.t + 1.0F;
    sensorFusion_B.scale_d = sensorFusion_B.absxk_l;
  } else {
    sensorFusion_B.t = sensorFusion_B.absxk_l / sensorFusion_B.scale_d;
    y += sensorFusion_B.t * sensorFusion_B.t;
  }

  sensorFusion_B.absxk_l = (real32_T)fabs(x[3].re);
  if (sensorFusion_B.absxk_l > sensorFusion_B.scale_d) {
    sensorFusion_B.t = sensorFusion_B.scale_d / sensorFusion_B.absxk_l;
    y = y * sensorFusion_B.t * sensorFusion_B.t + 1.0F;
    sensorFusion_B.scale_d = sensorFusion_B.absxk_l;
  } else {
    sensorFusion_B.t = sensorFusion_B.absxk_l / sensorFusion_B.scale_d;
    y += sensorFusion_B.t * sensorFusion_B.t;
  }

  sensorFusion_B.absxk_l = (real32_T)fabs(x[3].im);
  if (sensorFusion_B.absxk_l > sensorFusion_B.scale_d) {
    sensorFusion_B.t = sensorFusion_B.scale_d / sensorFusion_B.absxk_l;
    y = y * sensorFusion_B.t * sensorFusion_B.t + 1.0F;
    sensorFusion_B.scale_d = sensorFusion_B.absxk_l;
  } else {
    sensorFusion_B.t = sensorFusion_B.absxk_l / sensorFusion_B.scale_d;
    y += sensorFusion_B.t * sensorFusion_B.t;
  }

  return sensorFusion_B.scale_d * (real32_T)sqrt(y);
}

/*
 * Function for MATLAB Function: '<S3>/MATLAB Function'
 * function C=getC(q)
 */
static void sensorFusion_getC(const creal32_T q[4], creal32_T C[9])
{
  real32_T t;
  real32_T absxr;
  int32_T i;
  real32_T s_idx_0_re;
  real32_T s_idx_0_im;
  real32_T s_idx_1_re;
  real32_T s_idx_1_im;
  real32_T s_idx_2_re;
  real32_T s_idx_2_im;
  real32_T s_idx_3_re;
  real32_T s_idx_3_im;

  /* '<S5>:1:86' s=q.^2; */
  s_idx_0_re = q[0].re * q[0].re - q[0].im * q[0].im;
  s_idx_0_im = q[0].re * q[0].im + q[0].im * q[0].re;
  s_idx_1_re = q[1].re * q[1].re - q[1].im * q[1].im;
  s_idx_1_im = q[1].re * q[1].im + q[1].im * q[1].re;
  s_idx_2_re = q[2].re * q[2].re - q[2].im * q[2].im;
  s_idx_2_im = q[2].re * q[2].im + q[2].im * q[2].re;
  s_idx_3_re = q[3].re * q[3].re - q[3].im * q[3].im;
  s_idx_3_im = q[3].re * q[3].im + q[3].im * q[3].re;

  /* '<S5>:1:87' C=[s(1)-s(2)-s(3)+s(4)        2*(q(1)*q(2)+q(3)*q(4))    2*(q(1)*q(3)-q(2)*q(4)) */
  /* '<S5>:1:88'    2*(q(1)*q(2)-q(3)*q(4))   -s(1)+s(2)-s(3)+s(4)        2*(q(2)*q(3)+q(4)*q(1)) */
  /* '<S5>:1:89'    2*(q(1)*q(3)+q(2)*q(4))    2*(q(2)*q(3)-q(4)*q(1))   -s(1)-s(2)+s(3)+s(4)]; */
  /* '<S5>:1:91' C=(1/sqrt(norm(q(1:3))^2+q(4)^2))*C; */
  sensorFusion_B.scale = 1.17549435E-38F;
  sensorFusion_B.absxk = (real32_T)fabs(q[0].re);
  if (sensorFusion_B.absxk > 1.17549435E-38F) {
    absxr = 1.0F;
    sensorFusion_B.scale = sensorFusion_B.absxk;
  } else {
    t = sensorFusion_B.absxk / 1.17549435E-38F;
    absxr = t * t;
  }

  sensorFusion_B.absxk = (real32_T)fabs(q[0].im);
  if (sensorFusion_B.absxk > sensorFusion_B.scale) {
    t = sensorFusion_B.scale / sensorFusion_B.absxk;
    absxr = absxr * t * t + 1.0F;
    sensorFusion_B.scale = sensorFusion_B.absxk;
  } else {
    t = sensorFusion_B.absxk / sensorFusion_B.scale;
    absxr += t * t;
  }

  sensorFusion_B.absxk = (real32_T)fabs(q[1].re);
  if (sensorFusion_B.absxk > sensorFusion_B.scale) {
    t = sensorFusion_B.scale / sensorFusion_B.absxk;
    absxr = absxr * t * t + 1.0F;
    sensorFusion_B.scale = sensorFusion_B.absxk;
  } else {
    t = sensorFusion_B.absxk / sensorFusion_B.scale;
    absxr += t * t;
  }

  sensorFusion_B.absxk = (real32_T)fabs(q[1].im);
  if (sensorFusion_B.absxk > sensorFusion_B.scale) {
    t = sensorFusion_B.scale / sensorFusion_B.absxk;
    absxr = absxr * t * t + 1.0F;
    sensorFusion_B.scale = sensorFusion_B.absxk;
  } else {
    t = sensorFusion_B.absxk / sensorFusion_B.scale;
    absxr += t * t;
  }

  sensorFusion_B.absxk = (real32_T)fabs(q[2].re);
  if (sensorFusion_B.absxk > sensorFusion_B.scale) {
    t = sensorFusion_B.scale / sensorFusion_B.absxk;
    absxr = absxr * t * t + 1.0F;
    sensorFusion_B.scale = sensorFusion_B.absxk;
  } else {
    t = sensorFusion_B.absxk / sensorFusion_B.scale;
    absxr += t * t;
  }

  sensorFusion_B.absxk = (real32_T)fabs(q[2].im);
  if (sensorFusion_B.absxk > sensorFusion_B.scale) {
    t = sensorFusion_B.scale / sensorFusion_B.absxk;
    absxr = absxr * t * t + 1.0F;
    sensorFusion_B.scale = sensorFusion_B.absxk;
  } else {
    t = sensorFusion_B.absxk / sensorFusion_B.scale;
    absxr += t * t;
  }

  absxr = sensorFusion_B.scale * (real32_T)sqrt(absxr);
  t = q[3].re * q[3].im + q[3].im * q[3].re;
  sensorFusion_B.absxk = (q[3].re * q[3].re - q[3].im * q[3].im) + absxr * absxr;
  if (t == 0.0F) {
    if (sensorFusion_B.absxk < 0.0F) {
      absxr = 0.0F;
      sensorFusion_B.scale = (real32_T)sqrt((real32_T)fabs(sensorFusion_B.absxk));
    } else {
      absxr = (real32_T)sqrt(sensorFusion_B.absxk);
      sensorFusion_B.scale = 0.0F;
    }
  } else if (sensorFusion_B.absxk == 0.0F) {
    if (t < 0.0F) {
      absxr = (real32_T)sqrt(-t / 2.0F);
      sensorFusion_B.scale = -absxr;
    } else {
      absxr = (real32_T)sqrt(t / 2.0F);
      sensorFusion_B.scale = absxr;
    }
  } else if (rtIsNaNF(sensorFusion_B.absxk) || rtIsNaNF(t)) {
    absxr = (rtNaNF);
    sensorFusion_B.scale = (rtNaNF);
  } else if (rtIsInfF(t)) {
    absxr = (rtInfF);
    sensorFusion_B.scale = t;
  } else if (rtIsInfF(sensorFusion_B.absxk)) {
    if (sensorFusion_B.absxk < 0.0F) {
      absxr = 0.0F;
      sensorFusion_B.scale = (rtInfF);
    } else {
      absxr = (rtInfF);
      sensorFusion_B.scale = 0.0F;
    }
  } else {
    absxr = (real32_T)fabs(sensorFusion_B.absxk);
    sensorFusion_B.scale = (real32_T)fabs(t);
    if ((absxr > 8.50705867E+37F) || (sensorFusion_B.scale > 8.50705867E+37F)) {
      absxr *= 0.5F;
      sensorFusion_B.scale *= 0.5F;
      sensorFusion_B.scale = sensorFusion_rt_hypotf_snf(absxr,
        sensorFusion_B.scale);
      if (sensorFusion_B.scale > absxr) {
        absxr = (real32_T)sqrt(absxr / sensorFusion_B.scale + 1.0F) * (real32_T)
          sqrt(sensorFusion_B.scale);
      } else {
        absxr = (real32_T)sqrt(sensorFusion_B.scale) * 1.41421354F;
      }
    } else {
      absxr = (real32_T)sqrt((sensorFusion_rt_hypotf_snf(absxr,
        sensorFusion_B.scale) + absxr) * 0.5F);
    }

    if (sensorFusion_B.absxk > 0.0F) {
      sensorFusion_B.scale = t / absxr * 0.5F;
    } else {
      if (t < 0.0F) {
        sensorFusion_B.scale = -absxr;
      } else {
        sensorFusion_B.scale = absxr;
      }

      absxr = t / sensorFusion_B.scale * 0.5F;
    }
  }

  if (sensorFusion_B.scale == 0.0F) {
    sensorFusion_B.absxk = 1.0F / absxr;
    sensorFusion_B.scale = 0.0F;
  } else if (absxr == 0.0F) {
    sensorFusion_B.absxk = 0.0F;
    sensorFusion_B.scale = -(1.0F / sensorFusion_B.scale);
  } else {
    t = (real32_T)fabs(absxr);
    sensorFusion_B.absxk = (real32_T)fabs(sensorFusion_B.scale);
    if (t > sensorFusion_B.absxk) {
      t = sensorFusion_B.scale / absxr;
      sensorFusion_B.scale = t * sensorFusion_B.scale + absxr;
      sensorFusion_B.absxk = (t * 0.0F + 1.0F) / sensorFusion_B.scale;
      sensorFusion_B.scale = (0.0F - t) / sensorFusion_B.scale;
    } else if (sensorFusion_B.absxk == t) {
      absxr = absxr > 0.0F ? 0.5F : -0.5F;
      sensorFusion_B.scale = sensorFusion_B.scale > 0.0F ? 0.5F : -0.5F;
      sensorFusion_B.absxk = (0.0F * sensorFusion_B.scale + absxr) / t;
      sensorFusion_B.scale = (0.0F * absxr - sensorFusion_B.scale) / t;
    } else {
      t = absxr / sensorFusion_B.scale;
      sensorFusion_B.scale += t * absxr;
      sensorFusion_B.absxk = t / sensorFusion_B.scale;
      sensorFusion_B.scale = (t * 0.0F - 1.0F) / sensorFusion_B.scale;
    }
  }

  sensorFusion_B.s[0].re = ((s_idx_0_re - s_idx_1_re) - s_idx_2_re) + s_idx_3_re;
  sensorFusion_B.s[0].im = ((s_idx_0_im - s_idx_1_im) - s_idx_2_im) + s_idx_3_im;
  sensorFusion_B.s[3].re = ((q[0].re * q[1].re - q[0].im * q[1].im) + (q[2].re *
    q[3].re - q[2].im * q[3].im)) * 2.0F;
  sensorFusion_B.s[3].im = ((q[0].re * q[1].im + q[0].im * q[1].re) + (q[2].re *
    q[3].im + q[2].im * q[3].re)) * 2.0F;
  sensorFusion_B.s[6].re = ((q[0].re * q[2].re - q[0].im * q[2].im) - (q[1].re *
    q[3].re - q[1].im * q[3].im)) * 2.0F;
  sensorFusion_B.s[6].im = ((q[0].re * q[2].im + q[0].im * q[2].re) - (q[1].re *
    q[3].im + q[1].im * q[3].re)) * 2.0F;
  sensorFusion_B.s[1].re = ((q[0].re * q[1].re - q[0].im * q[1].im) - (q[2].re *
    q[3].re - q[2].im * q[3].im)) * 2.0F;
  sensorFusion_B.s[1].im = ((q[0].re * q[1].im + q[0].im * q[1].re) - (q[2].re *
    q[3].im + q[2].im * q[3].re)) * 2.0F;
  sensorFusion_B.s[4].re = ((-s_idx_0_re + s_idx_1_re) - s_idx_2_re) +
    s_idx_3_re;
  sensorFusion_B.s[4].im = ((-s_idx_0_im + s_idx_1_im) - s_idx_2_im) +
    s_idx_3_im;
  sensorFusion_B.s[7].re = ((q[1].re * q[2].re - q[1].im * q[2].im) + (q[3].re *
    q[0].re - q[3].im * q[0].im)) * 2.0F;
  sensorFusion_B.s[7].im = ((q[1].re * q[2].im + q[1].im * q[2].re) + (q[3].re *
    q[0].im + q[3].im * q[0].re)) * 2.0F;
  sensorFusion_B.s[2].re = ((q[0].re * q[2].re - q[0].im * q[2].im) + (q[1].re *
    q[3].re - q[1].im * q[3].im)) * 2.0F;
  sensorFusion_B.s[2].im = ((q[0].re * q[2].im + q[0].im * q[2].re) + (q[1].re *
    q[3].im + q[1].im * q[3].re)) * 2.0F;
  sensorFusion_B.s[5].re = ((q[1].re * q[2].re - q[1].im * q[2].im) - (q[3].re *
    q[0].re - q[3].im * q[0].im)) * 2.0F;
  sensorFusion_B.s[5].im = ((q[1].re * q[2].im + q[1].im * q[2].re) - (q[3].re *
    q[0].im + q[3].im * q[0].re)) * 2.0F;
  sensorFusion_B.s[8].re = ((-s_idx_0_re - s_idx_1_re) + s_idx_2_re) +
    s_idx_3_re;
  sensorFusion_B.s[8].im = ((-s_idx_0_im - s_idx_1_im) + s_idx_2_im) +
    s_idx_3_im;
  for (i = 0; i < 3; i++) {
    C[3 * i].re = sensorFusion_B.s[3 * i].re * sensorFusion_B.absxk -
      sensorFusion_B.s[3 * i].im * sensorFusion_B.scale;
    C[3 * i].im = sensorFusion_B.s[3 * i].im * sensorFusion_B.absxk +
      sensorFusion_B.s[3 * i].re * sensorFusion_B.scale;
    C[1 + 3 * i].re = sensorFusion_B.s[3 * i + 1].re * sensorFusion_B.absxk -
      sensorFusion_B.s[3 * i + 1].im * sensorFusion_B.scale;
    C[1 + 3 * i].im = sensorFusion_B.s[3 * i + 1].im * sensorFusion_B.absxk +
      sensorFusion_B.s[3 * i + 1].re * sensorFusion_B.scale;
    C[2 + 3 * i].re = sensorFusion_B.s[3 * i + 2].re * sensorFusion_B.absxk -
      sensorFusion_B.s[3 * i + 2].im * sensorFusion_B.scale;
    C[2 + 3 * i].im = sensorFusion_B.s[3 * i + 2].im * sensorFusion_B.absxk +
      sensorFusion_B.s[3 * i + 2].re * sensorFusion_B.scale;
  }
}

/* Function for MATLAB Function: '<S3>/MATLAB Function' */
static void sensorFusion_mrdivide(creal32_T A[24], const creal32_T B[36])
{
  int32_T jp;
  creal32_T b_A[36];
  int8_T ipiv[6];
  int32_T j;
  int32_T ix;
  int32_T c_ix;
  int32_T d;
  int32_T ijA;
  real32_T br;
  real32_T brm;
  real32_T bim;
  int32_T b_jAcol;
  int32_T b_kBcol;
  real32_T temp_re;
  real32_T temp_im;
  memcpy(&b_A[0], &B[0], 36U * sizeof(creal32_T));
  for (j = 0; j < 6; j++) {
    ipiv[j] = (int8_T)(1 + j);
  }

  for (j = 0; j < 5; j++) {
    jp = j * 7;
    b_jAcol = 0;
    ix = jp;
    temp_im = (real32_T)fabs(b_A[jp].re) + (real32_T)fabs(b_A[jp].im);
    for (b_kBcol = 2; b_kBcol <= 6 - j; b_kBcol++) {
      ix++;
      br = (real32_T)fabs(b_A[ix].re) + (real32_T)fabs(b_A[ix].im);
      if (br > temp_im) {
        b_jAcol = b_kBcol - 1;
        temp_im = br;
      }
    }

    if ((b_A[jp + b_jAcol].re != 0.0F) || (b_A[jp + b_jAcol].im != 0.0F)) {
      if (b_jAcol != 0) {
        ipiv[j] = (int8_T)((j + b_jAcol) + 1);
        ix = j;
        b_jAcol += j;
        for (b_kBcol = 0; b_kBcol < 6; b_kBcol++) {
          temp_re = b_A[ix].re;
          temp_im = b_A[ix].im;
          b_A[ix] = b_A[b_jAcol];
          b_A[b_jAcol].re = temp_re;
          b_A[b_jAcol].im = temp_im;
          ix += 6;
          b_jAcol += 6;
        }
      }

      b_jAcol = (jp - j) + 6;
      for (ix = jp + 1; ix + 1 <= b_jAcol; ix++) {
        temp_re = b_A[ix].re;
        brm = b_A[jp].re;
        if (b_A[jp].im == 0.0F) {
          if (b_A[ix].im == 0.0F) {
            b_A[ix].re /= b_A[jp].re;
            b_A[ix].im = 0.0F;
          } else if (b_A[ix].re == 0.0F) {
            b_A[ix].re = 0.0F;
            b_A[ix].im /= brm;
          } else {
            b_A[ix].re /= b_A[jp].re;
            b_A[ix].im /= brm;
          }
        } else if (b_A[jp].re == 0.0F) {
          if (b_A[ix].re == 0.0F) {
            b_A[ix].re = b_A[ix].im / b_A[jp].im;
            b_A[ix].im = 0.0F;
          } else if (b_A[ix].im == 0.0F) {
            b_A[ix].re = 0.0F;
            b_A[ix].im = -(temp_re / b_A[jp].im);
          } else {
            b_A[ix].re = b_A[ix].im / b_A[jp].im;
            b_A[ix].im = -(temp_re / b_A[jp].im);
          }
        } else {
          brm = (real32_T)fabs(b_A[jp].re);
          bim = (real32_T)fabs(b_A[jp].im);
          if (brm > bim) {
            brm = b_A[jp].im / b_A[jp].re;
            temp_im = brm * b_A[jp].im + b_A[jp].re;
            b_A[ix].re = (brm * b_A[ix].im + b_A[ix].re) / temp_im;
            b_A[ix].im = (b_A[ix].im - brm * temp_re) / temp_im;
          } else if (bim == brm) {
            temp_im = b_A[jp].re > 0.0F ? 0.5F : -0.5F;
            bim = b_A[jp].im > 0.0F ? 0.5F : -0.5F;
            b_A[ix].re = (b_A[ix].re * temp_im + b_A[ix].im * bim) / brm;
            b_A[ix].im = (b_A[ix].im * temp_im - temp_re * bim) / brm;
          } else {
            brm = b_A[jp].re / b_A[jp].im;
            temp_im = brm * b_A[jp].re + b_A[jp].im;
            b_A[ix].re = (brm * b_A[ix].re + b_A[ix].im) / temp_im;
            b_A[ix].im = (brm * b_A[ix].im - temp_re) / temp_im;
          }
        }
      }
    }

    b_jAcol = jp;
    ix = jp + 6;
    for (b_kBcol = 1; b_kBcol <= 5 - j; b_kBcol++) {
      if ((b_A[ix].re != 0.0F) || (b_A[ix].im != 0.0F)) {
        temp_re = -b_A[ix].re - b_A[ix].im * 0.0F;
        temp_im = b_A[ix].re * 0.0F + -b_A[ix].im;
        c_ix = jp + 1;
        d = (b_jAcol - j) + 12;
        for (ijA = 7 + b_jAcol; ijA + 1 <= d; ijA++) {
          brm = b_A[c_ix].re * temp_im + b_A[c_ix].im * temp_re;
          b_A[ijA].re += b_A[c_ix].re * temp_re - b_A[c_ix].im * temp_im;
          b_A[ijA].im += brm;
          c_ix++;
        }
      }

      ix += 6;
      b_jAcol += 6;
    }
  }

  for (j = 0; j < 6; j++) {
    jp = j << 2;
    b_jAcol = 6 * j;
    for (ix = 1; ix <= j; ix++) {
      b_kBcol = (ix - 1) << 2;
      if ((b_A[(ix + b_jAcol) - 1].re != 0.0F) || (b_A[(ix + b_jAcol) - 1].im !=
           0.0F)) {
        brm = b_A[(ix + b_jAcol) - 1].re * A[b_kBcol].im + b_A[(ix + b_jAcol) -
          1].im * A[b_kBcol].re;
        A[jp].re -= b_A[(ix + b_jAcol) - 1].re * A[b_kBcol].re - b_A[(ix +
          b_jAcol) - 1].im * A[b_kBcol].im;
        A[jp].im -= brm;
        brm = b_A[(ix + b_jAcol) - 1].re * A[1 + b_kBcol].im + b_A[(ix + b_jAcol)
          - 1].im * A[1 + b_kBcol].re;
        A[1 + jp].re -= b_A[(ix + b_jAcol) - 1].re * A[1 + b_kBcol].re - b_A[(ix
          + b_jAcol) - 1].im * A[1 + b_kBcol].im;
        A[1 + jp].im -= brm;
        brm = b_A[(ix + b_jAcol) - 1].re * A[2 + b_kBcol].im + b_A[(ix + b_jAcol)
          - 1].im * A[2 + b_kBcol].re;
        A[2 + jp].re -= b_A[(ix + b_jAcol) - 1].re * A[2 + b_kBcol].re - b_A[(ix
          + b_jAcol) - 1].im * A[2 + b_kBcol].im;
        A[2 + jp].im -= brm;
        brm = b_A[(ix + b_jAcol) - 1].re * A[3 + b_kBcol].im + b_A[(ix + b_jAcol)
          - 1].im * A[3 + b_kBcol].re;
        A[3 + jp].re -= b_A[(ix + b_jAcol) - 1].re * A[3 + b_kBcol].re - b_A[(ix
          + b_jAcol) - 1].im * A[3 + b_kBcol].im;
        A[3 + jp].im -= brm;
      }
    }

    temp_re = b_A[j + b_jAcol].re;
    temp_im = b_A[j + b_jAcol].im;
    brm = (real32_T)fabs(temp_re);
    bim = (real32_T)fabs(temp_im);
    if (temp_im == 0.0F) {
      temp_re = 1.0F / temp_re;
      temp_im = 0.0F;
    } else if (temp_re == 0.0F) {
      temp_re = 0.0F;
      temp_im = -1.0F / temp_im;
    } else if (brm > bim) {
      brm = temp_im / temp_re;
      temp_im = brm * temp_im + temp_re;
      temp_re = 1.0F / temp_im;
      temp_im = -brm / temp_im;
    } else if (brm == bim) {
      bim = 0.5F;
      if (temp_re < 0.0F) {
        bim = -0.5F;
      }

      br = 0.5F;
      if (temp_im < 0.0F) {
        br = -0.5F;
      }

      temp_re = bim / brm;
      temp_im = -br / brm;
    } else {
      brm = temp_re / temp_im;
      temp_im += brm * temp_re;
      temp_re = brm / temp_im;
      temp_im = -1.0F / temp_im;
    }

    brm = A[jp].re;
    bim = A[jp].im;
    A[jp].re = temp_re * brm - temp_im * bim;
    A[jp].im = temp_re * bim + temp_im * brm;
    brm = A[1 + jp].re;
    bim = A[1 + jp].im;
    A[1 + jp].re = temp_re * brm - temp_im * bim;
    A[1 + jp].im = temp_re * bim + temp_im * brm;
    brm = A[2 + jp].re;
    bim = A[2 + jp].im;
    A[2 + jp].re = temp_re * brm - temp_im * bim;
    A[2 + jp].im = temp_re * bim + temp_im * brm;
    brm = A[3 + jp].re;
    bim = A[3 + jp].im;
    A[3 + jp].re = temp_re * brm - temp_im * bim;
    A[3 + jp].im = temp_re * bim + temp_im * brm;
  }

  for (j = 5; j >= 0; j += -1) {
    jp = j << 2;
    b_jAcol = 6 * j - 1;
    for (ix = j + 2; ix < 7; ix++) {
      b_kBcol = (ix - 1) << 2;
      if ((b_A[ix + b_jAcol].re != 0.0F) || (b_A[ix + b_jAcol].im != 0.0F)) {
        brm = b_A[ix + b_jAcol].re * A[b_kBcol].im + b_A[ix + b_jAcol].im *
          A[b_kBcol].re;
        A[jp].re -= b_A[ix + b_jAcol].re * A[b_kBcol].re - b_A[ix + b_jAcol].im *
          A[b_kBcol].im;
        A[jp].im -= brm;
        brm = b_A[ix + b_jAcol].re * A[1 + b_kBcol].im + b_A[ix + b_jAcol].im *
          A[1 + b_kBcol].re;
        A[1 + jp].re -= b_A[ix + b_jAcol].re * A[1 + b_kBcol].re - b_A[ix +
          b_jAcol].im * A[1 + b_kBcol].im;
        A[1 + jp].im -= brm;
        brm = b_A[ix + b_jAcol].re * A[2 + b_kBcol].im + b_A[ix + b_jAcol].im *
          A[2 + b_kBcol].re;
        A[2 + jp].re -= b_A[ix + b_jAcol].re * A[2 + b_kBcol].re - b_A[ix +
          b_jAcol].im * A[2 + b_kBcol].im;
        A[2 + jp].im -= brm;
        brm = b_A[ix + b_jAcol].re * A[3 + b_kBcol].im + b_A[ix + b_jAcol].im *
          A[3 + b_kBcol].re;
        A[3 + jp].re -= b_A[ix + b_jAcol].re * A[3 + b_kBcol].re - b_A[ix +
          b_jAcol].im * A[3 + b_kBcol].im;
        A[3 + jp].im -= brm;
      }
    }
  }

  for (j = 4; j >= 0; j += -1) {
    if (j + 1 != ipiv[j]) {
      jp = ipiv[j] - 1;
      temp_re = A[j << 2].re;
      temp_im = A[j << 2].im;
      A[j << 2] = A[jp << 2];
      A[jp << 2].re = temp_re;
      A[jp << 2].im = temp_im;
      temp_re = A[(j << 2) + 1].re;
      temp_im = A[(j << 2) + 1].im;
      A[1 + (j << 2)] = A[(jp << 2) + 1];
      A[1 + (jp << 2)].re = temp_re;
      A[1 + (jp << 2)].im = temp_im;
      temp_re = A[(j << 2) + 2].re;
      temp_im = A[(j << 2) + 2].im;
      A[2 + (j << 2)] = A[(jp << 2) + 2];
      A[2 + (jp << 2)].re = temp_re;
      A[2 + (jp << 2)].im = temp_im;
      temp_re = A[(j << 2) + 3].re;
      temp_im = A[(j << 2) + 3].im;
      A[3 + (j << 2)] = A[(jp << 2) + 3];
      A[3 + (jp << 2)].re = temp_re;
      A[3 + (jp << 2)].im = temp_im;
    }
  }
}

/* Function for MATLAB Function: '<S3>/MATLAB Function' */
static real32_T sensorFusion_eps(const creal32_T x)
{
  real32_T r;
  sensorFusion_B.absxk_d = sensorFusion_rt_hypotf_snf(x.re, x.im);
  if ((!rtIsInfF(sensorFusion_B.absxk_d)) && (!rtIsNaNF(sensorFusion_B.absxk_d)))
  {
    if (sensorFusion_B.absxk_d <= 1.17549435E-38F) {
      r = 1.4013E-45F;
    } else {
      frexp(sensorFusion_B.absxk_d, &sensorFusion_B.exponent);
      r = (real32_T)ldexp(1.0F, sensorFusion_B.exponent - 24);
    }
  } else {
    r = (rtNaNF);
  }

  return r;
}

/*
 * Function for MATLAB Function: '<S3>/MATLAB Function'
 * function [zNew,jacobian]=measurementFcn(x,g,h,doJacobian)
 */
static void sensorFusion_measurementFcn(const creal32_T x[4], const real_T g[3],
  const real_T h[3], creal32_T zNew[6])
{
  /* '<S5>:1:61' b_C_n=getC(x(1:4)); */
  sensorFusion_getC(x, sensorFusion_B.b_C_n_m);

  /* '<S5>:1:63' zNew=blkdiag(b_C_n,b_C_n)*[g;h]; */
  memset(&sensorFusion_B.y[0], 0, 36U * sizeof(creal32_T));
  for (sensorFusion_B.i3 = 0; sensorFusion_B.i3 < 3; sensorFusion_B.i3++) {
    sensorFusion_B.y[6 * sensorFusion_B.i3] = sensorFusion_B.b_C_n_m[3 *
      sensorFusion_B.i3];
    sensorFusion_B.y[3 + 6 * (3 + sensorFusion_B.i3)] = sensorFusion_B.b_C_n_m[3
      * sensorFusion_B.i3];
    sensorFusion_B.y[1 + 6 * sensorFusion_B.i3] = sensorFusion_B.b_C_n_m[3 *
      sensorFusion_B.i3 + 1];
    sensorFusion_B.y[4 + 6 * (3 + sensorFusion_B.i3)] = sensorFusion_B.b_C_n_m[3
      * sensorFusion_B.i3 + 1];
    sensorFusion_B.y[2 + 6 * sensorFusion_B.i3] = sensorFusion_B.b_C_n_m[3 *
      sensorFusion_B.i3 + 2];
    sensorFusion_B.y[5 + 6 * (3 + sensorFusion_B.i3)] = sensorFusion_B.b_C_n_m[3
      * sensorFusion_B.i3 + 2];
    sensorFusion_B.g_n[sensorFusion_B.i3] = (real32_T)g[sensorFusion_B.i3];
    sensorFusion_B.g_n[sensorFusion_B.i3 + 3] = (real32_T)h[sensorFusion_B.i3];
  }

  for (sensorFusion_B.i3 = 0; sensorFusion_B.i3 < 6; sensorFusion_B.i3++) {
    sensorFusion_B.g[sensorFusion_B.i3].re =
      sensorFusion_B.g_n[sensorFusion_B.i3];
    sensorFusion_B.g[sensorFusion_B.i3].im = 0.0F;
  }

  for (sensorFusion_B.i3 = 0; sensorFusion_B.i3 < 6; sensorFusion_B.i3++) {
    zNew[sensorFusion_B.i3].re = 0.0F;
    zNew[sensorFusion_B.i3].im = 0.0F;
    for (sensorFusion_B.i4 = 0; sensorFusion_B.i4 < 6; sensorFusion_B.i4++) {
      sensorFusion_B.zNew.re = (sensorFusion_B.y[6 * sensorFusion_B.i4 +
        sensorFusion_B.i3].re * sensorFusion_B.g[sensorFusion_B.i4].re -
        sensorFusion_B.y[6 * sensorFusion_B.i4 + sensorFusion_B.i3].im *
        sensorFusion_B.g[sensorFusion_B.i4].im) + zNew[sensorFusion_B.i3].re;
      sensorFusion_B.zNew.im = (sensorFusion_B.y[6 * sensorFusion_B.i4 +
        sensorFusion_B.i3].re * sensorFusion_B.g[sensorFusion_B.i4].im +
        sensorFusion_B.y[6 * sensorFusion_B.i4 + sensorFusion_B.i3].im *
        sensorFusion_B.g[sensorFusion_B.i4].re) + zNew[sensorFusion_B.i3].im;
      zNew[sensorFusion_B.i3] = sensorFusion_B.zNew;
    }
  }

  /* '<S5>:1:65' if ~doJacobian */
}

/*
 * Function for MATLAB Function: '<S3>/MATLAB Function'
 * function [xNew,jacobian]=stateUpdateFcn(Ts,x,w,doJacobian)
 */
static void sensorFusion_stateUpdateFcn(real_T Ts, const creal32_T x[4], const
  real32_T w[3], boolean_T doJacobian, creal32_T xNew[4])
{
  creal32_T xtemp[4];
  int32_T i;
  creal32_T varargin_1[16];
  real32_T y;
  creal32_T tmp[16];
  real32_T tmp_0[16];
  creal32_T xNew_0;
  creal32_T unusedExpr[4];

  /* '<S5>:1:37' wX=[0       -w(3)   w(2) */
  /* '<S5>:1:38'     w(3)    0       -w(1) */
  /* '<S5>:1:39'     -w(2)   w(1)    0]; */
  /* '<S5>:1:40' OMEGA=complex(.5*[wX  w */
  /* '<S5>:1:41'           -w' 0]); */
  /* '<S5>:1:43' xNew=blkdiag(expm(OMEGA*Ts))*x; */
  tmp_0[0] = 0.0F;
  tmp_0[4] = -w[2];
  tmp_0[8] = w[1];
  tmp_0[1] = w[2];
  tmp_0[5] = 0.0F;
  tmp_0[9] = -w[0];
  tmp_0[2] = -w[1];
  tmp_0[6] = w[0];
  tmp_0[10] = 0.0F;
  tmp_0[12] = w[0];
  tmp_0[3] = -w[0];
  tmp_0[13] = w[1];
  tmp_0[7] = -w[1];
  tmp_0[14] = w[2];
  tmp_0[11] = -w[2];
  tmp_0[15] = 0.0F;
  for (i = 0; i < 4; i++) {
    tmp[i << 2].re = tmp_0[i << 2] * 0.5F * (real32_T)Ts;
    tmp[i << 2].im = (real32_T)Ts * 0.0F;
    tmp[1 + (i << 2)].re = tmp_0[(i << 2) + 1] * 0.5F * (real32_T)Ts;
    tmp[1 + (i << 2)].im = (real32_T)Ts * 0.0F;
    tmp[2 + (i << 2)].re = tmp_0[(i << 2) + 2] * 0.5F * (real32_T)Ts;
    tmp[2 + (i << 2)].im = (real32_T)Ts * 0.0F;
    tmp[3 + (i << 2)].re = tmp_0[(i << 2) + 3] * 0.5F * (real32_T)Ts;
    tmp[3 + (i << 2)].im = (real32_T)Ts * 0.0F;
  }

  sensorFusion_expm(tmp, varargin_1);
  for (i = 0; i < 4; i++) {
    xNew_0.re = varargin_1[i].re * x[0].re - varargin_1[i].im * x[0].im;
    xNew_0.im = varargin_1[i].re * x[0].im + varargin_1[i].im * x[0].re;
    xNew_0.re += varargin_1[i + 4].re * x[1].re - varargin_1[i + 4].im * x[1].im;
    xNew_0.im += varargin_1[i + 4].re * x[1].im + varargin_1[i + 4].im * x[1].re;
    xNew_0.re += varargin_1[i + 8].re * x[2].re - varargin_1[i + 8].im * x[2].im;
    xNew_0.im += varargin_1[i + 8].re * x[2].im + varargin_1[i + 8].im * x[2].re;
    xNew_0.re += varargin_1[i + 12].re * x[3].re - varargin_1[i + 12].im * x[3].
      im;
    xNew_0.im += varargin_1[i + 12].re * x[3].im + varargin_1[i + 12].im * x[3].
      re;
    xNew[i] = xNew_0;
  }

  /* '<S5>:1:44' xNew(1:4)=xNew(1:4)./norm(xNew(1:4)); */
  y = sensorFusion_norm(xNew);
  if (xNew[0].im == 0.0F) {
    xNew[0].re /= y;
    xNew[0].im = 0.0F;
  } else if (xNew[0].re == 0.0F) {
    xNew[0].re = 0.0F;
    xNew[0].im /= y;
  } else {
    xNew[0].re /= y;
    xNew[0].im /= y;
  }

  if (xNew[1].im == 0.0F) {
    xNew[1].re /= y;
    xNew[1].im = 0.0F;
  } else if (xNew[1].re == 0.0F) {
    xNew[1].re = 0.0F;
    xNew[1].im /= y;
  } else {
    xNew[1].re /= y;
    xNew[1].im /= y;
  }

  if (xNew[2].im == 0.0F) {
    xNew[2].re /= y;
    xNew[2].im = 0.0F;
  } else if (xNew[2].re == 0.0F) {
    xNew[2].re = 0.0F;
    xNew[2].im /= y;
  } else {
    xNew[2].re /= y;
    xNew[2].im /= y;
  }

  if (xNew[3].im == 0.0F) {
    xNew[3].re /= y;
    xNew[3].im = 0.0F;
  } else if (xNew[3].re == 0.0F) {
    xNew[3].re = 0.0F;
    xNew[3].im /= y;
  } else {
    xNew[3].re /= y;
    xNew[3].im /= y;
  }

  /* '<S5>:1:46' if ~doJacobian */
  if (doJacobian) {
    /* '<S5>:1:50' jacobian=zeros(size(xNew,1),size(xNew,1)); */
    /* '<S5>:1:52' for i=1:length(x) */
    for (i = 0; i < 4; i++) {
      /* '<S5>:1:53' dx=100*eps(xNew(i)); */
      /* '<S5>:1:54' xtemp=xNew; */
      xtemp[0] = xNew[0];
      xtemp[1] = xNew[1];
      xtemp[2] = xNew[2];
      xtemp[3] = xNew[3];

      /* '<S5>:1:55' xtemp(i)=xtemp(i)+dx*1i; */
      xtemp[i].re = 100.0F * sensorFusion_eps(xNew[i]) * 0.0F + xNew[i].re;
      xtemp[i].im = 100.0F * sensorFusion_eps(xNew[i]) + xNew[i].im;

      /* '<S5>:1:56' jacobian(:,i)=imag(stateUpdateFcn(Ts,xtemp,w,false))./dx; */
      sensorFusion_stateUpdateFcn(Ts, xtemp, w, false, unusedExpr);
    }
  }
}

/* Model step function */
void sensorFusion_step(void)
{
  char_T *sErr;
  static const int8_T e[9] = { 1, 0, 0, 0, 1, 0, 0, 0, 1 };

  real32_T *rtb_MathFunction1_0;

  /* Reset subsysRan breadcrumbs */
  srClearBC(sensorFusion_DW.runSensorFusion_SubsysRanBC);

  /* S-Function (sdspFromNetwork): '<Root>/UDP Receive' */
  sErr = GetErrorBuffer(&sensorFusion_DW.UDPReceive_NetworkLib[0U]);
  sensorFusion_B.s3_iter = 32;
  LibOutputs_Network(&sensorFusion_DW.UDPReceive_NetworkLib[0U],
                     &sensorFusion_B.UDPReceive_o1[0U], &sensorFusion_B.s3_iter);
  if (*sErr != 0) {
    rtmSetErrorStatus(sensorFusion_M, sErr);
    rtmSetStopRequested(sensorFusion_M, 1);
  }

  sensorFusion_B.UDPReceive_o2 = (uint16_T)sensorFusion_B.s3_iter;

  /* End of S-Function (sdspFromNetwork): '<Root>/UDP Receive' */

  /* RelationalOperator: '<S1>/Compare' incorporates:
   *  Constant: '<S1>/Constant'
   */
  sensorFusion_B.Compare = (sensorFusion_B.UDPReceive_o2 >
    sensorFusion_P.Constant_Value_h);

  /* Outputs for Triggered SubSystem: '<Root>/runSensorFusion' incorporates:
   *  TriggerPort: '<S2>/Trigger'
   */
  if (sensorFusion_B.Compare && (sensorFusion_PrevZCX.runSensorFusion_Trig_ZCE
       != POS_ZCSIG)) {
    /* Math: '<S4>/Math Function1' */
    rtb_MathFunction1_0 = &sensorFusion_B.UDPReceive_o1[0];

    /* Concatenate: '<S4>/Matrix Concatenate1' */
    sensorFusion_B.MatrixConcatenate1[0] = rtb_MathFunction1_0[0];
    sensorFusion_B.MatrixConcatenate1[1] = rtb_MathFunction1_0[4];
    sensorFusion_B.MatrixConcatenate1[2] = rtb_MathFunction1_0[8];

    /* Concatenate: '<S4>/Matrix Concatenate2' */
    sensorFusion_B.MatrixConcatenate2[0] = rtb_MathFunction1_0[12];
    sensorFusion_B.MatrixConcatenate2[1] = rtb_MathFunction1_0[16];
    sensorFusion_B.MatrixConcatenate2[2] = rtb_MathFunction1_0[20];

    /* Concatenate: '<S4>/Matrix Concatenate1' */
    sensorFusion_B.MatrixConcatenate1[3] = rtb_MathFunction1_0[1];
    sensorFusion_B.MatrixConcatenate1[4] = rtb_MathFunction1_0[5];
    sensorFusion_B.MatrixConcatenate1[5] = rtb_MathFunction1_0[9];

    /* Concatenate: '<S4>/Matrix Concatenate2' */
    sensorFusion_B.MatrixConcatenate2[3] = rtb_MathFunction1_0[13];
    sensorFusion_B.MatrixConcatenate2[4] = rtb_MathFunction1_0[17];
    sensorFusion_B.MatrixConcatenate2[5] = rtb_MathFunction1_0[21];

    /* Concatenate: '<S4>/Matrix Concatenate1' */
    sensorFusion_B.MatrixConcatenate1[6] = rtb_MathFunction1_0[2];
    sensorFusion_B.MatrixConcatenate1[7] = rtb_MathFunction1_0[6];
    sensorFusion_B.MatrixConcatenate1[8] = rtb_MathFunction1_0[10];

    /* Concatenate: '<S4>/Matrix Concatenate2' */
    sensorFusion_B.MatrixConcatenate2[6] = rtb_MathFunction1_0[14];
    sensorFusion_B.MatrixConcatenate2[7] = rtb_MathFunction1_0[18];
    sensorFusion_B.MatrixConcatenate2[8] = rtb_MathFunction1_0[22];

    /* Concatenate: '<S4>/Matrix Concatenate1' */
    sensorFusion_B.MatrixConcatenate1[9] = rtb_MathFunction1_0[3];
    sensorFusion_B.MatrixConcatenate1[10] = rtb_MathFunction1_0[7];
    sensorFusion_B.MatrixConcatenate1[11] = rtb_MathFunction1_0[11];

    /* Concatenate: '<S4>/Matrix Concatenate2' */
    sensorFusion_B.MatrixConcatenate2[9] = rtb_MathFunction1_0[15];
    sensorFusion_B.MatrixConcatenate2[10] = rtb_MathFunction1_0[19];
    sensorFusion_B.MatrixConcatenate2[11] = rtb_MathFunction1_0[23];

    /* Math: '<S4>/Math Function' */
    for (sensorFusion_B.i = 0; sensorFusion_B.i < 6; sensorFusion_B.i++) {
      sensorFusion_B.MathFunction[sensorFusion_B.i] =
        sensorFusion_B.UDPReceive_o1[sensorFusion_B.i + 24];
    }

    /* End of Math: '<S4>/Math Function' */

    /* Concatenate: '<S4>/Matrix Concatenate' */
    sensorFusion_B.MatrixConcatenate[0] = sensorFusion_B.MathFunction[0];
    sensorFusion_B.MatrixConcatenate[1] = sensorFusion_B.MathFunction[2];
    sensorFusion_B.MatrixConcatenate[2] = sensorFusion_B.MathFunction[4];
    sensorFusion_B.MatrixConcatenate[3] = sensorFusion_B.MathFunction[1];
    sensorFusion_B.MatrixConcatenate[4] = sensorFusion_B.MathFunction[3];
    sensorFusion_B.MatrixConcatenate[5] = sensorFusion_B.MathFunction[5];

    /* Outputs for Iterator SubSystem: '<S2>/iterateAlg' incorporates:
     *  ForIterator: '<S3>/For Iterator'
     */
    sensorFusion_B.s3_iter = 1;
    while (sensorFusion_B.s3_iter <= sensorFusion_P.ForIterator_IterationLimit)
    {
      /* Selector: '<S3>/Selector' */
      sensorFusion_B.accel[0] = sensorFusion_B.MatrixConcatenate1
        [(sensorFusion_B.s3_iter - 1) * 3];
      sensorFusion_B.accel[1] = sensorFusion_B.MatrixConcatenate1
        [(sensorFusion_B.s3_iter - 1) * 3 + 1];
      sensorFusion_B.accel[2] = sensorFusion_B.MatrixConcatenate1
        [(sensorFusion_B.s3_iter - 1) * 3 + 2];

      /* Bias: '<S3>/Bias' incorporates:
       *  Selector: '<S3>/Selector1'
       */
      sensorFusion_B.Bias[0] = sensorFusion_B.MatrixConcatenate2
        [(sensorFusion_B.s3_iter - 1) * 3] + sensorFusion_P.Bias_Bias[0];
      sensorFusion_B.Bias[1] = sensorFusion_B.MatrixConcatenate2
        [(sensorFusion_B.s3_iter - 1) * 3 + 1] + sensorFusion_P.Bias_Bias[1];
      sensorFusion_B.Bias[2] = sensorFusion_B.MatrixConcatenate2
        [(sensorFusion_B.s3_iter - 1) * 3 + 2] + sensorFusion_P.Bias_Bias[2];

      /* Switch: '<S3>/Switch' */
      if (sensorFusion_B.s3_iter > sensorFusion_P.Switch_Threshold) {
        /* Selector: '<S3>/Selector2' incorporates:
         *  Constant: '<S3>/Constant1'
         */
        sensorFusion_B.s3_iter_o = sensorFusion_P.Constant1_Value;
      } else {
        /* Selector: '<S3>/Selector2' incorporates:
         *  Constant: '<S3>/Constant'
         */
        sensorFusion_B.s3_iter_o = sensorFusion_P.Constant_Value;
      }

      /* End of Switch: '<S3>/Switch' */

      /* Selector: '<S3>/Selector2' */
      sensorFusion_B.mag[0] = sensorFusion_B.MatrixConcatenate
        [(sensorFusion_B.s3_iter_o - 1) * 3];
      sensorFusion_B.mag[1] = sensorFusion_B.MatrixConcatenate
        [(sensorFusion_B.s3_iter_o - 1) * 3 + 1];
      sensorFusion_B.mag[2] = sensorFusion_B.MatrixConcatenate
        [(sensorFusion_B.s3_iter_o - 1) * 3 + 2];

      /* MATLAB Function: '<S3>/MATLAB Function' incorporates:
       *  Constant: '<S3>/Constant2'
       *  Constant: '<S3>/Constant3'
       *  Constant: '<S3>/Constant4'
       *  Constant: '<S3>/Constant5'
       *  Constant: '<S3>/Constant6'
       *  UnitDelay: '<S3>/Unit Delay'
       *  UnitDelay: '<S3>/Unit Delay1'
       */
      /*  Update Q */
      /* MATLAB Function 'runSensorFusion/iterateAlg/MATLAB Function': '<S5>:1' */
      /* '<S5>:1:3' QqChi=[skew(x_last(1:3)) + x_last(4)*eye(3) */
      /* '<S5>:1:4'             -x_last(1:3)']; */
      /* '<S5>:1:79' s=[0       -w(3)   w(2) */
      /* '<S5>:1:80'     w(3)    0       -w(1) */
      /* '<S5>:1:81'     -w(2)   w(1)    0]; */
      sensorFusion_B.b_dx = sensorFusion_DW.UnitDelay_DSTATE[3].re;
      sensorFusion_B.u1 = sensorFusion_DW.UnitDelay_DSTATE[3].im;
      sensorFusion_B.b[0].re = 0.0F;
      sensorFusion_B.b[0].im = 0.0F;
      sensorFusion_B.b[3].re = -sensorFusion_DW.UnitDelay_DSTATE[2].re;
      sensorFusion_B.b[3].im = -sensorFusion_DW.UnitDelay_DSTATE[2].im;
      sensorFusion_B.b[6] = sensorFusion_DW.UnitDelay_DSTATE[1];
      sensorFusion_B.b[1] = sensorFusion_DW.UnitDelay_DSTATE[2];
      sensorFusion_B.b[4].re = 0.0F;
      sensorFusion_B.b[4].im = 0.0F;
      sensorFusion_B.b[7].re = -sensorFusion_DW.UnitDelay_DSTATE[0].re;
      sensorFusion_B.b[7].im = -sensorFusion_DW.UnitDelay_DSTATE[0].im;
      sensorFusion_B.b[2].re = -sensorFusion_DW.UnitDelay_DSTATE[1].re;
      sensorFusion_B.b[2].im = -sensorFusion_DW.UnitDelay_DSTATE[1].im;
      sensorFusion_B.b[5] = sensorFusion_DW.UnitDelay_DSTATE[0];
      sensorFusion_B.b[8].re = 0.0F;
      sensorFusion_B.b[8].im = 0.0F;
      for (sensorFusion_B.s3_iter_o = 0; sensorFusion_B.s3_iter_o < 3;
           sensorFusion_B.s3_iter_o++) {
        sensorFusion_B.QqChi[sensorFusion_B.s3_iter_o << 2].re = (real32_T)e[3 *
          sensorFusion_B.s3_iter_o] * sensorFusion_B.b_dx + sensorFusion_B.b[3 *
          sensorFusion_B.s3_iter_o].re;
        sensorFusion_B.QqChi[sensorFusion_B.s3_iter_o << 2].im = (real32_T)e[3 *
          sensorFusion_B.s3_iter_o] * sensorFusion_B.u1 + sensorFusion_B.b[3 *
          sensorFusion_B.s3_iter_o].im;
        sensorFusion_B.QqChi[1 + (sensorFusion_B.s3_iter_o << 2)].re = (real32_T)
          e[3 * sensorFusion_B.s3_iter_o + 1] * sensorFusion_B.b_dx +
          sensorFusion_B.b[3 * sensorFusion_B.s3_iter_o + 1].re;
        sensorFusion_B.QqChi[1 + (sensorFusion_B.s3_iter_o << 2)].im = (real32_T)
          e[3 * sensorFusion_B.s3_iter_o + 1] * sensorFusion_B.u1 +
          sensorFusion_B.b[3 * sensorFusion_B.s3_iter_o + 1].im;
        sensorFusion_B.QqChi[2 + (sensorFusion_B.s3_iter_o << 2)].re = (real32_T)
          e[3 * sensorFusion_B.s3_iter_o + 2] * sensorFusion_B.b_dx +
          sensorFusion_B.b[3 * sensorFusion_B.s3_iter_o + 2].re;
        sensorFusion_B.QqChi[2 + (sensorFusion_B.s3_iter_o << 2)].im = (real32_T)
          e[3 * sensorFusion_B.s3_iter_o + 2] * sensorFusion_B.u1 +
          sensorFusion_B.b[3 * sensorFusion_B.s3_iter_o + 2].im;
        sensorFusion_B.QqChi[3 + (sensorFusion_B.s3_iter_o << 2)].re =
          -sensorFusion_DW.UnitDelay_DSTATE[sensorFusion_B.s3_iter_o].re;
        sensorFusion_B.QqChi[3 + (sensorFusion_B.s3_iter_o << 2)].im =
          -(-sensorFusion_DW.UnitDelay_DSTATE[sensorFusion_B.s3_iter_o].im);
      }

      /* '<S5>:1:5' Q=blkdiag((Ts/2)^2*QqChi*diag(Ra)*(QqChi')); */
      sensorFusion_B.y_p = sensorFusion_P.Constant6_Value / 2.0;
      sensorFusion_B.y_p *= sensorFusion_B.y_p;
      memset(&sensorFusion_B.d[0], 0, 9U * sizeof(real_T));
      sensorFusion_B.d[0] = sensorFusion_P.aVar[0];
      sensorFusion_B.d[4] = sensorFusion_P.aVar[1];
      sensorFusion_B.d[8] = sensorFusion_P.aVar[2];

      /* '<S5>:1:6' R=single(zeros(6)); */
      memset(&sensorFusion_B.R[0], 0, 36U * sizeof(real32_T));

      /* '<S5>:1:7' R(1,1)=Ra(1); */
      sensorFusion_B.R[0] = (real32_T)sensorFusion_P.aVar[0];

      /* '<S5>:1:8' R(2,2)=Ra(2); */
      sensorFusion_B.R[7] = (real32_T)sensorFusion_P.aVar[1];

      /* '<S5>:1:9' R(3,3)=Ra(3); */
      sensorFusion_B.R[14] = (real32_T)sensorFusion_P.aVar[2];

      /* '<S5>:1:10' R(4,4)=Rm(1); */
      sensorFusion_B.R[21] = (real32_T)sensorFusion_P.mVar[0];

      /* '<S5>:1:11' R(5,5)=Rm(2); */
      sensorFusion_B.R[28] = (real32_T)sensorFusion_P.mVar[1];

      /* '<S5>:1:12' R(6,6)=Rm(3); */
      sensorFusion_B.R[35] = (real32_T)sensorFusion_P.mVar[2];

      /*  Update Apriori Estimate and State Update Jacobian */
      /* '<S5>:1:15' [x_apriori,A]=stateUpdateFcn(Ts,x_last,w,true); */
      /* '<S5>:1:37' wX=[0       -w(3)   w(2) */
      /* '<S5>:1:38'     w(3)    0       -w(1) */
      /* '<S5>:1:39'     -w(2)   w(1)    0]; */
      /* '<S5>:1:40' OMEGA=complex(.5*[wX  w */
      /* '<S5>:1:41'           -w' 0]); */
      /* '<S5>:1:43' xNew=blkdiag(expm(OMEGA*Ts))*x; */
      sensorFusion_B.fv0[0] = 0.0F;
      sensorFusion_B.fv0[4] = -sensorFusion_B.Bias[2];
      sensorFusion_B.fv0[8] = sensorFusion_B.Bias[1];
      sensorFusion_B.fv0[1] = sensorFusion_B.Bias[2];
      sensorFusion_B.fv0[5] = 0.0F;
      sensorFusion_B.fv0[9] = -sensorFusion_B.Bias[0];
      sensorFusion_B.fv0[2] = -sensorFusion_B.Bias[1];
      sensorFusion_B.fv0[6] = sensorFusion_B.Bias[0];
      sensorFusion_B.fv0[10] = 0.0F;
      sensorFusion_B.fv0[12] = sensorFusion_B.Bias[0];
      sensorFusion_B.fv0[3] = -sensorFusion_B.Bias[0];
      sensorFusion_B.fv0[13] = sensorFusion_B.Bias[1];
      sensorFusion_B.fv0[7] = -sensorFusion_B.Bias[1];
      sensorFusion_B.fv0[14] = sensorFusion_B.Bias[2];
      sensorFusion_B.fv0[11] = -sensorFusion_B.Bias[2];
      sensorFusion_B.fv0[15] = 0.0F;
      for (sensorFusion_B.s3_iter_o = 0; sensorFusion_B.s3_iter_o < 4;
           sensorFusion_B.s3_iter_o++) {
        sensorFusion_B.A_b[sensorFusion_B.s3_iter_o << 2].re =
          sensorFusion_B.fv0[sensorFusion_B.s3_iter_o << 2] * 0.5F * (real32_T)
          sensorFusion_P.Constant6_Value;
        sensorFusion_B.A_b[sensorFusion_B.s3_iter_o << 2].im = (real32_T)
          sensorFusion_P.Constant6_Value * 0.0F;
        sensorFusion_B.A_b[1 + (sensorFusion_B.s3_iter_o << 2)].re =
          sensorFusion_B.fv0[(sensorFusion_B.s3_iter_o << 2) + 1] * 0.5F *
          (real32_T)sensorFusion_P.Constant6_Value;
        sensorFusion_B.A_b[1 + (sensorFusion_B.s3_iter_o << 2)].im = (real32_T)
          sensorFusion_P.Constant6_Value * 0.0F;
        sensorFusion_B.A_b[2 + (sensorFusion_B.s3_iter_o << 2)].re =
          sensorFusion_B.fv0[(sensorFusion_B.s3_iter_o << 2) + 2] * 0.5F *
          (real32_T)sensorFusion_P.Constant6_Value;
        sensorFusion_B.A_b[2 + (sensorFusion_B.s3_iter_o << 2)].im = (real32_T)
          sensorFusion_P.Constant6_Value * 0.0F;
        sensorFusion_B.A_b[3 + (sensorFusion_B.s3_iter_o << 2)].re =
          sensorFusion_B.fv0[(sensorFusion_B.s3_iter_o << 2) + 3] * 0.5F *
          (real32_T)sensorFusion_P.Constant6_Value;
        sensorFusion_B.A_b[3 + (sensorFusion_B.s3_iter_o << 2)].im = (real32_T)
          sensorFusion_P.Constant6_Value * 0.0F;
      }

      sensorFusion_expm(sensorFusion_B.A_b, sensorFusion_B.P_apriori);
      for (sensorFusion_B.s3_iter_o = 0; sensorFusion_B.s3_iter_o < 4;
           sensorFusion_B.s3_iter_o++) {
        sensorFusion_B.x_apriori_l.re =
          sensorFusion_B.P_apriori[sensorFusion_B.s3_iter_o].re *
          sensorFusion_DW.UnitDelay_DSTATE[0].re -
          sensorFusion_B.P_apriori[sensorFusion_B.s3_iter_o].im *
          sensorFusion_DW.UnitDelay_DSTATE[0].im;
        sensorFusion_B.x_apriori_l.im =
          sensorFusion_B.P_apriori[sensorFusion_B.s3_iter_o].re *
          sensorFusion_DW.UnitDelay_DSTATE[0].im +
          sensorFusion_B.P_apriori[sensorFusion_B.s3_iter_o].im *
          sensorFusion_DW.UnitDelay_DSTATE[0].re;
        sensorFusion_B.x_apriori_l.re +=
          sensorFusion_B.P_apriori[sensorFusion_B.s3_iter_o + 4].re *
          sensorFusion_DW.UnitDelay_DSTATE[1].re -
          sensorFusion_B.P_apriori[sensorFusion_B.s3_iter_o + 4].im *
          sensorFusion_DW.UnitDelay_DSTATE[1].im;
        sensorFusion_B.x_apriori_l.im +=
          sensorFusion_B.P_apriori[sensorFusion_B.s3_iter_o + 4].re *
          sensorFusion_DW.UnitDelay_DSTATE[1].im +
          sensorFusion_B.P_apriori[sensorFusion_B.s3_iter_o + 4].im *
          sensorFusion_DW.UnitDelay_DSTATE[1].re;
        sensorFusion_B.x_apriori_l.re +=
          sensorFusion_B.P_apriori[sensorFusion_B.s3_iter_o + 8].re *
          sensorFusion_DW.UnitDelay_DSTATE[2].re -
          sensorFusion_B.P_apriori[sensorFusion_B.s3_iter_o + 8].im *
          sensorFusion_DW.UnitDelay_DSTATE[2].im;
        sensorFusion_B.x_apriori_l.im +=
          sensorFusion_B.P_apriori[sensorFusion_B.s3_iter_o + 8].re *
          sensorFusion_DW.UnitDelay_DSTATE[2].im +
          sensorFusion_B.P_apriori[sensorFusion_B.s3_iter_o + 8].im *
          sensorFusion_DW.UnitDelay_DSTATE[2].re;
        sensorFusion_B.x_apriori_l.re +=
          sensorFusion_B.P_apriori[sensorFusion_B.s3_iter_o + 12].re *
          sensorFusion_DW.UnitDelay_DSTATE[3].re -
          sensorFusion_B.P_apriori[sensorFusion_B.s3_iter_o + 12].im *
          sensorFusion_DW.UnitDelay_DSTATE[3].im;
        sensorFusion_B.x_apriori_l.im +=
          sensorFusion_B.P_apriori[sensorFusion_B.s3_iter_o + 12].re *
          sensorFusion_DW.UnitDelay_DSTATE[3].im +
          sensorFusion_B.P_apriori[sensorFusion_B.s3_iter_o + 12].im *
          sensorFusion_DW.UnitDelay_DSTATE[3].re;
        sensorFusion_B.x_apriori[sensorFusion_B.s3_iter_o] =
          sensorFusion_B.x_apriori_l;
      }

      /* '<S5>:1:44' xNew(1:4)=xNew(1:4)./norm(xNew(1:4)); */
      sensorFusion_B.b_dx = sensorFusion_norm(sensorFusion_B.x_apriori);
      if (sensorFusion_B.x_apriori[0].im == 0.0F) {
        sensorFusion_B.x_apriori[0].re /= sensorFusion_B.b_dx;
        sensorFusion_B.x_apriori[0].im = 0.0F;
      } else if (sensorFusion_B.x_apriori[0].re == 0.0F) {
        sensorFusion_B.x_apriori[0].re = 0.0F;
        sensorFusion_B.x_apriori[0].im /= sensorFusion_B.b_dx;
      } else {
        sensorFusion_B.x_apriori[0].re /= sensorFusion_B.b_dx;
        sensorFusion_B.x_apriori[0].im /= sensorFusion_B.b_dx;
      }

      if (sensorFusion_B.x_apriori[1].im == 0.0F) {
        sensorFusion_B.x_apriori[1].re /= sensorFusion_B.b_dx;
        sensorFusion_B.x_apriori[1].im = 0.0F;
      } else if (sensorFusion_B.x_apriori[1].re == 0.0F) {
        sensorFusion_B.x_apriori[1].re = 0.0F;
        sensorFusion_B.x_apriori[1].im /= sensorFusion_B.b_dx;
      } else {
        sensorFusion_B.x_apriori[1].re /= sensorFusion_B.b_dx;
        sensorFusion_B.x_apriori[1].im /= sensorFusion_B.b_dx;
      }

      if (sensorFusion_B.x_apriori[2].im == 0.0F) {
        sensorFusion_B.x_apriori[2].re /= sensorFusion_B.b_dx;
        sensorFusion_B.x_apriori[2].im = 0.0F;
      } else if (sensorFusion_B.x_apriori[2].re == 0.0F) {
        sensorFusion_B.x_apriori[2].re = 0.0F;
        sensorFusion_B.x_apriori[2].im /= sensorFusion_B.b_dx;
      } else {
        sensorFusion_B.x_apriori[2].re /= sensorFusion_B.b_dx;
        sensorFusion_B.x_apriori[2].im /= sensorFusion_B.b_dx;
      }

      if (sensorFusion_B.x_apriori[3].im == 0.0F) {
        sensorFusion_B.x_apriori[3].re /= sensorFusion_B.b_dx;
        sensorFusion_B.x_apriori[3].im = 0.0F;
      } else if (sensorFusion_B.x_apriori[3].re == 0.0F) {
        sensorFusion_B.x_apriori[3].re = 0.0F;
        sensorFusion_B.x_apriori[3].im /= sensorFusion_B.b_dx;
      } else {
        sensorFusion_B.x_apriori[3].re /= sensorFusion_B.b_dx;
        sensorFusion_B.x_apriori[3].im /= sensorFusion_B.b_dx;
      }

      /* '<S5>:1:46' if ~doJacobian */
      /* '<S5>:1:50' jacobian=zeros(size(xNew,1),size(xNew,1)); */
      /* '<S5>:1:52' for i=1:length(x) */
      for (sensorFusion_B.i = 0; sensorFusion_B.i < 4; sensorFusion_B.i++) {
        /* '<S5>:1:53' dx=100*eps(xNew(i)); */
        sensorFusion_B.b_dx = 100.0F * sensorFusion_eps
          (sensorFusion_B.x_apriori[sensorFusion_B.i]);

        /* '<S5>:1:54' xtemp=xNew; */
        sensorFusion_B.xtemp[0] = sensorFusion_B.x_apriori[0];
        sensorFusion_B.xtemp[1] = sensorFusion_B.x_apriori[1];
        sensorFusion_B.xtemp[2] = sensorFusion_B.x_apriori[2];
        sensorFusion_B.xtemp[3] = sensorFusion_B.x_apriori[3];

        /* '<S5>:1:55' xtemp(i)=xtemp(i)+dx*1i; */
        sensorFusion_B.xtemp[sensorFusion_B.i].re = sensorFusion_B.b_dx * 0.0F +
          sensorFusion_B.x_apriori[sensorFusion_B.i].re;
        sensorFusion_B.xtemp[sensorFusion_B.i].im =
          sensorFusion_B.x_apriori[sensorFusion_B.i].im + sensorFusion_B.b_dx;

        /* '<S5>:1:56' jacobian(:,i)=imag(stateUpdateFcn(Ts,xtemp,w,false))./dx; */
        sensorFusion_stateUpdateFcn(sensorFusion_P.Constant6_Value,
          sensorFusion_B.xtemp, sensorFusion_B.Bias, false, sensorFusion_B.x);
        sensorFusion_B.A[sensorFusion_B.i << 2] = sensorFusion_B.x[0].im /
          sensorFusion_B.b_dx;
        sensorFusion_B.A[1 + (sensorFusion_B.i << 2)] = sensorFusion_B.x[1].im /
          sensorFusion_B.b_dx;
        sensorFusion_B.A[2 + (sensorFusion_B.i << 2)] = sensorFusion_B.x[2].im /
          sensorFusion_B.b_dx;
        sensorFusion_B.A[3 + (sensorFusion_B.i << 2)] = sensorFusion_B.x[3].im /
          sensorFusion_B.b_dx;
      }

      /*  Update apriori Error Covariance Estimate */
      /* '<S5>:1:18' P_apriori = A*P_last*A' + Q; */
      for (sensorFusion_B.s3_iter_o = 0; sensorFusion_B.s3_iter_o < 4;
           sensorFusion_B.s3_iter_o++) {
        sensorFusion_B.A_b[sensorFusion_B.s3_iter_o << 2].re = (real32_T)
          sensorFusion_B.A[sensorFusion_B.s3_iter_o << 2];
        sensorFusion_B.A_b[sensorFusion_B.s3_iter_o << 2].im = 0.0F;
        sensorFusion_B.A_b[1 + (sensorFusion_B.s3_iter_o << 2)].re = (real32_T)
          sensorFusion_B.A[(sensorFusion_B.s3_iter_o << 2) + 1];
        sensorFusion_B.A_b[1 + (sensorFusion_B.s3_iter_o << 2)].im = 0.0F;
        sensorFusion_B.A_b[2 + (sensorFusion_B.s3_iter_o << 2)].re = (real32_T)
          sensorFusion_B.A[(sensorFusion_B.s3_iter_o << 2) + 2];
        sensorFusion_B.A_b[2 + (sensorFusion_B.s3_iter_o << 2)].im = 0.0F;
        sensorFusion_B.A_b[3 + (sensorFusion_B.s3_iter_o << 2)].re = (real32_T)
          sensorFusion_B.A[(sensorFusion_B.s3_iter_o << 2) + 3];
        sensorFusion_B.A_b[3 + (sensorFusion_B.s3_iter_o << 2)].im = 0.0F;
      }

      for (sensorFusion_B.s3_iter_o = 0; sensorFusion_B.s3_iter_o < 4;
           sensorFusion_B.s3_iter_o++) {
        for (sensorFusion_B.i0 = 0; sensorFusion_B.i0 < 4; sensorFusion_B.i0++)
        {
          sensorFusion_B.A_p[sensorFusion_B.s3_iter_o + (sensorFusion_B.i0 << 2)]
            .re = 0.0F;
          sensorFusion_B.A_p[sensorFusion_B.s3_iter_o + (sensorFusion_B.i0 << 2)]
            .im = 0.0F;
          sensorFusion_B.A_p[sensorFusion_B.s3_iter_o + (sensorFusion_B.i0 << 2)]
            .re += sensorFusion_DW.UnitDelay1_DSTATE[sensorFusion_B.i0 << 2].re *
            sensorFusion_B.A_b[sensorFusion_B.s3_iter_o].re -
            sensorFusion_DW.UnitDelay1_DSTATE[sensorFusion_B.i0 << 2].im *
            sensorFusion_B.A_b[sensorFusion_B.s3_iter_o].im;
          sensorFusion_B.A_p[sensorFusion_B.s3_iter_o + (sensorFusion_B.i0 << 2)]
            .im += sensorFusion_DW.UnitDelay1_DSTATE[sensorFusion_B.i0 << 2].im *
            sensorFusion_B.A_b[sensorFusion_B.s3_iter_o].re +
            sensorFusion_DW.UnitDelay1_DSTATE[sensorFusion_B.i0 << 2].re *
            sensorFusion_B.A_b[sensorFusion_B.s3_iter_o].im;
          sensorFusion_B.A_p[sensorFusion_B.s3_iter_o + (sensorFusion_B.i0 << 2)]
            .re += sensorFusion_DW.UnitDelay1_DSTATE[(sensorFusion_B.i0 << 2) +
            1].re * sensorFusion_B.A_b[sensorFusion_B.s3_iter_o + 4].re -
            sensorFusion_DW.UnitDelay1_DSTATE[(sensorFusion_B.i0 << 2) + 1].im *
            sensorFusion_B.A_b[sensorFusion_B.s3_iter_o + 4].im;
          sensorFusion_B.A_p[sensorFusion_B.s3_iter_o + (sensorFusion_B.i0 << 2)]
            .im += sensorFusion_DW.UnitDelay1_DSTATE[(sensorFusion_B.i0 << 2) +
            1].im * sensorFusion_B.A_b[sensorFusion_B.s3_iter_o + 4].re +
            sensorFusion_DW.UnitDelay1_DSTATE[(sensorFusion_B.i0 << 2) + 1].re *
            sensorFusion_B.A_b[sensorFusion_B.s3_iter_o + 4].im;
          sensorFusion_B.A_p[sensorFusion_B.s3_iter_o + (sensorFusion_B.i0 << 2)]
            .re += sensorFusion_DW.UnitDelay1_DSTATE[(sensorFusion_B.i0 << 2) +
            2].re * sensorFusion_B.A_b[sensorFusion_B.s3_iter_o + 8].re -
            sensorFusion_DW.UnitDelay1_DSTATE[(sensorFusion_B.i0 << 2) + 2].im *
            sensorFusion_B.A_b[sensorFusion_B.s3_iter_o + 8].im;
          sensorFusion_B.A_p[sensorFusion_B.s3_iter_o + (sensorFusion_B.i0 << 2)]
            .im += sensorFusion_DW.UnitDelay1_DSTATE[(sensorFusion_B.i0 << 2) +
            2].im * sensorFusion_B.A_b[sensorFusion_B.s3_iter_o + 8].re +
            sensorFusion_DW.UnitDelay1_DSTATE[(sensorFusion_B.i0 << 2) + 2].re *
            sensorFusion_B.A_b[sensorFusion_B.s3_iter_o + 8].im;
          sensorFusion_B.A_p[sensorFusion_B.s3_iter_o + (sensorFusion_B.i0 << 2)]
            .re += sensorFusion_DW.UnitDelay1_DSTATE[(sensorFusion_B.i0 << 2) +
            3].re * sensorFusion_B.A_b[sensorFusion_B.s3_iter_o + 12].re -
            sensorFusion_DW.UnitDelay1_DSTATE[(sensorFusion_B.i0 << 2) + 3].im *
            sensorFusion_B.A_b[sensorFusion_B.s3_iter_o + 12].im;
          sensorFusion_B.A_p[sensorFusion_B.s3_iter_o + (sensorFusion_B.i0 << 2)]
            .im += sensorFusion_DW.UnitDelay1_DSTATE[(sensorFusion_B.i0 << 2) +
            3].im * sensorFusion_B.A_b[sensorFusion_B.s3_iter_o + 12].re +
            sensorFusion_DW.UnitDelay1_DSTATE[(sensorFusion_B.i0 << 2) + 3].re *
            sensorFusion_B.A_b[sensorFusion_B.s3_iter_o + 12].im;
          sensorFusion_B.A_c[sensorFusion_B.i0 + (sensorFusion_B.s3_iter_o << 2)]
            .re = (real32_T)sensorFusion_B.A[(sensorFusion_B.i0 << 2) +
            sensorFusion_B.s3_iter_o];
          sensorFusion_B.A_c[sensorFusion_B.i0 + (sensorFusion_B.s3_iter_o << 2)]
            .im = 0.0F;
        }
      }

      for (sensorFusion_B.s3_iter_o = 0; sensorFusion_B.s3_iter_o < 3;
           sensorFusion_B.s3_iter_o++) {
        sensorFusion_B.b_C_n[3 * sensorFusion_B.s3_iter_o].re = (real32_T)
          sensorFusion_B.d[3 * sensorFusion_B.s3_iter_o];
        sensorFusion_B.b_C_n[3 * sensorFusion_B.s3_iter_o].im = 0.0F;
        sensorFusion_B.b_C_n[1 + 3 * sensorFusion_B.s3_iter_o].re = (real32_T)
          sensorFusion_B.d[3 * sensorFusion_B.s3_iter_o + 1];
        sensorFusion_B.b_C_n[1 + 3 * sensorFusion_B.s3_iter_o].im = 0.0F;
        sensorFusion_B.b_C_n[2 + 3 * sensorFusion_B.s3_iter_o].re = (real32_T)
          sensorFusion_B.d[3 * sensorFusion_B.s3_iter_o + 2];
        sensorFusion_B.b_C_n[2 + 3 * sensorFusion_B.s3_iter_o].im = 0.0F;
      }

      for (sensorFusion_B.s3_iter_o = 0; sensorFusion_B.s3_iter_o < 4;
           sensorFusion_B.s3_iter_o++) {
        for (sensorFusion_B.i0 = 0; sensorFusion_B.i0 < 3; sensorFusion_B.i0++)
        {
          sensorFusion_B.y_g[sensorFusion_B.s3_iter_o + (sensorFusion_B.i0 << 2)]
            .re = 0.0F;
          sensorFusion_B.y_g[sensorFusion_B.s3_iter_o + (sensorFusion_B.i0 << 2)]
            .im = 0.0F;
          sensorFusion_B.b_dx = (real32_T)sensorFusion_B.y_p *
            sensorFusion_B.QqChi[sensorFusion_B.s3_iter_o].re;
          sensorFusion_B.u1 = (real32_T)sensorFusion_B.y_p *
            sensorFusion_B.QqChi[sensorFusion_B.s3_iter_o].im;
          sensorFusion_B.y_g[sensorFusion_B.s3_iter_o + (sensorFusion_B.i0 << 2)]
            .re += sensorFusion_B.b_C_n[3 * sensorFusion_B.i0].re *
            sensorFusion_B.b_dx - sensorFusion_B.b_C_n[3 * sensorFusion_B.i0].im
            * sensorFusion_B.u1;
          sensorFusion_B.y_g[sensorFusion_B.s3_iter_o + (sensorFusion_B.i0 << 2)]
            .im += sensorFusion_B.b_C_n[3 * sensorFusion_B.i0].im *
            sensorFusion_B.b_dx + sensorFusion_B.b_C_n[3 * sensorFusion_B.i0].re
            * sensorFusion_B.u1;
          sensorFusion_B.b_dx = sensorFusion_B.QqChi[sensorFusion_B.s3_iter_o +
            4].re * (real32_T)sensorFusion_B.y_p;
          sensorFusion_B.u1 = sensorFusion_B.QqChi[sensorFusion_B.s3_iter_o + 4]
            .im * (real32_T)sensorFusion_B.y_p;
          sensorFusion_B.y_g[sensorFusion_B.s3_iter_o + (sensorFusion_B.i0 << 2)]
            .re += sensorFusion_B.b_C_n[3 * sensorFusion_B.i0 + 1].re *
            sensorFusion_B.b_dx - sensorFusion_B.b_C_n[3 * sensorFusion_B.i0 + 1]
            .im * sensorFusion_B.u1;
          sensorFusion_B.y_g[sensorFusion_B.s3_iter_o + (sensorFusion_B.i0 << 2)]
            .im += sensorFusion_B.b_C_n[3 * sensorFusion_B.i0 + 1].im *
            sensorFusion_B.b_dx + sensorFusion_B.b_C_n[3 * sensorFusion_B.i0 + 1]
            .re * sensorFusion_B.u1;
          sensorFusion_B.b_dx = sensorFusion_B.QqChi[sensorFusion_B.s3_iter_o +
            8].re * (real32_T)sensorFusion_B.y_p;
          sensorFusion_B.u1 = sensorFusion_B.QqChi[sensorFusion_B.s3_iter_o + 8]
            .im * (real32_T)sensorFusion_B.y_p;
          sensorFusion_B.y_g[sensorFusion_B.s3_iter_o + (sensorFusion_B.i0 << 2)]
            .re += sensorFusion_B.b_C_n[3 * sensorFusion_B.i0 + 2].re *
            sensorFusion_B.b_dx - sensorFusion_B.b_C_n[3 * sensorFusion_B.i0 + 2]
            .im * sensorFusion_B.u1;
          sensorFusion_B.y_g[sensorFusion_B.s3_iter_o + (sensorFusion_B.i0 << 2)]
            .im += sensorFusion_B.b_C_n[3 * sensorFusion_B.i0 + 2].im *
            sensorFusion_B.b_dx + sensorFusion_B.b_C_n[3 * sensorFusion_B.i0 + 2]
            .re * sensorFusion_B.u1;
        }

        for (sensorFusion_B.i0 = 0; sensorFusion_B.i0 < 4; sensorFusion_B.i0++)
        {
          sensorFusion_B.A_b[sensorFusion_B.s3_iter_o + (sensorFusion_B.i0 << 2)]
            .re = 0.0F;
          sensorFusion_B.A_b[sensorFusion_B.s3_iter_o + (sensorFusion_B.i0 << 2)]
            .im = 0.0F;
          sensorFusion_B.A_b[sensorFusion_B.s3_iter_o + (sensorFusion_B.i0 << 2)]
            .re += sensorFusion_B.A_c[sensorFusion_B.i0 << 2].re *
            sensorFusion_B.A_p[sensorFusion_B.s3_iter_o].re -
            sensorFusion_B.A_c[sensorFusion_B.i0 << 2].im *
            sensorFusion_B.A_p[sensorFusion_B.s3_iter_o].im;
          sensorFusion_B.A_b[sensorFusion_B.s3_iter_o + (sensorFusion_B.i0 << 2)]
            .im += sensorFusion_B.A_c[sensorFusion_B.i0 << 2].im *
            sensorFusion_B.A_p[sensorFusion_B.s3_iter_o].re +
            sensorFusion_B.A_c[sensorFusion_B.i0 << 2].re *
            sensorFusion_B.A_p[sensorFusion_B.s3_iter_o].im;
          sensorFusion_B.A_b[sensorFusion_B.s3_iter_o + (sensorFusion_B.i0 << 2)]
            .re += sensorFusion_B.A_c[(sensorFusion_B.i0 << 2) + 1].re *
            sensorFusion_B.A_p[sensorFusion_B.s3_iter_o + 4].re -
            sensorFusion_B.A_c[(sensorFusion_B.i0 << 2) + 1].im *
            sensorFusion_B.A_p[sensorFusion_B.s3_iter_o + 4].im;
          sensorFusion_B.A_b[sensorFusion_B.s3_iter_o + (sensorFusion_B.i0 << 2)]
            .im += sensorFusion_B.A_c[(sensorFusion_B.i0 << 2) + 1].im *
            sensorFusion_B.A_p[sensorFusion_B.s3_iter_o + 4].re +
            sensorFusion_B.A_c[(sensorFusion_B.i0 << 2) + 1].re *
            sensorFusion_B.A_p[sensorFusion_B.s3_iter_o + 4].im;
          sensorFusion_B.A_b[sensorFusion_B.s3_iter_o + (sensorFusion_B.i0 << 2)]
            .re += sensorFusion_B.A_c[(sensorFusion_B.i0 << 2) + 2].re *
            sensorFusion_B.A_p[sensorFusion_B.s3_iter_o + 8].re -
            sensorFusion_B.A_c[(sensorFusion_B.i0 << 2) + 2].im *
            sensorFusion_B.A_p[sensorFusion_B.s3_iter_o + 8].im;
          sensorFusion_B.A_b[sensorFusion_B.s3_iter_o + (sensorFusion_B.i0 << 2)]
            .im += sensorFusion_B.A_c[(sensorFusion_B.i0 << 2) + 2].im *
            sensorFusion_B.A_p[sensorFusion_B.s3_iter_o + 8].re +
            sensorFusion_B.A_c[(sensorFusion_B.i0 << 2) + 2].re *
            sensorFusion_B.A_p[sensorFusion_B.s3_iter_o + 8].im;
          sensorFusion_B.A_b[sensorFusion_B.s3_iter_o + (sensorFusion_B.i0 << 2)]
            .re += sensorFusion_B.A_c[(sensorFusion_B.i0 << 2) + 3].re *
            sensorFusion_B.A_p[sensorFusion_B.s3_iter_o + 12].re -
            sensorFusion_B.A_c[(sensorFusion_B.i0 << 2) + 3].im *
            sensorFusion_B.A_p[sensorFusion_B.s3_iter_o + 12].im;
          sensorFusion_B.A_b[sensorFusion_B.s3_iter_o + (sensorFusion_B.i0 << 2)]
            .im += sensorFusion_B.A_c[(sensorFusion_B.i0 << 2) + 3].im *
            sensorFusion_B.A_p[sensorFusion_B.s3_iter_o + 12].re +
            sensorFusion_B.A_c[(sensorFusion_B.i0 << 2) + 3].re *
            sensorFusion_B.A_p[sensorFusion_B.s3_iter_o + 12].im;
          sensorFusion_B.y_f[sensorFusion_B.s3_iter_o + (sensorFusion_B.i0 << 2)]
            .re = 0.0F;
          sensorFusion_B.y_f[sensorFusion_B.s3_iter_o + (sensorFusion_B.i0 << 2)]
            .im = 0.0F;
          sensorFusion_B.y_f[sensorFusion_B.s3_iter_o + (sensorFusion_B.i0 << 2)]
            .re += sensorFusion_B.y_g[sensorFusion_B.s3_iter_o].re *
            sensorFusion_B.QqChi[sensorFusion_B.i0].re -
            sensorFusion_B.y_g[sensorFusion_B.s3_iter_o].im *
            -sensorFusion_B.QqChi[sensorFusion_B.i0].im;
          sensorFusion_B.y_f[sensorFusion_B.s3_iter_o + (sensorFusion_B.i0 << 2)]
            .im += sensorFusion_B.y_g[sensorFusion_B.s3_iter_o].re *
            -sensorFusion_B.QqChi[sensorFusion_B.i0].im +
            sensorFusion_B.y_g[sensorFusion_B.s3_iter_o].im *
            sensorFusion_B.QqChi[sensorFusion_B.i0].re;
          sensorFusion_B.b_dx = sensorFusion_B.QqChi[sensorFusion_B.i0 + 4].re;
          sensorFusion_B.u1 = -sensorFusion_B.QqChi[sensorFusion_B.i0 + 4].im;
          sensorFusion_B.y_f[sensorFusion_B.s3_iter_o + (sensorFusion_B.i0 << 2)]
            .re += sensorFusion_B.y_g[sensorFusion_B.s3_iter_o + 4].re *
            sensorFusion_B.b_dx - sensorFusion_B.y_g[sensorFusion_B.s3_iter_o +
            4].im * sensorFusion_B.u1;
          sensorFusion_B.y_f[sensorFusion_B.s3_iter_o + (sensorFusion_B.i0 << 2)]
            .im += sensorFusion_B.y_g[sensorFusion_B.s3_iter_o + 4].re *
            sensorFusion_B.u1 + sensorFusion_B.y_g[sensorFusion_B.s3_iter_o + 4]
            .im * sensorFusion_B.b_dx;
          sensorFusion_B.b_dx = sensorFusion_B.QqChi[sensorFusion_B.i0 + 8].re;
          sensorFusion_B.u1 = -sensorFusion_B.QqChi[sensorFusion_B.i0 + 8].im;
          sensorFusion_B.y_f[sensorFusion_B.s3_iter_o + (sensorFusion_B.i0 << 2)]
            .re += sensorFusion_B.y_g[sensorFusion_B.s3_iter_o + 8].re *
            sensorFusion_B.b_dx - sensorFusion_B.y_g[sensorFusion_B.s3_iter_o +
            8].im * sensorFusion_B.u1;
          sensorFusion_B.y_f[sensorFusion_B.s3_iter_o + (sensorFusion_B.i0 << 2)]
            .im += sensorFusion_B.y_g[sensorFusion_B.s3_iter_o + 8].re *
            sensorFusion_B.u1 + sensorFusion_B.y_g[sensorFusion_B.s3_iter_o + 8]
            .im * sensorFusion_B.b_dx;
        }
      }

      for (sensorFusion_B.s3_iter_o = 0; sensorFusion_B.s3_iter_o < 4;
           sensorFusion_B.s3_iter_o++) {
        sensorFusion_B.P_apriori[sensorFusion_B.s3_iter_o << 2].re =
          sensorFusion_B.A_b[sensorFusion_B.s3_iter_o << 2].re +
          sensorFusion_B.y_f[sensorFusion_B.s3_iter_o << 2].re;
        sensorFusion_B.P_apriori[sensorFusion_B.s3_iter_o << 2].im =
          sensorFusion_B.A_b[sensorFusion_B.s3_iter_o << 2].im +
          sensorFusion_B.y_f[sensorFusion_B.s3_iter_o << 2].im;
        sensorFusion_B.P_apriori[1 + (sensorFusion_B.s3_iter_o << 2)].re =
          sensorFusion_B.A_b[(sensorFusion_B.s3_iter_o << 2) + 1].re +
          sensorFusion_B.y_f[(sensorFusion_B.s3_iter_o << 2) + 1].re;
        sensorFusion_B.P_apriori[1 + (sensorFusion_B.s3_iter_o << 2)].im =
          sensorFusion_B.A_b[(sensorFusion_B.s3_iter_o << 2) + 1].im +
          sensorFusion_B.y_f[(sensorFusion_B.s3_iter_o << 2) + 1].im;
        sensorFusion_B.P_apriori[2 + (sensorFusion_B.s3_iter_o << 2)].re =
          sensorFusion_B.A_b[(sensorFusion_B.s3_iter_o << 2) + 2].re +
          sensorFusion_B.y_f[(sensorFusion_B.s3_iter_o << 2) + 2].re;
        sensorFusion_B.P_apriori[2 + (sensorFusion_B.s3_iter_o << 2)].im =
          sensorFusion_B.A_b[(sensorFusion_B.s3_iter_o << 2) + 2].im +
          sensorFusion_B.y_f[(sensorFusion_B.s3_iter_o << 2) + 2].im;
        sensorFusion_B.P_apriori[3 + (sensorFusion_B.s3_iter_o << 2)].re =
          sensorFusion_B.A_b[(sensorFusion_B.s3_iter_o << 2) + 3].re +
          sensorFusion_B.y_f[(sensorFusion_B.s3_iter_o << 2) + 3].re;
        sensorFusion_B.P_apriori[3 + (sensorFusion_B.s3_iter_o << 2)].im =
          sensorFusion_B.A_b[(sensorFusion_B.s3_iter_o << 2) + 3].im +
          sensorFusion_B.y_f[(sensorFusion_B.s3_iter_o << 2) + 3].im;
      }

      /*  Get apriori measurement and Measurement jacobian */
      /* '<S5>:1:21' [z_apriori,H]=measurementFcn(x_apriori,g,h,true); */
      /* '<S5>:1:61' b_C_n=getC(x(1:4)); */
      sensorFusion_getC(sensorFusion_B.x_apriori, sensorFusion_B.b_C_n);

      /* '<S5>:1:63' zNew=blkdiag(b_C_n,b_C_n)*[g;h]; */
      memset(&sensorFusion_B.c_y[0], 0, 36U * sizeof(creal32_T));
      for (sensorFusion_B.s3_iter_o = 0; sensorFusion_B.s3_iter_o < 3;
           sensorFusion_B.s3_iter_o++) {
        sensorFusion_B.c_y[6 * sensorFusion_B.s3_iter_o] = sensorFusion_B.b_C_n
          [3 * sensorFusion_B.s3_iter_o];
        sensorFusion_B.c_y[3 + 6 * (3 + sensorFusion_B.s3_iter_o)] =
          sensorFusion_B.b_C_n[3 * sensorFusion_B.s3_iter_o];
        sensorFusion_B.c_y[1 + 6 * sensorFusion_B.s3_iter_o] =
          sensorFusion_B.b_C_n[3 * sensorFusion_B.s3_iter_o + 1];
        sensorFusion_B.c_y[4 + 6 * (3 + sensorFusion_B.s3_iter_o)] =
          sensorFusion_B.b_C_n[3 * sensorFusion_B.s3_iter_o + 1];
        sensorFusion_B.c_y[2 + 6 * sensorFusion_B.s3_iter_o] =
          sensorFusion_B.b_C_n[3 * sensorFusion_B.s3_iter_o + 2];
        sensorFusion_B.c_y[5 + 6 * (3 + sensorFusion_B.s3_iter_o)] =
          sensorFusion_B.b_C_n[3 * sensorFusion_B.s3_iter_o + 2];
      }

      /* '<S5>:1:65' if ~doJacobian */
      /* '<S5>:1:69' jacobian=zeros(size(zNew,1),size(x,1)); */
      /* '<S5>:1:71' for i=1:length(x) */
      for (sensorFusion_B.i = 0; sensorFusion_B.i < 4; sensorFusion_B.i++) {
        /* '<S5>:1:72' dx=100*eps(x(i)); */
        sensorFusion_B.b_dx = 100.0F * sensorFusion_eps
          (sensorFusion_B.x_apriori[sensorFusion_B.i]);

        /* '<S5>:1:73' xtemp=x; */
        sensorFusion_B.xtemp[0] = sensorFusion_B.x_apriori[0];
        sensorFusion_B.xtemp[1] = sensorFusion_B.x_apriori[1];
        sensorFusion_B.xtemp[2] = sensorFusion_B.x_apriori[2];
        sensorFusion_B.xtemp[3] = sensorFusion_B.x_apriori[3];

        /* '<S5>:1:74' xtemp(i)=xtemp(i)+dx*1i; */
        sensorFusion_B.xtemp[sensorFusion_B.i].re = sensorFusion_B.b_dx * 0.0F +
          sensorFusion_B.x_apriori[sensorFusion_B.i].re;
        sensorFusion_B.xtemp[sensorFusion_B.i].im =
          sensorFusion_B.x_apriori[sensorFusion_B.i].im + sensorFusion_B.b_dx;

        /* '<S5>:1:75' jacobian(:,i)=imag(measurementFcn(xtemp,g,h,false))./dx; */
        sensorFusion_measurementFcn(sensorFusion_B.xtemp, sensorFusion_P.aMean,
          sensorFusion_P.mMean, sensorFusion_B.fcv0);
        for (sensorFusion_B.s3_iter_o = 0; sensorFusion_B.s3_iter_o < 6;
             sensorFusion_B.s3_iter_o++) {
          sensorFusion_B.H_m[sensorFusion_B.s3_iter_o + 6 * sensorFusion_B.i] =
            sensorFusion_B.fcv0[sensorFusion_B.s3_iter_o].im /
            sensorFusion_B.b_dx;
        }
      }

      /*  Update Kalman gain */
      /* '<S5>:1:24' K = (P_apriori*H') / (H*P_apriori*H' + R); */
      for (sensorFusion_B.s3_iter_o = 0; sensorFusion_B.s3_iter_o < 6;
           sensorFusion_B.s3_iter_o++) {
        sensorFusion_B.H_c[sensorFusion_B.s3_iter_o << 2].re = (real32_T)
          sensorFusion_B.H_m[sensorFusion_B.s3_iter_o];
        sensorFusion_B.H_c[sensorFusion_B.s3_iter_o << 2].im = 0.0F;
        sensorFusion_B.H_c[1 + (sensorFusion_B.s3_iter_o << 2)].re = (real32_T)
          sensorFusion_B.H_m[sensorFusion_B.s3_iter_o + 6];
        sensorFusion_B.H_c[1 + (sensorFusion_B.s3_iter_o << 2)].im = 0.0F;
        sensorFusion_B.H_c[2 + (sensorFusion_B.s3_iter_o << 2)].re = (real32_T)
          sensorFusion_B.H_m[sensorFusion_B.s3_iter_o + 12];
        sensorFusion_B.H_c[2 + (sensorFusion_B.s3_iter_o << 2)].im = 0.0F;
        sensorFusion_B.H_c[3 + (sensorFusion_B.s3_iter_o << 2)].re = (real32_T)
          sensorFusion_B.H_m[sensorFusion_B.s3_iter_o + 18];
        sensorFusion_B.H_c[3 + (sensorFusion_B.s3_iter_o << 2)].im = 0.0F;
      }

      for (sensorFusion_B.s3_iter_o = 0; sensorFusion_B.s3_iter_o < 4;
           sensorFusion_B.s3_iter_o++) {
        for (sensorFusion_B.i0 = 0; sensorFusion_B.i0 < 6; sensorFusion_B.i0++)
        {
          sensorFusion_B.K[sensorFusion_B.s3_iter_o + (sensorFusion_B.i0 << 2)].
            re = 0.0F;
          sensorFusion_B.K[sensorFusion_B.s3_iter_o + (sensorFusion_B.i0 << 2)].
            im = 0.0F;
          sensorFusion_B.K[sensorFusion_B.s3_iter_o + (sensorFusion_B.i0 << 2)].
            re += sensorFusion_B.H_c[sensorFusion_B.i0 << 2].re *
            sensorFusion_B.P_apriori[sensorFusion_B.s3_iter_o].re -
            sensorFusion_B.H_c[sensorFusion_B.i0 << 2].im *
            sensorFusion_B.P_apriori[sensorFusion_B.s3_iter_o].im;
          sensorFusion_B.K[sensorFusion_B.s3_iter_o + (sensorFusion_B.i0 << 2)].
            im += sensorFusion_B.H_c[sensorFusion_B.i0 << 2].im *
            sensorFusion_B.P_apriori[sensorFusion_B.s3_iter_o].re +
            sensorFusion_B.H_c[sensorFusion_B.i0 << 2].re *
            sensorFusion_B.P_apriori[sensorFusion_B.s3_iter_o].im;
          sensorFusion_B.K[sensorFusion_B.s3_iter_o + (sensorFusion_B.i0 << 2)].
            re += sensorFusion_B.H_c[(sensorFusion_B.i0 << 2) + 1].re *
            sensorFusion_B.P_apriori[sensorFusion_B.s3_iter_o + 4].re -
            sensorFusion_B.H_c[(sensorFusion_B.i0 << 2) + 1].im *
            sensorFusion_B.P_apriori[sensorFusion_B.s3_iter_o + 4].im;
          sensorFusion_B.K[sensorFusion_B.s3_iter_o + (sensorFusion_B.i0 << 2)].
            im += sensorFusion_B.H_c[(sensorFusion_B.i0 << 2) + 1].im *
            sensorFusion_B.P_apriori[sensorFusion_B.s3_iter_o + 4].re +
            sensorFusion_B.H_c[(sensorFusion_B.i0 << 2) + 1].re *
            sensorFusion_B.P_apriori[sensorFusion_B.s3_iter_o + 4].im;
          sensorFusion_B.K[sensorFusion_B.s3_iter_o + (sensorFusion_B.i0 << 2)].
            re += sensorFusion_B.H_c[(sensorFusion_B.i0 << 2) + 2].re *
            sensorFusion_B.P_apriori[sensorFusion_B.s3_iter_o + 8].re -
            sensorFusion_B.H_c[(sensorFusion_B.i0 << 2) + 2].im *
            sensorFusion_B.P_apriori[sensorFusion_B.s3_iter_o + 8].im;
          sensorFusion_B.K[sensorFusion_B.s3_iter_o + (sensorFusion_B.i0 << 2)].
            im += sensorFusion_B.H_c[(sensorFusion_B.i0 << 2) + 2].im *
            sensorFusion_B.P_apriori[sensorFusion_B.s3_iter_o + 8].re +
            sensorFusion_B.H_c[(sensorFusion_B.i0 << 2) + 2].re *
            sensorFusion_B.P_apriori[sensorFusion_B.s3_iter_o + 8].im;
          sensorFusion_B.K[sensorFusion_B.s3_iter_o + (sensorFusion_B.i0 << 2)].
            re += sensorFusion_B.H_c[(sensorFusion_B.i0 << 2) + 3].re *
            sensorFusion_B.P_apriori[sensorFusion_B.s3_iter_o + 12].re -
            sensorFusion_B.H_c[(sensorFusion_B.i0 << 2) + 3].im *
            sensorFusion_B.P_apriori[sensorFusion_B.s3_iter_o + 12].im;
          sensorFusion_B.K[sensorFusion_B.s3_iter_o + (sensorFusion_B.i0 << 2)].
            im += sensorFusion_B.H_c[(sensorFusion_B.i0 << 2) + 3].im *
            sensorFusion_B.P_apriori[sensorFusion_B.s3_iter_o + 12].re +
            sensorFusion_B.H_c[(sensorFusion_B.i0 << 2) + 3].re *
            sensorFusion_B.P_apriori[sensorFusion_B.s3_iter_o + 12].im;
          sensorFusion_B.H_k[sensorFusion_B.i0 + 6 * sensorFusion_B.s3_iter_o].
            re = (real32_T)sensorFusion_B.H_m[6 * sensorFusion_B.s3_iter_o +
            sensorFusion_B.i0];
          sensorFusion_B.H_k[sensorFusion_B.i0 + 6 * sensorFusion_B.s3_iter_o].
            im = 0.0F;
        }
      }

      for (sensorFusion_B.s3_iter_o = 0; sensorFusion_B.s3_iter_o < 6;
           sensorFusion_B.s3_iter_o++) {
        for (sensorFusion_B.i0 = 0; sensorFusion_B.i0 < 4; sensorFusion_B.i0++)
        {
          sensorFusion_B.H_c[sensorFusion_B.s3_iter_o + 6 * sensorFusion_B.i0].
            re = 0.0F;
          sensorFusion_B.H_c[sensorFusion_B.s3_iter_o + 6 * sensorFusion_B.i0].
            im = 0.0F;
          sensorFusion_B.H_c[sensorFusion_B.s3_iter_o + 6 * sensorFusion_B.i0].
            re += sensorFusion_B.P_apriori[sensorFusion_B.i0 << 2].re *
            sensorFusion_B.H_k[sensorFusion_B.s3_iter_o].re -
            sensorFusion_B.P_apriori[sensorFusion_B.i0 << 2].im *
            sensorFusion_B.H_k[sensorFusion_B.s3_iter_o].im;
          sensorFusion_B.H_c[sensorFusion_B.s3_iter_o + 6 * sensorFusion_B.i0].
            im += sensorFusion_B.P_apriori[sensorFusion_B.i0 << 2].im *
            sensorFusion_B.H_k[sensorFusion_B.s3_iter_o].re +
            sensorFusion_B.P_apriori[sensorFusion_B.i0 << 2].re *
            sensorFusion_B.H_k[sensorFusion_B.s3_iter_o].im;
          sensorFusion_B.H_c[sensorFusion_B.s3_iter_o + 6 * sensorFusion_B.i0].
            re += sensorFusion_B.P_apriori[(sensorFusion_B.i0 << 2) + 1].re *
            sensorFusion_B.H_k[sensorFusion_B.s3_iter_o + 6].re -
            sensorFusion_B.P_apriori[(sensorFusion_B.i0 << 2) + 1].im *
            sensorFusion_B.H_k[sensorFusion_B.s3_iter_o + 6].im;
          sensorFusion_B.H_c[sensorFusion_B.s3_iter_o + 6 * sensorFusion_B.i0].
            im += sensorFusion_B.P_apriori[(sensorFusion_B.i0 << 2) + 1].im *
            sensorFusion_B.H_k[sensorFusion_B.s3_iter_o + 6].re +
            sensorFusion_B.P_apriori[(sensorFusion_B.i0 << 2) + 1].re *
            sensorFusion_B.H_k[sensorFusion_B.s3_iter_o + 6].im;
          sensorFusion_B.H_c[sensorFusion_B.s3_iter_o + 6 * sensorFusion_B.i0].
            re += sensorFusion_B.P_apriori[(sensorFusion_B.i0 << 2) + 2].re *
            sensorFusion_B.H_k[sensorFusion_B.s3_iter_o + 12].re -
            sensorFusion_B.P_apriori[(sensorFusion_B.i0 << 2) + 2].im *
            sensorFusion_B.H_k[sensorFusion_B.s3_iter_o + 12].im;
          sensorFusion_B.H_c[sensorFusion_B.s3_iter_o + 6 * sensorFusion_B.i0].
            im += sensorFusion_B.P_apriori[(sensorFusion_B.i0 << 2) + 2].im *
            sensorFusion_B.H_k[sensorFusion_B.s3_iter_o + 12].re +
            sensorFusion_B.P_apriori[(sensorFusion_B.i0 << 2) + 2].re *
            sensorFusion_B.H_k[sensorFusion_B.s3_iter_o + 12].im;
          sensorFusion_B.H_c[sensorFusion_B.s3_iter_o + 6 * sensorFusion_B.i0].
            re += sensorFusion_B.P_apriori[(sensorFusion_B.i0 << 2) + 3].re *
            sensorFusion_B.H_k[sensorFusion_B.s3_iter_o + 18].re -
            sensorFusion_B.P_apriori[(sensorFusion_B.i0 << 2) + 3].im *
            sensorFusion_B.H_k[sensorFusion_B.s3_iter_o + 18].im;
          sensorFusion_B.H_c[sensorFusion_B.s3_iter_o + 6 * sensorFusion_B.i0].
            im += sensorFusion_B.P_apriori[(sensorFusion_B.i0 << 2) + 3].im *
            sensorFusion_B.H_k[sensorFusion_B.s3_iter_o + 18].re +
            sensorFusion_B.P_apriori[(sensorFusion_B.i0 << 2) + 3].re *
            sensorFusion_B.H_k[sensorFusion_B.s3_iter_o + 18].im;
          sensorFusion_B.H_cx[sensorFusion_B.i0 + (sensorFusion_B.s3_iter_o << 2)]
            .re = (real32_T)sensorFusion_B.H_m[6 * sensorFusion_B.i0 +
            sensorFusion_B.s3_iter_o];
          sensorFusion_B.H_cx[sensorFusion_B.i0 + (sensorFusion_B.s3_iter_o << 2)]
            .im = 0.0F;
        }
      }

      for (sensorFusion_B.s3_iter_o = 0; sensorFusion_B.s3_iter_o < 6;
           sensorFusion_B.s3_iter_o++) {
        for (sensorFusion_B.i0 = 0; sensorFusion_B.i0 < 6; sensorFusion_B.i0++)
        {
          sensorFusion_B.H[sensorFusion_B.s3_iter_o + 6 * sensorFusion_B.i0].re =
            ((((sensorFusion_B.H_cx[(sensorFusion_B.i0 << 2) + 1].re *
                sensorFusion_B.H_c[sensorFusion_B.s3_iter_o + 6].re -
                sensorFusion_B.H_cx[(sensorFusion_B.i0 << 2) + 1].im *
                sensorFusion_B.H_c[sensorFusion_B.s3_iter_o + 6].im) +
               (sensorFusion_B.H_cx[sensorFusion_B.i0 << 2].re *
                sensorFusion_B.H_c[sensorFusion_B.s3_iter_o].re -
                sensorFusion_B.H_cx[sensorFusion_B.i0 << 2].im *
                sensorFusion_B.H_c[sensorFusion_B.s3_iter_o].im)) +
              (sensorFusion_B.H_cx[(sensorFusion_B.i0 << 2) + 2].re *
               sensorFusion_B.H_c[sensorFusion_B.s3_iter_o + 12].re -
               sensorFusion_B.H_cx[(sensorFusion_B.i0 << 2) + 2].im *
               sensorFusion_B.H_c[sensorFusion_B.s3_iter_o + 12].im)) +
             (sensorFusion_B.H_cx[(sensorFusion_B.i0 << 2) + 3].re *
              sensorFusion_B.H_c[sensorFusion_B.s3_iter_o + 18].re -
              sensorFusion_B.H_cx[(sensorFusion_B.i0 << 2) + 3].im *
              sensorFusion_B.H_c[sensorFusion_B.s3_iter_o + 18].im)) +
            sensorFusion_B.R[6 * sensorFusion_B.i0 + sensorFusion_B.s3_iter_o];
          sensorFusion_B.H[sensorFusion_B.s3_iter_o + 6 * sensorFusion_B.i0].im =
            (((sensorFusion_B.H_cx[(sensorFusion_B.i0 << 2) + 1].im *
               sensorFusion_B.H_c[sensorFusion_B.s3_iter_o + 6].re +
               sensorFusion_B.H_cx[(sensorFusion_B.i0 << 2) + 1].re *
               sensorFusion_B.H_c[sensorFusion_B.s3_iter_o + 6].im) +
              (sensorFusion_B.H_cx[sensorFusion_B.i0 << 2].im *
               sensorFusion_B.H_c[sensorFusion_B.s3_iter_o].re +
               sensorFusion_B.H_cx[sensorFusion_B.i0 << 2].re *
               sensorFusion_B.H_c[sensorFusion_B.s3_iter_o].im)) +
             (sensorFusion_B.H_cx[(sensorFusion_B.i0 << 2) + 2].im *
              sensorFusion_B.H_c[sensorFusion_B.s3_iter_o + 12].re +
              sensorFusion_B.H_cx[(sensorFusion_B.i0 << 2) + 2].re *
              sensorFusion_B.H_c[sensorFusion_B.s3_iter_o + 12].im)) +
            (sensorFusion_B.H_cx[(sensorFusion_B.i0 << 2) + 3].im *
             sensorFusion_B.H_c[sensorFusion_B.s3_iter_o + 18].re +
             sensorFusion_B.H_cx[(sensorFusion_B.i0 << 2) + 3].re *
             sensorFusion_B.H_c[sensorFusion_B.s3_iter_o + 18].im);
        }
      }

      sensorFusion_mrdivide(sensorFusion_B.K, sensorFusion_B.H);

      /*  Update aposteriori state estimate with measurement */
      /* '<S5>:1:27' z = [a;m]; */
      /* '<S5>:1:28' x = x_apriori + K *(z-z_apriori); */
      sensorFusion_B.fv1[0] = sensorFusion_B.accel[0];
      sensorFusion_B.fv1[3] = sensorFusion_B.mag[0];
      sensorFusion_B.fv2[0] = (real32_T)sensorFusion_P.aMean[0];
      sensorFusion_B.fv2[3] = (real32_T)sensorFusion_P.mMean[0];
      sensorFusion_B.fv1[1] = sensorFusion_B.accel[1];
      sensorFusion_B.fv1[4] = sensorFusion_B.mag[1];
      sensorFusion_B.fv2[1] = (real32_T)sensorFusion_P.aMean[1];
      sensorFusion_B.fv2[4] = (real32_T)sensorFusion_P.mMean[1];
      sensorFusion_B.fv1[2] = sensorFusion_B.accel[2];
      sensorFusion_B.fv1[5] = sensorFusion_B.mag[2];
      sensorFusion_B.fv2[2] = (real32_T)sensorFusion_P.aMean[2];
      sensorFusion_B.fv2[5] = (real32_T)sensorFusion_P.mMean[2];
      for (sensorFusion_B.s3_iter_o = 0; sensorFusion_B.s3_iter_o < 6;
           sensorFusion_B.s3_iter_o++) {
        sensorFusion_B.fcv0[sensorFusion_B.s3_iter_o].re =
          sensorFusion_B.fv2[sensorFusion_B.s3_iter_o];
        sensorFusion_B.fcv0[sensorFusion_B.s3_iter_o].im = 0.0F;
      }

      for (sensorFusion_B.s3_iter_o = 0; sensorFusion_B.s3_iter_o < 6;
           sensorFusion_B.s3_iter_o++) {
        sensorFusion_B.b_dx = 0.0F;
        sensorFusion_B.u1 = 0.0F;
        for (sensorFusion_B.i0 = 0; sensorFusion_B.i0 < 6; sensorFusion_B.i0++)
        {
          sensorFusion_B.b_dx += sensorFusion_B.c_y[6 * sensorFusion_B.i0 +
            sensorFusion_B.s3_iter_o].re * sensorFusion_B.fcv0[sensorFusion_B.i0]
            .re - sensorFusion_B.c_y[6 * sensorFusion_B.i0 +
            sensorFusion_B.s3_iter_o].im * sensorFusion_B.fcv0[sensorFusion_B.i0]
            .im;
          sensorFusion_B.u1 += sensorFusion_B.c_y[6 * sensorFusion_B.i0 +
            sensorFusion_B.s3_iter_o].re * sensorFusion_B.fcv0[sensorFusion_B.i0]
            .im + sensorFusion_B.c_y[6 * sensorFusion_B.i0 +
            sensorFusion_B.s3_iter_o].im * sensorFusion_B.fcv0[sensorFusion_B.i0]
            .re;
        }

        sensorFusion_B.fcv1[sensorFusion_B.s3_iter_o].re =
          sensorFusion_B.fv1[sensorFusion_B.s3_iter_o] - sensorFusion_B.b_dx;
        sensorFusion_B.fcv1[sensorFusion_B.s3_iter_o].im = 0.0F -
          sensorFusion_B.u1;
      }

      for (sensorFusion_B.s3_iter_o = 0; sensorFusion_B.s3_iter_o < 4;
           sensorFusion_B.s3_iter_o++) {
        sensorFusion_B.b_dx = 0.0F;
        sensorFusion_B.u1 = 0.0F;
        for (sensorFusion_B.i0 = 0; sensorFusion_B.i0 < 6; sensorFusion_B.i0++)
        {
          sensorFusion_B.b_dx += sensorFusion_B.K[(sensorFusion_B.i0 << 2) +
            sensorFusion_B.s3_iter_o].re * sensorFusion_B.fcv1[sensorFusion_B.i0]
            .re - sensorFusion_B.K[(sensorFusion_B.i0 << 2) +
            sensorFusion_B.s3_iter_o].im * sensorFusion_B.fcv1[sensorFusion_B.i0]
            .im;
          sensorFusion_B.u1 += sensorFusion_B.K[(sensorFusion_B.i0 << 2) +
            sensorFusion_B.s3_iter_o].re * sensorFusion_B.fcv1[sensorFusion_B.i0]
            .im + sensorFusion_B.K[(sensorFusion_B.i0 << 2) +
            sensorFusion_B.s3_iter_o].im * sensorFusion_B.fcv1[sensorFusion_B.i0]
            .re;
        }

        sensorFusion_B.x[sensorFusion_B.s3_iter_o].re =
          sensorFusion_B.x_apriori[sensorFusion_B.s3_iter_o].re +
          sensorFusion_B.b_dx;
        sensorFusion_B.x[sensorFusion_B.s3_iter_o].im =
          sensorFusion_B.x_apriori[sensorFusion_B.s3_iter_o].im +
          sensorFusion_B.u1;
      }

      /* '<S5>:1:29' x(1:4)=x(1:4)./norm(x(1:4)); */
      sensorFusion_B.b_dx = sensorFusion_norm(sensorFusion_B.x);
      if (sensorFusion_B.x[0].im == 0.0F) {
        sensorFusion_B.u1 = sensorFusion_B.x[0].re / sensorFusion_B.b_dx;
        sensorFusion_B.rtb_x_im = 0.0F;
      } else if (sensorFusion_B.x[0].re == 0.0F) {
        sensorFusion_B.u1 = 0.0F;
        sensorFusion_B.rtb_x_im = sensorFusion_B.x[0].im / sensorFusion_B.b_dx;
      } else {
        sensorFusion_B.u1 = sensorFusion_B.x[0].re / sensorFusion_B.b_dx;
        sensorFusion_B.rtb_x_im = sensorFusion_B.x[0].im / sensorFusion_B.b_dx;
      }

      sensorFusion_B.x[0].re = sensorFusion_B.u1;
      sensorFusion_B.x[0].im = sensorFusion_B.rtb_x_im;
      if (sensorFusion_B.x[1].im == 0.0F) {
        sensorFusion_B.u1 = sensorFusion_B.x[1].re / sensorFusion_B.b_dx;
        sensorFusion_B.rtb_x_im = 0.0F;
      } else if (sensorFusion_B.x[1].re == 0.0F) {
        sensorFusion_B.u1 = 0.0F;
        sensorFusion_B.rtb_x_im = sensorFusion_B.x[1].im / sensorFusion_B.b_dx;
      } else {
        sensorFusion_B.u1 = sensorFusion_B.x[1].re / sensorFusion_B.b_dx;
        sensorFusion_B.rtb_x_im = sensorFusion_B.x[1].im / sensorFusion_B.b_dx;
      }

      sensorFusion_B.x[1].re = sensorFusion_B.u1;
      sensorFusion_B.x[1].im = sensorFusion_B.rtb_x_im;
      if (sensorFusion_B.x[2].im == 0.0F) {
        sensorFusion_B.u1 = sensorFusion_B.x[2].re / sensorFusion_B.b_dx;
        sensorFusion_B.rtb_x_im = 0.0F;
      } else if (sensorFusion_B.x[2].re == 0.0F) {
        sensorFusion_B.u1 = 0.0F;
        sensorFusion_B.rtb_x_im = sensorFusion_B.x[2].im / sensorFusion_B.b_dx;
      } else {
        sensorFusion_B.u1 = sensorFusion_B.x[2].re / sensorFusion_B.b_dx;
        sensorFusion_B.rtb_x_im = sensorFusion_B.x[2].im / sensorFusion_B.b_dx;
      }

      sensorFusion_B.x[2].re = sensorFusion_B.u1;
      sensorFusion_B.x[2].im = sensorFusion_B.rtb_x_im;
      if (sensorFusion_B.x[3].im == 0.0F) {
        sensorFusion_B.u1 = sensorFusion_B.x[3].re / sensorFusion_B.b_dx;
        sensorFusion_B.rtb_x_im = 0.0F;
      } else if (sensorFusion_B.x[3].re == 0.0F) {
        sensorFusion_B.u1 = 0.0F;
        sensorFusion_B.rtb_x_im = sensorFusion_B.x[3].im / sensorFusion_B.b_dx;
      } else {
        sensorFusion_B.u1 = sensorFusion_B.x[3].re / sensorFusion_B.b_dx;
        sensorFusion_B.rtb_x_im = sensorFusion_B.x[3].im / sensorFusion_B.b_dx;
      }

      sensorFusion_B.x[3].re = sensorFusion_B.u1;
      sensorFusion_B.x[3].im = sensorFusion_B.rtb_x_im;

      /*  Update apostriori error covariance estimate */
      /* '<S5>:1:32' P = (eye(size(K,1)) - K*H) * P_apriori; */
      memset(&sensorFusion_B.A[0], 0, sizeof(real_T) << 4U);
      for (sensorFusion_B.i = 0; sensorFusion_B.i < 4; sensorFusion_B.i++) {
        sensorFusion_B.A[sensorFusion_B.i + (sensorFusion_B.i << 2)] = 1.0;
        for (sensorFusion_B.s3_iter_o = 0; sensorFusion_B.s3_iter_o < 6;
             sensorFusion_B.s3_iter_o++) {
          sensorFusion_B.H_c[sensorFusion_B.s3_iter_o + 6 * sensorFusion_B.i].re
            = (real32_T)sensorFusion_B.H_m[6 * sensorFusion_B.i +
            sensorFusion_B.s3_iter_o];
          sensorFusion_B.H_c[sensorFusion_B.s3_iter_o + 6 * sensorFusion_B.i].im
            = 0.0F;
        }
      }

      for (sensorFusion_B.i = 0; sensorFusion_B.i < 4; sensorFusion_B.i++) {
        for (sensorFusion_B.s3_iter_o = 0; sensorFusion_B.s3_iter_o < 4;
             sensorFusion_B.s3_iter_o++) {
          sensorFusion_B.b_dx = 0.0F;
          sensorFusion_B.u1 = 0.0F;
          for (sensorFusion_B.i0 = 0; sensorFusion_B.i0 < 6; sensorFusion_B.i0++)
          {
            sensorFusion_B.b_dx += sensorFusion_B.K[(sensorFusion_B.i0 << 2) +
              sensorFusion_B.i].re * sensorFusion_B.H_c[6 *
              sensorFusion_B.s3_iter_o + sensorFusion_B.i0].re -
              sensorFusion_B.K[(sensorFusion_B.i0 << 2) + sensorFusion_B.i].im *
              sensorFusion_B.H_c[6 * sensorFusion_B.s3_iter_o +
              sensorFusion_B.i0].im;
            sensorFusion_B.u1 += sensorFusion_B.K[(sensorFusion_B.i0 << 2) +
              sensorFusion_B.i].re * sensorFusion_B.H_c[6 *
              sensorFusion_B.s3_iter_o + sensorFusion_B.i0].im +
              sensorFusion_B.K[(sensorFusion_B.i0 << 2) + sensorFusion_B.i].im *
              sensorFusion_B.H_c[6 * sensorFusion_B.s3_iter_o +
              sensorFusion_B.i0].re;
          }

          sensorFusion_B.A_b[sensorFusion_B.i + (sensorFusion_B.s3_iter_o << 2)]
            .re = (real32_T)sensorFusion_B.A[(sensorFusion_B.s3_iter_o << 2) +
            sensorFusion_B.i] - sensorFusion_B.b_dx;
          sensorFusion_B.A_b[sensorFusion_B.i + (sensorFusion_B.s3_iter_o << 2)]
            .im = 0.0F - sensorFusion_B.u1;
        }

        for (sensorFusion_B.s3_iter_o = 0; sensorFusion_B.s3_iter_o < 4;
             sensorFusion_B.s3_iter_o++) {
          sensorFusion_B.P[sensorFusion_B.i + (sensorFusion_B.s3_iter_o << 2)].
            re = (((sensorFusion_B.P_apriori[(sensorFusion_B.s3_iter_o << 2) + 1]
                    .re * sensorFusion_B.A_b[sensorFusion_B.i + 4].re -
                    sensorFusion_B.P_apriori[(sensorFusion_B.s3_iter_o << 2) + 1]
                    .im * sensorFusion_B.A_b[sensorFusion_B.i + 4].im) +
                   (sensorFusion_B.P_apriori[sensorFusion_B.s3_iter_o << 2].re *
                    sensorFusion_B.A_b[sensorFusion_B.i].re -
                    sensorFusion_B.P_apriori[sensorFusion_B.s3_iter_o << 2].im *
                    sensorFusion_B.A_b[sensorFusion_B.i].im)) +
                  (sensorFusion_B.P_apriori[(sensorFusion_B.s3_iter_o << 2) + 2]
                   .re * sensorFusion_B.A_b[sensorFusion_B.i + 8].re -
                   sensorFusion_B.P_apriori[(sensorFusion_B.s3_iter_o << 2) + 2]
                   .im * sensorFusion_B.A_b[sensorFusion_B.i + 8].im)) +
            (sensorFusion_B.P_apriori[(sensorFusion_B.s3_iter_o << 2) + 3].re *
             sensorFusion_B.A_b[sensorFusion_B.i + 12].re -
             sensorFusion_B.P_apriori[(sensorFusion_B.s3_iter_o << 2) + 3].im *
             sensorFusion_B.A_b[sensorFusion_B.i + 12].im);
          sensorFusion_B.P[sensorFusion_B.i + (sensorFusion_B.s3_iter_o << 2)].
            im = (((sensorFusion_B.P_apriori[(sensorFusion_B.s3_iter_o << 2) + 1]
                    .im * sensorFusion_B.A_b[sensorFusion_B.i + 4].re +
                    sensorFusion_B.P_apriori[(sensorFusion_B.s3_iter_o << 2) + 1]
                    .re * sensorFusion_B.A_b[sensorFusion_B.i + 4].im) +
                   (sensorFusion_B.P_apriori[sensorFusion_B.s3_iter_o << 2].im *
                    sensorFusion_B.A_b[sensorFusion_B.i].re +
                    sensorFusion_B.P_apriori[sensorFusion_B.s3_iter_o << 2].re *
                    sensorFusion_B.A_b[sensorFusion_B.i].im)) +
                  (sensorFusion_B.P_apriori[(sensorFusion_B.s3_iter_o << 2) + 2]
                   .im * sensorFusion_B.A_b[sensorFusion_B.i + 8].re +
                   sensorFusion_B.P_apriori[(sensorFusion_B.s3_iter_o << 2) + 2]
                   .re * sensorFusion_B.A_b[sensorFusion_B.i + 8].im)) +
            (sensorFusion_B.P_apriori[(sensorFusion_B.s3_iter_o << 2) + 3].im *
             sensorFusion_B.A_b[sensorFusion_B.i + 12].re +
             sensorFusion_B.P_apriori[(sensorFusion_B.s3_iter_o << 2) + 3].re *
             sensorFusion_B.A_b[sensorFusion_B.i + 12].im);
        }

        /* ComplexToRealImag: '<S3>/Complex to Real-Imag' */
        sensorFusion_B.ComplextoRealImag[sensorFusion_B.i] =
          sensorFusion_B.x[sensorFusion_B.i].re;
      }

      /* End of MATLAB Function: '<S3>/MATLAB Function' */

      /* ComplexToRealImag: '<S3>/Complex to Real-Imag1' */
      for (sensorFusion_B.i = 0; sensorFusion_B.i < 16; sensorFusion_B.i++) {
        sensorFusion_B.ComplextoRealImag1[sensorFusion_B.i] =
          sensorFusion_B.P[sensorFusion_B.i].re;
      }

      /* End of ComplexToRealImag: '<S3>/Complex to Real-Imag1' */

      /* Update for UnitDelay: '<S3>/Unit Delay' */
      sensorFusion_DW.UnitDelay_DSTATE[0] = sensorFusion_B.x[0];
      sensorFusion_DW.UnitDelay_DSTATE[1] = sensorFusion_B.x[1];
      sensorFusion_DW.UnitDelay_DSTATE[2] = sensorFusion_B.x[2];
      sensorFusion_DW.UnitDelay_DSTATE[3] = sensorFusion_B.x[3];

      /* Update for UnitDelay: '<S3>/Unit Delay1' */
      memcpy(&sensorFusion_DW.UnitDelay1_DSTATE[0], &sensorFusion_B.P[0], sizeof
             (creal32_T) << 4U);
      sensorFusion_B.s3_iter++;
    }

    /* End of Outputs for SubSystem: '<S2>/iterateAlg' */

    /* MATLAB Function: '<S4>/MATLAB Function' */
    /* MATLAB Function 'runSensorFusion/unpackData/MATLAB Function': '<S6>:1' */
    /* '<S6>:1:3' y = typecast(u,'uint32'); */
    memcpy(&sensorFusion_B.y_b, &sensorFusion_B.UDPReceive_o1[31], (size_t)1 *
           sizeof(uint32_T));

    /* Product: '<S4>/Product' incorporates:
     *  MATLAB Function: '<S4>/MATLAB Function'
     *  Sum: '<S4>/Sum'
     *  UnitDelay: '<S4>/Unit Delay1'
     *  UnitDelay: '<S4>/Unit Delay2'
     */
    sensorFusion_B.u0 = sensorFusion_B.y_b - sensorFusion_DW.UnitDelay2_DSTATE;
    uMultiWordMul(&sensorFusion_B.u0, 1, &sensorFusion_DW.UnitDelay1_DSTATE_k, 1,
                  &sensorFusion_B.r0.chunks[0U], 2);

    /* DataTypeConversion: '<S4>/Data Type Conversion' */
    sensorFusion_B.b_dx = uMultiWordSingle(&sensorFusion_B.r0.chunks[0U], 2, 0);

    /* UnitDelay: '<S4>/Unit Delay' */
    sensorFusion_B.u1 = sensorFusion_DW.UnitDelay_DSTATE_j;

    /* MinMax: '<S4>/MinMax' */
    if ((sensorFusion_B.b_dx >= sensorFusion_B.u1) || rtIsNaNF(sensorFusion_B.u1))
    {
      sensorFusion_B.MinMax = sensorFusion_B.b_dx;
    } else {
      sensorFusion_B.MinMax = sensorFusion_B.u1;
    }

    /* End of MinMax: '<S4>/MinMax' */

    /* Update for UnitDelay: '<S4>/Unit Delay2' incorporates:
     *  MATLAB Function: '<S4>/MATLAB Function'
     */
    sensorFusion_DW.UnitDelay2_DSTATE = sensorFusion_B.y_b;

    /* Update for UnitDelay: '<S4>/Unit Delay1' incorporates:
     *  Constant: '<S4>/Constant'
     */
    sensorFusion_DW.UnitDelay1_DSTATE_k = sensorFusion_P.Constant_Value_m;

    /* Update for UnitDelay: '<S4>/Unit Delay' */
    sensorFusion_DW.UnitDelay_DSTATE_j = sensorFusion_B.MinMax;
    sensorFusion_DW.runSensorFusion_SubsysRanBC = 4;
  }

  sensorFusion_PrevZCX.runSensorFusion_Trig_ZCE = sensorFusion_B.Compare;

  /* End of Outputs for SubSystem: '<Root>/runSensorFusion' */

  /* External mode */
  rtExtModeUploadCheckTrigger(1);

  {                                    /* Sample time: [0.001s, 0.0s] */
    rtExtModeUpload(0, sensorFusion_M->Timing.taskTime0);
  }

  /* signal main to stop simulation */
  {                                    /* Sample time: [0.001s, 0.0s] */
    if ((rtmGetTFinal(sensorFusion_M)!=-1) &&
        !((rtmGetTFinal(sensorFusion_M)-sensorFusion_M->Timing.taskTime0) >
          sensorFusion_M->Timing.taskTime0 * (DBL_EPSILON))) {
      rtmSetErrorStatus(sensorFusion_M, "Simulation finished");
    }

    if (rtmGetStopRequested(sensorFusion_M)) {
      rtmSetErrorStatus(sensorFusion_M, "Simulation finished");
    }
  }

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   */
  sensorFusion_M->Timing.taskTime0 =
    (++sensorFusion_M->Timing.clockTick0) * sensorFusion_M->Timing.stepSize0;
}

/* Model initialize function */
void sensorFusion_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)sensorFusion_M, 0,
                sizeof(RT_MODEL_sensorFusion_T));
  rtmSetTFinal(sensorFusion_M, -1);
  sensorFusion_M->Timing.stepSize0 = 0.001;

  /* External mode info */
  sensorFusion_M->Sizes.checksums[0] = (1983448965U);
  sensorFusion_M->Sizes.checksums[1] = (3041953648U);
  sensorFusion_M->Sizes.checksums[2] = (3714026635U);
  sensorFusion_M->Sizes.checksums[3] = (1382190736U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[7];
    sensorFusion_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    systemRan[1] = (sysRanDType *)&sensorFusion_DW.runSensorFusion_SubsysRanBC;
    systemRan[2] = (sysRanDType *)&sensorFusion_DW.runSensorFusion_SubsysRanBC;
    systemRan[3] = (sysRanDType *)&sensorFusion_DW.runSensorFusion_SubsysRanBC;
    systemRan[4] = (sysRanDType *)&sensorFusion_DW.runSensorFusion_SubsysRanBC;
    systemRan[5] = (sysRanDType *)&sensorFusion_DW.runSensorFusion_SubsysRanBC;
    systemRan[6] = (sysRanDType *)&sensorFusion_DW.runSensorFusion_SubsysRanBC;
    rteiSetModelMappingInfoPtr(sensorFusion_M->extModeInfo,
      &sensorFusion_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(sensorFusion_M->extModeInfo,
                        sensorFusion_M->Sizes.checksums);
    rteiSetTPtr(sensorFusion_M->extModeInfo, rtmGetTPtr(sensorFusion_M));
  }

  /* block I/O */
  (void) memset(((void *) &sensorFusion_B), 0,
                sizeof(B_sensorFusion_T));

  /* states (dwork) */
  (void) memset((void *)&sensorFusion_DW, 0,
                sizeof(DW_sensorFusion_T));

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    sensorFusion_M->SpecialInfo.mappingInfo = (&dtInfo);
    dtInfo.numDataTypes = 29;
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
    sErr = GetErrorBuffer(&sensorFusion_DW.UDPReceive_NetworkLib[0U]);
    CreateUDPInterface(&sensorFusion_DW.UDPReceive_NetworkLib[0U]);
    if (*sErr == 0) {
      LibCreate_Network(&sensorFusion_DW.UDPReceive_NetworkLib[0U], 0, "0.0.0.0",
                        25000, "0.0.0.0", -1, 8192, 4, 0);
    }

    if (*sErr == 0) {
      LibStart(&sensorFusion_DW.UDPReceive_NetworkLib[0U]);
    }

    if (*sErr != 0) {
      DestroyUDPInterface(&sensorFusion_DW.UDPReceive_NetworkLib[0U]);
      if (*sErr != 0) {
        rtmSetErrorStatus(sensorFusion_M, sErr);
        rtmSetStopRequested(sensorFusion_M, 1);
      }
    }

    /* End of Start for S-Function (sdspFromNetwork): '<Root>/UDP Receive' */
    sensorFusion_PrevZCX.runSensorFusion_Trig_ZCE = POS_ZCSIG;

    /* SystemInitialize for Triggered SubSystem: '<Root>/runSensorFusion' */
    /* InitializeConditions for UnitDelay: '<S4>/Unit Delay2' */
    sensorFusion_DW.UnitDelay2_DSTATE =
      sensorFusion_P.UnitDelay2_InitialCondition;

    /* InitializeConditions for UnitDelay: '<S4>/Unit Delay1' */
    sensorFusion_DW.UnitDelay1_DSTATE_k =
      sensorFusion_P.UnitDelay1_InitialCondition_d;

    /* InitializeConditions for UnitDelay: '<S4>/Unit Delay' */
    sensorFusion_DW.UnitDelay_DSTATE_j =
      sensorFusion_P.UnitDelay_InitialCondition_i;

    /* SystemInitialize for Iterator SubSystem: '<S2>/iterateAlg' */
    /* InitializeConditions for UnitDelay: '<S3>/Unit Delay' */
    sensorFusion_DW.UnitDelay_DSTATE[0].re =
      sensorFusion_P.UnitDelay_InitialCondition[0];
    sensorFusion_DW.UnitDelay_DSTATE[0].im = 0.0F;
    sensorFusion_DW.UnitDelay_DSTATE[1].re =
      sensorFusion_P.UnitDelay_InitialCondition[1];
    sensorFusion_DW.UnitDelay_DSTATE[1].im = 0.0F;
    sensorFusion_DW.UnitDelay_DSTATE[2].re =
      sensorFusion_P.UnitDelay_InitialCondition[2];
    sensorFusion_DW.UnitDelay_DSTATE[2].im = 0.0F;
    sensorFusion_DW.UnitDelay_DSTATE[3].re =
      sensorFusion_P.UnitDelay_InitialCondition[3];
    sensorFusion_DW.UnitDelay_DSTATE[3].im = 0.0F;

    /* InitializeConditions for UnitDelay: '<S3>/Unit Delay1' */
    for (i = 0; i < 16; i++) {
      sensorFusion_DW.UnitDelay1_DSTATE[i].re =
        sensorFusion_P.UnitDelay1_InitialCondition[i];
      sensorFusion_DW.UnitDelay1_DSTATE[i].im = 0.0F;
    }

    /* End of InitializeConditions for UnitDelay: '<S3>/Unit Delay1' */
    /* End of SystemInitialize for SubSystem: '<S2>/iterateAlg' */
    /* End of SystemInitialize for SubSystem: '<Root>/runSensorFusion' */
  }
}

/* Model terminate function */
void sensorFusion_terminate(void)
{
  char_T *sErr;

  /* Terminate for S-Function (sdspFromNetwork): '<Root>/UDP Receive' */
  sErr = GetErrorBuffer(&sensorFusion_DW.UDPReceive_NetworkLib[0U]);
  LibTerminate(&sensorFusion_DW.UDPReceive_NetworkLib[0U]);
  if (*sErr != 0) {
    rtmSetErrorStatus(sensorFusion_M, sErr);
    rtmSetStopRequested(sensorFusion_M, 1);
  }

  LibDestroy(&sensorFusion_DW.UDPReceive_NetworkLib[0U], 0);
  DestroyUDPInterface(&sensorFusion_DW.UDPReceive_NetworkLib[0U]);

  /* End of Terminate for S-Function (sdspFromNetwork): '<Root>/UDP Receive' */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
