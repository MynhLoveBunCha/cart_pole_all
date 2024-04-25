//
// File: cartPend_control.h
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
#ifndef RTW_HEADER_cartPend_control_h_
#define RTW_HEADER_cartPend_control_h_
#include "rtwtypes.h"
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

// Class declaration for model cartPend_control
class cartPend_control final
{
  // public data and function members
 public:
  // External inputs (root inport signals with default storage)
  struct ExtU {
    real_T X_b[4];                     // '<Root>/X'
    real_T error[4];                   // '<Root>/error'
  };

  // External outputs (root outports fed by signals with default storage)
  struct ExtY {
    real_T u;                          // '<Root>/u'
  };

  // Copy Constructor
  cartPend_control(cartPend_control const&) = delete;

  // Assignment Operator
  cartPend_control& operator= (cartPend_control const&) & = delete;

  // Move Constructor
  cartPend_control(cartPend_control &&) = delete;

  // Move Assignment Operator
  cartPend_control& operator= (cartPend_control &&) = delete;

  // External inputs
  ExtU rtU;

  // External outputs
  ExtY rtY;

  // model initialize function
  void initialize();

  // model step function
  void step();

  // Constructor
  cartPend_control();

  // Destructor
  ~cartPend_control();
};

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
//  hilite_system('cart_pend_controller/cartPend_control')    - opens subsystem cart_pend_controller/cartPend_control
//  hilite_system('cart_pend_controller/cartPend_control/Kp') - opens and selects block Kp
//
//  Here is the system hierarchy for this model
//
//  '<Root>' : 'cart_pend_controller'
//  '<S1>'   : 'cart_pend_controller/cartPend_control'
//  '<S2>'   : 'cart_pend_controller/cartPend_control/LQR'
//  '<S3>'   : 'cart_pend_controller/cartPend_control/energy swing up'
//  '<S4>'   : 'cart_pend_controller/cartPend_control/energy swing up/energy injection'
//  '<S5>'   : 'cart_pend_controller/cartPend_control/energy swing up/energy maintenance'
//  '<S6>'   : 'cart_pend_controller/cartPend_control/energy swing up/position potential well'
//  '<S7>'   : 'cart_pend_controller/cartPend_control/energy swing up/velocity potential well'
//  '<S8>'   : 'cart_pend_controller/cartPend_control/energy swing up/energy maintenance/Pend energy'

#endif                                 // RTW_HEADER_cartPend_control_h_

//
// File trailer for generated code.
//
// [EOF]
//
