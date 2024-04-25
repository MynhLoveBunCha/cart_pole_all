//
// File: MPC_controller.cpp
//
// Code generated for Simulink model 'MPC_controller'.
//
// Model version                  : 1.20
// Simulink Coder version         : 9.8 (R2022b) 13-May-2022
// C/C++ source code generated on : Fri Mar  1 15:04:28 2024
//
// Target selection: ert.tlc
// Embedded hardware selection: ARM Compatible->ARM Cortex-M
// Code generation objectives:
//    1. Execution efficiency
//    2. RAM efficiency
// Validation result: Not run
//
#include "MPC_controller.h"
#include "rtwtypes.h"
#include <cstring>
#include <cmath>
#include <stddef.h>
#define NumBitsPerChar                 8U

extern real_T rt_hypotd_snf(real_T u0, real_T u1);
extern "C"
{
  real_T rtInf;
  real_T rtMinusInf;
  real_T rtNaN;
  real32_T rtInfF;
  real32_T rtMinusInfF;
  real32_T rtNaNF;
}

extern "C"
{
  //
  // Initialize rtInf needed by the generated code.
  // Inf is initialized as non-signaling. Assumes IEEE.
  //
  static real_T rtGetInf(void)
  {
    size_t bitsPerReal{ sizeof(real_T) * (NumBitsPerChar) };

    real_T inf{ 0.0 };

    if (bitsPerReal == 32U) {
      inf = rtGetInfF();
    } else {
      union {
        LittleEndianIEEEDouble bitVal;
        real_T fltVal;
      } tmpVal;

      tmpVal.bitVal.words.wordH = 0x7FF00000U;
      tmpVal.bitVal.words.wordL = 0x00000000U;
      inf = tmpVal.fltVal;
    }

    return inf;
  }

  //
  // Initialize rtInfF needed by the generated code.
  // Inf is initialized as non-signaling. Assumes IEEE.
  //
  static real32_T rtGetInfF(void)
  {
    IEEESingle infF;
    infF.wordL.wordLuint = 0x7F800000U;
    return infF.wordL.wordLreal;
  }

  //
  // Initialize rtMinusInf needed by the generated code.
  // Inf is initialized as non-signaling. Assumes IEEE.
  //
  static real_T rtGetMinusInf(void)
  {
    size_t bitsPerReal{ sizeof(real_T) * (NumBitsPerChar) };

    real_T minf{ 0.0 };

    if (bitsPerReal == 32U) {
      minf = rtGetMinusInfF();
    } else {
      union {
        LittleEndianIEEEDouble bitVal;
        real_T fltVal;
      } tmpVal;

      tmpVal.bitVal.words.wordH = 0xFFF00000U;
      tmpVal.bitVal.words.wordL = 0x00000000U;
      minf = tmpVal.fltVal;
    }

    return minf;
  }

  //
  // Initialize rtMinusInfF needed by the generated code.
  // Inf is initialized as non-signaling. Assumes IEEE.
  //
  static real32_T rtGetMinusInfF(void)
  {
    IEEESingle minfF;
    minfF.wordL.wordLuint = 0xFF800000U;
    return minfF.wordL.wordLreal;
  }
}

extern "C"
{
  //
  // Initialize rtNaN needed by the generated code.
  // NaN is initialized as non-signaling. Assumes IEEE.
  //
  static real_T rtGetNaN(void)
  {
    size_t bitsPerReal{ sizeof(real_T) * (NumBitsPerChar) };

    real_T nan{ 0.0 };

    if (bitsPerReal == 32U) {
      nan = rtGetNaNF();
    } else {
      union {
        LittleEndianIEEEDouble bitVal;
        real_T fltVal;
      } tmpVal;

      tmpVal.bitVal.words.wordH = 0xFFF80000U;
      tmpVal.bitVal.words.wordL = 0x00000000U;
      nan = tmpVal.fltVal;
    }

    return nan;
  }

  //
  // Initialize rtNaNF needed by the generated code.
  // NaN is initialized as non-signaling. Assumes IEEE.
  //
  static real32_T rtGetNaNF(void)
  {
    IEEESingle nanF{ { 0.0F } };

    nanF.wordL.wordLuint = 0xFFC00000U;
    return nanF.wordL.wordLreal;
  }
}

extern "C"
{
  //
  // Initialize the rtInf, rtMinusInf, and rtNaN needed by the
  // generated code. NaN is initialized as non-signaling. Assumes IEEE.
  //
  static void rt_InitInfAndNaN(size_t realSize)
  {
    (void) (realSize);
    rtNaN = rtGetNaN();
    rtNaNF = rtGetNaNF();
    rtInf = rtGetInf();
    rtInfF = rtGetInfF();
    rtMinusInf = rtGetMinusInf();
    rtMinusInfF = rtGetMinusInfF();
  }

  // Test if value is infinite
  static boolean_T rtIsInf(real_T value)
  {
    return (boolean_T)((value==rtInf || value==rtMinusInf) ? 1U : 0U);
  }

  // Test if single-precision value is infinite
  static boolean_T rtIsInfF(real32_T value)
  {
    return (boolean_T)(((value)==rtInfF || (value)==rtMinusInfF) ? 1U : 0U);
  }

  // Test if value is not a number
  static boolean_T rtIsNaN(real_T value)
  {
    boolean_T result{ (boolean_T) 0 };

    size_t bitsPerReal{ sizeof(real_T) * (NumBitsPerChar) };

    if (bitsPerReal == 32U) {
      result = rtIsNaNF((real32_T)value);
    } else {
      union {
        LittleEndianIEEEDouble bitVal;
        real_T fltVal;
      } tmpVal;

      tmpVal.fltVal = value;
      result = (boolean_T)((tmpVal.bitVal.words.wordH & 0x7FF00000) ==
                           0x7FF00000 &&
                           ( (tmpVal.bitVal.words.wordH & 0x000FFFFF) != 0 ||
                            (tmpVal.bitVal.words.wordL != 0) ));
    }

    return result;
  }

  // Test if single-precision value is not a number
  static boolean_T rtIsNaNF(real32_T value)
  {
    IEEESingle tmp;
    tmp.wordL.wordLreal = value;
    return (boolean_T)( (tmp.wordL.wordLuint & 0x7F800000) == 0x7F800000 &&
                       (tmp.wordL.wordLuint & 0x007FFFFF) != 0 );
  }
}

// Function for MATLAB Function: '<S2>/NLMPC'
void MPC_controller::mtimes(const real_T A_data[], const int32_T A_size[2],
  real_T C_data[], int32_T C_size[2])
{
  static const int8_T c[50]{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 1, 1, 1, 1, 1, 1 };

  int32_T m;
  m = A_size[0];
  C_size[0] = A_size[0];
  C_size[1] = 5;
  for (int32_T j{0}; j < 5; j++) {
    int32_T boffset;
    int32_T coffset;
    coffset = j * m;
    boffset = j * 10;
    for (int32_T i{0}; i < m; i++) {
      real_T s;
      s = 0.0;
      for (int32_T k{0}; k < 10; k++) {
        s += A_data[k * A_size[0] + i] * static_cast<real_T>(c[boffset + k]);
      }

      C_data[coffset + i] = s;
    }
  }
}

// Function for MATLAB Function: '<S2>/NLMPC'
void MPC_controller::znlmpc_getXUe(const real_T z[46], const real_T x[4], real_T
  X_1[44], real_T U[11], real_T *e)
{
  static const int8_T y[50]{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 1, 1, 1, 1, 1, 1 };

  real_T z_0[40];
  std::memset(&X_1[0], 0, 44U * sizeof(real_T));
  std::memset(&U[0], 0, 11U * sizeof(real_T));
  for (int32_T i{0}; i < 10; i++) {
    U[i] = 0.0;
    for (int32_T i_0{0}; i_0 < 5; i_0++) {
      U[i] += static_cast<real_T>(y[10 * i_0 + i]) * z[i_0 + 40];
    }
  }

  *e = z[45];
  std::memcpy(&z_0[0], &z[0], 40U * sizeof(real_T));
  for (int32_T i{0}; i < 4; i++) {
    for (int32_T i_0{0}; i_0 < 10; i_0++) {
      X_1[(i_0 + 11 * i) + 1] = z_0[(i_0 << 2) + i];
    }

    X_1[11 * i] = x[i];
  }

  U[10] = U[9];
}

// Function for MATLAB Function: '<S2>/NLMPC'
void MPC_controller::all(const boolean_T x[40], boolean_T y[4])
{
  int32_T ix;
  boolean_T exitg1;
  y[0] = true;
  y[1] = true;
  y[2] = true;
  y[3] = true;
  ix = 1;
  exitg1 = false;
  while ((!exitg1) && (ix <= 10)) {
    if (!x[ix - 1]) {
      y[0] = false;
      exitg1 = true;
    } else {
      ix++;
    }
  }

  ix = 11;
  exitg1 = false;
  while ((!exitg1) && (ix <= 20)) {
    if (!x[ix - 1]) {
      y[1] = false;
      exitg1 = true;
    } else {
      ix++;
    }
  }

  ix = 21;
  exitg1 = false;
  while ((!exitg1) && (ix <= 30)) {
    if (!x[ix - 1]) {
      y[2] = false;
      exitg1 = true;
    } else {
      ix++;
    }
  }

  ix = 31;
  exitg1 = false;
  while ((!exitg1) && (ix <= 40)) {
    if (!x[ix - 1]) {
      y[3] = false;
      exitg1 = true;
    } else {
      ix++;
    }
  }
}

// Function for MATLAB Function: '<S2>/NLMPC'
boolean_T MPC_controller::any(const boolean_T x[8])
{
  int32_T k;
  boolean_T exitg1;
  boolean_T y;
  y = false;
  k = 0;
  exitg1 = false;
  while ((!exitg1) && (k <= 7)) {
    if (x[k]) {
      y = true;
      exitg1 = true;
    } else {
      k++;
    }
  }

  return y;
}

// Function for MATLAB Function: '<S2>/NLMPC'
void MPC_controller::eML_blk_kernel_anonFcn2(const real_T runtimedata_x[4],
  const real_T runtimedata_OutputMin[40], const real_T runtimedata_OutputMax[40],
  const real_T z[46], real_T varargout_1_data[], int32_T varargout_1_size[2],
  real_T varargout_2[40], real_T varargout_3_data[], int32_T varargout_3_size[2],
  real_T varargout_4[1840])
{
  static const int8_T b_b[50]{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 1, 1, 1, 1, 1, 1 };

  static const int8_T j[16]{ 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };

  static const int8_T val[16]{ -1, 0, 0, 0, 0, -1, 0, 0, 0, 0, -1, 0, 0, 0, 0,
    -1 };

  real_T Jmv[400];
  real_T tmp_data[400];
  real_T varargin_2_data[400];
  real_T Jmv_0[200];
  real_T c[80];
  real_T c_data[80];
  real_T X_0[44];
  real_T b_X[44];
  real_T Ak[16];
  real_T Ak1[16];
  real_T U[11];
  real_T ic[4];
  real_T tmp_0[4];
  real_T yk[4];
  real_T U_0;
  real_T e;
  int32_T ic_0[8];
  int32_T tmp_size[2];
  int32_T tmp_size_0[2];
  int32_T Ak1_tmp_tmp_tmp;
  int32_T a_tmp_tmp;
  int32_T b_varargin_1_size_idx_0;
  int32_T d_size_idx_0;
  int32_T i;
  int32_T varargin_1_size_idx_1;
  int32_T varargout_2_tmp;
  int32_T varargout_2_tmp_tmp;
  int8_T Je[80];
  int8_T b_data[80];
  int8_T d_data[80];
  int8_T d[2];
  int8_T tmp_1[2];
  int8_T varargin_2[2];
  int8_T b_sizes_idx_1;
  int8_T tmp_2;
  boolean_T icf[80];
  boolean_T tmp[40];
  boolean_T icf_0[8];
  boolean_T x[4];
  boolean_T exitg1;
  boolean_T y;
  znlmpc_getXUe(z, runtimedata_x, X_0, U, &e);
  std::memset(&rtDW.Jx[0], 0, 1600U * sizeof(real_T));
  std::memset(&Jmv[0], 0, 400U * sizeof(real_T));
  std::memset(&varargout_2[0], 0, 40U * sizeof(real_T));
  ic[0] = 1.0;
  ic[1] = 2.0;
  ic[2] = 3.0;
  ic[3] = 4.0;
  for (a_tmp_tmp = 0; a_tmp_tmp < 11; a_tmp_tmp++) {
    i = a_tmp_tmp << 2;
    b_X[i] = X_0[a_tmp_tmp];
    b_X[i + 1] = X_0[a_tmp_tmp + 11];
    b_X[i + 2] = X_0[a_tmp_tmp + 22];
    b_X[i + 3] = X_0[a_tmp_tmp + 33];
  }

  Ak[3] = 0.0;
  Ak[7] = 0.0;
  Ak[0] = 0.0;
  Ak[1] = 0.0;
  Ak[2] = 0.0;
  Ak1[0] = 0.0;
  Ak1[1] = 0.0;
  Ak1[2] = 0.0;
  Ak[4] = 1.0;
  Ak[5] = 0.0;
  Ak[6] = 0.0;
  Ak1[4] = 1.0;
  Ak1[5] = 0.0;
  Ak1[6] = 0.0;
  Ak[8] = 0.0;
  Ak[9] = 0.0;
  Ak[10] = 0.0;
  Ak1[8] = 0.0;
  Ak1[9] = 0.0;
  Ak1[10] = 0.0;
  Ak[12] = 0.0;
  Ak[13] = 0.0;
  Ak[14] = 1.0;
  Ak1[12] = 0.0;
  Ak1[13] = 0.0;
  Ak1[14] = 1.0;
  Ak1[3] = 0.0;
  Ak1[7] = 0.0;
  yk[0] = 0.0;
  yk[1] = 1.0;
  yk[2] = 0.0;
  tmp_0[0] = 0.0;
  tmp_0[1] = 1.0;
  tmp_0[2] = 0.0;
  for (i = 0; i < 10; i++) {
    real_T Ak1_tmp;
    real_T Ak1_tmp_0;
    real_T Ak1_tmp_tmp;
    real_T Ak_tmp;
    real_T Ak_tmp_tmp;
    real_T a_tmp;
    real_T b_a_tmp;
    real_T varargout_2_tmp_0;
    real_T varargout_2_tmp_1;
    real_T varargout_2_tmp_2;
    U_0 = U[i];
    a_tmp_tmp = i << 2;
    a_tmp = std::tanh(b_X[a_tmp_tmp + 3] * 150.0);
    Ak_tmp_tmp = b_X[a_tmp_tmp + 2];
    Ak_tmp = std::sin(Ak_tmp_tmp);
    Ak_tmp_tmp = std::cos(Ak_tmp_tmp);
    Ak[11] = (0.01747905 * U_0 * Ak_tmp + 0.1714109256825 * Ak_tmp_tmp) /
      0.0034958100000000002;
    Ak[15] = -((b_X[(i << 2) + 3] * 2.0E-6 + 0.000161) - (a_tmp * a_tmp - 1.0) *
               0.060000000000000005) / 0.0034958100000000002;
    b_a_tmp = std::tanh(b_X[((i + 1) << 2) + 3] * 150.0);
    Ak1_tmp_tmp_tmp = (i + 1) << 2;
    Ak1_tmp_tmp = b_X[Ak1_tmp_tmp_tmp + 2];
    Ak1_tmp = std::sin(Ak1_tmp_tmp);
    Ak1_tmp_tmp = std::cos(Ak1_tmp_tmp);
    Ak1[11] = (0.01747905 * U_0 * Ak1_tmp + 0.1714109256825 * Ak1_tmp_tmp) /
      0.0034958100000000002;
    Ak1_tmp_0 = b_X[Ak1_tmp_tmp_tmp + 3];
    Ak1[15] = -((Ak1_tmp_0 * 2.0E-6 + 0.000161) - (b_a_tmp * b_a_tmp - 1.0) *
                0.060000000000000005) / 0.0034958100000000002;
    varargout_2_tmp = i << 2;
    varargout_2_tmp_0 = b_X[varargout_2_tmp + 1];
    varargout_2_tmp_1 = b_X[Ak1_tmp_tmp_tmp + 1];
    varargout_2[static_cast<int32_T>(ic[0]) - 1] = ((varargout_2_tmp_1 +
      varargout_2_tmp_0) * 0.05 + b_X[varargout_2_tmp]) - b_X[Ak1_tmp_tmp_tmp];
    varargout_2[static_cast<int32_T>(ic[1]) - 1] = ((U_0 + U_0) * 0.05 +
      varargout_2_tmp_0) - varargout_2_tmp_1;
    a_tmp_tmp = i << 2;
    varargout_2_tmp_2 = b_X[a_tmp_tmp + 2];
    varargout_2[static_cast<int32_T>(ic[2]) - 1] = ((b_X[varargout_2_tmp + 3] +
      Ak1_tmp_0) * 0.05 + varargout_2_tmp_2) - b_X[Ak1_tmp_tmp_tmp + 2];
    varargout_2_tmp_tmp = (i + 1) << 2;
    varargout_2_tmp_0 = b_X[varargout_2_tmp_tmp + 3];
    varargout_2_tmp_1 = b_X[a_tmp_tmp + 3];
    varargout_2[static_cast<int32_T>(ic[3]) - 1] = ((((((0.1714109256825 *
      Ak1_tmp - 0.01747905 * Ak1_tmp_tmp * U_0) - varargout_2_tmp_0 * 0.000161)
      - varargout_2_tmp_0 * varargout_2_tmp_0 * 1.0E-6) - 0.0004 * b_a_tmp) /
      0.0034958100000000002 + ((((0.1714109256825 * Ak_tmp - 0.01747905 *
      Ak_tmp_tmp * U_0) - varargout_2_tmp_1 * 0.000161) - varargout_2_tmp_1 *
      varargout_2_tmp_1 * 1.0E-6) - 0.0004 * a_tmp) / 0.0034958100000000002) *
      0.05 + varargout_2_tmp_1) - varargout_2_tmp_0;
    if (i + 1 > 1) {
      for (a_tmp_tmp = 0; a_tmp_tmp < 4; a_tmp_tmp++) {
        varargout_2_tmp = a_tmp_tmp << 2;
        Ak1_tmp_tmp_tmp = (i - 1) * 160;
        rtDW.Jx[((static_cast<int32_T>(ic[0]) + 40 * a_tmp_tmp) +
                 Ak1_tmp_tmp_tmp) - 1] = Ak[varargout_2_tmp] * 0.05;
        rtDW.Jx[((static_cast<int32_T>(ic[1]) + 40 * a_tmp_tmp) +
                 Ak1_tmp_tmp_tmp) - 1] = Ak[varargout_2_tmp + 1] * 0.05;
        rtDW.Jx[((static_cast<int32_T>(ic[2]) + 40 * a_tmp_tmp) +
                 Ak1_tmp_tmp_tmp) - 1] = Ak[varargout_2_tmp + 2] * 0.05;
        rtDW.Jx[((static_cast<int32_T>(ic[3]) + 40 * a_tmp_tmp) +
                 Ak1_tmp_tmp_tmp) - 1] = Ak[varargout_2_tmp + 3] * 0.05;
        varargout_2_tmp = 40 * a_tmp_tmp + static_cast<int32_T>(ic[a_tmp_tmp]);
        rtDW.Jx[(varargout_2_tmp + 160 * (i - 1)) - 1] = rtDW.Jx
          [(varargout_2_tmp + Ak1_tmp_tmp_tmp) - 1] + 1.0;
      }
    }

    yk[3] = -(std::cos(varargout_2_tmp_2) * 0.01747905) / 0.0034958100000000002;
    tmp_0[3] = -(std::cos(b_X[varargout_2_tmp_tmp + 2]) * 0.01747905) /
      0.0034958100000000002;
    for (a_tmp_tmp = 0; a_tmp_tmp < 4; a_tmp_tmp++) {
      Ak1_tmp_tmp_tmp = a_tmp_tmp << 2;
      rtDW.Jx[((static_cast<int32_T>(ic[0]) + 40 * a_tmp_tmp) + 160 * i) - 1] =
        Ak1[Ak1_tmp_tmp_tmp] * 0.05;
      rtDW.Jx[((static_cast<int32_T>(ic[1]) + 40 * a_tmp_tmp) + 160 * i) - 1] =
        Ak1[Ak1_tmp_tmp_tmp + 1] * 0.05;
      rtDW.Jx[((static_cast<int32_T>(ic[2]) + 40 * a_tmp_tmp) + 160 * i) - 1] =
        Ak1[Ak1_tmp_tmp_tmp + 2] * 0.05;
      rtDW.Jx[((static_cast<int32_T>(ic[3]) + 40 * a_tmp_tmp) + 160 * i) - 1] =
        Ak1[Ak1_tmp_tmp_tmp + 3] * 0.05;
      varargout_2_tmp = ((40 * a_tmp_tmp + static_cast<int32_T>(ic[a_tmp_tmp]))
                         + 160 * i) - 1;
      rtDW.Jx[varargout_2_tmp]--;
      Jmv[(static_cast<int32_T>(ic[a_tmp_tmp]) + 40 * i) - 1] = (yk[a_tmp_tmp] +
        tmp_0[a_tmp_tmp]) * 0.05;
    }

    ic[0] += 4.0;
    ic[1] += 4.0;
    ic[2] += 4.0;
    ic[3] += 4.0;
  }

  for (a_tmp_tmp = 0; a_tmp_tmp < 40; a_tmp_tmp++) {
    tmp[a_tmp_tmp] = std::isinf(runtimedata_OutputMin[a_tmp_tmp]);
  }

  all(tmp, x);
  y = true;
  i = 0;
  exitg1 = false;
  while ((!exitg1) && (i < 4)) {
    if (!x[i]) {
      y = false;
      exitg1 = true;
    } else {
      i++;
    }
  }

  if (y) {
    for (a_tmp_tmp = 0; a_tmp_tmp < 40; a_tmp_tmp++) {
      tmp[a_tmp_tmp] = std::isinf(runtimedata_OutputMax[a_tmp_tmp]);
    }

    all(tmp, x);
    i = 0;
    exitg1 = false;
    while ((!exitg1) && (i < 4)) {
      if (!x[i]) {
        y = false;
        exitg1 = true;
      } else {
        i++;
      }
    }
  }

  if (y) {
    varargout_2_tmp_tmp = 0;
    varargin_1_size_idx_1 = 0;
    b_varargin_1_size_idx_0 = 0;
    d_size_idx_0 = 0;
  } else {
    for (i = 0; i < 80; i++) {
      c[i] = 0.0;
      icf[i] = true;
    }

    std::memset(&rtDW.b_Jx[0], 0, 3200U * sizeof(real_T));
    std::memset(&Je[0], 0, 80U * sizeof(int8_T));
    ic[0] = 1.0;
    ic[1] = 2.0;
    ic[2] = 3.0;
    ic[3] = 4.0;
    for (i = 0; i < 10; i++) {
      U_0 = runtimedata_OutputMin[i];
      icf[static_cast<int32_T>(ic[0]) - 1] = ((!std::isinf(U_0)) && (!std::isnan
        (U_0)));
      U_0 = runtimedata_OutputMin[i + 10];
      icf[static_cast<int32_T>(ic[1]) - 1] = ((!std::isinf(U_0)) && (!std::isnan
        (U_0)));
      U_0 = runtimedata_OutputMin[i + 20];
      icf[static_cast<int32_T>(ic[2]) - 1] = ((!std::isinf(U_0)) && (!std::isnan
        (U_0)));
      U_0 = runtimedata_OutputMin[i + 30];
      icf[static_cast<int32_T>(ic[3]) - 1] = ((!std::isinf(U_0)) && (!std::isnan
        (U_0)));
      U_0 = runtimedata_OutputMax[i];
      icf[static_cast<int32_T>(ic[0] + 4.0) - 1] = ((!std::isinf(U_0)) && (!std::
        isnan(U_0)));
      ic_0[0] = static_cast<int32_T>(ic[0]) - 1;
      ic_0[4] = static_cast<int32_T>(ic[0] + 4.0) - 1;
      U_0 = runtimedata_OutputMax[i + 10];
      icf[static_cast<int32_T>(ic[1] + 4.0) - 1] = ((!std::isinf(U_0)) && (!std::
        isnan(U_0)));
      ic_0[1] = static_cast<int32_T>(ic[1]) - 1;
      ic_0[5] = static_cast<int32_T>(ic[1] + 4.0) - 1;
      U_0 = runtimedata_OutputMax[i + 20];
      icf[static_cast<int32_T>(ic[2] + 4.0) - 1] = ((!std::isinf(U_0)) && (!std::
        isnan(U_0)));
      ic_0[2] = static_cast<int32_T>(ic[2]) - 1;
      ic_0[6] = static_cast<int32_T>(ic[2] + 4.0) - 1;
      U_0 = runtimedata_OutputMax[i + 30];
      icf[static_cast<int32_T>(ic[3] + 4.0) - 1] = ((!std::isinf(U_0)) && (!std::
        isnan(U_0)));
      ic_0[3] = static_cast<int32_T>(ic[3]) - 1;
      ic_0[7] = static_cast<int32_T>(ic[3] + 4.0) - 1;
      for (a_tmp_tmp = 0; a_tmp_tmp < 8; a_tmp_tmp++) {
        icf_0[a_tmp_tmp] = icf[ic_0[a_tmp_tmp]];
      }

      if (any(icf_0)) {
        yk[0] = X_0[i + 1];
        yk[1] = X_0[i + 12];
        yk[2] = X_0[i + 23];
        yk[3] = X_0[i + 34];
        c[static_cast<int32_T>(ic[0]) - 1] = (runtimedata_OutputMin[i] - e) -
          yk[0];
        c[static_cast<int32_T>(ic[1]) - 1] = (runtimedata_OutputMin[i + 10] - e)
          - yk[1];
        c[static_cast<int32_T>(ic[2]) - 1] = (runtimedata_OutputMin[i + 20] - e)
          - yk[2];
        c[static_cast<int32_T>(ic[3]) - 1] = (runtimedata_OutputMin[i + 30] - e)
          - yk[3];
        for (a_tmp_tmp = 0; a_tmp_tmp < 4; a_tmp_tmp++) {
          c[static_cast<int32_T>(ic[a_tmp_tmp] + 4.0) - 1] = (yk[a_tmp_tmp] -
            runtimedata_OutputMax[10 * a_tmp_tmp + i]) - e;
          varargout_2_tmp = a_tmp_tmp << 2;
          rtDW.b_Jx[((static_cast<int32_T>(ic[0]) + 80 * a_tmp_tmp) + 320 * i) -
            1] = val[varargout_2_tmp];
          rtDW.b_Jx[((static_cast<int32_T>(ic[1]) + 80 * a_tmp_tmp) + 320 * i) -
            1] = val[varargout_2_tmp + 1];
          rtDW.b_Jx[((static_cast<int32_T>(ic[2]) + 80 * a_tmp_tmp) + 320 * i) -
            1] = val[varargout_2_tmp + 2];
          rtDW.b_Jx[((static_cast<int32_T>(ic[3]) + 80 * a_tmp_tmp) + 320 * i) -
            1] = val[varargout_2_tmp + 3];
        }

        for (a_tmp_tmp = 0; a_tmp_tmp < 4; a_tmp_tmp++) {
          rtDW.b_Jx[((static_cast<int32_T>(ic[0] + 4.0) + 80 * a_tmp_tmp) + 320 *
                     i) - 1] = j[a_tmp_tmp << 2];
          rtDW.b_Jx[((static_cast<int32_T>(ic[1] + 4.0) + 80 * a_tmp_tmp) + 320 *
                     i) - 1] = j[(a_tmp_tmp << 2) + 1];
          rtDW.b_Jx[((static_cast<int32_T>(ic[2] + 4.0) + 80 * a_tmp_tmp) + 320 *
                     i) - 1] = j[(a_tmp_tmp << 2) + 2];
          rtDW.b_Jx[((static_cast<int32_T>(ic[3] + 4.0) + 80 * a_tmp_tmp) + 320 *
                     i) - 1] = j[(a_tmp_tmp << 2) + 3];
          Je[static_cast<int32_T>(ic[a_tmp_tmp]) - 1] = -1;
        }

        Je[static_cast<int32_T>(ic[0] + 4.0) - 1] = -1;
        Je[static_cast<int32_T>(ic[1] + 4.0) - 1] = -1;
        Je[static_cast<int32_T>(ic[2] + 4.0) - 1] = -1;
        Je[static_cast<int32_T>(ic[3] + 4.0) - 1] = -1;
      }

      ic[0] += 8.0;
      ic[1] += 8.0;
      ic[2] += 8.0;
      ic[3] += 8.0;
    }

    i = 0;
    for (a_tmp_tmp = 0; a_tmp_tmp < 80; a_tmp_tmp++) {
      if (icf[a_tmp_tmp]) {
        i++;
      }
    }

    varargout_2_tmp_tmp = i;
    i = 0;
    for (a_tmp_tmp = 0; a_tmp_tmp < 80; a_tmp_tmp++) {
      if (icf[a_tmp_tmp]) {
        b_data[i] = static_cast<int8_T>(a_tmp_tmp + 1);
        i++;
      }
    }

    for (a_tmp_tmp = 0; a_tmp_tmp < varargout_2_tmp_tmp; a_tmp_tmp++) {
      c_data[a_tmp_tmp] = c[b_data[a_tmp_tmp] - 1];
    }

    varargin_1_size_idx_1 = 1;
    if (varargout_2_tmp_tmp - 1 >= 0) {
      std::memcpy(&c[0], &c_data[0], static_cast<uint32_T>(varargout_2_tmp_tmp) *
                  sizeof(real_T));
    }

    i = 0;
    for (a_tmp_tmp = 0; a_tmp_tmp < 80; a_tmp_tmp++) {
      if (icf[a_tmp_tmp]) {
        i++;
      }
    }

    d_size_idx_0 = i;
    i = 0;
    for (a_tmp_tmp = 0; a_tmp_tmp < 80; a_tmp_tmp++) {
      if (icf[a_tmp_tmp]) {
        d_data[i] = static_cast<int8_T>(a_tmp_tmp + 1);
        i++;
      }
    }

    if (d_size_idx_0 == 0) {
      b_varargin_1_size_idx_0 = 0;
      d_size_idx_0 = 0;
    } else {
      for (a_tmp_tmp = 0; a_tmp_tmp < 10; a_tmp_tmp++) {
        for (i = 0; i < 4; i++) {
          for (Ak1_tmp_tmp_tmp = 0; Ak1_tmp_tmp_tmp < d_size_idx_0;
               Ak1_tmp_tmp_tmp++) {
            rtDW.b_Jx_data[(Ak1_tmp_tmp_tmp + d_size_idx_0 * i) + (d_size_idx_0 <<
              2) * a_tmp_tmp] = rtDW.b_Jx[((80 * i + d_data[Ak1_tmp_tmp_tmp]) +
              320 * a_tmp_tmp) - 1];
          }
        }
      }

      d[0] = static_cast<int8_T>(d_size_idx_0);
      varargout_2_tmp = static_cast<int8_T>(d_size_idx_0);
      for (a_tmp_tmp = 0; a_tmp_tmp < varargout_2_tmp; a_tmp_tmp++) {
        for (i = 0; i < 40; i++) {
          rtDW.b_Jx[i + 40 * a_tmp_tmp] = rtDW.b_Jx_data[d[0] * i + a_tmp_tmp];
        }
      }

      tmp_size[0] = d_size_idx_0;
      tmp_size[1] = 10;
      for (a_tmp_tmp = 0; a_tmp_tmp < 10; a_tmp_tmp++) {
        for (i = 0; i < d_size_idx_0; i++) {
          rtDW.tmp_data[i + d_size_idx_0 * a_tmp_tmp] = 0.0;
        }
      }

      mtimes(rtDW.tmp_data, tmp_size, tmp_data, tmp_size_0);
      varargout_2_tmp = tmp_size_0[0];
      for (a_tmp_tmp = 0; a_tmp_tmp < varargout_2_tmp; a_tmp_tmp++) {
        for (i = 0; i < 5; i++) {
          varargin_2_data[i + 5 * a_tmp_tmp] = tmp_data[tmp_size_0[0] * i +
            a_tmp_tmp];
        }
      }

      d[0] = 40;
      if (tmp_size_0[0] != 0) {
        varargin_2[0] = 5;
      } else {
        varargin_2[0] = 0;
      }

      for (a_tmp_tmp = 0; a_tmp_tmp < d_size_idx_0; a_tmp_tmp++) {
        b_data[a_tmp_tmp] = Je[d_data[a_tmp_tmp] - 1];
      }

      tmp_1[0] = 1;
      b_varargin_1_size_idx_0 = varargin_2[0] + 41;
      varargout_2_tmp = static_cast<int8_T>(d_size_idx_0);
      d_size_idx_0 = static_cast<int8_T>(d_size_idx_0);
      for (a_tmp_tmp = 0; a_tmp_tmp < varargout_2_tmp; a_tmp_tmp++) {
        for (i = 0; i < 40; i++) {
          rtDW.b_varargin_1_data[i + b_varargin_1_size_idx_0 * a_tmp_tmp] =
            rtDW.b_Jx[d[0] * a_tmp_tmp + i];
        }
      }

      Ak1_tmp_tmp_tmp = varargin_2[0];
      for (a_tmp_tmp = 0; a_tmp_tmp < varargout_2_tmp; a_tmp_tmp++) {
        for (i = 0; i < Ak1_tmp_tmp_tmp; i++) {
          rtDW.b_varargin_1_data[(i + b_varargin_1_size_idx_0 * a_tmp_tmp) + 40]
            = varargin_2_data[varargin_2[0] * a_tmp_tmp + i];
        }
      }

      for (a_tmp_tmp = 0; a_tmp_tmp < varargout_2_tmp; a_tmp_tmp++) {
        rtDW.b_varargin_1_data[(varargin_2[0] + b_varargin_1_size_idx_0 *
          a_tmp_tmp) + 40] = b_data[tmp_1[0] * a_tmp_tmp];
      }
    }
  }

  b_sizes_idx_1 = static_cast<int8_T>((varargout_2_tmp_tmp != 0) &&
    (varargin_1_size_idx_1 != 0));
  if (b_sizes_idx_1 == 0) {
    d[0] = static_cast<int8_T>(varargout_2_tmp_tmp);
  } else if ((varargout_2_tmp_tmp != 0) && (varargin_1_size_idx_1 != 0)) {
    d[0] = static_cast<int8_T>(varargout_2_tmp_tmp);
  } else {
    d[0] = 0;
  }

  varargout_1_size[0] = d[0];
  varargout_1_size[1] = b_sizes_idx_1;
  varargout_2_tmp = b_sizes_idx_1;
  for (a_tmp_tmp = 0; a_tmp_tmp < varargout_2_tmp; a_tmp_tmp++) {
    Ak1_tmp_tmp_tmp = d[0];
    if (Ak1_tmp_tmp_tmp - 1 >= 0) {
      std::memcpy(&varargout_1_data[0], &c[0], static_cast<uint32_T>
                  (Ak1_tmp_tmp_tmp) * sizeof(real_T));
    }
  }

  if ((b_varargin_1_size_idx_0 != 0) && (d_size_idx_0 != 0)) {
    b_sizes_idx_1 = static_cast<int8_T>(b_varargin_1_size_idx_0);
  } else {
    b_sizes_idx_1 = 0;
  }

  varargout_3_size[0] = b_sizes_idx_1;
  if (b_sizes_idx_1 == 0) {
    varargout_3_size[1] = d_size_idx_0;
    tmp_2 = static_cast<int8_T>(d_size_idx_0);
  } else {
    if ((b_varargin_1_size_idx_0 != 0) && (d_size_idx_0 != 0)) {
      varargout_3_size[1] = d_size_idx_0;
    } else {
      varargout_3_size[1] = 0;
    }

    if ((b_varargin_1_size_idx_0 != 0) && (d_size_idx_0 != 0)) {
      tmp_2 = static_cast<int8_T>(d_size_idx_0);
    } else {
      tmp_2 = 0;
    }
  }

  varargout_2_tmp = b_sizes_idx_1 * tmp_2;
  if (varargout_2_tmp - 1 >= 0) {
    std::memcpy(&varargout_3_data[0], &rtDW.b_varargin_1_data[0],
                static_cast<uint32_T>(varargout_2_tmp) * sizeof(real_T));
  }

  for (a_tmp_tmp = 0; a_tmp_tmp < 5; a_tmp_tmp++) {
    for (i = 0; i < 40; i++) {
      varargout_2_tmp = 5 * i + a_tmp_tmp;
      Jmv_0[varargout_2_tmp] = 0.0;
      for (Ak1_tmp_tmp_tmp = 0; Ak1_tmp_tmp_tmp < 10; Ak1_tmp_tmp_tmp++) {
        Jmv_0[varargout_2_tmp] += Jmv[40 * Ak1_tmp_tmp_tmp + i] *
          static_cast<real_T>(b_b[10 * a_tmp_tmp + Ak1_tmp_tmp_tmp]);
      }
    }
  }

  for (a_tmp_tmp = 0; a_tmp_tmp < 40; a_tmp_tmp++) {
    for (i = 0; i < 40; i++) {
      varargout_4[i + 46 * a_tmp_tmp] = rtDW.Jx[40 * i + a_tmp_tmp];
    }

    for (i = 0; i < 5; i++) {
      varargout_4[(i + 46 * a_tmp_tmp) + 40] = Jmv_0[5 * a_tmp_tmp + i];
    }

    varargout_4[46 * a_tmp_tmp + 45] = 0.0;
  }
}

// Function for MATLAB Function: '<S2>/NLMPC'
void MPC_controller::factoryConstruct(int32_T nVarMax, int32_T mConstrMax,
  int32_T mIneq, int32_T mNonlinIneq, s_aAq9pdCdNustb4CQC7xpeC *obj)
{
  obj->nVarMax = nVarMax;
  obj->mNonlinIneq = mNonlinIneq;
  obj->mNonlinEq = 40;
  obj->mIneq = mIneq;
  obj->mEq = 40;
  obj->iNonIneq0 = (mIneq - mNonlinIneq) + 1;
  obj->iNonEq0 = 1;
  obj->sqpFval = 0.0;
  obj->sqpFval_old = 0.0;
  obj->cIneq.size = mIneq;
  obj->cIneq_old.size = mIneq;
  obj->grad.size = nVarMax;
  obj->grad_old.size = nVarMax;
  obj->FunctionEvaluations = 0;
  obj->sqpIterations = 0;
  obj->sqpExitFlag = 0;
  obj->lambdasqp.size = mConstrMax;
  if (mConstrMax - 1 >= 0) {
    std::memset(&obj->lambdasqp.data[0], 0, static_cast<uint32_T>(mConstrMax) *
                sizeof(real_T));
  }

  obj->lambdaStopTest.size = mConstrMax;
  obj->lambdaStopTestPrev.size = mConstrMax;
  obj->steplength = 1.0;
  obj->delta_x.size = nVarMax;
  if (nVarMax - 1 >= 0) {
    std::memset(&obj->delta_x.data[0], 0, static_cast<uint32_T>(nVarMax) *
                sizeof(real_T));
  }

  obj->socDirection.size = nVarMax;
  obj->workingset_old.size = mConstrMax;
  if (mNonlinIneq > 0) {
    obj->JacCineqTrans_old.size[0] = nVarMax;
    obj->JacCineqTrans_old.size[1] = mNonlinIneq;
  } else {
    obj->JacCineqTrans_old.size[0] = 0;
    obj->JacCineqTrans_old.size[1] = 0;
  }

  obj->JacCeqTrans_old.size[0] = nVarMax;
  obj->JacCeqTrans_old.size[1] = 40;
  obj->gradLag.size = nVarMax;
  obj->delta_gradLag.size = nVarMax;
  obj->xstar.size = nVarMax;
  obj->fstar = 0.0;
  obj->firstorderopt = 0.0;
  obj->lambda.size = mConstrMax;
  if (mConstrMax - 1 >= 0) {
    std::memset(&obj->lambda.data[0], 0, static_cast<uint32_T>(mConstrMax) *
                sizeof(real_T));
  }

  obj->state = 0;
  obj->maxConstr = 0.0;
  obj->iterations = 0;
  obj->searchDir.size = nVarMax;
}

// Function for MATLAB Function: '<S2>/NLMPC'
void MPC_controller::factoryConstruct_h53b(int32_T MaxVars, int32_T
  *obj_grad_size, int32_T *obj_Hx_size, boolean_T *obj_hasLinear, int32_T
  *obj_nvar, int32_T *obj_maxVar, real_T *obj_beta, real_T *obj_rho, int32_T
  *obj_objtype, int32_T *obj_prev_objtype, int32_T *obj_prev_nvar, boolean_T
  *obj_prev_hasLinear, real_T *obj_gammaScalar)
{
  *obj_grad_size = MaxVars;
  *obj_Hx_size = MaxVars - 1;
  *obj_hasLinear = false;
  *obj_nvar = 0;
  *obj_maxVar = MaxVars;
  *obj_beta = 0.0;
  *obj_rho = 0.0;
  *obj_objtype = 3;
  *obj_prev_objtype = 3;
  *obj_prev_nvar = 0;
  *obj_prev_hasLinear = false;
  *obj_gammaScalar = 0.0;
}

// Function for MATLAB Function: '<S2>/NLMPC'
void MPC_controller::factoryConstruct_h53bm(int32_T mIneqMax, int32_T nVarMax,
  int32_T mConstrMax, s_YG0fmBFfsyHj5FdUrtbgBC *obj)
{
  obj->mConstr = 0;
  obj->mConstrOrig = 0;
  obj->mConstrMax = mConstrMax;
  obj->nVar = 46;
  obj->nVarOrig = 46;
  obj->nVarMax = nVarMax;
  obj->ldA = nVarMax;
  obj->Aineq.size = mIneqMax * nVarMax;
  obj->bineq.size = mIneqMax;
  obj->Aeq.size = 40 * nVarMax;
  obj->lb.size = nVarMax;
  obj->ub.size = nVarMax;
  obj->indexLB.size = nVarMax;
  obj->indexUB.size = nVarMax;
  obj->indexFixed.size = nVarMax;
  obj->mEqRemoved = 0;
  obj->ATwset.size = nVarMax * mConstrMax;
  obj->bwset.size = mConstrMax;
  obj->nActiveConstr = 0;
  obj->maxConstrWorkspace.size = mConstrMax;
  for (int32_T i{0}; i < 5; i++) {
    obj->sizes[i] = 0;
    obj->sizesNormal[i] = 0;
    obj->sizesPhaseOne[i] = 0;
    obj->sizesRegularized[i] = 0;
    obj->sizesRegPhaseOne[i] = 0;
  }

  for (int32_T i{0}; i < 6; i++) {
    obj->isActiveIdx[i] = 0;
    obj->isActiveIdxNormal[i] = 0;
    obj->isActiveIdxPhaseOne[i] = 0;
    obj->isActiveIdxRegularized[i] = 0;
    obj->isActiveIdxRegPhaseOne[i] = 0;
  }

  obj->isActiveConstr.size = mConstrMax;
  obj->Wid.size = mConstrMax;
  obj->Wlocalidx.size = mConstrMax;
  for (int32_T i{0}; i < 5; i++) {
    obj->nWConstr[i] = 0;
  }

  obj->probType = 3;
  obj->SLACK0 = 1.0E-5;
}

// Function for MATLAB Function: '<S2>/NLMPC'
int32_T MPC_controller::checkVectorNonFinite(int32_T N, const real_T vec_data[],
  int32_T iv0)
{
  int32_T idx_current;
  int32_T idx_end;
  int32_T status;
  boolean_T allFinite;
  status = 1;
  allFinite = true;
  idx_current = iv0 - 2;
  idx_end = (iv0 + N) - 1;
  while (allFinite && (idx_current + 2 <= idx_end)) {
    real_T allFinite_tmp;
    allFinite_tmp = vec_data[idx_current + 1];
    allFinite = ((!std::isinf(allFinite_tmp)) && (!std::isnan(allFinite_tmp)));
    idx_current++;
  }

  if (!allFinite) {
    if (std::isnan(vec_data[idx_current])) {
      status = -3;
    } else if (vec_data[idx_current] < 0.0) {
      status = -1;
    } else {
      status = -2;
    }
  }

  return status;
}

// Function for MATLAB Function: '<S2>/NLMPC'
int32_T MPC_controller::checkVectorNonFinite_n(const real_T vec[40])
{
  int32_T idx_current;
  int32_T status;
  boolean_T allFinite;
  status = 1;
  allFinite = true;
  idx_current = -1;
  while (allFinite && (idx_current + 2 <= 40)) {
    real_T allFinite_tmp;
    allFinite_tmp = vec[idx_current + 1];
    allFinite = ((!std::isinf(allFinite_tmp)) && (!std::isnan(allFinite_tmp)));
    idx_current++;
  }

  if (!allFinite) {
    if (std::isnan(vec[idx_current])) {
      status = -3;
    } else if (vec[idx_current] < 0.0) {
      status = -1;
    } else {
      status = -2;
    }
  }

  return status;
}

// Function for MATLAB Function: '<S2>/NLMPC'
void MPC_controller::evalObjAndConstrAndDerivatives(int32_T
  obj_next_next_next_next_next_va, const s_GSKgPzH92oA7AAcXEvWMnG
  *obj_next_next_next_next_next_ne, const s_OOgWGXXQYnSElkPXvuQxeH
  *obj_next_next_next_next_next__0, const real_T x[46], real_T
  grad_workspace_data[], real_T Cineq_workspace_data[], int32_T ineq0, real_T
  Ceq_workspace[40], real_T JacIneqTrans_workspace_data[], int32_T iJI_col,
  int32_T ldJI, real_T JacEqTrans_workspace_data[], int32_T ldJE, real_T *fval,
  int32_T *status)
{
  static const int8_T f_0[50]{ 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,
    0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0,
    0, 1, 0, 0, 0, 0, 1 };

  static const int8_T g[16]{ 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };

  real_T a__3_data[80];
  real_T b_x[46];
  real_T X_2[44];
  real_T b_X[44];
  real_T gfX[40];
  real_T U[11];
  real_T gfU[10];
  real_T f[5];
  real_T gfX_0[4];
  real_T ix[4];
  real_T e;
  real_T fs;
  int32_T a__3_size[2];
  int32_T a__4_size[2];
  int32_T i;
  int32_T iu;
  znlmpc_getXUe(x, obj_next_next_next_next_next__0->runtimedata.x, X_2, U, &e);
  std::memset(&gfX[0], 0, 40U * sizeof(real_T));
  std::memset(&gfU[0], 0, 10U * sizeof(real_T));
  fs = 0.0;
  ix[0] = 1.0;
  ix[1] = 2.0;
  ix[2] = 3.0;
  ix[3] = 4.0;
  for (iu = 0; iu < 11; iu++) {
    i = iu << 2;
    b_X[i] = X_2[iu];
    b_X[i + 1] = X_2[iu + 11];
    b_X[i + 2] = X_2[iu + 22];
    b_X[i + 3] = X_2[iu + 33];
  }

  for (i = 0; i < 10; i++) {
    real_T duk;
    real_T obj_next_next_next_next_next__1;
    real_T obj_next_next_next_next_next__2;
    real_T obj_next_next_next_next_next__3;
    real_T wtUerr;
    real_T wtYerr_tmp;
    iu = (i + 1) << 2;
    duk = (b_X[iu] - obj_next_next_next_next_next__0->runtimedata.ref[i]) *
      obj_next_next_next_next_next__0->runtimedata.OutputWeights[i];
    wtUerr = duk * duk;
    obj_next_next_next_next_next__1 =
      obj_next_next_next_next_next__0->runtimedata.OutputWeights[i] * duk;
    wtYerr_tmp = obj_next_next_next_next_next__0->runtimedata.OutputWeights[i +
      10];
    duk = (b_X[iu + 1] - obj_next_next_next_next_next__0->runtimedata.ref[i + 10])
      * wtYerr_tmp;
    wtUerr += duk * duk;
    obj_next_next_next_next_next__2 = wtYerr_tmp * duk;
    wtYerr_tmp = obj_next_next_next_next_next__0->runtimedata.OutputWeights[i +
      20];
    duk = (b_X[iu + 2] - obj_next_next_next_next_next__0->runtimedata.ref[i + 20])
      * wtYerr_tmp;
    wtUerr += duk * duk;
    obj_next_next_next_next_next__3 = wtYerr_tmp * duk;
    wtYerr_tmp = obj_next_next_next_next_next__0->runtimedata.OutputWeights[i +
      30];
    duk = (b_X[iu + 3] - obj_next_next_next_next_next__0->runtimedata.ref[i + 30])
      * wtYerr_tmp;
    wtYerr_tmp *= duk;
    fs += duk * duk + wtUerr;
    for (iu = 0; iu < 4; iu++) {
      gfX_0[iu] = (((static_cast<real_T>(g[iu + 4]) *
                     obj_next_next_next_next_next__2 + static_cast<real_T>(g[iu])
                     * obj_next_next_next_next_next__1) + static_cast<real_T>
                    (g[iu + 8]) * obj_next_next_next_next_next__3) +
                   static_cast<real_T>(g[iu + 12]) * wtYerr_tmp) + gfX[
        static_cast<int32_T>(ix[iu]) - 1];
    }

    gfX[static_cast<int32_T>(ix[0]) - 1] = gfX_0[0];
    ix[0] += 4.0;
    gfX[static_cast<int32_T>(ix[1]) - 1] = gfX_0[1];
    ix[1] += 4.0;
    gfX[static_cast<int32_T>(ix[2]) - 1] = gfX_0[2];
    ix[2] += 4.0;
    gfX[static_cast<int32_T>(ix[3]) - 1] = gfX_0[3];
    ix[3] += 4.0;
    if (i + 1 == 1) {
      duk = U[i] - obj_next_next_next_next_next__0->runtimedata.lastMV;
    } else {
      duk = U[i] - U[i - 1];
    }

    wtUerr = 0.0 * U[i];
    gfU[i] += 0.0 * wtUerr;
    duk *= 0.1;
    fs = (wtUerr * wtUerr + fs) + duk * duk;
    wtUerr = 0.1 * duk;
    gfU[i] += wtUerr;
    if (i + 1 > 1) {
      gfU[i - 1] -= wtUerr;
    }
  }

  *fval = 100000.0 * e * e + fs;
  for (iu = 0; iu < 5; iu++) {
    fs = 0.0;
    for (i = 0; i < 10; i++) {
      fs += static_cast<real_T>(f_0[5 * i + iu]) * (2.0 * gfU[i]);
    }

    f[iu] = fs;
  }

  for (iu = 0; iu < 40; iu++) {
    b_x[iu] = 2.0 * gfX[iu];
  }

  for (iu = 0; iu < 5; iu++) {
    b_x[iu + 40] = f[iu];
  }

  b_x[45] = 200000.0 * e;
  std::memcpy(&grad_workspace_data[0], &b_x[0], 46U * sizeof(real_T));
  if (std::isinf(*fval) || std::isnan(*fval)) {
    if (std::isnan(*fval)) {
      *status = -3;
    } else if (*fval < 0.0) {
      *status = -1;
    } else {
      *status = -2;
    }
  } else {
    boolean_T allFinite;
    allFinite = true;
    i = -1;
    while (allFinite && (i + 2 <= 46)) {
      e = grad_workspace_data[i + 1];
      allFinite = ((!std::isinf(e)) && (!std::isnan(e)));
      i++;
    }

    if (!allFinite) {
      if (std::isnan(grad_workspace_data[i])) {
        *status = -3;
      } else if (grad_workspace_data[i] < 0.0) {
        *status = -1;
      } else {
        *status = -2;
      }
    } else {
      int32_T col_end;
      int32_T idx_mat;
      if (obj_next_next_next_next_next_va > 0) {
        eML_blk_kernel_anonFcn2(obj_next_next_next_next_next_ne->x,
          obj_next_next_next_next_next_ne->OutputMin,
          obj_next_next_next_next_next_ne->OutputMax, x, a__3_data, a__3_size,
          gfX, rtDW.a__4_data, a__4_size, rtDW.JacEqTrans_tmp);
        iu = static_cast<uint8_T>(obj_next_next_next_next_next_va);
        for (i = 0; i < iu; i++) {
          Cineq_workspace_data[(ineq0 + i) - 1] = a__3_data[i];
        }

        std::memcpy(&Ceq_workspace[0], &gfX[0], 40U * sizeof(real_T));
        col_end = a__4_size[0];
        for (i = 0; i < col_end; i++) {
          idx_mat = a__4_size[1];
          for (iu = 0; iu < idx_mat; iu++) {
            JacIneqTrans_workspace_data[i + ldJI * ((iJI_col + iu) - 1)] =
              rtDW.a__4_data[a__4_size[0] * iu + i];
          }
        }

        for (i = 0; i < 46; i++) {
          for (iu = 0; iu < 40; iu++) {
            JacEqTrans_workspace_data[i + ldJE * iu] = rtDW.JacEqTrans_tmp[46 *
              iu + i];
          }
        }
      } else {
        eML_blk_kernel_anonFcn2(obj_next_next_next_next_next_ne->x,
          obj_next_next_next_next_next_ne->OutputMin,
          obj_next_next_next_next_next_ne->OutputMax, x, a__3_data, a__3_size,
          gfX, rtDW.a__4_data, a__4_size, rtDW.JacEqTrans_tmp);
        std::memcpy(&Ceq_workspace[0], &gfX[0], 40U * sizeof(real_T));
        for (i = 0; i < 46; i++) {
          for (iu = 0; iu < 40; iu++) {
            JacEqTrans_workspace_data[i + ldJE * iu] = rtDW.JacEqTrans_tmp[46 *
              iu + i];
          }
        }
      }

      *status = checkVectorNonFinite(obj_next_next_next_next_next_va,
        Cineq_workspace_data, ineq0);
      if (*status == 1) {
        *status = checkVectorNonFinite_n(Ceq_workspace);
        if (*status == 1) {
          allFinite = true;
          i = -1;
          iu = iJI_col;
          col_end = (iJI_col + obj_next_next_next_next_next_va) - 1;
          while (allFinite && (iu <= col_end)) {
            i = -1;
            while (allFinite && (i + 2 <= 46)) {
              idx_mat = ((iu - 1) * ldJI + i) + 1;
              allFinite = ((!std::isinf(JacIneqTrans_workspace_data[idx_mat])) &&
                           (!std::isnan(JacIneqTrans_workspace_data[idx_mat])));
              i++;
            }

            iu++;
          }

          if (!allFinite) {
            idx_mat = (iu - 2) * ldJI + i;
            if (std::isnan(JacIneqTrans_workspace_data[idx_mat])) {
              *status = -3;
            } else if (JacIneqTrans_workspace_data[idx_mat] < 0.0) {
              *status = -1;
            } else {
              *status = -2;
            }
          } else {
            i = -1;
            iu = -1;
            while (allFinite && (iu + 2 <= 40)) {
              i = -1;
              while (allFinite && (i + 2 <= 46)) {
                col_end = ((iu + 1) * ldJE + i) + 1;
                allFinite = ((!std::isinf(JacEqTrans_workspace_data[col_end])) &&
                             (!std::isnan(JacEqTrans_workspace_data[col_end])));
                i++;
              }

              iu++;
            }

            if (!allFinite) {
              col_end = ldJE * iu + i;
              if (std::isnan(JacEqTrans_workspace_data[col_end])) {
                *status = -3;
              } else if (JacEqTrans_workspace_data[col_end] < 0.0) {
                *status = -1;
              } else {
                *status = -2;
              }
            }
          }
        }
      }
    }
  }
}

// Function for MATLAB Function: '<S2>/NLMPC'
void MPC_controller::modifyOverheadPhaseOne_(s_YG0fmBFfsyHj5FdUrtbgBC *obj)
{
  int32_T d;
  int32_T idxEq;
  idxEq = static_cast<uint8_T>(obj->sizes[0]);
  for (int32_T idx{0}; idx < idxEq; idx++) {
    obj->ATwset.data[(obj->nVar + obj->ldA * idx) - 1] = 0.0;
  }

  for (int32_T idx{0}; idx < 40; idx++) {
    idxEq = (obj->ldA * idx + obj->nVar) - 1;
    obj->Aeq.data[idxEq] = 0.0;
    obj->ATwset.data[idxEq + obj->ldA * (obj->isActiveIdx[1] - 1)] = 0.0;
  }

  idxEq = static_cast<uint8_T>(obj->sizes[2]);
  for (int32_T idx{0}; idx < idxEq; idx++) {
    obj->Aineq.data[(obj->nVar + obj->ldA * idx) - 1] = -1.0;
  }

  obj->indexLB.data[obj->sizes[3] - 1] = obj->nVar;
  obj->lb.data[obj->nVar - 1] = 1.0E-5;
  idxEq = obj->isActiveIdx[2];
  d = obj->nActiveConstr;
  for (int32_T idx{idxEq}; idx <= d; idx++) {
    obj->ATwset.data[(obj->nVar + obj->ldA * (idx - 1)) - 1] = -1.0;
  }

  if (obj->nWConstr[4] > 0) {
    idxEq = static_cast<uint8_T>(obj->sizesNormal[4] + 1);
    for (int32_T idx{0}; idx < idxEq; idx++) {
      obj->isActiveConstr.data[(obj->isActiveIdx[4] + idx) - 1] = false;
    }
  }

  obj->isActiveConstr.data[obj->isActiveIdx[4] - 2] = false;
}

// Function for MATLAB Function: '<S2>/NLMPC'
void MPC_controller::setProblemType(s_YG0fmBFfsyHj5FdUrtbgBC *obj, int32_T
  PROBLEM_TYPE)
{
  switch (PROBLEM_TYPE) {
   case 3:
    {
      obj->nVar = 46;
      obj->mConstr = obj->mConstrOrig;
      if (obj->nWConstr[4] > 0) {
        int32_T mIneq;
        mIneq = static_cast<uint8_T>(obj->sizesNormal[4]);
        for (int32_T colOffsetATw{0}; colOffsetATw < mIneq; colOffsetATw++) {
          obj->isActiveConstr.data[(obj->isActiveIdxNormal[4] + colOffsetATw) -
            1] = obj->isActiveConstr.data[(obj->isActiveIdx[4] + colOffsetATw) -
            1];
        }
      }

      for (int32_T c{0}; c < 5; c++) {
        obj->sizes[c] = obj->sizesNormal[c];
      }

      for (int32_T c{0}; c < 6; c++) {
        obj->isActiveIdx[c] = obj->isActiveIdxNormal[c];
      }
    }
    break;

   case 1:
    obj->nVar = 47;
    obj->mConstr = obj->mConstrOrig + 1;
    for (int32_T c{0}; c < 5; c++) {
      obj->sizes[c] = obj->sizesPhaseOne[c];
    }

    for (int32_T c{0}; c < 6; c++) {
      obj->isActiveIdx[c] = obj->isActiveIdxPhaseOne[c];
    }

    modifyOverheadPhaseOne_(obj);
    break;

   case 2:
    {
      int32_T c;
      obj->nVar = obj->nVarMax - 1;
      obj->mConstr = obj->mConstrMax - 1;
      for (c = 0; c < 5; c++) {
        obj->sizes[c] = obj->sizesRegularized[c];
      }

      if (obj->probType != 4) {
        int32_T colOffsetATw;
        int32_T colOffsetAineq;
        int32_T idx_col;
        int32_T mIneq;
        int32_T offsetEq1;
        int32_T offsetEq2;
        mIneq = obj->sizes[2] + 86;
        offsetEq1 = obj->sizes[2] + 46;
        c = static_cast<uint8_T>(obj->sizes[0]);
        for (idx_col = 0; idx_col < c; idx_col++) {
          colOffsetATw = obj->ldA * idx_col;
          std::memset(&obj->ATwset.data[colOffsetATw + 46], 0,
                      static_cast<uint32_T>(((obj->nVar + colOffsetATw) -
            colOffsetATw) - 46) * sizeof(real_T));
        }

        idx_col = static_cast<uint8_T>(obj->sizes[2]);
        for (colOffsetATw = 0; colOffsetATw < idx_col; colOffsetATw++) {
          colOffsetAineq = obj->ldA * colOffsetATw - 1;
          for (c = 47; c <= colOffsetATw + 46; c++) {
            obj->Aineq.data[c + colOffsetAineq] = 0.0;
          }

          obj->Aineq.data[(colOffsetATw + colOffsetAineq) + 47] = -1.0;
          offsetEq2 = obj->nVar;
          for (c = colOffsetATw + 48; c <= offsetEq2; c++) {
            obj->Aineq.data[c + colOffsetAineq] = 0.0;
          }
        }

        for (idx_col = 0; idx_col < 40; idx_col++) {
          colOffsetAineq = obj->ldA * idx_col - 1;
          colOffsetATw = (obj->isActiveIdx[1] - 1) * obj->ldA + colOffsetAineq;
          if (offsetEq1 >= 47) {
            std::memset(&obj->Aeq.data[colOffsetAineq + 47], 0,
                        static_cast<uint32_T>(((offsetEq1 + colOffsetAineq) -
              colOffsetAineq) - 46) * sizeof(real_T));
          }

          if (offsetEq1 >= 47) {
            std::memset(&obj->ATwset.data[colOffsetATw + 47], 0,
                        static_cast<uint32_T>(((offsetEq1 + colOffsetATw) -
              colOffsetATw) - 46) * sizeof(real_T));
          }

          offsetEq2 = (mIneq + idx_col) - 40;
          if (mIneq - 39 <= offsetEq2) {
            std::memset(&obj->Aeq.data[(mIneq + colOffsetAineq) + -39], 0,
                        static_cast<uint32_T>((((offsetEq2 + colOffsetAineq) -
              mIneq) - colOffsetAineq) + 40) * sizeof(real_T));
          }

          if (mIneq - 39 <= offsetEq2) {
            std::memset(&obj->ATwset.data[(mIneq + colOffsetATw) + -39], 0,
                        static_cast<uint32_T>((((offsetEq2 + colOffsetATw) -
              mIneq) - colOffsetATw) + 40) * sizeof(real_T));
          }

          c = mIneq + idx_col;
          obj->Aeq.data[(c + colOffsetAineq) - 39] = -1.0;
          obj->ATwset.data[(c + colOffsetATw) - 39] = -1.0;
          if (c - 38 <= mIneq) {
            std::memset(&obj->Aeq.data[(c - 38) + colOffsetAineq], 0,
                        static_cast<uint32_T>((((mIneq + colOffsetAineq) - (c -
              38)) - colOffsetAineq) + 1) * sizeof(real_T));
          }

          if (c - 38 <= mIneq) {
            std::memset(&obj->ATwset.data[(c - 38) + colOffsetATw], 0,
                        static_cast<uint32_T>((((mIneq + colOffsetATw) - (c - 38))
              - colOffsetATw) + 1) * sizeof(real_T));
          }

          offsetEq2 = mIneq + idx_col;
          if (mIneq + 1 <= offsetEq2) {
            std::memset(&obj->Aeq.data[(mIneq + colOffsetAineq) + 1], 0,
                        static_cast<uint32_T>(((offsetEq2 + colOffsetAineq) -
              mIneq) - colOffsetAineq) * sizeof(real_T));
          }

          if (mIneq + 1 <= offsetEq2) {
            std::memset(&obj->ATwset.data[(mIneq + colOffsetATw) + 1], 0,
                        static_cast<uint32_T>(((offsetEq2 + colOffsetATw) -
              mIneq) - colOffsetATw) * sizeof(real_T));
          }

          obj->Aeq.data[(offsetEq2 + colOffsetAineq) + 1] = 1.0;
          obj->ATwset.data[(offsetEq2 + colOffsetATw) + 1] = 1.0;
          offsetEq2 += 2;
          if (offsetEq2 <= obj->nVar) {
            std::memset(&obj->Aeq.data[offsetEq2 + colOffsetAineq], 0,
                        static_cast<uint32_T>((((obj->nVar + colOffsetAineq) -
              offsetEq2) - colOffsetAineq) + 1) * sizeof(real_T));
          }

          if (offsetEq2 <= obj->nVar) {
            std::memset(&obj->ATwset.data[offsetEq2 + colOffsetATw], 0,
                        static_cast<uint32_T>((((obj->nVar + colOffsetATw) -
              offsetEq2) - colOffsetATw) + 1) * sizeof(real_T));
          }
        }

        mIneq = 46;
        offsetEq1 = obj->sizesNormal[3] + 1;
        offsetEq2 = obj->sizesRegularized[3];
        for (colOffsetATw = offsetEq1; colOffsetATw <= offsetEq2; colOffsetATw++)
        {
          mIneq++;
          obj->indexLB.data[colOffsetATw - 1] = mIneq;
        }

        if (obj->nWConstr[4] > 0) {
          mIneq = static_cast<uint8_T>(obj->sizesRegularized[4]);
          for (colOffsetATw = 0; colOffsetATw < mIneq; colOffsetATw++) {
            obj->isActiveConstr.data[obj->isActiveIdxRegularized[4] +
              colOffsetATw] = obj->isActiveConstr.data[(obj->isActiveIdx[4] +
              colOffsetATw) - 1];
          }
        }

        mIneq = obj->isActiveIdx[4];
        offsetEq1 = obj->isActiveIdxRegularized[4] - 1;
        if (mIneq <= offsetEq1) {
          std::memset(&obj->isActiveConstr.data[mIneq + -1], 0,
                      static_cast<uint32_T>((offsetEq1 - mIneq) + 1) * sizeof
                      (boolean_T));
        }

        mIneq = obj->sizes[2] + 126;
        std::memset(&obj->lb.data[46], 0, static_cast<uint32_T>(mIneq - 46) *
                    sizeof(real_T));
        offsetEq1 = obj->isActiveIdx[2];
        offsetEq2 = obj->nActiveConstr;
        for (mIneq = offsetEq1; mIneq <= offsetEq2; mIneq++) {
          colOffsetATw = (mIneq - 1) * obj->ldA - 1;
          if (obj->Wid.data[mIneq - 1] == 3) {
            colOffsetAineq = obj->Wlocalidx.data[mIneq - 1] + 45;
            if (colOffsetAineq >= 47) {
              std::memset(&obj->ATwset.data[colOffsetATw + 47], 0,
                          static_cast<uint32_T>(((colOffsetAineq + colOffsetATw)
                - colOffsetATw) - 46) * sizeof(real_T));
            }

            obj->ATwset.data[(obj->Wlocalidx.data[mIneq - 1] + colOffsetATw) +
              46] = -1.0;
            colOffsetAineq = obj->Wlocalidx.data[mIneq - 1] + 47;
            if (colOffsetAineq <= obj->nVar) {
              std::memset(&obj->ATwset.data[colOffsetAineq + colOffsetATw], 0,
                          static_cast<uint32_T>((((obj->nVar + colOffsetATw) -
                colOffsetAineq) - colOffsetATw) + 1) * sizeof(real_T));
            }
          } else {
            std::memset(&obj->ATwset.data[colOffsetATw + 47], 0,
                        static_cast<uint32_T>(((obj->nVar + colOffsetATw) -
              colOffsetATw) - 46) * sizeof(real_T));
          }
        }
      }

      for (c = 0; c < 6; c++) {
        obj->isActiveIdx[c] = obj->isActiveIdxRegularized[c];
      }
    }
    break;

   default:
    obj->nVar = obj->nVarMax;
    obj->mConstr = obj->mConstrMax;
    for (int32_T c{0}; c < 5; c++) {
      obj->sizes[c] = obj->sizesRegPhaseOne[c];
    }

    for (int32_T c{0}; c < 6; c++) {
      obj->isActiveIdx[c] = obj->isActiveIdxRegPhaseOne[c];
    }

    modifyOverheadPhaseOne_(obj);
    break;
  }

  obj->probType = PROBLEM_TYPE;
}

// Function for MATLAB Function: '<S2>/NLMPC'
void MPC_controller::initActiveSet(s_YG0fmBFfsyHj5FdUrtbgBC *obj)
{
  int32_T colOffsetATw;
  int32_T iATw0;
  int32_T idxFillStart;
  setProblemType(obj, 3);
  idxFillStart = obj->isActiveIdx[2];
  if (idxFillStart <= obj->mConstrMax) {
    std::memset(&obj->isActiveConstr.data[idxFillStart + -1], 0,
                static_cast<uint32_T>((obj->mConstrMax - idxFillStart) + 1) *
                sizeof(boolean_T));
  }

  obj->nWConstr[0] = obj->sizes[0];
  obj->nWConstr[1] = 40;
  obj->nWConstr[2] = 0;
  obj->nWConstr[3] = 0;
  obj->nWConstr[4] = 0;
  obj->nActiveConstr = obj->nWConstr[0] + 40;
  idxFillStart = static_cast<uint8_T>(obj->sizes[0]);
  for (int32_T idx{0}; idx < idxFillStart; idx++) {
    obj->Wid.data[idx] = 1;
    obj->Wlocalidx.data[idx] = idx + 1;
    obj->isActiveConstr.data[idx] = true;
    colOffsetATw = obj->ldA * idx;
    iATw0 = static_cast<uint8_T>(obj->indexFixed.data[idx] - 1);
    if (iATw0 - 1 >= 0) {
      std::memset(&obj->ATwset.data[colOffsetATw], 0, static_cast<uint32_T>
                  ((iATw0 + colOffsetATw) - colOffsetATw) * sizeof(real_T));
    }

    obj->ATwset.data[(obj->indexFixed.data[idx] + colOffsetATw) - 1] = 1.0;
    iATw0 = obj->indexFixed.data[idx] + 1;
    if (iATw0 <= obj->nVar) {
      std::memset(&obj->ATwset.data[(iATw0 + colOffsetATw) + -1], 0,
                  static_cast<uint32_T>((((obj->nVar + colOffsetATw) - iATw0) -
        colOffsetATw) + 1) * sizeof(real_T));
    }

    obj->bwset.data[idx] = obj->ub.data[obj->indexFixed.data[idx] - 1];
  }

  for (int32_T idx{0}; idx < 40; idx++) {
    int32_T f;
    int32_T iAeq0;
    colOffsetATw = obj->sizes[0] + idx;
    obj->Wid.data[colOffsetATw] = 2;
    obj->Wlocalidx.data[colOffsetATw] = idx + 1;
    obj->isActiveConstr.data[colOffsetATw] = true;
    iAeq0 = obj->ldA * idx;
    iATw0 = obj->ldA * colOffsetATw;
    f = obj->nVar - 1;
    for (idxFillStart = 0; idxFillStart <= f; idxFillStart++) {
      obj->ATwset.data[iATw0 + idxFillStart] = obj->Aeq.data[iAeq0 +
        idxFillStart];
    }

    obj->bwset.data[colOffsetATw] = obj->beq[idx];
  }
}

// Function for MATLAB Function: '<S2>/NLMPC'
void MPC_controller::factoryConstruct_h5(int32_T maxRows, int32_T maxCols,
  int32_T *obj_ldq, int32_T obj_QR_size[2], real_T obj_Q_data[], int32_T
  obj_Q_size[2], int32_T obj_jpvt_data[], int32_T *obj_jpvt_size, int32_T
  *obj_mrows, int32_T *obj_ncols, int32_T *obj_tau_size, int32_T *obj_minRowCol,
  boolean_T *obj_usedPivoting)
{
  int32_T loop_ub;
  *obj_ldq = maxRows;
  obj_QR_size[0] = maxRows;
  obj_QR_size[1] = maxCols;
  obj_Q_size[0] = maxRows;
  obj_Q_size[1] = maxRows;
  loop_ub = maxRows * maxRows;
  if (loop_ub - 1 >= 0) {
    std::memset(&obj_Q_data[0], 0, static_cast<uint32_T>(loop_ub) * sizeof
                (real_T));
  }

  *obj_jpvt_size = maxCols;
  if (maxCols - 1 >= 0) {
    std::memset(&obj_jpvt_data[0], 0, static_cast<uint32_T>(maxCols) * sizeof
                (int32_T));
  }

  *obj_mrows = 0;
  *obj_ncols = 0;
  if (maxRows <= maxCols) {
    *obj_tau_size = maxRows;
  } else {
    *obj_tau_size = maxCols;
  }

  *obj_minRowCol = 0;
  *obj_usedPivoting = false;
}

// Function for MATLAB Function: '<S2>/NLMPC'
void MPC_controller::factoryConstruct_h53(int32_T MaxDims, int32_T
  obj_FMat_size[2], int32_T *obj_ldm, int32_T *obj_ndims, int32_T *obj_info,
  real_T *obj_scaleFactor, boolean_T *obj_ConvexCheck, real_T *obj_regTol_,
  real_T *obj_workspace_, real_T *obj_workspace2_)
{
  obj_FMat_size[0] = MaxDims;
  obj_FMat_size[1] = MaxDims;
  *obj_ldm = MaxDims;
  *obj_ndims = 0;
  *obj_info = 0;
  *obj_scaleFactor = 0.0;
  *obj_ConvexCheck = true;
  *obj_regTol_ = (rtInf);
  *obj_workspace_ = (rtInf);
  *obj_workspace2_ = (rtInf);
}

// Function for MATLAB Function: '<S2>/NLMPC'
void MPC_controller::computeGradLag(real_T workspace_data[], int32_T ldA,
  int32_T nVar, const real_T grad_data[], int32_T mIneq, const real_T
  AineqTrans_data[], const real_T AeqTrans_data[], const int32_T
  finiteFixed_data[], int32_T mFixed, const int32_T finiteLB_data[], int32_T mLB,
  const int32_T finiteUB_data[], int32_T mUB, const real_T lambda_data[])
{
  int32_T b;
  int32_T f;
  int32_T g;
  int32_T iL0;
  int32_T ix;
  int32_T tmp;
  std::memcpy(&workspace_data[0], &grad_data[0], static_cast<uint8_T>(nVar) *
              sizeof(real_T));
  b = static_cast<uint8_T>(mFixed);
  for (iL0 = 0; iL0 < b; iL0++) {
    ix = finiteFixed_data[iL0];
    workspace_data[ix - 1] += lambda_data[iL0];
  }

  ix = mFixed;
  f = ldA * 39 + 1;
  for (iL0 = 1; ldA < 0 ? iL0 >= f : iL0 <= f; iL0 += ldA) {
    g = iL0 + nVar;
    for (b = iL0; b < g; b++) {
      tmp = b - iL0;
      workspace_data[tmp] += AeqTrans_data[b - 1] * lambda_data[ix];
    }

    ix++;
  }

  if (mIneq != 0) {
    ix = mFixed + 40;
    f = (mIneq - 1) * ldA + 1;
    for (iL0 = 1; ldA < 0 ? iL0 >= f : iL0 <= f; iL0 += ldA) {
      g = iL0 + nVar;
      for (b = iL0; b < g; b++) {
        tmp = b - iL0;
        workspace_data[tmp] += AineqTrans_data[b - 1] * lambda_data[ix];
      }

      ix++;
    }
  }

  iL0 = (mFixed + mIneq) + 40;
  ix = static_cast<uint16_T>(mLB);
  for (b = 0; b < ix; b++) {
    f = finiteLB_data[b];
    workspace_data[f - 1] -= lambda_data[iL0 + b];
  }

  iL0 += static_cast<uint16_T>(mLB);
  ix = static_cast<uint8_T>(mUB);
  for (b = 0; b < ix; b++) {
    f = finiteUB_data[b];
    workspace_data[f - 1] += lambda_data[iL0 + b];
  }
}

// Function for MATLAB Function: '<S2>/NLMPC'
real_T MPC_controller::computePrimalFeasError(const real_T x[46], int32_T
  mLinIneq, int32_T mNonlinIneq, const real_T cIneq_data[], const real_T cEq[40],
  const int32_T finiteLB_data[], int32_T mLB, const real_T lb[46], const int32_T
  finiteUB_data[], int32_T mUB)
{
  real_T feasError;
  int32_T mIneq;
  feasError = 0.0;
  mIneq = mNonlinIneq + mLinIneq;
  for (int32_T idx{0}; idx < 40; idx++) {
    feasError = std::fmax(feasError, std::abs(cEq[idx]));
  }

  for (int32_T idx{0}; idx < mIneq; idx++) {
    feasError = std::fmax(feasError, cIneq_data[idx]);
  }

  mIneq = static_cast<uint16_T>(mLB);
  for (int32_T idx{0}; idx < mIneq; idx++) {
    int32_T finiteLB;
    finiteLB = finiteLB_data[idx];
    feasError = std::fmax(feasError, lb[finiteLB - 1] - x[finiteLB - 1]);
  }

  mIneq = static_cast<uint8_T>(mUB);
  for (int32_T idx{0}; idx < mIneq; idx++) {
    feasError = std::fmax(feasError, x[finiteUB_data[idx] - 1] - (rtInf));
  }

  return feasError;
}

// Function for MATLAB Function: '<S2>/NLMPC'
void MPC_controller::computeDualFeasError(int32_T nVar, const real_T
  gradLag_data[], boolean_T *gradOK, real_T *val)
{
  int32_T idx;
  boolean_T exitg1;
  *gradOK = true;
  *val = 0.0;
  idx = 0;
  exitg1 = false;
  while ((!exitg1) && (idx <= static_cast<uint8_T>(nVar) - 1)) {
    *gradOK = ((!std::isinf(gradLag_data[idx])) && (!std::isnan(gradLag_data[idx])));
    if (!*gradOK) {
      exitg1 = true;
    } else {
      *val = std::fmax(*val, std::abs(gradLag_data[idx]));
      idx++;
    }
  }
}

// Function for MATLAB Function: '<S2>/NLMPC'
void MPC_controller::saveJacobian(s_aAq9pdCdNustb4CQC7xpeC *obj, int32_T nVar,
  int32_T mIneq, const real_T JacCineqTrans_data[], int32_T ineqCol0, const
  real_T JacCeqTrans_data[], int32_T ldJ)
{
  int32_T b;
  int32_T iCol;
  int32_T iCol_old;
  int32_T loop_ub_tmp;
  iCol = (ineqCol0 - 1) * ldJ;
  iCol_old = 0;
  b = mIneq - ineqCol0;
  for (int32_T idx_col{0}; idx_col <= b; idx_col++) {
    int32_T loop_ub;
    int32_T y_size_idx_0;
    int32_T y_size_idx_1;
    y_size_idx_0 = obj->JacCineqTrans_old.size[0];
    y_size_idx_1 = obj->JacCineqTrans_old.size[1];
    loop_ub_tmp = obj->JacCineqTrans_old.size[0] * obj->JacCineqTrans_old.size[1];
    if (loop_ub_tmp - 1 >= 0) {
      std::memcpy(&rtDW.y_data[0], &obj->JacCineqTrans_old.data[0], static_cast<
                  uint32_T>(loop_ub_tmp) * sizeof(real_T));
    }

    loop_ub = static_cast<uint8_T>(nVar);
    for (loop_ub_tmp = 0; loop_ub_tmp < loop_ub; loop_ub_tmp++) {
      rtDW.y_data[iCol_old + loop_ub_tmp] = JacCineqTrans_data[iCol +
        loop_ub_tmp];
    }

    obj->JacCineqTrans_old.size[1] = y_size_idx_1;
    loop_ub = y_size_idx_0 * y_size_idx_1;
    if (loop_ub - 1 >= 0) {
      std::memcpy(&obj->JacCineqTrans_old.data[0], &rtDW.y_data[0],
                  static_cast<uint32_T>(loop_ub) * sizeof(real_T));
    }

    iCol += ldJ;
    iCol_old += ldJ;
  }

  iCol = 0;
  iCol_old = 0;
  b = static_cast<uint8_T>(nVar);
  for (int32_T idx_col{0}; idx_col < 40; idx_col++) {
    for (loop_ub_tmp = 0; loop_ub_tmp < b; loop_ub_tmp++) {
      obj->JacCeqTrans_old.data[iCol_old + loop_ub_tmp] = JacCeqTrans_data[iCol
        + loop_ub_tmp];
    }

    iCol += ldJ;
    iCol_old += ldJ;
  }
}

// Function for MATLAB Function: '<S2>/NLMPC'
real_T MPC_controller::computeComplError(const int32_T
  *fscales_lineq_constraint_size, const int32_T *fscales_cineq_constraint_size,
  const real_T xCurrent[46], int32_T mIneq, const real_T cIneq_data[], const
  int32_T finiteLB_data[], int32_T mLB, const real_T lb[46], const int32_T
  finiteUB_data[], int32_T mUB, const real_T lambda_data[], int32_T iL0)
{
  real_T nlpComplError;
  nlpComplError = 0.0;
  if ((mIneq + mLB) + mUB > 0) {
    real_T lbDelta;
    real_T lbLambda;
    int32_T iLineq0;
    int32_T idx;
    int32_T mLinIneq;
    iLineq0 = *fscales_lineq_constraint_size;
    for (idx = 0; idx < iLineq0; idx++) {
      lbDelta = cIneq_data[idx];
      lbLambda = lambda_data[(iL0 + idx) - 1];
      nlpComplError = std::fmax(nlpComplError, std::fmin(std::abs(lbLambda *
        lbDelta), std::fmin(std::abs(lbDelta), lbLambda)));
    }

    iLineq0 = (iL0 + *fscales_lineq_constraint_size) - 1;
    idx = *fscales_cineq_constraint_size;
    for (int32_T b_idx{0}; b_idx < idx; b_idx++) {
      lbLambda = lambda_data[iLineq0 + b_idx];
      lbDelta = cIneq_data[*fscales_lineq_constraint_size + b_idx];
      nlpComplError = std::fmax(nlpComplError, std::fmin(std::abs(lbDelta *
        lbLambda), std::fmin(std::abs(lbDelta), lbLambda)));
    }

    iLineq0 = (iL0 + mIneq) - 1;
    mLinIneq = iLineq0 + mLB;
    idx = static_cast<uint16_T>(mLB);
    for (int32_T b_idx{0}; b_idx < idx; b_idx++) {
      int32_T finiteLB;
      finiteLB = finiteLB_data[b_idx];
      lbDelta = xCurrent[finiteLB - 1] - lb[finiteLB - 1];
      lbLambda = lambda_data[iLineq0 + b_idx];
      nlpComplError = std::fmax(nlpComplError, std::fmin(std::abs(lbDelta *
        lbLambda), std::fmin(std::abs(lbDelta), lbLambda)));
    }

    iLineq0 = static_cast<uint8_T>(mUB);
    for (idx = 0; idx < iLineq0; idx++) {
      lbDelta = lambda_data[mLinIneq + idx];
      lbLambda = (rtInf) - xCurrent[finiteUB_data[idx] - 1];
      nlpComplError = std::fmax(nlpComplError, std::fmin(std::abs(lbLambda *
        lbDelta), std::fmin(lbLambda, lbDelta)));
    }
  }

  return nlpComplError;
}

// Function for MATLAB Function: '<S2>/NLMPC'
void MPC_controller::computeGradLag_e(real_T workspace_data[], int32_T ldA,
  int32_T nVar, const real_T grad_data[], int32_T mIneq, const real_T
  AineqTrans_data[], const real_T AeqTrans_data[], const int32_T
  finiteFixed_data[], int32_T mFixed, const int32_T finiteLB_data[], int32_T mLB,
  const int32_T finiteUB_data[], int32_T mUB, const real_T lambda_data[])
{
  int32_T f;
  int32_T g;
  int32_T i;
  int32_T iL0;
  int32_T ix;
  int32_T tmp;
  std::memcpy(&workspace_data[0], &grad_data[0], static_cast<uint8_T>(nVar) *
              sizeof(real_T));
  i = static_cast<uint8_T>(mFixed);
  for (iL0 = 0; iL0 < i; iL0++) {
    ix = finiteFixed_data[iL0];
    workspace_data[ix - 1] += lambda_data[iL0];
  }

  ix = mFixed;
  f = ldA * 39 + 1;
  for (iL0 = 1; ldA < 0 ? iL0 >= f : iL0 <= f; iL0 += ldA) {
    g = iL0 + nVar;
    for (i = iL0; i < g; i++) {
      tmp = i - iL0;
      workspace_data[tmp] += AeqTrans_data[i - 1] * lambda_data[ix];
    }

    ix++;
  }

  if (mIneq != 0) {
    ix = mFixed + 40;
    f = (mIneq - 1) * ldA + 1;
    for (iL0 = 1; ldA < 0 ? iL0 >= f : iL0 <= f; iL0 += ldA) {
      g = iL0 + nVar;
      for (i = iL0; i < g; i++) {
        tmp = i - iL0;
        workspace_data[tmp] += AineqTrans_data[i - 1] * lambda_data[ix];
      }

      ix++;
    }
  }

  iL0 = (mFixed + mIneq) + 40;
  ix = static_cast<uint16_T>(mLB);
  for (i = 0; i < ix; i++) {
    f = finiteLB_data[i];
    workspace_data[f - 1] -= lambda_data[iL0 + i];
  }

  iL0 += static_cast<uint16_T>(mLB);
  ix = static_cast<uint8_T>(mUB);
  for (i = 0; i < ix; i++) {
    f = finiteUB_data[i];
    workspace_data[f - 1] += lambda_data[iL0 + i];
  }
}

// Function for MATLAB Function: '<S2>/NLMPC'
void MPC_controller::computeDualFeasError_k(int32_T nVar, const real_T
  gradLag_data[], boolean_T *gradOK, real_T *val)
{
  int32_T idx;
  boolean_T exitg1;
  *gradOK = true;
  *val = 0.0;
  idx = 0;
  exitg1 = false;
  while ((!exitg1) && (idx <= static_cast<uint8_T>(nVar) - 1)) {
    *gradOK = ((!std::isinf(gradLag_data[idx])) && (!std::isnan(gradLag_data[idx])));
    if (!*gradOK) {
      exitg1 = true;
    } else {
      *val = std::fmax(*val, std::abs(gradLag_data[idx]));
      idx++;
    }
  }
}

// Function for MATLAB Function: '<S2>/NLMPC'
void MPC_controller::updateWorkingSetForNewQP(const real_T xk[46],
  s_YG0fmBFfsyHj5FdUrtbgBC *WorkingSet, int32_T mIneq, int32_T mNonlinIneq,
  const real_T cIneq_data[], const real_T cEq[40], int32_T mLB, const real_T lb
  [46], int32_T mUB, int32_T mFixed)
{
  int32_T i;
  int32_T iEq0;
  int32_T iw0;
  int32_T nVar;
  nVar = WorkingSet->nVar;
  iw0 = WorkingSet->ldA * mFixed;
  iEq0 = 0;
  for (int32_T idx{0}; idx < 40; idx++) {
    WorkingSet->beq[idx] = -cEq[idx];
    WorkingSet->bwset.data[mFixed + idx] = WorkingSet->beq[idx];
    for (i = 0; i < nVar; i++) {
      WorkingSet->ATwset.data[iw0 + i] = WorkingSet->Aeq.data[iEq0 + i];
    }

    iw0 += WorkingSet->ldA;
    iEq0 += WorkingSet->ldA;
  }

  i = static_cast<uint8_T>(mIneq);
  for (int32_T idx{0}; idx < i; idx++) {
    WorkingSet->bineq.data[idx] = -cIneq_data[idx];
  }

  i = static_cast<uint16_T>(mLB);
  for (int32_T idx{0}; idx < i; idx++) {
    WorkingSet->lb.data[WorkingSet->indexLB.data[idx] - 1] = -lb
      [WorkingSet->indexLB.data[idx] - 1] + xk[WorkingSet->indexLB.data[idx] - 1];
  }

  i = static_cast<uint8_T>(mUB);
  for (int32_T idx{0}; idx < i; idx++) {
    WorkingSet->ub.data[WorkingSet->indexUB.data[idx] - 1] = (rtInf) -
      xk[WorkingSet->indexUB.data[idx] - 1];
  }

  i = static_cast<uint8_T>(mFixed);
  for (int32_T idx{0}; idx < i; idx++) {
    WorkingSet->ub.data[WorkingSet->indexFixed.data[idx] - 1] = (rtInf) -
      xk[WorkingSet->indexFixed.data[idx] - 1];
    WorkingSet->bwset.data[idx] = (rtInf) - xk[WorkingSet->indexFixed.data[idx]
      - 1];
  }

  if (WorkingSet->nActiveConstr > mFixed + 40) {
    iw0 = WorkingSet->nActiveConstr;
    for (int32_T idx{mFixed + 41}; idx <= iw0; idx++) {
      switch (WorkingSet->Wid.data[idx - 1]) {
       case 4:
        WorkingSet->bwset.data[idx - 1] = WorkingSet->lb.data
          [WorkingSet->indexLB.data[WorkingSet->Wlocalidx.data[idx - 1] - 1] - 1];
        break;

       case 5:
        WorkingSet->bwset.data[idx - 1] = WorkingSet->ub.data
          [WorkingSet->indexUB.data[WorkingSet->Wlocalidx.data[idx - 1] - 1] - 1];
        break;

       default:
        {
          WorkingSet->bwset.data[idx - 1] = WorkingSet->bineq.data
            [WorkingSet->Wlocalidx.data[idx - 1] - 1];
          if ((mNonlinIneq > 0) && (WorkingSet->Wlocalidx.data[idx - 1] >=
               mNonlinIneq)) {
            int32_T g;
            int32_T ix0;
            iEq0 = (idx - 1) * WorkingSet->ldA;
            ix0 = (WorkingSet->Wlocalidx.data[idx - 1] - 1) * WorkingSet->ldA;
            g = static_cast<uint8_T>(nVar);
            for (i = 0; i < g; i++) {
              WorkingSet->ATwset.data[iEq0 + i] = WorkingSet->Aineq.data[ix0 + i];
            }
          }
        }
        break;
      }
    }
  }
}

// Function for MATLAB Function: '<S2>/NLMPC'
void MPC_controller::xswap(int32_T n, real_T x_data[], int32_T ix0, int32_T iy0)
{
  for (int32_T k{0}; k < n; k++) {
    real_T temp;
    int32_T temp_tmp;
    int32_T tmp;
    temp_tmp = (ix0 + k) - 1;
    temp = x_data[temp_tmp];
    tmp = (iy0 + k) - 1;
    x_data[temp_tmp] = x_data[tmp];
    x_data[tmp] = temp;
  }
}

// Function for MATLAB Function: '<S2>/NLMPC'
real_T MPC_controller::xnrm2(int32_T n, const real_T x_data[], int32_T ix0)
{
  real_T y;
  y = 0.0;
  if (n >= 1) {
    if (n == 1) {
      y = std::abs(x_data[ix0 - 1]);
    } else {
      real_T scale;
      int32_T kend;
      scale = 3.3121686421112381E-170;
      kend = (ix0 + n) - 1;
      for (int32_T k{ix0}; k <= kend; k++) {
        real_T absxk;
        absxk = std::abs(x_data[k - 1]);
        if (absxk > scale) {
          real_T t;
          t = scale / absxk;
          y = y * t * t + 1.0;
          scale = absxk;
        } else {
          real_T t;
          t = absxk / scale;
          y += t * t;
        }
      }

      y = scale * std::sqrt(y);
    }
  }

  return y;
}

real_T rt_hypotd_snf(real_T u0, real_T u1)
{
  real_T a;
  real_T b;
  real_T y;
  a = std::abs(u0);
  b = std::abs(u1);
  if (a < b) {
    a /= b;
    y = std::sqrt(a * a + 1.0) * b;
  } else if (a > b) {
    b /= a;
    y = std::sqrt(b * b + 1.0) * a;
  } else if (std::isnan(b)) {
    y = (rtNaN);
  } else {
    y = a * 1.4142135623730951;
  }

  return y;
}

// Function for MATLAB Function: '<S2>/NLMPC'
real_T MPC_controller::xzlarfg(int32_T n, real_T *alpha1, real_T x_data[],
  int32_T ix0)
{
  real_T tau;
  tau = 0.0;
  if (n > 0) {
    real_T xnorm;
    xnorm = xnrm2(n - 1, x_data, ix0);
    if (xnorm != 0.0) {
      xnorm = rt_hypotd_snf(*alpha1, xnorm);
      if (*alpha1 >= 0.0) {
        xnorm = -xnorm;
      }

      if (std::abs(xnorm) < 1.0020841800044864E-292) {
        real_T a;
        int32_T c_tmp;
        int32_T knt;
        knt = 0;
        c_tmp = (ix0 + n) - 2;
        do {
          knt++;
          for (int32_T d{ix0}; d <= c_tmp; d++) {
            x_data[d - 1] *= 9.9792015476736E+291;
          }

          xnorm *= 9.9792015476736E+291;
          *alpha1 *= 9.9792015476736E+291;
        } while ((std::abs(xnorm) < 1.0020841800044864E-292) && (knt < 20));

        xnorm = rt_hypotd_snf(*alpha1, xnrm2(n - 1, x_data, ix0));
        if (*alpha1 >= 0.0) {
          xnorm = -xnorm;
        }

        tau = (xnorm - *alpha1) / xnorm;
        a = 1.0 / (*alpha1 - xnorm);
        for (int32_T d{ix0}; d <= c_tmp; d++) {
          x_data[d - 1] *= a;
        }

        for (int32_T d{0}; d < knt; d++) {
          xnorm *= 1.0020841800044864E-292;
        }

        *alpha1 = xnorm;
      } else {
        real_T a;
        int32_T d;
        tau = (xnorm - *alpha1) / xnorm;
        a = 1.0 / (*alpha1 - xnorm);
        d = (ix0 + n) - 2;
        for (int32_T knt{ix0}; knt <= d; knt++) {
          x_data[knt - 1] *= a;
        }

        *alpha1 = xnorm;
      }
    }
  }

  return tau;
}

// Function for MATLAB Function: '<S2>/NLMPC'
void MPC_controller::xgemv(int32_T m, int32_T n, const real_T A_data[], int32_T
  ia0, int32_T lda, const real_T x_data[], int32_T ix0, real_T y_data[])
{
  if (n != 0) {
    int32_T b;
    int32_T iy;
    if (n - 1 >= 0) {
      std::memset(&y_data[0], 0, static_cast<uint32_T>(n) * sizeof(real_T));
    }

    iy = 0;
    b = (n - 1) * lda + ia0;
    for (int32_T b_iy{ia0}; lda < 0 ? b_iy >= b : b_iy <= b; b_iy += lda) {
      real_T c;
      int32_T d;
      c = 0.0;
      d = b_iy + m;
      for (int32_T iyend{b_iy}; iyend < d; iyend++) {
        c += x_data[((ix0 + iyend) - b_iy) - 1] * A_data[iyend - 1];
      }

      y_data[iy] += c;
      iy++;
    }
  }
}

// Function for MATLAB Function: '<S2>/NLMPC'
void MPC_controller::xgerc(int32_T m, int32_T n, real_T alpha1, int32_T ix0,
  const real_T y_data[], real_T A_data[], int32_T ia0, int32_T lda)
{
  if (!(alpha1 == 0.0)) {
    int32_T jA;
    jA = ia0;
    for (int32_T j{0}; j < n; j++) {
      real_T temp;
      temp = y_data[j];
      if (temp != 0.0) {
        int32_T b;
        temp *= alpha1;
        b = m + jA;
        for (int32_T ijA{jA}; ijA < b; ijA++) {
          A_data[ijA - 1] += A_data[((ix0 + ijA) - jA) - 1] * temp;
        }
      }

      jA += lda;
    }
  }
}

// Function for MATLAB Function: '<S2>/NLMPC'
void MPC_controller::xzlarf(int32_T m, int32_T n, int32_T iv0, real_T tau,
  real_T C_data[], int32_T ic0, int32_T ldc, real_T work_data[])
{
  int32_T lastc;
  int32_T lastv;
  if (tau != 0.0) {
    boolean_T exitg2;
    lastv = m;
    lastc = iv0 + m;
    while ((lastv > 0) && (C_data[lastc - 2] == 0.0)) {
      lastv--;
      lastc--;
    }

    lastc = n;
    exitg2 = false;
    while ((!exitg2) && (lastc > 0)) {
      int32_T coltop;
      int32_T exitg1;
      int32_T ia;
      coltop = (lastc - 1) * ldc + ic0;
      ia = coltop;
      do {
        exitg1 = 0;
        if (ia <= (coltop + lastv) - 1) {
          if (C_data[ia - 1] != 0.0) {
            exitg1 = 1;
          } else {
            ia++;
          }
        } else {
          lastc--;
          exitg1 = 2;
        }
      } while (exitg1 == 0);

      if (exitg1 == 1) {
        exitg2 = true;
      }
    }
  } else {
    lastv = 0;
    lastc = 0;
  }

  if (lastv > 0) {
    xgemv(lastv, lastc, C_data, ic0, ldc, C_data, iv0, work_data);
    xgerc(lastv, lastc, -tau, iv0, work_data, C_data, ic0, ldc);
  }
}

// Function for MATLAB Function: '<S2>/NLMPC'
void MPC_controller::qrf(real_T A_data[], const int32_T A_size[2], int32_T m,
  int32_T n, int32_T nfxd, real_T tau_data[])
{
  real_T work_data[453];
  real_T b_atmp;
  int32_T lda;
  int32_T loop_ub;
  lda = A_size[0];
  loop_ub = A_size[1];
  if (loop_ub - 1 >= 0) {
    std::memset(&work_data[0], 0, static_cast<uint32_T>(loop_ub) * sizeof(real_T));
  }

  loop_ub = static_cast<uint8_T>(nfxd);
  for (int32_T i{0}; i < loop_ub; i++) {
    int32_T ii;
    int32_T mmi;
    ii = i * lda + i;
    mmi = m - i;
    if (i + 1 < m) {
      b_atmp = A_data[ii];
      tau_data[i] = xzlarfg(mmi, &b_atmp, A_data, ii + 2);
      A_data[ii] = b_atmp;
    } else {
      tau_data[i] = 0.0;
    }

    if (i + 1 < n) {
      b_atmp = A_data[ii];
      A_data[ii] = 1.0;
      xzlarf(mmi, (n - i) - 1, ii + 1, tau_data[i], A_data, (ii + lda) + 1, lda,
             work_data);
      A_data[ii] = b_atmp;
    }
  }
}

// Function for MATLAB Function: '<S2>/NLMPC'
void MPC_controller::qrpf(real_T A_data[], const int32_T A_size[2], int32_T m,
  int32_T n, int32_T nfxd, real_T tau_data[], int32_T jpvt_data[])
{
  real_T vn1_data[453];
  real_T vn2_data[453];
  real_T work_data[453];
  real_T smax;
  int32_T ma;
  int32_T minmn;
  int32_T pvt;
  ma = A_size[0];
  if (m <= n) {
    minmn = m;
  } else {
    minmn = n;
  }

  pvt = A_size[1];
  if (pvt - 1 >= 0) {
    std::memset(&work_data[0], 0, static_cast<uint32_T>(pvt) * sizeof(real_T));
  }

  pvt = A_size[1];
  if (pvt - 1 >= 0) {
    std::memset(&vn1_data[0], 0, static_cast<uint32_T>(pvt) * sizeof(real_T));
  }

  pvt = A_size[1];
  if (pvt - 1 >= 0) {
    std::memset(&vn2_data[0], 0, static_cast<uint32_T>(pvt) * sizeof(real_T));
  }

  for (int32_T j{nfxd + 1}; j <= n; j++) {
    vn1_data[j - 1] = xnrm2(m - nfxd, A_data, ((j - 1) * ma + nfxd) + 1);
    vn2_data[j - 1] = vn1_data[j - 1];
  }

  for (int32_T j{nfxd + 1}; j <= minmn; j++) {
    real_T s;
    int32_T ii;
    int32_T itemp;
    int32_T mmi;
    int32_T nmi;
    ii = ((j - 1) * ma + j) - 1;
    nmi = n - j;
    mmi = m - j;
    if (nmi + 1 < 1) {
      itemp = -2;
    } else {
      itemp = -1;
      if (nmi + 1 > 1) {
        smax = std::abs(vn1_data[j - 1]);
        for (pvt = 2; pvt <= nmi + 1; pvt++) {
          s = std::abs(vn1_data[(j + pvt) - 2]);
          if (s > smax) {
            itemp = pvt - 2;
            smax = s;
          }
        }
      }
    }

    pvt = j + itemp;
    if (pvt + 1 != j) {
      xswap(m, A_data, pvt * ma + 1, (j - 1) * ma + 1);
      itemp = jpvt_data[pvt];
      jpvt_data[pvt] = jpvt_data[j - 1];
      jpvt_data[j - 1] = itemp;
      vn1_data[pvt] = vn1_data[j - 1];
      vn2_data[pvt] = vn2_data[j - 1];
    }

    if (j < m) {
      smax = A_data[ii];
      tau_data[j - 1] = xzlarfg(mmi + 1, &smax, A_data, ii + 2);
      A_data[ii] = smax;
    } else {
      tau_data[j - 1] = 0.0;
    }

    if (j < n) {
      smax = A_data[ii];
      A_data[ii] = 1.0;
      xzlarf(mmi + 1, nmi, ii + 1, tau_data[j - 1], A_data, (ii + ma) + 1, ma,
             work_data);
      A_data[ii] = smax;
    }

    for (pvt = j + 1; pvt <= n; pvt++) {
      real_T tmp;
      ii = (pvt - 1) * ma + j;
      tmp = vn1_data[pvt - 1];
      if (tmp != 0.0) {
        smax = std::abs(A_data[ii - 1]) / tmp;
        smax = 1.0 - smax * smax;
        if (smax < 0.0) {
          smax = 0.0;
        }

        s = tmp / vn2_data[pvt - 1];
        s = s * s * smax;
        if (s <= 1.4901161193847656E-8) {
          if (j < m) {
            vn1_data[pvt - 1] = xnrm2(mmi, A_data, ii + 1);
            vn2_data[pvt - 1] = vn1_data[pvt - 1];
          } else {
            vn1_data[pvt - 1] = 0.0;
            vn2_data[pvt - 1] = 0.0;
          }
        } else {
          vn1_data[pvt - 1] = tmp * std::sqrt(smax);
        }
      }
    }
  }
}

// Function for MATLAB Function: '<S2>/NLMPC'
void MPC_controller::xgeqp3(real_T A_data[], const int32_T A_size[2], int32_T m,
  int32_T n, int32_T jpvt_data[], real_T tau_data[], int32_T *tau_size)
{
  int32_T ma;
  int32_T minmana;
  int32_T minmn;
  ma = A_size[0];
  if (A_size[0] <= A_size[1]) {
    minmana = A_size[0];
  } else {
    minmana = A_size[1];
  }

  if (m <= n) {
    minmn = m;
  } else {
    minmn = n;
  }

  *tau_size = minmana;
  if (minmana - 1 >= 0) {
    std::memset(&tau_data[0], 0, static_cast<uint32_T>(minmana) * sizeof(real_T));
  }

  if (minmn < 1) {
    for (minmana = 0; minmana < n; minmana++) {
      jpvt_data[minmana] = minmana + 1;
    }
  } else {
    int32_T nfxd;
    nfxd = -1;
    for (minmana = 0; minmana < n; minmana++) {
      if (jpvt_data[minmana] != 0) {
        nfxd++;
        if (minmana + 1 != nfxd + 1) {
          xswap(m, A_data, minmana * ma + 1, nfxd * ma + 1);
          jpvt_data[minmana] = jpvt_data[nfxd];
          jpvt_data[nfxd] = minmana + 1;
        } else {
          jpvt_data[minmana] = minmana + 1;
        }
      } else {
        jpvt_data[minmana] = minmana + 1;
      }
    }

    if (nfxd + 1 <= minmn) {
      nfxd++;
    } else {
      nfxd = minmn;
    }

    qrf(A_data, A_size, m, n, nfxd, tau_data);
    if (nfxd < minmn) {
      qrpf(A_data, A_size, m, n, nfxd, tau_data, jpvt_data);
    }
  }
}

// Function for MATLAB Function: '<S2>/NLMPC'
void MPC_controller::factorQRE(s_LP9wk1co4RSPM0xk4tXznB *obj, const real_T
  A_data[], int32_T mrows, int32_T ncols, int32_T ldA)
{
  int32_T b;
  b = static_cast<uint8_T>(mrows);
  for (int32_T idx{0}; idx < ncols; idx++) {
    int32_T ix0;
    int32_T iy0;
    ix0 = ldA * idx;
    iy0 = obj->ldq * idx;
    for (int32_T k{0}; k < b; k++) {
      obj->QR.data[iy0 + k] = A_data[ix0 + k];
    }
  }

  obj->usedPivoting = true;
  obj->mrows = mrows;
  obj->ncols = ncols;
  if (mrows <= ncols) {
    obj->minRowCol = mrows;
  } else {
    obj->minRowCol = ncols;
  }

  xgeqp3(obj->QR.data, obj->QR.size, mrows, ncols, obj->jpvt.data, obj->tau.data,
         &obj->tau.size);
}

// Function for MATLAB Function: '<S2>/NLMPC'
void MPC_controller::xorgqr(int32_T m, int32_T n, int32_T k, real_T A_data[],
  const int32_T A_size[2], int32_T lda, const real_T tau_data[])
{
  real_T work_data[453];
  if (n >= 1) {
    int32_T ia;
    int32_T itau;
    int32_T loop_ub;
    for (itau = k; itau < n; itau++) {
      ia = itau * lda;
      std::memset(&A_data[ia], 0, static_cast<uint32_T>((m + ia) - ia) * sizeof
                  (real_T));
      A_data[ia + itau] = 1.0;
    }

    itau = k - 1;
    loop_ub = static_cast<int16_T>(A_size[1]);
    if (loop_ub - 1 >= 0) {
      std::memset(&work_data[0], 0, static_cast<uint32_T>(loop_ub) * sizeof
                  (real_T));
    }

    for (int32_T i{k}; i >= 1; i--) {
      int32_T d;
      ia = (i - 1) * lda + i;
      if (i < n) {
        A_data[ia - 1] = 1.0;
        xzlarf((m - i) + 1, n - i, ia, tau_data[itau], A_data, ia + lda, lda,
               work_data);
      }

      if (i < m) {
        d = (ia + m) - i;
        for (loop_ub = ia + 1; loop_ub <= d; loop_ub++) {
          A_data[loop_ub - 1] *= -tau_data[itau];
        }
      }

      A_data[ia - 1] = 1.0 - tau_data[itau];
      d = static_cast<uint8_T>(i - 1);
      for (loop_ub = 0; loop_ub < d; loop_ub++) {
        A_data[(ia - loop_ub) - 2] = 0.0;
      }

      itau--;
    }
  }
}

// Function for MATLAB Function: '<S2>/NLMPC'
void MPC_controller::xgemv_d(int32_T m, int32_T n, const real_T A_data[],
  int32_T lda, const real_T x_data[], real_T y_data[])
{
  if (m != 0) {
    int32_T b;
    int32_T iy;
    std::memset(&y_data[0], 0, static_cast<uint32_T>(n) * sizeof(real_T));
    iy = 0;
    b = (n - 1) * lda + 1;
    for (int32_T b_iy{1}; lda < 0 ? b_iy >= b : b_iy <= b; b_iy += lda) {
      real_T c;
      int32_T d;
      c = 0.0;
      d = b_iy + m;
      for (int32_T iyend{b_iy}; iyend < d; iyend++) {
        c += A_data[iyend - 1] * x_data[iyend - b_iy];
      }

      y_data[iy] += c;
      iy++;
    }
  }
}

// Function for MATLAB Function: '<S2>/NLMPC'
void MPC_controller::sortLambdaQP(real_T lambda_data[], int32_T
  WorkingSet_nActiveConstr, const int32_T WorkingSet_sizes[5], const int32_T
  WorkingSet_isActiveIdx[6], const int32_T WorkingSet_Wid_data[], const int32_T
  WorkingSet_Wlocalidx_data[], real_T workspace_data[])
{
  if (WorkingSet_nActiveConstr != 0) {
    int32_T currentMplier;
    int32_T idxOffset;
    int32_T mAll;
    mAll = (((WorkingSet_sizes[0] + WorkingSet_sizes[3]) + WorkingSet_sizes[4])
            + WorkingSet_sizes[2]) + 39;
    if (static_cast<uint16_T>(mAll + 1) - 1 >= 0) {
      std::memcpy(&workspace_data[0], &lambda_data[0], static_cast<uint16_T>
                  (mAll + 1) * sizeof(real_T));
    }

    std::memset(&lambda_data[0], 0, static_cast<uint32_T>(mAll + 1) * sizeof
                (real_T));
    currentMplier = 0;
    mAll = 0;
    while ((mAll + 1 <= WorkingSet_nActiveConstr) && (WorkingSet_Wid_data[mAll] <=
            2)) {
      if (WorkingSet_Wid_data[mAll] == 1) {
        idxOffset = 1;
      } else {
        idxOffset = WorkingSet_isActiveIdx[1];
      }

      lambda_data[(idxOffset + WorkingSet_Wlocalidx_data[mAll]) - 2] =
        workspace_data[currentMplier];
      currentMplier++;
      mAll++;
    }

    while (mAll + 1 <= WorkingSet_nActiveConstr) {
      switch (WorkingSet_Wid_data[mAll]) {
       case 3:
        idxOffset = WorkingSet_isActiveIdx[2];
        break;

       case 4:
        idxOffset = WorkingSet_isActiveIdx[3];
        break;

       default:
        idxOffset = WorkingSet_isActiveIdx[4];
        break;
      }

      lambda_data[(idxOffset + WorkingSet_Wlocalidx_data[mAll]) - 2] =
        workspace_data[currentMplier];
      currentMplier++;
      mAll++;
    }
  }
}

// Function for MATLAB Function: '<S2>/NLMPC'
void MPC_controller::test_exit(s7RdrPWkr8UPAUyTdDJkLaG *Flags,
  s_AiLncvKJfAMbGh9HSVCzlG *memspace, sG8JZ69axY52WWR6RKyApQC *MeritFunction,
  const int32_T *fscales_lineq_constraint_size, const int32_T
  *fscales_cineq_constraint_size, s_YG0fmBFfsyHj5FdUrtbgBC *WorkingSet,
  s_aAq9pdCdNustb4CQC7xpeC *TrialState, s_LP9wk1co4RSPM0xk4tXznB *QRManager,
  const real_T lb[46])
{
  real_T s;
  real_T smax;
  int32_T iQR_diag;
  int32_T idx_max;
  int32_T idx_max_tmp;
  int32_T mFixed;
  int32_T nVar;
  boolean_T dxTooSmall;
  boolean_T isFeasible;
  nVar = WorkingSet->nVar;
  mFixed = WorkingSet->sizes[0];
  idx_max_tmp = static_cast<uint16_T>((((WorkingSet->sizes[0] +
    WorkingSet->sizes[2]) + WorkingSet->sizes[3]) + WorkingSet->sizes[4]) + 40);
  if (idx_max_tmp - 1 >= 0) {
    std::memcpy(&TrialState->lambdaStopTest.data[0], &TrialState->
                lambdasqp.data[0], static_cast<uint32_T>(idx_max_tmp) * sizeof
                (real_T));
  }

  computeGradLag(TrialState->gradLag.data, WorkingSet->ldA, WorkingSet->nVar,
                 TrialState->grad.data, WorkingSet->sizes[2],
                 WorkingSet->Aineq.data, WorkingSet->Aeq.data,
                 WorkingSet->indexFixed.data, WorkingSet->sizes[0],
                 WorkingSet->indexLB.data, WorkingSet->sizes[3],
                 WorkingSet->indexUB.data, WorkingSet->sizes[4],
                 TrialState->lambdaStopTest.data);
  if (WorkingSet->nVar < 1) {
    idx_max = 0;
  } else {
    idx_max = 1;
    if (WorkingSet->nVar > 1) {
      smax = std::abs(TrialState->grad.data[0]);
      for (iQR_diag = 2; iQR_diag <= nVar; iQR_diag++) {
        s = std::abs(TrialState->grad.data[iQR_diag - 1]);
        if (s > smax) {
          idx_max = iQR_diag;
          smax = s;
        }
      }
    }
  }

  smax = std::fmax(1.0, std::abs(TrialState->grad.data[idx_max - 1]));
  if (std::isinf(smax)) {
    smax = 1.0;
  }

  MeritFunction->nlpPrimalFeasError = computePrimalFeasError
    (TrialState->xstarsqp, WorkingSet->sizes[2] - TrialState->mNonlinIneq,
     TrialState->mNonlinIneq, TrialState->cIneq.data, TrialState->cEq,
     WorkingSet->indexLB.data, WorkingSet->sizes[3], lb,
     WorkingSet->indexUB.data, WorkingSet->sizes[4]);
  if (TrialState->sqpIterations == 0) {
    MeritFunction->feasRelativeFactor = std::fmax(1.0,
      MeritFunction->nlpPrimalFeasError);
  }

  isFeasible = (MeritFunction->nlpPrimalFeasError <= 1.0E-6 *
                MeritFunction->feasRelativeFactor);
  computeDualFeasError(WorkingSet->nVar, TrialState->gradLag.data,
                       &Flags->gradOK, &MeritFunction->nlpDualFeasError);
  if (!Flags->gradOK) {
    Flags->done = true;
    if (isFeasible) {
      TrialState->sqpExitFlag = 2;
    } else {
      TrialState->sqpExitFlag = -2;
    }
  } else {
    real_T nlpComplErrorTmp;
    MeritFunction->nlpComplError = computeComplError
      (fscales_lineq_constraint_size, fscales_cineq_constraint_size,
       TrialState->xstarsqp, WorkingSet->sizes[2], TrialState->cIneq.data,
       WorkingSet->indexLB.data, WorkingSet->sizes[3], lb,
       WorkingSet->indexUB.data, WorkingSet->sizes[4],
       TrialState->lambdaStopTest.data, WorkingSet->sizes[0] + 41);
    MeritFunction->firstOrderOpt = std::fmax(MeritFunction->nlpDualFeasError,
      MeritFunction->nlpComplError);
    if (TrialState->sqpIterations > 1) {
      real_T tmp;
      computeGradLag_e(memspace->workspace_double.data, WorkingSet->ldA,
                       WorkingSet->nVar, TrialState->grad.data,
                       WorkingSet->sizes[2], WorkingSet->Aineq.data,
                       WorkingSet->Aeq.data, WorkingSet->indexFixed.data,
                       WorkingSet->sizes[0], WorkingSet->indexLB.data,
                       WorkingSet->sizes[3], WorkingSet->indexUB.data,
                       WorkingSet->sizes[4], TrialState->lambdaStopTestPrev.data);
      computeDualFeasError_k(WorkingSet->nVar, memspace->workspace_double.data,
        &dxTooSmall, &s);
      nlpComplErrorTmp = computeComplError(fscales_lineq_constraint_size,
        fscales_cineq_constraint_size, TrialState->xstarsqp, WorkingSet->sizes[2],
        TrialState->cIneq.data, WorkingSet->indexLB.data, WorkingSet->sizes[3],
        lb, WorkingSet->indexUB.data, WorkingSet->sizes[4],
        TrialState->lambdaStopTestPrev.data, WorkingSet->sizes[0] + 41);
      tmp = std::fmax(s, nlpComplErrorTmp);
      if (tmp < std::fmax(MeritFunction->nlpDualFeasError,
                          MeritFunction->nlpComplError)) {
        MeritFunction->nlpDualFeasError = s;
        MeritFunction->nlpComplError = nlpComplErrorTmp;
        MeritFunction->firstOrderOpt = tmp;
        if (idx_max_tmp - 1 >= 0) {
          std::memcpy(&TrialState->lambdaStopTest.data[0],
                      &TrialState->lambdaStopTestPrev.data[0],
                      static_cast<uint32_T>(idx_max_tmp) * sizeof(real_T));
        }
      } else if (idx_max_tmp - 1 >= 0) {
        std::memcpy(&TrialState->lambdaStopTestPrev.data[0],
                    &TrialState->lambdaStopTest.data[0], static_cast<uint32_T>
                    (idx_max_tmp) * sizeof(real_T));
      }
    } else if (idx_max_tmp - 1 >= 0) {
      std::memcpy(&TrialState->lambdaStopTestPrev.data[0],
                  &TrialState->lambdaStopTest.data[0], static_cast<uint32_T>
                  (idx_max_tmp) * sizeof(real_T));
    }

    if (isFeasible && (MeritFunction->nlpDualFeasError <= 1.0E-6 * smax) &&
        (MeritFunction->nlpComplError <= 1.0E-6 * smax)) {
      Flags->done = true;
      TrialState->sqpExitFlag = 1;
    } else {
      Flags->done = false;
      if (isFeasible && (TrialState->sqpFval < -1.0E+20)) {
        Flags->done = true;
        TrialState->sqpExitFlag = -3;
      } else {
        boolean_T guard1{ false };

        guard1 = false;
        if (TrialState->sqpIterations > 0) {
          boolean_T exitg1;
          dxTooSmall = true;
          iQR_diag = 0;
          exitg1 = false;
          while ((!exitg1) && (iQR_diag <= static_cast<uint8_T>(WorkingSet->nVar)
                               - 1)) {
            if (1.0E-6 * std::fmax(1.0, std::abs(TrialState->xstarsqp[iQR_diag]))
                <= std::abs(TrialState->delta_x.data[iQR_diag])) {
              dxTooSmall = false;
              exitg1 = true;
            } else {
              iQR_diag++;
            }
          }

          if (dxTooSmall) {
            if (!isFeasible) {
              if (Flags->stepType != 2) {
                Flags->stepType = 2;
                Flags->failedLineSearch = false;
                Flags->stepAccepted = false;
                guard1 = true;
              } else {
                Flags->done = true;
                TrialState->sqpExitFlag = -2;
              }
            } else if (WorkingSet->nActiveConstr > 0) {
              int32_T b_ix;
              int32_T ix;
              int32_T rankR;
              updateWorkingSetForNewQP(TrialState->xstarsqp, WorkingSet,
                WorkingSet->sizes[2], TrialState->mNonlinIneq,
                TrialState->cIneq.data, TrialState->cEq, WorkingSet->sizes[3],
                lb, WorkingSet->sizes[4], WorkingSet->sizes[0]);
              std::memset(&TrialState->lambda.data[0], 0, static_cast<uint32_T>
                          ((WorkingSet->nActiveConstr - 1) + 1) * sizeof(real_T));
              factorQRE(QRManager, WorkingSet->ATwset.data, WorkingSet->nVar,
                        WorkingSet->nActiveConstr, WorkingSet->ldA);
              rankR = QRManager->minRowCol;
              for (nVar = 0; nVar < rankR; nVar++) {
                iQR_diag = QRManager->ldq * nVar + nVar;
                b_ix = QRManager->mrows - nVar;
                if (b_ix - 2 >= 0) {
                  std::memcpy(&QRManager->Q.data[iQR_diag + 1],
                              &QRManager->QR.data[iQR_diag + 1],
                              static_cast<uint32_T>(((b_ix + iQR_diag) -
                    iQR_diag) - 1) * sizeof(real_T));
                }
              }

              xorgqr(QRManager->mrows, QRManager->mrows, QRManager->minRowCol,
                     QRManager->Q.data, QRManager->Q.size, QRManager->ldq,
                     QRManager->tau.data);
              xgemv_d(WorkingSet->nVar, WorkingSet->nVar, QRManager->Q.data,
                      QRManager->ldq, TrialState->grad.data,
                      memspace->workspace_double.data);
              if (WorkingSet->nVar >= WorkingSet->nActiveConstr) {
                idx_max = WorkingSet->nVar;
              } else {
                idx_max = WorkingSet->nActiveConstr;
              }

              s = std::fmin(1.4901161193847656E-8, static_cast<real_T>(idx_max) *
                            2.2204460492503131E-16) * std::abs
                (QRManager->QR.data[0]);
              if (WorkingSet->nVar <= WorkingSet->nActiveConstr) {
                ix = WorkingSet->nVar;
              } else {
                ix = WorkingSet->nActiveConstr;
              }

              rankR = 0;
              iQR_diag = 0;
              while ((rankR < ix) && (std::abs(QRManager->QR.data[iQR_diag]) > s))
              {
                rankR++;
                iQR_diag = (iQR_diag + QRManager->ldq) + 1;
              }

              if (rankR != 0) {
                for (nVar = rankR; nVar >= 1; nVar--) {
                  iQR_diag = ((nVar - 1) * QRManager->ldq + nVar) - 2;
                  memspace->workspace_double.data[nVar - 1] /=
                    QRManager->QR.data[iQR_diag + 1];
                  for (idx_max = 0; idx_max <= nVar - 2; idx_max++) {
                    b_ix = (nVar - idx_max) - 2;
                    memspace->workspace_double.data[b_ix] -=
                      memspace->workspace_double.data[nVar - 1] *
                      QRManager->QR.data[iQR_diag - idx_max];
                  }
                }
              }

              if (WorkingSet->nActiveConstr <= ix) {
                nVar = static_cast<uint8_T>(WorkingSet->nActiveConstr);
              } else {
                nVar = static_cast<uint8_T>(ix);
              }

              for (iQR_diag = 0; iQR_diag < nVar; iQR_diag++) {
                TrialState->lambda.data[QRManager->jpvt.data[iQR_diag] - 1] =
                  memspace->workspace_double.data[iQR_diag];
              }

              for (iQR_diag = mFixed + 1; iQR_diag <= mFixed + 40; iQR_diag++) {
                TrialState->lambda.data[iQR_diag - 1] = -TrialState->
                  lambda.data[iQR_diag - 1];
              }

              sortLambdaQP(TrialState->lambda.data, WorkingSet->nActiveConstr,
                           WorkingSet->sizes, WorkingSet->isActiveIdx,
                           WorkingSet->Wid.data, WorkingSet->Wlocalidx.data,
                           memspace->workspace_double.data);
              computeGradLag_e(memspace->workspace_double.data, WorkingSet->ldA,
                               WorkingSet->nVar, TrialState->grad.data,
                               WorkingSet->sizes[2], WorkingSet->Aineq.data,
                               WorkingSet->Aeq.data, WorkingSet->indexFixed.data,
                               WorkingSet->sizes[0], WorkingSet->indexLB.data,
                               WorkingSet->sizes[3], WorkingSet->indexUB.data,
                               WorkingSet->sizes[4], TrialState->lambda.data);
              computeDualFeasError_k(WorkingSet->nVar,
                memspace->workspace_double.data, &isFeasible, &s);
              nlpComplErrorTmp = computeComplError(fscales_lineq_constraint_size,
                fscales_cineq_constraint_size, TrialState->xstarsqp,
                WorkingSet->sizes[2], TrialState->cIneq.data,
                WorkingSet->indexLB.data, WorkingSet->sizes[3], lb,
                WorkingSet->indexUB.data, WorkingSet->sizes[4],
                TrialState->lambda.data, WorkingSet->sizes[0] + 1);
              if ((s <= 1.0E-6 * smax) && (nlpComplErrorTmp <= 1.0E-6 * smax)) {
                MeritFunction->nlpDualFeasError = s;
                MeritFunction->nlpComplError = nlpComplErrorTmp;
                MeritFunction->firstOrderOpt = std::fmax(s, nlpComplErrorTmp);
                if (idx_max_tmp - 1 >= 0) {
                  std::memcpy(&TrialState->lambdaStopTest.data[0],
                              &TrialState->lambda.data[0], static_cast<uint32_T>
                              (idx_max_tmp) * sizeof(real_T));
                }

                Flags->done = true;
                TrialState->sqpExitFlag = 1;
              } else {
                Flags->done = true;
                TrialState->sqpExitFlag = 2;
              }
            } else {
              Flags->done = true;
              TrialState->sqpExitFlag = 2;
            }
          } else {
            guard1 = true;
          }
        } else {
          guard1 = true;
        }

        if (guard1) {
          if (TrialState->sqpIterations >= 400) {
            Flags->done = true;
            TrialState->sqpExitFlag = 0;
          } else if (TrialState->FunctionEvaluations >= 4600) {
            Flags->done = true;
            TrialState->sqpExitFlag = 0;
          }
        }
      }
    }
  }
}

// Function for MATLAB Function: '<S2>/NLMPC'
boolean_T MPC_controller::BFGSUpdate(int32_T nvar, real_T Bk[2116], const real_T
  sk_data[], real_T yk_data[], real_T workspace_data[])
{
  real_T curvatureS;
  real_T dotSY;
  int32_T b;
  int32_T b_ix;
  int32_T b_jA;
  int32_T b_tmp;
  int32_T ix;
  int32_T jy;
  boolean_T success;
  dotSY = 0.0;
  if (nvar >= 1) {
    b = static_cast<uint8_T>(nvar);
    for (ix = 0; ix < b; ix++) {
      dotSY += sk_data[ix] * yk_data[ix];
    }
  }

  b_tmp = static_cast<uint8_T>(nvar);
  std::memset(&workspace_data[0], 0, static_cast<uint8_T>(nvar) * sizeof(real_T));
  ix = 0;
  jy = (nvar - 1) * 46 + 1;
  for (b = 1; b <= jy; b += 46) {
    b_ix = b + nvar;
    for (b_jA = b; b_jA < b_ix; b_jA++) {
      int32_T tmp;
      tmp = b_jA - b;
      workspace_data[tmp] += Bk[b_jA - 1] * sk_data[ix];
    }

    ix++;
  }

  curvatureS = 0.0;
  if (nvar >= 1) {
    for (b = 0; b < b_tmp; b++) {
      curvatureS += workspace_data[b] * sk_data[b];
    }
  }

  if (dotSY < 0.2 * curvatureS) {
    dotSY = 0.8 * curvatureS / (curvatureS - dotSY);
    for (ix = 0; ix < b_tmp; ix++) {
      yk_data[ix] *= dotSY;
    }

    if (!(1.0 - dotSY == 0.0)) {
      for (b = 0; b < nvar; b++) {
        yk_data[b] += (1.0 - dotSY) * workspace_data[b];
      }
    }

    dotSY = 0.0;
    if (nvar >= 1) {
      for (ix = 0; ix < b_tmp; ix++) {
        dotSY += sk_data[ix] * yk_data[ix];
      }
    }
  }

  success = ((curvatureS > 2.2204460492503131E-16) && (dotSY >
              2.2204460492503131E-16));
  if (success) {
    curvatureS = -1.0 / curvatureS;
    if (!(curvatureS == 0.0)) {
      ix = 0;
      for (b = 0; b < b_tmp; b++) {
        if (workspace_data[b] != 0.0) {
          real_T temp;
          temp = workspace_data[b] * curvatureS;
          b_ix = nvar + ix;
          for (b_jA = ix + 1; b_jA <= b_ix; b_jA++) {
            Bk[b_jA - 1] += workspace_data[(b_jA - ix) - 1] * temp;
          }
        }

        ix += 46;
      }
    }

    dotSY = 1.0 / dotSY;
    if (!(dotSY == 0.0)) {
      b_jA = 0;
      for (ix = 0; ix < b_tmp; ix++) {
        if (yk_data[ix] != 0.0) {
          curvatureS = yk_data[ix] * dotSY;
          b_ix = nvar + b_jA;
          for (b = b_jA + 1; b <= b_ix; b++) {
            Bk[b - 1] += yk_data[(b - b_jA) - 1] * curvatureS;
          }
        }

        b_jA += 46;
      }
    }
  }

  return success;
}

// Function for MATLAB Function: '<S2>/NLMPC'
void MPC_controller::factorQRE_o(s_LP9wk1co4RSPM0xk4tXznB *obj, int32_T mrows,
  int32_T ncols)
{
  if (mrows * ncols == 0) {
    obj->mrows = mrows;
    obj->ncols = ncols;
    obj->minRowCol = 0;
  } else {
    obj->usedPivoting = true;
    obj->mrows = mrows;
    obj->ncols = ncols;
    if (mrows <= ncols) {
      obj->minRowCol = mrows;
    } else {
      obj->minRowCol = ncols;
    }

    xgeqp3(obj->QR.data, obj->QR.size, mrows, ncols, obj->jpvt.data,
           obj->tau.data, &obj->tau.size);
  }
}

// Function for MATLAB Function: '<S2>/NLMPC'
void MPC_controller::countsort(int32_T x_data[], int32_T xLen, int32_T
  workspace_data[], int32_T xMin, int32_T xMax)
{
  if ((xLen > 1) && (xMax > xMin)) {
    int32_T idxEnd;
    int32_T idxEnd_tmp;
    int32_T idxStart;
    int32_T maxOffset_tmp;
    idxEnd_tmp = xMax - xMin;
    if (idxEnd_tmp >= 0) {
      std::memset(&workspace_data[0], 0, static_cast<uint32_T>(idxEnd_tmp + 1) *
                  sizeof(int32_T));
    }

    maxOffset_tmp = idxEnd_tmp - 1;
    for (idxStart = 0; idxStart < xLen; idxStart++) {
      idxEnd = x_data[idxStart] - xMin;
      workspace_data[idxEnd]++;
    }

    for (idxStart = 2; idxStart <= maxOffset_tmp + 2; idxStart++) {
      workspace_data[idxStart - 1] += workspace_data[idxStart - 2];
    }

    idxStart = 1;
    idxEnd = workspace_data[0];
    for (int32_T maxOffset{0}; maxOffset <= maxOffset_tmp; maxOffset++) {
      for (idxEnd_tmp = idxStart; idxEnd_tmp <= idxEnd; idxEnd_tmp++) {
        x_data[idxEnd_tmp - 1] = maxOffset + xMin;
      }

      idxStart = workspace_data[maxOffset] + 1;
      idxEnd = workspace_data[maxOffset + 1];
    }

    for (int32_T maxOffset{idxStart}; maxOffset <= idxEnd; maxOffset++) {
      x_data[maxOffset - 1] = xMax;
    }
  }
}

// Function for MATLAB Function: '<S2>/NLMPC'
void MPC_controller::removeConstr(s_YG0fmBFfsyHj5FdUrtbgBC *obj, int32_T
  idx_global)
{
  int32_T TYPE_tmp;
  int32_T b;
  int32_T idx_global_start_tmp_tmp;
  TYPE_tmp = obj->Wid.data[idx_global - 1] - 1;
  obj->isActiveConstr.data[(obj->isActiveIdx[TYPE_tmp] + obj->
    Wlocalidx.data[idx_global - 1]) - 2] = false;
  idx_global_start_tmp_tmp = obj->nActiveConstr - 1;
  obj->Wid.data[idx_global - 1] = obj->Wid.data[obj->nActiveConstr - 1];
  obj->Wlocalidx.data[idx_global - 1] = obj->
    Wlocalidx.data[idx_global_start_tmp_tmp];
  b = static_cast<uint8_T>(obj->nVar);
  for (int32_T idx{0}; idx < b; idx++) {
    obj->ATwset.data[idx + obj->ldA * (idx_global - 1)] = obj->ATwset.data
      [obj->ldA * idx_global_start_tmp_tmp + idx];
  }

  obj->bwset.data[idx_global - 1] = obj->bwset.data[idx_global_start_tmp_tmp];
  obj->nActiveConstr--;
  obj->nWConstr[TYPE_tmp]--;
}

// Function for MATLAB Function: '<S2>/NLMPC'
int32_T MPC_controller::RemoveDependentEq_(s_AiLncvKJfAMbGh9HSVCzlG *memspace,
  s_YG0fmBFfsyHj5FdUrtbgBC *workingset, s_LP9wk1co4RSPM0xk4tXznB *qrmanager)
{
  int32_T mTotalWorkingEq_tmp;
  int32_T mWorkingFixed;
  int32_T nDepInd;
  mWorkingFixed = workingset->nWConstr[0];
  mTotalWorkingEq_tmp = workingset->nWConstr[0] + workingset->nWConstr[1];
  nDepInd = 0;
  if (mTotalWorkingEq_tmp > 0) {
    real_T tol;
    int32_T c_tmp_tmp;
    int32_T iQR0;
    int32_T ix;
    int32_T nVar;
    int32_T totalRank;
    c_tmp_tmp = static_cast<uint8_T>(workingset->nVar);
    for (totalRank = 0; totalRank < mTotalWorkingEq_tmp; totalRank++) {
      for (nVar = 0; nVar < c_tmp_tmp; nVar++) {
        qrmanager->QR.data[totalRank + qrmanager->ldq * nVar] =
          workingset->ATwset.data[workingset->ldA * totalRank + nVar];
      }
    }

    nVar = mTotalWorkingEq_tmp - workingset->nVar;
    if (nVar > 0) {
      nDepInd = nVar;
    }

    std::memset(&qrmanager->jpvt.data[0], 0, static_cast<uint32_T>(c_tmp_tmp) *
                sizeof(int32_T));
    factorQRE_o(qrmanager, mTotalWorkingEq_tmp, workingset->nVar);
    tol = 100.0 * static_cast<real_T>(workingset->nVar) * 2.2204460492503131E-16;
    if (workingset->nVar <= mTotalWorkingEq_tmp) {
      totalRank = workingset->nVar;
    } else {
      totalRank = mTotalWorkingEq_tmp;
    }

    totalRank += (totalRank - 1) * qrmanager->ldq;
    while ((totalRank > 0) && (std::abs(qrmanager->QR.data[totalRank - 1]) < tol))
    {
      totalRank = (totalRank - qrmanager->ldq) - 1;
      nDepInd++;
    }

    if (nDepInd > 0) {
      boolean_T exitg1;
      totalRank = qrmanager->minRowCol;
      for (nVar = 0; nVar < totalRank; nVar++) {
        iQR0 = qrmanager->ldq * nVar + nVar;
        ix = qrmanager->mrows - nVar;
        if (ix - 2 >= 0) {
          std::memcpy(&qrmanager->Q.data[iQR0 + 1], &qrmanager->QR.data[iQR0 + 1],
                      static_cast<uint32_T>(((ix + iQR0) - iQR0) - 1) * sizeof
                      (real_T));
        }
      }

      xorgqr(qrmanager->mrows, qrmanager->mrows, qrmanager->minRowCol,
             qrmanager->Q.data, qrmanager->Q.size, qrmanager->ldq,
             qrmanager->tau.data);
      iQR0 = 0;
      exitg1 = false;
      while ((!exitg1) && (iQR0 <= nDepInd - 1)) {
        real_T qtb;
        ix = ((mTotalWorkingEq_tmp - iQR0) - 1) * qrmanager->ldq;
        qtb = 0.0;
        for (nVar = 0; nVar < mTotalWorkingEq_tmp; nVar++) {
          qtb += qrmanager->Q.data[ix + nVar] * workingset->bwset.data[nVar];
        }

        if (std::abs(qtb) >= tol) {
          nDepInd = -1;
          exitg1 = true;
        } else {
          iQR0++;
        }
      }
    }

    if (nDepInd > 0) {
      for (totalRank = 0; totalRank < mTotalWorkingEq_tmp; totalRank++) {
        iQR0 = qrmanager->ldq * totalRank;
        ix = workingset->ldA * totalRank;
        for (nVar = 0; nVar < c_tmp_tmp; nVar++) {
          qrmanager->QR.data[iQR0 + nVar] = workingset->ATwset.data[ix + nVar];
        }
      }

      for (nVar = 0; nVar < mWorkingFixed; nVar++) {
        qrmanager->jpvt.data[nVar] = 1;
      }

      nVar = workingset->nWConstr[0] + 1;
      if (nVar <= mTotalWorkingEq_tmp) {
        std::memset(&qrmanager->jpvt.data[nVar + -1], 0, static_cast<uint32_T>
                    ((mTotalWorkingEq_tmp - nVar) + 1) * sizeof(int32_T));
      }

      factorQRE_o(qrmanager, workingset->nVar, mTotalWorkingEq_tmp);
      for (mWorkingFixed = 0; mWorkingFixed < nDepInd; mWorkingFixed++) {
        memspace->workspace_int.data[mWorkingFixed] = qrmanager->jpvt.data
          [(mTotalWorkingEq_tmp - nDepInd) + mWorkingFixed];
      }

      countsort(memspace->workspace_int.data, nDepInd,
                memspace->workspace_sort.data, 1, mTotalWorkingEq_tmp);
      for (totalRank = nDepInd; totalRank >= 1; totalRank--) {
        nVar = workingset->nWConstr[0] + workingset->nWConstr[1];
        if (nVar != 0) {
          iQR0 = memspace->workspace_int.data[totalRank - 1];
          if (iQR0 <= nVar) {
            if ((nVar == workingset->nActiveConstr) || (iQR0 == nVar)) {
              workingset->mEqRemoved++;
              workingset->indexEqRemoved[workingset->mEqRemoved - 1] =
                workingset->Wlocalidx.data[memspace->
                workspace_int.data[totalRank - 1] - 1];
              removeConstr(workingset, memspace->workspace_int.data[totalRank -
                           1]);
            } else {
              workingset->mEqRemoved++;
              mTotalWorkingEq_tmp = workingset->Wid.data[iQR0 - 1] - 1;
              workingset->indexEqRemoved[workingset->mEqRemoved - 1] =
                workingset->Wlocalidx.data[iQR0 - 1];
              workingset->isActiveConstr.data[(workingset->
                isActiveIdx[workingset->Wid.data[iQR0 - 1] - 1] +
                workingset->Wlocalidx.data[iQR0 - 1]) - 2] = false;
              workingset->Wid.data[iQR0 - 1] = workingset->Wid.data[nVar - 1];
              workingset->Wlocalidx.data[iQR0 - 1] = workingset->
                Wlocalidx.data[nVar - 1];
              c_tmp_tmp = static_cast<uint8_T>(workingset->nVar);
              for (mWorkingFixed = 0; mWorkingFixed < c_tmp_tmp; mWorkingFixed++)
              {
                workingset->ATwset.data[mWorkingFixed + workingset->ldA * (iQR0
                  - 1)] = workingset->ATwset.data[(nVar - 1) * workingset->ldA +
                  mWorkingFixed];
              }

              workingset->bwset.data[iQR0 - 1] = workingset->bwset.data[nVar - 1];
              c_tmp_tmp = workingset->nActiveConstr - 1;
              workingset->Wid.data[nVar - 1] = workingset->Wid.data
                [workingset->nActiveConstr - 1];
              workingset->Wlocalidx.data[nVar - 1] = workingset->
                Wlocalidx.data[c_tmp_tmp];
              iQR0 = static_cast<uint8_T>(workingset->nVar);
              for (mWorkingFixed = 0; mWorkingFixed < iQR0; mWorkingFixed++) {
                workingset->ATwset.data[mWorkingFixed + workingset->ldA * (nVar
                  - 1)] = workingset->ATwset.data[workingset->ldA * c_tmp_tmp +
                  mWorkingFixed];
              }

              workingset->bwset.data[nVar - 1] = workingset->
                bwset.data[c_tmp_tmp];
              workingset->nActiveConstr--;
              workingset->nWConstr[mTotalWorkingEq_tmp]--;
            }
          }
        }
      }
    }
  }

  return nDepInd;
}

// Function for MATLAB Function: '<S2>/NLMPC'
void MPC_controller::RemoveDependentIneq_(s_YG0fmBFfsyHj5FdUrtbgBC *workingset,
  s_LP9wk1co4RSPM0xk4tXznB *qrmanager, s_AiLncvKJfAMbGh9HSVCzlG *memspace)
{
  int32_T nActiveConstr_tmp;
  int32_T nFixedConstr;
  int32_T nVar;
  nActiveConstr_tmp = workingset->nActiveConstr;
  nFixedConstr = workingset->nWConstr[0] + workingset->nWConstr[1];
  nVar = workingset->nVar;
  if ((workingset->nWConstr[2] + workingset->nWConstr[3]) + workingset->
      nWConstr[4] > 0) {
    real_T tol;
    int32_T nActiveConstr;
    int32_T nDepIneq;
    tol = 100.0 * static_cast<real_T>(workingset->nVar) * 2.2204460492503131E-16;
    for (nDepIneq = 0; nDepIneq < nFixedConstr; nDepIneq++) {
      qrmanager->jpvt.data[nDepIneq] = 1;
    }

    if (nFixedConstr + 1 <= nActiveConstr_tmp) {
      std::memset(&qrmanager->jpvt.data[nFixedConstr], 0, static_cast<uint32_T>
                  (nActiveConstr_tmp - nFixedConstr) * sizeof(int32_T));
    }

    for (nDepIneq = 0; nDepIneq < nActiveConstr_tmp; nDepIneq++) {
      int32_T c;
      int32_T ix0;
      int32_T iy0;
      iy0 = qrmanager->ldq * nDepIneq;
      ix0 = workingset->ldA * nDepIneq;
      c = static_cast<uint8_T>(nVar);
      for (nActiveConstr = 0; nActiveConstr < c; nActiveConstr++) {
        qrmanager->QR.data[iy0 + nActiveConstr] = workingset->ATwset.data[ix0 +
          nActiveConstr];
      }
    }

    factorQRE_o(qrmanager, workingset->nVar, workingset->nActiveConstr);
    nDepIneq = 0;
    for (nActiveConstr = workingset->nActiveConstr - 1; nActiveConstr + 1 > nVar;
         nActiveConstr--) {
      nDepIneq++;
      memspace->workspace_int.data[nDepIneq - 1] = qrmanager->
        jpvt.data[nActiveConstr];
    }

    if (nActiveConstr + 1 <= workingset->nVar) {
      nVar = qrmanager->ldq * nActiveConstr + nActiveConstr;
      while ((nActiveConstr + 1 > nFixedConstr) && (std::abs(qrmanager->
               QR.data[nVar]) < tol)) {
        nDepIneq++;
        memspace->workspace_int.data[nDepIneq - 1] = qrmanager->
          jpvt.data[nActiveConstr];
        nActiveConstr--;
        nVar = (nVar - qrmanager->ldq) - 1;
      }
    }

    countsort(memspace->workspace_int.data, nDepIneq,
              memspace->workspace_sort.data, nFixedConstr + 1,
              workingset->nActiveConstr);
    for (nFixedConstr = nDepIneq; nFixedConstr >= 1; nFixedConstr--) {
      removeConstr(workingset, memspace->workspace_int.data[nFixedConstr - 1]);
    }
  }
}

// Function for MATLAB Function: '<S2>/NLMPC'
void MPC_controller::xgeqrf(real_T A_data[], const int32_T A_size[2], int32_T m,
  int32_T n, real_T tau_data[], int32_T *tau_size)
{
  int32_T minmana;
  int32_T minmn;
  if (A_size[0] <= A_size[1]) {
    minmana = A_size[0];
  } else {
    minmana = A_size[1];
  }

  if (m <= n) {
    minmn = m;
  } else {
    minmn = n;
  }

  *tau_size = minmana;
  if (minmana - 1 >= 0) {
    std::memset(&tau_data[0], 0, static_cast<uint32_T>(minmana) * sizeof(real_T));
  }

  if (minmn >= 1) {
    qrf(A_data, A_size, m, n, minmn, tau_data);
  }
}

// Function for MATLAB Function: '<S2>/NLMPC'
void MPC_controller::factorQR_p(s_LP9wk1co4RSPM0xk4tXznB *obj, const real_T
  A_data[], int32_T mrows, int32_T ncols, int32_T ldA)
{
  int32_T idx;
  boolean_T guard1{ false };

  idx = mrows * ncols;
  guard1 = false;
  if (idx > 0) {
    for (idx = 0; idx < ncols; idx++) {
      int32_T b;
      int32_T ix0;
      int32_T iy0;
      ix0 = ldA * idx;
      iy0 = obj->ldq * idx;
      b = static_cast<uint8_T>(mrows);
      for (int32_T k{0}; k < b; k++) {
        obj->QR.data[iy0 + k] = A_data[ix0 + k];
      }
    }

    guard1 = true;
  } else if (idx == 0) {
    obj->mrows = mrows;
    obj->ncols = ncols;
    obj->minRowCol = 0;
  } else {
    guard1 = true;
  }

  if (guard1) {
    obj->usedPivoting = false;
    obj->mrows = mrows;
    obj->ncols = ncols;
    for (idx = 0; idx < ncols; idx++) {
      obj->jpvt.data[idx] = idx + 1;
    }

    if (mrows <= ncols) {
      obj->minRowCol = mrows;
    } else {
      obj->minRowCol = ncols;
    }

    xgeqrf(obj->QR.data, obj->QR.size, mrows, ncols, obj->tau.data,
           &obj->tau.size);
  }
}

// Function for MATLAB Function: '<S2>/NLMPC'
void MPC_controller::factorQR(s_LP9wk1co4RSPM0xk4tXznB *obj, int32_T mrows,
  int32_T ncols)
{
  int32_T b;
  obj->usedPivoting = false;
  obj->mrows = mrows;
  obj->ncols = ncols;
  b = static_cast<uint8_T>(ncols);
  for (int32_T idx{0}; idx < b; idx++) {
    obj->jpvt.data[idx] = idx + 1;
  }

  if (mrows <= ncols) {
    obj->minRowCol = mrows;
  } else {
    obj->minRowCol = ncols;
  }

  xgeqrf(obj->QR.data, obj->QR.size, mrows, ncols, obj->tau.data, &obj->tau.size);
}

// Function for MATLAB Function: '<S2>/NLMPC'
void MPC_controller::xgemv_dff(int32_T m, int32_T n, const real_T A_data[],
  int32_T lda, const real_T x_data[], real_T y_data[])
{
  if (n != 0) {
    int32_T b;
    int32_T d;
    int32_T iy;
    b = static_cast<uint8_T>(n);
    for (int32_T b_iy{0}; b_iy < b; b_iy++) {
      y_data[b_iy] = -y_data[b_iy];
    }

    iy = 0;
    d = (n - 1) * lda + 1;
    for (int32_T b_iy{1}; lda < 0 ? b_iy >= d : b_iy <= d; b_iy += lda) {
      real_T c;
      int32_T e;
      c = 0.0;
      e = b_iy + m;
      for (b = b_iy; b < e; b++) {
        c += x_data[b - b_iy] * A_data[b - 1];
      }

      y_data[iy] += c;
      iy++;
    }
  }
}

// Function for MATLAB Function: '<S2>/NLMPC'
void MPC_controller::xgemv_df(int32_T n, const real_T A_data[], int32_T lda,
  const real_T x_data[], real_T y_data[])
{
  if (n != 0) {
    int32_T b;
    int32_T d;
    int32_T iy;
    b = static_cast<uint8_T>(n);
    for (int32_T b_iy{0}; b_iy < b; b_iy++) {
      y_data[b_iy] = -y_data[b_iy];
    }

    iy = 0;
    d = (n - 1) * lda + 1;
    for (int32_T b_iy{1}; lda < 0 ? b_iy >= d : b_iy <= d; b_iy += lda) {
      real_T c;
      c = 0.0;
      for (b = b_iy; b <= b_iy + 45; b++) {
        c += x_data[b - b_iy] * A_data[b - 1];
      }

      y_data[iy] += c;
      iy++;
    }
  }
}

// Function for MATLAB Function: '<S2>/NLMPC'
real_T MPC_controller::maxConstraintViolation(s_YG0fmBFfsyHj5FdUrtbgBC *obj,
  const real_T x_data[])
{
  real_T v;
  int32_T g;
  int32_T mFixed;
  int32_T mLB;
  int32_T mUB;
  mLB = obj->sizes[3];
  mUB = obj->sizes[4];
  mFixed = obj->sizes[0];
  if (obj->probType == 2) {
    int32_T k;
    v = 0.0;
    if (obj->Aineq.size != 0) {
      g = static_cast<uint16_T>(obj->sizes[2]);
      if (g - 1 >= 0) {
        std::memcpy(&obj->maxConstrWorkspace.data[0], &obj->bineq.data[0],
                    static_cast<uint32_T>(g) * sizeof(real_T));
      }

      xgemv_df(obj->sizes[2], obj->Aineq.data, obj->ldA, x_data,
               obj->maxConstrWorkspace.data);
      k = static_cast<uint8_T>(obj->sizes[2]);
      for (g = 0; g < k; g++) {
        obj->maxConstrWorkspace.data[g] -= x_data[g + 46];
        v = std::fmax(v, obj->maxConstrWorkspace.data[g]);
      }
    }

    std::memcpy(&obj->maxConstrWorkspace.data[0], &obj->beq[0], 40U * sizeof
                (real_T));
    xgemv_df(40, obj->Aeq.data, obj->ldA, x_data, obj->maxConstrWorkspace.data);
    for (g = 0; g < 40; g++) {
      k = obj->sizes[2] + g;
      obj->maxConstrWorkspace.data[g] = (obj->maxConstrWorkspace.data[g] -
        x_data[k + 46]) + x_data[k + 86];
      v = std::fmax(v, std::abs(obj->maxConstrWorkspace.data[g]));
    }
  } else {
    v = 0.0;
    if (obj->Aineq.size != 0) {
      g = static_cast<uint16_T>(obj->sizes[2]);
      if (g - 1 >= 0) {
        std::memcpy(&obj->maxConstrWorkspace.data[0], &obj->bineq.data[0],
                    static_cast<uint32_T>(g) * sizeof(real_T));
      }

      xgemv_dff(obj->nVar, obj->sizes[2], obj->Aineq.data, obj->ldA, x_data,
                obj->maxConstrWorkspace.data);
      g = static_cast<uint8_T>(obj->sizes[2]);
      for (int32_T k{0}; k < g; k++) {
        v = std::fmax(v, obj->maxConstrWorkspace.data[k]);
      }
    }

    std::memcpy(&obj->maxConstrWorkspace.data[0], &obj->beq[0], 40U * sizeof
                (real_T));
    xgemv_dff(obj->nVar, 40, obj->Aeq.data, obj->ldA, x_data,
              obj->maxConstrWorkspace.data);
    for (int32_T k{0}; k < 40; k++) {
      v = std::fmax(v, std::abs(obj->maxConstrWorkspace.data[k]));
    }
  }

  if (mLB > 0) {
    g = static_cast<uint16_T>(mLB);
    for (mLB = 0; mLB < g; mLB++) {
      v = std::fmax(v, -x_data[obj->indexLB.data[mLB] - 1] - obj->lb.data
                    [obj->indexLB.data[mLB] - 1]);
    }
  }

  if (mUB > 0) {
    mLB = static_cast<uint8_T>(mUB);
    for (mUB = 0; mUB < mLB; mUB++) {
      v = std::fmax(v, x_data[obj->indexUB.data[mUB] - 1] - obj->ub.data
                    [obj->indexUB.data[mUB] - 1]);
    }
  }

  if (mFixed > 0) {
    mUB = static_cast<uint8_T>(mFixed);
    for (mFixed = 0; mFixed < mUB; mFixed++) {
      v = std::fmax(v, std::abs(x_data[obj->indexFixed.data[mFixed] - 1] -
        obj->ub.data[obj->indexFixed.data[mFixed] - 1]));
    }
  }

  return v;
}

// Function for MATLAB Function: '<S2>/NLMPC'
void MPC_controller::xgemv_dffo(int32_T m, int32_T n, const real_T A_data[],
  int32_T lda, const real_T x_data[], int32_T ix0, real_T y_data[])
{
  if (n != 0) {
    int32_T b;
    int32_T d;
    int32_T iy;
    b = static_cast<uint8_T>(n);
    for (int32_T b_iy{0}; b_iy < b; b_iy++) {
      y_data[b_iy] = -y_data[b_iy];
    }

    iy = 0;
    d = (n - 1) * lda + 1;
    for (int32_T b_iy{1}; lda < 0 ? b_iy >= d : b_iy <= d; b_iy += lda) {
      real_T c;
      int32_T e;
      c = 0.0;
      e = b_iy + m;
      for (b = b_iy; b < e; b++) {
        c += x_data[((ix0 + b) - b_iy) - 1] * A_data[b - 1];
      }

      y_data[iy] += c;
      iy++;
    }
  }
}

// Function for MATLAB Function: '<S2>/NLMPC'
real_T MPC_controller::maxConstraintViolation_i(s_YG0fmBFfsyHj5FdUrtbgBC *obj,
  const real_T x_data[], int32_T ix0)
{
  real_T v;
  int32_T g;
  int32_T mFixed;
  int32_T mLB;
  int32_T mUB;
  mLB = obj->sizes[3];
  mUB = obj->sizes[4];
  mFixed = obj->sizes[0];
  if (obj->probType == 2) {
    int32_T k;
    v = 0.0;
    if (obj->Aineq.size != 0) {
      g = static_cast<uint16_T>(obj->sizes[2]);
      if (g - 1 >= 0) {
        std::memcpy(&obj->maxConstrWorkspace.data[0], &obj->bineq.data[0],
                    static_cast<uint32_T>(g) * sizeof(real_T));
      }

      xgemv_dffo(46, obj->sizes[2], obj->Aineq.data, obj->ldA, x_data, ix0,
                 obj->maxConstrWorkspace.data);
      k = static_cast<uint8_T>(obj->sizes[2]);
      for (g = 0; g < k; g++) {
        obj->maxConstrWorkspace.data[g] -= x_data[(ix0 + g) + 45];
        v = std::fmax(v, obj->maxConstrWorkspace.data[g]);
      }
    }

    std::memcpy(&obj->maxConstrWorkspace.data[0], &obj->beq[0], 40U * sizeof
                (real_T));
    xgemv_dffo(46, 40, obj->Aeq.data, obj->ldA, x_data, ix0,
               obj->maxConstrWorkspace.data);
    for (g = 0; g < 40; g++) {
      k = (ix0 + obj->sizes[2]) + g;
      obj->maxConstrWorkspace.data[g] = (obj->maxConstrWorkspace.data[g] -
        x_data[k + 45]) + x_data[k + 85];
      v = std::fmax(v, std::abs(obj->maxConstrWorkspace.data[g]));
    }
  } else {
    v = 0.0;
    if (obj->Aineq.size != 0) {
      g = static_cast<uint16_T>(obj->sizes[2]);
      if (g - 1 >= 0) {
        std::memcpy(&obj->maxConstrWorkspace.data[0], &obj->bineq.data[0],
                    static_cast<uint32_T>(g) * sizeof(real_T));
      }

      xgemv_dffo(obj->nVar, obj->sizes[2], obj->Aineq.data, obj->ldA, x_data,
                 ix0, obj->maxConstrWorkspace.data);
      g = static_cast<uint8_T>(obj->sizes[2]);
      for (int32_T k{0}; k < g; k++) {
        v = std::fmax(v, obj->maxConstrWorkspace.data[k]);
      }
    }

    std::memcpy(&obj->maxConstrWorkspace.data[0], &obj->beq[0], 40U * sizeof
                (real_T));
    xgemv_dffo(obj->nVar, 40, obj->Aeq.data, obj->ldA, x_data, ix0,
               obj->maxConstrWorkspace.data);
    for (int32_T k{0}; k < 40; k++) {
      v = std::fmax(v, std::abs(obj->maxConstrWorkspace.data[k]));
    }
  }

  if (mLB > 0) {
    g = static_cast<uint16_T>(mLB);
    for (mLB = 0; mLB < g; mLB++) {
      v = std::fmax(v, -x_data[(ix0 + obj->indexLB.data[mLB]) - 2] -
                    obj->lb.data[obj->indexLB.data[mLB] - 1]);
    }
  }

  if (mUB > 0) {
    mLB = static_cast<uint8_T>(mUB);
    for (mUB = 0; mUB < mLB; mUB++) {
      v = std::fmax(v, x_data[(ix0 + obj->indexUB.data[mUB]) - 2] - obj->
                    ub.data[obj->indexUB.data[mUB] - 1]);
    }
  }

  if (mFixed > 0) {
    mUB = static_cast<uint8_T>(mFixed);
    for (mFixed = 0; mFixed < mUB; mFixed++) {
      v = std::fmax(v, std::abs(x_data[(ix0 + obj->indexFixed.data[mFixed]) - 2]
        - obj->ub.data[obj->indexFixed.data[mFixed] - 1]));
    }
  }

  return v;
}

// Function for MATLAB Function: '<S2>/NLMPC'
boolean_T MPC_controller::feasibleX0ForWorkingSet(real_T workspace_data[], const
  int32_T workspace_size[2], real_T xCurrent_data[], s_YG0fmBFfsyHj5FdUrtbgBC
  *workingset, s_LP9wk1co4RSPM0xk4tXznB *qrmanager)
{
  int32_T mWConstr;
  int32_T nVar;
  boolean_T nonDegenerateWset;
  mWConstr = workingset->nActiveConstr - 1;
  nVar = workingset->nVar;
  nonDegenerateWset = true;
  if (workingset->nActiveConstr != 0) {
    real_T c;
    int32_T d;
    int32_T e;
    int32_T ix;
    int32_T iy;
    int32_T ldq;
    int32_T ldw;
    for (ix = 0; ix <= mWConstr; ix++) {
      workspace_data[ix] = workingset->bwset.data[ix];
      workspace_data[ix + workspace_size[0]] = workingset->bwset.data[ix];
    }

    ldw = workingset->ldA;
    if (workingset->nActiveConstr != 0) {
      iy = 0;
      d = (workingset->nActiveConstr - 1) * workingset->ldA + 1;
      for (ldq = 1; ldw < 0 ? ldq >= d : ldq <= d; ldq += ldw) {
        c = 0.0;
        e = ldq + nVar;
        for (ix = ldq; ix < e; ix++) {
          c += workingset->ATwset.data[ix - 1] * xCurrent_data[ix - ldq];
        }

        workspace_data[iy] -= c;
        iy++;
      }
    }

    if (workingset->nActiveConstr >= workingset->nVar) {
      int32_T ar;
      int32_T iAcol;
      ldw = static_cast<uint8_T>(workingset->nVar);
      for (ix = 0; ix < ldw; ix++) {
        iy = qrmanager->ldq * ix;
        for (ldq = 0; ldq <= mWConstr; ldq++) {
          qrmanager->QR.data[ldq + iy] = workingset->ATwset.data[workingset->ldA
            * ldq + ix];
        }
      }

      factorQR(qrmanager, workingset->nActiveConstr, workingset->nVar);
      d = qrmanager->minRowCol;
      for (ldq = 0; ldq < d; ldq++) {
        ix = qrmanager->ldq * ldq + ldq;
        e = qrmanager->mrows - ldq;
        if (e - 2 >= 0) {
          std::memcpy(&qrmanager->Q.data[ix + 1], &qrmanager->QR.data[ix + 1],
                      static_cast<uint32_T>(((e + ix) - ix) - 1) * sizeof(real_T));
        }
      }

      xorgqr(qrmanager->mrows, qrmanager->mrows, qrmanager->minRowCol,
             qrmanager->Q.data, qrmanager->Q.size, qrmanager->ldq,
             qrmanager->tau.data);
      ldq = qrmanager->ldq;
      ldw = workspace_size[0];
      ix = workspace_size[0] * workspace_size[1];
      if (ix - 1 >= 0) {
        std::memcpy(&rtDW.B_data[0], &workspace_data[0], static_cast<uint32_T>
                    (ix) * sizeof(real_T));
      }

      for (ix = 0; ldw < 0 ? ix >= ldw : ix <= ldw; ix += ldw) {
        d = ix + nVar;
        for (iy = ix + 1; iy <= d; iy++) {
          workspace_data[iy - 1] = 0.0;
        }
      }

      iy = -1;
      for (d = 0; ldw < 0 ? d >= ldw : d <= ldw; d += ldw) {
        iAcol = -1;
        ar = d + nVar;
        for (ix = d + 1; ix <= ar; ix++) {
          c = 0.0;
          for (e = 0; e <= mWConstr; e++) {
            c += qrmanager->Q.data[(e + iAcol) + 1] * rtDW.B_data[(e + iy) + 1];
          }

          workspace_data[ix - 1] += c;
          iAcol += ldq;
        }

        iy += ldw;
      }

      for (mWConstr = 0; mWConstr < 2; mWConstr++) {
        iy = ldw * mWConstr - 1;
        for (ix = nVar; ix >= 1; ix--) {
          iAcol = (ix - 1) * ldq;
          if (workspace_data[ix + iy] != 0.0) {
            d = ix + iy;
            workspace_data[d] /= qrmanager->QR.data[(ix + iAcol) - 1];
            ar = static_cast<uint8_T>(ix - 1);
            for (e = 0; e < ar; e++) {
              int32_T c_tmp;
              c_tmp = (e + iy) + 1;
              workspace_data[c_tmp] -= qrmanager->QR.data[e + iAcol] *
                workspace_data[d];
            }
          }
        }
      }
    } else {
      int32_T ar;
      int32_T c_tmp;
      int32_T iAcol;
      factorQR_p(qrmanager, workingset->ATwset.data, workingset->nVar,
                 workingset->nActiveConstr, workingset->ldA);
      iy = qrmanager->minRowCol;
      for (ldq = 0; ldq < iy; ldq++) {
        ix = qrmanager->ldq * ldq + ldq;
        e = qrmanager->mrows - ldq;
        if (e - 2 >= 0) {
          std::memcpy(&qrmanager->Q.data[ix + 1], &qrmanager->QR.data[ix + 1],
                      static_cast<uint32_T>(((e + ix) - ix) - 1) * sizeof(real_T));
        }
      }

      xorgqr(qrmanager->mrows, qrmanager->minRowCol, qrmanager->minRowCol,
             qrmanager->Q.data, qrmanager->Q.size, qrmanager->ldq,
             qrmanager->tau.data);
      ldq = qrmanager->ldq;
      ldw = workspace_size[0];
      for (d = 0; d < 2; d++) {
        iy = ldw * d;
        for (ix = 0; ix <= mWConstr; ix++) {
          iAcol = ldq * ix;
          c_tmp = ix + iy;
          c = workspace_data[c_tmp];
          ar = static_cast<uint8_T>(ix);
          for (e = 0; e < ar; e++) {
            c -= qrmanager->QR.data[e + iAcol] * workspace_data[e + iy];
          }

          workspace_data[c_tmp] = c / qrmanager->QR.data[ix + iAcol];
        }
      }

      ix = workspace_size[0] * workspace_size[1];
      if (ix - 1 >= 0) {
        std::memcpy(&rtDW.B_data[0], &workspace_data[0], static_cast<uint32_T>
                    (ix) * sizeof(real_T));
      }

      for (ix = 0; ldw < 0 ? ix >= ldw : ix <= ldw; ix += ldw) {
        d = ix + nVar;
        for (iy = ix + 1; iy <= d; iy++) {
          workspace_data[iy - 1] = 0.0;
        }
      }

      iAcol = 1;
      for (ix = 0; ldw < 0 ? ix >= ldw : ix <= ldw; ix += ldw) {
        ar = -1;
        d = iAcol + mWConstr;
        for (e = iAcol; e <= d; e++) {
          c_tmp = ix + nVar;
          for (iy = ix + 1; iy <= c_tmp; iy++) {
            workspace_data[iy - 1] += qrmanager->Q.data[(ar + iy) - ix] *
              rtDW.B_data[e - 1];
          }

          ar += ldq;
        }

        iAcol += ldw;
      }
    }

    mWConstr = 0;
    int32_T exitg1;
    do {
      exitg1 = 0;
      if (mWConstr <= static_cast<uint8_T>(nVar) - 1) {
        c = workspace_data[mWConstr];
        if (std::isinf(c) || std::isnan(c)) {
          nonDegenerateWset = false;
          exitg1 = 1;
        } else {
          c = workspace_data[mWConstr + workspace_size[0]];
          if (std::isinf(c) || std::isnan(c)) {
            nonDegenerateWset = false;
            exitg1 = 1;
          } else {
            mWConstr++;
          }
        }
      } else {
        real_T constrViolation_basicX;
        for (mWConstr = 0; mWConstr < nVar; mWConstr++) {
          workspace_data[mWConstr] += xCurrent_data[mWConstr];
        }

        c = maxConstraintViolation(workingset, workspace_data);
        constrViolation_basicX = maxConstraintViolation_i(workingset,
          workspace_data, workspace_size[0] + 1);
        if ((c <= 2.2204460492503131E-16) || (c < constrViolation_basicX)) {
          std::memcpy(&xCurrent_data[0], &workspace_data[0], static_cast<uint8_T>
                      (nVar) * sizeof(real_T));
        } else {
          mWConstr = static_cast<uint8_T>(nVar);
          for (nVar = 0; nVar < mWConstr; nVar++) {
            xCurrent_data[nVar] = workspace_data[workspace_size[0] + nVar];
          }
        }

        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }

  return nonDegenerateWset;
}

// Function for MATLAB Function: '<S2>/NLMPC'
void MPC_controller::RemoveDependentIneq__b(s_YG0fmBFfsyHj5FdUrtbgBC *workingset,
  s_LP9wk1co4RSPM0xk4tXznB *qrmanager, s_AiLncvKJfAMbGh9HSVCzlG *memspace)
{
  int32_T nActiveConstr_tmp;
  int32_T nFixedConstr;
  int32_T nVar;
  nActiveConstr_tmp = workingset->nActiveConstr;
  nFixedConstr = workingset->nWConstr[0] + workingset->nWConstr[1];
  nVar = workingset->nVar;
  if ((workingset->nWConstr[2] + workingset->nWConstr[3]) + workingset->
      nWConstr[4] > 0) {
    real_T tol;
    int32_T nActiveConstr;
    int32_T nDepIneq;
    tol = 1000.0 * static_cast<real_T>(workingset->nVar) *
      2.2204460492503131E-16;
    for (nDepIneq = 0; nDepIneq < nFixedConstr; nDepIneq++) {
      qrmanager->jpvt.data[nDepIneq] = 1;
    }

    if (nFixedConstr + 1 <= nActiveConstr_tmp) {
      std::memset(&qrmanager->jpvt.data[nFixedConstr], 0, static_cast<uint32_T>
                  (nActiveConstr_tmp - nFixedConstr) * sizeof(int32_T));
    }

    for (nDepIneq = 0; nDepIneq < nActiveConstr_tmp; nDepIneq++) {
      int32_T c;
      int32_T ix0;
      int32_T iy0;
      iy0 = qrmanager->ldq * nDepIneq;
      ix0 = workingset->ldA * nDepIneq;
      c = static_cast<uint8_T>(nVar);
      for (nActiveConstr = 0; nActiveConstr < c; nActiveConstr++) {
        qrmanager->QR.data[iy0 + nActiveConstr] = workingset->ATwset.data[ix0 +
          nActiveConstr];
      }
    }

    factorQRE_o(qrmanager, workingset->nVar, workingset->nActiveConstr);
    nDepIneq = 0;
    for (nActiveConstr = workingset->nActiveConstr - 1; nActiveConstr + 1 > nVar;
         nActiveConstr--) {
      nDepIneq++;
      memspace->workspace_int.data[nDepIneq - 1] = qrmanager->
        jpvt.data[nActiveConstr];
    }

    if (nActiveConstr + 1 <= workingset->nVar) {
      nVar = qrmanager->ldq * nActiveConstr + nActiveConstr;
      while ((nActiveConstr + 1 > nFixedConstr) && (std::abs(qrmanager->
               QR.data[nVar]) < tol)) {
        nDepIneq++;
        memspace->workspace_int.data[nDepIneq - 1] = qrmanager->
          jpvt.data[nActiveConstr];
        nActiveConstr--;
        nVar = (nVar - qrmanager->ldq) - 1;
      }
    }

    countsort(memspace->workspace_int.data, nDepIneq,
              memspace->workspace_sort.data, nFixedConstr + 1,
              workingset->nActiveConstr);
    for (nFixedConstr = nDepIneq; nFixedConstr >= 1; nFixedConstr--) {
      removeConstr(workingset, memspace->workspace_int.data[nFixedConstr - 1]);
    }
  }
}

// Function for MATLAB Function: '<S2>/NLMPC'
void MPC_controller::xgemv_dffoyl(int32_T m, int32_T n, const real_T A_data[],
  int32_T lda, const real_T x_data[], real_T y_data[])
{
  if (n != 0) {
    int32_T b;
    int32_T d;
    int32_T iy;
    b = static_cast<uint8_T>(n);
    for (int32_T b_iy{0}; b_iy < b; b_iy++) {
      y_data[b_iy] = -y_data[b_iy];
    }

    iy = 0;
    d = (n - 1) * lda + 1;
    for (int32_T b_iy{1}; lda < 0 ? b_iy >= d : b_iy <= d; b_iy += lda) {
      real_T c;
      int32_T e;
      c = 0.0;
      e = b_iy + m;
      for (b = b_iy; b < e; b++) {
        c += A_data[b - 1] * x_data[b - b_iy];
      }

      y_data[iy] += c;
      iy++;
    }
  }
}

// Function for MATLAB Function: '<S2>/NLMPC'
void MPC_controller::xgemv_dffoy(int32_T n, const real_T A_data[], int32_T lda,
  const real_T x_data[], real_T y_data[])
{
  if (n != 0) {
    int32_T b;
    int32_T d;
    int32_T iy;
    b = static_cast<uint8_T>(n);
    for (int32_T b_iy{0}; b_iy < b; b_iy++) {
      y_data[b_iy] = -y_data[b_iy];
    }

    iy = 0;
    d = (n - 1) * lda + 1;
    for (int32_T b_iy{1}; lda < 0 ? b_iy >= d : b_iy <= d; b_iy += lda) {
      real_T c;
      c = 0.0;
      for (b = b_iy; b <= b_iy + 45; b++) {
        c += A_data[b - 1] * x_data[b - b_iy];
      }

      y_data[iy] += c;
      iy++;
    }
  }
}

// Function for MATLAB Function: '<S2>/NLMPC'
real_T MPC_controller::maxConstraintViolation_in(s_YG0fmBFfsyHj5FdUrtbgBC *obj,
  const real_T x_data[])
{
  real_T v;
  int32_T k;
  int32_T mFixed;
  int32_T mLB;
  int32_T mUB;
  mLB = obj->sizes[3];
  mUB = obj->sizes[4];
  mFixed = obj->sizes[0];
  if (obj->probType == 2) {
    int32_T g;
    v = 0.0;
    if (obj->Aineq.size != 0) {
      g = static_cast<uint16_T>(obj->sizes[2]);
      if (g - 1 >= 0) {
        std::memcpy(&obj->maxConstrWorkspace.data[0], &obj->bineq.data[0],
                    static_cast<uint32_T>(g) * sizeof(real_T));
      }

      xgemv_dffoy(obj->sizes[2], obj->Aineq.data, obj->ldA, x_data,
                  obj->maxConstrWorkspace.data);
      g = static_cast<uint8_T>(obj->sizes[2]);
      for (k = 0; k < g; k++) {
        obj->maxConstrWorkspace.data[k] -= x_data[k + 46];
        v = std::fmax(v, obj->maxConstrWorkspace.data[k]);
      }
    }

    std::memcpy(&obj->maxConstrWorkspace.data[0], &obj->beq[0], 40U * sizeof
                (real_T));
    xgemv_dffoy(40, obj->Aeq.data, obj->ldA, x_data,
                obj->maxConstrWorkspace.data);
    for (k = 0; k < 40; k++) {
      g = obj->sizes[2] + k;
      obj->maxConstrWorkspace.data[k] = (obj->maxConstrWorkspace.data[k] -
        x_data[g + 46]) + x_data[g + 86];
      v = std::fmax(v, std::abs(obj->maxConstrWorkspace.data[k]));
    }
  } else {
    v = 0.0;
    if (obj->Aineq.size != 0) {
      int32_T g;
      g = static_cast<uint16_T>(obj->sizes[2]);
      if (g - 1 >= 0) {
        std::memcpy(&obj->maxConstrWorkspace.data[0], &obj->bineq.data[0],
                    static_cast<uint32_T>(g) * sizeof(real_T));
      }

      xgemv_dffoyl(obj->nVar, obj->sizes[2], obj->Aineq.data, obj->ldA, x_data,
                   obj->maxConstrWorkspace.data);
      g = static_cast<uint8_T>(obj->sizes[2]);
      for (k = 0; k < g; k++) {
        v = std::fmax(v, obj->maxConstrWorkspace.data[k]);
      }
    }

    std::memcpy(&obj->maxConstrWorkspace.data[0], &obj->beq[0], 40U * sizeof
                (real_T));
    xgemv_dffoyl(obj->nVar, 40, obj->Aeq.data, obj->ldA, x_data,
                 obj->maxConstrWorkspace.data);
    for (k = 0; k < 40; k++) {
      v = std::fmax(v, std::abs(obj->maxConstrWorkspace.data[k]));
    }
  }

  if (mLB > 0) {
    k = static_cast<uint16_T>(mLB);
    for (mLB = 0; mLB < k; mLB++) {
      v = std::fmax(v, -x_data[obj->indexLB.data[mLB] - 1] - obj->lb.data
                    [obj->indexLB.data[mLB] - 1]);
    }
  }

  if (mUB > 0) {
    mLB = static_cast<uint8_T>(mUB);
    for (mUB = 0; mUB < mLB; mUB++) {
      v = std::fmax(v, x_data[obj->indexUB.data[mUB] - 1] - obj->ub.data
                    [obj->indexUB.data[mUB] - 1]);
    }
  }

  if (mFixed > 0) {
    mUB = static_cast<uint8_T>(mFixed);
    for (mFixed = 0; mFixed < mUB; mFixed++) {
      v = std::fmax(v, std::abs(x_data[obj->indexFixed.data[mFixed] - 1] -
        obj->ub.data[obj->indexFixed.data[mFixed] - 1]));
    }
  }

  return v;
}

// Function for MATLAB Function: '<S2>/NLMPC'
void MPC_controller::PresolveWorkingSet(s_aAq9pdCdNustb4CQC7xpeC *solution,
  s_AiLncvKJfAMbGh9HSVCzlG *memspace, s_YG0fmBFfsyHj5FdUrtbgBC *workingset,
  s_LP9wk1co4RSPM0xk4tXznB *qrmanager)
{
  int32_T b;
  solution->state = 82;
  b = RemoveDependentEq_(memspace, workingset, qrmanager);
  if ((b != -1) && (workingset->nActiveConstr <= qrmanager->ldq)) {
    boolean_T guard1{ false };

    boolean_T okWorkingSet;
    RemoveDependentIneq_(workingset, qrmanager, memspace);
    okWorkingSet = feasibleX0ForWorkingSet(memspace->workspace_double.data,
      memspace->workspace_double.size, solution->xstar.data, workingset,
      qrmanager);
    guard1 = false;
    if (!okWorkingSet) {
      RemoveDependentIneq__b(workingset, qrmanager, memspace);
      okWorkingSet = feasibleX0ForWorkingSet(memspace->workspace_double.data,
        memspace->workspace_double.size, solution->xstar.data, workingset,
        qrmanager);
      if (!okWorkingSet) {
        solution->state = -7;
      } else {
        guard1 = true;
      }
    } else {
      guard1 = true;
    }

    if (guard1) {
      if (workingset->nWConstr[0] + workingset->nWConstr[1] == workingset->nVar)
      {
        real_T constrViolation;
        constrViolation = maxConstraintViolation_in(workingset,
          solution->xstar.data);
        if (constrViolation > 1.0E-6) {
          solution->state = -2;
        }
      }
    }
  } else {
    int32_T idxEndIneq;
    int32_T idxStartIneq;
    solution->state = -3;
    idxStartIneq = (workingset->nWConstr[0] + workingset->nWConstr[1]) + 1;
    idxEndIneq = workingset->nActiveConstr;
    for (b = idxStartIneq; b <= idxEndIneq; b++) {
      workingset->isActiveConstr.data[(workingset->isActiveIdx
        [workingset->Wid.data[b - 1] - 1] + workingset->Wlocalidx.data[b - 1]) -
        2] = false;
    }

    workingset->nWConstr[2] = 0;
    workingset->nWConstr[3] = 0;
    workingset->nWConstr[4] = 0;
    workingset->nActiveConstr = workingset->nWConstr[0] + workingset->nWConstr[1];
  }
}

// Function for MATLAB Function: '<S2>/NLMPC'
void MPC_controller::xgemv_dffoyl1(int32_T m, int32_T n, const real_T A[2116],
  int32_T lda, const real_T x_data[], real_T y_data[])
{
  if ((m != 0) && (n != 0)) {
    int32_T c;
    int32_T ix;
    std::memset(&y_data[0], 0, static_cast<uint8_T>(m) * sizeof(real_T));
    ix = 0;
    c = (n - 1) * lda + 1;
    for (int32_T b_iy{1}; lda < 0 ? b_iy >= c : b_iy <= c; b_iy += lda) {
      int32_T d;
      d = b_iy + m;
      for (int32_T b{b_iy}; b < d; b++) {
        int32_T tmp;
        tmp = b - b_iy;
        y_data[tmp] += A[b - 1] * x_data[ix];
      }

      ix++;
    }
  }
}

// Function for MATLAB Function: '<S2>/NLMPC'
void MPC_controller::computeGrad_StoreHx(s_4B8jbk60U8ZWFI1LxShFzC *obj, const
  real_T H[2116], const real_T f_data[], const real_T x_data[])
{
  switch (obj->objtype) {
   case 5:
    if (obj->nvar - 2 >= 0) {
      std::memset(&obj->grad.data[0], 0, static_cast<uint32_T>(obj->nvar - 1) *
                  sizeof(real_T));
    }

    obj->grad.data[obj->nvar - 1] = obj->gammaScalar;
    break;

   case 3:
    {
      xgemv_dffoyl1(obj->nvar, obj->nvar, H, obj->nvar, x_data, obj->Hx.data);
      if (static_cast<uint8_T>(obj->nvar) - 1 >= 0) {
        std::memcpy(&obj->grad.data[0], &obj->Hx.data[0], static_cast<uint8_T>
                    (obj->nvar) * sizeof(real_T));
      }

      if (obj->hasLinear && (obj->nvar >= 1)) {
        int32_T maxRegVar;
        maxRegVar = obj->nvar - 1;
        for (int32_T idx{0}; idx <= maxRegVar; idx++) {
          obj->grad.data[idx] += f_data[idx];
        }
      }
    }
    break;

   default:
    {
      int32_T iy;
      int32_T maxRegVar;
      maxRegVar = obj->maxVar - 1;
      xgemv_dffoyl1(obj->nvar, obj->nvar, H, obj->nvar, x_data, obj->Hx.data);
      iy = obj->nvar + 1;
      for (int32_T idx{iy}; idx <= maxRegVar; idx++) {
        obj->Hx.data[idx - 1] = x_data[idx - 1] * obj->beta;
      }

      std::memcpy(&obj->grad.data[0], &obj->Hx.data[0], static_cast<uint8_T>
                  (obj->maxVar - 1) * sizeof(real_T));
      if (obj->hasLinear && (obj->nvar >= 1)) {
        maxRegVar = obj->nvar - 1;
        for (int32_T idx{0}; idx <= maxRegVar; idx++) {
          obj->grad.data[idx] += f_data[idx];
        }
      }

      maxRegVar = (obj->maxVar - obj->nvar) - 1;
      if (maxRegVar >= 1) {
        iy = obj->nvar;
        for (int32_T idx{0}; idx < maxRegVar; idx++) {
          int32_T tmp;
          tmp = iy + idx;
          obj->grad.data[tmp] += obj->rho;
        }
      }
    }
    break;
  }
}

// Function for MATLAB Function: '<S2>/NLMPC'
real_T MPC_controller::computeFval_ReuseHx(const s_4B8jbk60U8ZWFI1LxShFzC *obj,
  real_T workspace_data[], const real_T f_data[], const real_T x_data[])
{
  real_T val;
  switch (obj->objtype) {
   case 5:
    val = x_data[obj->nvar - 1] * obj->gammaScalar;
    break;

   case 3:
    {
      if (obj->hasLinear) {
        int32_T j;
        j = static_cast<uint8_T>(obj->nvar);
        for (int32_T maxRegVar{0}; maxRegVar < j; maxRegVar++) {
          workspace_data[maxRegVar] = 0.5 * obj->Hx.data[maxRegVar] +
            f_data[maxRegVar];
        }

        val = 0.0;
        if (obj->nvar >= 1) {
          for (int32_T b_k{0}; b_k < j; b_k++) {
            val += workspace_data[b_k] * x_data[b_k];
          }
        }
      } else {
        val = 0.0;
        if (obj->nvar >= 1) {
          int32_T b_k;
          b_k = static_cast<uint8_T>(obj->nvar);
          for (int32_T maxRegVar{0}; maxRegVar < b_k; maxRegVar++) {
            val += x_data[maxRegVar] * obj->Hx.data[maxRegVar];
          }
        }

        val *= 0.5;
      }
    }
    break;

   default:
    {
      int32_T maxRegVar;
      maxRegVar = obj->maxVar - 1;
      if (obj->hasLinear) {
        int32_T b_k;
        if (static_cast<uint8_T>(obj->nvar) - 1 >= 0) {
          std::memcpy(&workspace_data[0], &f_data[0], static_cast<uint8_T>
                      (obj->nvar) * sizeof(real_T));
        }

        b_k = obj->maxVar - obj->nvar;
        for (maxRegVar = 0; maxRegVar <= b_k - 2; maxRegVar++) {
          workspace_data[obj->nvar + maxRegVar] = obj->rho;
        }

        maxRegVar = static_cast<uint8_T>(obj->maxVar - 1);
        for (b_k = 0; b_k < maxRegVar; b_k++) {
          workspace_data[b_k] += 0.5 * obj->Hx.data[b_k];
        }

        val = 0.0;
        if (obj->maxVar - 1 >= 1) {
          for (b_k = 0; b_k < maxRegVar; b_k++) {
            val += workspace_data[b_k] * x_data[b_k];
          }
        }
      } else {
        int32_T j;
        val = 0.0;
        if (obj->maxVar - 1 >= 1) {
          j = static_cast<uint8_T>(obj->maxVar - 1);
          for (int32_T b_k{0}; b_k < j; b_k++) {
            val += x_data[b_k] * obj->Hx.data[b_k];
          }
        }

        val *= 0.5;
        j = obj->nvar + 1;
        for (int32_T b_k{j}; b_k <= maxRegVar; b_k++) {
          val += x_data[b_k - 1] * obj->rho;
        }
      }
    }
    break;
  }

  return val;
}

// Function for MATLAB Function: '<S2>/NLMPC'
void MPC_controller::xrotg(real_T *a, real_T *b, real_T *c, real_T *s)
{
  real_T absa;
  real_T absb;
  real_T roe;
  real_T scale;
  roe = *b;
  absa = std::abs(*a);
  absb = std::abs(*b);
  if (absa > absb) {
    roe = *a;
  }

  scale = absa + absb;
  if (scale == 0.0) {
    *s = 0.0;
    *c = 1.0;
    *a = 0.0;
    *b = 0.0;
  } else {
    real_T ads;
    real_T bds;
    ads = absa / scale;
    bds = absb / scale;
    scale *= std::sqrt(ads * ads + bds * bds);
    if (roe < 0.0) {
      scale = -scale;
    }

    *c = *a / scale;
    *s = *b / scale;
    if (absa > absb) {
      *b = *s;
    } else if (*c != 0.0) {
      *b = 1.0 / *c;
    } else {
      *b = 1.0;
    }

    *a = scale;
  }
}

// Function for MATLAB Function: '<S2>/NLMPC'
void MPC_controller::deleteColMoveEnd(s_LP9wk1co4RSPM0xk4tXznB *obj, int32_T idx)
{
  real_T b_s;
  real_T b_temp;
  real_T c_c;
  int32_T i;
  if (obj->usedPivoting) {
    i = 1;
    while ((i <= obj->ncols) && (obj->jpvt.data[i - 1] != idx)) {
      i++;
    }

    idx = i;
  }

  if (idx >= obj->ncols) {
    obj->ncols--;
  } else {
    int32_T e;
    int32_T endIdx;
    obj->jpvt.data[idx - 1] = obj->jpvt.data[obj->ncols - 1];
    e = obj->minRowCol;
    for (endIdx = 0; endIdx < e; endIdx++) {
      obj->QR.data[endIdx + obj->ldq * (idx - 1)] = obj->QR.data[(obj->ncols - 1)
        * obj->ldq + endIdx];
    }

    obj->ncols--;
    if (obj->mrows <= obj->ncols) {
      obj->minRowCol = obj->mrows;
    } else {
      obj->minRowCol = obj->ncols;
    }

    if (idx < obj->mrows) {
      int32_T QRk0;
      int32_T b_ix;
      int32_T b_temp_tmp;
      int32_T b_temp_tmp_0;
      int32_T idxRotGCol;
      if (obj->mrows - 1 <= obj->ncols) {
        endIdx = obj->mrows - 1;
      } else {
        endIdx = obj->ncols;
      }

      e = endIdx;
      idxRotGCol = (idx - 1) * obj->ldq;
      while (e >= idx) {
        int32_T ix;
        b_temp = obj->QR.data[e + idxRotGCol];
        xrotg(&obj->QR.data[(e + idxRotGCol) - 1], &b_temp, &c_c, &b_s);
        obj->QR.data[e + idxRotGCol] = b_temp;
        obj->QR.data[e + obj->ldq * (e - 1)] = 0.0;
        QRk0 = obj->ldq * idx + e;
        b_ix = obj->ncols - idx;
        if (b_ix >= 1) {
          ix = QRk0 - 1;
          for (i = 0; i < b_ix; i++) {
            b_temp = obj->QR.data[ix] * c_c + obj->QR.data[QRk0] * b_s;
            obj->QR.data[QRk0] = obj->QR.data[QRk0] * c_c - obj->QR.data[ix] *
              b_s;
            obj->QR.data[ix] = b_temp;
            QRk0 += obj->ldq;
            ix += obj->ldq;
          }
        }

        i = (e - 1) * obj->ldq;
        QRk0 = obj->mrows;
        if (obj->mrows >= 1) {
          ix = obj->ldq + i;
          for (b_ix = 0; b_ix < QRk0; b_ix++) {
            b_temp_tmp = ix + b_ix;
            b_temp_tmp_0 = i + b_ix;
            b_temp = obj->Q.data[b_temp_tmp_0] * c_c + obj->Q.data[b_temp_tmp] *
              b_s;
            obj->Q.data[b_temp_tmp] = obj->Q.data[b_temp_tmp] * c_c -
              obj->Q.data[b_temp_tmp_0] * b_s;
            obj->Q.data[i + b_ix] = b_temp;
          }
        }

        e--;
      }

      for (e = idx + 1; e <= endIdx; e++) {
        i = (e - 1) * obj->ldq;
        b_temp_tmp = e + i;
        b_temp = obj->QR.data[b_temp_tmp];
        xrotg(&obj->QR.data[(e + i) - 1], &b_temp, &c_c, &b_s);
        obj->QR.data[b_temp_tmp] = b_temp;
        QRk0 = (obj->ldq + 1) * e;
        i = obj->ncols - e;
        if (i >= 1) {
          b_ix = QRk0 - 1;
          for (idxRotGCol = 0; idxRotGCol < i; idxRotGCol++) {
            b_temp = obj->QR.data[b_ix] * c_c + obj->QR.data[QRk0] * b_s;
            obj->QR.data[QRk0] = obj->QR.data[QRk0] * c_c - obj->QR.data[b_ix] *
              b_s;
            obj->QR.data[b_ix] = b_temp;
            QRk0 += obj->ldq;
            b_ix += obj->ldq;
          }
        }

        QRk0 = (e - 1) * obj->ldq;
        idxRotGCol = obj->mrows;
        if (obj->mrows >= 1) {
          b_ix = obj->ldq + QRk0;
          for (i = 0; i < idxRotGCol; i++) {
            b_temp_tmp = b_ix + i;
            b_temp_tmp_0 = QRk0 + i;
            b_temp = obj->Q.data[b_temp_tmp_0] * c_c + obj->Q.data[b_temp_tmp] *
              b_s;
            obj->Q.data[b_temp_tmp] = obj->Q.data[b_temp_tmp] * c_c -
              obj->Q.data[b_temp_tmp_0] * b_s;
            obj->Q.data[b_temp_tmp_0] = b_temp;
          }
        }
      }
    }
  }
}

// Function for MATLAB Function: '<S2>/NLMPC'
boolean_T MPC_controller::strcmp_c(const char_T a[7])
{
  static const char_T b[7]{ 'f', 'm', 'i', 'n', 'c', 'o', 'n' };

  int32_T ret;
  ret = memcmp(&a[0], &b[0], 7);
  return ret == 0;
}

// Function for MATLAB Function: '<S2>/NLMPC'
void MPC_controller::xgemm(int32_T m, int32_T n, int32_T k, const real_T A[2116],
  int32_T lda, const real_T B_data[], int32_T ib0, int32_T ldb, real_T C_data[],
  int32_T ldc)
{
  if ((m != 0) && (n != 0)) {
    int32_T b;
    int32_T br;
    int32_T lastColC;
    br = ib0;
    lastColC = (n - 1) * ldc;
    for (int32_T cr{0}; ldc < 0 ? cr >= lastColC : cr <= lastColC; cr += ldc) {
      b = cr + m;
      for (int32_T ic{cr + 1}; ic <= b; ic++) {
        C_data[ic - 1] = 0.0;
      }
    }

    for (int32_T cr{0}; ldc < 0 ? cr >= lastColC : cr <= lastColC; cr += ldc) {
      int32_T ar;
      int32_T c;
      ar = -1;
      c = br + k;
      for (int32_T ic{br}; ic < c; ic++) {
        int32_T d;
        d = cr + m;
        for (b = cr + 1; b <= d; b++) {
          C_data[b - 1] += A[(ar + b) - cr] * B_data[ic - 1];
        }

        ar += lda;
      }

      br += ldb;
    }
  }
}

// Function for MATLAB Function: '<S2>/NLMPC'
void MPC_controller::xgemm_k(int32_T m, int32_T n, int32_T k, const real_T
  A_data[], int32_T ia0, int32_T lda, const real_T B_data[], int32_T ldb, real_T
  C_data[], int32_T ldc)
{
  if ((m != 0) && (n != 0)) {
    int32_T b;
    int32_T br;
    int32_T lastColC;
    lastColC = (n - 1) * ldc;
    for (int32_T cr{0}; ldc < 0 ? cr >= lastColC : cr <= lastColC; cr += ldc) {
      b = cr + m;
      for (int32_T ic{cr + 1}; ic <= b; ic++) {
        C_data[ic - 1] = 0.0;
      }
    }

    br = -1;
    for (int32_T cr{0}; ldc < 0 ? cr >= lastColC : cr <= lastColC; cr += ldc) {
      int32_T ar;
      int32_T c;
      ar = ia0;
      c = cr + m;
      for (int32_T ic{cr + 1}; ic <= c; ic++) {
        real_T temp;
        temp = 0.0;
        for (b = 0; b < k; b++) {
          temp += A_data[(b + ar) - 1] * B_data[(b + br) + 1];
        }

        C_data[ic - 1] += temp;
        ar += lda;
      }

      br += ldb;
    }
  }
}

// Function for MATLAB Function: '<S2>/NLMPC'
void MPC_controller::fullColLDL2_(s_U0bKKPZx63yLz5SynYPvR *obj, int32_T
  LD_offset, int32_T NColsRemain)
{
  int32_T LDimSizeP1;
  LDimSizeP1 = obj->ldm;
  for (int32_T k{0}; k < NColsRemain; k++) {
    real_T alpha1;
    real_T y;
    int32_T LD_diagOffset;
    int32_T b_k;
    int32_T subMatrixDim;
    LD_diagOffset = (LDimSizeP1 + 1) * k + LD_offset;
    alpha1 = -1.0 / obj->FMat.data[LD_diagOffset - 1];
    subMatrixDim = (NColsRemain - k) - 2;
    for (b_k = 0; b_k <= subMatrixDim; b_k++) {
      obj->workspace_ = obj->FMat.data[LD_diagOffset + b_k];
    }

    y = obj->workspace_;
    if (!(alpha1 == 0.0)) {
      int32_T jA;
      jA = LD_diagOffset + LDimSizeP1;
      for (b_k = 0; b_k <= subMatrixDim; b_k++) {
        if (y != 0.0) {
          real_T temp;
          int32_T b;
          temp = y * alpha1;
          b = (subMatrixDim + jA) + 1;
          for (int32_T ijA{jA + 1}; ijA <= b; ijA++) {
            obj->FMat.data[ijA - 1] += obj->workspace_ * temp;
          }
        }

        jA += obj->ldm;
      }
    }

    alpha1 = 1.0 / obj->FMat.data[LD_diagOffset - 1];
    b_k = (LD_diagOffset + subMatrixDim) + 1;
    for (subMatrixDim = LD_diagOffset + 1; subMatrixDim <= b_k; subMatrixDim++)
    {
      obj->FMat.data[subMatrixDim - 1] *= alpha1;
    }
  }
}

// Function for MATLAB Function: '<S2>/NLMPC'
void MPC_controller::partialColLDL3_(s_U0bKKPZx63yLz5SynYPvR *obj, int32_T
  LD_offset, int32_T NColsRemain)
{
  int32_T LD_diagOffset;
  int32_T LDimSizeP1;
  int32_T c;
  int32_T idx;
  int32_T ix;
  int32_T iy;
  int32_T lastColC;
  int32_T lda;
  int32_T numStrictLowerRows;
  int32_T subRows;
  LDimSizeP1 = obj->ldm + 1;
  for (int32_T k{0}; k < 48; k++) {
    real_T y;
    subRows = (NColsRemain - k) - 1;
    LD_diagOffset = (LDimSizeP1 * k + LD_offset) - 1;
    for (numStrictLowerRows = 0; numStrictLowerRows <= subRows;
         numStrictLowerRows++) {
      obj->workspace_ = obj->FMat.data[LD_diagOffset + numStrictLowerRows];
    }

    for (numStrictLowerRows = 0; numStrictLowerRows < NColsRemain;
         numStrictLowerRows++) {
      obj->workspace2_ = obj->workspace_;
    }

    lda = obj->ldm;
    y = obj->workspace2_;
    if ((NColsRemain != 0) && (k != 0)) {
      ix = LD_offset + k;
      c = (k - 1) * obj->ldm + 1;
      for (numStrictLowerRows = 1; lda < 0 ? numStrictLowerRows >= c :
           numStrictLowerRows <= c; numStrictLowerRows += lda) {
        lastColC = (numStrictLowerRows + NColsRemain) - 1;
        for (idx = numStrictLowerRows; idx <= lastColC; idx++) {
          y += -obj->FMat.data[ix - 1] * obj->workspace_;
        }

        ix += obj->ldm;
      }
    }

    obj->workspace2_ = y;
    for (numStrictLowerRows = 0; numStrictLowerRows < NColsRemain;
         numStrictLowerRows++) {
      obj->workspace_ = y;
    }

    for (numStrictLowerRows = 0; numStrictLowerRows <= subRows;
         numStrictLowerRows++) {
      obj->FMat.data[LD_diagOffset + numStrictLowerRows] = obj->workspace_;
    }

    numStrictLowerRows = subRows;
    for (subRows = 0; subRows < numStrictLowerRows; subRows++) {
      iy = (subRows + LD_diagOffset) + 1;
      obj->FMat.data[iy] /= obj->FMat.data[LD_diagOffset];
    }
  }

  for (int32_T k{48}; k <= NColsRemain - 1; k += 48) {
    int32_T br;
    int32_T f;
    int32_T numStrictLowerRows_tmp;
    int32_T u1_tmp;
    u1_tmp = NColsRemain - k;
    if (u1_tmp >= 48) {
      LD_diagOffset = 48;
    } else {
      LD_diagOffset = u1_tmp;
    }

    numStrictLowerRows_tmp = k + LD_diagOffset;
    numStrictLowerRows = numStrictLowerRows_tmp - 1;
    for (subRows = k; subRows <= numStrictLowerRows; subRows++) {
      idx = numStrictLowerRows_tmp - subRows;
      lda = (LDimSizeP1 * subRows + LD_offset) - 1;
      for (ix = 0; ix < 48; ix++) {
        obj->workspace2_ = obj->FMat.data[((LD_offset + subRows) + ix * obj->ldm)
          - 1];
      }

      lastColC = obj->ldm;
      if (idx != 0) {
        br = (obj->ldm * 47 + subRows) + 1;
        for (ix = subRows + 1; lastColC < 0 ? ix >= br : ix <= br; ix +=
             lastColC) {
          f = ix + idx;
          for (c = ix; c < f; c++) {
            iy = (lda + c) - ix;
            obj->FMat.data[iy] += obj->workspace_ * -obj->workspace2_;
          }
        }
      }
    }

    if (numStrictLowerRows_tmp < NColsRemain) {
      subRows = u1_tmp - LD_diagOffset;
      numStrictLowerRows = ((LD_offset + LD_diagOffset) + LDimSizeP1 * k) - 1;
      for (idx = 0; idx < 48; idx++) {
        ix = (LD_offset + k) + idx * obj->ldm;
        for (lda = 0; lda < LD_diagOffset; lda++) {
          obj->workspace2_ = obj->FMat.data[(ix + lda) - 1];
        }
      }

      idx = obj->ldm;
      lda = obj->ldm;
      if ((subRows != 0) && (LD_diagOffset != 0)) {
        lastColC = (LD_diagOffset - 1) * obj->ldm + numStrictLowerRows;
        br = 0;
        for (LD_diagOffset = numStrictLowerRows; lda < 0 ? LD_diagOffset >=
             lastColC : LD_diagOffset <= lastColC; LD_diagOffset += lda) {
          br++;
          iy = idx * 47 + br;
          for (ix = br; idx < 0 ? ix >= iy : ix <= iy; ix += idx) {
            f = LD_diagOffset + subRows;
            for (c = LD_diagOffset + 1; c <= f; c++) {
              obj->FMat.data[c - 1] += -obj->workspace2_ * obj->workspace_;
            }
          }
        }
      }
    }
  }
}

// Function for MATLAB Function: '<S2>/NLMPC'
int32_T MPC_controller::xpotrf(int32_T n, real_T A_data[], int32_T lda)
{
  int32_T b_j;
  int32_T info;
  boolean_T exitg1;
  info = 0;
  b_j = 0;
  exitg1 = false;
  while ((!exitg1) && (b_j <= n - 1)) {
    real_T ssq;
    int32_T b_ix;
    int32_T idxA1j;
    int32_T idxAjj;
    int32_T nmj;
    idxA1j = b_j * lda;
    idxAjj = idxA1j + b_j;
    ssq = 0.0;
    if (b_j >= 1) {
      for (nmj = 0; nmj < b_j; nmj++) {
        b_ix = idxA1j + nmj;
        ssq += A_data[b_ix] * A_data[b_ix];
      }
    }

    ssq = A_data[idxAjj] - ssq;
    if (ssq > 0.0) {
      ssq = std::sqrt(ssq);
      A_data[idxAjj] = ssq;
      if (b_j + 1 < n) {
        int32_T jm1;
        nmj = (n - b_j) - 2;
        jm1 = (idxA1j + lda) + 1;
        idxAjj += lda;
        if ((b_j != 0) && (nmj + 1 != 0)) {
          int32_T b;
          int32_T iy;
          iy = idxAjj;
          b = lda * nmj + jm1;
          for (b_ix = jm1; lda < 0 ? b_ix >= b : b_ix <= b; b_ix += lda) {
            real_T c;
            int32_T d;
            c = 0.0;
            d = b_ix + b_j;
            for (int32_T b_iy{b_ix}; b_iy < d; b_iy++) {
              c += A_data[(idxA1j + b_iy) - b_ix] * A_data[b_iy - 1];
            }

            A_data[iy] -= c;
            iy += lda;
          }
        }

        ssq = 1.0 / ssq;
        idxA1j = (lda * nmj + idxAjj) + 1;
        for (nmj = idxAjj + 1; lda < 0 ? nmj >= idxA1j : nmj <= idxA1j; nmj +=
             lda) {
          A_data[nmj - 1] *= ssq;
        }
      }

      b_j++;
    } else {
      A_data[idxAjj] = ssq;
      info = b_j + 1;
      exitg1 = true;
    }
  }

  return info;
}

// Function for MATLAB Function: '<S2>/NLMPC'
void MPC_controller::xgemv_dffoyl1j(int32_T m, int32_T n, const real_T A_data[],
  int32_T ia0, int32_T lda, const real_T x_data[], real_T y_data[])
{
  if (m != 0) {
    int32_T b;
    int32_T ix;
    std::memset(&y_data[0], 0, static_cast<uint32_T>(m) * sizeof(real_T));
    ix = 0;
    b = (n - 1) * lda + ia0;
    for (int32_T b_iy{ia0}; lda < 0 ? b_iy >= b : b_iy <= b; b_iy += lda) {
      int32_T c;
      c = b_iy + m;
      for (int32_T iyend{b_iy}; iyend < c; iyend++) {
        int32_T tmp;
        tmp = iyend - b_iy;
        y_data[tmp] += A_data[iyend - 1] * x_data[ix];
      }

      ix++;
    }
  }
}

// Function for MATLAB Function: '<S2>/NLMPC'
void MPC_controller::factor(s_U0bKKPZx63yLz5SynYPvR *obj, const real_T A[2116],
  int32_T ndims, int32_T ldA)
{
  obj->ndims = ndims;
  for (int32_T idx{0}; idx < ndims; idx++) {
    int32_T ix0;
    int32_T iy0;
    ix0 = ldA * idx;
    iy0 = obj->ldm * idx;
    for (int32_T b_k{0}; b_k < ndims; b_k++) {
      obj->FMat.data[iy0 + b_k] = A[b_k + ix0];
    }
  }

  obj->info = xpotrf(ndims, obj->FMat.data, obj->ldm);
}

// Function for MATLAB Function: '<S2>/NLMPC'
void MPC_controller::solve(const s_U0bKKPZx63yLz5SynYPvR *obj, real_T rhs_data[])
{
  int32_T n_tmp;
  n_tmp = obj->ndims;
  if (obj->ndims != 0) {
    int32_T jA;
    for (int32_T j{0}; j < n_tmp; j++) {
      real_T temp;
      jA = j * obj->ldm;
      temp = rhs_data[j];
      for (int32_T i{0}; i < j; i++) {
        temp -= obj->FMat.data[jA + i] * rhs_data[i];
      }

      rhs_data[j] = temp / obj->FMat.data[jA + j];
    }

    for (int32_T j{n_tmp}; j >= 1; j--) {
      jA = ((j - 1) * obj->ldm + j) - 2;
      rhs_data[j - 1] /= obj->FMat.data[jA + 1];
      for (int32_T i{0}; i <= j - 2; i++) {
        int32_T ix;
        ix = (j - i) - 2;
        rhs_data[ix] -= obj->FMat.data[jA - i] * rhs_data[j - 1];
      }
    }
  }
}

// Function for MATLAB Function: '<S2>/NLMPC'
void MPC_controller::factor_g(s_U0bKKPZx63yLz5SynYPvR *obj, const real_T A[2116],
  int32_T ndims, int32_T ldA)
{
  int32_T A_maxDiag_idx;
  int32_T LD_diagOffset;
  int32_T LDimSizeP1;
  int32_T ix;
  LDimSizeP1 = obj->ldm + 1;
  obj->ndims = ndims;
  for (A_maxDiag_idx = 0; A_maxDiag_idx < ndims; A_maxDiag_idx++) {
    int32_T iy0;
    ix = ldA * A_maxDiag_idx;
    iy0 = obj->ldm * A_maxDiag_idx;
    for (LD_diagOffset = 0; LD_diagOffset < ndims; LD_diagOffset++) {
      obj->FMat.data[iy0 + LD_diagOffset] = A[LD_diagOffset + ix];
    }
  }

  if (ndims < 1) {
    A_maxDiag_idx = -1;
  } else {
    A_maxDiag_idx = 0;
    if (ndims > 1) {
      real_T smax;
      smax = std::abs(obj->FMat.data[0]);
      for (LD_diagOffset = 2; LD_diagOffset <= ndims; LD_diagOffset++) {
        real_T s;
        s = std::abs(obj->FMat.data[(LD_diagOffset - 1) * LDimSizeP1]);
        if (s > smax) {
          A_maxDiag_idx = LD_diagOffset - 1;
          smax = s;
        }
      }
    }
  }

  obj->regTol_ = std::fmax(std::abs(obj->FMat.data[obj->ldm * A_maxDiag_idx +
    A_maxDiag_idx]) * 2.2204460492503131E-16, 0.0);
  if (ndims > 128) {
    boolean_T exitg1;
    A_maxDiag_idx = 0;
    exitg1 = false;
    while ((!exitg1) && (A_maxDiag_idx < ndims)) {
      LD_diagOffset = LDimSizeP1 * A_maxDiag_idx + 1;
      ix = ndims - A_maxDiag_idx;
      if (A_maxDiag_idx + 48 <= ndims) {
        partialColLDL3_(obj, LD_diagOffset, ix);
        A_maxDiag_idx += 48;
      } else {
        fullColLDL2_(obj, LD_diagOffset, ix);
        exitg1 = true;
      }
    }
  } else {
    fullColLDL2_(obj, 1, ndims);
  }

  if (obj->ConvexCheck) {
    LDimSizeP1 = 0;
    int32_T exitg2;
    do {
      exitg2 = 0;
      if (LDimSizeP1 <= ndims - 1) {
        if (obj->FMat.data[obj->ldm * LDimSizeP1 + LDimSizeP1] <= 0.0) {
          obj->info = -LDimSizeP1 - 1;
          exitg2 = 1;
        } else {
          LDimSizeP1++;
        }
      } else {
        obj->ConvexCheck = false;
        exitg2 = 1;
      }
    } while (exitg2 == 0);
  }
}

// Function for MATLAB Function: '<S2>/NLMPC'
void MPC_controller::solve_i(const s_U0bKKPZx63yLz5SynYPvR *obj, real_T
  rhs_data[])
{
  int32_T b_i;
  int32_T jjA;
  int32_T n;
  n = obj->ndims - 1;
  if (obj->ndims != 0) {
    for (int32_T b_j{0}; b_j <= n; b_j++) {
      int32_T c;
      jjA = b_j * obj->ldm + b_j;
      c = n - b_j;
      for (b_i = 0; b_i < c; b_i++) {
        int32_T ix;
        ix = (b_i + b_j) + 1;
        rhs_data[ix] -= obj->FMat.data[(b_i + jjA) + 1] * rhs_data[b_j];
      }
    }
  }

  b_i = obj->ndims;
  for (int32_T b_j{0}; b_j < b_i; b_j++) {
    rhs_data[b_j] /= obj->FMat.data[obj->ldm * b_j + b_j];
  }

  n = obj->ndims;
  if (obj->ndims != 0) {
    for (int32_T b_j{n}; b_j >= 1; b_j--) {
      real_T temp;
      jjA = (b_j - 1) * obj->ldm;
      temp = rhs_data[b_j - 1];
      for (b_i = n; b_i >= b_j + 1; b_i--) {
        temp -= obj->FMat.data[(jjA + b_i) - 1] * rhs_data[b_i - 1];
      }

      rhs_data[b_j - 1] = temp;
    }
  }
}

// Function for MATLAB Function: '<S2>/NLMPC'
void MPC_controller::compute_deltax(const real_T H[2116],
  s_aAq9pdCdNustb4CQC7xpeC *solution, s_AiLncvKJfAMbGh9HSVCzlG *memspace, const
  s_LP9wk1co4RSPM0xk4tXznB *qrmanager, s_U0bKKPZx63yLz5SynYPvR *cholmanager,
  const s_4B8jbk60U8ZWFI1LxShFzC *objective, boolean_T alwaysPositiveDef)
{
  int32_T mNull_tmp;
  int32_T nVar;
  nVar = qrmanager->mrows - 1;
  mNull_tmp = qrmanager->mrows - qrmanager->ncols;
  if (mNull_tmp <= 0) {
    if (qrmanager->mrows - 1 >= 0) {
      std::memset(&solution->searchDir.data[0], 0, static_cast<uint32_T>
                  ((qrmanager->mrows - 1) + 1) * sizeof(real_T));
    }
  } else {
    int32_T nullStartIdx;
    for (nullStartIdx = 0; nullStartIdx <= nVar; nullStartIdx++) {
      solution->searchDir.data[nullStartIdx] = -objective->
        grad.data[nullStartIdx];
    }

    if (qrmanager->ncols <= 0) {
      switch (objective->objtype) {
       case 5:
        break;

       case 3:
        if (alwaysPositiveDef) {
          factor(cholmanager, H, qrmanager->mrows, qrmanager->mrows);
        } else {
          factor_g(cholmanager, H, qrmanager->mrows, qrmanager->mrows);
        }

        if (cholmanager->info != 0) {
          solution->state = -6;
        } else if (alwaysPositiveDef) {
          solve(cholmanager, solution->searchDir.data);
        } else {
          solve_i(cholmanager, solution->searchDir.data);
        }
        break;

       default:
        {
          if (alwaysPositiveDef) {
            factor(cholmanager, H, objective->nvar, objective->nvar);
            if (cholmanager->info != 0) {
              solution->state = -6;
            } else {
              real_T smax;
              int32_T b_mNull;
              solve(cholmanager, solution->searchDir.data);
              smax = 1.0 / objective->beta;
              nullStartIdx = objective->nvar + 1;
              b_mNull = qrmanager->mrows;
              for (int32_T c_mNull{nullStartIdx}; c_mNull <= b_mNull; c_mNull++)
              {
                solution->searchDir.data[c_mNull - 1] *= smax;
              }
            }
          }
        }
        break;
      }
    } else {
      int32_T nullStartIdx_tmp;
      nullStartIdx_tmp = qrmanager->ldq * qrmanager->ncols + 1;
      if (objective->objtype == 5) {
        for (int32_T nullStart{0}; nullStart < mNull_tmp; nullStart++) {
          memspace->workspace_double.data[nullStart] = -qrmanager->Q.data
            [(qrmanager->ncols + nullStart) * qrmanager->ldq + nVar];
        }

        xgemv_dffoyl1j(qrmanager->mrows, mNull_tmp, qrmanager->Q.data,
                       nullStartIdx_tmp, qrmanager->ldq,
                       memspace->workspace_double.data, solution->searchDir.data);
      } else {
        real_T smax;
        int32_T b_ldw;
        int32_T b_mNull;
        int32_T c_mNull;
        int32_T ix;
        int32_T nullStart;
        if (objective->objtype == 3) {
          xgemm(qrmanager->mrows, mNull_tmp, qrmanager->mrows, H,
                qrmanager->mrows, qrmanager->Q.data, nullStartIdx_tmp,
                qrmanager->ldq, memspace->workspace_double.data,
                memspace->workspace_double.size[0]);
          xgemm_k(mNull_tmp, mNull_tmp, qrmanager->mrows, qrmanager->Q.data,
                  nullStartIdx_tmp, qrmanager->ldq,
                  memspace->workspace_double.data,
                  memspace->workspace_double.size[0], cholmanager->FMat.data,
                  cholmanager->ldm);
        } else if (alwaysPositiveDef) {
          nullStartIdx = qrmanager->mrows;
          b_ldw = memspace->workspace_double.size[0];
          xgemm(objective->nvar, mNull_tmp, objective->nvar, H, objective->nvar,
                qrmanager->Q.data, nullStartIdx_tmp, qrmanager->ldq,
                memspace->workspace_double.data, memspace->
                workspace_double.size[0]);
          for (b_mNull = 0; b_mNull < mNull_tmp; b_mNull++) {
            ix = objective->nvar + 1;
            for (nullStart = ix; nullStart <= nullStartIdx; nullStart++) {
              memspace->workspace_double.data[(nullStart +
                memspace->workspace_double.size[0] * b_mNull) - 1] =
                qrmanager->Q.data[((b_mNull + qrmanager->ncols) *
                                   qrmanager->Q.size[0] + nullStart) - 1] *
                objective->beta;
            }
          }

          xgemm_k(mNull_tmp, mNull_tmp, qrmanager->mrows, qrmanager->Q.data,
                  nullStartIdx_tmp, qrmanager->ldq,
                  memspace->workspace_double.data, b_ldw, cholmanager->FMat.data,
                  cholmanager->ldm);
        }

        if (alwaysPositiveDef) {
          cholmanager->ndims = mNull_tmp;
          cholmanager->info = xpotrf(mNull_tmp, cholmanager->FMat.data,
            cholmanager->ldm);
        } else {
          nullStart = cholmanager->ldm + 1;
          cholmanager->ndims = mNull_tmp;
          nullStartIdx = 0;
          if (mNull_tmp > 1) {
            smax = std::abs(cholmanager->FMat.data[0]);
            for (b_mNull = 2; b_mNull <= mNull_tmp; b_mNull++) {
              real_T s;
              s = std::abs(cholmanager->FMat.data[(b_mNull - 1) * nullStart]);
              if (s > smax) {
                nullStartIdx = b_mNull - 1;
                smax = s;
              }
            }
          }

          cholmanager->regTol_ = std::fmax(std::abs(cholmanager->
            FMat.data[cholmanager->ldm * nullStartIdx + nullStartIdx]) *
            2.2204460492503131E-16, 0.0);
          if (mNull_tmp > 128) {
            boolean_T exitg1;
            b_mNull = 0;
            exitg1 = false;
            while ((!exitg1) && (b_mNull < mNull_tmp)) {
              nullStartIdx = nullStart * b_mNull + 1;
              c_mNull = mNull_tmp - b_mNull;
              if (b_mNull + 48 <= mNull_tmp) {
                partialColLDL3_(cholmanager, nullStartIdx, c_mNull);
                b_mNull += 48;
              } else {
                fullColLDL2_(cholmanager, nullStartIdx, c_mNull);
                exitg1 = true;
              }
            }
          } else {
            fullColLDL2_(cholmanager, 1, mNull_tmp);
          }

          if (cholmanager->ConvexCheck) {
            b_mNull = 0;
            int32_T exitg2;
            do {
              exitg2 = 0;
              if (b_mNull <= mNull_tmp - 1) {
                if (cholmanager->FMat.data[cholmanager->ldm * b_mNull + b_mNull]
                    <= 0.0) {
                  cholmanager->info = -b_mNull - 1;
                  exitg2 = 1;
                } else {
                  b_mNull++;
                }
              } else {
                cholmanager->ConvexCheck = false;
                exitg2 = 1;
              }
            } while (exitg2 == 0);
          }
        }

        if (cholmanager->info != 0) {
          solution->state = -6;
        } else {
          c_mNull = qrmanager->ldq;
          if (qrmanager->mrows != 0) {
            std::memset(&memspace->workspace_double.data[0], 0,
                        static_cast<uint32_T>(mNull_tmp) * sizeof(real_T));
            b_ldw = 0;
            ix = (mNull_tmp - 1) * qrmanager->ldq + nullStartIdx_tmp;
            for (nullStart = nullStartIdx_tmp; c_mNull < 0 ? nullStart >= ix :
                 nullStart <= ix; nullStart += c_mNull) {
              smax = 0.0;
              b_mNull = nullStart + nVar;
              for (nullStartIdx = nullStart; nullStartIdx <= b_mNull;
                   nullStartIdx++) {
                smax += qrmanager->Q.data[nullStartIdx - 1] *
                  objective->grad.data[nullStartIdx - nullStart];
              }

              memspace->workspace_double.data[b_ldw] -= smax;
              b_ldw++;
            }
          }

          if (alwaysPositiveDef) {
            c_mNull = cholmanager->ndims;
            if (cholmanager->ndims != 0) {
              for (nullStart = 0; nullStart < c_mNull; nullStart++) {
                b_ldw = nullStart * cholmanager->ldm;
                smax = memspace->workspace_double.data[nullStart];
                for (nullStartIdx = 0; nullStartIdx < nullStart; nullStartIdx++)
                {
                  smax -= cholmanager->FMat.data[b_ldw + nullStartIdx] *
                    memspace->workspace_double.data[nullStartIdx];
                }

                memspace->workspace_double.data[nullStart] = smax /
                  cholmanager->FMat.data[b_ldw + nullStart];
              }
            }

            b_ldw = cholmanager->ndims;
            if (cholmanager->ndims != 0) {
              for (nullStartIdx = b_ldw; nullStartIdx >= 1; nullStartIdx--) {
                ix = ((nullStartIdx - 1) * cholmanager->ldm + nullStartIdx) - 2;
                memspace->workspace_double.data[nullStartIdx - 1] /=
                  cholmanager->FMat.data[ix + 1];
                for (c_mNull = 0; c_mNull <= nullStartIdx - 2; c_mNull++) {
                  b_mNull = (nullStartIdx - c_mNull) - 2;
                  memspace->workspace_double.data[b_mNull] -=
                    memspace->workspace_double.data[nullStartIdx - 1] *
                    cholmanager->FMat.data[ix - c_mNull];
                }
              }
            }
          } else {
            b_ldw = cholmanager->ndims - 1;
            if (cholmanager->ndims != 0) {
              for (nullStartIdx = 0; nullStartIdx <= b_ldw; nullStartIdx++) {
                ix = nullStartIdx * cholmanager->ldm + nullStartIdx;
                b_mNull = b_ldw - nullStartIdx;
                for (c_mNull = 0; c_mNull < b_mNull; c_mNull++) {
                  nullStart = (c_mNull + nullStartIdx) + 1;
                  memspace->workspace_double.data[nullStart] -=
                    cholmanager->FMat.data[(c_mNull + ix) + 1] *
                    memspace->workspace_double.data[nullStartIdx];
                }
              }
            }

            nullStartIdx = cholmanager->ndims;
            for (nullStart = 0; nullStart < nullStartIdx; nullStart++) {
              memspace->workspace_double.data[nullStart] /=
                cholmanager->FMat.data[cholmanager->ldm * nullStart + nullStart];
            }

            c_mNull = cholmanager->ndims;
            if (cholmanager->ndims != 0) {
              for (nullStart = c_mNull; nullStart >= 1; nullStart--) {
                b_ldw = (nullStart - 1) * cholmanager->ldm;
                smax = memspace->workspace_double.data[nullStart - 1];
                for (nullStartIdx = c_mNull; nullStartIdx >= nullStart + 1;
                     nullStartIdx--) {
                  smax -= cholmanager->FMat.data[(b_ldw + nullStartIdx) - 1] *
                    memspace->workspace_double.data[nullStartIdx - 1];
                }

                memspace->workspace_double.data[nullStart - 1] = smax;
              }
            }
          }

          xgemv_dffoyl1j(qrmanager->mrows, mNull_tmp, qrmanager->Q.data,
                         nullStartIdx_tmp, qrmanager->ldq,
                         memspace->workspace_double.data,
                         solution->searchDir.data);
        }
      }
    }
  }
}

// Function for MATLAB Function: '<S2>/NLMPC'
real_T MPC_controller::xnrm2_n(int32_T n, const real_T x_data[])
{
  real_T y;
  y = 0.0;
  if (n >= 1) {
    if (n == 1) {
      y = std::abs(x_data[0]);
    } else {
      real_T scale;
      int32_T b;
      scale = 3.3121686421112381E-170;
      b = static_cast<uint8_T>(n);
      for (int32_T k{0}; k < b; k++) {
        real_T absxk;
        absxk = std::abs(x_data[k]);
        if (absxk > scale) {
          real_T t;
          t = scale / absxk;
          y = y * t * t + 1.0;
          scale = absxk;
        } else {
          real_T t;
          t = absxk / scale;
          y += t * t;
        }
      }

      y = scale * std::sqrt(y);
    }
  }

  return y;
}

// Function for MATLAB Function: '<S2>/NLMPC'
void MPC_controller::xgemv_dffoyl1jt(int32_T m, int32_T n, const real_T A_data[],
  int32_T lda, const real_T x_data[], real_T y_data[])
{
  if (n != 0) {
    int32_T b;
    int32_T d;
    b = static_cast<uint8_T>(n);
    for (int32_T b_iy{0}; b_iy < b; b_iy++) {
      y_data[b_iy] = -y_data[b_iy];
    }

    b = 0;
    d = (n - 1) * lda + 1;
    for (int32_T b_iy{1}; lda < 0 ? b_iy >= d : b_iy <= d; b_iy += lda) {
      real_T c;
      int32_T e;
      c = 0.0;
      e = b_iy + m;
      for (int32_T ia{b_iy}; ia < e; ia++) {
        c += A_data[ia - 1] * x_data[ia - b_iy];
      }

      y_data[b] += c;
      b++;
    }
  }
}

// Function for MATLAB Function: '<S2>/NLMPC'
void MPC_controller::feasibleratiotest(const real_T solution_xstar_data[], const
  real_T solution_searchDir_data[], real_T workspace_data[], const int32_T
  workspace_size[2], int32_T workingset_nVar, int32_T workingset_ldA, const
  real_T workingset_Aineq_data[], const real_T workingset_bineq_data[], const
  real_T workingset_lb_data[], const int32_T workingset_indexLB_data[], const
  int32_T workingset_sizes[5], const int32_T workingset_isActiveIdx[6], const
  boolean_T workingset_isActiveConstr_data[], const int32_T workingset_nWConstr
  [5], boolean_T isPhaseOne, real_T *alpha, boolean_T *newBlocking, int32_T
  *constrType, int32_T *constrIdx)
{
  real_T alphaTemp;
  real_T b_c;
  real_T denomTol;
  int32_T d;
  int32_T ia;
  int32_T iyend;
  int32_T ldw;
  *alpha = 1.0E+30;
  *newBlocking = false;
  *constrType = 0;
  *constrIdx = 0;
  denomTol = 2.2204460492503131E-13 * xnrm2_n(workingset_nVar,
    solution_searchDir_data);
  if (workingset_nWConstr[2] < workingset_sizes[2]) {
    d = static_cast<uint16_T>(workingset_sizes[2]);
    if (d - 1 >= 0) {
      std::memcpy(&workspace_data[0], &workingset_bineq_data[0],
                  static_cast<uint32_T>(d) * sizeof(real_T));
    }

    xgemv_dffoyl1jt(workingset_nVar, workingset_sizes[2], workingset_Aineq_data,
                    workingset_ldA, solution_xstar_data, workspace_data);
    ldw = workspace_size[0];
    if (workingset_sizes[2] != 0) {
      int32_T e;
      iyend = workspace_size[0] + workingset_sizes[2];
      if (ldw + 1 <= iyend) {
        std::memset(&workspace_data[ldw], 0, static_cast<uint32_T>(iyend - ldw) *
                    sizeof(real_T));
      }

      iyend = workspace_size[0];
      e = (workingset_sizes[2] - 1) * workingset_ldA + 1;
      for (d = 1; workingset_ldA < 0 ? d >= e : d <= e; d += workingset_ldA) {
        int32_T f;
        b_c = 0.0;
        f = d + workingset_nVar;
        for (ia = d; ia < f; ia++) {
          b_c += workingset_Aineq_data[ia - 1] * solution_searchDir_data[ia - d];
        }

        workspace_data[iyend] += b_c;
        iyend++;
      }
    }

    iyend = static_cast<uint8_T>(workingset_sizes[2]);
    for (d = 0; d < iyend; d++) {
      ia = ldw + d;
      if ((workspace_data[ia] > denomTol) && (!workingset_isActiveConstr_data
           [(workingset_isActiveIdx[2] + d) - 1])) {
        alphaTemp = std::fmin(std::abs(workspace_data[d]), 1.0E-6 -
                              workspace_data[d]) / workspace_data[ia];
        if (alphaTemp < *alpha) {
          *alpha = alphaTemp;
          *constrType = 3;
          *constrIdx = d + 1;
          *newBlocking = true;
        }
      }
    }
  }

  if (workingset_nWConstr[3] < workingset_sizes[3]) {
    real_T phaseOneCorrectionP;
    real_T ratio;
    b_c = solution_xstar_data[workingset_nVar - 1] * static_cast<real_T>
      (isPhaseOne);
    phaseOneCorrectionP = solution_searchDir_data[workingset_nVar - 1] *
      static_cast<real_T>(isPhaseOne);
    d = workingset_sizes[3];
    for (ldw = 0; ldw <= d - 2; ldw++) {
      iyend = workingset_indexLB_data[ldw];
      alphaTemp = -solution_searchDir_data[iyend - 1] - phaseOneCorrectionP;
      if ((alphaTemp > denomTol) && (!workingset_isActiveConstr_data
           [(workingset_isActiveIdx[3] + ldw) - 1])) {
        ratio = (-solution_xstar_data[iyend - 1] - workingset_lb_data[iyend - 1])
          - b_c;
        alphaTemp = std::fmin(std::abs(ratio), 1.0E-6 - ratio) / alphaTemp;
        if (alphaTemp < *alpha) {
          *alpha = alphaTemp;
          *constrType = 4;
          *constrIdx = ldw + 1;
          *newBlocking = true;
        }
      }
    }

    ia = workingset_indexLB_data[workingset_sizes[3] - 1] - 1;
    b_c = -solution_searchDir_data[ia];
    if ((b_c > denomTol) && (!workingset_isActiveConstr_data
         [(workingset_isActiveIdx[3] + workingset_sizes[3]) - 2])) {
      ratio = -solution_xstar_data[ia] - workingset_lb_data[ia];
      alphaTemp = std::fmin(std::abs(ratio), 1.0E-6 - ratio) / b_c;
      if (alphaTemp < *alpha) {
        *alpha = alphaTemp;
        *constrType = 4;
        *constrIdx = workingset_sizes[3];
        *newBlocking = true;
      }
    }
  }

  if (!isPhaseOne) {
    *newBlocking = (((!*newBlocking) || (!(*alpha > 1.0))) && (*newBlocking));
    *alpha = std::fmin(*alpha, 1.0);
  }
}

// Function for MATLAB Function: '<S2>/NLMPC'
void MPC_controller::checkUnboundedOrIllPosed(s_aAq9pdCdNustb4CQC7xpeC *solution,
  const s_4B8jbk60U8ZWFI1LxShFzC *objective)
{
  if (objective->objtype == 5) {
    if (xnrm2_n(objective->nvar, solution->searchDir.data) > 100.0 *
        static_cast<real_T>(objective->nvar) * 1.4901161193847656E-8) {
      solution->state = 3;
    } else {
      solution->state = 4;
    }
  }
}

// Function for MATLAB Function: '<S2>/NLMPC'
void MPC_controller::addBoundToActiveSetMatrix_(s_YG0fmBFfsyHj5FdUrtbgBC *obj,
  int32_T TYPE, int32_T idx_local)
{
  int32_T colOffset;
  int32_T idx_bnd_local;
  obj->nWConstr[TYPE - 1]++;
  obj->isActiveConstr.data[(obj->isActiveIdx[TYPE - 1] + idx_local) - 2] = true;
  obj->nActiveConstr++;
  obj->Wid.data[obj->nActiveConstr - 1] = TYPE;
  obj->Wlocalidx.data[obj->nActiveConstr - 1] = idx_local;
  colOffset = (obj->nActiveConstr - 1) * obj->ldA - 1;
  if (TYPE == 5) {
    idx_bnd_local = obj->indexUB.data[idx_local - 1];
    obj->bwset.data[obj->nActiveConstr - 1] = obj->ub.data[idx_bnd_local - 1];
  } else {
    idx_bnd_local = obj->indexLB.data[idx_local - 1];
    obj->bwset.data[obj->nActiveConstr - 1] = obj->lb.data[idx_bnd_local - 1];
  }

  if (static_cast<uint8_T>(idx_bnd_local - 1) - 1 >= 0) {
    std::memset(&obj->ATwset.data[colOffset + 1], 0, static_cast<uint32_T>((
      static_cast<uint8_T>(idx_bnd_local - 1) + colOffset) - colOffset) * sizeof
                (real_T));
  }

  obj->ATwset.data[idx_bnd_local + colOffset] = static_cast<real_T>(TYPE == 5) *
    2.0 - 1.0;
  if (idx_bnd_local + 1 <= obj->nVar) {
    std::memset(&obj->ATwset.data[(idx_bnd_local + colOffset) + 1], 0,
                static_cast<uint32_T>(((obj->nVar + colOffset) - idx_bnd_local)
      - colOffset) * sizeof(real_T));
  }

  switch (obj->probType) {
   case 3:
   case 2:
    break;

   default:
    obj->ATwset.data[obj->nVar + colOffset] = -1.0;
    break;
  }
}

// Function for MATLAB Function: '<S2>/NLMPC'
void MPC_controller::addAineqConstr(s_YG0fmBFfsyHj5FdUrtbgBC *obj, int32_T
  idx_local)
{
  int32_T b;
  int32_T iAineq0;
  int32_T iAw0;
  obj->nWConstr[2]++;
  obj->isActiveConstr.data[(obj->isActiveIdx[2] + idx_local) - 2] = true;
  obj->nActiveConstr++;
  obj->Wid.data[obj->nActiveConstr - 1] = 3;
  obj->Wlocalidx.data[obj->nActiveConstr - 1] = idx_local;
  iAineq0 = (idx_local - 1) * obj->ldA;
  iAw0 = (obj->nActiveConstr - 1) * obj->ldA;
  b = obj->nVar - 1;
  for (int32_T idx{0}; idx <= b; idx++) {
    obj->ATwset.data[iAw0 + idx] = obj->Aineq.data[iAineq0 + idx];
  }

  obj->bwset.data[obj->nActiveConstr - 1] = obj->bineq.data[idx_local - 1];
}

// Function for MATLAB Function: '<S2>/NLMPC'
void MPC_controller::checkStoppingAndUpdateFval(int32_T *activeSetChangeID,
  const real_T f_data[], s_aAq9pdCdNustb4CQC7xpeC *solution,
  s_AiLncvKJfAMbGh9HSVCzlG *memspace, const s_4B8jbk60U8ZWFI1LxShFzC *objective,
  s_YG0fmBFfsyHj5FdUrtbgBC *workingset, s_LP9wk1co4RSPM0xk4tXznB *qrmanager,
  real_T options_ObjectiveLimit, int32_T runTimeOptions_MaxIterations, boolean_T
  updateFval)
{
  real_T y_data[453];
  solution->iterations++;
  if ((solution->iterations >= runTimeOptions_MaxIterations) &&
      ((solution->state != 1) || (objective->objtype == 5))) {
    solution->state = 0;
  }

  if (solution->iterations - solution->iterations / 50 * 50 == 0) {
    real_T tempMaxConstr;
    solution->maxConstr = maxConstraintViolation_in(workingset,
      solution->xstar.data);
    tempMaxConstr = solution->maxConstr;
    if (objective->objtype == 5) {
      tempMaxConstr = solution->maxConstr - solution->xstar.data[objective->nvar
        - 1];
    }

    if (tempMaxConstr > 1.0E-6) {
      boolean_T nonDegenerateWset;
      if (solution->searchDir.size - 1 >= 0) {
        std::memcpy(&y_data[0], &solution->searchDir.data[0],
                    static_cast<uint32_T>(solution->searchDir.size) * sizeof
                    (real_T));
      }

      if (static_cast<uint16_T>(objective->nvar) - 1 >= 0) {
        std::memcpy(&y_data[0], &solution->xstar.data[0], static_cast<uint16_T>
                    (objective->nvar) * sizeof(real_T));
      }

      if (solution->searchDir.size - 1 >= 0) {
        std::memcpy(&solution->searchDir.data[0], &y_data[0],
                    static_cast<uint32_T>(solution->searchDir.size) * sizeof
                    (real_T));
      }

      nonDegenerateWset = feasibleX0ForWorkingSet
        (memspace->workspace_double.data, memspace->workspace_double.size,
         solution->searchDir.data, workingset, qrmanager);
      if ((!nonDegenerateWset) && (solution->state != 0)) {
        solution->state = -2;
      }

      *activeSetChangeID = 0;
      tempMaxConstr = maxConstraintViolation_in(workingset,
        solution->searchDir.data);
      if (tempMaxConstr < solution->maxConstr) {
        if (static_cast<uint8_T>(objective->nvar) - 1 >= 0) {
          std::memcpy(&solution->xstar.data[0], &solution->searchDir.data[0],
                      static_cast<uint8_T>(objective->nvar) * sizeof(real_T));
        }

        solution->maxConstr = tempMaxConstr;
      }
    }
  }

  if (updateFval && (options_ObjectiveLimit > (rtMinusInf))) {
    solution->fstar = computeFval_ReuseHx(objective,
      memspace->workspace_double.data, f_data, solution->xstar.data);
    if ((solution->fstar < options_ObjectiveLimit) && ((solution->state != 0) ||
         (objective->objtype != 5))) {
      solution->state = 2;
    }
  }
}

// Function for MATLAB Function: '<S2>/NLMPC'
void MPC_controller::iterate(const real_T H[2116], const real_T f_data[],
  s_aAq9pdCdNustb4CQC7xpeC *solution, s_AiLncvKJfAMbGh9HSVCzlG *memspace,
  s_YG0fmBFfsyHj5FdUrtbgBC *workingset, s_LP9wk1co4RSPM0xk4tXznB *qrmanager,
  s_U0bKKPZx63yLz5SynYPvR *cholmanager, s_4B8jbk60U8ZWFI1LxShFzC *objective,
  const char_T options_SolverName[7], real_T options_StepTolerance, real_T
  options_ObjectiveLimit, int32_T runTimeOptions_MaxIterations)
{
  real_T y_data[453];
  real_T normDelta;
  real_T s;
  real_T temp;
  int32_T activeSetChangeID;
  int32_T globalActiveConstrIdx;
  int32_T idxRotGCol;
  int32_T iyend;
  int32_T nVar;
  boolean_T subProblemChanged;
  boolean_T updateFval;
  subProblemChanged = true;
  updateFval = true;
  activeSetChangeID = 0;
  nVar = workingset->nVar;
  globalActiveConstrIdx = 0;
  computeGrad_StoreHx(objective, H, f_data, solution->xstar.data);
  solution->fstar = computeFval_ReuseHx(objective,
    memspace->workspace_double.data, f_data, solution->xstar.data);
  if (solution->iterations < runTimeOptions_MaxIterations) {
    solution->state = -5;
  } else {
    solution->state = 0;
  }

  iyend = workingset->mConstrMax;
  std::memset(&solution->lambda.data[0], 0, static_cast<uint32_T>
              (workingset->mConstrMax) * sizeof(real_T));
  int32_T exitg1;
  do {
    exitg1 = 0;
    if (solution->state == -5) {
      int32_T iQR0;
      int32_T idx;
      int32_T nActiveConstr;
      int32_T nrows;
      boolean_T guard11{ false };

      guard11 = false;
      if (subProblemChanged) {
        switch (activeSetChangeID) {
         case 1:
          {
            int32_T iy;
            nrows = (workingset->nActiveConstr - 1) * workingset->ldA;
            if (qrmanager->mrows <= qrmanager->ncols + 1) {
              qrmanager->minRowCol = qrmanager->mrows;
            } else {
              qrmanager->minRowCol = qrmanager->ncols + 1;
            }

            iQR0 = qrmanager->ldq * qrmanager->ncols;
            nActiveConstr = qrmanager->ldq;
            if (qrmanager->mrows != 0) {
              iyend = iQR0 + qrmanager->mrows;
              if (iQR0 + 1 <= iyend) {
                std::memset(&qrmanager->QR.data[iQR0], 0, static_cast<uint32_T>
                            (iyend - iQR0) * sizeof(real_T));
              }

              iy = (qrmanager->mrows - 1) * qrmanager->ldq + 1;
              for (iyend = 1; nActiveConstr < 0 ? iyend >= iy : iyend <= iy;
                   iyend += nActiveConstr) {
                normDelta = 0.0;
                idxRotGCol = iyend + qrmanager->mrows;
                for (idx = iyend; idx < idxRotGCol; idx++) {
                  normDelta += workingset->ATwset.data[(nrows + idx) - iyend] *
                    qrmanager->Q.data[idx - 1];
                }

                qrmanager->QR.data[iQR0] += normDelta;
                iQR0++;
              }
            }

            qrmanager->ncols++;
            qrmanager->jpvt.data[qrmanager->ncols - 1] = qrmanager->ncols;
            for (idx = qrmanager->mrows - 2; idx + 2 > qrmanager->ncols; idx--)
            {
              idxRotGCol = (qrmanager->ncols - 1) * qrmanager->ldq;
              iQR0 = (idx + idxRotGCol) + 1;
              temp = qrmanager->QR.data[iQR0];
              xrotg(&qrmanager->QR.data[idx + idxRotGCol], &temp, &normDelta, &s);
              qrmanager->QR.data[iQR0] = temp;
              idxRotGCol = qrmanager->ldq * idx;
              nActiveConstr = qrmanager->mrows;
              if (qrmanager->mrows >= 1) {
                iy = qrmanager->ldq + idxRotGCol;
                for (iyend = 0; iyend < nActiveConstr; iyend++) {
                  iQR0 = iy + iyend;
                  nrows = idxRotGCol + iyend;
                  temp = qrmanager->Q.data[nrows] * normDelta +
                    qrmanager->Q.data[iQR0] * s;
                  qrmanager->Q.data[iQR0] = qrmanager->Q.data[iQR0] * normDelta
                    - qrmanager->Q.data[nrows] * s;
                  qrmanager->Q.data[nrows] = temp;
                }
              }
            }
          }
          break;

         case -1:
          deleteColMoveEnd(qrmanager, globalActiveConstrIdx);
          break;

         default:
          {
            factorQR_p(qrmanager, workingset->ATwset.data, nVar,
                       workingset->nActiveConstr, workingset->ldA);
            nActiveConstr = qrmanager->minRowCol;
            for (iyend = 0; iyend < nActiveConstr; iyend++) {
              int32_T iy;
              iQR0 = qrmanager->ldq * iyend + iyend;
              iy = qrmanager->mrows - iyend;
              if (iy - 2 >= 0) {
                std::memcpy(&qrmanager->Q.data[iQR0 + 1], &qrmanager->
                            QR.data[iQR0 + 1], static_cast<uint32_T>(((iy + iQR0)
                  - iQR0) - 1) * sizeof(real_T));
              }
            }

            xorgqr(qrmanager->mrows, qrmanager->mrows, qrmanager->minRowCol,
                   qrmanager->Q.data, qrmanager->Q.size, qrmanager->ldq,
                   qrmanager->tau.data);
          }
          break;
        }

        compute_deltax(H, solution, memspace, qrmanager, cholmanager, objective,
                       strcmp_c(options_SolverName));
        if (solution->state != -5) {
          exitg1 = 1;
        } else {
          normDelta = xnrm2_n(nVar, solution->searchDir.data);
          guard11 = true;
        }
      } else {
        iyend = solution->searchDir.size;
        if (solution->searchDir.size - 1 >= 0) {
          std::memcpy(&y_data[0], &solution->searchDir.data[0],
                      static_cast<uint32_T>(solution->searchDir.size) * sizeof
                      (real_T));
        }

        std::memset(&y_data[0], 0, static_cast<uint32_T>(nVar) * sizeof(real_T));
        if (solution->searchDir.size - 1 >= 0) {
          std::memcpy(&solution->searchDir.data[0], &y_data[0],
                      static_cast<uint32_T>(solution->searchDir.size) * sizeof
                      (real_T));
        }

        normDelta = 0.0;
        guard11 = true;
      }

      if (guard11) {
        if ((!subProblemChanged) || (normDelta < options_StepTolerance) ||
            (workingset->nActiveConstr >= nVar)) {
          nActiveConstr = qrmanager->ncols;
          if (qrmanager->ncols > 0) {
            boolean_T guard1{ false };

            guard1 = false;
            if (objective->objtype != 4) {
              normDelta = 100.0 * static_cast<real_T>(qrmanager->mrows) *
                2.2204460492503131E-16;
              updateFval = ((qrmanager->mrows > 0) && (qrmanager->ncols > 0));
              if (updateFval) {
                boolean_T guard2{ false };

                idxRotGCol = qrmanager->ncols;
                guard2 = false;
                if (qrmanager->mrows < qrmanager->ncols) {
                  iyend = (qrmanager->ncols - 1) * qrmanager->ldq +
                    qrmanager->mrows;
                  while ((idxRotGCol > qrmanager->mrows) && (std::abs
                          (qrmanager->QR.data[iyend - 1]) >= normDelta)) {
                    idxRotGCol--;
                    iyend -= qrmanager->ldq;
                  }

                  updateFval = (idxRotGCol == qrmanager->mrows);
                  if (!updateFval) {
                  } else {
                    guard2 = true;
                  }
                } else {
                  guard2 = true;
                }

                if (guard2) {
                  iyend = (idxRotGCol - 1) * qrmanager->ldq + idxRotGCol;
                  while ((idxRotGCol >= 1) && (std::abs(qrmanager->QR.data[iyend
                           - 1]) >= normDelta)) {
                    idxRotGCol--;
                    iyend = (iyend - qrmanager->ldq) - 1;
                  }

                  updateFval = (idxRotGCol == 0);
                }
              }

              if (!updateFval) {
                solution->state = -7;
              } else {
                guard1 = true;
              }
            } else {
              guard1 = true;
            }

            if (guard1) {
              xgemv_d(qrmanager->mrows, qrmanager->ncols, qrmanager->Q.data,
                      qrmanager->ldq, objective->grad.data,
                      memspace->workspace_double.data);
              if (qrmanager->ncols != 0) {
                for (iyend = nActiveConstr; iyend >= 1; iyend--) {
                  iQR0 = ((iyend - 1) * qrmanager->ldq + iyend) - 2;
                  memspace->workspace_double.data[iyend - 1] /=
                    qrmanager->QR.data[iQR0 + 1];
                  for (idx = 0; idx <= iyend - 2; idx++) {
                    idxRotGCol = (iyend - idx) - 2;
                    memspace->workspace_double.data[idxRotGCol] -=
                      memspace->workspace_double.data[iyend - 1] *
                      qrmanager->QR.data[iQR0 - idx];
                  }
                }
              }

              for (idxRotGCol = 0; idxRotGCol < nActiveConstr; idxRotGCol++) {
                solution->lambda.data[idxRotGCol] =
                  -memspace->workspace_double.data[idxRotGCol];
              }
            }
          }

          if ((solution->state != -7) || (workingset->nActiveConstr > nVar)) {
            iyend = 0;
            normDelta = 0.0;
            idx = (workingset->nWConstr[0] + workingset->nWConstr[1]) + 1;
            nrows = workingset->nActiveConstr;
            for (idxRotGCol = idx; idxRotGCol <= nrows; idxRotGCol++) {
              if (solution->lambda.data[idxRotGCol - 1] < normDelta) {
                normDelta = solution->lambda.data[idxRotGCol - 1];
                iyend = idxRotGCol;
              }
            }

            if (iyend == 0) {
              solution->state = 1;
            } else {
              activeSetChangeID = -1;
              globalActiveConstrIdx = iyend;
              subProblemChanged = true;
              removeConstr(workingset, iyend);
              solution->lambda.data[iyend - 1] = 0.0;
            }
          } else {
            iyend = workingset->nActiveConstr;
            activeSetChangeID = 0;
            globalActiveConstrIdx = workingset->nActiveConstr;
            subProblemChanged = true;
            removeConstr(workingset, workingset->nActiveConstr);
            solution->lambda.data[iyend - 1] = 0.0;
          }

          updateFval = false;
        } else {
          feasibleratiotest(solution->xstar.data, solution->searchDir.data,
                            memspace->workspace_double.data,
                            memspace->workspace_double.size, workingset->nVar,
                            workingset->ldA, workingset->Aineq.data,
                            workingset->bineq.data, workingset->lb.data,
                            workingset->indexLB.data, workingset->sizes,
                            workingset->isActiveIdx,
                            workingset->isActiveConstr.data,
                            workingset->nWConstr, objective->objtype == 5,
                            &normDelta, &updateFval, &idxRotGCol, &iyend);
          if (updateFval) {
            switch (idxRotGCol) {
             case 3:
              addAineqConstr(workingset, iyend);
              break;

             case 4:
              addBoundToActiveSetMatrix_(workingset, 4, iyend);
              break;

             default:
              addBoundToActiveSetMatrix_(workingset, 5, iyend);
              break;
            }

            activeSetChangeID = 1;
          } else {
            checkUnboundedOrIllPosed(solution, objective);
            subProblemChanged = false;
            if (workingset->nActiveConstr == 0) {
              solution->state = 1;
            }
          }

          if ((nVar >= 1) && (!(normDelta == 0.0))) {
            for (idxRotGCol = 0; idxRotGCol < nVar; idxRotGCol++) {
              solution->xstar.data[idxRotGCol] += normDelta *
                solution->searchDir.data[idxRotGCol];
            }
          }

          computeGrad_StoreHx(objective, H, f_data, solution->xstar.data);
          updateFval = true;
        }

        checkStoppingAndUpdateFval(&activeSetChangeID, f_data, solution,
          memspace, objective, workingset, qrmanager, options_ObjectiveLimit,
          runTimeOptions_MaxIterations, updateFval);
      }
    } else {
      if (!updateFval) {
        solution->fstar = computeFval_ReuseHx(objective,
          memspace->workspace_double.data, f_data, solution->xstar.data);
      }

      exitg1 = 1;
    }
  } while (exitg1 == 0);
}

// Function for MATLAB Function: '<S2>/NLMPC'
void MPC_controller::linearForm_(boolean_T obj_hasLinear, int32_T obj_nvar,
  real_T workspace_data[], const real_T H[2116], const real_T f_data[], const
  real_T x_data[])
{
  int32_T beta1;
  beta1 = 0;
  if (obj_hasLinear) {
    if (static_cast<uint8_T>(obj_nvar) - 1 >= 0) {
      std::memcpy(&workspace_data[0], &f_data[0], static_cast<uint8_T>(obj_nvar)
                  * sizeof(real_T));
    }

    beta1 = 1;
  }

  if (obj_nvar != 0) {
    int32_T e;
    int32_T ix;
    if (beta1 != 1) {
      std::memset(&workspace_data[0], 0, static_cast<uint8_T>(obj_nvar) * sizeof
                  (real_T));
    }

    ix = 0;
    e = (obj_nvar - 1) * obj_nvar + 1;
    for (beta1 = 1; obj_nvar < 0 ? beta1 >= e : beta1 <= e; beta1 += obj_nvar) {
      real_T c;
      int32_T g;
      c = 0.5 * x_data[ix];
      g = beta1 + obj_nvar;
      for (int32_T b{beta1}; b < g; b++) {
        int32_T tmp;
        tmp = b - beta1;
        workspace_data[tmp] += H[b - 1] * c;
      }

      ix++;
    }
  }
}

// Function for MATLAB Function: '<S2>/NLMPC'
real_T MPC_controller::computeFval(const s_4B8jbk60U8ZWFI1LxShFzC *obj, real_T
  workspace_data[], const real_T H[2116], const real_T f_data[], const real_T
  x_data[])
{
  real_T val;
  switch (obj->objtype) {
   case 5:
    val = x_data[obj->nvar - 1] * obj->gammaScalar;
    break;

   case 3:
    {
      linearForm_(obj->hasLinear, obj->nvar, workspace_data, H, f_data, x_data);
      val = 0.0;
      if (obj->nvar >= 1) {
        int32_T b;
        b = static_cast<uint8_T>(obj->nvar);
        for (int32_T idx{0}; idx < b; idx++) {
          val += workspace_data[idx] * x_data[idx];
        }
      }
    }
    break;

   default:
    {
      int32_T b;
      int32_T c_tmp_tmp;
      linearForm_(obj->hasLinear, obj->nvar, workspace_data, H, f_data, x_data);
      b = obj->nvar + 1;
      c_tmp_tmp = obj->maxVar - 1;
      for (int32_T idx{b}; idx <= c_tmp_tmp; idx++) {
        workspace_data[idx - 1] = 0.5 * obj->beta * x_data[idx - 1] + obj->rho;
      }

      val = 0.0;
      if (obj->maxVar - 1 >= 1) {
        b = static_cast<uint8_T>(obj->maxVar - 1);
        for (int32_T idx{0}; idx < b; idx++) {
          val += workspace_data[idx] * x_data[idx];
        }
      }
    }
    break;
  }

  return val;
}

// Function for MATLAB Function: '<S2>/NLMPC'
void MPC_controller::phaseone(const real_T H[2116], const real_T f_data[],
  s_aAq9pdCdNustb4CQC7xpeC *solution, s_AiLncvKJfAMbGh9HSVCzlG *memspace,
  s_YG0fmBFfsyHj5FdUrtbgBC *workingset, s_LP9wk1co4RSPM0xk4tXznB *qrmanager,
  s_U0bKKPZx63yLz5SynYPvR *cholmanager, s_4B8jbk60U8ZWFI1LxShFzC *objective,
  somzaGboVhDG7PNQS6E98jD *options, const somzaGboVhDG7PNQS6E98jD
  *runTimeOptions)
{
  int32_T PROBTYPE_ORIG;
  int32_T idxEndIneq;
  int32_T idxStartIneq;
  int32_T mConstr;
  int32_T nVar_tmp;
  PROBTYPE_ORIG = workingset->probType;
  nVar_tmp = workingset->nVar;
  solution->xstar.data[workingset->nVar] = solution->maxConstr + 1.0;
  if (workingset->probType == 3) {
    mConstr = 1;
  } else {
    mConstr = 4;
  }

  setProblemType(workingset, mConstr);
  idxStartIneq = (workingset->nWConstr[0] + workingset->nWConstr[1]) + 1;
  idxEndIneq = workingset->nActiveConstr;
  for (mConstr = idxStartIneq; mConstr <= idxEndIneq; mConstr++) {
    workingset->isActiveConstr.data[(workingset->isActiveIdx
      [workingset->Wid.data[mConstr - 1] - 1] + workingset->
      Wlocalidx.data[mConstr - 1]) - 2] = false;
  }

  workingset->nWConstr[2] = 0;
  workingset->nWConstr[3] = 0;
  workingset->nWConstr[4] = 0;
  workingset->nActiveConstr = workingset->nWConstr[0] + workingset->nWConstr[1];
  objective->prev_objtype = objective->objtype;
  objective->prev_nvar = objective->nvar;
  objective->prev_hasLinear = objective->hasLinear;
  objective->objtype = 5;
  objective->nvar = nVar_tmp + 1;
  objective->gammaScalar = 1.0;
  objective->hasLinear = true;
  options->ObjectiveLimit = 1.0E-6;
  options->StepTolerance = 1.4901161193847657E-10;
  solution->fstar = computeFval(objective, memspace->workspace_double.data, H,
    f_data, solution->xstar.data);
  solution->state = 5;
  iterate(H, f_data, solution, memspace, workingset, qrmanager, cholmanager,
          objective, options->SolverName, options->StepTolerance,
          options->ObjectiveLimit, runTimeOptions->MaxIterations);
  if (workingset->isActiveConstr.data[(workingset->isActiveIdx[3] +
       workingset->sizes[3]) - 2]) {
    boolean_T exitg1;
    mConstr = workingset->sizes[0] + 41;
    exitg1 = false;
    while ((!exitg1) && (mConstr <= workingset->nActiveConstr)) {
      if ((workingset->Wid.data[mConstr - 1] == 4) &&
          (workingset->Wlocalidx.data[mConstr - 1] == workingset->sizes[3])) {
        removeConstr(workingset, mConstr);
        exitg1 = true;
      } else {
        mConstr++;
      }
    }
  }

  mConstr = workingset->nActiveConstr;
  while ((mConstr > workingset->sizes[0] + 40) && (mConstr > nVar_tmp)) {
    removeConstr(workingset, mConstr);
    mConstr--;
  }

  solution->maxConstr = solution->xstar.data[nVar_tmp];
  setProblemType(workingset, PROBTYPE_ORIG);
  objective->objtype = objective->prev_objtype;
  objective->nvar = objective->prev_nvar;
  objective->hasLinear = objective->prev_hasLinear;
  options->ObjectiveLimit = (rtMinusInf);
  options->StepTolerance = 1.0E-6;
}

// Function for MATLAB Function: '<S2>/NLMPC'
void MPC_controller::driver_o(const real_T H[2116], const real_T f_data[],
  s_aAq9pdCdNustb4CQC7xpeC *solution, s_AiLncvKJfAMbGh9HSVCzlG *memspace,
  s_YG0fmBFfsyHj5FdUrtbgBC *workingset, s_LP9wk1co4RSPM0xk4tXznB *qrmanager,
  s_U0bKKPZx63yLz5SynYPvR *cholmanager, s_4B8jbk60U8ZWFI1LxShFzC *objective,
  somzaGboVhDG7PNQS6E98jD *options, somzaGboVhDG7PNQS6E98jD *runTimeOptions)
{
  real_T y_data[453];
  int32_T nVar;
  boolean_T guard1{ false };

  solution->iterations = 0;
  runTimeOptions->RemainFeasible = true;
  nVar = workingset->nVar;
  guard1 = false;
  if (workingset->probType == 3) {
    int32_T b;
    b = static_cast<uint8_T>(workingset->sizes[0]);
    for (int32_T idx{0}; idx < b; idx++) {
      solution->xstar.data[workingset->indexFixed.data[idx] - 1] =
        workingset->ub.data[workingset->indexFixed.data[idx] - 1];
    }

    b = static_cast<uint16_T>(workingset->sizes[3]);
    for (int32_T idx{0}; idx < b; idx++) {
      if (workingset->isActiveConstr.data[(workingset->isActiveIdx[3] + idx) - 1])
      {
        solution->xstar.data[workingset->indexLB.data[idx] - 1] =
          -workingset->lb.data[workingset->indexLB.data[idx] - 1];
      }
    }

    b = static_cast<uint8_T>(workingset->sizes[4]);
    for (int32_T idx{0}; idx < b; idx++) {
      if (workingset->isActiveConstr.data[(workingset->isActiveIdx[4] + idx) - 1])
      {
        solution->xstar.data[workingset->indexUB.data[idx] - 1] =
          workingset->ub.data[workingset->indexUB.data[idx] - 1];
      }
    }

    PresolveWorkingSet(solution, memspace, workingset, qrmanager);
    if (solution->state < 0) {
    } else {
      guard1 = true;
    }
  } else {
    solution->state = 82;
    guard1 = true;
  }

  if (guard1) {
    solution->iterations = 0;
    solution->maxConstr = maxConstraintViolation_in(workingset,
      solution->xstar.data);
    if (solution->maxConstr > 1.0E-6) {
      phaseone(H, f_data, solution, memspace, workingset, qrmanager, cholmanager,
               objective, options, runTimeOptions);
      if (solution->state != 0) {
        solution->maxConstr = maxConstraintViolation_in(workingset,
          solution->xstar.data);
        if (solution->maxConstr > 1.0E-6) {
          std::memset(&solution->lambda.data[0], 0, static_cast<uint32_T>
                      (workingset->mConstrMax) * sizeof(real_T));
          solution->fstar = computeFval(objective,
            memspace->workspace_double.data, H, f_data, solution->xstar.data);
          solution->state = -2;
        } else {
          if (solution->maxConstr > 0.0) {
            real_T maxConstr_new;
            if (solution->searchDir.size - 1 >= 0) {
              std::memcpy(&y_data[0], &solution->searchDir.data[0], static_cast<
                          uint32_T>(solution->searchDir.size) * sizeof(real_T));
            }

            if (static_cast<uint16_T>(nVar) - 1 >= 0) {
              std::memcpy(&y_data[0], &solution->xstar.data[0],
                          static_cast<uint16_T>(nVar) * sizeof(real_T));
            }

            if (solution->searchDir.size - 1 >= 0) {
              std::memcpy(&solution->searchDir.data[0], &y_data[0],
                          static_cast<uint32_T>(solution->searchDir.size) *
                          sizeof(real_T));
            }

            PresolveWorkingSet(solution, memspace, workingset, qrmanager);
            maxConstr_new = maxConstraintViolation_in(workingset,
              solution->xstar.data);
            if (maxConstr_new >= solution->maxConstr) {
              solution->maxConstr = maxConstr_new;
              if (solution->xstar.size - 1 >= 0) {
                std::memcpy(&y_data[0], &solution->xstar.data[0],
                            static_cast<uint32_T>(solution->xstar.size) * sizeof
                            (real_T));
              }

              if (static_cast<uint16_T>(nVar) - 1 >= 0) {
                std::memcpy(&y_data[0], &solution->searchDir.data[0],
                            static_cast<uint16_T>(nVar) * sizeof(real_T));
              }

              if (solution->xstar.size - 1 >= 0) {
                std::memcpy(&solution->xstar.data[0], &y_data[0],
                            static_cast<uint32_T>(solution->xstar.size) * sizeof
                            (real_T));
              }
            }
          }

          iterate(H, f_data, solution, memspace, workingset, qrmanager,
                  cholmanager, objective, options->SolverName,
                  options->StepTolerance, options->ObjectiveLimit,
                  runTimeOptions->MaxIterations);
        }
      }
    } else {
      iterate(H, f_data, solution, memspace, workingset, qrmanager, cholmanager,
              objective, options->SolverName, options->StepTolerance,
              options->ObjectiveLimit, runTimeOptions->MaxIterations);
    }
  }
}

// Function for MATLAB Function: '<S2>/NLMPC'
void MPC_controller::addAeqConstr(s_YG0fmBFfsyHj5FdUrtbgBC *obj, int32_T
  idx_local)
{
  int32_T totalEq;
  totalEq = obj->nWConstr[0] + obj->nWConstr[1];
  if ((obj->nActiveConstr == totalEq) && (idx_local > obj->nWConstr[1])) {
    int32_T iAeq0;
    int32_T iAw0;
    int32_T iAw0_tmp;
    obj->nWConstr[1]++;
    obj->isActiveConstr.data[(obj->isActiveIdx[1] + idx_local) - 2] = true;
    obj->nActiveConstr++;
    obj->Wid.data[obj->nActiveConstr - 1] = 2;
    obj->Wlocalidx.data[obj->nActiveConstr - 1] = idx_local;
    iAeq0 = (idx_local - 1) * obj->ldA;
    iAw0 = (obj->nActiveConstr - 1) * obj->ldA;
    iAw0_tmp = static_cast<uint8_T>(obj->nVar);
    for (totalEq = 0; totalEq < iAw0_tmp; totalEq++) {
      obj->ATwset.data[iAw0 + totalEq] = obj->Aeq.data[iAeq0 + totalEq];
    }

    obj->bwset.data[obj->nActiveConstr - 1] = obj->beq[idx_local - 1];
  } else {
    int32_T c;
    int32_T iAeq0;
    int32_T iAw0;
    int32_T iAw0_tmp;
    obj->nActiveConstr++;
    iAw0 = obj->nActiveConstr - 1;
    obj->Wid.data[obj->nActiveConstr - 1] = obj->Wid.data[totalEq];
    obj->Wlocalidx.data[iAw0] = obj->Wlocalidx.data[totalEq];
    iAw0_tmp = static_cast<uint8_T>(obj->nVar);
    for (iAeq0 = 0; iAeq0 < iAw0_tmp; iAeq0++) {
      obj->ATwset.data[iAeq0 + obj->ldA * iAw0] = obj->ATwset.data[obj->ldA *
        totalEq + iAeq0];
    }

    obj->bwset.data[iAw0] = obj->bwset.data[totalEq];
    obj->nWConstr[1]++;
    obj->isActiveConstr.data[(obj->isActiveIdx[1] + idx_local) - 2] = true;
    obj->Wid.data[totalEq] = 2;
    obj->Wlocalidx.data[totalEq] = idx_local;
    iAeq0 = (idx_local - 1) * obj->ldA;
    iAw0 = obj->ldA * totalEq;
    c = static_cast<uint8_T>(obj->nVar);
    for (iAw0_tmp = 0; iAw0_tmp < c; iAw0_tmp++) {
      obj->ATwset.data[iAw0 + iAw0_tmp] = obj->Aeq.data[iAeq0 + iAw0_tmp];
    }

    obj->bwset.data[totalEq] = obj->beq[idx_local - 1];
  }
}

// Function for MATLAB Function: '<S2>/NLMPC'
boolean_T MPC_controller::soc(const real_T Hessian[2116], const real_T
  grad_data[], s_aAq9pdCdNustb4CQC7xpeC *TrialState, s_AiLncvKJfAMbGh9HSVCzlG
  *memspace, s_YG0fmBFfsyHj5FdUrtbgBC *WorkingSet, s_LP9wk1co4RSPM0xk4tXznB
  *QRManager, s_U0bKKPZx63yLz5SynYPvR *CholManager, s_4B8jbk60U8ZWFI1LxShFzC
  *QPObjective, const somzaGboVhDG7PNQS6E98jD *qpoptions)
{
  somzaGboVhDG7PNQS6E98jD qpoptions_0;
  somzaGboVhDG7PNQS6E98jD qpoptions_1;
  real_T b_c;
  int32_T idxIneqOffset;
  int32_T idx_Aineq;
  int32_T idx_lower;
  int32_T ix;
  int32_T iy;
  int32_T mConstrMax;
  int32_T mLB;
  int32_T n;
  int32_T nVar;
  int32_T nWIneq_old;
  int32_T nWLower_old;
  int32_T nWUpper_old;
  boolean_T success;
  nWIneq_old = WorkingSet->nWConstr[2];
  nWLower_old = WorkingSet->nWConstr[3];
  nWUpper_old = WorkingSet->nWConstr[4];
  nVar = WorkingSet->nVar;
  mConstrMax = WorkingSet->mConstrMax;
  mLB = static_cast<uint8_T>(WorkingSet->nVar);
  for (idxIneqOffset = 0; idxIneqOffset < mLB; idxIneqOffset++) {
    TrialState->xstarsqp[idxIneqOffset] = TrialState->xstarsqp_old[idxIneqOffset];
    TrialState->socDirection.data[idxIneqOffset] = TrialState->
      xstar.data[idxIneqOffset];
  }

  if (static_cast<uint16_T>(WorkingSet->mConstrMax) - 1 >= 0) {
    std::memcpy(&TrialState->lambdaStopTest.data[0], &TrialState->lambda.data[0],
                static_cast<uint16_T>(WorkingSet->mConstrMax) * sizeof(real_T));
  }

  idxIneqOffset = WorkingSet->isActiveIdx[2];
  for (mLB = 0; mLB < 40; mLB++) {
    WorkingSet->beq[mLB] = -TrialState->cEq[mLB];
  }

  ix = WorkingSet->ldA;
  iy = 0;
  n = WorkingSet->ldA * 39 + 1;
  for (mLB = 1; ix < 0 ? mLB >= n : mLB <= n; mLB += ix) {
    b_c = 0.0;
    idx_lower = mLB + WorkingSet->nVar;
    for (idx_Aineq = mLB; idx_Aineq < idx_lower; idx_Aineq++) {
      b_c += WorkingSet->Aeq.data[idx_Aineq - 1] * TrialState->
        searchDir.data[idx_Aineq - mLB];
    }

    WorkingSet->beq[iy] += b_c;
    iy++;
  }

  for (mLB = 0; mLB < 40; mLB++) {
    WorkingSet->bwset.data[WorkingSet->sizes[0] + mLB] = WorkingSet->beq[mLB];
  }

  if (WorkingSet->sizes[2] > 0) {
    idx_Aineq = static_cast<uint8_T>(WorkingSet->sizes[2]);
    for (mLB = 0; mLB < idx_Aineq; mLB++) {
      WorkingSet->bineq.data[mLB] = -TrialState->cIneq.data[mLB];
    }

    ix = WorkingSet->ldA;
    iy = 0;
    n = (WorkingSet->sizes[2] - 1) * WorkingSet->ldA + 1;
    for (mLB = 1; ix < 0 ? mLB >= n : mLB <= n; mLB += ix) {
      b_c = 0.0;
      idx_lower = mLB + WorkingSet->nVar;
      for (idx_Aineq = mLB; idx_Aineq < idx_lower; idx_Aineq++) {
        b_c += WorkingSet->Aineq.data[idx_Aineq - 1] *
          TrialState->searchDir.data[idx_Aineq - mLB];
      }

      WorkingSet->bineq.data[iy] += b_c;
      iy++;
    }

    idx_Aineq = 1;
    idx_lower = WorkingSet->sizes[2] + 1;
    iy = (WorkingSet->sizes[2] + WorkingSet->sizes[3]) + 1;
    n = WorkingSet->nActiveConstr;
    for (mLB = idxIneqOffset; mLB <= n; mLB++) {
      switch (WorkingSet->Wid.data[mLB - 1]) {
       case 3:
        ix = idx_Aineq;
        idx_Aineq++;
        WorkingSet->bwset.data[mLB - 1] = WorkingSet->bineq.data
          [WorkingSet->Wlocalidx.data[mLB - 1] - 1];
        break;

       case 4:
        ix = idx_lower;
        idx_lower++;
        break;

       default:
        ix = iy;
        iy++;
        break;
      }

      TrialState->workingset_old.data[ix - 1] = WorkingSet->Wlocalidx.data[mLB -
        1];
    }
  }

  std::memcpy(&TrialState->xstar.data[0], &TrialState->xstarsqp[0],
              static_cast<uint8_T>(WorkingSet->nVar) * sizeof(real_T));
  qpoptions_0 = *qpoptions;
  qpoptions_1 = *qpoptions;
  driver_o(Hessian, grad_data, TrialState, memspace, WorkingSet, QRManager,
           CholManager, QPObjective, &qpoptions_0, &qpoptions_1);
  while ((WorkingSet->mEqRemoved > 0) && (WorkingSet->indexEqRemoved
          [WorkingSet->mEqRemoved - 1] >= 1)) {
    addAeqConstr(WorkingSet, WorkingSet->indexEqRemoved[WorkingSet->mEqRemoved -
                 1]);
    WorkingSet->mEqRemoved--;
  }

  ix = static_cast<uint8_T>(nVar);
  for (idxIneqOffset = 0; idxIneqOffset < ix; idxIneqOffset++) {
    b_c = TrialState->socDirection.data[idxIneqOffset];
    TrialState->socDirection.data[idxIneqOffset] = TrialState->
      xstar.data[idxIneqOffset] - TrialState->socDirection.data[idxIneqOffset];
    TrialState->xstar.data[idxIneqOffset] = b_c;
  }

  success = (xnrm2_n(nVar, TrialState->socDirection.data) <= 2.0 * xnrm2_n(nVar,
              TrialState->xstar.data));
  idxIneqOffset = WorkingSet->sizes[2];
  mLB = WorkingSet->sizes[3];
  for (nVar = 0; nVar < 40; nVar++) {
    WorkingSet->beq[nVar] = -TrialState->cEq[nVar];
  }

  for (nVar = 0; nVar < 40; nVar++) {
    WorkingSet->bwset.data[WorkingSet->sizes[0] + nVar] = WorkingSet->beq[nVar];
  }

  if (WorkingSet->sizes[2] > 0) {
    idx_Aineq = static_cast<uint8_T>(WorkingSet->sizes[2]);
    for (nVar = 0; nVar < idx_Aineq; nVar++) {
      WorkingSet->bineq.data[nVar] = -TrialState->cIneq.data[nVar];
    }

    if (!success) {
      idx_Aineq = (WorkingSet->nWConstr[0] + WorkingSet->nWConstr[1]) + 1;
      idx_lower = WorkingSet->nActiveConstr;
      for (nVar = idx_Aineq; nVar <= idx_lower; nVar++) {
        WorkingSet->isActiveConstr.data[(WorkingSet->isActiveIdx
          [WorkingSet->Wid.data[nVar - 1] - 1] + WorkingSet->Wlocalidx.data[nVar
          - 1]) - 2] = false;
      }

      WorkingSet->nWConstr[2] = 0;
      WorkingSet->nWConstr[3] = 0;
      WorkingSet->nWConstr[4] = 0;
      WorkingSet->nActiveConstr = WorkingSet->nWConstr[0] + WorkingSet->
        nWConstr[1];
      for (nVar = 0; nVar < nWIneq_old; nVar++) {
        addAineqConstr(WorkingSet, TrialState->workingset_old.data[nVar]);
      }

      for (nWIneq_old = 0; nWIneq_old < nWLower_old; nWIneq_old++) {
        addBoundToActiveSetMatrix_(WorkingSet, 4,
          TrialState->workingset_old.data[nWIneq_old + idxIneqOffset]);
      }

      for (nWLower_old = 0; nWLower_old < nWUpper_old; nWLower_old++) {
        addBoundToActiveSetMatrix_(WorkingSet, 5,
          TrialState->workingset_old.data[(nWLower_old + idxIneqOffset) + mLB]);
      }
    }
  }

  if (!success) {
    if (static_cast<uint16_T>(mConstrMax) - 1 >= 0) {
      std::memcpy(&TrialState->lambda.data[0], &TrialState->lambdaStopTest.data
                  [0], static_cast<uint16_T>(mConstrMax) * sizeof(real_T));
    }
  } else {
    sortLambdaQP(TrialState->lambda.data, WorkingSet->nActiveConstr,
                 WorkingSet->sizes, WorkingSet->isActiveIdx,
                 WorkingSet->Wid.data, WorkingSet->Wlocalidx.data,
                 memspace->workspace_double.data);
  }

  return success;
}

// Function for MATLAB Function: '<S2>/NLMPC'
void MPC_controller::normal(const real_T Hessian[2116], const real_T grad_data[],
  s_aAq9pdCdNustb4CQC7xpeC *TrialState, sG8JZ69axY52WWR6RKyApQC *MeritFunction,
  s_AiLncvKJfAMbGh9HSVCzlG *memspace, s_YG0fmBFfsyHj5FdUrtbgBC *WorkingSet,
  s_LP9wk1co4RSPM0xk4tXznB *QRManager, s_U0bKKPZx63yLz5SynYPvR *CholManager,
  s_4B8jbk60U8ZWFI1LxShFzC *QPObjective, const somzaGboVhDG7PNQS6E98jD
  *qpoptions)
{
  somzaGboVhDG7PNQS6E98jD qpoptions_0;
  somzaGboVhDG7PNQS6E98jD qpoptions_1;
  boolean_T nonlinEqRemoved;
  qpoptions_0 = *qpoptions;
  qpoptions_1 = *qpoptions;
  driver_o(Hessian, grad_data, TrialState, memspace, WorkingSet, QRManager,
           CholManager, QPObjective, &qpoptions_0, &qpoptions_1);
  if (TrialState->state > 0) {
    real_T constrViolationEq;
    real_T constrViolationIneq;
    real_T penaltyParamTrial;
    int32_T b;
    penaltyParamTrial = MeritFunction->penaltyParam;
    constrViolationEq = 0.0;
    for (int32_T k{0}; k < 40; k++) {
      constrViolationEq += std::abs(TrialState->cEq[k]);
    }

    constrViolationIneq = 0.0;
    b = static_cast<uint8_T>(WorkingSet->sizes[2]);
    for (int32_T k{0}; k < b; k++) {
      if (TrialState->cIneq.data[k] > 0.0) {
        constrViolationIneq += TrialState->cIneq.data[k];
      }
    }

    constrViolationEq += constrViolationIneq;
    constrViolationIneq = MeritFunction->linearizedConstrViol;
    MeritFunction->linearizedConstrViol = 0.0;
    constrViolationIneq += constrViolationEq;
    if ((constrViolationIneq > 2.2204460492503131E-16) && (TrialState->fstar >
         0.0)) {
      if (TrialState->sqpFval == 0.0) {
        penaltyParamTrial = 1.0;
      } else {
        penaltyParamTrial = 1.5;
      }

      penaltyParamTrial = penaltyParamTrial * TrialState->fstar /
        constrViolationIneq;
    }

    if (penaltyParamTrial < MeritFunction->penaltyParam) {
      MeritFunction->phi = penaltyParamTrial * constrViolationEq +
        TrialState->sqpFval;
      if (((MeritFunction->initConstrViolationEq +
            MeritFunction->initConstrViolationIneq) * penaltyParamTrial +
           MeritFunction->initFval) - MeritFunction->phi > static_cast<real_T>
          (MeritFunction->nPenaltyDecreases) * MeritFunction->threshold) {
        MeritFunction->nPenaltyDecreases++;
        if ((MeritFunction->nPenaltyDecreases << 1) > TrialState->sqpIterations)
        {
          MeritFunction->threshold *= 10.0;
        }

        MeritFunction->penaltyParam = std::fmax(penaltyParamTrial, 1.0E-10);
      } else {
        MeritFunction->phi = MeritFunction->penaltyParam * constrViolationEq +
          TrialState->sqpFval;
      }
    } else {
      MeritFunction->penaltyParam = std::fmax(penaltyParamTrial, 1.0E-10);
      MeritFunction->phi = MeritFunction->penaltyParam * constrViolationEq +
        TrialState->sqpFval;
    }

    MeritFunction->phiPrimePlus = std::fmin(TrialState->fstar -
      MeritFunction->penaltyParam * constrViolationEq, 0.0);
  }

  sortLambdaQP(TrialState->lambda.data, WorkingSet->nActiveConstr,
               WorkingSet->sizes, WorkingSet->isActiveIdx, WorkingSet->Wid.data,
               WorkingSet->Wlocalidx.data, memspace->workspace_double.data);
  nonlinEqRemoved = (WorkingSet->mEqRemoved > 0);
  while ((WorkingSet->mEqRemoved > 0) && (WorkingSet->indexEqRemoved
          [WorkingSet->mEqRemoved - 1] >= 1)) {
    addAeqConstr(WorkingSet, WorkingSet->indexEqRemoved[WorkingSet->mEqRemoved -
                 1]);
    WorkingSet->mEqRemoved--;
  }

  if (nonlinEqRemoved) {
    for (int32_T k{0}; k < 40; k++) {
      WorkingSet->Wlocalidx.data[WorkingSet->sizes[0] + k] = k + 1;
    }
  }
}

// Function for MATLAB Function: '<S2>/NLMPC'
void MPC_controller::relaxed(const real_T Hessian[2116], const real_T grad_data[],
  s_aAq9pdCdNustb4CQC7xpeC *TrialState, sG8JZ69axY52WWR6RKyApQC *MeritFunction,
  s_AiLncvKJfAMbGh9HSVCzlG *memspace, s_YG0fmBFfsyHj5FdUrtbgBC *WorkingSet,
  s_LP9wk1co4RSPM0xk4tXznB *QRManager, s_U0bKKPZx63yLz5SynYPvR *CholManager,
  s_4B8jbk60U8ZWFI1LxShFzC *QPObjective, somzaGboVhDG7PNQS6E98jD *qpoptions)
{
  somzaGboVhDG7PNQS6E98jD qpoptions_0;
  somzaGboVhDG7PNQS6E98jD qpoptions_1;
  real_T beta;
  real_T s;
  real_T smax;
  int32_T idx_max;
  int32_T ix;
  int32_T mFiniteLBOrig;
  int32_T mLBOrig;
  int32_T mLBOrig_tmp;
  int32_T nVarOrig;
  boolean_T tf;
  nVarOrig = WorkingSet->nVar - 1;
  beta = 0.0;
  idx_max = static_cast<uint8_T>(WorkingSet->nVar);
  for (mFiniteLBOrig = 0; mFiniteLBOrig < idx_max; mFiniteLBOrig++) {
    beta += Hessian[46 * mFiniteLBOrig + mFiniteLBOrig];
  }

  beta /= static_cast<real_T>(WorkingSet->nVar);
  if (TrialState->sqpIterations <= 1) {
    mLBOrig = QPObjective->nvar;
    if (QPObjective->nvar < 1) {
      idx_max = 0;
    } else {
      idx_max = 1;
      if (QPObjective->nvar > 1) {
        smax = std::abs(grad_data[0]);
        for (mFiniteLBOrig = 2; mFiniteLBOrig <= mLBOrig; mFiniteLBOrig++) {
          s = std::abs(grad_data[mFiniteLBOrig - 1]);
          if (s > smax) {
            idx_max = mFiniteLBOrig;
            smax = s;
          }
        }
      }
    }

    smax = std::fmax(1.0, std::abs(grad_data[idx_max - 1])) * 100.0;
  } else {
    mLBOrig = WorkingSet->mConstr;
    if (WorkingSet->mConstr < 1) {
      idx_max = 0;
    } else {
      idx_max = 1;
      if (WorkingSet->mConstr > 1) {
        smax = std::abs(TrialState->lambdasqp.data[0]);
        for (mFiniteLBOrig = 2; mFiniteLBOrig <= mLBOrig; mFiniteLBOrig++) {
          s = std::abs(TrialState->lambdasqp.data[mFiniteLBOrig - 1]);
          if (s > smax) {
            idx_max = mFiniteLBOrig;
            smax = s;
          }
        }
      }
    }

    smax = std::abs(TrialState->lambdasqp.data[idx_max - 1]);
  }

  QPObjective->nvar = WorkingSet->nVar;
  QPObjective->beta = beta;
  QPObjective->rho = smax;
  QPObjective->hasLinear = true;
  QPObjective->objtype = 4;
  rtDW.b_WorkingSet = *WorkingSet;
  setProblemType(&rtDW.b_WorkingSet, 2);
  idx_max = rtDW.b_WorkingSet.sizes[2] + 1;
  mLBOrig = (rtDW.b_WorkingSet.sizes[3] - rtDW.b_WorkingSet.sizes[2]) - 80;
  ix = static_cast<uint16_T>(rtDW.b_WorkingSet.sizes[2]);
  if (ix - 1 >= 0) {
    std::memcpy(&memspace->workspace_double.data[0],
                &rtDW.b_WorkingSet.bineq.data[0], static_cast<uint32_T>(ix) *
                sizeof(real_T));
  }

  xgemv_dffoyl1jt(WorkingSet->nVar, rtDW.b_WorkingSet.sizes[2],
                  rtDW.b_WorkingSet.Aineq.data, rtDW.b_WorkingSet.ldA,
                  TrialState->xstar.data, memspace->workspace_double.data);
  ix = static_cast<uint8_T>(rtDW.b_WorkingSet.sizes[2]);
  for (mFiniteLBOrig = 0; mFiniteLBOrig < ix; mFiniteLBOrig++) {
    TrialState->xstar.data[(nVarOrig + mFiniteLBOrig) + 1] = static_cast<real_T>
      (memspace->workspace_double.data[mFiniteLBOrig] > 0.0) *
      memspace->workspace_double.data[mFiniteLBOrig];
  }

  std::memcpy(&memspace->workspace_double.data[0], &rtDW.b_WorkingSet.beq[0],
              40U * sizeof(real_T));
  xgemv_dffoyl1jt(WorkingSet->nVar, 40, rtDW.b_WorkingSet.Aeq.data,
                  rtDW.b_WorkingSet.ldA, TrialState->xstar.data,
                  memspace->workspace_double.data);
  for (mFiniteLBOrig = 0; mFiniteLBOrig < 40; mFiniteLBOrig++) {
    ix = idx_max + mFiniteLBOrig;
    if (memspace->workspace_double.data[mFiniteLBOrig] <= 0.0) {
      TrialState->xstar.data[nVarOrig + ix] = 0.0;
      TrialState->xstar.data[(nVarOrig + ix) + 40] =
        -memspace->workspace_double.data[mFiniteLBOrig];
      addBoundToActiveSetMatrix_(&rtDW.b_WorkingSet, 4, mLBOrig + ix);
      if (memspace->workspace_double.data[mFiniteLBOrig] >= -1.0E-6) {
        addBoundToActiveSetMatrix_(&rtDW.b_WorkingSet, 4, (mLBOrig + ix) + 40);
      }
    } else {
      mLBOrig_tmp = nVarOrig + ix;
      TrialState->xstar.data[mLBOrig_tmp] = memspace->
        workspace_double.data[mFiniteLBOrig];
      TrialState->xstar.data[mLBOrig_tmp + 40] = 0.0;
      addBoundToActiveSetMatrix_(&rtDW.b_WorkingSet, 4, (mLBOrig + ix) + 40);
      if (memspace->workspace_double.data[mFiniteLBOrig] <= 1.0E-6) {
        addBoundToActiveSetMatrix_(&rtDW.b_WorkingSet, 4, mLBOrig + ix);
      }
    }
  }

  nVarOrig = qpoptions->MaxIterations;
  qpoptions->MaxIterations = (qpoptions->MaxIterations + rtDW.b_WorkingSet.nVar)
    - WorkingSet->nVar;
  qpoptions_0 = *qpoptions;
  qpoptions_1 = *qpoptions;
  driver_o(Hessian, grad_data, TrialState, memspace, &rtDW.b_WorkingSet,
           QRManager, CholManager, QPObjective, &qpoptions_0, &qpoptions_1);
  qpoptions->MaxIterations = nVarOrig;
  idx_max = rtDW.b_WorkingSet.sizes[3] - 81;
  nVarOrig = 0;
  for (mFiniteLBOrig = 0; mFiniteLBOrig < 40; mFiniteLBOrig++) {
    boolean_T b_tf;
    mLBOrig = (rtDW.b_WorkingSet.isActiveIdx[3] + idx_max) + mFiniteLBOrig;
    tf = rtDW.b_WorkingSet.isActiveConstr.data[mLBOrig];
    b_tf = rtDW.b_WorkingSet.isActiveConstr.data[mLBOrig + 40];
    memspace->workspace_int.data[mFiniteLBOrig] = tf;
    memspace->workspace_int.data[mFiniteLBOrig + 40] = b_tf;
    nVarOrig = (nVarOrig + tf) + b_tf;
  }

  mLBOrig = static_cast<uint8_T>(rtDW.b_WorkingSet.sizes[2]);
  for (mFiniteLBOrig = 0; mFiniteLBOrig < mLBOrig; mFiniteLBOrig++) {
    tf = rtDW.b_WorkingSet.isActiveConstr.data[((rtDW.b_WorkingSet.isActiveIdx[3]
      + idx_max) - rtDW.b_WorkingSet.sizes[2]) + mFiniteLBOrig];
    memspace->workspace_int.data[mFiniteLBOrig + 80] = tf;
    nVarOrig += tf;
  }

  if (TrialState->state != -6) {
    real_T qpfvalQuadExcess;
    real_T qpfvalQuadExcess_tmp;
    idx_max = (rtDW.b_WorkingSet.nVarMax - WorkingSet->nVar) - 1;
    mLBOrig_tmp = WorkingSet->nVar + 1;
    s = 0.0;
    qpfvalQuadExcess = 0.0;
    if (idx_max >= 1) {
      ix = WorkingSet->nVar + idx_max;
      for (mFiniteLBOrig = mLBOrig_tmp; mFiniteLBOrig <= ix; mFiniteLBOrig++) {
        s += std::abs(TrialState->xstar.data[mFiniteLBOrig - 1]);
      }

      idx_max = static_cast<uint8_T>(idx_max);
      for (mFiniteLBOrig = 0; mFiniteLBOrig < idx_max; mFiniteLBOrig++) {
        qpfvalQuadExcess_tmp = TrialState->xstar.data[WorkingSet->nVar +
          mFiniteLBOrig];
        qpfvalQuadExcess += qpfvalQuadExcess_tmp * qpfvalQuadExcess_tmp;
      }
    }

    beta = (TrialState->fstar - smax * s) - beta / 2.0 * qpfvalQuadExcess;
    mLBOrig = (WorkingSet->nVarMax - WorkingSet->nVar) - 1;
    smax = MeritFunction->penaltyParam;
    s = 0.0;
    for (mFiniteLBOrig = 0; mFiniteLBOrig < 40; mFiniteLBOrig++) {
      s += std::abs(TrialState->cEq[mFiniteLBOrig]);
    }

    qpfvalQuadExcess = 0.0;
    ix = static_cast<uint8_T>(WorkingSet->sizes[2]);
    for (mFiniteLBOrig = 0; mFiniteLBOrig < ix; mFiniteLBOrig++) {
      if (TrialState->cIneq.data[mFiniteLBOrig] > 0.0) {
        qpfvalQuadExcess += TrialState->cIneq.data[mFiniteLBOrig];
      }
    }

    s += qpfvalQuadExcess;
    qpfvalQuadExcess = MeritFunction->linearizedConstrViol;
    qpfvalQuadExcess_tmp = 0.0;
    if (mLBOrig >= 1) {
      mLBOrig += WorkingSet->nVar;
      for (mFiniteLBOrig = mLBOrig_tmp; mFiniteLBOrig <= mLBOrig; mFiniteLBOrig
           ++) {
        qpfvalQuadExcess_tmp += std::abs(TrialState->xstar.data[mFiniteLBOrig -
          1]);
      }
    }

    MeritFunction->linearizedConstrViol = qpfvalQuadExcess_tmp;
    qpfvalQuadExcess = (s + qpfvalQuadExcess) - qpfvalQuadExcess_tmp;
    if ((qpfvalQuadExcess > 2.2204460492503131E-16) && (beta > 0.0)) {
      if (TrialState->sqpFval == 0.0) {
        smax = 1.0;
      } else {
        smax = 1.5;
      }

      smax = smax * beta / qpfvalQuadExcess;
    }

    if (smax < MeritFunction->penaltyParam) {
      MeritFunction->phi = smax * s + TrialState->sqpFval;
      if (((MeritFunction->initConstrViolationEq +
            MeritFunction->initConstrViolationIneq) * smax +
           MeritFunction->initFval) - MeritFunction->phi > static_cast<real_T>
          (MeritFunction->nPenaltyDecreases) * MeritFunction->threshold) {
        MeritFunction->nPenaltyDecreases++;
        if ((MeritFunction->nPenaltyDecreases << 1) > TrialState->sqpIterations)
        {
          MeritFunction->threshold *= 10.0;
        }

        MeritFunction->penaltyParam = std::fmax(smax, 1.0E-10);
      } else {
        MeritFunction->phi = MeritFunction->penaltyParam * s +
          TrialState->sqpFval;
      }
    } else {
      MeritFunction->penaltyParam = std::fmax(smax, 1.0E-10);
      MeritFunction->phi = MeritFunction->penaltyParam * s + TrialState->sqpFval;
    }

    MeritFunction->phiPrimePlus = std::fmin(beta - MeritFunction->penaltyParam *
      s, 0.0);
    idx_max = rtDW.b_WorkingSet.isActiveIdx[1] - 1;
    for (mFiniteLBOrig = 0; mFiniteLBOrig < 40; mFiniteLBOrig++) {
      if (memspace->workspace_int.data[mFiniteLBOrig] != 0) {
        tf = (memspace->workspace_int.data[mFiniteLBOrig + 40] != 0);
      } else {
        tf = false;
      }

      mLBOrig = idx_max + mFiniteLBOrig;
      TrialState->lambda.data[mLBOrig] *= static_cast<real_T>(tf);
    }

    idx_max = rtDW.b_WorkingSet.isActiveIdx[2];
    mLBOrig = rtDW.b_WorkingSet.nActiveConstr;
    for (mFiniteLBOrig = idx_max; mFiniteLBOrig <= mLBOrig; mFiniteLBOrig++) {
      if (rtDW.b_WorkingSet.Wid.data[mFiniteLBOrig - 1] == 3) {
        TrialState->lambda.data[mFiniteLBOrig - 1] *= static_cast<real_T>
          (memspace->
           workspace_int.data[rtDW.b_WorkingSet.Wlocalidx.data[mFiniteLBOrig - 1]
           + 79]);
      }
    }
  }

  rtDW.c_WorkingSet = rtDW.b_WorkingSet;
  mFiniteLBOrig = (rtDW.b_WorkingSet.sizes[3] - rtDW.b_WorkingSet.sizes[2]) - 80;
  idx_max = rtDW.b_WorkingSet.nActiveConstr;
  while ((idx_max > rtDW.b_WorkingSet.sizes[0] + 40) && (nVarOrig > 0)) {
    if ((rtDW.c_WorkingSet.Wid.data[idx_max - 1] == 4) &&
        (rtDW.c_WorkingSet.Wlocalidx.data[idx_max - 1] > mFiniteLBOrig)) {
      beta = TrialState->lambda.data[rtDW.c_WorkingSet.nActiveConstr - 1];
      TrialState->lambda.data[rtDW.c_WorkingSet.nActiveConstr - 1] = 0.0;
      TrialState->lambda.data[idx_max - 1] = beta;
      removeConstr(&rtDW.c_WorkingSet, idx_max);
      nVarOrig--;
    }

    idx_max--;
  }

  QPObjective->nvar = WorkingSet->nVar;
  QPObjective->hasLinear = true;
  QPObjective->objtype = 3;
  *WorkingSet = rtDW.c_WorkingSet;
  setProblemType(WorkingSet, 3);
  sortLambdaQP(TrialState->lambda.data, WorkingSet->nActiveConstr,
               WorkingSet->sizes, WorkingSet->isActiveIdx, WorkingSet->Wid.data,
               WorkingSet->Wlocalidx.data, memspace->workspace_double.data);
}

// Function for MATLAB Function: '<S2>/NLMPC'
boolean_T MPC_controller::step_k(int32_T *STEP_TYPE, real_T Hessian[2116], const
  real_T lb[46], s_aAq9pdCdNustb4CQC7xpeC *TrialState, sG8JZ69axY52WWR6RKyApQC
  *MeritFunction, s_AiLncvKJfAMbGh9HSVCzlG *memspace, s_YG0fmBFfsyHj5FdUrtbgBC
  *WorkingSet, s_LP9wk1co4RSPM0xk4tXznB *QRManager, s_U0bKKPZx63yLz5SynYPvR
  *CholManager, s_4B8jbk60U8ZWFI1LxShFzC *QPObjective, somzaGboVhDG7PNQS6E98jD
  *qpoptions)
{
  real_T y_data[453];
  real_T m_data[247];
  real_T nrmDirInf;
  real_T nrmGradInf;
  int32_T idxEndIneq;
  int32_T loop_ub;
  int32_T nVar;
  boolean_T checkBoundViolation;
  boolean_T stepSuccess;
  stepSuccess = true;
  checkBoundViolation = true;
  nVar = WorkingSet->nVar;
  if (*STEP_TYPE != 3) {
    std::memcpy(&TrialState->xstar.data[0], &TrialState->xstarsqp[0],
                static_cast<uint8_T>(WorkingSet->nVar) * sizeof(real_T));
  } else {
    if (TrialState->searchDir.size - 1 >= 0) {
      std::memcpy(&y_data[0], &TrialState->searchDir.data[0], static_cast<
                  uint32_T>(TrialState->searchDir.size) * sizeof(real_T));
    }

    if (static_cast<uint16_T>(WorkingSet->nVar) - 1 >= 0) {
      std::memcpy(&y_data[0], &TrialState->xstar.data[0], static_cast<uint16_T>
                  (WorkingSet->nVar) * sizeof(real_T));
    }

    if (TrialState->searchDir.size - 1 >= 0) {
      std::memcpy(&TrialState->searchDir.data[0], &y_data[0],
                  static_cast<uint32_T>(TrialState->searchDir.size) * sizeof
                  (real_T));
    }
  }

  int32_T exitg1;
  boolean_T guard1{ false };

  do {
    int32_T idxStartIneq;
    exitg1 = 0;
    guard1 = false;
    switch (*STEP_TYPE) {
     case 1:
      normal(Hessian, TrialState->grad.data, TrialState, MeritFunction, memspace,
             WorkingSet, QRManager, CholManager, QPObjective, qpoptions);
      if ((TrialState->state <= 0) && (TrialState->state != -6)) {
        *STEP_TYPE = 2;
      } else {
        if (TrialState->delta_x.size - 1 >= 0) {
          std::memcpy(&y_data[0], &TrialState->delta_x.data[0],
                      static_cast<uint32_T>(TrialState->delta_x.size) * sizeof
                      (real_T));
        }

        if (static_cast<uint16_T>(nVar) - 1 >= 0) {
          std::memcpy(&y_data[0], &TrialState->xstar.data[0],
                      static_cast<uint16_T>(nVar) * sizeof(real_T));
        }

        if (TrialState->delta_x.size - 1 >= 0) {
          std::memcpy(&TrialState->delta_x.data[0], &y_data[0],
                      static_cast<uint32_T>(TrialState->delta_x.size) * sizeof
                      (real_T));
        }

        guard1 = true;
      }
      break;

     case 2:
      idxStartIneq = (WorkingSet->nWConstr[0] + WorkingSet->nWConstr[1]) + 1;
      idxEndIneq = WorkingSet->nActiveConstr;
      for (loop_ub = idxStartIneq; loop_ub <= idxEndIneq; loop_ub++) {
        WorkingSet->isActiveConstr.data[(WorkingSet->isActiveIdx
          [WorkingSet->Wid.data[loop_ub - 1] - 1] + WorkingSet->
          Wlocalidx.data[loop_ub - 1]) - 2] = false;
      }

      WorkingSet->nWConstr[2] = 0;
      WorkingSet->nWConstr[3] = 0;
      WorkingSet->nWConstr[4] = 0;
      WorkingSet->nActiveConstr = WorkingSet->nWConstr[0] + WorkingSet->
        nWConstr[1];
      if (TrialState->xstar.size - 1 >= 0) {
        std::memcpy(&m_data[0], &TrialState->xstar.data[0], static_cast<uint32_T>
                    (TrialState->xstar.size) * sizeof(real_T));
      }

      idxStartIneq = static_cast<uint16_T>(WorkingSet->sizes[3]);
      for (loop_ub = 0; loop_ub < idxStartIneq; loop_ub++) {
        nrmGradInf = WorkingSet->lb.data[WorkingSet->indexLB.data[loop_ub] - 1];
        if (-m_data[WorkingSet->indexLB.data[loop_ub] - 1] > nrmGradInf) {
          m_data[WorkingSet->indexLB.data[loop_ub] - 1] = -nrmGradInf + std::abs
            (nrmGradInf);
        }
      }

      if (TrialState->xstar.size - 1 >= 0) {
        std::memcpy(&TrialState->xstar.data[0], &m_data[0], static_cast<uint32_T>
                    (TrialState->xstar.size) * sizeof(real_T));
      }

      relaxed(Hessian, TrialState->grad.data, TrialState, MeritFunction,
              memspace, WorkingSet, QRManager, CholManager, QPObjective,
              qpoptions);
      if (TrialState->delta_x.size - 1 >= 0) {
        std::memcpy(&y_data[0], &TrialState->delta_x.data[0],
                    static_cast<uint32_T>(TrialState->delta_x.size) * sizeof
                    (real_T));
      }

      if (static_cast<uint16_T>(nVar) - 1 >= 0) {
        std::memcpy(&y_data[0], &TrialState->xstar.data[0], static_cast<uint16_T>
                    (nVar) * sizeof(real_T));
      }

      if (TrialState->delta_x.size - 1 >= 0) {
        std::memcpy(&TrialState->delta_x.data[0], &y_data[0],
                    static_cast<uint32_T>(TrialState->delta_x.size) * sizeof
                    (real_T));
      }

      guard1 = true;
      break;

     default:
      stepSuccess = soc(Hessian, TrialState->grad.data, TrialState, memspace,
                        WorkingSet, QRManager, CholManager, QPObjective,
                        qpoptions);
      checkBoundViolation = stepSuccess;
      if (stepSuccess && (TrialState->state != -6)) {
        idxStartIneq = static_cast<uint8_T>(nVar);
        for (loop_ub = 0; loop_ub < idxStartIneq; loop_ub++) {
          TrialState->delta_x.data[loop_ub] = TrialState->xstar.data[loop_ub] +
            TrialState->socDirection.data[loop_ub];
        }
      }

      guard1 = true;
      break;
    }

    if (guard1) {
      if (TrialState->state != -6) {
        exitg1 = 1;
      } else {
        nrmGradInf = 0.0;
        nrmDirInf = 1.0;
        for (loop_ub = 0; loop_ub < 46; loop_ub++) {
          nrmGradInf = std::fmax(nrmGradInf, std::abs(TrialState->
            grad.data[loop_ub]));
          nrmDirInf = std::fmax(nrmDirInf, std::abs(TrialState->
            xstar.data[loop_ub]));
        }

        nrmGradInf = std::fmax(2.2204460492503131E-16, nrmGradInf / nrmDirInf);
        for (loop_ub = 0; loop_ub < 46; loop_ub++) {
          idxEndIneq = 46 * loop_ub;
          for (idxStartIneq = 0; idxStartIneq < loop_ub; idxStartIneq++) {
            Hessian[idxEndIneq + idxStartIneq] = 0.0;
          }

          Hessian[loop_ub + 46 * loop_ub] = nrmGradInf;
          idxEndIneq += loop_ub;
          if (44 - loop_ub >= 0) {
            std::memset(&Hessian[idxEndIneq + 1], 0, static_cast<uint32_T>((((44
              - loop_ub) + idxEndIneq) - idxEndIneq) + 1) * sizeof(real_T));
          }
        }
      }
    }
  } while (exitg1 == 0);

  if (checkBoundViolation) {
    idxEndIneq = TrialState->delta_x.size;
    if (TrialState->delta_x.size - 1 >= 0) {
      std::memcpy(&m_data[0], &TrialState->delta_x.data[0], static_cast<uint32_T>
                  (TrialState->delta_x.size) * sizeof(real_T));
    }

    loop_ub = static_cast<uint16_T>(WorkingSet->sizes[3]);
    for (nVar = 0; nVar < loop_ub; nVar++) {
      nrmDirInf = m_data[WorkingSet->indexLB.data[nVar] - 1];
      nrmGradInf = (TrialState->xstarsqp[WorkingSet->indexLB.data[nVar] - 1] +
                    nrmDirInf) - lb[WorkingSet->indexLB.data[nVar] - 1];
      if (nrmGradInf < 0.0) {
        m_data[WorkingSet->indexLB.data[nVar] - 1] = nrmDirInf - nrmGradInf;
        TrialState->xstar.data[WorkingSet->indexLB.data[nVar] - 1] -= nrmGradInf;
      }
    }

    TrialState->delta_x.size = idxEndIneq;
    if (idxEndIneq - 1 >= 0) {
      std::memcpy(&TrialState->delta_x.data[0], &m_data[0], static_cast<uint32_T>
                  (idxEndIneq) * sizeof(real_T));
    }
  }

  return stepSuccess;
}

// Function for MATLAB Function: '<S2>/NLMPC'
void MPC_controller::evalObjAndConstr(int32_T obj_next_next_next_next_next_va,
  const s_GSKgPzH92oA7AAcXEvWMnG *obj_next_next_next_next_next_ne, const
  s_OOgWGXXQYnSElkPXvuQxeH *obj_next_next_next_next_next__0, const real_T x[46],
  real_T Cineq_workspace_data[], int32_T ineq0, real_T Ceq_workspace[40], real_T
  *fval, int32_T *status)
{
  real_T c[80];
  real_T c_data[80];
  real_T X_3[44];
  real_T b_X_tmp[44];
  real_T reshapes_f1[40];
  real_T U[11];
  real_T duk;
  real_T e;
  real_T wtUerr;
  real_T wtYerr_idx_0;
  int32_T ineqRange_data[80];
  int32_T wtYerr[8];
  int32_T b_X_tmp_tmp;
  int32_T n;
  int8_T b_data[80];
  int8_T sizes[2];
  boolean_T icf[80];
  boolean_T tmp[40];
  boolean_T icf_0[8];
  boolean_T b_x[4];
  znlmpc_getXUe(x, obj_next_next_next_next_next__0->runtimedata.x, X_3, U, &e);
  wtYerr_idx_0 = 0.0;
  for (n = 0; n < 11; n++) {
    b_X_tmp_tmp = n << 2;
    b_X_tmp[b_X_tmp_tmp] = X_3[n];
    b_X_tmp[b_X_tmp_tmp + 1] = X_3[n + 11];
    b_X_tmp[b_X_tmp_tmp + 2] = X_3[n + 22];
    b_X_tmp[b_X_tmp_tmp + 3] = X_3[n + 33];
  }

  for (b_X_tmp_tmp = 0; b_X_tmp_tmp < 10; b_X_tmp_tmp++) {
    n = (b_X_tmp_tmp + 1) << 2;
    duk = (b_X_tmp[n] - obj_next_next_next_next_next__0->
           runtimedata.ref[b_X_tmp_tmp]) *
      obj_next_next_next_next_next__0->runtimedata.OutputWeights[b_X_tmp_tmp];
    wtUerr = duk * duk;
    duk = (b_X_tmp[n + 1] - obj_next_next_next_next_next__0->
           runtimedata.ref[b_X_tmp_tmp + 10]) *
      obj_next_next_next_next_next__0->runtimedata.OutputWeights[b_X_tmp_tmp +
      10];
    wtUerr += duk * duk;
    duk = (b_X_tmp[n + 2] - obj_next_next_next_next_next__0->
           runtimedata.ref[b_X_tmp_tmp + 20]) *
      obj_next_next_next_next_next__0->runtimedata.OutputWeights[b_X_tmp_tmp +
      20];
    wtUerr += duk * duk;
    duk = (b_X_tmp[n + 3] - obj_next_next_next_next_next__0->
           runtimedata.ref[b_X_tmp_tmp + 30]) *
      obj_next_next_next_next_next__0->runtimedata.OutputWeights[b_X_tmp_tmp +
      30];
    wtYerr_idx_0 += duk * duk + wtUerr;
    if (b_X_tmp_tmp + 1 == 1) {
      duk = U[b_X_tmp_tmp] - obj_next_next_next_next_next__0->runtimedata.lastMV;
    } else {
      duk = U[b_X_tmp_tmp] - U[b_X_tmp_tmp - 1];
    }

    wtUerr = 0.0 * U[b_X_tmp_tmp];
    duk *= 0.1;
    wtYerr_idx_0 = (wtUerr * wtUerr + wtYerr_idx_0) + duk * duk;
  }

  *fval = 100000.0 * e * e + wtYerr_idx_0;
  if (std::isinf(*fval) || std::isnan(*fval)) {
    if (std::isnan(*fval)) {
      *status = -3;
    } else if (*fval < 0.0) {
      *status = -1;
    } else {
      *status = -2;
    }
  } else {
    real_T U_0;
    real_T reshapes_f1_tmp;
    real_T reshapes_f1_tmp_0;
    real_T reshapes_f1_tmp_1;
    real_T reshapes_f1_tmp_2;
    real_T wtYerr_idx_3;
    int32_T ineqRange_size_idx_1;
    int32_T yk;
    int8_T sizes_idx_1;
    boolean_T exitg1;
    boolean_T y;
    if (obj_next_next_next_next_next_va - 1 < 0) {
      n = 0;
    } else {
      n = static_cast<uint8_T>(obj_next_next_next_next_next_va - 1) + 1;
    }

    ineqRange_size_idx_1 = n;
    if (n > 0) {
      ineqRange_data[0] = 0;
      yk = 0;
      for (b_X_tmp_tmp = 2; b_X_tmp_tmp <= n; b_X_tmp_tmp++) {
        yk++;
        ineqRange_data[b_X_tmp_tmp - 1] = yk;
      }
    }

    yk = n - 1;
    for (n = 0; n <= yk; n++) {
      ineqRange_data[n] += ineq0;
    }

    znlmpc_getXUe(x, obj_next_next_next_next_next_ne->x, X_3, U, &e);
    std::memset(&reshapes_f1[0], 0, 40U * sizeof(real_T));
    wtYerr_idx_0 = 1.0;
    duk = 2.0;
    wtUerr = 3.0;
    wtYerr_idx_3 = 4.0;
    for (n = 0; n < 11; n++) {
      b_X_tmp_tmp = n << 2;
      b_X_tmp[b_X_tmp_tmp] = X_3[n];
      b_X_tmp[b_X_tmp_tmp + 1] = X_3[n + 11];
      b_X_tmp[b_X_tmp_tmp + 2] = X_3[n + 22];
      b_X_tmp[b_X_tmp_tmp + 3] = X_3[n + 33];
    }

    for (b_X_tmp_tmp = 0; b_X_tmp_tmp < 10; b_X_tmp_tmp++) {
      U_0 = U[b_X_tmp_tmp];
      n = b_X_tmp_tmp << 2;
      reshapes_f1_tmp = b_X_tmp[n + 1];
      yk = (b_X_tmp_tmp + 1) << 2;
      reshapes_f1_tmp_0 = b_X_tmp[yk + 1];
      reshapes_f1[static_cast<int32_T>(wtYerr_idx_0) - 1] = ((reshapes_f1_tmp_0
        + reshapes_f1_tmp) * 0.05 + b_X_tmp[n]) - b_X_tmp[yk];
      wtYerr_idx_0 += 4.0;
      reshapes_f1[static_cast<int32_T>(duk) - 1] = ((U_0 + U_0) * 0.05 +
        reshapes_f1_tmp) - reshapes_f1_tmp_0;
      duk += 4.0;
      n = b_X_tmp_tmp << 2;
      yk = (b_X_tmp_tmp + 1) << 2;
      reshapes_f1[static_cast<int32_T>(wtUerr) - 1] = ((b_X_tmp[yk + 3] +
        b_X_tmp[n + 3]) * 0.05 + b_X_tmp[n + 2]) - b_X_tmp[yk + 2];
      wtUerr += 4.0;
      reshapes_f1_tmp = b_X_tmp[yk + 2];
      reshapes_f1_tmp_0 = b_X_tmp[yk + 3];
      n = b_X_tmp_tmp << 2;
      reshapes_f1_tmp_1 = b_X_tmp[n + 2];
      reshapes_f1_tmp_2 = b_X_tmp[n + 3];
      reshapes_f1[static_cast<int32_T>(wtYerr_idx_3) - 1] = ((((((std::sin
        (reshapes_f1_tmp) * 0.1714109256825 - std::cos(reshapes_f1_tmp) *
        0.01747905 * U_0) - reshapes_f1_tmp_0 * 0.000161) - reshapes_f1_tmp_0 *
        reshapes_f1_tmp_0 * 1.0E-6) - std::tanh(reshapes_f1_tmp_0 * 150.0) *
        0.0004) / 0.0034958100000000002 + ((((std::sin(reshapes_f1_tmp_1) *
        0.1714109256825 - std::cos(reshapes_f1_tmp_1) * 0.01747905 * U_0) -
        reshapes_f1_tmp_2 * 0.000161) - reshapes_f1_tmp_2 * reshapes_f1_tmp_2 *
        1.0E-6) - std::tanh(reshapes_f1_tmp_2 * 150.0) * 0.0004) /
        0.0034958100000000002) * 0.05 + reshapes_f1_tmp_2) - reshapes_f1_tmp_0;
      wtYerr_idx_3 += 4.0;
    }

    for (n = 0; n < 40; n++) {
      tmp[n] = std::isinf(obj_next_next_next_next_next_ne->OutputMin[n]);
    }

    all(tmp, b_x);
    y = true;
    b_X_tmp_tmp = 0;
    exitg1 = false;
    while ((!exitg1) && (b_X_tmp_tmp < 4)) {
      if (!b_x[b_X_tmp_tmp]) {
        y = false;
        exitg1 = true;
      } else {
        b_X_tmp_tmp++;
      }
    }

    if (y) {
      for (n = 0; n < 40; n++) {
        tmp[n] = std::isinf(obj_next_next_next_next_next_ne->OutputMax[n]);
      }

      all(tmp, b_x);
      b_X_tmp_tmp = 0;
      exitg1 = false;
      while ((!exitg1) && (b_X_tmp_tmp < 4)) {
        if (!b_x[b_X_tmp_tmp]) {
          y = false;
          exitg1 = true;
        } else {
          b_X_tmp_tmp++;
        }
      }
    }

    if (y) {
      yk = 0;
      n = 0;
    } else {
      for (b_X_tmp_tmp = 0; b_X_tmp_tmp < 80; b_X_tmp_tmp++) {
        c[b_X_tmp_tmp] = 0.0;
        icf[b_X_tmp_tmp] = true;
      }

      wtYerr_idx_0 = 1.0;
      duk = 2.0;
      wtUerr = 3.0;
      wtYerr_idx_3 = 4.0;
      for (b_X_tmp_tmp = 0; b_X_tmp_tmp < 10; b_X_tmp_tmp++) {
        real_T icf_tmp;
        icf[static_cast<int32_T>(wtYerr_idx_0) - 1] = ((!std::isinf
          (obj_next_next_next_next_next_ne->OutputMin[b_X_tmp_tmp])) && (!std::
          isnan(obj_next_next_next_next_next_ne->OutputMin[b_X_tmp_tmp])));
        U_0 = obj_next_next_next_next_next_ne->OutputMin[b_X_tmp_tmp + 10];
        icf[static_cast<int32_T>(duk) - 1] = ((!std::isinf(U_0)) && (!std::isnan
          (U_0)));
        reshapes_f1_tmp = obj_next_next_next_next_next_ne->OutputMin[b_X_tmp_tmp
          + 20];
        icf[static_cast<int32_T>(wtUerr) - 1] = ((!std::isinf(reshapes_f1_tmp)) &&
          (!std::isnan(reshapes_f1_tmp)));
        reshapes_f1_tmp_0 = obj_next_next_next_next_next_ne->
          OutputMin[b_X_tmp_tmp + 30];
        icf[static_cast<int32_T>(wtYerr_idx_3) - 1] = ((!std::isinf
          (reshapes_f1_tmp_0)) && (!std::isnan(reshapes_f1_tmp_0)));
        icf[static_cast<int32_T>(wtYerr_idx_0 + 4.0) - 1] = ((!std::isinf
          (obj_next_next_next_next_next_ne->OutputMax[b_X_tmp_tmp])) && (!std::
          isnan(obj_next_next_next_next_next_ne->OutputMax[b_X_tmp_tmp])));
        wtYerr[0] = static_cast<int32_T>(wtYerr_idx_0) - 1;
        wtYerr[4] = static_cast<int32_T>(wtYerr_idx_0 + 4.0) - 1;
        reshapes_f1_tmp_1 = obj_next_next_next_next_next_ne->
          OutputMax[b_X_tmp_tmp + 10];
        icf[static_cast<int32_T>(duk + 4.0) - 1] = ((!std::isinf
          (reshapes_f1_tmp_1)) && (!std::isnan(reshapes_f1_tmp_1)));
        wtYerr[1] = static_cast<int32_T>(duk) - 1;
        wtYerr[5] = static_cast<int32_T>(duk + 4.0) - 1;
        reshapes_f1_tmp_2 = obj_next_next_next_next_next_ne->
          OutputMax[b_X_tmp_tmp + 20];
        icf[static_cast<int32_T>(wtUerr + 4.0) - 1] = ((!std::isinf
          (reshapes_f1_tmp_2)) && (!std::isnan(reshapes_f1_tmp_2)));
        wtYerr[2] = static_cast<int32_T>(wtUerr) - 1;
        wtYerr[6] = static_cast<int32_T>(wtUerr + 4.0) - 1;
        icf_tmp = obj_next_next_next_next_next_ne->OutputMax[b_X_tmp_tmp + 30];
        icf[static_cast<int32_T>(wtYerr_idx_3 + 4.0) - 1] = ((!std::isinf
          (icf_tmp)) && (!std::isnan(icf_tmp)));
        wtYerr[3] = static_cast<int32_T>(wtYerr_idx_3) - 1;
        wtYerr[7] = static_cast<int32_T>(wtYerr_idx_3 + 4.0) - 1;
        for (n = 0; n < 8; n++) {
          icf_0[n] = icf[wtYerr[n]];
        }

        if (any(icf_0)) {
          real_T b_yk_idx_0;
          real_T b_yk_idx_1;
          real_T b_yk_idx_2;
          real_T b_yk_idx_3;
          b_yk_idx_0 = X_3[b_X_tmp_tmp + 1];
          b_yk_idx_1 = X_3[b_X_tmp_tmp + 12];
          b_yk_idx_2 = X_3[b_X_tmp_tmp + 23];
          b_yk_idx_3 = X_3[b_X_tmp_tmp + 34];
          c[static_cast<int32_T>(wtYerr_idx_0) - 1] =
            (obj_next_next_next_next_next_ne->OutputMin[b_X_tmp_tmp] - e) -
            b_yk_idx_0;
          c[static_cast<int32_T>(duk) - 1] = (U_0 - e) - b_yk_idx_1;
          c[static_cast<int32_T>(wtUerr) - 1] = (reshapes_f1_tmp - e) -
            b_yk_idx_2;
          c[static_cast<int32_T>(wtYerr_idx_3) - 1] = (reshapes_f1_tmp_0 - e) -
            b_yk_idx_3;
          c[static_cast<int32_T>(wtYerr_idx_0 + 4.0) - 1] = (b_yk_idx_0 -
            obj_next_next_next_next_next_ne->OutputMax[b_X_tmp_tmp]) - e;
          c[static_cast<int32_T>(duk + 4.0) - 1] = (b_yk_idx_1 -
            reshapes_f1_tmp_1) - e;
          c[static_cast<int32_T>(wtUerr + 4.0) - 1] = (b_yk_idx_2 -
            reshapes_f1_tmp_2) - e;
          c[static_cast<int32_T>(wtYerr_idx_3 + 4.0) - 1] = (b_yk_idx_3 -
            icf_tmp) - e;
        }

        wtYerr_idx_0 += 8.0;
        duk += 8.0;
        wtUerr += 8.0;
        wtYerr_idx_3 += 8.0;
      }

      n = 0;
      for (b_X_tmp_tmp = 0; b_X_tmp_tmp < 80; b_X_tmp_tmp++) {
        if (icf[b_X_tmp_tmp]) {
          n++;
        }
      }

      yk = n;
      n = 0;
      for (b_X_tmp_tmp = 0; b_X_tmp_tmp < 80; b_X_tmp_tmp++) {
        if (icf[b_X_tmp_tmp]) {
          b_data[n] = static_cast<int8_T>(b_X_tmp_tmp + 1);
          n++;
        }
      }

      for (n = 0; n < yk; n++) {
        c_data[n] = c[b_data[n] - 1];
      }

      n = 1;
      if (yk - 1 >= 0) {
        std::memcpy(&c[0], &c_data[0], static_cast<uint32_T>(yk) * sizeof(real_T));
      }
    }

    sizes_idx_1 = static_cast<int8_T>((yk != 0) && (n != 0));
    if (sizes_idx_1 == 0) {
      sizes[0] = static_cast<int8_T>(yk);
    } else if ((yk != 0) && (n != 0)) {
      sizes[0] = static_cast<int8_T>(yk);
    } else {
      sizes[0] = 0;
    }

    b_X_tmp_tmp = sizes[0];
    yk = sizes_idx_1;
    for (n = 0; n < yk; n++) {
      if (b_X_tmp_tmp - 1 >= 0) {
        std::memcpy(&rtDW.varargin_1_data[0], &c[0], static_cast<uint32_T>
                    (b_X_tmp_tmp) * sizeof(real_T));
      }
    }

    for (n = 0; n < ineqRange_size_idx_1; n++) {
      Cineq_workspace_data[ineqRange_data[n] - 1] = rtDW.varargin_1_data[n];
    }

    std::memcpy(&Ceq_workspace[0], &reshapes_f1[0], 40U * sizeof(real_T));
    *status = checkVectorNonFinite(obj_next_next_next_next_next_va,
      Cineq_workspace_data, ineq0);
    if (*status == 1) {
      *status = checkVectorNonFinite_n(Ceq_workspace);
    }
  }
}

// Function for MATLAB Function: '<S2>/NLMPC'
void MPC_controller::computeLinearResiduals(const real_T x[46], int32_T nVar,
  real_T workspaceIneq_data[], const int32_T *workspaceIneq_size, int32_T
  mLinIneq, const real_T AineqT_data[], const real_T bineq_data[], int32_T ldAi)
{
  real_T y_data[453];
  if (mLinIneq > 0) {
    int32_T b;
    int32_T e;
    int32_T y_size_idx_0;
    if (*workspaceIneq_size - 1 >= 0) {
      std::memcpy(&y_data[0], &workspaceIneq_data[0], static_cast<uint32_T>
                  (*workspaceIneq_size) * sizeof(real_T));
    }

    if (static_cast<uint16_T>(mLinIneq) - 1 >= 0) {
      std::memcpy(&y_data[0], &bineq_data[0], static_cast<uint16_T>(mLinIneq) *
                  sizeof(real_T));
    }

    if (*workspaceIneq_size - 1 >= 0) {
      std::memcpy(&workspaceIneq_data[0], &y_data[0], static_cast<uint32_T>
                  (*workspaceIneq_size) * sizeof(real_T));
    }

    b = static_cast<uint8_T>(mLinIneq);
    for (int32_T loop_ub{0}; loop_ub < b; loop_ub++) {
      workspaceIneq_data[loop_ub] = -workspaceIneq_data[loop_ub];
    }

    y_size_idx_0 = 0;
    e = (mLinIneq - 1) * ldAi + 1;
    for (int32_T loop_ub{1}; ldAi < 0 ? loop_ub >= e : loop_ub <= e; loop_ub +=
         ldAi) {
      real_T c;
      int32_T f;
      c = 0.0;
      f = loop_ub + nVar;
      for (b = loop_ub; b < f; b++) {
        c += AineqT_data[b - 1] * x[b - loop_ub];
      }

      workspaceIneq_data[y_size_idx_0] += c;
      y_size_idx_0++;
    }
  }
}

// Function for MATLAB Function: '<S2>/NLMPC'
real_T MPC_controller::computeMeritFcn(real_T obj_penaltyParam, real_T fval,
  const real_T Cineq_workspace_data[], int32_T mIneq, const real_T
  Ceq_workspace[40], boolean_T evalWellDefined)
{
  real_T val;
  if (evalWellDefined) {
    real_T constrViolationEq;
    real_T constrViolationIneq;
    int32_T k;
    constrViolationEq = 0.0;
    for (k = 0; k < 40; k++) {
      constrViolationEq += std::abs(Ceq_workspace[k]);
    }

    constrViolationIneq = 0.0;
    k = static_cast<uint8_T>(mIneq);
    for (int32_T idx{0}; idx < k; idx++) {
      real_T Cineq_workspace;
      Cineq_workspace = Cineq_workspace_data[idx];
      if (Cineq_workspace > 0.0) {
        constrViolationIneq += Cineq_workspace;
      }
    }

    val = (constrViolationEq + constrViolationIneq) * obj_penaltyParam + fval;
  } else {
    val = (rtInf);
  }

  return val;
}

// Function for MATLAB Function: '<S2>/NLMPC'
void MPC_controller::linesearch(boolean_T *evalWellDefined, const real_T
  bineq_data[], int32_T WorkingSet_nVar, int32_T WorkingSet_ldA, const real_T
  WorkingSet_Aineq_data[], s_aAq9pdCdNustb4CQC7xpeC *TrialState, real_T
  MeritFunction_penaltyParam, real_T MeritFunction_phi, real_T
  MeritFunction_phiPrimePlus, real_T MeritFunction_phiFullStep, int32_T
  FcnEvaluator_next_next_next_nex, const s_GSKgPzH92oA7AAcXEvWMnG
  *FcnEvaluator_next_next_next_n_0, const s_OOgWGXXQYnSElkPXvuQxeH
  *FcnEvaluator_next_next_next_n_1, boolean_T socTaken, real_T *alpha, int32_T
  *exitflag)
{
  real_T y_data[453];
  real_T phi_alpha;
  int32_T mLinIneq;
  int32_T y_size_idx_0;
  mLinIneq = TrialState->mIneq - TrialState->mNonlinIneq;
  *alpha = 1.0;
  *exitflag = 1;
  phi_alpha = MeritFunction_phiFullStep;
  if (TrialState->searchDir.size - 1 >= 0) {
    std::memcpy(&y_data[0], &TrialState->searchDir.data[0], static_cast<uint32_T>
                (TrialState->searchDir.size) * sizeof(real_T));
  }

  if (static_cast<uint16_T>(WorkingSet_nVar) - 1 >= 0) {
    std::memcpy(&y_data[0], &TrialState->delta_x.data[0], static_cast<uint16_T>
                (WorkingSet_nVar) * sizeof(real_T));
  }

  if (TrialState->searchDir.size - 1 >= 0) {
    std::memcpy(&TrialState->searchDir.data[0], &y_data[0], static_cast<uint32_T>
                (TrialState->searchDir.size) * sizeof(real_T));
  }

  int32_T exitg1;
  do {
    exitg1 = 0;
    if (TrialState->FunctionEvaluations < 4600) {
      if ((*evalWellDefined) && (phi_alpha <= *alpha * 0.0001 *
           MeritFunction_phiPrimePlus + MeritFunction_phi)) {
        exitg1 = 1;
      } else {
        int32_T loop_ub;
        boolean_T exitg2;
        boolean_T tooSmallX;
        *alpha *= 0.7;
        loop_ub = static_cast<uint8_T>(WorkingSet_nVar);
        for (y_size_idx_0 = 0; y_size_idx_0 < loop_ub; y_size_idx_0++) {
          TrialState->delta_x.data[y_size_idx_0] = *alpha *
            TrialState->xstar.data[y_size_idx_0];
        }

        if (socTaken) {
          phi_alpha = *alpha * *alpha;
          if ((WorkingSet_nVar >= 1) && (!(phi_alpha == 0.0))) {
            for (y_size_idx_0 = 0; y_size_idx_0 < WorkingSet_nVar; y_size_idx_0
                 ++) {
              TrialState->delta_x.data[y_size_idx_0] += phi_alpha *
                TrialState->socDirection.data[y_size_idx_0];
            }
          }
        }

        tooSmallX = true;
        y_size_idx_0 = 0;
        exitg2 = false;
        while ((!exitg2) && (y_size_idx_0 <= static_cast<uint8_T>
                             (WorkingSet_nVar) - 1)) {
          if (1.0E-6 * std::fmax(1.0, std::abs(TrialState->xstarsqp[y_size_idx_0]))
              <= std::abs(TrialState->delta_x.data[y_size_idx_0])) {
            tooSmallX = false;
            exitg2 = true;
          } else {
            y_size_idx_0++;
          }
        }

        if (tooSmallX) {
          *exitflag = -2;
          exitg1 = 1;
        } else {
          for (y_size_idx_0 = 0; y_size_idx_0 < loop_ub; y_size_idx_0++) {
            TrialState->xstarsqp[y_size_idx_0] = TrialState->
              xstarsqp_old[y_size_idx_0] + TrialState->delta_x.data[y_size_idx_0];
          }

          evalObjAndConstr(FcnEvaluator_next_next_next_nex,
                           FcnEvaluator_next_next_next_n_0,
                           FcnEvaluator_next_next_next_n_1, TrialState->xstarsqp,
                           TrialState->cIneq.data, TrialState->iNonIneq0,
                           TrialState->cEq, &TrialState->sqpFval, &y_size_idx_0);
          computeLinearResiduals(TrialState->xstarsqp, WorkingSet_nVar,
            TrialState->cIneq.data, &TrialState->cIneq.size, mLinIneq,
            WorkingSet_Aineq_data, bineq_data, WorkingSet_ldA);
          TrialState->FunctionEvaluations++;
          *evalWellDefined = (y_size_idx_0 == 1);
          phi_alpha = computeMeritFcn(MeritFunction_penaltyParam,
            TrialState->sqpFval, TrialState->cIneq.data, TrialState->mIneq,
            TrialState->cEq, *evalWellDefined);
        }
      }
    } else {
      *exitflag = 0;
      exitg1 = 1;
    }
  } while (exitg1 == 0);
}

// Function for MATLAB Function: '<S2>/NLMPC'
void MPC_controller::driver(const real_T bineq_data[], const real_T lb[46],
  s_aAq9pdCdNustb4CQC7xpeC *TrialState, sG8JZ69axY52WWR6RKyApQC *MeritFunction,
  const coder_internal_stickyStruct_9 *FcnEvaluator, s_AiLncvKJfAMbGh9HSVCzlG
  *memspace, s_YG0fmBFfsyHj5FdUrtbgBC *WorkingSet, s_LP9wk1co4RSPM0xk4tXznB
  *QRManager, s_U0bKKPZx63yLz5SynYPvR *CholManager, s_4B8jbk60U8ZWFI1LxShFzC
  *QPObjective, const int32_T *fscales_lineq_constraint_size, const int32_T
  *fscales_cineq_constraint_size, real_T Hessian[2116])
{
  static const char_T x[7]{ 'f', 'm', 'i', 'n', 'c', 'o', 'n' };

  static const int8_T ab[2116]{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 };

  s7RdrPWkr8UPAUyTdDJkLaG Flags;
  somzaGboVhDG7PNQS6E98jD expl_temp;
  somzaGboVhDG7PNQS6E98jD expl_temp_0;
  real_T y_data[453];
  real_T smax;
  int32_T idx_max;
  int32_T idx_max_tmp;
  int32_T idx_max_tmp_tmp;
  int32_T mFixed;
  int32_T mIneq;
  int32_T mLB;
  int32_T mLinIneq_tmp_tmp;
  int32_T mUB;
  int32_T nVar_tmp_tmp;
  int32_T qpoptions_MaxIterations;
  int32_T u1;
  boolean_T isFeasible;
  for (idx_max_tmp = 0; idx_max_tmp < 2116; idx_max_tmp++) {
    Hessian[idx_max_tmp] = ab[idx_max_tmp];
  }

  nVar_tmp_tmp = WorkingSet->nVar;
  mFixed = WorkingSet->sizes[0];
  mIneq = WorkingSet->sizes[2];
  mLB = WorkingSet->sizes[3];
  mUB = WorkingSet->sizes[4];
  mLinIneq_tmp_tmp = WorkingSet->sizes[2] - TrialState->mNonlinIneq;
  u1 = ((WorkingSet->sizes[2] + WorkingSet->sizes[3]) + WorkingSet->sizes[4]) +
    (WorkingSet->sizes[0] << 1);
  if (WorkingSet->nVar >= u1) {
    u1 = WorkingSet->nVar;
  }

  qpoptions_MaxIterations = 10 * u1;
  TrialState->steplength = 1.0;
  Flags.fevalOK = true;
  Flags.stepAccepted = false;
  Flags.failedLineSearch = false;
  Flags.stepType = 1;
  idx_max_tmp_tmp = static_cast<uint16_T>((((WorkingSet->sizes[0] +
    WorkingSet->sizes[2]) + WorkingSet->sizes[3]) + WorkingSet->sizes[4]) + 40);
  if (idx_max_tmp_tmp - 1 >= 0) {
    std::memcpy(&TrialState->lambdaStopTest.data[0], &TrialState->
                lambdasqp.data[0], static_cast<uint32_T>(idx_max_tmp_tmp) *
                sizeof(real_T));
  }

  computeGradLag(TrialState->gradLag.data, WorkingSet->ldA, WorkingSet->nVar,
                 TrialState->grad.data, WorkingSet->sizes[2],
                 WorkingSet->Aineq.data, WorkingSet->Aeq.data,
                 WorkingSet->indexFixed.data, WorkingSet->sizes[0],
                 WorkingSet->indexLB.data, WorkingSet->sizes[3],
                 WorkingSet->indexUB.data, WorkingSet->sizes[4],
                 TrialState->lambdaStopTest.data);
  if (WorkingSet->nVar < 1) {
    idx_max = 0;
  } else {
    idx_max = 1;
    if (WorkingSet->nVar > 1) {
      smax = std::abs(TrialState->grad.data[0]);
      for (u1 = 2; u1 <= nVar_tmp_tmp; u1++) {
        real_T s;
        s = std::abs(TrialState->grad.data[u1 - 1]);
        if (s > smax) {
          idx_max = u1;
          smax = s;
        }
      }
    }
  }

  smax = std::fmax(1.0, std::abs(TrialState->grad.data[idx_max - 1]));
  if (std::isinf(smax)) {
    smax = 1.0;
  }

  MeritFunction->nlpPrimalFeasError = computePrimalFeasError
    (TrialState->xstarsqp, WorkingSet->sizes[2] - TrialState->mNonlinIneq,
     TrialState->mNonlinIneq, TrialState->cIneq.data, TrialState->cEq,
     WorkingSet->indexLB.data, WorkingSet->sizes[3], lb,
     WorkingSet->indexUB.data, WorkingSet->sizes[4]);
  MeritFunction->feasRelativeFactor = std::fmax(1.0,
    MeritFunction->nlpPrimalFeasError);
  isFeasible = (MeritFunction->nlpPrimalFeasError <= 1.0E-6 *
                MeritFunction->feasRelativeFactor);
  computeDualFeasError(WorkingSet->nVar, TrialState->gradLag.data, &Flags.gradOK,
                       &MeritFunction->nlpDualFeasError);
  if (!Flags.gradOK) {
    Flags.done = true;
    if (isFeasible) {
      TrialState->sqpExitFlag = 2;
    } else {
      TrialState->sqpExitFlag = -2;
    }
  } else {
    MeritFunction->nlpComplError = 0.0;
    MeritFunction->firstOrderOpt = std::fmax(MeritFunction->nlpDualFeasError,
      0.0);
    if (idx_max_tmp_tmp - 1 >= 0) {
      std::memcpy(&TrialState->lambdaStopTestPrev.data[0],
                  &TrialState->lambdaStopTest.data[0], static_cast<uint32_T>
                  (idx_max_tmp_tmp) * sizeof(real_T));
    }

    if (isFeasible && (MeritFunction->nlpDualFeasError <= 1.0E-6 * smax)) {
      Flags.done = true;
      TrialState->sqpExitFlag = 1;
    } else {
      Flags.done = false;
      if (isFeasible && (TrialState->sqpFval < -1.0E+20)) {
        Flags.done = true;
        TrialState->sqpExitFlag = -3;
      }
    }
  }

  saveJacobian(TrialState, WorkingSet->nVar, WorkingSet->sizes[2],
               WorkingSet->Aineq.data, TrialState->iNonIneq0,
               WorkingSet->Aeq.data, WorkingSet->ldA);
  TrialState->sqpFval_old = TrialState->sqpFval;
  for (u1 = 0; u1 < 46; u1++) {
    TrialState->xstarsqp_old[u1] = TrialState->xstarsqp[u1];
    TrialState->grad_old.data[u1] = TrialState->grad.data[u1];
  }

  u1 = TrialState->cIneq_old.size;
  if (TrialState->cIneq_old.size - 1 >= 0) {
    std::memcpy(&y_data[0], &TrialState->cIneq_old.data[0], static_cast<uint32_T>
                (TrialState->cIneq_old.size) * sizeof(real_T));
  }

  if (static_cast<uint16_T>(TrialState->mIneq) - 1 >= 0) {
    std::memcpy(&y_data[0], &TrialState->cIneq.data[0], static_cast<uint16_T>
                (TrialState->mIneq) * sizeof(real_T));
  }

  if (TrialState->cIneq_old.size - 1 >= 0) {
    std::memcpy(&TrialState->cIneq_old.data[0], &y_data[0], static_cast<uint32_T>
                (TrialState->cIneq_old.size) * sizeof(real_T));
  }

  std::memcpy(&TrialState->cEq_old[0], &TrialState->cEq[0], 40U * sizeof(real_T));
  if (!Flags.done) {
    TrialState->sqpIterations = 1;
  }

  while (!Flags.done) {
    int32_T b_nVar;
    if ((!Flags.stepAccepted) && (!Flags.failedLineSearch)) {
      expl_temp.IterDisplayQP = false;
      expl_temp.RemainFeasible = false;
      expl_temp.ProbRelTolFactor = 1.0;
      expl_temp.ConstrRelTolFactor = 1.0;
      expl_temp.PricingTolerance = 0.0;
      expl_temp.ObjectiveLimit = (rtMinusInf);
      expl_temp.ConstraintTolerance = 1.0E-6;
      expl_temp.OptimalityTolerance = 2.2204460492503131E-14;
      expl_temp.StepTolerance = 1.0E-6;
      expl_temp.MaxIterations = qpoptions_MaxIterations;
      for (idx_max_tmp = 0; idx_max_tmp < 7; idx_max_tmp++) {
        expl_temp.SolverName[idx_max_tmp] = x[idx_max_tmp];
      }
    }

    while ((!Flags.stepAccepted) && (!Flags.failedLineSearch)) {
      if (Flags.stepType != 3) {
        updateWorkingSetForNewQP(TrialState->xstarsqp, WorkingSet, mIneq,
          TrialState->mNonlinIneq, TrialState->cIneq.data, TrialState->cEq, mLB,
          lb, mUB, mFixed);
      }

      expl_temp_0 = expl_temp;
      Flags.stepAccepted = step_k(&Flags.stepType, Hessian, lb, TrialState,
        MeritFunction, memspace, WorkingSet, QRManager, CholManager, QPObjective,
        &expl_temp_0);
      if (Flags.stepAccepted) {
        b_nVar = static_cast<uint8_T>(nVar_tmp_tmp);
        for (u1 = 0; u1 < b_nVar; u1++) {
          TrialState->xstarsqp[u1] += TrialState->delta_x.data[u1];
        }

        evalObjAndConstr(FcnEvaluator->next.next.next.next.next.value,
                         &FcnEvaluator->next.next.next.next.next.next.next.value.workspace.runtimedata,
                         &FcnEvaluator->next.next.next.next.next.next.next.next.value.workspace,
                         TrialState->xstarsqp, TrialState->cIneq.data,
                         TrialState->iNonIneq0, TrialState->cEq,
                         &TrialState->sqpFval, &u1);
        Flags.fevalOK = (u1 == 1);
        TrialState->FunctionEvaluations++;
        computeLinearResiduals(TrialState->xstarsqp, nVar_tmp_tmp,
          TrialState->cIneq.data, &TrialState->cIneq.size, mLinIneq_tmp_tmp,
          WorkingSet->Aineq.data, bineq_data, WorkingSet->ldA);
        MeritFunction->phiFullStep = computeMeritFcn(MeritFunction->penaltyParam,
          TrialState->sqpFval, TrialState->cIneq.data, mIneq, TrialState->cEq,
          Flags.fevalOK);
      }

      if ((Flags.stepType == 1) && Flags.stepAccepted && Flags.fevalOK &&
          (MeritFunction->phi < MeritFunction->phiFullStep) &&
          (TrialState->sqpFval < TrialState->sqpFval_old)) {
        Flags.stepType = 3;
        Flags.stepAccepted = false;
      } else {
        linesearch(&Flags.fevalOK, bineq_data, WorkingSet->nVar, WorkingSet->ldA,
                   WorkingSet->Aineq.data, TrialState,
                   MeritFunction->penaltyParam, MeritFunction->phi,
                   MeritFunction->phiPrimePlus, MeritFunction->phiFullStep,
                   FcnEvaluator->next.next.next.next.next.value,
                   &FcnEvaluator->next.next.next.next.next.next.next.value.workspace.runtimedata,
                   &FcnEvaluator->next.next.next.next.next.next.next.next.value.workspace,
                   (Flags.stepType == 3) && Flags.stepAccepted, &smax, &u1);
        TrialState->steplength = smax;
        if (u1 > 0) {
          Flags.stepAccepted = true;
        } else {
          Flags.failedLineSearch = true;
        }
      }
    }

    if (Flags.stepAccepted && (!Flags.failedLineSearch)) {
      b_nVar = static_cast<uint8_T>(nVar_tmp_tmp);
      for (u1 = 0; u1 < b_nVar; u1++) {
        TrialState->xstarsqp[u1] = TrialState->xstarsqp_old[u1] +
          TrialState->delta_x.data[u1];
      }

      for (u1 = 0; u1 < idx_max_tmp_tmp; u1++) {
        TrialState->lambdasqp.data[u1] += (TrialState->lambda.data[u1] -
          TrialState->lambdasqp.data[u1]) * TrialState->steplength;
      }

      TrialState->sqpFval_old = TrialState->sqpFval;
      for (u1 = 0; u1 < 46; u1++) {
        TrialState->xstarsqp_old[u1] = TrialState->xstarsqp[u1];
        TrialState->grad_old.data[u1] = TrialState->grad.data[u1];
      }

      u1 = TrialState->cIneq_old.size;
      if (TrialState->cIneq_old.size - 1 >= 0) {
        std::memcpy(&y_data[0], &TrialState->cIneq_old.data[0],
                    static_cast<uint32_T>(TrialState->cIneq_old.size) * sizeof
                    (real_T));
      }

      if (static_cast<uint16_T>(TrialState->mIneq) - 1 >= 0) {
        std::memcpy(&y_data[0], &TrialState->cIneq.data[0], static_cast<uint16_T>
                    (TrialState->mIneq) * sizeof(real_T));
      }

      if (TrialState->cIneq_old.size - 1 >= 0) {
        std::memcpy(&TrialState->cIneq_old.data[0], &y_data[0],
                    static_cast<uint32_T>(TrialState->cIneq_old.size) * sizeof
                    (real_T));
      }

      std::memcpy(&TrialState->cEq_old[0], &TrialState->cEq[0], 40U * sizeof
                  (real_T));
      Flags.gradOK = true;
      evalObjAndConstrAndDerivatives
        (FcnEvaluator->next.next.next.next.next.value,
         &FcnEvaluator->next.next.next.next.next.next.next.value.workspace.runtimedata,
         &FcnEvaluator->next.next.next.next.next.next.next.next.value.workspace,
         TrialState->xstarsqp, TrialState->grad.data, TrialState->cIneq.data,
         TrialState->iNonIneq0, TrialState->cEq, WorkingSet->Aineq.data,
         TrialState->iNonIneq0, WorkingSet->ldA, WorkingSet->Aeq.data,
         WorkingSet->ldA, &TrialState->sqpFval, &u1);
      TrialState->FunctionEvaluations++;
      Flags.fevalOK = (u1 == 1);
    } else {
      TrialState->sqpFval = TrialState->sqpFval_old;
      std::memcpy(&TrialState->xstarsqp[0], &TrialState->xstarsqp_old[0], 46U *
                  sizeof(real_T));
      u1 = TrialState->cIneq.size;
      if (TrialState->cIneq.size - 1 >= 0) {
        std::memcpy(&y_data[0], &TrialState->cIneq.data[0], static_cast<uint32_T>
                    (TrialState->cIneq.size) * sizeof(real_T));
      }

      if (static_cast<uint16_T>(TrialState->mIneq) - 1 >= 0) {
        std::memcpy(&y_data[0], &TrialState->cIneq_old.data[0],
                    static_cast<uint16_T>(TrialState->mIneq) * sizeof(real_T));
      }

      if (TrialState->cIneq.size - 1 >= 0) {
        std::memcpy(&TrialState->cIneq.data[0], &y_data[0], static_cast<uint32_T>
                    (TrialState->cIneq.size) * sizeof(real_T));
      }

      std::memcpy(&TrialState->cEq[0], &TrialState->cEq_old[0], 40U * sizeof
                  (real_T));
    }

    test_exit(&Flags, memspace, MeritFunction, fscales_lineq_constraint_size,
              fscales_cineq_constraint_size, WorkingSet, TrialState, QRManager,
              lb);
    if ((!Flags.done) && Flags.stepAccepted) {
      int32_T b_iy;
      int32_T c_ix;
      int32_T ix;
      int32_T iy;
      Flags.stepAccepted = false;
      Flags.stepType = 1;
      Flags.failedLineSearch = false;
      b_nVar = (mFixed + TrialState->iNonIneq0) + 39;
      u1 = WorkingSet->ldA;
      std::memcpy(&TrialState->delta_gradLag.data[0], &TrialState->grad.data[0],
                  static_cast<uint8_T>(nVar_tmp_tmp) * sizeof(real_T));
      if (nVar_tmp_tmp >= 1) {
        for (int32_T mLambda{0}; mLambda < nVar_tmp_tmp; mLambda++) {
          TrialState->delta_gradLag.data[mLambda] -= TrialState->
            grad_old.data[mLambda];
        }
      }

      ix = mFixed;
      iy = WorkingSet->ldA * 39 + 1;
      for (int32_T mLambda{1}; u1 < 0 ? mLambda >= iy : mLambda <= iy; mLambda +=
           u1) {
        b_iy = mLambda + nVar_tmp_tmp;
        for (idx_max = mLambda; idx_max < b_iy; idx_max++) {
          idx_max_tmp = idx_max - mLambda;
          TrialState->delta_gradLag.data[idx_max_tmp] += WorkingSet->
            Aeq.data[idx_max - 1] * TrialState->lambdasqp.data[ix];
        }

        ix++;
      }

      c_ix = mFixed;
      for (int32_T mLambda{1}; u1 < 0 ? mLambda >= iy : mLambda <= iy; mLambda +=
           u1) {
        b_iy = mLambda + nVar_tmp_tmp;
        for (idx_max = mLambda; idx_max < b_iy; idx_max++) {
          idx_max_tmp = idx_max - mLambda;
          TrialState->delta_gradLag.data[idx_max_tmp] +=
            TrialState->JacCeqTrans_old.data[idx_max - 1] *
            -TrialState->lambdasqp.data[c_ix];
        }

        c_ix++;
      }

      if (TrialState->mNonlinIneq > 0) {
        ix = (TrialState->iNonIneq0 - 1) * WorkingSet->ldA + 1;
        c_ix = b_nVar;
        iy = (TrialState->mNonlinIneq - 1) * WorkingSet->ldA + ix;
        for (int32_T mLambda{ix}; u1 < 0 ? mLambda >= iy : mLambda <= iy;
             mLambda += u1) {
          b_iy = mLambda + nVar_tmp_tmp;
          for (idx_max = mLambda; idx_max < b_iy; idx_max++) {
            idx_max_tmp = idx_max - mLambda;
            TrialState->delta_gradLag.data[idx_max_tmp] +=
              WorkingSet->Aineq.data[idx_max - 1] * TrialState->
              lambdasqp.data[c_ix];
          }

          c_ix++;
        }

        idx_max = b_nVar;
        c_ix = (TrialState->mNonlinIneq - 1) * WorkingSet->ldA + 1;
        for (b_nVar = 1; u1 < 0 ? b_nVar >= c_ix : b_nVar <= c_ix; b_nVar += u1)
        {
          b_iy = b_nVar + nVar_tmp_tmp;
          for (int32_T mLambda{b_nVar}; mLambda < b_iy; mLambda++) {
            idx_max_tmp = mLambda - b_nVar;
            TrialState->delta_gradLag.data[idx_max_tmp] +=
              TrialState->JacCineqTrans_old.data[mLambda - 1] *
              -TrialState->lambdasqp.data[idx_max];
          }

          idx_max++;
        }
      }

      saveJacobian(TrialState, nVar_tmp_tmp, mIneq, WorkingSet->Aineq.data,
                   TrialState->iNonIneq0, WorkingSet->Aeq.data, WorkingSet->ldA);
      BFGSUpdate(nVar_tmp_tmp, Hessian, TrialState->delta_x.data,
                 TrialState->delta_gradLag.data, memspace->workspace_double.data);
      TrialState->sqpIterations++;
    }
  }
}

// Function for MATLAB Function: '<S2>/NLMPC'
void MPC_controller::fmincon(const s_GSKgPzH92oA7AAcXEvWMnG
  *fun_workspace_runtimedata, const sXyXDxkiKhsfpX9ivkpx9WG
  *fun_workspace_userdata, const real_T x0[46], const real_T Aineq_data[], const
  real_T bineq_data[], const int32_T *bineq_size, const real_T lb[46], const
  s_GSKgPzH92oA7AAcXEvWMnG *nonlcon_workspace_runtimedata, const
  sXyXDxkiKhsfpX9ivkpx9WG *nonlcon_workspace_userdata, real_T x[46], real_T
  *fval, real_T *exitflag, real_T *output_iterations, real_T *output_funcCount,
  char_T output_algorithm[3], real_T *output_constrviolation, real_T
  *output_stepsize, real_T *output_lssteplength, real_T *output_firstorderopt)
{
  sG8JZ69axY52WWR6RKyApQC MeritFunction;
  s_4B8jbk60U8ZWFI1LxShFzC QPObjective;
  real_T y_data[453];
  real_T Cineq_data[80];
  real_T Ceq[40];
  real_T b_c;
  real_T scale;
  int32_T Cineq_size[2];
  int32_T JacCineqTrans_size[2];
  int32_T WorkingSet_tmp_tmp;
  int32_T i;
  int32_T k;
  int32_T mConstrMax;
  int32_T mIneq;
  int32_T mNonlinIneq;
  int32_T maxDims;
  int8_T WorkingSet_tmp[5];
  eML_blk_kernel_anonFcn2(nonlcon_workspace_runtimedata->x,
    nonlcon_workspace_runtimedata->OutputMin,
    nonlcon_workspace_runtimedata->OutputMax, x0, Cineq_data, Cineq_size, Ceq,
    rtDW.JacCineqTrans_data, JacCineqTrans_size, rtDW.JacCeqTrans);
  mNonlinIneq = Cineq_size[0] * Cineq_size[1];
  mIneq = *bineq_size + mNonlinIneq;
  mConstrMax = (mIneq + mIneq) + 213;
  if (mIneq + 127 >= mConstrMax) {
    maxDims = mIneq + 127;
  } else {
    maxDims = mConstrMax;
  }

  factoryConstruct(mIneq + 127, mConstrMax, mIneq, mNonlinIneq, &rtDW.TrialState);
  std::memcpy(&rtDW.TrialState.xstarsqp[0], &x0[0], 46U * sizeof(real_T));
  rtDW.FcnEvaluator.next.next.next.next.next.value = mNonlinIneq;
  rtDW.FcnEvaluator.next.next.next.next.next.next.next.value.workspace.runtimedata.x
    [0] = nonlcon_workspace_runtimedata->x[0];
  rtDW.FcnEvaluator.next.next.next.next.next.next.next.value.workspace.runtimedata.x
    [1] = nonlcon_workspace_runtimedata->x[1];
  rtDW.FcnEvaluator.next.next.next.next.next.next.next.value.workspace.runtimedata.x
    [2] = nonlcon_workspace_runtimedata->x[2];
  rtDW.FcnEvaluator.next.next.next.next.next.next.next.value.workspace.runtimedata.x
    [3] = nonlcon_workspace_runtimedata->x[3];
  rtDW.FcnEvaluator.next.next.next.next.next.next.next.value.workspace.runtimedata.lastMV
    = nonlcon_workspace_runtimedata->lastMV;
  std::memcpy
    (&rtDW.FcnEvaluator.next.next.next.next.next.next.next.value.workspace.runtimedata.ref
     [0], &nonlcon_workspace_runtimedata->ref[0], 40U * sizeof(real_T));
  std::memcpy
    (&rtDW.FcnEvaluator.next.next.next.next.next.next.next.value.workspace.runtimedata.OutputWeights
     [0], &nonlcon_workspace_runtimedata->OutputWeights[0], 40U * sizeof(real_T));
  std::memcpy
    (&rtDW.FcnEvaluator.next.next.next.next.next.next.next.value.workspace.runtimedata.MVWeights
     [0], &nonlcon_workspace_runtimedata->MVWeights[0], 10U * sizeof(real_T));
  std::memcpy
    (&rtDW.FcnEvaluator.next.next.next.next.next.next.next.value.workspace.runtimedata.MVRateWeights
     [0], &nonlcon_workspace_runtimedata->MVRateWeights[0], 10U * sizeof(real_T));
  rtDW.FcnEvaluator.next.next.next.next.next.next.next.value.workspace.runtimedata.ECRWeight
    = nonlcon_workspace_runtimedata->ECRWeight;
  std::memcpy
    (&rtDW.FcnEvaluator.next.next.next.next.next.next.next.value.workspace.runtimedata.OutputMin
     [0], &nonlcon_workspace_runtimedata->OutputMin[0], 40U * sizeof(real_T));
  std::memcpy
    (&rtDW.FcnEvaluator.next.next.next.next.next.next.next.value.workspace.runtimedata.OutputMax
     [0], &nonlcon_workspace_runtimedata->OutputMax[0], 40U * sizeof(real_T));
  std::memcpy
    (&rtDW.FcnEvaluator.next.next.next.next.next.next.next.value.workspace.runtimedata.StateMin
     [0], &nonlcon_workspace_runtimedata->StateMin[0], 40U * sizeof(real_T));
  std::memcpy
    (&rtDW.FcnEvaluator.next.next.next.next.next.next.next.value.workspace.runtimedata.StateMax
     [0], &nonlcon_workspace_runtimedata->StateMax[0], 40U * sizeof(real_T));
  std::memcpy
    (&rtDW.FcnEvaluator.next.next.next.next.next.next.next.value.workspace.runtimedata.MVMin
     [0], &nonlcon_workspace_runtimedata->MVMin[0], 10U * sizeof(real_T));
  std::memcpy
    (&rtDW.FcnEvaluator.next.next.next.next.next.next.next.value.workspace.runtimedata.MVMax
     [0], &nonlcon_workspace_runtimedata->MVMax[0], 10U * sizeof(real_T));
  std::memcpy
    (&rtDW.FcnEvaluator.next.next.next.next.next.next.next.value.workspace.runtimedata.MVRateMin
     [0], &nonlcon_workspace_runtimedata->MVRateMin[0], 10U * sizeof(real_T));
  std::memcpy
    (&rtDW.FcnEvaluator.next.next.next.next.next.next.next.value.workspace.runtimedata.MVRateMax
     [0], &nonlcon_workspace_runtimedata->MVRateMax[0], 10U * sizeof(real_T));
  std::memcpy
    (&rtDW.FcnEvaluator.next.next.next.next.next.next.next.value.workspace.runtimedata.MVScaledTarget
     [0], &nonlcon_workspace_runtimedata->MVScaledTarget[0], 10U * sizeof(real_T));
  rtDW.FcnEvaluator.next.next.next.next.next.next.next.value.workspace.userdata =
    *nonlcon_workspace_userdata;
  rtDW.FcnEvaluator.next.next.next.next.next.next.next.next.value.workspace.runtimedata.x
    [0] = fun_workspace_runtimedata->x[0];
  rtDW.FcnEvaluator.next.next.next.next.next.next.next.next.value.workspace.runtimedata.x
    [1] = fun_workspace_runtimedata->x[1];
  rtDW.FcnEvaluator.next.next.next.next.next.next.next.next.value.workspace.runtimedata.x
    [2] = fun_workspace_runtimedata->x[2];
  rtDW.FcnEvaluator.next.next.next.next.next.next.next.next.value.workspace.runtimedata.x
    [3] = fun_workspace_runtimedata->x[3];
  rtDW.FcnEvaluator.next.next.next.next.next.next.next.next.value.workspace.runtimedata.lastMV
    = fun_workspace_runtimedata->lastMV;
  std::memcpy
    (&rtDW.FcnEvaluator.next.next.next.next.next.next.next.next.value.workspace.runtimedata.ref
     [0], &fun_workspace_runtimedata->ref[0], 40U * sizeof(real_T));
  std::memcpy
    (&rtDW.FcnEvaluator.next.next.next.next.next.next.next.next.value.workspace.runtimedata.OutputWeights
     [0], &fun_workspace_runtimedata->OutputWeights[0], 40U * sizeof(real_T));
  std::memcpy
    (&rtDW.FcnEvaluator.next.next.next.next.next.next.next.next.value.workspace.runtimedata.MVWeights
     [0], &fun_workspace_runtimedata->MVWeights[0], 10U * sizeof(real_T));
  std::memcpy
    (&rtDW.FcnEvaluator.next.next.next.next.next.next.next.next.value.workspace.runtimedata.MVRateWeights
     [0], &fun_workspace_runtimedata->MVRateWeights[0], 10U * sizeof(real_T));
  rtDW.FcnEvaluator.next.next.next.next.next.next.next.next.value.workspace.runtimedata.ECRWeight
    = fun_workspace_runtimedata->ECRWeight;
  std::memcpy
    (&rtDW.FcnEvaluator.next.next.next.next.next.next.next.next.value.workspace.runtimedata.OutputMin
     [0], &fun_workspace_runtimedata->OutputMin[0], 40U * sizeof(real_T));
  std::memcpy
    (&rtDW.FcnEvaluator.next.next.next.next.next.next.next.next.value.workspace.runtimedata.OutputMax
     [0], &fun_workspace_runtimedata->OutputMax[0], 40U * sizeof(real_T));
  std::memcpy
    (&rtDW.FcnEvaluator.next.next.next.next.next.next.next.next.value.workspace.runtimedata.StateMin
     [0], &fun_workspace_runtimedata->StateMin[0], 40U * sizeof(real_T));
  std::memcpy
    (&rtDW.FcnEvaluator.next.next.next.next.next.next.next.next.value.workspace.runtimedata.StateMax
     [0], &fun_workspace_runtimedata->StateMax[0], 40U * sizeof(real_T));
  std::memcpy
    (&rtDW.FcnEvaluator.next.next.next.next.next.next.next.next.value.workspace.runtimedata.MVMin
     [0], &fun_workspace_runtimedata->MVMin[0], 10U * sizeof(real_T));
  std::memcpy
    (&rtDW.FcnEvaluator.next.next.next.next.next.next.next.next.value.workspace.runtimedata.MVMax
     [0], &fun_workspace_runtimedata->MVMax[0], 10U * sizeof(real_T));
  std::memcpy
    (&rtDW.FcnEvaluator.next.next.next.next.next.next.next.next.value.workspace.runtimedata.MVRateMin
     [0], &fun_workspace_runtimedata->MVRateMin[0], 10U * sizeof(real_T));
  std::memcpy
    (&rtDW.FcnEvaluator.next.next.next.next.next.next.next.next.value.workspace.runtimedata.MVRateMax
     [0], &fun_workspace_runtimedata->MVRateMax[0], 10U * sizeof(real_T));
  std::memcpy
    (&rtDW.FcnEvaluator.next.next.next.next.next.next.next.next.value.workspace.runtimedata.MVScaledTarget
     [0], &fun_workspace_runtimedata->MVScaledTarget[0], 10U * sizeof(real_T));
  rtDW.FcnEvaluator.next.next.next.next.next.next.next.next.value.workspace.userdata
    = *fun_workspace_userdata;
  factoryConstruct_h53b(mIneq + 127, &QPObjective.grad.size,
                        &QPObjective.Hx.size, &QPObjective.hasLinear,
                        &QPObjective.nvar, &QPObjective.maxVar,
                        &QPObjective.beta, &QPObjective.rho,
                        &QPObjective.objtype, &QPObjective.prev_objtype,
                        &QPObjective.prev_nvar, &QPObjective.prev_hasLinear,
                        &QPObjective.gammaScalar);
  QPObjective.nvar = 46;
  QPObjective.hasLinear = true;
  QPObjective.objtype = 3;
  rtDW.memspace.workspace_double.size[0] = maxDims;
  rtDW.memspace.workspace_double.size[1] = mIneq + 127;
  rtDW.memspace.workspace_int.size = maxDims;
  rtDW.memspace.workspace_sort.size = maxDims;
  factoryConstruct_h53bm(mIneq, mIneq + 127, mConstrMax, &rtDW.WorkingSet);
  k = -1;
  for (i = 0; i < 46; i++) {
    b_c = lb[i];
    if ((!std::isinf(b_c)) && (!std::isnan(b_c))) {
      k++;
      rtDW.WorkingSet.indexLB.data[k] = i + 1;
    }
  }

  rtDW.WorkingSet.mConstrMax = mConstrMax;
  WorkingSet_tmp_tmp = mIneq + k;
  rtDW.WorkingSet.mConstr = WorkingSet_tmp_tmp + 41;
  rtDW.WorkingSet.mConstrOrig = WorkingSet_tmp_tmp + 41;
  WorkingSet_tmp[0] = 0;
  WorkingSet_tmp[1] = 40;
  WorkingSet_tmp[2] = static_cast<int8_T>(mIneq);
  WorkingSet_tmp[3] = static_cast<int8_T>(k + 1);
  WorkingSet_tmp[4] = 0;
  for (i = 0; i < 5; i++) {
    int8_T WorkingSet_tmp_0;
    WorkingSet_tmp_0 = WorkingSet_tmp[i];
    rtDW.WorkingSet.sizes[i] = WorkingSet_tmp_0;
    rtDW.WorkingSet.sizesNormal[i] = WorkingSet_tmp_0;
  }

  rtDW.WorkingSet.sizesPhaseOne[0] = 0;
  rtDW.WorkingSet.sizesPhaseOne[1] = 40;
  rtDW.WorkingSet.sizesPhaseOne[2] = mIneq;
  rtDW.WorkingSet.sizesPhaseOne[3] = k + 2;
  rtDW.WorkingSet.sizesPhaseOne[4] = 0;
  rtDW.WorkingSet.sizesRegularized[0] = 0;
  rtDW.WorkingSet.sizesRegularized[1] = 40;
  rtDW.WorkingSet.sizesRegularized[2] = mIneq;
  rtDW.WorkingSet.sizesRegularized[3] = WorkingSet_tmp_tmp + 81;
  rtDW.WorkingSet.sizesRegularized[4] = 0;
  rtDW.WorkingSet.sizesRegPhaseOne[0] = 0;
  rtDW.WorkingSet.sizesRegPhaseOne[1] = 40;
  rtDW.WorkingSet.sizesRegPhaseOne[2] = mIneq;
  rtDW.WorkingSet.sizesRegPhaseOne[3] = WorkingSet_tmp_tmp + 82;
  rtDW.WorkingSet.sizesRegPhaseOne[4] = 0;
  rtDW.WorkingSet.isActiveIdxNormal[0] = 1;
  rtDW.WorkingSet.isActiveIdxNormal[1] = 0;
  rtDW.WorkingSet.isActiveIdxNormal[2] = 40;
  rtDW.WorkingSet.isActiveIdxNormal[3] = mIneq;
  rtDW.WorkingSet.isActiveIdxNormal[4] = k + 1;
  rtDW.WorkingSet.isActiveIdxNormal[5] = 0;
  for (i = 0; i < 6; i++) {
    rtDW.WorkingSet.isActiveIdxRegPhaseOne[i] =
      rtDW.WorkingSet.isActiveIdxNormal[i];
  }

  for (mConstrMax = 0; mConstrMax < 5; mConstrMax++) {
    rtDW.WorkingSet.isActiveIdxRegPhaseOne[mConstrMax + 1] +=
      rtDW.WorkingSet.isActiveIdxRegPhaseOne[mConstrMax];
  }

  for (i = 0; i < 6; i++) {
    rtDW.WorkingSet.isActiveIdx[i] = rtDW.WorkingSet.isActiveIdxRegPhaseOne[i];
  }

  rtDW.WorkingSet.isActiveIdxRegPhaseOne[0] = 1;
  rtDW.WorkingSet.isActiveIdxRegPhaseOne[1] = 0;
  rtDW.WorkingSet.isActiveIdxRegPhaseOne[2] = 40;
  rtDW.WorkingSet.isActiveIdxRegPhaseOne[3] = mIneq;
  rtDW.WorkingSet.isActiveIdxRegPhaseOne[4] = k + 2;
  rtDW.WorkingSet.isActiveIdxRegPhaseOne[5] = 0;
  for (mConstrMax = 0; mConstrMax < 5; mConstrMax++) {
    rtDW.WorkingSet.isActiveIdxNormal[mConstrMax + 1] +=
      rtDW.WorkingSet.isActiveIdxNormal[mConstrMax];
    rtDW.WorkingSet.isActiveIdxRegPhaseOne[mConstrMax + 1] +=
      rtDW.WorkingSet.isActiveIdxRegPhaseOne[mConstrMax];
  }

  for (i = 0; i < 6; i++) {
    rtDW.WorkingSet.isActiveIdxPhaseOne[i] =
      rtDW.WorkingSet.isActiveIdxRegPhaseOne[i];
  }

  rtDW.WorkingSet.isActiveIdxRegPhaseOne[0] = 1;
  rtDW.WorkingSet.isActiveIdxRegPhaseOne[1] = 0;
  rtDW.WorkingSet.isActiveIdxRegPhaseOne[2] = 40;
  rtDW.WorkingSet.isActiveIdxRegPhaseOne[3] = mIneq;
  rtDW.WorkingSet.isActiveIdxRegPhaseOne[4] = WorkingSet_tmp_tmp + 81;
  rtDW.WorkingSet.isActiveIdxRegPhaseOne[5] = 0;
  for (mConstrMax = 0; mConstrMax < 5; mConstrMax++) {
    rtDW.WorkingSet.isActiveIdxRegPhaseOne[mConstrMax + 1] +=
      rtDW.WorkingSet.isActiveIdxRegPhaseOne[mConstrMax];
  }

  for (i = 0; i < 6; i++) {
    rtDW.WorkingSet.isActiveIdxRegularized[i] =
      rtDW.WorkingSet.isActiveIdxRegPhaseOne[i];
  }

  rtDW.WorkingSet.isActiveIdxRegPhaseOne[0] = 1;
  rtDW.WorkingSet.isActiveIdxRegPhaseOne[1] = 0;
  rtDW.WorkingSet.isActiveIdxRegPhaseOne[2] = 40;
  rtDW.WorkingSet.isActiveIdxRegPhaseOne[3] = mIneq;
  rtDW.WorkingSet.isActiveIdxRegPhaseOne[4] = WorkingSet_tmp_tmp + 82;
  rtDW.WorkingSet.isActiveIdxRegPhaseOne[5] = 0;
  for (mConstrMax = 0; mConstrMax < 5; mConstrMax++) {
    rtDW.WorkingSet.isActiveIdxRegPhaseOne[mConstrMax + 1] +=
      rtDW.WorkingSet.isActiveIdxRegPhaseOne[mConstrMax];
  }

  if (mIneq > 0) {
    mConstrMax = *bineq_size;
    for (i = 0; i < mConstrMax; i++) {
      for (WorkingSet_tmp_tmp = 0; WorkingSet_tmp_tmp < 46; WorkingSet_tmp_tmp++)
      {
        rtDW.WorkingSet.Aineq.data[WorkingSet_tmp_tmp + rtDW.WorkingSet.ldA * i]
          = Aineq_data[*bineq_size * WorkingSet_tmp_tmp + i];
      }
    }
  }

  for (i = 0; i <= k; i++) {
    rtDW.TrialState.xstarsqp[rtDW.WorkingSet.indexLB.data[i] - 1] = std::fmax
      (rtDW.TrialState.xstarsqp[rtDW.WorkingSet.indexLB.data[i] - 1],
       lb[rtDW.WorkingSet.indexLB.data[i] - 1]);
  }

  evalObjAndConstrAndDerivatives(mNonlinIneq,
    &rtDW.FcnEvaluator.next.next.next.next.next.next.next.value.workspace.runtimedata,
    &rtDW.FcnEvaluator.next.next.next.next.next.next.next.next.value.workspace,
    rtDW.TrialState.xstarsqp, rtDW.TrialState.grad.data,
    rtDW.TrialState.cIneq.data, rtDW.TrialState.iNonIneq0, rtDW.TrialState.cEq,
    rtDW.WorkingSet.Aineq.data, rtDW.TrialState.iNonIneq0, rtDW.WorkingSet.ldA,
    rtDW.WorkingSet.Aeq.data, rtDW.WorkingSet.ldA, &rtDW.TrialState.sqpFval,
    &mConstrMax);
  rtDW.TrialState.FunctionEvaluations = 1;
  mConstrMax = rtDW.WorkingSet.ldA;
  if (*bineq_size > 0) {
    int32_T y_size_idx_0;
    y_size_idx_0 = rtDW.TrialState.cIneq.size;
    WorkingSet_tmp_tmp = rtDW.TrialState.cIneq.size;
    if (WorkingSet_tmp_tmp - 1 >= 0) {
      std::memcpy(&y_data[0], &rtDW.TrialState.cIneq.data[0],
                  static_cast<uint32_T>(WorkingSet_tmp_tmp) * sizeof(real_T));
    }

    std::memcpy(&y_data[0], &bineq_data[0], static_cast<uint32_T>(*bineq_size) *
                sizeof(real_T));
    if (y_size_idx_0 - 1 >= 0) {
      std::memcpy(&rtDW.TrialState.cIneq.data[0], &y_data[0],
                  static_cast<uint32_T>(y_size_idx_0) * sizeof(real_T));
    }

    i = *bineq_size;
    for (WorkingSet_tmp_tmp = 0; WorkingSet_tmp_tmp < i; WorkingSet_tmp_tmp++) {
      rtDW.TrialState.cIneq.data[WorkingSet_tmp_tmp] =
        -rtDW.TrialState.cIneq.data[WorkingSet_tmp_tmp];
    }

    i = 0;
    WorkingSet_tmp_tmp = (*bineq_size - 1) * rtDW.WorkingSet.ldA + 1;
    for (y_size_idx_0 = 1; mConstrMax < 0 ? y_size_idx_0 >= WorkingSet_tmp_tmp :
         y_size_idx_0 <= WorkingSet_tmp_tmp; y_size_idx_0 += mConstrMax) {
      b_c = 0.0;
      for (int32_T ia{y_size_idx_0}; ia <= y_size_idx_0 + 45; ia++) {
        b_c += rtDW.WorkingSet.Aineq.data[ia - 1] * rtDW.TrialState.xstarsqp[ia
          - y_size_idx_0];
      }

      rtDW.TrialState.cIneq.data[i] += b_c;
      i++;
    }
  }

  for (mConstrMax = 0; mConstrMax < 40; mConstrMax++) {
    rtDW.WorkingSet.beq[mConstrMax] = -rtDW.TrialState.cEq[mConstrMax];
    rtDW.WorkingSet.bwset.data[mConstrMax] = rtDW.WorkingSet.beq[mConstrMax];
  }

  mConstrMax = 0;
  i = 0;
  for (WorkingSet_tmp_tmp = 0; WorkingSet_tmp_tmp < 40; WorkingSet_tmp_tmp++) {
    std::memcpy(&rtDW.WorkingSet.ATwset.data[mConstrMax],
                &rtDW.WorkingSet.Aeq.data[i], 46U * sizeof(real_T));
    mConstrMax += rtDW.WorkingSet.ldA;
    i += rtDW.WorkingSet.ldA;
  }

  for (i = 0; i < mIneq; i++) {
    rtDW.WorkingSet.bineq.data[i] = -rtDW.TrialState.cIneq.data[i];
  }

  for (mConstrMax = 0; mConstrMax <= k; mConstrMax++) {
    rtDW.WorkingSet.lb.data[rtDW.WorkingSet.indexLB.data[mConstrMax] - 1] =
      -lb[rtDW.WorkingSet.indexLB.data[mConstrMax] - 1] +
      x0[rtDW.WorkingSet.indexLB.data[mConstrMax] - 1];
  }

  initActiveSet(&rtDW.WorkingSet);
  MeritFunction.initFval = rtDW.TrialState.sqpFval;
  MeritFunction.penaltyParam = 1.0;
  MeritFunction.threshold = 0.0001;
  MeritFunction.nPenaltyDecreases = 0;
  MeritFunction.linearizedConstrViol = 0.0;
  b_c = 0.0;
  for (k = 0; k < 40; k++) {
    b_c += std::abs(rtDW.TrialState.cEq[k]);
  }

  MeritFunction.initConstrViolationEq = b_c;
  b_c = 0.0;
  for (k = 0; k < mIneq; k++) {
    if (rtDW.TrialState.cIneq.data[k] > 0.0) {
      b_c += rtDW.TrialState.cIneq.data[k];
    }
  }

  MeritFunction.initConstrViolationIneq = b_c;
  MeritFunction.phi = 0.0;
  MeritFunction.phiPrimePlus = 0.0;
  MeritFunction.phiFullStep = 0.0;
  MeritFunction.feasRelativeFactor = 0.0;
  MeritFunction.nlpPrimalFeasError = 0.0;
  MeritFunction.nlpDualFeasError = 0.0;
  MeritFunction.nlpComplError = 0.0;
  MeritFunction.firstOrderOpt = 0.0;
  MeritFunction.hasObjective = true;
  factoryConstruct_h5(maxDims, maxDims, &rtDW.QRManager.ldq,
                      rtDW.QRManager.QR.size, rtDW.QRManager.Q.data,
                      rtDW.QRManager.Q.size, rtDW.QRManager.jpvt.data,
                      &rtDW.QRManager.jpvt.size, &rtDW.QRManager.mrows,
                      &rtDW.QRManager.ncols, &rtDW.QRManager.tau.size,
                      &rtDW.QRManager.minRowCol, &rtDW.QRManager.usedPivoting);
  factoryConstruct_h53(maxDims, rtDW.CholManager.FMat.size,
                       &rtDW.CholManager.ldm, &rtDW.CholManager.ndims,
                       &rtDW.CholManager.info, &rtDW.CholManager.scaleFactor,
                       &rtDW.CholManager.ConvexCheck, &rtDW.CholManager.regTol_,
                       &rtDW.CholManager.workspace_,
                       &rtDW.CholManager.workspace2_);
  driver(bineq_data, lb, &rtDW.TrialState, &MeritFunction, &rtDW.FcnEvaluator,
         &rtDW.memspace, &rtDW.WorkingSet, &rtDW.QRManager, &rtDW.CholManager,
         &QPObjective, bineq_size, &mNonlinIneq, rtDW.unusedExpr);
  *fval = rtDW.TrialState.sqpFval;
  *exitflag = rtDW.TrialState.sqpExitFlag;
  *output_iterations = rtDW.TrialState.sqpIterations;
  *output_funcCount = rtDW.TrialState.FunctionEvaluations;
  output_algorithm[0] = 's';
  output_algorithm[1] = 'q';
  output_algorithm[2] = 'p';
  *output_constrviolation = MeritFunction.nlpPrimalFeasError;
  b_c = 0.0;
  scale = 3.3121686421112381E-170;
  for (mNonlinIneq = 0; mNonlinIneq < 46; mNonlinIneq++) {
    real_T absxk;
    x[mNonlinIneq] = rtDW.TrialState.xstarsqp[mNonlinIneq];
    absxk = std::abs(rtDW.TrialState.delta_x.data[mNonlinIneq]);
    if (absxk > scale) {
      real_T t;
      t = scale / absxk;
      b_c = b_c * t * t + 1.0;
      scale = absxk;
    } else {
      real_T t;
      t = absxk / scale;
      b_c += t * t;
    }
  }

  *output_stepsize = scale * std::sqrt(b_c);
  *output_lssteplength = rtDW.TrialState.steplength;
  *output_firstorderopt = MeritFunction.firstOrderOpt;
}

// Model step function
void MPC_controller::step()
{
  static real_T h[40]{ -0.43, -0.43, -0.43, -0.43, -0.43, -0.43, -0.43, -0.43,
    -0.43, -0.43, -2.0, -2.0, -2.0, -2.0, -2.0, -2.0, -2.0, -2.0, -2.0, -2.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0 };

  static real_T j[40]{ 0.43, 0.43, 0.43, 0.43, 0.43, 0.43, 0.43, 0.43, 0.43,
    0.43, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0 };

  static const int8_T a_0[50]{ 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,
    0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0 };

  static const int8_T g[40]{ 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

  sXyXDxkiKhsfpX9ivkpx9WG expl_temp_5;
  sXyXDxkiKhsfpX9ivkpx9WG expl_temp_6;
  s_GSKgPzH92oA7AAcXEvWMnG ConFcn_workspace_runtimedata;
  s_GSKgPzH92oA7AAcXEvWMnG CostFcn_workspace_runtimedata;
  real_T Au[400];
  real_T Auf_data[400];
  real_T rtb_Selector_0[46];
  real_T tmp_0[46];
  real_T z[46];
  real_T X_4[44];
  real_T B_data[40];
  real_T ref[40];
  real_T rtb_Selector[36];
  real_T U[11];
  real_T tmp[10];
  real_T a[5];
  real_T ExitFlag;
  real_T Out_constrviolation;
  real_T expl_temp;
  real_T expl_temp_0;
  real_T expl_temp_2;
  real_T expl_temp_3;
  real_T expl_temp_4;
  real_T ref_0;
  real_T rtb_UnitDelay;
  int32_T ic_0[2];
  int32_T tmp_size[2];
  int32_T Au_tmp;
  int32_T B_size;
  int32_T i;
  int32_T ic;
  char_T expl_temp_1[3];
  int8_T ii_data[40];
  boolean_T x[40];
  boolean_T exitg1;

  // MATLAB Function: '<S2>/NLMPC'
  j[20U] = (rtInf);
  j[21U] = (rtInf);
  j[22U] = (rtInf);
  j[23U] = (rtInf);
  j[24U] = (rtInf);
  j[25U] = (rtInf);
  j[26U] = (rtInf);
  j[27U] = (rtInf);
  j[28U] = (rtInf);
  j[29U] = (rtInf);
  j[30U] = (rtInf);
  j[31U] = (rtInf);
  j[32U] = (rtInf);
  j[33U] = (rtInf);
  j[34U] = (rtInf);
  j[35U] = (rtInf);
  j[36U] = (rtInf);
  j[37U] = (rtInf);
  j[38U] = (rtInf);
  j[39U] = (rtInf);
  h[20U] = (rtMinusInf);
  h[21U] = (rtMinusInf);
  h[22U] = (rtMinusInf);
  h[23U] = (rtMinusInf);
  h[24U] = (rtMinusInf);
  h[25U] = (rtMinusInf);
  h[26U] = (rtMinusInf);
  h[27U] = (rtMinusInf);
  h[28U] = (rtMinusInf);
  h[29U] = (rtMinusInf);
  h[30U] = (rtMinusInf);
  h[31U] = (rtMinusInf);
  h[32U] = (rtMinusInf);
  h[33U] = (rtMinusInf);
  h[34U] = (rtMinusInf);
  h[35U] = (rtMinusInf);
  h[36U] = (rtMinusInf);
  h[37U] = (rtMinusInf);
  h[38U] = (rtMinusInf);
  h[39U] = (rtMinusInf);

  // Delay: '<S3>/x_Delay' incorporates:
  //   Constant: '<S3>/ones'
  //   Inport: '<Root>/x'
  //   Product: '<S3>/Product1'

  if (rtDW.icLoad) {
    for (i = 0; i < 4; i++) {
      for (ic = 0; ic < 11; ic++) {
        rtDW.x_Delay_DSTATE[ic + 11 * i] = rtU.x[i];
      }
    }
  }

  // UnitDelay: '<Root>/Unit Delay'
  rtb_UnitDelay = rtDW.UnitDelay_DSTATE;

  // Delay: '<S3>/mv_Delay' incorporates:
  //   Product: '<S3>/Product'

  if (rtDW.icLoad_e) {
    for (i = 0; i < 11; i++) {
      rtDW.mv_Delay_DSTATE[i] = rtb_UnitDelay;
    }
  }

  // Selector: '<S3>/Selector' incorporates:
  //   Constant: '<S3>/Constant'
  //   Delay: '<S3>/x_Delay'

  for (i = 0; i < 4; i++) {
    for (ic = 0; ic < 9; ic++) {
      rtb_Selector[ic + 9 * i] = rtDW.x_Delay_DSTATE[(11 * i + static_cast<
        int32_T>(rtConstP.Constant_Value[ic])) - 1];
    }
  }

  // End of Selector: '<S3>/Selector'

  // Delay: '<S3>/slack_delay' incorporates:
  //   Constant: '<S1>/e.init_zero'

  if (rtDW.icLoad_m) {
    rtDW.slack_delay_DSTATE = 0.0;
  }

  // MATLAB Function: '<S2>/NLMPC' incorporates:
  //   Constant: '<S3>/Constant1'
  //   Delay: '<S3>/mv_Delay'
  //   Delay: '<S3>/slack_delay'
  //   Inport: '<Root>/ref'
  //   Inport: '<Root>/x'
  //   Selector: '<S3>/Selector'
  //   Selector: '<S3>/Selector1'

  for (i = 0; i < 4; i++) {
    ref[10 * i] = rtU.ref[i];
    for (ic = 0; ic < 9; ic++) {
      ref[(ic + 10 * i) + 1] = rtU.ref[i];
    }
  }

  for (i = 0; i < 40; i++) {
    ref_0 = ref[i];
    expl_temp_5.References[i] = ref_0;
    CostFcn_workspace_runtimedata.ref[i] = ref_0;
    CostFcn_workspace_runtimedata.OutputWeights[i] = g[i];
  }

  std::memset(&Au[0], 0, 400U * sizeof(real_T));
  std::memset(&ref[0], 0, 40U * sizeof(real_T));
  for (i = 0; i < 10; i++) {
    ic = i << 2;
    x[ic] = false;
    x[ic + 1] = false;
    x[ic + 2] = true;
    x[(i << 2) + 3] = true;
    Au[44 * i] = -1.0;
    ic = i << 2;
    Au_tmp = 40 * i + ic;
    Au[Au_tmp + 1] = 1.0;
    Au[Au_tmp + 2] = -1.0;
    Au[Au_tmp + 3] = 1.0;
    ref[ic] = (rtInf);
    ref[ic + 1] = (rtInf);
    ref[ic + 2] = 29.41995;
    ref[ic + 3] = 29.41995;
    if (i + 1 == 1) {
      ref[ic] -= rtb_UnitDelay;
      ref[ic + 1] += rtb_UnitDelay;
    } else {
      Au_tmp = (i - 1) * 40 + ic;
      Au[Au_tmp] = 1.0;
      Au[Au_tmp + 1] = -1.0;
    }
  }

  ic = 0;
  i = 0;
  exitg1 = false;
  while ((!exitg1) && (i < 40)) {
    if (x[i]) {
      ic++;
      ii_data[ic - 1] = static_cast<int8_T>(i + 1);
      if (ic >= 40) {
        exitg1 = true;
      } else {
        i++;
      }
    } else {
      i++;
    }
  }

  if (ic < 1) {
    ic = 0;
  }

  if (ic > 0) {
    B_size = ic;
    for (i = 0; i < ic; i++) {
      B_data[i] = ref[ii_data[i] - 1];
    }

    std::memset(&Auf_data[0], 0, static_cast<uint32_T>(ic * 10) * sizeof(real_T));
    for (i = 0; i < 10; i++) {
      for (Au_tmp = 0; Au_tmp < ic; Au_tmp++) {
        Auf_data[Au_tmp + ic * i] = Au[(40 * i + ii_data[Au_tmp]) - 1];
      }
    }

    ic_0[0] = ic;
    ic_0[1] = 10;
    mtimes(Auf_data, ic_0, Au, tmp_size);
    std::memset(&rtDW.A_data[0], 0, static_cast<uint32_T>(ic * 40) * sizeof
                (real_T));
    Au_tmp = ic * 5;
    for (i = 0; i < Au_tmp; i++) {
      rtDW.A_data[i + ic * 40] = Au[i];
    }

    std::memset(&rtDW.A_data[45 * ic], 0, static_cast<uint32_T>((ic + 45 * ic) -
      45 * ic) * sizeof(real_T));
  } else {
    B_size = 0;
  }

  CostFcn_workspace_runtimedata.x[0] = rtU.x[0];
  CostFcn_workspace_runtimedata.x[1] = rtU.x[1];
  CostFcn_workspace_runtimedata.x[2] = rtU.x[2];
  CostFcn_workspace_runtimedata.x[3] = rtU.x[3];
  CostFcn_workspace_runtimedata.lastMV = rtb_UnitDelay;
  for (i = 0; i < 10; i++) {
    CostFcn_workspace_runtimedata.MVWeights[i] = 0.0;
    CostFcn_workspace_runtimedata.MVRateWeights[i] = 0.1;
  }

  CostFcn_workspace_runtimedata.ECRWeight = 100000.0;
  for (i = 0; i < 40; i++) {
    CostFcn_workspace_runtimedata.OutputMin[i] = h[i];
    CostFcn_workspace_runtimedata.OutputMax[i] = j[i];
    CostFcn_workspace_runtimedata.StateMin[i] = (rtMinusInf);
    CostFcn_workspace_runtimedata.StateMax[i] = (rtInf);
  }

  for (i = 0; i < 10; i++) {
    CostFcn_workspace_runtimedata.MVMin[i] = -29.41995;
    CostFcn_workspace_runtimedata.MVMax[i] = 29.41995;
    CostFcn_workspace_runtimedata.MVRateMin[i] = (rtMinusInf);
    CostFcn_workspace_runtimedata.MVRateMax[i] = (rtInf);
    CostFcn_workspace_runtimedata.MVScaledTarget[i] = 0.0;
  }

  ConFcn_workspace_runtimedata.x[0] = rtU.x[0];
  ConFcn_workspace_runtimedata.x[1] = rtU.x[1];
  ConFcn_workspace_runtimedata.x[2] = rtU.x[2];
  ConFcn_workspace_runtimedata.x[3] = rtU.x[3];
  ConFcn_workspace_runtimedata.lastMV = rtb_UnitDelay;
  std::memcpy(&ConFcn_workspace_runtimedata.ref[0],
              &CostFcn_workspace_runtimedata.ref[0], 40U * sizeof(real_T));
  std::memcpy(&ConFcn_workspace_runtimedata.OutputWeights[0],
              &CostFcn_workspace_runtimedata.OutputWeights[0], 40U * sizeof
              (real_T));
  for (i = 0; i < 10; i++) {
    ConFcn_workspace_runtimedata.MVWeights[i] = 0.0;
    ConFcn_workspace_runtimedata.MVRateWeights[i] = 0.1;
  }

  ConFcn_workspace_runtimedata.ECRWeight = 100000.0;
  for (i = 0; i < 40; i++) {
    ConFcn_workspace_runtimedata.OutputMin[i] = h[i];
    ConFcn_workspace_runtimedata.OutputMax[i] = j[i];
    ConFcn_workspace_runtimedata.StateMin[i] = (rtMinusInf);
    ConFcn_workspace_runtimedata.StateMax[i] = (rtInf);
  }

  expl_temp_5.PassivityUsePredictedX = true;
  expl_temp_5.OutputPassivityIndex = 0.1;
  expl_temp_5.InputPassivityIndex = 0.0;
  expl_temp_5.MVIndex = 1.0;
  expl_temp_5.NumOfInputs = 1.0;
  expl_temp_5.NumOfOutputs = 4.0;
  expl_temp_5.NumOfStates = 4.0;
  expl_temp_5.PredictionHorizon = 10.0;
  expl_temp_5.LastMV = rtb_UnitDelay;
  expl_temp_5.CurrentStates[0] = rtU.x[0];
  expl_temp_5.CurrentStates[1] = rtU.x[1];
  expl_temp_5.CurrentStates[2] = rtU.x[2];
  expl_temp_5.CurrentStates[3] = rtU.x[3];
  expl_temp_5.Ts = 0.1;
  expl_temp_6.PassivityUsePredictedX = true;
  expl_temp_6.OutputPassivityIndex = 0.1;
  expl_temp_6.InputPassivityIndex = 0.0;
  expl_temp_6.MVIndex = 1.0;
  expl_temp_6.NumOfInputs = 1.0;
  expl_temp_6.NumOfOutputs = 4.0;
  expl_temp_6.NumOfStates = 4.0;
  expl_temp_6.PredictionHorizon = 10.0;
  for (i = 0; i < 10; i++) {
    ConFcn_workspace_runtimedata.MVMin[i] = -29.41995;
    ConFcn_workspace_runtimedata.MVMax[i] = 29.41995;
    ConFcn_workspace_runtimedata.MVRateMin[i] = (rtMinusInf);
    ConFcn_workspace_runtimedata.MVRateMax[i] = (rtInf);
    ConFcn_workspace_runtimedata.MVScaledTarget[i] = 0.0;
    expl_temp_5.MVTarget[i] = 0.0;
    expl_temp_6.MVTarget[i] = 0.0;
  }

  std::memcpy(&expl_temp_6.References[0], &expl_temp_5.References[0], 40U *
              sizeof(real_T));
  expl_temp_6.LastMV = rtb_UnitDelay;
  expl_temp_6.CurrentStates[0] = rtU.x[0];
  expl_temp_6.CurrentStates[1] = rtU.x[1];
  expl_temp_6.CurrentStates[2] = rtU.x[2];
  expl_temp_6.CurrentStates[3] = rtU.x[3];
  expl_temp_6.Ts = 0.1;
  for (i = 0; i < 9; i++) {
    ic = i << 2;
    ref[ic] = rtb_Selector[i];
    ref[ic + 1] = rtb_Selector[i + 9];
    ref[ic + 2] = rtb_Selector[i + 18];
    ref[ic + 3] = rtb_Selector[i + 27];
  }

  ref[36] = rtb_Selector[8];
  ref[37] = rtb_Selector[17];
  ref[38] = rtb_Selector[26];
  ref[39] = rtb_Selector[35];
  for (i = 0; i < 9; i++) {
    tmp[i] = rtDW.mv_Delay_DSTATE[static_cast<int32_T>
      (rtConstP.Constant1_Value[i]) - 1];
  }

  tmp[9] = rtDW.mv_Delay_DSTATE[9];
  for (i = 0; i < 5; i++) {
    a[i] = 0.0;
    for (ic = 0; ic < 10; ic++) {
      a[i] += static_cast<real_T>(a_0[5 * ic + i]) * tmp[ic];
    }
  }

  std::memcpy(&rtb_Selector_0[0], &ref[0], 40U * sizeof(real_T));
  for (i = 0; i < 5; i++) {
    rtb_Selector_0[i + 40] = a[i];
  }

  rtb_Selector_0[45] = rtDW.slack_delay_DSTATE;
  for (i = 0; i < 40; i++) {
    tmp_0[i] = (rtMinusInf);
  }

  for (i = 0; i < 5; i++) {
    tmp_0[i + 40] = (rtMinusInf);
  }

  tmp_0[45] = 0.0;
  fmincon(&CostFcn_workspace_runtimedata, &expl_temp_5, rtb_Selector_0,
          rtDW.A_data, B_data, &B_size, tmp_0, &ConFcn_workspace_runtimedata,
          &expl_temp_6, z, &ref_0, &ExitFlag, &expl_temp, &expl_temp_0,
          expl_temp_1, &Out_constrviolation, &expl_temp_2, &expl_temp_3,
          &expl_temp_4);
  if ((ExitFlag == 0.0) && (Out_constrviolation > 1.0E-6)) {
    ExitFlag = -2.0;
  }

  // Update for Delay: '<S3>/slack_delay' incorporates:
  //   Inport: '<Root>/x'
  //   MATLAB Function: '<S2>/NLMPC'

  znlmpc_getXUe(z, rtU.x, X_4, U, &rtDW.slack_delay_DSTATE);

  // MATLAB Function: '<S2>/NLMPC'
  if (ExitFlag > 0.0) {
    rtb_UnitDelay = U[0];
  }

  // Outport: '<Root>/u'
  rtY.u = rtb_UnitDelay;

  // Update for Delay: '<S3>/x_Delay' incorporates:
  //   MATLAB Function: '<S2>/NLMPC'

  rtDW.icLoad = false;
  std::memcpy(&rtDW.x_Delay_DSTATE[0], &X_4[0], 44U * sizeof(real_T));

  // Update for UnitDelay: '<Root>/Unit Delay'
  rtDW.UnitDelay_DSTATE = rtb_UnitDelay;

  // Update for Delay: '<S3>/mv_Delay' incorporates:
  //   MATLAB Function: '<S2>/NLMPC'

  rtDW.icLoad_e = false;
  std::memcpy(&rtDW.mv_Delay_DSTATE[0], &U[0], 11U * sizeof(real_T));

  // Update for Delay: '<S3>/slack_delay'
  rtDW.icLoad_m = false;
}

// Model initialize function
void MPC_controller::initialize()
{
  // Registration code

  // initialize non-finites
  rt_InitInfAndNaN(sizeof(real_T));

  // InitializeConditions for Delay: '<S3>/x_Delay'
  rtDW.icLoad = true;

  // InitializeConditions for Delay: '<S3>/mv_Delay'
  rtDW.icLoad_e = true;

  // InitializeConditions for Delay: '<S3>/slack_delay'
  rtDW.icLoad_m = true;
}

// Constructor
MPC_controller::MPC_controller() :
  rtU(),
  rtY(),
  rtDW(),
  rtM()
{
  // Currently there is no constructor body generated.
}

// Destructor
MPC_controller::~MPC_controller()
{
  // Currently there is no destructor body generated.
}

// Real-Time Model get method
MPC_controller::RT_MODEL * MPC_controller::getRTM()
{
  return (&rtM);
}

//
// File trailer for generated code.
//
// [EOF]
//
