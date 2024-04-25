//
// File: cartPend_control.cpp
//
// Code generated for Simulink model 'cartPend_control'.
//
// Model version                  : 1.23
// Simulink Coder version         : 9.8 (R2022b) 13-May-2022
// C/C++ source code generated on : Fri Feb 23 15:02:37 2024
//
// Target selection: ert.tlc
// Embedded hardware selection: ARM Compatible->ARM Cortex-M
// Code generation objectives:
//    1. Execution efficiency
//    2. RAM efficiency
// Validation result: Not run
//
#include "cartPend_control.h"
#include <cmath>
#include "rtwtypes.h"
#include <stddef.h>
#define NumBitsPerChar                 8U

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

// Model step function
void cartPend_control::step()
{
  real_T rtb_Abs;

  // Outputs for Atomic SubSystem: '<Root>/cartPend_control'
  // If: '<S1>/If' incorporates:
  //   Abs: '<S1>/Abs'
  //   Inport: '<Root>/X'

  if (std::abs(rtU.X_b[2]) < 0.3490658503988659) {
    // Outputs for IfAction SubSystem: '<S1>/LQR' incorporates:
    //   ActionPort: '<S2>/Action Port'

    // Gain: '<S2>/LQR_gain' incorporates:
    //   Inport: '<Root>/error'

    rtb_Abs = ((-13.944915126997138 * rtU.error[0] + -11.671088650515138 *
                rtU.error[1]) + -55.99305070541638 * rtU.error[2]) +
      -7.8999159299139547 * rtU.error[3];

    // End of Outputs for SubSystem: '<S1>/LQR'
  } else {
    real_T rtb_Abs_tmp;
    real_T tmp;
    real_T tmp_0;
    real_T tmp_1;

    // Outputs for IfAction SubSystem: '<S1>/energy swing up' incorporates:
    //   ActionPort: '<S3>/Action Port'

    // Trigonometry: '<S8>/Cos' incorporates:
    //   Trigonometry: '<S4>/Cos'

    rtb_Abs_tmp = std::cos(rtU.X_b[2]);

    // Sum: '<S8>/Sum' incorporates:
    //   Gain: '<S8>/Gain'
    //   Gain: '<S8>/Gain1'
    //   Math: '<S8>/Square'
    //   Trigonometry: '<S8>/Cos'

    rtb_Abs = rtU.X_b[3] * rtU.X_b[3] * 0.0017479050000000001 + 0.1714109256825 *
      rtb_Abs_tmp;

    // Product: '<S4>/Product'
    rtb_Abs_tmp *= rtU.X_b[3];

    // Signum: '<S4>/Sign'
    if (std::isnan(rtb_Abs_tmp)) {
      // Signum: '<S5>/Sign'
      rtb_Abs_tmp = (rtNaN);
    } else if (rtb_Abs_tmp < 0.0) {
      // Signum: '<S5>/Sign'
      rtb_Abs_tmp = -1.0;
    } else {
      // Signum: '<S5>/Sign'
      rtb_Abs_tmp = (rtb_Abs_tmp > 0.0);
    }

    // Signum: '<S6>/Sign'
    if (std::isnan(rtU.X_b[0])) {
      tmp = (rtNaN);
    } else if (rtU.X_b[0] < 0.0) {
      tmp = -1.0;
    } else {
      tmp = (rtU.X_b[0] > 0.0);
    }

    // Signum: '<S7>/Sign'
    if (std::isnan(rtU.X_b[1])) {
      tmp_0 = (rtNaN);
    } else if (rtU.X_b[1] < 0.0) {
      tmp_0 = -1.0;
    } else {
      tmp_0 = (rtU.X_b[1] > 0.0);
    }

    // Signum: '<S5>/Sign1' incorporates:
    //   Constant: '<S5>/Constant'
    //   Sum: '<S5>/Sum'

    if (std::isnan(rtb_Abs - 0.1714109256825)) {
      tmp_1 = (rtNaN);
    } else if (rtb_Abs - 0.1714109256825 < 0.0) {
      tmp_1 = -1.0;
    } else {
      tmp_1 = (rtb_Abs - 0.1714109256825 > 0.0);
    }

    // Sum: '<S3>/Sum' incorporates:
    //   Abs: '<S5>/Abs'
    //   Abs: '<S6>/Abs'
    //   Abs: '<S7>/Abs'
    //   Constant: '<S5>/Constant1'
    //   Constant: '<S6>/Constant'
    //   Constant: '<S7>/Constant'
    //   Gain: '<S4>/minus_k_su'
    //   Gain: '<S5>/k_em'
    //   Gain: '<S6>/Gain1'
    //   Gain: '<S6>/k_cw'
    //   Gain: '<S7>/Gain1'
    //   Gain: '<S7>/k_vw'
    //   Math: '<S5>/Exp'
    //   Math: '<S6>/Log'
    //   Math: '<S7>/Log'
    //   Product: '<S5>/Product1'
    //   Product: '<S6>/Product'
    //   Product: '<S7>/Product'
    //   Signum: '<S4>/Sign'
    //   Signum: '<S5>/Sign1'
    //   Signum: '<S6>/Sign'
    //   Signum: '<S7>/Sign'
    //   Sum: '<S5>/Subtract'
    //   Sum: '<S5>/Sum1'
    //   Sum: '<S6>/Sum'
    //   Sum: '<S7>/Sum'
    //
    //  About '<S5>/Exp':
    //   Operator: exp
    //
    //  About '<S6>/Log':
    //   Operator: log
    //
    //  About '<S7>/Log':
    //   Operator: log

    rtb_Abs = ((std::log(1.0 - 2.3255813953488373 * std::abs(rtU.X_b[0])) * tmp *
                6.0 + std::log(1.0 - 0.5 * std::abs(rtU.X_b[1])) * tmp_0 * 2.5)
               + -2.0 * rtb_Abs_tmp) + (std::exp(std::abs(rtb_Abs -
      0.22283420338725)) - 1.0) * (rtb_Abs_tmp * tmp_1) * 10.0;

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
  // End of Outputs for SubSystem: '<Root>/cartPend_control'
}

// Model initialize function
void cartPend_control::initialize()
{
  // Registration code

  // initialize non-finites
  rt_InitInfAndNaN(sizeof(real_T));
}

// Constructor
cartPend_control::cartPend_control():
  rtU(),
  rtY()
{
  // Currently there is no constructor body generated.
}

// Destructor
cartPend_control::~cartPend_control()
{
  // Currently there is no destructor body generated.
}

//
// File trailer for generated code.
//
// [EOF]
//
