//
// File: GHAC_ctrl_swingUp.cpp
//
// Code generated for Simulink model 'GHAC_ctrl_swingUp'.
//
// Model version                  : 1.7
// Simulink Coder version         : 23.2 (R2023b) 01-Aug-2023
// C/C++ source code generated on : Thu Apr 11 17:10:01 2024
//
// Target selection: ert.tlc
// Embedded hardware selection: ARM Compatible->ARM Cortex-M
// Code generation objectives:
//    1. Execution efficiency
//    2. RAM efficiency
// Validation result: Not run
//
#include "GHAC_ctrl_swingUp.h"
#include "rtwtypes.h"
#include <cmath>
#include <stddef.h>
#define NumBitsPerChar                 8U

static real_T look1_binlx(real_T u0, const real_T bp0[], const real_T table[],
  uint32_T maxIndex);
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

static real_T look1_binlx(real_T u0, const real_T bp0[], const real_T table[],
  uint32_T maxIndex)
{
  real_T frac;
  real_T yL_0d0;
  uint32_T iLeft;

  // Column-major Lookup 1-D
  // Search method: 'binary'
  // Use previous index: 'off'
  // Interpolation method: 'Linear point-slope'
  // Extrapolation method: 'Linear'
  // Use last breakpoint for index at or above upper limit: 'off'
  // Remove protection against out-of-range input in generated code: 'off'

  // Prelookup - Index and Fraction
  // Index Search method: 'binary'
  // Extrapolation method: 'Linear'
  // Use previous index: 'off'
  // Use last breakpoint for index at or above upper limit: 'off'
  // Remove protection against out-of-range input in generated code: 'off'

  if (u0 <= bp0[0U]) {
    iLeft = 0U;
    frac = (u0 - bp0[0U]) / (bp0[1U] - bp0[0U]);
  } else if (u0 < bp0[maxIndex]) {
    uint32_T bpIdx;
    uint32_T iRght;

    // Binary Search
    bpIdx = maxIndex >> 1U;
    iLeft = 0U;
    iRght = maxIndex;
    while (iRght - iLeft > 1U) {
      if (u0 < bp0[bpIdx]) {
        iRght = bpIdx;
      } else {
        iLeft = bpIdx;
      }

      bpIdx = (iRght + iLeft) >> 1U;
    }

    frac = (u0 - bp0[iLeft]) / (bp0[iLeft + 1U] - bp0[iLeft]);
  } else {
    iLeft = maxIndex - 1U;
    frac = (u0 - bp0[maxIndex - 1U]) / (bp0[maxIndex] - bp0[maxIndex - 1U]);
  }

  // Column-major Interpolation 1-D
  // Interpolation method: 'Linear point-slope'
  // Use last breakpoint for index at or above upper limit: 'off'
  // Overflow mode: 'wrapping'

  yL_0d0 = table[iLeft];
  return (table[iLeft + 1U] - yL_0d0) * frac + yL_0d0;
}

//
// Output and update for atomic system:
//    '<S8>/MATLAB Function'
//    '<S9>/MATLAB Function'
//
void GHAC_ctrl_swingUp::MATLABFunction(real_T rtu_x, real_T *rty_y, real_T rtp_a,
  real_T rtp_c)
{
  *rty_y = 1.0 / (std::exp((rtu_x - rtp_c) * -rtp_a) + 1.0);
}

// Model step function
void GHAC_ctrl_swingUp::step()
{
  real_T rtb_Abs;
  real_T rtb_Bias_e;
  real_T rtb_Bias_o;
  real_T rtb_W_idx_1;
  real_T rtb_abs_q;
  real_T rtb_w1_2;
  real_T rtb_w4;

  // Outputs for Atomic SubSystem: '<Root>/GHAC_ctrl_swingUp'
  // If: '<S1>/If' incorporates:
  //   Abs: '<S1>/Abs'
  //   Inport: '<Root>/X'

  if (std::abs(rtU.X_i[2]) < 0.43633231299858238) {
    // Outputs for IfAction SubSystem: '<S1>/HAC' incorporates:
    //   ActionPort: '<S2>/Action Port'

    // Lookup_n-D: '<S4>/xd lookup' incorporates:
    //   Bias: '<S4>/Bias1'
    //   Gain: '<S4>/Gain1'
    //   Inport: '<Root>/error'

    rtb_Abs = look1_binlx((rtU.error[1] + 2.0) * 0.25, rtConstP.pooled4,
                          rtConstP.xdlookup_tableData, 4U);

    // Bias: '<S11>/Bias' incorporates:
    //   Gain: '<S11>/Gain'

    rtb_Bias_o = 58.8399 * rtb_Abs - 29.41995;

    // MATLAB Function: '<S8>/MATLAB Function' incorporates:
    //   Inport: '<Root>/error'

    MATLABFunction(rtU.error[2], &rtb_Abs, 8.0, 0.0);

    // Lookup_n-D: '<S4>/q lookup' incorporates:
    //   Lookup_n-D: '<S4>/qd lookup'

    rtb_Abs = look1_binlx(rtb_Abs, rtConstP.pooled4, rtConstP.qlookup_tableData,
                          4U);

    // Bias: '<S12>/Bias' incorporates:
    //   Gain: '<S12>/Gain'

    rtb_Bias_e = 58.8399 * rtb_Abs - 29.41995;

    // MATLAB Function: '<S9>/MATLAB Function' incorporates:
    //   Inport: '<Root>/error'

    MATLABFunction(rtU.error[3], &rtb_Abs, 0.45, 0.0);

    // Abs: '<S4>/Abs' incorporates:
    //   Inport: '<Root>/error'

    rtb_abs_q = std::abs(rtU.error[2]);

    // If: '<S4>/If'
    if (rtb_abs_q <= 0.26179938779914941) {
      // Outputs for IfAction SubSystem: '<S4>/If Action Subsystem' incorporates:
      //   ActionPort: '<S5>/Action Port'

      // SignalConversion generated from: '<S5>/W' incorporates:
      //   Constant: '<S5>/weight'
      //   Merge: '<S4>/Merge'

      rtb_w1_2 = 0.25;
      rtb_W_idx_1 = 0.25;
      rtb_abs_q = 0.25;
      rtb_w4 = 0.25;

      // End of Outputs for SubSystem: '<S4>/If Action Subsystem'
    } else if (rtb_abs_q >= 0.87266462599716477) {
      // Outputs for IfAction SubSystem: '<S4>/If Action Subsystem1' incorporates:
      //   ActionPort: '<S6>/Action Port'

      // SignalConversion generated from: '<S6>/W' incorporates:
      //   Constant: '<S6>/weights'
      //   Merge: '<S4>/Merge'

      rtb_w1_2 = 0.0;
      rtb_W_idx_1 = 0.0;
      rtb_abs_q = 1.0;
      rtb_w4 = 0.0;

      // End of Outputs for SubSystem: '<S4>/If Action Subsystem1'
    } else {
      // Outputs for IfAction SubSystem: '<S4>/If Action Subsystem2' incorporates:
      //   ActionPort: '<S7>/Action Port'

      // Bias: '<S7>/Bias1' incorporates:
      //   Bias: '<S7>/Bias'
      //   Gain: '<S7>/Multiply'

      rtb_abs_q = (rtb_abs_q - 0.26179938779914941) * 1.2277667038517641 + 0.25;

      // Gain: '<S7>/Gain' incorporates:
      //   Constant: '<S7>/Constant'
      //   Sum: '<S7>/Subtract'

      rtb_w4 = (1.0 - rtb_abs_q) * 0.5;

      // Gain: '<S7>/Gain1' incorporates:
      //   Constant: '<S7>/Constant'
      //   Sum: '<S7>/Subtract1'

      rtb_w1_2 = ((1.0 - rtb_w4) - rtb_abs_q) * 0.5;

      // SignalConversion generated from: '<S7>/W'
      rtb_W_idx_1 = rtb_w1_2;

      // End of Outputs for SubSystem: '<S4>/If Action Subsystem2'
    }

    // End of If: '<S4>/If'

    // DotProduct: '<S4>/Dot Product' incorporates:
    //   Bias: '<S10>/Bias'
    //   Bias: '<S13>/Bias'
    //   Bias: '<S4>/Bias'
    //   Gain: '<S10>/Gain'
    //   Gain: '<S13>/Gain'
    //   Gain: '<S4>/Gain'
    //   Inport: '<Root>/error'
    //   Lookup_n-D: '<S4>/qd lookup'
    //   Lookup_n-D: '<S4>/x lookup'
    //   Merge: '<S4>/Merge'
    //   SignalConversion generated from: '<S4>/Dot Product'

    rtb_Abs = (((look1_binlx((rtU.error[0] + 0.43) * 1.1627906976744187,
      rtConstP.pooled4, rtConstP.xlookup_tableData, 4U) * 58.8399 - 29.41995) *
                rtb_w1_2 + rtb_W_idx_1 * rtb_Bias_o) + rtb_abs_q * rtb_Bias_e) +
      (58.8399 * look1_binlx(rtb_Abs, rtConstP.qdlookup_bp01Data,
        rtConstP.qdlookup_tableData, 6U) - 29.41995) * rtb_w4;

    // End of Outputs for SubSystem: '<S1>/HAC'
  } else {
    // Outputs for IfAction SubSystem: '<S1>/energy swing up' incorporates:
    //   ActionPort: '<S3>/Action Port'

    // Trigonometry: '<S20>/Cos' incorporates:
    //   Trigonometry: '<S16>/Cos'

    rtb_Bias_o = std::cos(rtU.X_i[2]);

    // Sum: '<S20>/Sum' incorporates:
    //   Gain: '<S20>/Gain'
    //   Gain: '<S20>/Gain1'
    //   Math: '<S20>/Square'
    //   Trigonometry: '<S20>/Cos'

    rtb_Abs = rtU.X_i[3] * rtU.X_i[3] * 0.0017479050000000001 + 0.1714109256825 *
      rtb_Bias_o;

    // Product: '<S16>/Product'
    rtb_Bias_o *= rtU.X_i[3];

    // Signum: '<S16>/Sign'
    if (std::isnan(rtb_Bias_o)) {
      // Signum: '<S17>/Sign'
      rtb_Bias_o = (rtNaN);
    } else if (rtb_Bias_o < 0.0) {
      // Signum: '<S17>/Sign'
      rtb_Bias_o = -1.0;
    } else {
      // Signum: '<S17>/Sign'
      rtb_Bias_o = (rtb_Bias_o > 0.0);
    }

    // Signum: '<S18>/Sign'
    if (std::isnan(rtU.X_i[0])) {
      rtb_Bias_e = (rtNaN);
    } else if (rtU.X_i[0] < 0.0) {
      rtb_Bias_e = -1.0;
    } else {
      rtb_Bias_e = (rtU.X_i[0] > 0.0);
    }

    // Signum: '<S19>/Sign'
    if (std::isnan(rtU.X_i[1])) {
      rtb_abs_q = (rtNaN);
    } else if (rtU.X_i[1] < 0.0) {
      rtb_abs_q = -1.0;
    } else {
      rtb_abs_q = (rtU.X_i[1] > 0.0);
    }

    // Signum: '<S17>/Sign1' incorporates:
    //   Constant: '<S17>/Constant'
    //   Sum: '<S17>/Sum'

    if (std::isnan(rtb_Abs - 0.1714109256825)) {
      rtb_w4 = (rtNaN);
    } else if (rtb_Abs - 0.1714109256825 < 0.0) {
      rtb_w4 = -1.0;
    } else {
      rtb_w4 = (rtb_Abs - 0.1714109256825 > 0.0);
    }

    // Sum: '<S3>/Sum' incorporates:
    //   Abs: '<S17>/Abs'
    //   Abs: '<S18>/Abs'
    //   Abs: '<S19>/Abs'
    //   Constant: '<S17>/Constant1'
    //   Constant: '<S18>/Constant'
    //   Constant: '<S19>/Constant'
    //   Gain: '<S16>/minus_k_su'
    //   Gain: '<S17>/k_em'
    //   Gain: '<S18>/Gain1'
    //   Gain: '<S18>/k_cw'
    //   Gain: '<S19>/Gain1'
    //   Gain: '<S19>/k_vw'
    //   Math: '<S17>/Exp'
    //   Math: '<S18>/Log'
    //   Math: '<S19>/Log'
    //   Product: '<S17>/Product1'
    //   Product: '<S18>/Product'
    //   Product: '<S19>/Product'
    //   Signum: '<S16>/Sign'
    //   Signum: '<S17>/Sign1'
    //   Signum: '<S18>/Sign'
    //   Signum: '<S19>/Sign'
    //   Sum: '<S17>/Subtract'
    //   Sum: '<S17>/Sum1'
    //   Sum: '<S18>/Sum'
    //   Sum: '<S19>/Sum'
    //
    //  About '<S17>/Exp':
    //   Operator: exp
    //
    //  About '<S18>/Log':
    //   Operator: log
    //
    //  About '<S19>/Log':
    //   Operator: log

    rtb_Abs = ((std::log(1.0 - 2.3255813953488373 * std::abs(rtU.X_i[0])) *
                rtb_Bias_e * 6.0 + std::log(1.0 - 0.5 * std::abs(rtU.X_i[1])) *
                rtb_abs_q * 2.5) + -2.0 * rtb_Bias_o) + (std::exp(std::abs
      (rtb_Abs - 0.22283420338725)) - 1.0) * (rtb_Bias_o * rtb_w4) * 10.0;

    // End of Outputs for SubSystem: '<S1>/energy swing up'
  }

  // End of If: '<S1>/If'

  // Saturate: '<S1>/Saturation'
  if (rtb_Abs > 29.41995) {
    // Outport: '<Root>/u'
    rtY.u = 29.41995;
  } else if (rtb_Abs < -29.41995) {
    // Outport: '<Root>/u'
    rtY.u = -29.41995;
  } else {
    // Outport: '<Root>/u'
    rtY.u = rtb_Abs;
  }

  // End of Saturate: '<S1>/Saturation'
  // End of Outputs for SubSystem: '<Root>/GHAC_ctrl_swingUp'
}

// Model initialize function
void GHAC_ctrl_swingUp::initialize()
{
  // Registration code

  // initialize non-finites
  rt_InitInfAndNaN(sizeof(real_T));
}

// Constructor
GHAC_ctrl_swingUp::GHAC_ctrl_swingUp() :
  rtU(),
  rtY(),
  rtM()
{
  // Currently there is no constructor body generated.
}

// Destructor
// Currently there is no destructor body generated.
GHAC_ctrl_swingUp::~GHAC_ctrl_swingUp() = default;

// Real-Time Model get method
GHAC_ctrl_swingUp::RT_MODEL * GHAC_ctrl_swingUp::getRTM()
{
  return (&rtM);
}

//
// File trailer for generated code.
//
// [EOF]
//
