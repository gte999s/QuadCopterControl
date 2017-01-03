/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: sensorTask.c
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

#include "sensorTask.h"
#include "sensorTask_private.h"
#include "sensorTask_dt.h"

/* Block signals (auto storage) */
B_sensorTask_T sensorTask_B;

/* Block states (auto storage) */
DW_sensorTask_T sensorTask_DW;

/* Real-time model */
RT_MODEL_sensorTask_T sensorTask_M_;
RT_MODEL_sensorTask_T *const sensorTask_M = &sensorTask_M_;

/* Model step function */
void sensorTask_step(void)
{
  char_T *sErr;

  /* Outputs for Atomic SubSystem: '<Root>/readSensors' */

  /* S-Function (readAccelGryoMag): '<S6>/readAccelGyroMagSfun' */
  readAccelGryoMag_Outputs_wrapper( &sensorTask_B.readAccelGyroMagSfun_o1[0],
    &sensorTask_B.readAccelGyroMagSfun_o2[0],
    &sensorTask_B.readAccelGyroMagSfun_o3[0],
    &sensorTask_B.readAccelGyroMagSfun_o4[0],
    &sensorTask_B.readAccelGyroMagSfun_o5[0],
    &sensorTask_B.readAccelGyroMagSfun_o6[0],
    &sensorTask_B.readAccelGyroMagSfun_o7[0],
    &sensorTask_B.readAccelGyroMagSfun_o8[0],
    &sensorTask_B.readAccelGyroMagSfun_o9[0],
    &sensorTask_B.readAccelGyroMagSfun_o10,
    &sensorTask_DW.readAccelGyroMagSfun_DSTATE);

  /* S-Function "readAccelGryoMag_wrapper" Block: <S6>/readAccelGyroMagSfun */
  readAccelGryoMag_Update_wrapper( &sensorTask_B.readAccelGyroMagSfun_o1[0],
    &sensorTask_B.readAccelGyroMagSfun_o2[0],
    &sensorTask_B.readAccelGyroMagSfun_o3[0],
    &sensorTask_B.readAccelGyroMagSfun_o4[0],
    &sensorTask_B.readAccelGyroMagSfun_o5[0],
    &sensorTask_B.readAccelGyroMagSfun_o6[0],
    &sensorTask_B.readAccelGyroMagSfun_o7[0],
    &sensorTask_B.readAccelGyroMagSfun_o8[0],
    &sensorTask_B.readAccelGyroMagSfun_o9[0],
    &sensorTask_B.readAccelGyroMagSfun_o10,
    &sensorTask_DW.readAccelGyroMagSfun_DSTATE);

  /* End of Outputs for SubSystem: '<Root>/readSensors' */

  /* SignalConversion: '<Root>/TmpSignal ConversionAtUDP SendInport1' */
  sensorTask_B.TmpSignalConversionAtUDPSendInp[0] =
    sensorTask_B.readAccelGyroMagSfun_o1[0];
  sensorTask_B.TmpSignalConversionAtUDPSendInp[1] =
    sensorTask_B.readAccelGyroMagSfun_o1[1];
  sensorTask_B.TmpSignalConversionAtUDPSendInp[2] =
    sensorTask_B.readAccelGyroMagSfun_o1[2];
  sensorTask_B.TmpSignalConversionAtUDPSendInp[3] =
    sensorTask_B.readAccelGyroMagSfun_o1[3];
  sensorTask_B.TmpSignalConversionAtUDPSendInp[4] =
    sensorTask_B.readAccelGyroMagSfun_o2[0];
  sensorTask_B.TmpSignalConversionAtUDPSendInp[5] =
    sensorTask_B.readAccelGyroMagSfun_o2[1];
  sensorTask_B.TmpSignalConversionAtUDPSendInp[6] =
    sensorTask_B.readAccelGyroMagSfun_o2[2];
  sensorTask_B.TmpSignalConversionAtUDPSendInp[7] =
    sensorTask_B.readAccelGyroMagSfun_o2[3];
  sensorTask_B.TmpSignalConversionAtUDPSendInp[8] =
    sensorTask_B.readAccelGyroMagSfun_o3[0];
  sensorTask_B.TmpSignalConversionAtUDPSendInp[9] =
    sensorTask_B.readAccelGyroMagSfun_o3[1];
  sensorTask_B.TmpSignalConversionAtUDPSendInp[10] =
    sensorTask_B.readAccelGyroMagSfun_o3[2];
  sensorTask_B.TmpSignalConversionAtUDPSendInp[11] =
    sensorTask_B.readAccelGyroMagSfun_o3[3];
  sensorTask_B.TmpSignalConversionAtUDPSendInp[12] =
    sensorTask_B.readAccelGyroMagSfun_o4[0];
  sensorTask_B.TmpSignalConversionAtUDPSendInp[13] =
    sensorTask_B.readAccelGyroMagSfun_o4[1];
  sensorTask_B.TmpSignalConversionAtUDPSendInp[14] =
    sensorTask_B.readAccelGyroMagSfun_o4[2];
  sensorTask_B.TmpSignalConversionAtUDPSendInp[15] =
    sensorTask_B.readAccelGyroMagSfun_o4[3];
  sensorTask_B.TmpSignalConversionAtUDPSendInp[16] =
    sensorTask_B.readAccelGyroMagSfun_o5[0];
  sensorTask_B.TmpSignalConversionAtUDPSendInp[17] =
    sensorTask_B.readAccelGyroMagSfun_o5[1];
  sensorTask_B.TmpSignalConversionAtUDPSendInp[18] =
    sensorTask_B.readAccelGyroMagSfun_o5[2];
  sensorTask_B.TmpSignalConversionAtUDPSendInp[19] =
    sensorTask_B.readAccelGyroMagSfun_o5[3];
  sensorTask_B.TmpSignalConversionAtUDPSendInp[20] =
    sensorTask_B.readAccelGyroMagSfun_o6[0];
  sensorTask_B.TmpSignalConversionAtUDPSendInp[21] =
    sensorTask_B.readAccelGyroMagSfun_o6[1];
  sensorTask_B.TmpSignalConversionAtUDPSendInp[22] =
    sensorTask_B.readAccelGyroMagSfun_o6[2];
  sensorTask_B.TmpSignalConversionAtUDPSendInp[23] =
    sensorTask_B.readAccelGyroMagSfun_o6[3];
  sensorTask_B.TmpSignalConversionAtUDPSendInp[24] =
    sensorTask_B.readAccelGyroMagSfun_o7[0];
  sensorTask_B.TmpSignalConversionAtUDPSendInp[25] =
    sensorTask_B.readAccelGyroMagSfun_o7[1];
  sensorTask_B.TmpSignalConversionAtUDPSendInp[26] =
    sensorTask_B.readAccelGyroMagSfun_o8[0];
  sensorTask_B.TmpSignalConversionAtUDPSendInp[27] =
    sensorTask_B.readAccelGyroMagSfun_o8[1];
  sensorTask_B.TmpSignalConversionAtUDPSendInp[28] =
    sensorTask_B.readAccelGyroMagSfun_o9[0];
  sensorTask_B.TmpSignalConversionAtUDPSendInp[29] =
    sensorTask_B.readAccelGyroMagSfun_o9[1];
  sensorTask_B.TmpSignalConversionAtUDPSendInp[30] =
    sensorTask_B.readAccelGyroMagSfun_o10;

  /* Update for S-Function (sdspToNetwork): '<Root>/UDP Send' */
  sErr = GetErrorBuffer(&sensorTask_DW.UDPSend_NetworkLib[0U]);
  LibUpdate_Network(&sensorTask_DW.UDPSend_NetworkLib[0U],
                    &sensorTask_B.TmpSignalConversionAtUDPSendInp[0U], 31);
  if (*sErr != 0) {
    rtmSetErrorStatus(sensorTask_M, sErr);
    rtmSetStopRequested(sensorTask_M, 1);
  }

  /* End of Update for S-Function (sdspToNetwork): '<Root>/UDP Send' */

  /* External mode */
  rtExtModeUploadCheckTrigger(1);

  {                                    /* Sample time: [0.001s, 0.0s] */
    rtExtModeUpload(0, sensorTask_M->Timing.taskTime0);
  }

  /* signal main to stop simulation */
  {                                    /* Sample time: [0.001s, 0.0s] */
    if ((rtmGetTFinal(sensorTask_M)!=-1) &&
        !((rtmGetTFinal(sensorTask_M)-sensorTask_M->Timing.taskTime0) >
          sensorTask_M->Timing.taskTime0 * (DBL_EPSILON))) {
      rtmSetErrorStatus(sensorTask_M, "Simulation finished");
    }

    if (rtmGetStopRequested(sensorTask_M)) {
      rtmSetErrorStatus(sensorTask_M, "Simulation finished");
    }
  }

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   */
  sensorTask_M->Timing.taskTime0 =
    (++sensorTask_M->Timing.clockTick0) * sensorTask_M->Timing.stepSize0;
}

/* Model initialize function */
void sensorTask_initialize(void)
{
  /* Registration code */

  /* initialize real-time model */
  (void) memset((void *)sensorTask_M, 0,
                sizeof(RT_MODEL_sensorTask_T));
  rtmSetTFinal(sensorTask_M, -1);
  sensorTask_M->Timing.stepSize0 = 0.001;

  /* External mode info */
  sensorTask_M->Sizes.checksums[0] = (3935354751U);
  sensorTask_M->Sizes.checksums[1] = (1656119003U);
  sensorTask_M->Sizes.checksums[2] = (818636135U);
  sensorTask_M->Sizes.checksums[3] = (2569935220U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[2];
    sensorTask_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    systemRan[1] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(sensorTask_M->extModeInfo,
      &sensorTask_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(sensorTask_M->extModeInfo, sensorTask_M->Sizes.checksums);
    rteiSetTPtr(sensorTask_M->extModeInfo, rtmGetTPtr(sensorTask_M));
  }

  /* block I/O */
  (void) memset(((void *) &sensorTask_B), 0,
                sizeof(B_sensorTask_T));

  /* states (dwork) */
  (void) memset((void *)&sensorTask_DW, 0,
                sizeof(DW_sensorTask_T));

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    sensorTask_M->SpecialInfo.mappingInfo = (&dtInfo);
    dtInfo.numDataTypes = 14;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.BTransTable = &rtBTransTable;
  }

  {
    char_T *sErr;

    /* Start for S-Function (sdspToNetwork): '<Root>/UDP Send' */
    sErr = GetErrorBuffer(&sensorTask_DW.UDPSend_NetworkLib[0U]);
    CreateUDPInterface(&sensorTask_DW.UDPSend_NetworkLib[0U]);
    if (*sErr == 0) {
      LibCreate_Network(&sensorTask_DW.UDPSend_NetworkLib[0U], 1,
                        "255.255.255.255", -1, "255.255.255.255", 25000, 8192, 4,
                        0);
    }

    if (*sErr == 0) {
      LibStart(&sensorTask_DW.UDPSend_NetworkLib[0U]);
    }

    if (*sErr != 0) {
      DestroyUDPInterface(&sensorTask_DW.UDPSend_NetworkLib[0U]);
      if (*sErr != 0) {
        rtmSetErrorStatus(sensorTask_M, sErr);
        rtmSetStopRequested(sensorTask_M, 1);
      }
    }

    /* End of Start for S-Function (sdspToNetwork): '<Root>/UDP Send' */

    /* SystemInitialize for Atomic SubSystem: '<Root>/readSensors' */

    /* S-Function Block: <S6>/readAccelGyroMagSfun */
    {
      real_T initVector[1] = { 0 };

      {
        int_T i1;
        for (i1=0; i1 < 1; i1++) {
          sensorTask_DW.readAccelGyroMagSfun_DSTATE = initVector[0];
        }
      }
    }

    /* End of SystemInitialize for SubSystem: '<Root>/readSensors' */
  }
}

/* Model terminate function */
void sensorTask_terminate(void)
{
  char_T *sErr;

  /* Terminate for S-Function (sdspToNetwork): '<Root>/UDP Send' */
  sErr = GetErrorBuffer(&sensorTask_DW.UDPSend_NetworkLib[0U]);
  LibTerminate(&sensorTask_DW.UDPSend_NetworkLib[0U]);
  if (*sErr != 0) {
    rtmSetErrorStatus(sensorTask_M, sErr);
    rtmSetStopRequested(sensorTask_M, 1);
  }

  LibDestroy(&sensorTask_DW.UDPSend_NetworkLib[0U], 1);
  DestroyUDPInterface(&sensorTask_DW.UDPSend_NetworkLib[0U]);

  /* End of Terminate for S-Function (sdspToNetwork): '<Root>/UDP Send' */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
