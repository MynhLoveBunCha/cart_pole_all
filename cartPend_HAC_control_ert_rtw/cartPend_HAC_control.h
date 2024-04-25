//
// File: cartPend_HAC_control.h
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
#ifndef RTW_HEADER_cartPend_HAC_control_h_
#define RTW_HEADER_cartPend_HAC_control_h_
#include "rtwtypes.h"
#include "rtsplntypes.h"
#include <stddef.h>

extern "C"
{
  static real_T rtGetNaN(void);
  static real32_T rtGetNaNF(void);
}                                      // extern "C"

#define NOT_USING_NONFINITE_LITERALS   1

extern "C"
{
  extern real_T rtInf;
  extern real_T rtMinusInf;
  extern real_T rtNaN;
  extern real32_T rtInfF;
  extern real32_T rtMinusInfF;
  extern real32_T rtNaNF;
  static void rt_InitInfAndNaN(size_t realSize);
  static boolean_T rtIsInf(real_T value);
  static boolean_T rtIsInfF(real32_T value);
  static boolean_T rtIsNaN(real_T value);
  static boolean_T rtIsNaNF(real32_T value);
  struct BigEndianIEEEDouble {
    struct {
      uint32_T wordH;
      uint32_T wordL;
    } words;
  };

  struct LittleEndianIEEEDouble {
    struct {
      uint32_T wordL;
      uint32_T wordH;
    } words;
  };

  struct IEEESingle {
    union {
      real32_T wordLreal;
      uint32_T wordLuint;
    } wordL;
  };
}                                      // extern "C"

extern "C"
{
  static real_T rtGetInf(void);
  static real32_T rtGetInfF(void);
  static real_T rtGetMinusInf(void);
  static real32_T rtGetMinusInfF(void);
}                                      // extern "C"

// Class declaration for model cartPend_HAC_control
class cartPend_HAC_control final
{
  // public data and function members
 public:
  // Block signals and states (default storage) for system '<Root>'
  struct DW {
    real_T m_up[16];                   // '<S4>/1-D Lookup Table'
    real_T m_y2[16];                   // '<S4>/1-D Lookup Table'
    real_T m_bpLambda;                 // '<S4>/1-D Lookup Table'
    real_T m_yyA;                      // '<S4>/1-D Lookup Table'
    real_T m_yyB;                      // '<S4>/1-D Lookup Table'
    real_T m_yy2;                      // '<S4>/1-D Lookup Table'
    uint32_T m_bpIndex;                // '<S4>/1-D Lookup Table'
    void* TWork[6];                    // '<S4>/1-D Lookup Table'
    void* SWork[9];                    // '<S4>/1-D Lookup Table'
    void* m_bpDataSet;                 // '<S4>/1-D Lookup Table'
  };

  // Constant parameters (default storage)
  struct ConstP {
    // Expression: interp_y
    //  Referenced by: '<S4>/1-D Lookup Table'

    real_T uDLookupTable_tableData[16];

    // Expression: interp_x
    //  Referenced by: '<S4>/1-D Lookup Table'

    real_T uDLookupTable_bp01Data[16];

    // Computed Parameter: uDLookupTable_maxIndex
    //  Referenced by: '<S4>/1-D Lookup Table'

    uint32_T uDLookupTable_maxIndex;

    // Computed Parameter: uDLookupTable_dimSizes
    //  Referenced by: '<S4>/1-D Lookup Table'

    uint32_T uDLookupTable_dimSizes;

    // Computed Parameter: uDLookupTable_numYWorkElts
    //  Referenced by: '<S4>/1-D Lookup Table'

    uint32_T uDLookupTable_numYWorkElts[2];
  };

  // External inputs (root inport signals with default storage)
  struct ExtU {
    real_T X_d[4];                     // '<Root>/X'
    real_T error[4];                   // '<Root>/error'
  };

  // External outputs (root outports fed by signals with default storage)
  struct ExtY {
    real_T u;                          // '<Root>/u'
  };

  // Copy Constructor
  cartPend_HAC_control(cartPend_HAC_control const&) = delete;

  // Assignment Operator
  cartPend_HAC_control& operator= (cartPend_HAC_control const&) & = delete;

  // Move Constructor
  cartPend_HAC_control(cartPend_HAC_control &&) = delete;

  // Move Assignment Operator
  cartPend_HAC_control& operator= (cartPend_HAC_control &&) = delete;

  // External inputs
  ExtU rtU;

  // External outputs
  ExtY rtY;

  // model initialize function
  void initialize();

  // model step function
  void step();

  // Constructor
  cartPend_HAC_control();

  // Destructor
  ~cartPend_HAC_control();

  // private data and function members
 private:
  // Block states
  DW rtDW;
};

// Constant parameters (default storage)
extern const cartPend_HAC_control::ConstP rtConstP;

//-
//  The generated code includes comments that allow you to trace directly
//  back to the appropriate location in the model.  The basic format
//  is <system>/block_name, where system is the system number (uniquely
//  assigned by Simulink) and block_name is the name of the block.
//
//  Note that this particular code originates from a subsystem build,
//  and has its own system numbers different from the parent model.
//  Refer to the system hierarchy for this subsystem below, and use the
//  MATLAB hilite_system command to trace the generated code back
//  to the parent model.  For example,
//
//  hilite_system('HAC_swingUp_controller/cartPend_HAC_control')    - opens subsystem HAC_swingUp_controller/cartPend_HAC_control
//  hilite_system('HAC_swingUp_controller/cartPend_HAC_control/Kp') - opens and selects block Kp
//
//  Here is the system hierarchy for this model
//
//  '<Root>' : 'HAC_swingUp_controller'
//  '<S1>'   : 'HAC_swingUp_controller/cartPend_HAC_control'
//  '<S2>'   : 'HAC_swingUp_controller/cartPend_HAC_control/HAC'
//  '<S3>'   : 'HAC_swingUp_controller/cartPend_HAC_control/energy swing up'
//  '<S4>'   : 'HAC_swingUp_controller/cartPend_HAC_control/HAC/HAC'
//  '<S5>'   : 'HAC_swingUp_controller/cartPend_HAC_control/energy swing up/energy injection'
//  '<S6>'   : 'HAC_swingUp_controller/cartPend_HAC_control/energy swing up/energy maintenance'
//  '<S7>'   : 'HAC_swingUp_controller/cartPend_HAC_control/energy swing up/position potential well'
//  '<S8>'   : 'HAC_swingUp_controller/cartPend_HAC_control/energy swing up/velocity potential well'
//  '<S9>'   : 'HAC_swingUp_controller/cartPend_HAC_control/energy swing up/energy maintenance/Pend energy'

#endif                                 // RTW_HEADER_cartPend_HAC_control_h_

//
// File trailer for generated code.
//
// [EOF]
//
