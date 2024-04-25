//
// File: GHAC_ctrl_swingUp.h
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
#ifndef RTW_HEADER_GHAC_ctrl_swingUp_h_
#define RTW_HEADER_GHAC_ctrl_swingUp_h_
#include "rtwtypes.h"
#include <stddef.h>

// Macros for accessing real-time model data structure
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

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

// Class declaration for model GHAC_ctrl_swingUp
class GHAC_ctrl_swingUp final
{
  // public data and function members
 public:
  // Constant parameters (default storage)
  struct ConstP {
    // Expression: u_x_sqm
    //  Referenced by: '<S4>/x lookup'

    real_T xlookup_tableData[5];

    // Pooled Parameter (Mixed Expressions)
    //  Referenced by:
    //    '<S4>/q lookup'
    //    '<S4>/x lookup'
    //    '<S4>/xd lookup'

    real_T pooled4[5];

    // Expression: u_xd_sqm
    //  Referenced by: '<S4>/xd lookup'

    real_T xdlookup_tableData[5];

    // Expression: u_q_sqm
    //  Referenced by: '<S4>/q lookup'

    real_T qlookup_tableData[5];

    // Expression: u_qd_sqm
    //  Referenced by: '<S4>/qd lookup'

    real_T qdlookup_tableData[7];

    // Expression: qd_sqm
    //  Referenced by: '<S4>/qd lookup'

    real_T qdlookup_bp01Data[7];
  };

  // External inputs (root inport signals with default storage)
  struct ExtU {
    real_T X_i[4];                     // '<Root>/X'
    real_T error[4];                   // '<Root>/error'
  };

  // External outputs (root outports fed by signals with default storage)
  struct ExtY {
    real_T u;                          // '<Root>/u'
  };

  // Real-time Model Data Structure
  struct RT_MODEL {
    const char_T * volatile errorStatus;
  };

  // Copy Constructor
  GHAC_ctrl_swingUp(GHAC_ctrl_swingUp const&) = delete;

  // Assignment Operator
  GHAC_ctrl_swingUp& operator= (GHAC_ctrl_swingUp const&) & = delete;

  // Move Constructor
  GHAC_ctrl_swingUp(GHAC_ctrl_swingUp &&) = delete;

  // Move Assignment Operator
  GHAC_ctrl_swingUp& operator= (GHAC_ctrl_swingUp &&) = delete;

  // Real-Time Model get method
  GHAC_ctrl_swingUp::RT_MODEL * getRTM();

  // External inputs
  ExtU rtU;

  // External outputs
  ExtY rtY;

  // model initialize function
  void initialize();

  // model step function
  void step();

  // Constructor
  GHAC_ctrl_swingUp();

  // Destructor
  ~GHAC_ctrl_swingUp();

  // private data and function members
 private:
  // private member function(s) for subsystem '<S8>/MATLAB Function'
  static void MATLABFunction(real_T rtu_x, real_T *rty_y, real_T rtp_a, real_T
    rtp_c);

  // Real-Time Model
  RT_MODEL rtM;
};

// Constant parameters (default storage)
extern const GHAC_ctrl_swingUp::ConstP rtConstP;

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
//  hilite_system('CODE_GEN/GHAC_ctrl_swingUp')    - opens subsystem CODE_GEN/GHAC_ctrl_swingUp
//  hilite_system('CODE_GEN/GHAC_ctrl_swingUp/Kp') - opens and selects block Kp
//
//  Here is the system hierarchy for this model
//
//  '<Root>' : 'CODE_GEN'
//  '<S1>'   : 'CODE_GEN/GHAC_ctrl_swingUp'
//  '<S2>'   : 'CODE_GEN/GHAC_ctrl_swingUp/HAC'
//  '<S3>'   : 'CODE_GEN/GHAC_ctrl_swingUp/energy swing up'
//  '<S4>'   : 'CODE_GEN/GHAC_ctrl_swingUp/HAC/HAC'
//  '<S5>'   : 'CODE_GEN/GHAC_ctrl_swingUp/HAC/HAC/If Action Subsystem'
//  '<S6>'   : 'CODE_GEN/GHAC_ctrl_swingUp/HAC/HAC/If Action Subsystem1'
//  '<S7>'   : 'CODE_GEN/GHAC_ctrl_swingUp/HAC/HAC/If Action Subsystem2'
//  '<S8>'   : 'CODE_GEN/GHAC_ctrl_swingUp/HAC/HAC/Sigmoidal MF'
//  '<S9>'   : 'CODE_GEN/GHAC_ctrl_swingUp/HAC/HAC/Sigmoidal MF1'
//  '<S10>'  : 'CODE_GEN/GHAC_ctrl_swingUp/HAC/HAC/denorm_u'
//  '<S11>'  : 'CODE_GEN/GHAC_ctrl_swingUp/HAC/HAC/denorm_u1'
//  '<S12>'  : 'CODE_GEN/GHAC_ctrl_swingUp/HAC/HAC/denorm_u2'
//  '<S13>'  : 'CODE_GEN/GHAC_ctrl_swingUp/HAC/HAC/denorm_u3'
//  '<S14>'  : 'CODE_GEN/GHAC_ctrl_swingUp/HAC/HAC/Sigmoidal MF/MATLAB Function'
//  '<S15>'  : 'CODE_GEN/GHAC_ctrl_swingUp/HAC/HAC/Sigmoidal MF1/MATLAB Function'
//  '<S16>'  : 'CODE_GEN/GHAC_ctrl_swingUp/energy swing up/energy injection'
//  '<S17>'  : 'CODE_GEN/GHAC_ctrl_swingUp/energy swing up/energy maintenance'
//  '<S18>'  : 'CODE_GEN/GHAC_ctrl_swingUp/energy swing up/position potential well'
//  '<S19>'  : 'CODE_GEN/GHAC_ctrl_swingUp/energy swing up/velocity potential well'
//  '<S20>'  : 'CODE_GEN/GHAC_ctrl_swingUp/energy swing up/energy maintenance/Pend energy'

#endif                                 // RTW_HEADER_GHAC_ctrl_swingUp_h_

//
// File trailer for generated code.
//
// [EOF]
//
