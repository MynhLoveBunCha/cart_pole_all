//
// File: cartPend_HAC_control.cpp
//
// Code generated for Simulink model 'cartPend_HAC_control'.
//
// Model version                  : 1.6
// Simulink Coder version         : 9.8 (R2022b) 13-May-2022
// C/C++ source code generated on : Mon Feb 26 17:32:52 2024
//
// Target selection: ert.tlc
// Embedded hardware selection: ARM Compatible->ARM Cortex-M
// Code generation objectives:
//    1. Execution efficiency
//    2. RAM efficiency
// Validation result: Not run
//
#include "cartPend_HAC_control.h"
#include <cmath>
#include "rtwtypes.h"
#include <stddef.h>
#define NumBitsPerChar                 8U

void rt_Spline2Derivd(const real_T *x, const real_T *y, uint32_T n, real_T *u,
                      real_T *y2);
real_T look_SplNBinXZd(uint32_T numDims, const real_T* u, const rt_LUTSplineWork
  * const SWork);
real_T intrp_NSpld(uint32_T numDims, const rt_LUTSplineWork * const splWork,
                   uint32_T extrapMethod);
static uint32_T plook_binx(real_T u, const real_T bp[], uint32_T maxIndex,
  real_T *fraction);
static uint32_T binsearch_u32d(real_T u, const real_T bp[], uint32_T startIndex,
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

//
// Second derivative initialization function for spline
// for last dimension.
//
void rt_Spline2Derivd(const real_T *x, const real_T *y, uint32_T n, real_T *u,
                      real_T *y2)
{
  real_T p, qn, sig, un;
  uint32_T n1, i, k;
  n1 = n - 1U;
  y2[0U] = 0.0;
  u[0U] = 0.0;
  for (i = 1U; i < n1; i++) {
    real_T dxm1{ x[i] - x[i - 1U] };

    real_T dxp1{ x[i + 1U] - x[i] };

    real_T dxpm{ dxp1 + dxm1 };

    sig = dxm1 / dxpm;
    p = (sig * y2[i - 1U]) + 2.0;
    y2[i] = (sig - 1.0) / p;
    u[i] = ((y[i + 1U] - y[i]) / dxp1) - ((y[i] - y[i - 1U]) / dxm1);
    u[i] = (((6.0 * u[i]) / dxpm) - (sig * u[i - 1U])) / p;
  }

  qn = 0.0;
  un = 0.0;
  y2[n1] = (un - (qn * u[n1 - 1U])) / ((qn * y2[n1 - 1U]) + 1.0);
  for (k = n1; k > 0U; k--) {
    y2[k-1U] = (y2[k-1U] * y2[k]) + u[k-1U];
  }

  return;
}

// n-D Spline interpolation function
real_T look_SplNBinXZd(uint32_T numDims, const real_T* u, const rt_LUTSplineWork
  * const SWork)
{
  //
  //    n-D column-major table lookup operating on real_T with:
  //        - Spline interpolation
  //        - Linear extrapolation
  //        - Binary breakpoint search
  //        - Index search starts at the same place each time

  rt_LUTnWork * const TWork_look{ SWork->m_TWork };

  real_T* const fraction{ static_cast<real_T*>(TWork_look->m_bpLambda) };

  uint32_T* const bpIdx { TWork_look->m_bpIndex };

  const uint32_T* const maxIndex{ TWork_look->m_maxIndex };

  uint32_T k;
  for (k = 0U; k < numDims; k++) {
    const real_T* const bpData{ ((const real_T * const *)TWork_look->m_bpDataSet)
      [k] };

    bpIdx[k] = plook_binx(u[k], bpData, maxIndex[k], &fraction[k]);
  }

  return(intrp_NSpld(numDims, SWork, 2U));
}

// n-D natural spline calculation function
real_T intrp_NSpld(uint32_T numDims, const rt_LUTSplineWork * const splWork,
                   uint32_T extrapMethod)
{
  uint32_T il;
  uint32_T iu, k, i;
  real_T h, s, p, smsq, pmsq;

  // intermediate results work areas "this" and "next"
  const rt_LUTnWork *TWork_interp{ static_cast<const rt_LUTnWork *>
    (splWork->m_TWork) };

  const real_T *fraction { static_cast<real_T *>(TWork_interp->m_bpLambda) };

  const real_T *yp { static_cast<real_T *>(TWork_interp->m_tableData) };

  real_T *yyA { static_cast<real_T *>(splWork->m_yyA) };

  real_T *yyB { static_cast<real_T *>(splWork->m_yyB) };

  real_T *yy2 { static_cast<real_T *>(splWork->m_yy2) };

  real_T *up { static_cast<real_T *>(splWork->m_up) };

  real_T *y2 { static_cast<real_T *>(splWork->m_y2) };

  const real_T **bpDataSet { (const real_T **) TWork_interp->m_bpDataSet };

  const real_T *xp { bpDataSet[0U] };

  real_T *yy { yyA };

  uint32_T bufBank { 0U };

  uint32_T len { TWork_interp->m_maxIndex[0U] + 1U };

  // Generate at-point splines in each dimension
  for (k = 0U; k < numDims; k++ ) {
    // this dimension's input setup
    xp = bpDataSet[k];
    len = TWork_interp->m_maxIndex[k] + 1U;
    il = TWork_interp->m_bpIndex[k];
    iu = il + 1U;
    h = xp[iu] - xp[il];
    p = fraction[k];
    s = 1.0 - p;
    pmsq = p * ((p*p) - 1.0);
    smsq = s * ((s*s) - 1.0);

    //
    //  Calculate spline curves for input in this
    //  dimension at each value of the higher
    //  other dimensions\' points in the table.

    if ((p > 1.0) && (extrapMethod == 2U) ) {
      real_T slope;
      for (i = 0U; i < splWork->m_numYWorkElts[k]; i++) {
        slope = (yp[iu] - yp[il]) + ((y2[il]*h*h)*(1.0/6.0));
        yy[i] = yp[iu] + (slope * (p-1.0));
        yp = &yp[len];
        y2 = &y2[len];
      }
    } else if ((p < 0.0) && (extrapMethod == 2U) ) {
      real_T slope;
      for (i = 0U; i < splWork->m_numYWorkElts[k]; i++) {
        slope = (yp[iu] - yp[il]) - ((y2[iu]*h*h)*(1.0/6.0));
        yy[i] = yp[il] + (slope * p);
        yp = &yp[len];
        y2 = &y2[len];
      }
    } else {
      for (i = 0U; i < splWork->m_numYWorkElts[k]; i++) {
        yy[i] = yp[il] + p * (yp[iu] - yp[il]) +
          ((smsq * y2[il] + pmsq * y2[iu])*h*h)*(1.0/6.0);
        yp = &yp[len];
        y2 = &y2[len];
      }
    }

    // set pointers to new result and calculate second derivatives
    yp = yy;
    y2 = yy2;
    if (splWork->m_numYWorkElts[k+1U] > 0U ) {
      uint32_T nextLen{ TWork_interp->m_maxIndex[k+1U] + 1U };

      const real_T *nextXp { bpDataSet[k+1U] };

      for (i = 0U; i < splWork->m_numYWorkElts[k+1U]; i++) {
        rt_Spline2Derivd(nextXp, yp, nextLen, up, y2);
        yp = &yp[nextLen];
        y2 = &y2[nextLen];
      }
    }

    //
    //  Set work vectors yp, y2 and yy for next iteration;
    //  the yy just calculated becomes the yp in the
    //  next iteration, y2 was just calculated for these
    //  new points and the yy buffer is swapped to the space
    //  for storing the next iteration\'s results.

    yp = yy;
    y2 = yy2;

    //
    //  Swap buffers for next dimension and
    //  toggle bufBank for next iteration.

    if (bufBank == 0U) {
      yy = yyA;
      bufBank = 1U;
    } else {
      yy = yyB;
      bufBank = 0U;
    }
  }

  return( yp[0U] );
}

static uint32_T plook_binx(real_T u, const real_T bp[], uint32_T maxIndex,
  real_T *fraction)
{
  uint32_T bpIndex;

  // Prelookup - Index and Fraction
  // Index Search method: 'binary'
  // Extrapolation method: 'Linear'
  // Use previous index: 'off'
  // Use last breakpoint for index at or above upper limit: 'off'
  // Remove protection against out-of-range input in generated code: 'off'

  if (u <= bp[0U]) {
    bpIndex = 0U;
    *fraction = (u - bp[0U]) / (bp[1U] - bp[0U]);
  } else if (u < bp[maxIndex]) {
    bpIndex = binsearch_u32d(u, bp, maxIndex >> 1U, maxIndex);
    *fraction = (u - bp[bpIndex]) / (bp[bpIndex + 1U] - bp[bpIndex]);
  } else {
    bpIndex = maxIndex - 1U;
    *fraction = (u - bp[maxIndex - 1U]) / (bp[maxIndex] - bp[maxIndex - 1U]);
  }

  return bpIndex;
}

static uint32_T binsearch_u32d(real_T u, const real_T bp[], uint32_T startIndex,
  uint32_T maxIndex)
{
  uint32_T bpIdx;
  uint32_T bpIndex;
  uint32_T iRght;

  // Binary Search
  bpIdx = startIndex;
  bpIndex = 0U;
  iRght = maxIndex;
  while (iRght - bpIndex > 1U) {
    if (u < bp[bpIdx]) {
      iRght = bpIdx;
    } else {
      bpIndex = bpIdx;
    }

    bpIdx = (iRght + bpIndex) >> 1U;
  }

  return bpIndex;
}

// Model step function
void cartPend_HAC_control::step()
{
  // local block i/o variables
  real_T rtb_Product1_b;
  real_T rtb_Abs;

  // Outputs for Atomic SubSystem: '<Root>/cartPend_HAC_control'
  // If: '<S1>/If' incorporates:
  //   Abs: '<S1>/Abs'
  //   Inport: '<Root>/X'

  if (std::abs(rtU.X_d[2]) < 0.19198621771937624) {
    real_T rtb_q_s;
    real_T rtb_x_d_s;

    // Outputs for IfAction SubSystem: '<S1>/HAC' incorporates:
    //   ActionPort: '<S2>/Action Port'

    // Product: '<S4>/Product1' incorporates:
    //   Constant: '<S4>/x_kt'
    //   Inport: '<Root>/error'
    //   Sum: '<S4>/Subtract5'

    rtb_Product1_b = rtU.error[0] - -3.0;

    // Product: '<S4>/Divide'
    rtb_Abs = rtb_Product1_b / 6.0;

    // Product: '<S4>/Product1' incorporates:
    //   Constant: '<S4>/x_dot_kt'
    //   Inport: '<Root>/error'
    //   Sum: '<S4>/Subtract6'

    rtb_Product1_b = rtU.error[1] - -3.0;

    // Product: '<S4>/Divide1'
    rtb_x_d_s = rtb_Product1_b / 6.0;

    // Product: '<S4>/Product1' incorporates:
    //   Constant: '<S4>/q_kt'
    //   Inport: '<Root>/error'
    //   Sum: '<S4>/Subtract7'

    rtb_Product1_b = rtU.error[2] - -0.3;

    // Product: '<S4>/Divide2'
    rtb_q_s = rtb_Product1_b / 0.6;

    // Product: '<S4>/Product1' incorporates:
    //   Constant: '<S4>/q_dot_kt'
    //   Inport: '<Root>/error'
    //   Product: '<S4>/Divide3'
    //   Product: '<S4>/Product'
    //   Sum: '<S4>/Subtract8'

    rtb_Product1_b = rtU.error[3] - -1.0;
    rtb_Product1_b = rtb_Abs * rtb_x_d_s * rtb_q_s * (rtb_Product1_b / 2.0);

    // Lookup_n-D: '<S4>/1-D Lookup Table'
    //
    //  About '<S4>/1-D Lookup Table':
    //        Table size:  16
    //     Interpolation:  Spline
    //     Extrapolation:  Linear
    //    Breakpt Search:  Binary
    //     Breakpt Cache:  OFF

    rtb_Product1_b = look_SplNBinXZd(1U, &rtb_Product1_b, (rt_LUTSplineWork*)
      &rtDW.SWork[0]);

    // Product: '<S4>/Product1'
    rtb_Product1_b *= 80.0;

    // Sum: '<S4>/Add'
    rtb_Abs = rtb_Product1_b - 40.0;

    // End of Outputs for SubSystem: '<S1>/HAC'
  } else {
    real_T rtb_q_s;
    real_T rtb_x_d_s;
    real_T tmp;
    real_T tmp_0;

    // Outputs for IfAction SubSystem: '<S1>/energy swing up' incorporates:
    //   ActionPort: '<S3>/Action Port'

    // Trigonometry: '<S9>/Cos' incorporates:
    //   Trigonometry: '<S5>/Cos'

    rtb_x_d_s = std::cos(rtU.X_d[2]);

    // Sum: '<S9>/Sum' incorporates:
    //   Gain: '<S9>/Gain'
    //   Gain: '<S9>/Gain1'
    //   Math: '<S9>/Square'
    //   Trigonometry: '<S9>/Cos'

    rtb_Abs = rtU.X_d[3] * rtU.X_d[3] * 0.0017479050000000001 + 0.1714109256825 *
      rtb_x_d_s;

    // Product: '<S5>/Product'
    rtb_x_d_s *= rtU.X_d[3];

    // Signum: '<S5>/Sign'
    if (std::isnan(rtb_x_d_s)) {
      // Signum: '<S6>/Sign'
      rtb_x_d_s = (rtNaN);
    } else if (rtb_x_d_s < 0.0) {
      // Signum: '<S6>/Sign'
      rtb_x_d_s = -1.0;
    } else {
      // Signum: '<S6>/Sign'
      rtb_x_d_s = (rtb_x_d_s > 0.0);
    }

    // Signum: '<S7>/Sign'
    if (std::isnan(rtU.X_d[0])) {
      rtb_q_s = (rtNaN);
    } else if (rtU.X_d[0] < 0.0) {
      rtb_q_s = -1.0;
    } else {
      rtb_q_s = (rtU.X_d[0] > 0.0);
    }

    // Signum: '<S8>/Sign'
    if (std::isnan(rtU.X_d[1])) {
      tmp = (rtNaN);
    } else if (rtU.X_d[1] < 0.0) {
      tmp = -1.0;
    } else {
      tmp = (rtU.X_d[1] > 0.0);
    }

    // Signum: '<S6>/Sign1' incorporates:
    //   Constant: '<S6>/Constant'
    //   Sum: '<S6>/Sum'

    if (std::isnan(rtb_Abs - 0.1714109256825)) {
      tmp_0 = (rtNaN);
    } else if (rtb_Abs - 0.1714109256825 < 0.0) {
      tmp_0 = -1.0;
    } else {
      tmp_0 = (rtb_Abs - 0.1714109256825 > 0.0);
    }

    // Sum: '<S3>/Sum' incorporates:
    //   Abs: '<S6>/Abs'
    //   Abs: '<S7>/Abs'
    //   Abs: '<S8>/Abs'
    //   Constant: '<S6>/Constant1'
    //   Constant: '<S7>/Constant'
    //   Constant: '<S8>/Constant'
    //   Gain: '<S5>/minus_k_su'
    //   Gain: '<S6>/k_em'
    //   Gain: '<S7>/Gain1'
    //   Gain: '<S7>/k_cw'
    //   Gain: '<S8>/Gain1'
    //   Gain: '<S8>/k_vw'
    //   Math: '<S6>/Exp'
    //   Math: '<S7>/Log'
    //   Math: '<S8>/Log'
    //   Product: '<S6>/Product1'
    //   Product: '<S7>/Product'
    //   Product: '<S8>/Product'
    //   Signum: '<S5>/Sign'
    //   Signum: '<S6>/Sign1'
    //   Signum: '<S7>/Sign'
    //   Signum: '<S8>/Sign'
    //   Sum: '<S6>/Subtract'
    //   Sum: '<S6>/Sum1'
    //   Sum: '<S7>/Sum'
    //   Sum: '<S8>/Sum'
    //
    //  About '<S6>/Exp':
    //   Operator: exp
    //
    //  About '<S7>/Log':
    //   Operator: log
    //
    //  About '<S8>/Log':
    //   Operator: log

    rtb_Abs = ((std::log(1.0 - 2.3255813953488373 * std::abs(rtU.X_d[0])) *
                rtb_q_s * 6.0 + std::log(1.0 - 0.5 * std::abs(rtU.X_d[1])) * tmp
                * 2.5) + -2.0 * rtb_x_d_s) + (std::exp(std::abs(rtb_Abs -
      0.22283420338725)) - 1.0) * (rtb_x_d_s * tmp_0) * 10.0;

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
  // End of Outputs for SubSystem: '<Root>/cartPend_HAC_control'
}

// Model initialize function
void cartPend_HAC_control::initialize()
{
  // Registration code

  // initialize non-finites
  rt_InitInfAndNaN(sizeof(real_T));

  // SystemInitialize for Atomic SubSystem: '<Root>/cartPend_HAC_control'
  // SystemInitialize for IfAction SubSystem: '<S1>/HAC'
  // Start for Lookup_n-D: '<S4>/1-D Lookup Table'
  {
    rt_LUTnWork *TWork_start{ (rt_LUTnWork *) &rtDW.TWork[0] };

    void **bpDataSet{ static_cast<void **>(&rtDW.m_bpDataSet) };

    TWork_start->m_dimSizes = static_cast<const uint32_T *>
      (&rtConstP.uDLookupTable_dimSizes);
    TWork_start->m_tableData = (void *) rtConstP.uDLookupTable_tableData;
    TWork_start->m_bpDataSet = bpDataSet;
    TWork_start->m_bpIndex = &rtDW.m_bpIndex;
    TWork_start->m_bpLambda = &rtDW.m_bpLambda;
    TWork_start->m_maxIndex = static_cast<const uint32_T *>
      (&rtConstP.uDLookupTable_maxIndex);
    bpDataSet[0] = (void *) rtConstP.uDLookupTable_bp01Data;
  }

  {
    const real_T **bpDataSet;
    const real_T *xp, *yp;
    real_T *up, *y2;
    uint32_T yWorkElIdx, len;
    const rt_LUTnWork *TWork_interp;
    rt_LUTSplineWork *rt_SplWk{ (rt_LUTSplineWork*)&rtDW.SWork[0] };

    rt_SplWk->m_TWork = (rt_LUTnWork*)&rtDW.TWork[0];
    rt_SplWk->m_yyA = &rtDW.m_yyA;
    rt_SplWk->m_yyB = &rtDW.m_yyB;
    rt_SplWk->m_yy2 = &rtDW.m_yy2;
    rt_SplWk->m_up = &rtDW.m_up[0];
    rt_SplWk->m_y2 = &rtDW.m_y2[0];
    rt_SplWk->m_numYWorkElts = rtConstP.uDLookupTable_numYWorkElts;

    // If table and bps are not-tunable then precalculate 1st dim 2nd deriv
    TWork_interp = static_cast<const rt_LUTnWork *>(rt_SplWk->m_TWork);
    bpDataSet = (const real_T **) TWork_interp->m_bpDataSet;
    xp = bpDataSet[0U];
    yp = static_cast<real_T *>(TWork_interp->m_tableData);
    len = TWork_interp->m_maxIndex[0U] + 1U;
    up = static_cast<real_T *>(rt_SplWk->m_up);
    y2 = static_cast<real_T *>(rt_SplWk->m_y2);

    // Generate first dimension's second derivatives
    for (yWorkElIdx = 0U; yWorkElIdx < rt_SplWk->m_numYWorkElts[0U]; yWorkElIdx
         ++) {
      rt_Spline2Derivd(xp, yp, len, up, y2);
      yp = &yp[len];
      y2 = &y2[len];
    }
  }

  // End of SystemInitialize for SubSystem: '<S1>/HAC'
  // End of SystemInitialize for SubSystem: '<Root>/cartPend_HAC_control'
}

// Constructor
cartPend_HAC_control::cartPend_HAC_control():
  rtU(),
  rtY(),
  rtDW()
{
  // Currently there is no constructor body generated.
}

// Destructor
cartPend_HAC_control::~cartPend_HAC_control()
{
  // Currently there is no destructor body generated.
}

//
// File trailer for generated code.
//
// [EOF]
//
