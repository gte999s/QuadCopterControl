/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: ert_main.c
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

#include <stdio.h>
#include <stdlib.h>
#include "flightControl.h"
#include "flightControl_private.h"
#include "rtwtypes.h"
#include "limits.h"
#include "rt_nonfinite.h"
#include "linuxinitialize.h"
#define UNUSED(x)                      x = x

/* Function prototype declaration*/
void exitFcn(int sig);
void *terminateTask(void *arg);
void *baseRateTask(void *arg);
void *subrateTask(void *arg);
volatile boolean_T runModel = true;
sem_t stopSem;
sem_t baserateTaskSem;
pthread_t schedulerThread;
pthread_t baseRateThread;
unsigned long threadJoinStatus[8];
int terminatingmodel = 0;
pthread_mutex_t rateTaskFcnRunningMutex[1];
void testForRateOverrun(int rateID);
void *baseRateTask(void *arg)
{
  runModel = (rtmGetErrorStatus(flightControl_M) == (NULL)) &&
    !rtmGetStopRequested(flightControl_M);
  while (runModel) {
    sem_wait(&baserateTaskSem);
    pthread_mutex_lock(&rateTaskFcnRunningMutex[0]);

    /* External mode */
    {
      boolean_T rtmStopReq = false;
      rtExtModePauseIfNeeded(flightControl_M->extModeInfo, 1, &rtmStopReq);
      if (rtmStopReq) {
        rtmSetStopRequested(flightControl_M, true);
      }

      if (rtmGetStopRequested(flightControl_M) == true) {
        rtmSetErrorStatus(flightControl_M, "Simulation finished");
        break;
      }
    }

    /* External mode */
    {
      boolean_T rtmStopReq = false;
      rtExtModeOneStep(flightControl_M->extModeInfo, 1, &rtmStopReq);
      if (rtmStopReq) {
        rtmSetStopRequested(flightControl_M, true);
      }
    }

    flightControl_step();

    /* Get model outputs here */
    rtExtModeCheckEndTrigger();
    pthread_mutex_unlock(&rateTaskFcnRunningMutex[0]);
    runModel = (rtmGetErrorStatus(flightControl_M) == (NULL)) &&
      !rtmGetStopRequested(flightControl_M);
  }

  runModel = 0;
  terminateTask(arg);
  pthread_exit((void *)0);
  return NULL;
}

void exitFcn(int sig)
{
  UNUSED(sig);
  rtmSetErrorStatus(flightControl_M, "stopping the model");
}

void *terminateTask(void *arg)
{
  UNUSED(arg);
  terminatingmodel = 1;
  printf("**terminating the model**\n");
  fflush(stdout);

  {
    runModel = 0;
  }

  rtExtModeShutdown(1);

  /* Disable rt_OneStep() here */

  /* Terminate model */
  flightControl_terminate();
  sem_post(&stopSem);
  return NULL;
}

void testForRateOverrun(int rateID)
{
  if (pthread_mutex_trylock(&rateTaskFcnRunningMutex[rateID]) == 0) {
    pthread_mutex_unlock(&rateTaskFcnRunningMutex[rateID]);
  } else {
    reportOverrun(rateID);
  }
}

int main(int argc, char **argv)
{
  UNUSED(argc);
  UNUSED(argv);
  printf("**starting the model**\n");
  fflush(stdout);
  rtmSetErrorStatus(flightControl_M, 0);
  rtExtModeParseArgs(argc, (const char_T **)argv, NULL);

  /* Initialize model */
  flightControl_initialize();

  /* External mode */
  rtSetTFinalForExtMode(&rtmGetTFinal(flightControl_M));
  rtExtModeCheckInit(1);

  {
    boolean_T rtmStopReq = false;
    rtExtModeWaitForStartPkt(flightControl_M->extModeInfo, 1, &rtmStopReq);
    if (rtmStopReq) {
      rtmSetStopRequested(flightControl_M, true);
    }
  }

  rtERTExtModeStartMsg();

  /* Call RTOS Initialization function */
  myRTOSInit(0.001, 0);

  /* Wait for stop semaphore */
  sem_wait(&stopSem);

  {
    int idxMutex;
    for (idxMutex=0; idxMutex<1; idxMutex++)
      pthread_mutex_destroy(&rateTaskFcnRunningMutex[idxMutex]);
  }

  return 0;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
