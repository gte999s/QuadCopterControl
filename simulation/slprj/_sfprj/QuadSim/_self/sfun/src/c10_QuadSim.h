#ifndef __c10_QuadSim_h__
#define __c10_QuadSim_h__

/* Include files */
#include "sf_runtime/sfc_sf.h"
#include "sf_runtime/sfc_mex.h"
#include "rtwtypes.h"
#include "multiword_types.h"

/* Type Definitions */
#ifndef typedef_SFc10_QuadSimInstanceStruct
#define typedef_SFc10_QuadSimInstanceStruct

typedef struct {
  SimStruct *S;
  ChartInfoStruct chartInfo;
  uint32_T chartNumber;
  uint32_T instanceNumber;
  int32_T c10_sfEvent;
  boolean_T c10_isStable;
  boolean_T c10_doneDoubleBufferReInit;
  uint8_T c10_is_active_c10_QuadSim;
  real32_T c10_qLocal[4];
  boolean_T c10_qLocal_not_empty;
  real_T c10_counter;
  boolean_T c10_counter_not_empty;
  real32_T (*c10_Accelerometer)[12];
  real32_T (*c10_q)[4];
  real32_T (*c10_Gyroscope)[12];
  real32_T (*c10_Magnetometer)[6];
  real32_T *c10_Beta;
} SFc10_QuadSimInstanceStruct;

#endif                                 /*typedef_SFc10_QuadSimInstanceStruct*/

/* Named Constants */

/* Variable Declarations */
extern struct SfDebugInstanceStruct *sfGlobalDebugInstanceStruct;

/* Variable Definitions */

/* Function Declarations */
extern const mxArray *sf_c10_QuadSim_get_eml_resolved_functions_info(void);

/* Function Definitions */
extern void sf_c10_QuadSim_get_check_sum(mxArray *plhs[]);
extern void c10_QuadSim_method_dispatcher(SimStruct *S, int_T method, void *data);

#endif
