/* Include files */

#include <stddef.h>
#include "blas.h"
#include "QuadSim_sfun.h"
#include "c10_QuadSim.h"
#include "mwmathutil.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "QuadSim_sfun_debug_macros.h"
#define _SF_MEX_LISTEN_FOR_CTRL_C(S)   sf_mex_listen_for_ctrl_c_with_debugger(S, sfGlobalDebugInstanceStruct);

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization);
static void chart_debug_initialize_data_addresses(SimStruct *S);
static const mxArray* sf_opaque_get_hover_data_for_msg(void *chartInstance,
  int32_T msgSSID);

/* Type Definitions */

/* Named Constants */
#define CALL_EVENT                     (-1)

/* Variable Declarations */

/* Variable Definitions */
static real_T _sfTime_;
static const char * c10_debug_family_names[13] = { "qIn", "x", "magInterp", "i",
  "nargin", "nargout", "Accelerometer", "Gyroscope", "Magnetometer", "Beta", "q",
  "qLocal", "counter" };

static const char * c10_b_debug_family_names[4] = { "nargin", "nargout", "q",
  "qConj" };

static const char * c10_c_debug_family_names[5] = { "nargin", "nargout", "a",
  "b", "ab" };

static const char * c10_d_debug_family_names[5] = { "nargin", "nargout", "a",
  "b", "ab" };

static const char * c10_e_debug_family_names[5] = { "nargin", "nargout", "a",
  "b", "ab" };

static const char * c10_f_debug_family_names[15] = { "SamplePeriod", "h", "b",
  "F", "J", "step", "qDot", "nargin", "nargout", "qIn", "Accelerometer",
  "Gyroscope", "Magnetometer", "Beta", "q" };

/* Function Declarations */
static void initialize_c10_QuadSim(SFc10_QuadSimInstanceStruct *chartInstance);
static void initialize_params_c10_QuadSim(SFc10_QuadSimInstanceStruct
  *chartInstance);
static void enable_c10_QuadSim(SFc10_QuadSimInstanceStruct *chartInstance);
static void disable_c10_QuadSim(SFc10_QuadSimInstanceStruct *chartInstance);
static void c10_update_debugger_state_c10_QuadSim(SFc10_QuadSimInstanceStruct
  *chartInstance);
static const mxArray *get_sim_state_c10_QuadSim(SFc10_QuadSimInstanceStruct
  *chartInstance);
static void set_sim_state_c10_QuadSim(SFc10_QuadSimInstanceStruct *chartInstance,
  const mxArray *c10_st);
static void finalize_c10_QuadSim(SFc10_QuadSimInstanceStruct *chartInstance);
static void sf_gateway_c10_QuadSim(SFc10_QuadSimInstanceStruct *chartInstance);
static void mdl_start_c10_QuadSim(SFc10_QuadSimInstanceStruct *chartInstance);
static void initSimStructsc10_QuadSim(SFc10_QuadSimInstanceStruct *chartInstance);
static void init_script_number_translation(uint32_T c10_machineNumber, uint32_T
  c10_chartNumber, uint32_T c10_instanceNumber);
static const mxArray *c10_sf_marshallOut(void *chartInstanceVoid, void
  *c10_inData);
static real_T c10_emlrt_marshallIn(SFc10_QuadSimInstanceStruct *chartInstance,
  const mxArray *c10_b_counter, const char_T *c10_identifier, boolean_T
  *c10_svPtr);
static real_T c10_b_emlrt_marshallIn(SFc10_QuadSimInstanceStruct *chartInstance,
  const mxArray *c10_u, const emlrtMsgIdentifier *c10_parentId, boolean_T
  *c10_svPtr);
static void c10_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c10_mxArrayInData, const char_T *c10_varName, void *c10_outData);
static const mxArray *c10_b_sf_marshallOut(void *chartInstanceVoid, void
  *c10_inData);
static void c10_c_emlrt_marshallIn(SFc10_QuadSimInstanceStruct *chartInstance,
  const mxArray *c10_b_qLocal, const char_T *c10_identifier, boolean_T
  *c10_svPtr, real32_T c10_y[4]);
static void c10_d_emlrt_marshallIn(SFc10_QuadSimInstanceStruct *chartInstance,
  const mxArray *c10_u, const emlrtMsgIdentifier *c10_parentId, boolean_T
  *c10_svPtr, real32_T c10_y[4]);
static void c10_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c10_mxArrayInData, const char_T *c10_varName, void *c10_outData);
static const mxArray *c10_c_sf_marshallOut(void *chartInstanceVoid, void
  *c10_inData);
static void c10_e_emlrt_marshallIn(SFc10_QuadSimInstanceStruct *chartInstance,
  const mxArray *c10_b_q, const char_T *c10_identifier, real32_T c10_y[4]);
static void c10_f_emlrt_marshallIn(SFc10_QuadSimInstanceStruct *chartInstance,
  const mxArray *c10_u, const emlrtMsgIdentifier *c10_parentId, real32_T c10_y[4]);
static void c10_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c10_mxArrayInData, const char_T *c10_varName, void *c10_outData);
static const mxArray *c10_d_sf_marshallOut(void *chartInstanceVoid, void
  *c10_inData);
static const mxArray *c10_e_sf_marshallOut(void *chartInstanceVoid, void
  *c10_inData);
static const mxArray *c10_f_sf_marshallOut(void *chartInstanceVoid, void
  *c10_inData);
static const mxArray *c10_g_sf_marshallOut(void *chartInstanceVoid, void
  *c10_inData);
static real_T c10_g_emlrt_marshallIn(SFc10_QuadSimInstanceStruct *chartInstance,
  const mxArray *c10_u, const emlrtMsgIdentifier *c10_parentId);
static void c10_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c10_mxArrayInData, const char_T *c10_varName, void *c10_outData);
static void c10_h_emlrt_marshallIn(SFc10_QuadSimInstanceStruct *chartInstance,
  const mxArray *c10_u, const emlrtMsgIdentifier *c10_parentId, real32_T c10_y
  [12]);
static void c10_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c10_mxArrayInData, const char_T *c10_varName, void *c10_outData);
static const mxArray *c10_h_sf_marshallOut(void *chartInstanceVoid, void
  *c10_inData);
static void c10_i_emlrt_marshallIn(SFc10_QuadSimInstanceStruct *chartInstance,
  const mxArray *c10_u, const emlrtMsgIdentifier *c10_parentId, real32_T c10_y[4]);
static void c10_f_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c10_mxArrayInData, const char_T *c10_varName, void *c10_outData);
static const mxArray *c10_i_sf_marshallOut(void *chartInstanceVoid, void
  *c10_inData);
static void c10_j_emlrt_marshallIn(SFc10_QuadSimInstanceStruct *chartInstance,
  const mxArray *c10_u, const emlrtMsgIdentifier *c10_parentId, real_T c10_y[4]);
static void c10_g_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c10_mxArrayInData, const char_T *c10_varName, void *c10_outData);
static const mxArray *c10_j_sf_marshallOut(void *chartInstanceVoid, void
  *c10_inData);
static void c10_k_emlrt_marshallIn(SFc10_QuadSimInstanceStruct *chartInstance,
  const mxArray *c10_u, const emlrtMsgIdentifier *c10_parentId, real32_T c10_y[4]);
static void c10_h_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c10_mxArrayInData, const char_T *c10_varName, void *c10_outData);
static real32_T c10_l_emlrt_marshallIn(SFc10_QuadSimInstanceStruct
  *chartInstance, const mxArray *c10_u, const emlrtMsgIdentifier *c10_parentId);
static void c10_i_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c10_mxArrayInData, const char_T *c10_varName, void *c10_outData);
static const mxArray *c10_k_sf_marshallOut(void *chartInstanceVoid, void
  *c10_inData);
static void c10_m_emlrt_marshallIn(SFc10_QuadSimInstanceStruct *chartInstance,
  const mxArray *c10_u, const emlrtMsgIdentifier *c10_parentId, real32_T c10_y[3]);
static void c10_j_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c10_mxArrayInData, const char_T *c10_varName, void *c10_outData);
static const mxArray *c10_l_sf_marshallOut(void *chartInstanceVoid, void
  *c10_inData);
static void c10_n_emlrt_marshallIn(SFc10_QuadSimInstanceStruct *chartInstance,
  const mxArray *c10_u, const emlrtMsgIdentifier *c10_parentId, real32_T c10_y
  [24]);
static void c10_k_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c10_mxArrayInData, const char_T *c10_varName, void *c10_outData);
static const mxArray *c10_m_sf_marshallOut(void *chartInstanceVoid, void
  *c10_inData);
static void c10_o_emlrt_marshallIn(SFc10_QuadSimInstanceStruct *chartInstance,
  const mxArray *c10_u, const emlrtMsgIdentifier *c10_parentId, real32_T c10_y[6]);
static void c10_l_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c10_mxArrayInData, const char_T *c10_varName, void *c10_outData);
static const mxArray *c10_n_sf_marshallOut(void *chartInstanceVoid, void
  *c10_inData);
static void c10_p_emlrt_marshallIn(SFc10_QuadSimInstanceStruct *chartInstance,
  const mxArray *c10_u, const emlrtMsgIdentifier *c10_parentId, real_T c10_y[4]);
static void c10_m_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c10_mxArrayInData, const char_T *c10_varName, void *c10_outData);
static void c10_scalarEg(SFc10_QuadSimInstanceStruct *chartInstance);
static void c10_interp1_work(SFc10_QuadSimInstanceStruct *chartInstance,
  real32_T c10_y[6], real32_T c10_yi[12]);
static void c10_StringToMethodID(SFc10_QuadSimInstanceStruct *chartInstance);
static void c10_strncmpi(SFc10_QuadSimInstanceStruct *chartInstance);
static void c10_b_strncmpi(SFc10_QuadSimInstanceStruct *chartInstance);
static void c10_c_strncmpi(SFc10_QuadSimInstanceStruct *chartInstance);
static void c10_d_strncmpi(SFc10_QuadSimInstanceStruct *chartInstance);
static boolean_T c10_isnan(SFc10_QuadSimInstanceStruct *chartInstance, real_T
  c10_x);
static void c10_error(SFc10_QuadSimInstanceStruct *chartInstance);
static void c10_runMadwickUpdate(SFc10_QuadSimInstanceStruct *chartInstance,
  real32_T c10_qIn[4], real32_T c10_b_Accelerometer[3], real32_T
  c10_b_Gyroscope[3], real32_T c10_b_Magnetometer[3], real32_T c10_b_Beta,
  real32_T c10_b_q[4]);
static void c10_abs(SFc10_QuadSimInstanceStruct *chartInstance, real32_T c10_x[3],
                    real32_T c10_y[3]);
static boolean_T c10_all(SFc10_QuadSimInstanceStruct *chartInstance, boolean_T
  c10_x[3]);
static real32_T c10_norm(SFc10_QuadSimInstanceStruct *chartInstance, real32_T
  c10_x[3]);
static void c10_realmin(SFc10_QuadSimInstanceStruct *chartInstance);
static real32_T c10_b_abs(SFc10_QuadSimInstanceStruct *chartInstance, real32_T
  c10_x);
static void c10_quaternConj(SFc10_QuadSimInstanceStruct *chartInstance, real32_T
  c10_b_q[4], real32_T c10_qConj[4]);
static void c10_quaternProd(SFc10_QuadSimInstanceStruct *chartInstance, real32_T
  c10_a[4], real32_T c10_b[4], real_T c10_ab[4]);
static void c10_b_quaternProd(SFc10_QuadSimInstanceStruct *chartInstance,
  real32_T c10_a[4], real_T c10_b[4], real_T c10_ab[4]);
static real_T c10_b_norm(SFc10_QuadSimInstanceStruct *chartInstance, real_T
  c10_x[2]);
static real32_T c10_mpower(SFc10_QuadSimInstanceStruct *chartInstance, real32_T
  c10_a);
static void c10_b_scalarEg(SFc10_QuadSimInstanceStruct *chartInstance);
static void c10_dimagree(SFc10_QuadSimInstanceStruct *chartInstance);
static void c10_b_error(SFc10_QuadSimInstanceStruct *chartInstance);
static void c10_c_scalarEg(SFc10_QuadSimInstanceStruct *chartInstance);
static void c10_d_scalarEg(SFc10_QuadSimInstanceStruct *chartInstance);
static real32_T c10_c_norm(SFc10_QuadSimInstanceStruct *chartInstance, real32_T
  c10_x[4]);
static const mxArray *c10_o_sf_marshallOut(void *chartInstanceVoid, void
  *c10_inData);
static int32_T c10_q_emlrt_marshallIn(SFc10_QuadSimInstanceStruct *chartInstance,
  const mxArray *c10_u, const emlrtMsgIdentifier *c10_parentId);
static void c10_n_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c10_mxArrayInData, const char_T *c10_varName, void *c10_outData);
static uint8_T c10_r_emlrt_marshallIn(SFc10_QuadSimInstanceStruct *chartInstance,
  const mxArray *c10_b_is_active_c10_QuadSim, const char_T *c10_identifier);
static uint8_T c10_s_emlrt_marshallIn(SFc10_QuadSimInstanceStruct *chartInstance,
  const mxArray *c10_u, const emlrtMsgIdentifier *c10_parentId);
static void init_dsm_address_info(SFc10_QuadSimInstanceStruct *chartInstance);
static void init_simulink_io_address(SFc10_QuadSimInstanceStruct *chartInstance);

/* Function Definitions */
static void initialize_c10_QuadSim(SFc10_QuadSimInstanceStruct *chartInstance)
{
  if (sf_is_first_init_cond(chartInstance->S)) {
    initSimStructsc10_QuadSim(chartInstance);
    chart_debug_initialize_data_addresses(chartInstance->S);
  }

  chartInstance->c10_sfEvent = CALL_EVENT;
  _sfTime_ = sf_get_time(chartInstance->S);
  chartInstance->c10_qLocal_not_empty = false;
  chartInstance->c10_counter_not_empty = false;
  chartInstance->c10_is_active_c10_QuadSim = 0U;
}

static void initialize_params_c10_QuadSim(SFc10_QuadSimInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void enable_c10_QuadSim(SFc10_QuadSimInstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void disable_c10_QuadSim(SFc10_QuadSimInstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void c10_update_debugger_state_c10_QuadSim(SFc10_QuadSimInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static const mxArray *get_sim_state_c10_QuadSim(SFc10_QuadSimInstanceStruct
  *chartInstance)
{
  const mxArray *c10_st;
  const mxArray *c10_y = NULL;
  const mxArray *c10_b_y = NULL;
  real_T c10_hoistedGlobal;
  real_T c10_u;
  const mxArray *c10_c_y = NULL;
  const mxArray *c10_d_y = NULL;
  uint8_T c10_b_hoistedGlobal;
  uint8_T c10_b_u;
  const mxArray *c10_e_y = NULL;
  c10_st = NULL;
  c10_st = NULL;
  c10_y = NULL;
  sf_mex_assign(&c10_y, sf_mex_createcellmatrix(4, 1), false);
  c10_b_y = NULL;
  sf_mex_assign(&c10_b_y, sf_mex_create("y", *chartInstance->c10_q, 1, 0U, 1U,
    0U, 2, 4, 1), false);
  sf_mex_setcell(c10_y, 0, c10_b_y);
  c10_hoistedGlobal = chartInstance->c10_counter;
  c10_u = c10_hoistedGlobal;
  c10_c_y = NULL;
  if (!chartInstance->c10_counter_not_empty) {
    sf_mex_assign(&c10_c_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  false);
  } else {
    sf_mex_assign(&c10_c_y, sf_mex_create("y", &c10_u, 0, 0U, 0U, 0U, 0), false);
  }

  sf_mex_setcell(c10_y, 1, c10_c_y);
  c10_d_y = NULL;
  if (!chartInstance->c10_qLocal_not_empty) {
    sf_mex_assign(&c10_d_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  false);
  } else {
    sf_mex_assign(&c10_d_y, sf_mex_create("y", chartInstance->c10_qLocal, 1, 0U,
      1U, 0U, 1, 4), false);
  }

  sf_mex_setcell(c10_y, 2, c10_d_y);
  c10_b_hoistedGlobal = chartInstance->c10_is_active_c10_QuadSim;
  c10_b_u = c10_b_hoistedGlobal;
  c10_e_y = NULL;
  sf_mex_assign(&c10_e_y, sf_mex_create("y", &c10_b_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c10_y, 3, c10_e_y);
  sf_mex_assign(&c10_st, c10_y, false);
  return c10_st;
}

static void set_sim_state_c10_QuadSim(SFc10_QuadSimInstanceStruct *chartInstance,
  const mxArray *c10_st)
{
  const mxArray *c10_u;
  real32_T c10_fv0[4];
  int32_T c10_i0;
  real32_T c10_fv1[4];
  int32_T c10_i1;
  chartInstance->c10_doneDoubleBufferReInit = true;
  c10_u = sf_mex_dup(c10_st);
  c10_e_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell("q", c10_u, 0)),
    "q", c10_fv0);
  for (c10_i0 = 0; c10_i0 < 4; c10_i0++) {
    (*chartInstance->c10_q)[c10_i0] = c10_fv0[c10_i0];
  }

  chartInstance->c10_counter = c10_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell("counter", c10_u, 1)), "counter",
    &chartInstance->c10_counter_not_empty);
  c10_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell("qLocal",
    c10_u, 2)), "qLocal", &chartInstance->c10_qLocal_not_empty, c10_fv1);
  for (c10_i1 = 0; c10_i1 < 4; c10_i1++) {
    chartInstance->c10_qLocal[c10_i1] = c10_fv1[c10_i1];
  }

  chartInstance->c10_is_active_c10_QuadSim = c10_r_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell("is_active_c10_QuadSim", c10_u, 3)),
     "is_active_c10_QuadSim");
  sf_mex_destroy(&c10_u);
  c10_update_debugger_state_c10_QuadSim(chartInstance);
  sf_mex_destroy(&c10_st);
}

static void finalize_c10_QuadSim(SFc10_QuadSimInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void sf_gateway_c10_QuadSim(SFc10_QuadSimInstanceStruct *chartInstance)
{
  int32_T c10_i2;
  int32_T c10_i3;
  int32_T c10_i4;
  real32_T c10_hoistedGlobal;
  int32_T c10_i5;
  real32_T c10_b_Accelerometer[12];
  int32_T c10_i6;
  real32_T c10_b_Gyroscope[12];
  int32_T c10_i7;
  real32_T c10_b_Magnetometer[6];
  real32_T c10_b_Beta;
  uint32_T c10_debug_family_var_map[13];
  real32_T c10_qIn[4];
  real_T c10_x;
  real32_T c10_magInterp[12];
  real_T c10_i;
  real_T c10_nargin = 4.0;
  real_T c10_nargout = 1.0;
  real32_T c10_b_q[4];
  int32_T c10_i8;
  static real32_T c10_fv2[4] = { 1.0F, 0.0F, 0.0F, 0.0F };

  int32_T c10_i9;
  int32_T c10_i10;
  int32_T c10_i11;
  int32_T c10_i12;
  int32_T c10_i13;
  real32_T c10_varargin_2[6];
  int32_T c10_i14;
  real32_T c10_b_varargin_2[6];
  real32_T c10_Vq[12];
  int32_T c10_i15;
  int32_T c10_i16;
  int32_T c10_i17;
  int32_T c10_i18;
  int32_T c10_b_i;
  int32_T c10_i19;
  real32_T c10_b_qIn[4];
  int32_T c10_c_i;
  int32_T c10_i20;
  real32_T c10_c_Accelerometer[3];
  int32_T c10_d_i;
  int32_T c10_i21;
  real32_T c10_c_Gyroscope[3];
  int32_T c10_e_i;
  int32_T c10_i22;
  real32_T c10_b_magInterp[3];
  real32_T c10_fv3[4];
  int32_T c10_i23;
  int32_T c10_i24;
  int32_T c10_i25;
  int32_T c10_i26;
  int32_T c10_i27;
  _SFD_SYMBOL_SCOPE_PUSH(0U, 0U);
  _sfTime_ = sf_get_time(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 8U, chartInstance->c10_sfEvent);
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c10_Beta, 3U, 1U, 0U,
                        chartInstance->c10_sfEvent, false);
  for (c10_i2 = 0; c10_i2 < 6; c10_i2++) {
    _SFD_DATA_RANGE_CHECK((real_T)(*chartInstance->c10_Magnetometer)[c10_i2], 2U,
                          1U, 0U, chartInstance->c10_sfEvent, false);
  }

  for (c10_i3 = 0; c10_i3 < 12; c10_i3++) {
    _SFD_DATA_RANGE_CHECK((real_T)(*chartInstance->c10_Gyroscope)[c10_i3], 1U,
                          1U, 0U, chartInstance->c10_sfEvent, false);
  }

  for (c10_i4 = 0; c10_i4 < 12; c10_i4++) {
    _SFD_DATA_RANGE_CHECK((real_T)(*chartInstance->c10_Accelerometer)[c10_i4],
                          0U, 1U, 0U, chartInstance->c10_sfEvent, false);
  }

  chartInstance->c10_sfEvent = CALL_EVENT;
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 8U, chartInstance->c10_sfEvent);
  c10_hoistedGlobal = *chartInstance->c10_Beta;
  for (c10_i5 = 0; c10_i5 < 12; c10_i5++) {
    c10_b_Accelerometer[c10_i5] = (*chartInstance->c10_Accelerometer)[c10_i5];
  }

  for (c10_i6 = 0; c10_i6 < 12; c10_i6++) {
    c10_b_Gyroscope[c10_i6] = (*chartInstance->c10_Gyroscope)[c10_i6];
  }

  for (c10_i7 = 0; c10_i7 < 6; c10_i7++) {
    c10_b_Magnetometer[c10_i7] = (*chartInstance->c10_Magnetometer)[c10_i7];
  }

  c10_b_Beta = c10_hoistedGlobal;
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 13U, 13U, c10_debug_family_names,
    c10_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c10_qIn, 0U, c10_h_sf_marshallOut,
    c10_f_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c10_x, 1U, c10_g_sf_marshallOut,
    c10_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c10_magInterp, 2U, c10_f_sf_marshallOut,
    c10_e_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c10_i, 3U, c10_g_sf_marshallOut,
    c10_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c10_nargin, 4U, c10_g_sf_marshallOut,
    c10_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c10_nargout, 5U, c10_g_sf_marshallOut,
    c10_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(c10_b_Accelerometer, 6U, c10_f_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c10_b_Gyroscope, 7U, c10_f_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c10_b_Magnetometer, 8U, c10_e_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c10_b_Beta, 9U, c10_d_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c10_b_q, 10U, c10_c_sf_marshallOut,
    c10_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(chartInstance->c10_qLocal, 11U,
    c10_b_sf_marshallOut, c10_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&chartInstance->c10_counter, 12U,
    c10_sf_marshallOut, c10_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c10_sfEvent, 2);
  _SFD_EML_CALL(0U, chartInstance->c10_sfEvent, 3);
  if (CV_EML_IF(0, 1, 0, !chartInstance->c10_qLocal_not_empty)) {
    _SFD_EML_CALL(0U, chartInstance->c10_sfEvent, 4);
    for (c10_i8 = 0; c10_i8 < 4; c10_i8++) {
      chartInstance->c10_qLocal[c10_i8] = c10_fv2[c10_i8];
    }

    chartInstance->c10_qLocal_not_empty = true;
    _SFD_EML_CALL(0U, chartInstance->c10_sfEvent, 5);
    chartInstance->c10_counter = 0.0;
    chartInstance->c10_counter_not_empty = true;
  }

  _SFD_EML_CALL(0U, chartInstance->c10_sfEvent, 7);
  for (c10_i9 = 0; c10_i9 < 4; c10_i9++) {
    c10_qIn[c10_i9] = chartInstance->c10_qLocal[c10_i9];
  }

  _SFD_EML_CALL(0U, chartInstance->c10_sfEvent, 10);
  chartInstance->c10_counter++;
  _SFD_EML_CALL(0U, chartInstance->c10_sfEvent, 12);
  if (CV_EML_IF(0, 1, 1, CV_RELATIONAL_EVAL(4U, 0U, 0,
        chartInstance->c10_counter, 100.0, -1, 4U, chartInstance->c10_counter >
        100.0))) {
    _SFD_EML_CALL(0U, chartInstance->c10_sfEvent, 13);
    c10_x = 1.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c10_sfEvent, 16);
  c10_i10 = 0;
  for (c10_i11 = 0; c10_i11 < 3; c10_i11++) {
    c10_i12 = 0;
    for (c10_i13 = 0; c10_i13 < 2; c10_i13++) {
      c10_varargin_2[c10_i13 + c10_i10] = c10_b_Magnetometer[c10_i12 + c10_i11];
      c10_i12 += 3;
    }

    c10_i10 += 2;
  }

  for (c10_i14 = 0; c10_i14 < 6; c10_i14++) {
    c10_b_varargin_2[c10_i14] = c10_varargin_2[c10_i14];
  }

  c10_interp1_work(chartInstance, c10_b_varargin_2, c10_Vq);
  c10_i15 = 0;
  for (c10_i16 = 0; c10_i16 < 4; c10_i16++) {
    c10_i17 = 0;
    for (c10_i18 = 0; c10_i18 < 3; c10_i18++) {
      c10_magInterp[c10_i18 + c10_i15] = c10_Vq[c10_i17 + c10_i16];
      c10_i17 += 4;
    }

    c10_i15 += 3;
  }

  _SFD_EML_CALL(0U, chartInstance->c10_sfEvent, 18);
  c10_i = 1.0;
  c10_b_i = 0;
  while (c10_b_i < 4) {
    c10_i = 1.0 + (real_T)c10_b_i;
    CV_EML_FOR(0, 1, 0, 1);
    _SFD_EML_CALL(0U, chartInstance->c10_sfEvent, 20);
    for (c10_i19 = 0; c10_i19 < 4; c10_i19++) {
      c10_b_qIn[c10_i19] = c10_qIn[c10_i19];
    }

    c10_c_i = sf_eml_array_bounds_check(sfGlobalDebugInstanceStruct,
      chartInstance->S, 1U, 355, 1, MAX_uint32_T, (int32_T)sf_integer_check
      (chartInstance->S, 1U, 355U, 1U, c10_i), 1, 4) - 1;
    for (c10_i20 = 0; c10_i20 < 3; c10_i20++) {
      c10_c_Accelerometer[c10_i20] = c10_b_Accelerometer[c10_i20 + 3 * c10_c_i];
    }

    c10_d_i = sf_eml_array_bounds_check(sfGlobalDebugInstanceStruct,
      chartInstance->S, 1U, 370, 1, MAX_uint32_T, (int32_T)sf_integer_check
      (chartInstance->S, 1U, 370U, 1U, c10_i), 1, 4) - 1;
    for (c10_i21 = 0; c10_i21 < 3; c10_i21++) {
      c10_c_Gyroscope[c10_i21] = c10_b_Gyroscope[c10_i21 + 3 * c10_d_i];
    }

    c10_e_i = sf_eml_array_bounds_check(sfGlobalDebugInstanceStruct,
      chartInstance->S, 1U, 385, 1, MAX_uint32_T, (int32_T)sf_integer_check
      (chartInstance->S, 1U, 385U, 1U, c10_i), 1, 4) - 1;
    for (c10_i22 = 0; c10_i22 < 3; c10_i22++) {
      c10_b_magInterp[c10_i22] = c10_magInterp[c10_i22 + 3 * c10_e_i];
    }

    c10_runMadwickUpdate(chartInstance, c10_b_qIn, c10_c_Accelerometer,
                         c10_c_Gyroscope, c10_b_magInterp, c10_b_Beta, c10_fv3);
    for (c10_i23 = 0; c10_i23 < 4; c10_i23++) {
      c10_b_q[c10_i23] = c10_fv3[c10_i23];
    }

    _SFD_EML_CALL(0U, chartInstance->c10_sfEvent, 21);
    for (c10_i24 = 0; c10_i24 < 4; c10_i24++) {
      c10_qIn[c10_i24] = c10_b_q[c10_i24];
    }

    c10_b_i++;
    _SF_MEX_LISTEN_FOR_CTRL_C(chartInstance->S);
  }

  CV_EML_FOR(0, 1, 0, 0);
  _SFD_EML_CALL(0U, chartInstance->c10_sfEvent, 25);
  for (c10_i25 = 0; c10_i25 < 4; c10_i25++) {
    chartInstance->c10_qLocal[c10_i25] = c10_b_q[c10_i25];
  }

  _SFD_EML_CALL(0U, chartInstance->c10_sfEvent, -25);
  _SFD_SYMBOL_SCOPE_POP();
  for (c10_i26 = 0; c10_i26 < 4; c10_i26++) {
    (*chartInstance->c10_q)[c10_i26] = c10_b_q[c10_i26];
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 8U, chartInstance->c10_sfEvent);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_QuadSimMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
  for (c10_i27 = 0; c10_i27 < 4; c10_i27++) {
    _SFD_DATA_RANGE_CHECK((real_T)(*chartInstance->c10_q)[c10_i27], 4U, 1U, 0U,
                          chartInstance->c10_sfEvent, false);
  }
}

static void mdl_start_c10_QuadSim(SFc10_QuadSimInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void initSimStructsc10_QuadSim(SFc10_QuadSimInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void init_script_number_translation(uint32_T c10_machineNumber, uint32_T
  c10_chartNumber, uint32_T c10_instanceNumber)
{
  (void)c10_machineNumber;
  (void)c10_chartNumber;
  (void)c10_instanceNumber;
}

static const mxArray *c10_sf_marshallOut(void *chartInstanceVoid, void
  *c10_inData)
{
  const mxArray *c10_mxArrayOutData;
  real_T c10_u;
  const mxArray *c10_y = NULL;
  SFc10_QuadSimInstanceStruct *chartInstance;
  chartInstance = (SFc10_QuadSimInstanceStruct *)chartInstanceVoid;
  c10_mxArrayOutData = NULL;
  c10_mxArrayOutData = NULL;
  c10_u = *(real_T *)c10_inData;
  c10_y = NULL;
  if (!chartInstance->c10_counter_not_empty) {
    sf_mex_assign(&c10_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  false);
  } else {
    sf_mex_assign(&c10_y, sf_mex_create("y", &c10_u, 0, 0U, 0U, 0U, 0), false);
  }

  sf_mex_assign(&c10_mxArrayOutData, c10_y, false);
  return c10_mxArrayOutData;
}

static real_T c10_emlrt_marshallIn(SFc10_QuadSimInstanceStruct *chartInstance,
  const mxArray *c10_b_counter, const char_T *c10_identifier, boolean_T
  *c10_svPtr)
{
  real_T c10_y;
  emlrtMsgIdentifier c10_thisId;
  c10_thisId.fIdentifier = c10_identifier;
  c10_thisId.fParent = NULL;
  c10_thisId.bParentIsCell = false;
  c10_y = c10_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c10_b_counter),
    &c10_thisId, c10_svPtr);
  sf_mex_destroy(&c10_b_counter);
  return c10_y;
}

static real_T c10_b_emlrt_marshallIn(SFc10_QuadSimInstanceStruct *chartInstance,
  const mxArray *c10_u, const emlrtMsgIdentifier *c10_parentId, boolean_T
  *c10_svPtr)
{
  real_T c10_y;
  real_T c10_d0;
  (void)chartInstance;
  if (mxIsEmpty(c10_u)) {
    *c10_svPtr = false;
  } else {
    *c10_svPtr = true;
    sf_mex_import(c10_parentId, sf_mex_dup(c10_u), &c10_d0, 1, 0, 0U, 0, 0U, 0);
    c10_y = c10_d0;
  }

  sf_mex_destroy(&c10_u);
  return c10_y;
}

static void c10_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c10_mxArrayInData, const char_T *c10_varName, void *c10_outData)
{
  const mxArray *c10_b_counter;
  const char_T *c10_identifier;
  boolean_T *c10_svPtr;
  emlrtMsgIdentifier c10_thisId;
  real_T c10_y;
  SFc10_QuadSimInstanceStruct *chartInstance;
  chartInstance = (SFc10_QuadSimInstanceStruct *)chartInstanceVoid;
  c10_b_counter = sf_mex_dup(c10_mxArrayInData);
  c10_identifier = c10_varName;
  c10_svPtr = &chartInstance->c10_counter_not_empty;
  c10_thisId.fIdentifier = c10_identifier;
  c10_thisId.fParent = NULL;
  c10_thisId.bParentIsCell = false;
  c10_y = c10_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c10_b_counter),
    &c10_thisId, c10_svPtr);
  sf_mex_destroy(&c10_b_counter);
  *(real_T *)c10_outData = c10_y;
  sf_mex_destroy(&c10_mxArrayInData);
}

static const mxArray *c10_b_sf_marshallOut(void *chartInstanceVoid, void
  *c10_inData)
{
  const mxArray *c10_mxArrayOutData;
  int32_T c10_i28;
  real32_T c10_u[4];
  const mxArray *c10_y = NULL;
  SFc10_QuadSimInstanceStruct *chartInstance;
  chartInstance = (SFc10_QuadSimInstanceStruct *)chartInstanceVoid;
  c10_mxArrayOutData = NULL;
  c10_mxArrayOutData = NULL;
  for (c10_i28 = 0; c10_i28 < 4; c10_i28++) {
    c10_u[c10_i28] = (*(real32_T (*)[4])c10_inData)[c10_i28];
  }

  c10_y = NULL;
  if (!chartInstance->c10_qLocal_not_empty) {
    sf_mex_assign(&c10_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  false);
  } else {
    sf_mex_assign(&c10_y, sf_mex_create("y", c10_u, 1, 0U, 1U, 0U, 1, 4), false);
  }

  sf_mex_assign(&c10_mxArrayOutData, c10_y, false);
  return c10_mxArrayOutData;
}

static void c10_c_emlrt_marshallIn(SFc10_QuadSimInstanceStruct *chartInstance,
  const mxArray *c10_b_qLocal, const char_T *c10_identifier, boolean_T
  *c10_svPtr, real32_T c10_y[4])
{
  emlrtMsgIdentifier c10_thisId;
  c10_thisId.fIdentifier = c10_identifier;
  c10_thisId.fParent = NULL;
  c10_thisId.bParentIsCell = false;
  c10_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c10_b_qLocal), &c10_thisId,
    c10_svPtr, c10_y);
  sf_mex_destroy(&c10_b_qLocal);
}

static void c10_d_emlrt_marshallIn(SFc10_QuadSimInstanceStruct *chartInstance,
  const mxArray *c10_u, const emlrtMsgIdentifier *c10_parentId, boolean_T
  *c10_svPtr, real32_T c10_y[4])
{
  real32_T c10_fv4[4];
  int32_T c10_i29;
  (void)chartInstance;
  if (mxIsEmpty(c10_u)) {
    *c10_svPtr = false;
  } else {
    *c10_svPtr = true;
    sf_mex_import(c10_parentId, sf_mex_dup(c10_u), c10_fv4, 1, 1, 0U, 1, 0U, 1,
                  4);
    for (c10_i29 = 0; c10_i29 < 4; c10_i29++) {
      c10_y[c10_i29] = c10_fv4[c10_i29];
    }
  }

  sf_mex_destroy(&c10_u);
}

static void c10_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c10_mxArrayInData, const char_T *c10_varName, void *c10_outData)
{
  const mxArray *c10_b_qLocal;
  const char_T *c10_identifier;
  boolean_T *c10_svPtr;
  emlrtMsgIdentifier c10_thisId;
  real32_T c10_y[4];
  int32_T c10_i30;
  SFc10_QuadSimInstanceStruct *chartInstance;
  chartInstance = (SFc10_QuadSimInstanceStruct *)chartInstanceVoid;
  c10_b_qLocal = sf_mex_dup(c10_mxArrayInData);
  c10_identifier = c10_varName;
  c10_svPtr = &chartInstance->c10_qLocal_not_empty;
  c10_thisId.fIdentifier = c10_identifier;
  c10_thisId.fParent = NULL;
  c10_thisId.bParentIsCell = false;
  c10_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c10_b_qLocal), &c10_thisId,
    c10_svPtr, c10_y);
  sf_mex_destroy(&c10_b_qLocal);
  for (c10_i30 = 0; c10_i30 < 4; c10_i30++) {
    (*(real32_T (*)[4])c10_outData)[c10_i30] = c10_y[c10_i30];
  }

  sf_mex_destroy(&c10_mxArrayInData);
}

static const mxArray *c10_c_sf_marshallOut(void *chartInstanceVoid, void
  *c10_inData)
{
  const mxArray *c10_mxArrayOutData = NULL;
  int32_T c10_i31;
  real32_T c10_u[4];
  const mxArray *c10_y = NULL;
  SFc10_QuadSimInstanceStruct *chartInstance;
  chartInstance = (SFc10_QuadSimInstanceStruct *)chartInstanceVoid;
  c10_mxArrayOutData = NULL;
  for (c10_i31 = 0; c10_i31 < 4; c10_i31++) {
    c10_u[c10_i31] = (*(real32_T (*)[4])c10_inData)[c10_i31];
  }

  c10_y = NULL;
  sf_mex_assign(&c10_y, sf_mex_create("y", c10_u, 1, 0U, 1U, 0U, 2, 4, 1), false);
  sf_mex_assign(&c10_mxArrayOutData, c10_y, false);
  return c10_mxArrayOutData;
}

static void c10_e_emlrt_marshallIn(SFc10_QuadSimInstanceStruct *chartInstance,
  const mxArray *c10_b_q, const char_T *c10_identifier, real32_T c10_y[4])
{
  emlrtMsgIdentifier c10_thisId;
  c10_thisId.fIdentifier = c10_identifier;
  c10_thisId.fParent = NULL;
  c10_thisId.bParentIsCell = false;
  c10_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c10_b_q), &c10_thisId, c10_y);
  sf_mex_destroy(&c10_b_q);
}

static void c10_f_emlrt_marshallIn(SFc10_QuadSimInstanceStruct *chartInstance,
  const mxArray *c10_u, const emlrtMsgIdentifier *c10_parentId, real32_T c10_y[4])
{
  real32_T c10_fv5[4];
  int32_T c10_i32;
  (void)chartInstance;
  sf_mex_import(c10_parentId, sf_mex_dup(c10_u), c10_fv5, 1, 1, 0U, 1, 0U, 2, 4,
                1);
  for (c10_i32 = 0; c10_i32 < 4; c10_i32++) {
    c10_y[c10_i32] = c10_fv5[c10_i32];
  }

  sf_mex_destroy(&c10_u);
}

static void c10_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c10_mxArrayInData, const char_T *c10_varName, void *c10_outData)
{
  const mxArray *c10_b_q;
  const char_T *c10_identifier;
  emlrtMsgIdentifier c10_thisId;
  real32_T c10_y[4];
  int32_T c10_i33;
  SFc10_QuadSimInstanceStruct *chartInstance;
  chartInstance = (SFc10_QuadSimInstanceStruct *)chartInstanceVoid;
  c10_b_q = sf_mex_dup(c10_mxArrayInData);
  c10_identifier = c10_varName;
  c10_thisId.fIdentifier = c10_identifier;
  c10_thisId.fParent = NULL;
  c10_thisId.bParentIsCell = false;
  c10_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c10_b_q), &c10_thisId, c10_y);
  sf_mex_destroy(&c10_b_q);
  for (c10_i33 = 0; c10_i33 < 4; c10_i33++) {
    (*(real32_T (*)[4])c10_outData)[c10_i33] = c10_y[c10_i33];
  }

  sf_mex_destroy(&c10_mxArrayInData);
}

static const mxArray *c10_d_sf_marshallOut(void *chartInstanceVoid, void
  *c10_inData)
{
  const mxArray *c10_mxArrayOutData = NULL;
  real32_T c10_u;
  const mxArray *c10_y = NULL;
  SFc10_QuadSimInstanceStruct *chartInstance;
  chartInstance = (SFc10_QuadSimInstanceStruct *)chartInstanceVoid;
  c10_mxArrayOutData = NULL;
  c10_u = *(real32_T *)c10_inData;
  c10_y = NULL;
  sf_mex_assign(&c10_y, sf_mex_create("y", &c10_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c10_mxArrayOutData, c10_y, false);
  return c10_mxArrayOutData;
}

static const mxArray *c10_e_sf_marshallOut(void *chartInstanceVoid, void
  *c10_inData)
{
  const mxArray *c10_mxArrayOutData = NULL;
  int32_T c10_i34;
  int32_T c10_i35;
  int32_T c10_i36;
  real32_T c10_u[6];
  const mxArray *c10_y = NULL;
  SFc10_QuadSimInstanceStruct *chartInstance;
  chartInstance = (SFc10_QuadSimInstanceStruct *)chartInstanceVoid;
  c10_mxArrayOutData = NULL;
  c10_i34 = 0;
  for (c10_i35 = 0; c10_i35 < 2; c10_i35++) {
    for (c10_i36 = 0; c10_i36 < 3; c10_i36++) {
      c10_u[c10_i36 + c10_i34] = (*(real32_T (*)[6])c10_inData)[c10_i36 +
        c10_i34];
    }

    c10_i34 += 3;
  }

  c10_y = NULL;
  sf_mex_assign(&c10_y, sf_mex_create("y", c10_u, 1, 0U, 1U, 0U, 2, 3, 2), false);
  sf_mex_assign(&c10_mxArrayOutData, c10_y, false);
  return c10_mxArrayOutData;
}

static const mxArray *c10_f_sf_marshallOut(void *chartInstanceVoid, void
  *c10_inData)
{
  const mxArray *c10_mxArrayOutData = NULL;
  int32_T c10_i37;
  int32_T c10_i38;
  int32_T c10_i39;
  real32_T c10_u[12];
  const mxArray *c10_y = NULL;
  SFc10_QuadSimInstanceStruct *chartInstance;
  chartInstance = (SFc10_QuadSimInstanceStruct *)chartInstanceVoid;
  c10_mxArrayOutData = NULL;
  c10_i37 = 0;
  for (c10_i38 = 0; c10_i38 < 4; c10_i38++) {
    for (c10_i39 = 0; c10_i39 < 3; c10_i39++) {
      c10_u[c10_i39 + c10_i37] = (*(real32_T (*)[12])c10_inData)[c10_i39 +
        c10_i37];
    }

    c10_i37 += 3;
  }

  c10_y = NULL;
  sf_mex_assign(&c10_y, sf_mex_create("y", c10_u, 1, 0U, 1U, 0U, 2, 3, 4), false);
  sf_mex_assign(&c10_mxArrayOutData, c10_y, false);
  return c10_mxArrayOutData;
}

static const mxArray *c10_g_sf_marshallOut(void *chartInstanceVoid, void
  *c10_inData)
{
  const mxArray *c10_mxArrayOutData = NULL;
  real_T c10_u;
  const mxArray *c10_y = NULL;
  SFc10_QuadSimInstanceStruct *chartInstance;
  chartInstance = (SFc10_QuadSimInstanceStruct *)chartInstanceVoid;
  c10_mxArrayOutData = NULL;
  c10_u = *(real_T *)c10_inData;
  c10_y = NULL;
  sf_mex_assign(&c10_y, sf_mex_create("y", &c10_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c10_mxArrayOutData, c10_y, false);
  return c10_mxArrayOutData;
}

static real_T c10_g_emlrt_marshallIn(SFc10_QuadSimInstanceStruct *chartInstance,
  const mxArray *c10_u, const emlrtMsgIdentifier *c10_parentId)
{
  real_T c10_y;
  real_T c10_d1;
  (void)chartInstance;
  sf_mex_import(c10_parentId, sf_mex_dup(c10_u), &c10_d1, 1, 0, 0U, 0, 0U, 0);
  c10_y = c10_d1;
  sf_mex_destroy(&c10_u);
  return c10_y;
}

static void c10_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c10_mxArrayInData, const char_T *c10_varName, void *c10_outData)
{
  const mxArray *c10_nargout;
  const char_T *c10_identifier;
  emlrtMsgIdentifier c10_thisId;
  real_T c10_y;
  SFc10_QuadSimInstanceStruct *chartInstance;
  chartInstance = (SFc10_QuadSimInstanceStruct *)chartInstanceVoid;
  c10_nargout = sf_mex_dup(c10_mxArrayInData);
  c10_identifier = c10_varName;
  c10_thisId.fIdentifier = c10_identifier;
  c10_thisId.fParent = NULL;
  c10_thisId.bParentIsCell = false;
  c10_y = c10_g_emlrt_marshallIn(chartInstance, sf_mex_dup(c10_nargout),
    &c10_thisId);
  sf_mex_destroy(&c10_nargout);
  *(real_T *)c10_outData = c10_y;
  sf_mex_destroy(&c10_mxArrayInData);
}

static void c10_h_emlrt_marshallIn(SFc10_QuadSimInstanceStruct *chartInstance,
  const mxArray *c10_u, const emlrtMsgIdentifier *c10_parentId, real32_T c10_y
  [12])
{
  real32_T c10_fv6[12];
  int32_T c10_i40;
  (void)chartInstance;
  sf_mex_import(c10_parentId, sf_mex_dup(c10_u), c10_fv6, 1, 1, 0U, 1, 0U, 2, 3,
                4);
  for (c10_i40 = 0; c10_i40 < 12; c10_i40++) {
    c10_y[c10_i40] = c10_fv6[c10_i40];
  }

  sf_mex_destroy(&c10_u);
}

static void c10_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c10_mxArrayInData, const char_T *c10_varName, void *c10_outData)
{
  const mxArray *c10_magInterp;
  const char_T *c10_identifier;
  emlrtMsgIdentifier c10_thisId;
  real32_T c10_y[12];
  int32_T c10_i41;
  int32_T c10_i42;
  int32_T c10_i43;
  SFc10_QuadSimInstanceStruct *chartInstance;
  chartInstance = (SFc10_QuadSimInstanceStruct *)chartInstanceVoid;
  c10_magInterp = sf_mex_dup(c10_mxArrayInData);
  c10_identifier = c10_varName;
  c10_thisId.fIdentifier = c10_identifier;
  c10_thisId.fParent = NULL;
  c10_thisId.bParentIsCell = false;
  c10_h_emlrt_marshallIn(chartInstance, sf_mex_dup(c10_magInterp), &c10_thisId,
    c10_y);
  sf_mex_destroy(&c10_magInterp);
  c10_i41 = 0;
  for (c10_i42 = 0; c10_i42 < 4; c10_i42++) {
    for (c10_i43 = 0; c10_i43 < 3; c10_i43++) {
      (*(real32_T (*)[12])c10_outData)[c10_i43 + c10_i41] = c10_y[c10_i43 +
        c10_i41];
    }

    c10_i41 += 3;
  }

  sf_mex_destroy(&c10_mxArrayInData);
}

static const mxArray *c10_h_sf_marshallOut(void *chartInstanceVoid, void
  *c10_inData)
{
  const mxArray *c10_mxArrayOutData = NULL;
  int32_T c10_i44;
  real32_T c10_u[4];
  const mxArray *c10_y = NULL;
  SFc10_QuadSimInstanceStruct *chartInstance;
  chartInstance = (SFc10_QuadSimInstanceStruct *)chartInstanceVoid;
  c10_mxArrayOutData = NULL;
  for (c10_i44 = 0; c10_i44 < 4; c10_i44++) {
    c10_u[c10_i44] = (*(real32_T (*)[4])c10_inData)[c10_i44];
  }

  c10_y = NULL;
  sf_mex_assign(&c10_y, sf_mex_create("y", c10_u, 1, 0U, 1U, 0U, 1, 4), false);
  sf_mex_assign(&c10_mxArrayOutData, c10_y, false);
  return c10_mxArrayOutData;
}

static void c10_i_emlrt_marshallIn(SFc10_QuadSimInstanceStruct *chartInstance,
  const mxArray *c10_u, const emlrtMsgIdentifier *c10_parentId, real32_T c10_y[4])
{
  real32_T c10_fv7[4];
  int32_T c10_i45;
  (void)chartInstance;
  sf_mex_import(c10_parentId, sf_mex_dup(c10_u), c10_fv7, 1, 1, 0U, 1, 0U, 1, 4);
  for (c10_i45 = 0; c10_i45 < 4; c10_i45++) {
    c10_y[c10_i45] = c10_fv7[c10_i45];
  }

  sf_mex_destroy(&c10_u);
}

static void c10_f_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c10_mxArrayInData, const char_T *c10_varName, void *c10_outData)
{
  const mxArray *c10_qIn;
  const char_T *c10_identifier;
  emlrtMsgIdentifier c10_thisId;
  real32_T c10_y[4];
  int32_T c10_i46;
  SFc10_QuadSimInstanceStruct *chartInstance;
  chartInstance = (SFc10_QuadSimInstanceStruct *)chartInstanceVoid;
  c10_qIn = sf_mex_dup(c10_mxArrayInData);
  c10_identifier = c10_varName;
  c10_thisId.fIdentifier = c10_identifier;
  c10_thisId.fParent = NULL;
  c10_thisId.bParentIsCell = false;
  c10_i_emlrt_marshallIn(chartInstance, sf_mex_dup(c10_qIn), &c10_thisId, c10_y);
  sf_mex_destroy(&c10_qIn);
  for (c10_i46 = 0; c10_i46 < 4; c10_i46++) {
    (*(real32_T (*)[4])c10_outData)[c10_i46] = c10_y[c10_i46];
  }

  sf_mex_destroy(&c10_mxArrayInData);
}

static const mxArray *c10_i_sf_marshallOut(void *chartInstanceVoid, void
  *c10_inData)
{
  const mxArray *c10_mxArrayOutData = NULL;
  int32_T c10_i47;
  real_T c10_u[4];
  const mxArray *c10_y = NULL;
  SFc10_QuadSimInstanceStruct *chartInstance;
  chartInstance = (SFc10_QuadSimInstanceStruct *)chartInstanceVoid;
  c10_mxArrayOutData = NULL;
  for (c10_i47 = 0; c10_i47 < 4; c10_i47++) {
    c10_u[c10_i47] = (*(real_T (*)[4])c10_inData)[c10_i47];
  }

  c10_y = NULL;
  sf_mex_assign(&c10_y, sf_mex_create("y", c10_u, 0, 0U, 1U, 0U, 1, 4), false);
  sf_mex_assign(&c10_mxArrayOutData, c10_y, false);
  return c10_mxArrayOutData;
}

static void c10_j_emlrt_marshallIn(SFc10_QuadSimInstanceStruct *chartInstance,
  const mxArray *c10_u, const emlrtMsgIdentifier *c10_parentId, real_T c10_y[4])
{
  real_T c10_dv0[4];
  int32_T c10_i48;
  (void)chartInstance;
  sf_mex_import(c10_parentId, sf_mex_dup(c10_u), c10_dv0, 1, 0, 0U, 1, 0U, 1, 4);
  for (c10_i48 = 0; c10_i48 < 4; c10_i48++) {
    c10_y[c10_i48] = c10_dv0[c10_i48];
  }

  sf_mex_destroy(&c10_u);
}

static void c10_g_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c10_mxArrayInData, const char_T *c10_varName, void *c10_outData)
{
  const mxArray *c10_ab;
  const char_T *c10_identifier;
  emlrtMsgIdentifier c10_thisId;
  real_T c10_y[4];
  int32_T c10_i49;
  SFc10_QuadSimInstanceStruct *chartInstance;
  chartInstance = (SFc10_QuadSimInstanceStruct *)chartInstanceVoid;
  c10_ab = sf_mex_dup(c10_mxArrayInData);
  c10_identifier = c10_varName;
  c10_thisId.fIdentifier = c10_identifier;
  c10_thisId.fParent = NULL;
  c10_thisId.bParentIsCell = false;
  c10_j_emlrt_marshallIn(chartInstance, sf_mex_dup(c10_ab), &c10_thisId, c10_y);
  sf_mex_destroy(&c10_ab);
  for (c10_i49 = 0; c10_i49 < 4; c10_i49++) {
    (*(real_T (*)[4])c10_outData)[c10_i49] = c10_y[c10_i49];
  }

  sf_mex_destroy(&c10_mxArrayInData);
}

static const mxArray *c10_j_sf_marshallOut(void *chartInstanceVoid, void
  *c10_inData)
{
  const mxArray *c10_mxArrayOutData = NULL;
  int32_T c10_i50;
  real32_T c10_u[4];
  const mxArray *c10_y = NULL;
  SFc10_QuadSimInstanceStruct *chartInstance;
  chartInstance = (SFc10_QuadSimInstanceStruct *)chartInstanceVoid;
  c10_mxArrayOutData = NULL;
  for (c10_i50 = 0; c10_i50 < 4; c10_i50++) {
    c10_u[c10_i50] = (*(real32_T (*)[4])c10_inData)[c10_i50];
  }

  c10_y = NULL;
  sf_mex_assign(&c10_y, sf_mex_create("y", c10_u, 1, 0U, 1U, 0U, 2, 1, 4), false);
  sf_mex_assign(&c10_mxArrayOutData, c10_y, false);
  return c10_mxArrayOutData;
}

static void c10_k_emlrt_marshallIn(SFc10_QuadSimInstanceStruct *chartInstance,
  const mxArray *c10_u, const emlrtMsgIdentifier *c10_parentId, real32_T c10_y[4])
{
  real32_T c10_fv8[4];
  int32_T c10_i51;
  (void)chartInstance;
  sf_mex_import(c10_parentId, sf_mex_dup(c10_u), c10_fv8, 1, 1, 0U, 1, 0U, 2, 1,
                4);
  for (c10_i51 = 0; c10_i51 < 4; c10_i51++) {
    c10_y[c10_i51] = c10_fv8[c10_i51];
  }

  sf_mex_destroy(&c10_u);
}

static void c10_h_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c10_mxArrayInData, const char_T *c10_varName, void *c10_outData)
{
  const mxArray *c10_a;
  const char_T *c10_identifier;
  emlrtMsgIdentifier c10_thisId;
  real32_T c10_y[4];
  int32_T c10_i52;
  SFc10_QuadSimInstanceStruct *chartInstance;
  chartInstance = (SFc10_QuadSimInstanceStruct *)chartInstanceVoid;
  c10_a = sf_mex_dup(c10_mxArrayInData);
  c10_identifier = c10_varName;
  c10_thisId.fIdentifier = c10_identifier;
  c10_thisId.fParent = NULL;
  c10_thisId.bParentIsCell = false;
  c10_k_emlrt_marshallIn(chartInstance, sf_mex_dup(c10_a), &c10_thisId, c10_y);
  sf_mex_destroy(&c10_a);
  for (c10_i52 = 0; c10_i52 < 4; c10_i52++) {
    (*(real32_T (*)[4])c10_outData)[c10_i52] = c10_y[c10_i52];
  }

  sf_mex_destroy(&c10_mxArrayInData);
}

static real32_T c10_l_emlrt_marshallIn(SFc10_QuadSimInstanceStruct
  *chartInstance, const mxArray *c10_u, const emlrtMsgIdentifier *c10_parentId)
{
  real32_T c10_y;
  real32_T c10_f0;
  (void)chartInstance;
  sf_mex_import(c10_parentId, sf_mex_dup(c10_u), &c10_f0, 1, 1, 0U, 0, 0U, 0);
  c10_y = c10_f0;
  sf_mex_destroy(&c10_u);
  return c10_y;
}

static void c10_i_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c10_mxArrayInData, const char_T *c10_varName, void *c10_outData)
{
  const mxArray *c10_b_Beta;
  const char_T *c10_identifier;
  emlrtMsgIdentifier c10_thisId;
  real32_T c10_y;
  SFc10_QuadSimInstanceStruct *chartInstance;
  chartInstance = (SFc10_QuadSimInstanceStruct *)chartInstanceVoid;
  c10_b_Beta = sf_mex_dup(c10_mxArrayInData);
  c10_identifier = c10_varName;
  c10_thisId.fIdentifier = c10_identifier;
  c10_thisId.fParent = NULL;
  c10_thisId.bParentIsCell = false;
  c10_y = c10_l_emlrt_marshallIn(chartInstance, sf_mex_dup(c10_b_Beta),
    &c10_thisId);
  sf_mex_destroy(&c10_b_Beta);
  *(real32_T *)c10_outData = c10_y;
  sf_mex_destroy(&c10_mxArrayInData);
}

static const mxArray *c10_k_sf_marshallOut(void *chartInstanceVoid, void
  *c10_inData)
{
  const mxArray *c10_mxArrayOutData = NULL;
  int32_T c10_i53;
  real32_T c10_u[3];
  const mxArray *c10_y = NULL;
  SFc10_QuadSimInstanceStruct *chartInstance;
  chartInstance = (SFc10_QuadSimInstanceStruct *)chartInstanceVoid;
  c10_mxArrayOutData = NULL;
  for (c10_i53 = 0; c10_i53 < 3; c10_i53++) {
    c10_u[c10_i53] = (*(real32_T (*)[3])c10_inData)[c10_i53];
  }

  c10_y = NULL;
  sf_mex_assign(&c10_y, sf_mex_create("y", c10_u, 1, 0U, 1U, 0U, 1, 3), false);
  sf_mex_assign(&c10_mxArrayOutData, c10_y, false);
  return c10_mxArrayOutData;
}

static void c10_m_emlrt_marshallIn(SFc10_QuadSimInstanceStruct *chartInstance,
  const mxArray *c10_u, const emlrtMsgIdentifier *c10_parentId, real32_T c10_y[3])
{
  real32_T c10_fv9[3];
  int32_T c10_i54;
  (void)chartInstance;
  sf_mex_import(c10_parentId, sf_mex_dup(c10_u), c10_fv9, 1, 1, 0U, 1, 0U, 1, 3);
  for (c10_i54 = 0; c10_i54 < 3; c10_i54++) {
    c10_y[c10_i54] = c10_fv9[c10_i54];
  }

  sf_mex_destroy(&c10_u);
}

static void c10_j_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c10_mxArrayInData, const char_T *c10_varName, void *c10_outData)
{
  const mxArray *c10_b_Magnetometer;
  const char_T *c10_identifier;
  emlrtMsgIdentifier c10_thisId;
  real32_T c10_y[3];
  int32_T c10_i55;
  SFc10_QuadSimInstanceStruct *chartInstance;
  chartInstance = (SFc10_QuadSimInstanceStruct *)chartInstanceVoid;
  c10_b_Magnetometer = sf_mex_dup(c10_mxArrayInData);
  c10_identifier = c10_varName;
  c10_thisId.fIdentifier = c10_identifier;
  c10_thisId.fParent = NULL;
  c10_thisId.bParentIsCell = false;
  c10_m_emlrt_marshallIn(chartInstance, sf_mex_dup(c10_b_Magnetometer),
    &c10_thisId, c10_y);
  sf_mex_destroy(&c10_b_Magnetometer);
  for (c10_i55 = 0; c10_i55 < 3; c10_i55++) {
    (*(real32_T (*)[3])c10_outData)[c10_i55] = c10_y[c10_i55];
  }

  sf_mex_destroy(&c10_mxArrayInData);
}

static const mxArray *c10_l_sf_marshallOut(void *chartInstanceVoid, void
  *c10_inData)
{
  const mxArray *c10_mxArrayOutData = NULL;
  int32_T c10_i56;
  int32_T c10_i57;
  int32_T c10_i58;
  real32_T c10_u[24];
  const mxArray *c10_y = NULL;
  SFc10_QuadSimInstanceStruct *chartInstance;
  chartInstance = (SFc10_QuadSimInstanceStruct *)chartInstanceVoid;
  c10_mxArrayOutData = NULL;
  c10_i56 = 0;
  for (c10_i57 = 0; c10_i57 < 4; c10_i57++) {
    for (c10_i58 = 0; c10_i58 < 6; c10_i58++) {
      c10_u[c10_i58 + c10_i56] = (*(real32_T (*)[24])c10_inData)[c10_i58 +
        c10_i56];
    }

    c10_i56 += 6;
  }

  c10_y = NULL;
  sf_mex_assign(&c10_y, sf_mex_create("y", c10_u, 1, 0U, 1U, 0U, 2, 6, 4), false);
  sf_mex_assign(&c10_mxArrayOutData, c10_y, false);
  return c10_mxArrayOutData;
}

static void c10_n_emlrt_marshallIn(SFc10_QuadSimInstanceStruct *chartInstance,
  const mxArray *c10_u, const emlrtMsgIdentifier *c10_parentId, real32_T c10_y
  [24])
{
  real32_T c10_fv10[24];
  int32_T c10_i59;
  (void)chartInstance;
  sf_mex_import(c10_parentId, sf_mex_dup(c10_u), c10_fv10, 1, 1, 0U, 1, 0U, 2, 6,
                4);
  for (c10_i59 = 0; c10_i59 < 24; c10_i59++) {
    c10_y[c10_i59] = c10_fv10[c10_i59];
  }

  sf_mex_destroy(&c10_u);
}

static void c10_k_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c10_mxArrayInData, const char_T *c10_varName, void *c10_outData)
{
  const mxArray *c10_J;
  const char_T *c10_identifier;
  emlrtMsgIdentifier c10_thisId;
  real32_T c10_y[24];
  int32_T c10_i60;
  int32_T c10_i61;
  int32_T c10_i62;
  SFc10_QuadSimInstanceStruct *chartInstance;
  chartInstance = (SFc10_QuadSimInstanceStruct *)chartInstanceVoid;
  c10_J = sf_mex_dup(c10_mxArrayInData);
  c10_identifier = c10_varName;
  c10_thisId.fIdentifier = c10_identifier;
  c10_thisId.fParent = NULL;
  c10_thisId.bParentIsCell = false;
  c10_n_emlrt_marshallIn(chartInstance, sf_mex_dup(c10_J), &c10_thisId, c10_y);
  sf_mex_destroy(&c10_J);
  c10_i60 = 0;
  for (c10_i61 = 0; c10_i61 < 4; c10_i61++) {
    for (c10_i62 = 0; c10_i62 < 6; c10_i62++) {
      (*(real32_T (*)[24])c10_outData)[c10_i62 + c10_i60] = c10_y[c10_i62 +
        c10_i60];
    }

    c10_i60 += 6;
  }

  sf_mex_destroy(&c10_mxArrayInData);
}

static const mxArray *c10_m_sf_marshallOut(void *chartInstanceVoid, void
  *c10_inData)
{
  const mxArray *c10_mxArrayOutData = NULL;
  int32_T c10_i63;
  real32_T c10_u[6];
  const mxArray *c10_y = NULL;
  SFc10_QuadSimInstanceStruct *chartInstance;
  chartInstance = (SFc10_QuadSimInstanceStruct *)chartInstanceVoid;
  c10_mxArrayOutData = NULL;
  for (c10_i63 = 0; c10_i63 < 6; c10_i63++) {
    c10_u[c10_i63] = (*(real32_T (*)[6])c10_inData)[c10_i63];
  }

  c10_y = NULL;
  sf_mex_assign(&c10_y, sf_mex_create("y", c10_u, 1, 0U, 1U, 0U, 1, 6), false);
  sf_mex_assign(&c10_mxArrayOutData, c10_y, false);
  return c10_mxArrayOutData;
}

static void c10_o_emlrt_marshallIn(SFc10_QuadSimInstanceStruct *chartInstance,
  const mxArray *c10_u, const emlrtMsgIdentifier *c10_parentId, real32_T c10_y[6])
{
  real32_T c10_fv11[6];
  int32_T c10_i64;
  (void)chartInstance;
  sf_mex_import(c10_parentId, sf_mex_dup(c10_u), c10_fv11, 1, 1, 0U, 1, 0U, 1, 6);
  for (c10_i64 = 0; c10_i64 < 6; c10_i64++) {
    c10_y[c10_i64] = c10_fv11[c10_i64];
  }

  sf_mex_destroy(&c10_u);
}

static void c10_l_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c10_mxArrayInData, const char_T *c10_varName, void *c10_outData)
{
  const mxArray *c10_F;
  const char_T *c10_identifier;
  emlrtMsgIdentifier c10_thisId;
  real32_T c10_y[6];
  int32_T c10_i65;
  SFc10_QuadSimInstanceStruct *chartInstance;
  chartInstance = (SFc10_QuadSimInstanceStruct *)chartInstanceVoid;
  c10_F = sf_mex_dup(c10_mxArrayInData);
  c10_identifier = c10_varName;
  c10_thisId.fIdentifier = c10_identifier;
  c10_thisId.fParent = NULL;
  c10_thisId.bParentIsCell = false;
  c10_o_emlrt_marshallIn(chartInstance, sf_mex_dup(c10_F), &c10_thisId, c10_y);
  sf_mex_destroy(&c10_F);
  for (c10_i65 = 0; c10_i65 < 6; c10_i65++) {
    (*(real32_T (*)[6])c10_outData)[c10_i65] = c10_y[c10_i65];
  }

  sf_mex_destroy(&c10_mxArrayInData);
}

static const mxArray *c10_n_sf_marshallOut(void *chartInstanceVoid, void
  *c10_inData)
{
  const mxArray *c10_mxArrayOutData = NULL;
  int32_T c10_i66;
  real_T c10_u[4];
  const mxArray *c10_y = NULL;
  SFc10_QuadSimInstanceStruct *chartInstance;
  chartInstance = (SFc10_QuadSimInstanceStruct *)chartInstanceVoid;
  c10_mxArrayOutData = NULL;
  for (c10_i66 = 0; c10_i66 < 4; c10_i66++) {
    c10_u[c10_i66] = (*(real_T (*)[4])c10_inData)[c10_i66];
  }

  c10_y = NULL;
  sf_mex_assign(&c10_y, sf_mex_create("y", c10_u, 0, 0U, 1U, 0U, 2, 1, 4), false);
  sf_mex_assign(&c10_mxArrayOutData, c10_y, false);
  return c10_mxArrayOutData;
}

static void c10_p_emlrt_marshallIn(SFc10_QuadSimInstanceStruct *chartInstance,
  const mxArray *c10_u, const emlrtMsgIdentifier *c10_parentId, real_T c10_y[4])
{
  real_T c10_dv1[4];
  int32_T c10_i67;
  (void)chartInstance;
  sf_mex_import(c10_parentId, sf_mex_dup(c10_u), c10_dv1, 1, 0, 0U, 1, 0U, 2, 1,
                4);
  for (c10_i67 = 0; c10_i67 < 4; c10_i67++) {
    c10_y[c10_i67] = c10_dv1[c10_i67];
  }

  sf_mex_destroy(&c10_u);
}

static void c10_m_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c10_mxArrayInData, const char_T *c10_varName, void *c10_outData)
{
  const mxArray *c10_b;
  const char_T *c10_identifier;
  emlrtMsgIdentifier c10_thisId;
  real_T c10_y[4];
  int32_T c10_i68;
  SFc10_QuadSimInstanceStruct *chartInstance;
  chartInstance = (SFc10_QuadSimInstanceStruct *)chartInstanceVoid;
  c10_b = sf_mex_dup(c10_mxArrayInData);
  c10_identifier = c10_varName;
  c10_thisId.fIdentifier = c10_identifier;
  c10_thisId.fParent = NULL;
  c10_thisId.bParentIsCell = false;
  c10_p_emlrt_marshallIn(chartInstance, sf_mex_dup(c10_b), &c10_thisId, c10_y);
  sf_mex_destroy(&c10_b);
  for (c10_i68 = 0; c10_i68 < 4; c10_i68++) {
    (*(real_T (*)[4])c10_outData)[c10_i68] = c10_y[c10_i68];
  }

  sf_mex_destroy(&c10_mxArrayInData);
}

const mxArray *sf_c10_QuadSim_get_eml_resolved_functions_info(void)
{
  const mxArray *c10_nameCaptureInfo = NULL;
  c10_nameCaptureInfo = NULL;
  sf_mex_assign(&c10_nameCaptureInfo, sf_mex_create("nameCaptureInfo", NULL, 0,
    0U, 1U, 0U, 2, 0, 1), false);
  return c10_nameCaptureInfo;
}

static void c10_scalarEg(SFc10_QuadSimInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void c10_interp1_work(SFc10_QuadSimInstanceStruct *chartInstance,
  real32_T c10_y[6], real32_T c10_yi[12])
{
  int32_T c10_k;
  int32_T c10_b_k;
  int32_T c10_i69;
  int32_T c10_c_k;
  int32_T c10_d_k;
  int32_T c10_e_k;
  real_T c10_xik;
  real_T c10_x;
  boolean_T c10_b;
  int32_T c10_j;
  int32_T c10_b_j;
  real_T c10_xi;
  int32_T c10_low_i;
  int32_T c10_low_ip1;
  int32_T c10_high_i;
  int32_T c10_b_low_i;
  int32_T c10_b_high_i;
  int32_T c10_mid_i;
  int32_T c10_n;
  real_T c10_xn;
  real_T c10_xnp1;
  real_T c10_A;
  real_T c10_B;
  real_T c10_b_x;
  real_T c10_b_y;
  real_T c10_c_x;
  real_T c10_c_y;
  real_T c10_r;
  real_T c10_onemr;
  int32_T c10_c_j;
  real32_T c10_y1;
  int32_T c10_d_j;
  real32_T c10_y2;
  int32_T c10_e_j;
  real_T c10_a;
  real32_T c10_b_b;
  real32_T c10_d_y;
  real_T c10_b_a;
  real32_T c10_c_b;
  real32_T c10_e_y;
  int32_T exitg1;
  c10_k = 1;
  do {
    exitg1 = 0;
    if (c10_k < 3) {
      c10_b_k = c10_k - 1;
      if (c10_isnan(chartInstance, 1.0 + 3.0 * (real_T)c10_b_k)) {
        c10_error(chartInstance);
        exitg1 = 1;
      } else {
        c10_k++;
      }
    } else {
      for (c10_i69 = 0; c10_i69 < 12; c10_i69++) {
        c10_yi[c10_i69] = ((real32_T)rtNaN);
      }

      for (c10_c_k = 1; c10_c_k < 5; c10_c_k++) {
        c10_d_k = c10_c_k;
        c10_e_k = c10_d_k - 1;
        c10_xik = 1.0 + (real_T)c10_e_k;
        c10_x = c10_xik;
        c10_b = muDoubleScalarIsNaN(c10_x);
        if (c10_b) {
          for (c10_j = 0; c10_j < 3; c10_j++) {
            c10_b_j = c10_j;
            c10_yi[c10_e_k + (c10_b_j << 2)] = ((real32_T)rtNaN);
          }
        } else if (c10_xik > 4.0) {
        } else if (c10_xik < 1.0) {
        } else {
          c10_xi = c10_xik;
          c10_low_i = 1;
          c10_low_ip1 = 1;
          c10_high_i = 2;
          while (c10_high_i > c10_low_ip1 + 1) {
            c10_b_low_i = c10_low_i;
            c10_b_high_i = c10_high_i;
            c10_mid_i = (c10_b_low_i + c10_b_high_i) >> 1;
            if (c10_xi >= 1.0 + 3.0 * (real_T)(c10_mid_i - 1)) {
              c10_low_i = c10_mid_i;
              c10_low_ip1 = c10_low_i;
            } else {
              c10_high_i = c10_mid_i;
            }
          }

          c10_n = c10_low_i;
          c10_xn = 1.0 + 3.0 * (real_T)(c10_n - 1);
          c10_xnp1 = 1.0 + 3.0 * (real_T)c10_n;
          c10_A = c10_xik - c10_xn;
          c10_B = c10_xnp1 - c10_xn;
          c10_b_x = c10_A;
          c10_b_y = c10_B;
          c10_c_x = c10_b_x;
          c10_c_y = c10_b_y;
          c10_r = c10_c_x / c10_c_y;
          c10_onemr = 1.0 - c10_r;
          if (c10_r == 0.0) {
            for (c10_c_j = 0; c10_c_j < 3; c10_c_j++) {
              c10_b_j = c10_c_j;
              c10_y1 = c10_y[(c10_n + (c10_b_j << 1)) - 1];
              c10_yi[c10_e_k + (c10_b_j << 2)] = c10_y1;
            }
          } else if (c10_r == 1.0) {
            for (c10_d_j = 0; c10_d_j < 3; c10_d_j++) {
              c10_b_j = c10_d_j;
              c10_y2 = c10_y[c10_n + (c10_b_j << 1)];
              c10_yi[c10_e_k + (c10_b_j << 2)] = c10_y2;
            }
          } else {
            for (c10_e_j = 0; c10_e_j < 3; c10_e_j++) {
              c10_b_j = c10_e_j;
              c10_y1 = c10_y[(c10_n + (c10_b_j << 1)) - 1];
              c10_y2 = c10_y[c10_n + (c10_b_j << 1)];
              if (c10_y1 == c10_y2) {
                c10_yi[c10_e_k + (c10_b_j << 2)] = c10_y1;
              } else {
                c10_a = c10_onemr;
                c10_b_b = c10_y1;
                c10_d_y = (real32_T)c10_a * c10_b_b;
                c10_b_a = c10_r;
                c10_c_b = c10_y2;
                c10_e_y = (real32_T)c10_b_a * c10_c_b;
                c10_yi[c10_e_k + (c10_b_j << 2)] = c10_d_y + c10_e_y;
              }
            }
          }
        }
      }

      exitg1 = 1;
    }
  } while (exitg1 == 0);
}

static void c10_StringToMethodID(SFc10_QuadSimInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void c10_strncmpi(SFc10_QuadSimInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void c10_b_strncmpi(SFc10_QuadSimInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void c10_c_strncmpi(SFc10_QuadSimInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void c10_d_strncmpi(SFc10_QuadSimInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static boolean_T c10_isnan(SFc10_QuadSimInstanceStruct *chartInstance, real_T
  c10_x)
{
  (void)chartInstance;
  return muDoubleScalarIsNaN(c10_x);
}

static void c10_error(SFc10_QuadSimInstanceStruct *chartInstance)
{
  const mxArray *c10_y = NULL;
  static char_T c10_u[21] = { 'M', 'A', 'T', 'L', 'A', 'B', ':', 'i', 'n', 't',
    'e', 'r', 'p', '1', ':', 'N', 'a', 'N', 'i', 'n', 'X' };

  (void)chartInstance;
  c10_y = NULL;
  sf_mex_assign(&c10_y, sf_mex_create("y", c10_u, 10, 0U, 1U, 0U, 2, 1, 21),
                false);
  sf_mex_call_debug(sfGlobalDebugInstanceStruct, "error", 0U, 1U, 14,
                    sf_mex_call_debug(sfGlobalDebugInstanceStruct, "message", 1U,
    1U, 14, c10_y));
}

static void c10_runMadwickUpdate(SFc10_QuadSimInstanceStruct *chartInstance,
  real32_T c10_qIn[4], real32_T c10_b_Accelerometer[3], real32_T
  c10_b_Gyroscope[3], real32_T c10_b_Magnetometer[3], real32_T c10_b_Beta,
  real32_T c10_b_q[4])
{
  uint32_T c10_debug_family_var_map[15];
  real32_T c10_SamplePeriod;
  real_T c10_h[4];
  real_T c10_b[4];
  real32_T c10_F[6];
  real32_T c10_J[24];
  real32_T c10_step[4];
  real32_T c10_qDot[4];
  real_T c10_nargin = 5.0;
  real_T c10_nargout = 1.0;
  int32_T c10_i70;
  int32_T c10_i71;
  real32_T c10_c_Accelerometer[3];
  real32_T c10_A[3];
  int32_T c10_i72;
  boolean_T c10_b_A[3];
  int32_T c10_i73;
  int32_T c10_i74;
  real32_T c10_d_Accelerometer[3];
  real32_T c10_B;
  real32_T c10_y;
  real32_T c10_b_y;
  int32_T c10_i75;
  int32_T c10_i76;
  real32_T c10_c_Magnetometer[3];
  int32_T c10_i77;
  boolean_T c10_c_A[3];
  int32_T c10_i78;
  int32_T c10_i79;
  real32_T c10_d_Magnetometer[3];
  real32_T c10_b_B;
  real32_T c10_c_y;
  real32_T c10_d_y;
  int32_T c10_i80;
  int32_T c10_i81;
  real32_T c10_c_q[4];
  real32_T c10_C[4];
  real32_T c10_fv12[4];
  int32_T c10_i82;
  int32_T c10_i83;
  real32_T c10_b_C[4];
  real_T c10_b_b[4];
  int32_T c10_i84;
  real32_T c10_d_q[4];
  int32_T c10_i85;
  real_T c10_c_b[4];
  real_T c10_dv2[4];
  int32_T c10_i86;
  real_T c10_b_h[2];
  real_T c10_d2;
  real32_T c10_d_b;
  real32_T c10_e_y;
  real32_T c10_e_b;
  real32_T c10_f_y;
  real32_T c10_f_b;
  real32_T c10_g_y;
  real_T c10_a;
  real32_T c10_g_b;
  real32_T c10_h_y;
  real_T c10_b_a;
  real32_T c10_h_b;
  real32_T c10_i_y;
  real_T c10_c_a;
  real32_T c10_i_b;
  real32_T c10_j_y;
  real_T c10_d_a;
  real32_T c10_j_b;
  real32_T c10_k_y;
  real_T c10_e_a;
  real32_T c10_k_b;
  real32_T c10_l_y;
  real_T c10_f_a;
  real32_T c10_l_b;
  real32_T c10_m_y;
  real32_T c10_m_b;
  real32_T c10_n_y;
  real32_T c10_n_b;
  real32_T c10_o_y;
  real32_T c10_o_b;
  real32_T c10_p_y;
  real32_T c10_p_b;
  real32_T c10_q_y;
  real32_T c10_q_b;
  real32_T c10_r_y;
  real32_T c10_r_b;
  real32_T c10_s_y;
  real32_T c10_s_b;
  real32_T c10_t_y;
  real32_T c10_t_b;
  real32_T c10_u_y;
  real32_T c10_u_b;
  real32_T c10_v_y;
  real32_T c10_v_b;
  real32_T c10_w_y;
  real_T c10_g_a;
  real32_T c10_w_b;
  real32_T c10_x_y;
  real_T c10_h_a;
  real32_T c10_x_b;
  real32_T c10_y_y;
  real_T c10_i_a;
  real32_T c10_y_b;
  real32_T c10_ab_y;
  real_T c10_j_a;
  real32_T c10_ab_b;
  real32_T c10_bb_y;
  real_T c10_k_a;
  real32_T c10_bb_b;
  real32_T c10_cb_y;
  real_T c10_l_a;
  real32_T c10_cb_b;
  real32_T c10_db_y;
  real_T c10_m_a;
  real32_T c10_db_b;
  real32_T c10_eb_y;
  real_T c10_n_a;
  real32_T c10_eb_b;
  real32_T c10_fb_y;
  real_T c10_o_a;
  real32_T c10_fb_b;
  real32_T c10_gb_y;
  real_T c10_p_a;
  real32_T c10_gb_b;
  real32_T c10_hb_y;
  real_T c10_q_a;
  real32_T c10_hb_b;
  real32_T c10_ib_y;
  real_T c10_r_a;
  real32_T c10_ib_b;
  real32_T c10_jb_y;
  real_T c10_s_a;
  real32_T c10_jb_b;
  real32_T c10_kb_y;
  real_T c10_t_a;
  real32_T c10_kb_b;
  real32_T c10_lb_y;
  real_T c10_u_a;
  real32_T c10_lb_b;
  real32_T c10_mb_y;
  real_T c10_v_a;
  real32_T c10_mb_b;
  real32_T c10_nb_y;
  real_T c10_w_a;
  real32_T c10_nb_b;
  real32_T c10_ob_y;
  real_T c10_x_a;
  real32_T c10_ob_b;
  real32_T c10_pb_y;
  real_T c10_y_a;
  real32_T c10_pb_b;
  real32_T c10_qb_y;
  real_T c10_ab_a;
  real32_T c10_qb_b;
  real32_T c10_rb_y;
  int32_T c10_i87;
  int32_T c10_i88;
  int32_T c10_i89;
  int32_T c10_i90;
  real32_T c10_bb_a[24];
  int32_T c10_i91;
  real32_T c10_rb_b[6];
  int32_T c10_i92;
  int32_T c10_i93;
  int32_T c10_i94;
  int32_T c10_i95;
  int32_T c10_i96;
  int32_T c10_i97;
  int32_T c10_i98;
  int32_T c10_i99;
  int32_T c10_i100;
  real32_T c10_b_step[4];
  real32_T c10_c_B;
  real32_T c10_sb_y;
  real32_T c10_tb_y;
  int32_T c10_i101;
  int32_T c10_i102;
  real32_T c10_cb_a[4];
  real32_T c10_sb_b[4];
  uint32_T c10_b_debug_family_var_map[5];
  real_T c10_b_nargin = 2.0;
  real_T c10_b_nargout = 1.0;
  real_T c10_ab[4];
  int32_T c10_i103;
  int32_T c10_i104;
  int32_T c10_i105;
  real32_T c10_db_a;
  int32_T c10_i106;
  int32_T c10_i107;
  int32_T c10_i108;
  int32_T c10_i109;
  int32_T c10_i110;
  boolean_T c10_tb_b[4];
  int32_T c10_i111;
  boolean_T c10_ub_y;
  int32_T c10_k;
  real_T c10_b_k;
  int32_T c10_i112;
  int32_T c10_i113;
  int32_T c10_i114;
  int32_T c10_i115;
  int32_T c10_i116;
  real32_T c10_e_q[4];
  real32_T c10_d_B;
  real32_T c10_vb_y;
  real32_T c10_wb_y;
  int32_T c10_i117;
  boolean_T exitg1;
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 15U, 15U, c10_f_debug_family_names,
    c10_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c10_SamplePeriod, 0U, c10_d_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c10_h, 1U, c10_i_sf_marshallOut,
    c10_g_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c10_b, 2U, c10_n_sf_marshallOut,
    c10_m_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c10_F, 3U, c10_m_sf_marshallOut,
    c10_l_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c10_J, 4U, c10_l_sf_marshallOut,
    c10_k_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c10_step, 5U, c10_h_sf_marshallOut,
    c10_f_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c10_qDot, 6U, c10_h_sf_marshallOut,
    c10_f_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c10_nargin, 7U, c10_g_sf_marshallOut,
    c10_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c10_nargout, 8U, c10_g_sf_marshallOut,
    c10_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c10_qIn, 9U, c10_h_sf_marshallOut,
    c10_f_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c10_b_Accelerometer, 10U,
    c10_k_sf_marshallOut, c10_j_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c10_b_Gyroscope, 11U,
    c10_k_sf_marshallOut, c10_j_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c10_b_Magnetometer, 12U,
    c10_k_sf_marshallOut, c10_j_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c10_b_Beta, 13U, c10_d_sf_marshallOut,
    c10_i_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c10_b_q, 14U, c10_h_sf_marshallOut,
    c10_f_sf_marshallIn);
  CV_EML_FCN(0, 1);
  _SFD_EML_CALL(0U, chartInstance->c10_sfEvent, 28);
  for (c10_i70 = 0; c10_i70 < 4; c10_i70++) {
    c10_b_q[c10_i70] = c10_qIn[c10_i70];
  }

  _SFD_EML_CALL(0U, chartInstance->c10_sfEvent, 29);
  c10_SamplePeriod = 0.005F;
  _SFD_EML_CALL(0U, chartInstance->c10_sfEvent, 32);
  for (c10_i71 = 0; c10_i71 < 3; c10_i71++) {
    c10_c_Accelerometer[c10_i71] = c10_b_Accelerometer[c10_i71];
  }

  c10_abs(chartInstance, c10_c_Accelerometer, c10_A);
  for (c10_i72 = 0; c10_i72 < 3; c10_i72++) {
    c10_b_A[c10_i72] = ((real_T)c10_A[c10_i72] < 0.0001);
  }

  if (CV_EML_IF(0, 1, 2, CV_EML_MCDC(0, 1, 0, !CV_EML_COND(0, 1, 0, c10_all
         (chartInstance, c10_b_A))))) {
    _SFD_EML_CALL(0U, chartInstance->c10_sfEvent, 33);
    for (c10_i73 = 0; c10_i73 < 3; c10_i73++) {
      c10_A[c10_i73] = c10_b_Accelerometer[c10_i73];
    }

    for (c10_i74 = 0; c10_i74 < 3; c10_i74++) {
      c10_d_Accelerometer[c10_i74] = c10_b_Accelerometer[c10_i74];
    }

    c10_B = c10_norm(chartInstance, c10_d_Accelerometer);
    c10_y = c10_B;
    c10_b_y = c10_y;
    for (c10_i75 = 0; c10_i75 < 3; c10_i75++) {
      c10_b_Accelerometer[c10_i75] = c10_A[c10_i75] / c10_b_y;
    }
  }

  _SFD_EML_CALL(0U, chartInstance->c10_sfEvent, 36);
  for (c10_i76 = 0; c10_i76 < 3; c10_i76++) {
    c10_c_Magnetometer[c10_i76] = c10_b_Magnetometer[c10_i76];
  }

  c10_abs(chartInstance, c10_c_Magnetometer, c10_A);
  for (c10_i77 = 0; c10_i77 < 3; c10_i77++) {
    c10_c_A[c10_i77] = ((real_T)c10_A[c10_i77] < 0.0001);
  }

  if (CV_EML_IF(0, 1, 3, CV_EML_MCDC(0, 1, 1, !CV_EML_COND(0, 1, 1, c10_all
         (chartInstance, c10_c_A))))) {
    _SFD_EML_CALL(0U, chartInstance->c10_sfEvent, 37);
    for (c10_i78 = 0; c10_i78 < 3; c10_i78++) {
      c10_A[c10_i78] = c10_b_Magnetometer[c10_i78];
    }

    for (c10_i79 = 0; c10_i79 < 3; c10_i79++) {
      c10_d_Magnetometer[c10_i79] = c10_b_Magnetometer[c10_i79];
    }

    c10_b_B = c10_norm(chartInstance, c10_d_Magnetometer);
    c10_c_y = c10_b_B;
    c10_d_y = c10_c_y;
    for (c10_i80 = 0; c10_i80 < 3; c10_i80++) {
      c10_b_Magnetometer[c10_i80] = c10_A[c10_i80] / c10_d_y;
    }
  }

  _SFD_EML_CALL(0U, chartInstance->c10_sfEvent, 40);
  for (c10_i81 = 0; c10_i81 < 4; c10_i81++) {
    c10_c_q[c10_i81] = c10_b_q[c10_i81];
  }

  c10_quaternConj(chartInstance, c10_c_q, c10_C);
  c10_fv12[0] = 0.0F;
  for (c10_i82 = 0; c10_i82 < 3; c10_i82++) {
    c10_fv12[c10_i82 + 1] = c10_b_Magnetometer[c10_i82];
  }

  for (c10_i83 = 0; c10_i83 < 4; c10_i83++) {
    c10_b_C[c10_i83] = c10_C[c10_i83];
  }

  c10_quaternProd(chartInstance, c10_fv12, c10_b_C, c10_b_b);
  for (c10_i84 = 0; c10_i84 < 4; c10_i84++) {
    c10_d_q[c10_i84] = c10_b_q[c10_i84];
  }

  for (c10_i85 = 0; c10_i85 < 4; c10_i85++) {
    c10_c_b[c10_i85] = c10_b_b[c10_i85];
  }

  c10_b_quaternProd(chartInstance, c10_d_q, c10_c_b, c10_dv2);
  for (c10_i86 = 0; c10_i86 < 4; c10_i86++) {
    c10_h[c10_i86] = c10_dv2[c10_i86];
  }

  _SFD_EML_CALL(0U, chartInstance->c10_sfEvent, 41);
  c10_b_h[0] = c10_h[1];
  c10_b_h[1] = c10_h[2];
  c10_d2 = c10_b_norm(chartInstance, c10_b_h);
  c10_b[0] = 0.0;
  c10_b[1] = c10_d2;
  c10_b[2] = 0.0;
  c10_b[3] = c10_h[3];
  _SFD_EML_CALL(0U, chartInstance->c10_sfEvent, 43);
  c10_d_b = c10_b_q[1] * c10_b_q[3] - c10_b_q[0] * c10_b_q[2];
  c10_e_y = 2.0F * c10_d_b;
  c10_e_b = c10_b_q[0] * c10_b_q[1] + c10_b_q[2] * c10_b_q[3];
  c10_f_y = 2.0F * c10_e_b;
  c10_f_b = (0.5F - c10_mpower(chartInstance, c10_b_q[1])) - c10_mpower
    (chartInstance, c10_b_q[2]);
  c10_g_y = 2.0F * c10_f_b;
  c10_a = 2.0 * c10_b[1];
  c10_g_b = (0.5F - c10_mpower(chartInstance, c10_b_q[2])) - c10_mpower
    (chartInstance, c10_b_q[3]);
  c10_h_y = (real32_T)c10_a * c10_g_b;
  c10_b_a = 2.0 * c10_b[3];
  c10_h_b = c10_b_q[1] * c10_b_q[3] - c10_b_q[0] * c10_b_q[2];
  c10_i_y = (real32_T)c10_b_a * c10_h_b;
  c10_c_a = 2.0 * c10_b[1];
  c10_i_b = c10_b_q[1] * c10_b_q[2] - c10_b_q[0] * c10_b_q[3];
  c10_j_y = (real32_T)c10_c_a * c10_i_b;
  c10_d_a = 2.0 * c10_b[3];
  c10_j_b = c10_b_q[0] * c10_b_q[1] + c10_b_q[2] * c10_b_q[3];
  c10_k_y = (real32_T)c10_d_a * c10_j_b;
  c10_e_a = 2.0 * c10_b[1];
  c10_k_b = c10_b_q[0] * c10_b_q[2] + c10_b_q[1] * c10_b_q[3];
  c10_l_y = (real32_T)c10_e_a * c10_k_b;
  c10_f_a = 2.0 * c10_b[3];
  c10_l_b = (0.5F - c10_mpower(chartInstance, c10_b_q[1])) - c10_mpower
    (chartInstance, c10_b_q[2]);
  c10_m_y = (real32_T)c10_f_a * c10_l_b;
  c10_F[0] = c10_e_y - c10_b_Accelerometer[0];
  c10_F[1] = c10_f_y - c10_b_Accelerometer[1];
  c10_F[2] = c10_g_y - c10_b_Accelerometer[2];
  c10_F[3] = (c10_h_y + c10_i_y) - c10_b_Magnetometer[0];
  c10_F[4] = (c10_j_y + c10_k_y) - c10_b_Magnetometer[1];
  c10_F[5] = (c10_l_y + c10_m_y) - c10_b_Magnetometer[2];
  _SFD_EML_CALL(0U, chartInstance->c10_sfEvent, 49);
  c10_m_b = c10_b_q[2];
  c10_n_y = -2.0F * c10_m_b;
  c10_n_b = c10_b_q[3];
  c10_o_y = 2.0F * c10_n_b;
  c10_o_b = c10_b_q[0];
  c10_p_y = -2.0F * c10_o_b;
  c10_p_b = c10_b_q[1];
  c10_q_y = 2.0F * c10_p_b;
  c10_q_b = c10_b_q[1];
  c10_r_y = 2.0F * c10_q_b;
  c10_r_b = c10_b_q[0];
  c10_s_y = 2.0F * c10_r_b;
  c10_s_b = c10_b_q[3];
  c10_t_y = 2.0F * c10_s_b;
  c10_t_b = c10_b_q[2];
  c10_u_y = 2.0F * c10_t_b;
  c10_u_b = c10_b_q[1];
  c10_v_y = -4.0F * c10_u_b;
  c10_v_b = c10_b_q[2];
  c10_w_y = -4.0F * c10_v_b;
  c10_g_a = -2.0 * c10_b[3];
  c10_w_b = c10_b_q[2];
  c10_x_y = (real32_T)c10_g_a * c10_w_b;
  c10_h_a = 2.0 * c10_b[3];
  c10_x_b = c10_b_q[3];
  c10_y_y = (real32_T)c10_h_a * c10_x_b;
  c10_i_a = -4.0 * c10_b[1];
  c10_y_b = c10_b_q[2];
  c10_ab_y = (real32_T)c10_i_a * c10_y_b;
  c10_j_a = 2.0 * c10_b[3];
  c10_ab_b = c10_b_q[0];
  c10_bb_y = (real32_T)c10_j_a * c10_ab_b;
  c10_k_a = -4.0 * c10_b[1];
  c10_bb_b = c10_b_q[3];
  c10_cb_y = (real32_T)c10_k_a * c10_bb_b;
  c10_l_a = 2.0 * c10_b[3];
  c10_cb_b = c10_b_q[1];
  c10_db_y = (real32_T)c10_l_a * c10_cb_b;
  c10_m_a = -2.0 * c10_b[1];
  c10_db_b = c10_b_q[3];
  c10_eb_y = (real32_T)c10_m_a * c10_db_b;
  c10_n_a = 2.0 * c10_b[3];
  c10_eb_b = c10_b_q[1];
  c10_fb_y = (real32_T)c10_n_a * c10_eb_b;
  c10_o_a = 2.0 * c10_b[1];
  c10_fb_b = c10_b_q[2];
  c10_gb_y = (real32_T)c10_o_a * c10_fb_b;
  c10_p_a = 2.0 * c10_b[3];
  c10_gb_b = c10_b_q[0];
  c10_hb_y = (real32_T)c10_p_a * c10_gb_b;
  c10_q_a = 2.0 * c10_b[1];
  c10_hb_b = c10_b_q[1];
  c10_ib_y = (real32_T)c10_q_a * c10_hb_b;
  c10_r_a = 2.0 * c10_b[3];
  c10_ib_b = c10_b_q[3];
  c10_jb_y = (real32_T)c10_r_a * c10_ib_b;
  c10_s_a = -2.0 * c10_b[1];
  c10_jb_b = c10_b_q[0];
  c10_kb_y = (real32_T)c10_s_a * c10_jb_b;
  c10_t_a = 2.0 * c10_b[3];
  c10_kb_b = c10_b_q[2];
  c10_lb_y = (real32_T)c10_t_a * c10_kb_b;
  c10_u_a = 2.0 * c10_b[1];
  c10_lb_b = c10_b_q[2];
  c10_mb_y = (real32_T)c10_u_a * c10_lb_b;
  c10_v_a = 2.0 * c10_b[1];
  c10_mb_b = c10_b_q[3];
  c10_nb_y = (real32_T)c10_v_a * c10_mb_b;
  c10_w_a = 4.0 * c10_b[3];
  c10_nb_b = c10_b_q[1];
  c10_ob_y = (real32_T)c10_w_a * c10_nb_b;
  c10_x_a = 2.0 * c10_b[1];
  c10_ob_b = c10_b_q[0];
  c10_pb_y = (real32_T)c10_x_a * c10_ob_b;
  c10_y_a = 4.0 * c10_b[3];
  c10_pb_b = c10_b_q[2];
  c10_qb_y = (real32_T)c10_y_a * c10_pb_b;
  c10_ab_a = 2.0 * c10_b[1];
  c10_qb_b = c10_b_q[1];
  c10_rb_y = (real32_T)c10_ab_a * c10_qb_b;
  c10_J[0] = c10_n_y;
  c10_J[6] = c10_o_y;
  c10_J[12] = c10_p_y;
  c10_J[18] = c10_q_y;
  c10_J[1] = c10_r_y;
  c10_J[7] = c10_s_y;
  c10_J[13] = c10_t_y;
  c10_J[19] = c10_u_y;
  c10_J[2] = 0.0F;
  c10_J[8] = c10_v_y;
  c10_J[14] = c10_w_y;
  c10_J[20] = 0.0F;
  c10_J[3] = c10_x_y;
  c10_J[9] = c10_y_y;
  c10_J[15] = c10_ab_y - c10_bb_y;
  c10_J[21] = c10_cb_y + c10_db_y;
  c10_J[4] = c10_eb_y + c10_fb_y;
  c10_J[10] = c10_gb_y + c10_hb_y;
  c10_J[16] = c10_ib_y + c10_jb_y;
  c10_J[22] = c10_kb_y + c10_lb_y;
  c10_J[5] = c10_mb_y;
  c10_J[11] = c10_nb_y - c10_ob_y;
  c10_J[17] = c10_pb_y - c10_qb_y;
  c10_J[23] = c10_rb_y;
  _SFD_EML_CALL(0U, chartInstance->c10_sfEvent, 55);
  c10_i87 = 0;
  for (c10_i88 = 0; c10_i88 < 6; c10_i88++) {
    c10_i89 = 0;
    for (c10_i90 = 0; c10_i90 < 4; c10_i90++) {
      c10_bb_a[c10_i90 + c10_i87] = c10_J[c10_i89 + c10_i88];
      c10_i89 += 6;
    }

    c10_i87 += 4;
  }

  for (c10_i91 = 0; c10_i91 < 6; c10_i91++) {
    c10_rb_b[c10_i91] = c10_F[c10_i91];
  }

  for (c10_i92 = 0; c10_i92 < 4; c10_i92++) {
    c10_step[c10_i92] = 0.0F;
  }

  for (c10_i93 = 0; c10_i93 < 4; c10_i93++) {
    c10_step[c10_i93] = 0.0F;
  }

  for (c10_i94 = 0; c10_i94 < 4; c10_i94++) {
    c10_C[c10_i94] = c10_step[c10_i94];
  }

  for (c10_i95 = 0; c10_i95 < 4; c10_i95++) {
    c10_step[c10_i95] = c10_C[c10_i95];
  }

  for (c10_i96 = 0; c10_i96 < 4; c10_i96++) {
    c10_step[c10_i96] = 0.0F;
    c10_i97 = 0;
    for (c10_i98 = 0; c10_i98 < 6; c10_i98++) {
      c10_step[c10_i96] += c10_bb_a[c10_i97 + c10_i96] * c10_rb_b[c10_i98];
      c10_i97 += 4;
    }
  }

  _SFD_EML_CALL(0U, chartInstance->c10_sfEvent, 56);
  for (c10_i99 = 0; c10_i99 < 4; c10_i99++) {
    c10_C[c10_i99] = c10_step[c10_i99];
  }

  for (c10_i100 = 0; c10_i100 < 4; c10_i100++) {
    c10_b_step[c10_i100] = c10_step[c10_i100];
  }

  c10_c_B = c10_c_norm(chartInstance, c10_b_step);
  c10_sb_y = c10_c_B;
  c10_tb_y = c10_sb_y;
  for (c10_i101 = 0; c10_i101 < 4; c10_i101++) {
    c10_step[c10_i101] = c10_C[c10_i101] / c10_tb_y;
  }

  _SFD_EML_CALL(0U, chartInstance->c10_sfEvent, 59);
  for (c10_i102 = 0; c10_i102 < 4; c10_i102++) {
    c10_cb_a[c10_i102] = c10_b_q[c10_i102];
  }

  c10_sb_b[0] = 0.0F;
  c10_sb_b[1] = c10_b_Gyroscope[0];
  c10_sb_b[2] = c10_b_Gyroscope[1];
  c10_sb_b[3] = c10_b_Gyroscope[2];
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 5U, 5U, c10_e_debug_family_names,
    c10_b_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c10_b_nargin, 0U, c10_g_sf_marshallOut,
    c10_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c10_b_nargout, 1U, c10_g_sf_marshallOut,
    c10_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c10_cb_a, 2U, c10_h_sf_marshallOut,
    c10_f_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c10_sb_b, 3U, c10_h_sf_marshallOut,
    c10_f_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c10_ab, 4U, c10_i_sf_marshallOut,
    c10_g_sf_marshallIn);
  CV_EML_FCN(0, 2);
  _SFD_EML_CALL(0U, chartInstance->c10_sfEvent, 69);
  for (c10_i103 = 0; c10_i103 < 4; c10_i103++) {
    c10_ab[c10_i103] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c10_sfEvent, 82);
  c10_ab[0] = ((c10_cb_a[0] * c10_sb_b[0] - c10_cb_a[1] * c10_sb_b[1]) -
               c10_cb_a[2] * c10_sb_b[2]) - c10_cb_a[3] * c10_sb_b[3];
  _SFD_EML_CALL(0U, chartInstance->c10_sfEvent, 83);
  c10_ab[1] = ((c10_cb_a[0] * c10_sb_b[1] + c10_cb_a[1] * c10_sb_b[0]) +
               c10_cb_a[2] * c10_sb_b[3]) - c10_cb_a[3] * c10_sb_b[2];
  _SFD_EML_CALL(0U, chartInstance->c10_sfEvent, 84);
  c10_ab[2] = ((c10_cb_a[0] * c10_sb_b[2] - c10_cb_a[1] * c10_sb_b[3]) +
               c10_cb_a[2] * c10_sb_b[0]) + c10_cb_a[3] * c10_sb_b[1];
  _SFD_EML_CALL(0U, chartInstance->c10_sfEvent, 85);
  c10_ab[3] = ((c10_cb_a[0] * c10_sb_b[3] + c10_cb_a[1] * c10_sb_b[2]) -
               c10_cb_a[2] * c10_sb_b[1]) + c10_cb_a[3] * c10_sb_b[0];
  _SFD_EML_CALL(0U, chartInstance->c10_sfEvent, -85);
  _SFD_SYMBOL_SCOPE_POP();
  for (c10_i104 = 0; c10_i104 < 4; c10_i104++) {
    c10_b_b[c10_i104] = c10_ab[c10_i104];
  }

  for (c10_i105 = 0; c10_i105 < 4; c10_i105++) {
    c10_b_b[c10_i105] *= 0.5;
  }

  c10_db_a = c10_b_Beta;
  for (c10_i106 = 0; c10_i106 < 4; c10_i106++) {
    c10_C[c10_i106] = c10_step[c10_i106];
  }

  for (c10_i107 = 0; c10_i107 < 4; c10_i107++) {
    c10_C[c10_i107] *= c10_db_a;
  }

  for (c10_i108 = 0; c10_i108 < 4; c10_i108++) {
    c10_qDot[c10_i108] = (real32_T)c10_b_b[c10_i108] - c10_C[c10_i108];
  }

  _SFD_EML_CALL(0U, chartInstance->c10_sfEvent, 62);
  for (c10_i109 = 0; c10_i109 < 4; c10_i109++) {
    c10_C[c10_i109] = c10_qDot[c10_i109];
  }

  for (c10_i110 = 0; c10_i110 < 4; c10_i110++) {
    c10_tb_b[c10_i110] = muSingleScalarIsNaN(c10_C[c10_i110]);
  }

  for (c10_i111 = 0; c10_i111 < 4; c10_i111++) {
    c10_tb_b[c10_i111] = !c10_tb_b[c10_i111];
  }

  c10_ub_y = true;
  c10_k = 0;
  exitg1 = false;
  while ((exitg1 == false) && (c10_k < 4)) {
    c10_b_k = 1.0 + (real_T)c10_k;
    if (!c10_tb_b[(int32_T)c10_b_k - 1]) {
      c10_ub_y = false;
      exitg1 = true;
    } else {
      c10_k++;
    }
  }

  if (CV_EML_IF(0, 1, 4, c10_ub_y)) {
    _SFD_EML_CALL(0U, chartInstance->c10_sfEvent, 63);
    for (c10_i112 = 0; c10_i112 < 4; c10_i112++) {
      c10_C[c10_i112] = c10_qDot[c10_i112];
    }

    for (c10_i113 = 0; c10_i113 < 4; c10_i113++) {
      c10_C[c10_i113] *= 0.005F;
    }

    for (c10_i114 = 0; c10_i114 < 4; c10_i114++) {
      c10_b_q[c10_i114] += c10_C[c10_i114];
    }

    _SFD_EML_CALL(0U, chartInstance->c10_sfEvent, 64);
    for (c10_i115 = 0; c10_i115 < 4; c10_i115++) {
      c10_C[c10_i115] = c10_b_q[c10_i115];
    }

    for (c10_i116 = 0; c10_i116 < 4; c10_i116++) {
      c10_e_q[c10_i116] = c10_b_q[c10_i116];
    }

    c10_d_B = c10_c_norm(chartInstance, c10_e_q);
    c10_vb_y = c10_d_B;
    c10_wb_y = c10_vb_y;
    for (c10_i117 = 0; c10_i117 < 4; c10_i117++) {
      c10_b_q[c10_i117] = c10_C[c10_i117] / c10_wb_y;
    }
  }

  _SFD_EML_CALL(0U, chartInstance->c10_sfEvent, -64);
  _SFD_SYMBOL_SCOPE_POP();
}

static void c10_abs(SFc10_QuadSimInstanceStruct *chartInstance, real32_T c10_x[3],
                    real32_T c10_y[3])
{
  int32_T c10_k;
  int32_T c10_b_k;
  real32_T c10_b_x;
  real32_T c10_b_y;
  (void)chartInstance;
  for (c10_k = 1; c10_k < 4; c10_k++) {
    c10_b_k = c10_k - 1;
    c10_b_x = c10_x[c10_b_k];
    c10_b_y = muSingleScalarAbs(c10_b_x);
    c10_y[c10_b_k] = c10_b_y;
  }
}

static boolean_T c10_all(SFc10_QuadSimInstanceStruct *chartInstance, boolean_T
  c10_x[3])
{
  boolean_T c10_y;
  int32_T c10_k;
  real_T c10_b_k;
  boolean_T exitg1;
  (void)chartInstance;
  c10_y = true;
  c10_k = 0;
  exitg1 = false;
  while ((exitg1 == false) && (c10_k < 3)) {
    c10_b_k = 1.0 + (real_T)c10_k;
    if (!c10_x[(int32_T)c10_b_k - 1]) {
      c10_y = false;
      exitg1 = true;
    } else {
      c10_k++;
    }
  }

  return c10_y;
}

static real32_T c10_norm(SFc10_QuadSimInstanceStruct *chartInstance, real32_T
  c10_x[3])
{
  real32_T c10_y;
  real32_T c10_scale;
  int32_T c10_k;
  int32_T c10_b_k;
  real32_T c10_absxk;
  real32_T c10_t;
  c10_y = 0.0F;
  c10_scale = 1.17549435E-38F;
  for (c10_k = 1; c10_k < 4; c10_k++) {
    c10_b_k = c10_k - 1;
    c10_absxk = c10_b_abs(chartInstance, c10_x[c10_b_k]);
    if (c10_absxk > c10_scale) {
      c10_t = c10_scale / c10_absxk;
      c10_y = 1.0F + c10_y * c10_t * c10_t;
      c10_scale = c10_absxk;
    } else {
      c10_t = c10_absxk / c10_scale;
      c10_y += c10_t * c10_t;
    }
  }

  return c10_scale * muSingleScalarSqrt(c10_y);
}

static void c10_realmin(SFc10_QuadSimInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static real32_T c10_b_abs(SFc10_QuadSimInstanceStruct *chartInstance, real32_T
  c10_x)
{
  real32_T c10_b_x;
  real32_T c10_c_x;
  (void)chartInstance;
  c10_b_x = c10_x;
  c10_c_x = c10_b_x;
  return muSingleScalarAbs(c10_c_x);
}

static void c10_quaternConj(SFc10_QuadSimInstanceStruct *chartInstance, real32_T
  c10_b_q[4], real32_T c10_qConj[4])
{
  uint32_T c10_debug_family_var_map[4];
  real_T c10_nargin = 1.0;
  real_T c10_nargout = 1.0;
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 4U, 4U, c10_b_debug_family_names,
    c10_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c10_nargin, 0U, c10_g_sf_marshallOut,
    c10_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c10_nargout, 1U, c10_g_sf_marshallOut,
    c10_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c10_b_q, 2U, c10_h_sf_marshallOut,
    c10_f_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c10_qConj, 3U, c10_h_sf_marshallOut,
    c10_f_sf_marshallIn);
  CV_EML_FCN(0, 3);
  _SFD_EML_CALL(0U, chartInstance->c10_sfEvent, 100);
  c10_qConj[0] = c10_b_q[0];
  c10_qConj[1] = -c10_b_q[1];
  c10_qConj[2] = -c10_b_q[2];
  c10_qConj[3] = -c10_b_q[3];
  _SFD_EML_CALL(0U, chartInstance->c10_sfEvent, -100);
  _SFD_SYMBOL_SCOPE_POP();
}

static void c10_quaternProd(SFc10_QuadSimInstanceStruct *chartInstance, real32_T
  c10_a[4], real32_T c10_b[4], real_T c10_ab[4])
{
  uint32_T c10_debug_family_var_map[5];
  real_T c10_nargin = 2.0;
  real_T c10_nargout = 1.0;
  int32_T c10_i118;
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 5U, 5U, c10_c_debug_family_names,
    c10_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c10_nargin, 0U, c10_g_sf_marshallOut,
    c10_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c10_nargout, 1U, c10_g_sf_marshallOut,
    c10_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c10_a, 2U, c10_j_sf_marshallOut,
    c10_h_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c10_b, 3U, c10_h_sf_marshallOut,
    c10_f_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c10_ab, 4U, c10_i_sf_marshallOut,
    c10_g_sf_marshallIn);
  CV_EML_FCN(0, 2);
  _SFD_EML_CALL(0U, chartInstance->c10_sfEvent, 69);
  for (c10_i118 = 0; c10_i118 < 4; c10_i118++) {
    c10_ab[c10_i118] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c10_sfEvent, 82);
  c10_ab[0] = ((c10_a[0] * c10_b[0] - c10_a[1] * c10_b[1]) - c10_a[2] * c10_b[2])
    - c10_a[3] * c10_b[3];
  _SFD_EML_CALL(0U, chartInstance->c10_sfEvent, 83);
  c10_ab[1] = ((c10_a[0] * c10_b[1] + c10_a[1] * c10_b[0]) + c10_a[2] * c10_b[3])
    - c10_a[3] * c10_b[2];
  _SFD_EML_CALL(0U, chartInstance->c10_sfEvent, 84);
  c10_ab[2] = ((c10_a[0] * c10_b[2] - c10_a[1] * c10_b[3]) + c10_a[2] * c10_b[0])
    + c10_a[3] * c10_b[1];
  _SFD_EML_CALL(0U, chartInstance->c10_sfEvent, 85);
  c10_ab[3] = ((c10_a[0] * c10_b[3] + c10_a[1] * c10_b[2]) - c10_a[2] * c10_b[1])
    + c10_a[3] * c10_b[0];
  _SFD_EML_CALL(0U, chartInstance->c10_sfEvent, -85);
  _SFD_SYMBOL_SCOPE_POP();
}

static void c10_b_quaternProd(SFc10_QuadSimInstanceStruct *chartInstance,
  real32_T c10_a[4], real_T c10_b[4], real_T c10_ab[4])
{
  uint32_T c10_debug_family_var_map[5];
  real_T c10_nargin = 2.0;
  real_T c10_nargout = 1.0;
  int32_T c10_i119;
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 5U, 5U, c10_d_debug_family_names,
    c10_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c10_nargin, 0U, c10_g_sf_marshallOut,
    c10_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c10_nargout, 1U, c10_g_sf_marshallOut,
    c10_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c10_a, 2U, c10_h_sf_marshallOut,
    c10_f_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c10_b, 3U, c10_i_sf_marshallOut,
    c10_g_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c10_ab, 4U, c10_i_sf_marshallOut,
    c10_g_sf_marshallIn);
  CV_EML_FCN(0, 2);
  _SFD_EML_CALL(0U, chartInstance->c10_sfEvent, 69);
  for (c10_i119 = 0; c10_i119 < 4; c10_i119++) {
    c10_ab[c10_i119] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c10_sfEvent, 82);
  c10_ab[0] = ((c10_a[0] * (real32_T)c10_b[0] - c10_a[1] * (real32_T)c10_b[1]) -
               c10_a[2] * (real32_T)c10_b[2]) - c10_a[3] * (real32_T)c10_b[3];
  _SFD_EML_CALL(0U, chartInstance->c10_sfEvent, 83);
  c10_ab[1] = ((c10_a[0] * (real32_T)c10_b[1] + c10_a[1] * (real32_T)c10_b[0]) +
               c10_a[2] * (real32_T)c10_b[3]) - c10_a[3] * (real32_T)c10_b[2];
  _SFD_EML_CALL(0U, chartInstance->c10_sfEvent, 84);
  c10_ab[2] = ((c10_a[0] * (real32_T)c10_b[2] - c10_a[1] * (real32_T)c10_b[3]) +
               c10_a[2] * (real32_T)c10_b[0]) + c10_a[3] * (real32_T)c10_b[1];
  _SFD_EML_CALL(0U, chartInstance->c10_sfEvent, 85);
  c10_ab[3] = ((c10_a[0] * (real32_T)c10_b[3] + c10_a[1] * (real32_T)c10_b[2]) -
               c10_a[2] * (real32_T)c10_b[1]) + c10_a[3] * (real32_T)c10_b[0];
  _SFD_EML_CALL(0U, chartInstance->c10_sfEvent, -85);
  _SFD_SYMBOL_SCOPE_POP();
}

static real_T c10_b_norm(SFc10_QuadSimInstanceStruct *chartInstance, real_T
  c10_x[2])
{
  real_T c10_y;
  real_T c10_scale;
  int32_T c10_k;
  int32_T c10_b_k;
  real_T c10_b_x;
  real_T c10_c_x;
  real_T c10_d_x;
  real_T c10_absxk;
  real_T c10_t;
  (void)chartInstance;
  c10_y = 0.0;
  c10_scale = 2.2250738585072014E-308;
  for (c10_k = 1; c10_k < 3; c10_k++) {
    c10_b_k = c10_k - 1;
    c10_b_x = c10_x[c10_b_k];
    c10_c_x = c10_b_x;
    c10_d_x = c10_c_x;
    c10_absxk = muDoubleScalarAbs(c10_d_x);
    if (c10_absxk > c10_scale) {
      c10_t = c10_scale / c10_absxk;
      c10_y = 1.0 + c10_y * c10_t * c10_t;
      c10_scale = c10_absxk;
    } else {
      c10_t = c10_absxk / c10_scale;
      c10_y += c10_t * c10_t;
    }
  }

  return c10_scale * muDoubleScalarSqrt(c10_y);
}

static real32_T c10_mpower(SFc10_QuadSimInstanceStruct *chartInstance, real32_T
  c10_a)
{
  real32_T c10_c;
  real32_T c10_b_a;
  real32_T c10_c_a;
  real32_T c10_x;
  real32_T c10_d_a;
  boolean_T c10_p;
  c10_b_a = c10_a;
  c10_c_a = c10_b_a;
  c10_x = c10_c_a;
  c10_d_a = c10_x;
  c10_c = c10_d_a * c10_d_a;
  c10_p = false;
  if (c10_p) {
    c10_b_error(chartInstance);
  }

  return c10_c;
}

static void c10_b_scalarEg(SFc10_QuadSimInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void c10_dimagree(SFc10_QuadSimInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void c10_b_error(SFc10_QuadSimInstanceStruct *chartInstance)
{
  const mxArray *c10_y = NULL;
  static char_T c10_u[31] = { 'C', 'o', 'd', 'e', 'r', ':', 't', 'o', 'o', 'l',
    'b', 'o', 'x', ':', 'p', 'o', 'w', 'e', 'r', '_', 'd', 'o', 'm', 'a', 'i',
    'n', 'E', 'r', 'r', 'o', 'r' };

  (void)chartInstance;
  c10_y = NULL;
  sf_mex_assign(&c10_y, sf_mex_create("y", c10_u, 10, 0U, 1U, 0U, 2, 1, 31),
                false);
  sf_mex_call_debug(sfGlobalDebugInstanceStruct, "error", 0U, 1U, 14,
                    sf_mex_call_debug(sfGlobalDebugInstanceStruct, "message", 1U,
    1U, 14, c10_y));
}

static void c10_c_scalarEg(SFc10_QuadSimInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void c10_d_scalarEg(SFc10_QuadSimInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static real32_T c10_c_norm(SFc10_QuadSimInstanceStruct *chartInstance, real32_T
  c10_x[4])
{
  real32_T c10_y;
  real32_T c10_scale;
  int32_T c10_k;
  int32_T c10_b_k;
  real32_T c10_absxk;
  real32_T c10_t;
  c10_y = 0.0F;
  c10_scale = 1.17549435E-38F;
  for (c10_k = 1; c10_k < 5; c10_k++) {
    c10_b_k = c10_k - 1;
    c10_absxk = c10_b_abs(chartInstance, c10_x[c10_b_k]);
    if (c10_absxk > c10_scale) {
      c10_t = c10_scale / c10_absxk;
      c10_y = 1.0F + c10_y * c10_t * c10_t;
      c10_scale = c10_absxk;
    } else {
      c10_t = c10_absxk / c10_scale;
      c10_y += c10_t * c10_t;
    }
  }

  return c10_scale * muSingleScalarSqrt(c10_y);
}

static const mxArray *c10_o_sf_marshallOut(void *chartInstanceVoid, void
  *c10_inData)
{
  const mxArray *c10_mxArrayOutData = NULL;
  int32_T c10_u;
  const mxArray *c10_y = NULL;
  SFc10_QuadSimInstanceStruct *chartInstance;
  chartInstance = (SFc10_QuadSimInstanceStruct *)chartInstanceVoid;
  c10_mxArrayOutData = NULL;
  c10_u = *(int32_T *)c10_inData;
  c10_y = NULL;
  sf_mex_assign(&c10_y, sf_mex_create("y", &c10_u, 6, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c10_mxArrayOutData, c10_y, false);
  return c10_mxArrayOutData;
}

static int32_T c10_q_emlrt_marshallIn(SFc10_QuadSimInstanceStruct *chartInstance,
  const mxArray *c10_u, const emlrtMsgIdentifier *c10_parentId)
{
  int32_T c10_y;
  int32_T c10_i120;
  (void)chartInstance;
  sf_mex_import(c10_parentId, sf_mex_dup(c10_u), &c10_i120, 1, 6, 0U, 0, 0U, 0);
  c10_y = c10_i120;
  sf_mex_destroy(&c10_u);
  return c10_y;
}

static void c10_n_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c10_mxArrayInData, const char_T *c10_varName, void *c10_outData)
{
  const mxArray *c10_b_sfEvent;
  const char_T *c10_identifier;
  emlrtMsgIdentifier c10_thisId;
  int32_T c10_y;
  SFc10_QuadSimInstanceStruct *chartInstance;
  chartInstance = (SFc10_QuadSimInstanceStruct *)chartInstanceVoid;
  c10_b_sfEvent = sf_mex_dup(c10_mxArrayInData);
  c10_identifier = c10_varName;
  c10_thisId.fIdentifier = c10_identifier;
  c10_thisId.fParent = NULL;
  c10_thisId.bParentIsCell = false;
  c10_y = c10_q_emlrt_marshallIn(chartInstance, sf_mex_dup(c10_b_sfEvent),
    &c10_thisId);
  sf_mex_destroy(&c10_b_sfEvent);
  *(int32_T *)c10_outData = c10_y;
  sf_mex_destroy(&c10_mxArrayInData);
}

static uint8_T c10_r_emlrt_marshallIn(SFc10_QuadSimInstanceStruct *chartInstance,
  const mxArray *c10_b_is_active_c10_QuadSim, const char_T *c10_identifier)
{
  uint8_T c10_y;
  emlrtMsgIdentifier c10_thisId;
  c10_thisId.fIdentifier = c10_identifier;
  c10_thisId.fParent = NULL;
  c10_thisId.bParentIsCell = false;
  c10_y = c10_s_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c10_b_is_active_c10_QuadSim), &c10_thisId);
  sf_mex_destroy(&c10_b_is_active_c10_QuadSim);
  return c10_y;
}

static uint8_T c10_s_emlrt_marshallIn(SFc10_QuadSimInstanceStruct *chartInstance,
  const mxArray *c10_u, const emlrtMsgIdentifier *c10_parentId)
{
  uint8_T c10_y;
  uint8_T c10_u0;
  (void)chartInstance;
  sf_mex_import(c10_parentId, sf_mex_dup(c10_u), &c10_u0, 1, 3, 0U, 0, 0U, 0);
  c10_y = c10_u0;
  sf_mex_destroy(&c10_u);
  return c10_y;
}

static void init_dsm_address_info(SFc10_QuadSimInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void init_simulink_io_address(SFc10_QuadSimInstanceStruct *chartInstance)
{
  chartInstance->c10_Accelerometer = (real32_T (*)[12])
    ssGetInputPortSignal_wrapper(chartInstance->S, 0);
  chartInstance->c10_q = (real32_T (*)[4])ssGetOutputPortSignal_wrapper
    (chartInstance->S, 1);
  chartInstance->c10_Gyroscope = (real32_T (*)[12])ssGetInputPortSignal_wrapper
    (chartInstance->S, 1);
  chartInstance->c10_Magnetometer = (real32_T (*)[6])
    ssGetInputPortSignal_wrapper(chartInstance->S, 2);
  chartInstance->c10_Beta = (real32_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 3);
}

/* SFunction Glue Code */
#ifdef utFree
#undef utFree
#endif

#ifdef utMalloc
#undef utMalloc
#endif

#ifdef __cplusplus

extern "C" void *utMalloc(size_t size);
extern "C" void utFree(void*);

#else

extern void *utMalloc(size_t size);
extern void utFree(void*);

#endif

void sf_c10_QuadSim_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(3370484217U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(860141054U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(3606543839U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(676594630U);
}

mxArray* sf_c10_QuadSim_get_post_codegen_info(void);
mxArray *sf_c10_QuadSim_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals", "postCodegenInfo" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1, 1, sizeof
    (autoinheritanceFields)/sizeof(autoinheritanceFields[0]),
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("w2oYr05UWvjdGdtEB6vZWF");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,4,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(3);
      pr[1] = (double)(4);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(9));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(3);
      pr[1] = (double)(4);
      mxSetField(mxData,1,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(9));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,1,"type",mxType);
    }

    mxSetField(mxData,1,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(3);
      pr[1] = (double)(2);
      mxSetField(mxData,2,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(9));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,2,"type",mxType);
    }

    mxSetField(mxData,2,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,3,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(9));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,3,"type",mxType);
    }

    mxSetField(mxData,3,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"inputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"parameters",mxCreateDoubleMatrix(0,0,
                mxREAL));
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,1,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(4);
      pr[1] = (double)(1);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(9));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  {
    mxArray* mxPostCodegenInfo = sf_c10_QuadSim_get_post_codegen_info();
    mxSetField(mxAutoinheritanceInfo,0,"postCodegenInfo",mxPostCodegenInfo);
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c10_QuadSim_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

mxArray *sf_c10_QuadSim_jit_fallback_info(void)
{
  const char *infoFields[] = { "fallbackType", "fallbackReason",
    "hiddenFallbackType", "hiddenFallbackReason", "incompatibleSymbol" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 5, infoFields);
  mxArray *fallbackType = mxCreateString("pre");
  mxArray *fallbackReason = mxCreateString("hasBreakpoints");
  mxArray *hiddenFallbackType = mxCreateString("none");
  mxArray *hiddenFallbackReason = mxCreateString("");
  mxArray *incompatibleSymbol = mxCreateString("");
  mxSetField(mxInfo, 0, infoFields[0], fallbackType);
  mxSetField(mxInfo, 0, infoFields[1], fallbackReason);
  mxSetField(mxInfo, 0, infoFields[2], hiddenFallbackType);
  mxSetField(mxInfo, 0, infoFields[3], hiddenFallbackReason);
  mxSetField(mxInfo, 0, infoFields[4], incompatibleSymbol);
  return mxInfo;
}

mxArray *sf_c10_QuadSim_updateBuildInfo_args_info(void)
{
  mxArray *mxBIArgs = mxCreateCellMatrix(1,0);
  return mxBIArgs;
}

mxArray* sf_c10_QuadSim_get_post_codegen_info(void)
{
  const char* fieldNames[] = { "exportedFunctionsUsedByThisChart",
    "exportedFunctionsChecksum" };

  mwSize dims[2] = { 1, 1 };

  mxArray* mxPostCodegenInfo = mxCreateStructArray(2, dims, sizeof(fieldNames)/
    sizeof(fieldNames[0]), fieldNames);

  {
    mxArray* mxExportedFunctionsChecksum = mxCreateString("");
    mwSize exp_dims[2] = { 0, 1 };

    mxArray* mxExportedFunctionsUsedByThisChart = mxCreateCellArray(2, exp_dims);
    mxSetField(mxPostCodegenInfo, 0, "exportedFunctionsUsedByThisChart",
               mxExportedFunctionsUsedByThisChart);
    mxSetField(mxPostCodegenInfo, 0, "exportedFunctionsChecksum",
               mxExportedFunctionsChecksum);
  }

  return mxPostCodegenInfo;
}

static const mxArray *sf_get_sim_state_info_c10_QuadSim(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x4'type','srcId','name','auxInfo'{{M[1],M[5],T\"q\",},{M[4],M[0],T\"counter\",S'l','i','p'{{M1x2[93 100],M[0],}}},{M[4],M[0],T\"qLocal\",S'l','i','p'{{M1x2[86 92],M[0],}}},{M[8],M[0],T\"is_active_c10_QuadSim\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 4, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c10_QuadSim_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc10_QuadSimInstanceStruct *chartInstance = (SFc10_QuadSimInstanceStruct *)
      sf_get_chart_instance_ptr(S);
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _QuadSimMachineNumber_,
           10,
           1,
           1,
           0,
           5,
           0,
           0,
           0,
           0,
           0,
           &(chartInstance->chartNumber),
           &(chartInstance->instanceNumber),
           (void *)S);

        /* Each instance must initialize its own list of scripts */
        init_script_number_translation(_QuadSimMachineNumber_,
          chartInstance->chartNumber,chartInstance->instanceNumber);
        if (chartAlreadyPresent==0) {
          /* this is the first instance */
          sf_debug_set_chart_disable_implicit_casting
            (sfGlobalDebugInstanceStruct,_QuadSimMachineNumber_,
             chartInstance->chartNumber,1);
          sf_debug_set_chart_event_thresholds(sfGlobalDebugInstanceStruct,
            _QuadSimMachineNumber_,
            chartInstance->chartNumber,
            0,
            0,
            0);
          _SFD_SET_DATA_PROPS(0,1,1,0,"Accelerometer");
          _SFD_SET_DATA_PROPS(1,1,1,0,"Gyroscope");
          _SFD_SET_DATA_PROPS(2,1,1,0,"Magnetometer");
          _SFD_SET_DATA_PROPS(3,1,1,0,"Beta");
          _SFD_SET_DATA_PROPS(4,2,0,1,"q");
          _SFD_STATE_INFO(0,0,2);
          _SFD_CH_SUBSTATE_COUNT(0);
          _SFD_CH_SUBSTATE_DECOMP(0);
        }

        _SFD_CV_INIT_CHART(0,0,0,0);

        {
          _SFD_CV_INIT_STATE(0,0,0,0,0,0,NULL,NULL);
        }

        _SFD_CV_INIT_TRANS(0,0,NULL,NULL,0,NULL);

        /* Initialization of MATLAB Function Model Coverage */
        _SFD_CV_INIT_EML(0,1,4,0,5,0,0,0,1,0,2,2);
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,429);
        _SFD_CV_INIT_EML_FCN(0,1,"runMadwickUpdate",429,-1,2397);
        _SFD_CV_INIT_EML_FCN(0,2,"quaternProd",2397,-1,2982);
        _SFD_CV_INIT_EML_FCN(0,3,"quaternConj",2982,-1,3350);
        _SFD_CV_INIT_EML_IF(0,1,0,101,119,-1,169);
        _SFD_CV_INIT_EML_IF(0,1,1,204,218,-1,231);
        _SFD_CV_INIT_EML_IF(0,1,2,582,615,-1,699);
        _SFD_CV_INIT_EML_IF(0,1,3,737,769,-1,849);
        _SFD_CV_INIT_EML_IF(0,1,4,2301,2321,-1,2394);
        _SFD_CV_INIT_EML_FOR(0,1,0,294,304,416);

        {
          static int condStart[] = { 586 };

          static int condEnd[] = { 615 };

          static int pfixExpr[] = { 0, -1 };

          _SFD_CV_INIT_EML_MCDC(0,1,0,585,615,1,0,&(condStart[0]),&(condEnd[0]),
                                2,&(pfixExpr[0]));
        }

        {
          static int condStart[] = { 741 };

          static int condEnd[] = { 769 };

          static int pfixExpr[] = { 0, -1 };

          _SFD_CV_INIT_EML_MCDC(0,1,1,740,769,1,1,&(condStart[0]),&(condEnd[0]),
                                2,&(pfixExpr[0]));
        }

        _SFD_CV_INIT_EML_RELATIONAL(0,1,0,207,218,-1,4);

        {
          unsigned int dimVector[2];
          dimVector[0]= 3U;
          dimVector[1]= 4U;
          _SFD_SET_DATA_COMPILED_PROPS(0,SF_SINGLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c10_f_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 3U;
          dimVector[1]= 4U;
          _SFD_SET_DATA_COMPILED_PROPS(1,SF_SINGLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c10_f_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 3U;
          dimVector[1]= 2U;
          _SFD_SET_DATA_COMPILED_PROPS(2,SF_SINGLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c10_e_sf_marshallOut,(MexInFcnForType)NULL);
        }

        _SFD_SET_DATA_COMPILED_PROPS(3,SF_SINGLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c10_d_sf_marshallOut,(MexInFcnForType)NULL);

        {
          unsigned int dimVector[2];
          dimVector[0]= 4U;
          dimVector[1]= 1U;
          _SFD_SET_DATA_COMPILED_PROPS(4,SF_SINGLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c10_c_sf_marshallOut,(MexInFcnForType)
            c10_c_sf_marshallIn);
        }
      }
    } else {
      sf_debug_reset_current_state_configuration(sfGlobalDebugInstanceStruct,
        _QuadSimMachineNumber_,chartInstance->chartNumber,
        chartInstance->instanceNumber);
    }
  }
}

static void chart_debug_initialize_data_addresses(SimStruct *S)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc10_QuadSimInstanceStruct *chartInstance = (SFc10_QuadSimInstanceStruct *)
      sf_get_chart_instance_ptr(S);
    if (ssIsFirstInitCond(S)) {
      /* do this only if simulation is starting and after we know the addresses of all data */
      {
        _SFD_SET_DATA_VALUE_PTR(0U, *chartInstance->c10_Accelerometer);
        _SFD_SET_DATA_VALUE_PTR(4U, *chartInstance->c10_q);
        _SFD_SET_DATA_VALUE_PTR(1U, *chartInstance->c10_Gyroscope);
        _SFD_SET_DATA_VALUE_PTR(2U, *chartInstance->c10_Magnetometer);
        _SFD_SET_DATA_VALUE_PTR(3U, chartInstance->c10_Beta);
      }
    }
  }
}

static const char* sf_get_instance_specialization(void)
{
  return "skrz61SPm00Bw1E92MD1fnB";
}

static void sf_opaque_initialize_c10_QuadSim(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc10_QuadSimInstanceStruct*) chartInstanceVar)
    ->S,0);
  initialize_params_c10_QuadSim((SFc10_QuadSimInstanceStruct*) chartInstanceVar);
  initialize_c10_QuadSim((SFc10_QuadSimInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c10_QuadSim(void *chartInstanceVar)
{
  enable_c10_QuadSim((SFc10_QuadSimInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c10_QuadSim(void *chartInstanceVar)
{
  disable_c10_QuadSim((SFc10_QuadSimInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c10_QuadSim(void *chartInstanceVar)
{
  sf_gateway_c10_QuadSim((SFc10_QuadSimInstanceStruct*) chartInstanceVar);
}

static const mxArray* sf_opaque_get_sim_state_c10_QuadSim(SimStruct* S)
{
  return get_sim_state_c10_QuadSim((SFc10_QuadSimInstanceStruct *)
    sf_get_chart_instance_ptr(S));     /* raw sim ctx */
}

static void sf_opaque_set_sim_state_c10_QuadSim(SimStruct* S, const mxArray *st)
{
  set_sim_state_c10_QuadSim((SFc10_QuadSimInstanceStruct*)
    sf_get_chart_instance_ptr(S), st);
}

static void sf_opaque_terminate_c10_QuadSim(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc10_QuadSimInstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_QuadSim_optimization_info();
    }

    finalize_c10_QuadSim((SFc10_QuadSimInstanceStruct*) chartInstanceVar);
    utFree(chartInstanceVar);
    if (ssGetUserData(S)!= NULL) {
      sf_free_ChartRunTimeInfo(S);
    }

    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc10_QuadSim((SFc10_QuadSimInstanceStruct*) chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c10_QuadSim(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c10_QuadSim((SFc10_QuadSimInstanceStruct*)
      sf_get_chart_instance_ptr(S));
  }
}

static void mdlSetWorkWidths_c10_QuadSim(SimStruct *S)
{
  ssMdlUpdateIsEmpty(S, 1);
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_QuadSim_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(sf_get_instance_specialization(),infoStruct,
      10);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,1);
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop
      (sf_get_instance_specialization(),infoStruct,10,
       "gatewayCannotBeInlinedMultipleTimes"));
    sf_set_chart_accesses_machine_info(S, sf_get_instance_specialization(),
      infoStruct, 10);
    sf_update_buildInfo(sf_get_instance_specialization(),infoStruct,10);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 2, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 3, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,10,4);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,10,1);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=1; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 4; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,10);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(1569107220U));
  ssSetChecksum1(S,(4273007918U));
  ssSetChecksum2(S,(385539260U));
  ssSetChecksum3(S,(2547587315U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c10_QuadSim(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c10_QuadSim(SimStruct *S)
{
  SFc10_QuadSimInstanceStruct *chartInstance;
  chartInstance = (SFc10_QuadSimInstanceStruct *)utMalloc(sizeof
    (SFc10_QuadSimInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  memset(chartInstance, 0, sizeof(SFc10_QuadSimInstanceStruct));
  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c10_QuadSim;
  chartInstance->chartInfo.initializeChart = sf_opaque_initialize_c10_QuadSim;
  chartInstance->chartInfo.terminateChart = sf_opaque_terminate_c10_QuadSim;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c10_QuadSim;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c10_QuadSim;
  chartInstance->chartInfo.getSimState = sf_opaque_get_sim_state_c10_QuadSim;
  chartInstance->chartInfo.setSimState = sf_opaque_set_sim_state_c10_QuadSim;
  chartInstance->chartInfo.getSimStateInfo = sf_get_sim_state_info_c10_QuadSim;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c10_QuadSim;
  chartInstance->chartInfo.mdlStart = mdlStart_c10_QuadSim;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c10_QuadSim;
  chartInstance->chartInfo.callGetHoverDataForMsg = NULL;
  chartInstance->chartInfo.extModeExec = NULL;
  chartInstance->chartInfo.restoreLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.restoreBeforeLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.storeCurrentConfiguration = NULL;
  chartInstance->chartInfo.callAtomicSubchartUserFcn = NULL;
  chartInstance->chartInfo.callAtomicSubchartAutoFcn = NULL;
  chartInstance->chartInfo.debugInstance = sfGlobalDebugInstanceStruct;
  chartInstance->S = S;
  sf_init_ChartRunTimeInfo(S, &(chartInstance->chartInfo), false, 0);
  init_dsm_address_info(chartInstance);
  init_simulink_io_address(chartInstance);
  if (!sim_mode_is_rtw_gen(S)) {
  }

  chart_debug_initialization(S,1);
  mdl_start_c10_QuadSim(chartInstance);
}

void c10_QuadSim_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c10_QuadSim(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c10_QuadSim(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c10_QuadSim(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c10_QuadSim_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
