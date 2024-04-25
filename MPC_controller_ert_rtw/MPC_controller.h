//
// File: MPC_controller.h
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
#ifndef RTW_HEADER_MPC_controller_h_
#define RTW_HEADER_MPC_controller_h_
#include <stdio.h>
#include <string.h>
#include "rtwtypes.h"
#include <stddef.h>

// Macros for accessing real-time model data structure
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

// Custom Type definition for MATLAB Function: '<S2>/NLMPC'
#ifndef struct_sG8JZ69axY52WWR6RKyApQC
#define struct_sG8JZ69axY52WWR6RKyApQC

struct sG8JZ69axY52WWR6RKyApQC
{
  real_T penaltyParam;
  real_T threshold;
  int32_T nPenaltyDecreases;
  real_T linearizedConstrViol;
  real_T initFval;
  real_T initConstrViolationEq;
  real_T initConstrViolationIneq;
  real_T phi;
  real_T phiPrimePlus;
  real_T phiFullStep;
  real_T feasRelativeFactor;
  real_T nlpPrimalFeasError;
  real_T nlpDualFeasError;
  real_T nlpComplError;
  real_T firstOrderOpt;
  boolean_T hasObjective;
};

#endif                                 // struct_sG8JZ69axY52WWR6RKyApQC

#ifndef struct_s7RdrPWkr8UPAUyTdDJkLaG
#define struct_s7RdrPWkr8UPAUyTdDJkLaG

struct s7RdrPWkr8UPAUyTdDJkLaG
{
  boolean_T gradOK;
  boolean_T fevalOK;
  boolean_T done;
  boolean_T stepAccepted;
  boolean_T failedLineSearch;
  int32_T stepType;
};

#endif                                 // struct_s7RdrPWkr8UPAUyTdDJkLaG

#ifndef struct_somzaGboVhDG7PNQS6E98jD
#define struct_somzaGboVhDG7PNQS6E98jD

struct somzaGboVhDG7PNQS6E98jD
{
  char_T SolverName[7];
  int32_T MaxIterations;
  real_T StepTolerance;
  real_T OptimalityTolerance;
  real_T ConstraintTolerance;
  real_T ObjectiveLimit;
  real_T PricingTolerance;
  real_T ConstrRelTolFactor;
  real_T ProbRelTolFactor;
  boolean_T RemainFeasible;
  boolean_T IterDisplayQP;
};

#endif                                 // struct_somzaGboVhDG7PNQS6E98jD

#ifndef struct_emxArray_real_T_247x80
#define struct_emxArray_real_T_247x80

struct emxArray_real_T_247x80
{
  real_T data[19760];
  int32_T size[2];
};

#endif                                 // struct_emxArray_real_T_247x80

#ifndef struct_emxArray_real_T_247x40
#define struct_emxArray_real_T_247x40

struct emxArray_real_T_247x40
{
  real_T data[9880];
  int32_T size[2];
};

#endif                                 // struct_emxArray_real_T_247x40

#ifndef struct_emxArray_real_T_453x247
#define struct_emxArray_real_T_453x247

struct emxArray_real_T_453x247
{
  real_T data[111891];
  int32_T size[2];
};

#endif                                 // struct_emxArray_real_T_453x247

#ifndef struct_emxArray_real_T_453x453
#define struct_emxArray_real_T_453x453

struct emxArray_real_T_453x453
{
  real_T data[205209];
  int32_T size[2];
};

#endif                                 // struct_emxArray_real_T_453x453

// Custom Type definition for MATLAB Function: '<S2>/NLMPC'
#ifndef struct_s_U0bKKPZx63yLz5SynYPvR
#define struct_s_U0bKKPZx63yLz5SynYPvR

struct s_U0bKKPZx63yLz5SynYPvR
{
  emxArray_real_T_453x453 FMat;
  int32_T ldm;
  int32_T ndims;
  int32_T info;
  real_T scaleFactor;
  boolean_T ConvexCheck;
  real_T regTol_;
  real_T workspace_;
  real_T workspace2_;
};

#endif                                 // struct_s_U0bKKPZx63yLz5SynYPvR

#ifndef struct_sXyXDxkiKhsfpX9ivkpx9WG
#define struct_sXyXDxkiKhsfpX9ivkpx9WG

struct sXyXDxkiKhsfpX9ivkpx9WG
{
  real_T Ts;
  real_T CurrentStates[4];
  real_T LastMV;
  real_T References[40];
  real_T MVTarget[10];
  real_T PredictionHorizon;
  real_T NumOfStates;
  real_T NumOfOutputs;
  real_T NumOfInputs;
  real_T MVIndex;
  real_T InputPassivityIndex;
  real_T OutputPassivityIndex;
  boolean_T PassivityUsePredictedX;
};

#endif                                 // struct_sXyXDxkiKhsfpX9ivkpx9WG

#ifndef struct_s_GSKgPzH92oA7AAcXEvWMnG
#define struct_s_GSKgPzH92oA7AAcXEvWMnG

struct s_GSKgPzH92oA7AAcXEvWMnG
{
  real_T x[4];
  real_T lastMV;
  real_T ref[40];
  real_T OutputWeights[40];
  real_T MVWeights[10];
  real_T MVRateWeights[10];
  real_T ECRWeight;
  real_T OutputMin[40];
  real_T OutputMax[40];
  real_T StateMin[40];
  real_T StateMax[40];
  real_T MVMin[10];
  real_T MVMax[10];
  real_T MVRateMin[10];
  real_T MVRateMax[10];
  real_T MVScaledTarget[10];
};

#endif                                 // struct_s_GSKgPzH92oA7AAcXEvWMnG

#ifndef struct_s_OOgWGXXQYnSElkPXvuQxeH
#define struct_s_OOgWGXXQYnSElkPXvuQxeH

struct s_OOgWGXXQYnSElkPXvuQxeH
{
  s_GSKgPzH92oA7AAcXEvWMnG runtimedata;
  sXyXDxkiKhsfpX9ivkpx9WG userdata;
};

#endif                                 // struct_s_OOgWGXXQYnSElkPXvuQxeH

#ifndef struct_anonymous_function
#define struct_anonymous_function

struct anonymous_function
{
  s_OOgWGXXQYnSElkPXvuQxeH workspace;
};

#endif                                 // struct_anonymous_function

#ifndef struct_coder_internal_stickyStruct_1
#define struct_coder_internal_stickyStruct_1

struct coder_internal_stickyStruct_1
{
  anonymous_function value;
};

#endif                                 // struct_coder_internal_stickyStruct_1

#ifndef struct_coder_internal_stickyStruct_2
#define struct_coder_internal_stickyStruct_2

struct coder_internal_stickyStruct_2
{
  anonymous_function value;
  coder_internal_stickyStruct_1 next;
};

#endif                                 // struct_coder_internal_stickyStruct_2

#ifndef struct_coder_internal_stickyStruct_3
#define struct_coder_internal_stickyStruct_3

struct coder_internal_stickyStruct_3
{
  coder_internal_stickyStruct_2 next;
};

#endif                                 // struct_coder_internal_stickyStruct_3

#ifndef struct_coder_internal_stickyStruct_4
#define struct_coder_internal_stickyStruct_4

struct coder_internal_stickyStruct_4
{
  int32_T value;
  coder_internal_stickyStruct_3 next;
};

#endif                                 // struct_coder_internal_stickyStruct_4

#ifndef struct_coder_internal_stickyStruct_5
#define struct_coder_internal_stickyStruct_5

struct coder_internal_stickyStruct_5
{
  coder_internal_stickyStruct_4 next;
};

#endif                                 // struct_coder_internal_stickyStruct_5

#ifndef struct_coder_internal_stickyStruct_6
#define struct_coder_internal_stickyStruct_6

struct coder_internal_stickyStruct_6
{
  coder_internal_stickyStruct_5 next;
};

#endif                                 // struct_coder_internal_stickyStruct_6

#ifndef struct_coder_internal_stickyStruct_7
#define struct_coder_internal_stickyStruct_7

struct coder_internal_stickyStruct_7
{
  coder_internal_stickyStruct_6 next;
};

#endif                                 // struct_coder_internal_stickyStruct_7

#ifndef struct_coder_internal_stickyStruct_8
#define struct_coder_internal_stickyStruct_8

struct coder_internal_stickyStruct_8
{
  coder_internal_stickyStruct_7 next;
};

#endif                                 // struct_coder_internal_stickyStruct_8

#ifndef struct_coder_internal_stickyStruct_9
#define struct_coder_internal_stickyStruct_9

struct coder_internal_stickyStruct_9
{
  coder_internal_stickyStruct_8 next;
};

#endif                                 // struct_coder_internal_stickyStruct_9

#ifndef struct_emxArray_real_T_120
#define struct_emxArray_real_T_120

struct emxArray_real_T_120
{
  real_T data[120];
  int32_T size;
};

#endif                                 // struct_emxArray_real_T_120

#ifndef struct_emxArray_real_T_247
#define struct_emxArray_real_T_247

struct emxArray_real_T_247
{
  real_T data[247];
  int32_T size;
};

#endif                                 // struct_emxArray_real_T_247

#ifndef struct_emxArray_real_T_453
#define struct_emxArray_real_T_453

struct emxArray_real_T_453
{
  real_T data[453];
  int32_T size;
};

#endif                                 // struct_emxArray_real_T_453

#ifndef struct_emxArray_int32_T_453
#define struct_emxArray_int32_T_453

struct emxArray_int32_T_453
{
  int32_T data[453];
  int32_T size;
};

#endif                                 // struct_emxArray_int32_T_453

// Custom Type definition for MATLAB Function: '<S2>/NLMPC'
#ifndef struct_s_aAq9pdCdNustb4CQC7xpeC
#define struct_s_aAq9pdCdNustb4CQC7xpeC

struct s_aAq9pdCdNustb4CQC7xpeC
{
  int32_T nVarMax;
  int32_T mNonlinIneq;
  int32_T mNonlinEq;
  int32_T mIneq;
  int32_T mEq;
  int32_T iNonIneq0;
  int32_T iNonEq0;
  real_T sqpFval;
  real_T sqpFval_old;
  real_T xstarsqp[46];
  real_T xstarsqp_old[46];
  emxArray_real_T_120 cIneq;
  emxArray_real_T_120 cIneq_old;
  real_T cEq[40];
  real_T cEq_old[40];
  emxArray_real_T_247 grad;
  emxArray_real_T_247 grad_old;
  int32_T FunctionEvaluations;
  int32_T sqpIterations;
  int32_T sqpExitFlag;
  emxArray_real_T_453 lambdasqp;
  emxArray_real_T_453 lambdaStopTest;
  emxArray_real_T_453 lambdaStopTestPrev;
  real_T steplength;
  emxArray_real_T_247 delta_x;
  emxArray_real_T_247 socDirection;
  emxArray_int32_T_453 workingset_old;
  emxArray_real_T_247x80 JacCineqTrans_old;
  emxArray_real_T_247x40 JacCeqTrans_old;
  emxArray_real_T_247 gradLag;
  emxArray_real_T_247 delta_gradLag;
  emxArray_real_T_247 xstar;
  real_T fstar;
  real_T firstorderopt;
  emxArray_real_T_453 lambda;
  int32_T state;
  real_T maxConstr;
  int32_T iterations;
  emxArray_real_T_247 searchDir;
};

#endif                                 // struct_s_aAq9pdCdNustb4CQC7xpeC

#ifndef struct_s_AiLncvKJfAMbGh9HSVCzlG
#define struct_s_AiLncvKJfAMbGh9HSVCzlG

struct s_AiLncvKJfAMbGh9HSVCzlG
{
  emxArray_real_T_453x247 workspace_double;
  emxArray_int32_T_453 workspace_int;
  emxArray_int32_T_453 workspace_sort;
};

#endif                                 // struct_s_AiLncvKJfAMbGh9HSVCzlG

#ifndef struct_emxArray_real_T_29640
#define struct_emxArray_real_T_29640

struct emxArray_real_T_29640
{
  real_T data[29640];
  int32_T size;
};

#endif                                 // struct_emxArray_real_T_29640

#ifndef struct_emxArray_real_T_9880
#define struct_emxArray_real_T_9880

struct emxArray_real_T_9880
{
  real_T data[9880];
  int32_T size;
};

#endif                                 // struct_emxArray_real_T_9880

#ifndef struct_emxArray_int32_T_247
#define struct_emxArray_int32_T_247

struct emxArray_int32_T_247
{
  int32_T data[247];
  int32_T size;
};

#endif                                 // struct_emxArray_int32_T_247

#ifndef struct_emxArray_real_T_111891
#define struct_emxArray_real_T_111891

struct emxArray_real_T_111891
{
  real_T data[111891];
  int32_T size;
};

#endif                                 // struct_emxArray_real_T_111891

#ifndef struct_emxArray_boolean_T_453
#define struct_emxArray_boolean_T_453

struct emxArray_boolean_T_453
{
  boolean_T data[453];
  int32_T size;
};

#endif                                 // struct_emxArray_boolean_T_453

// Custom Type definition for MATLAB Function: '<S2>/NLMPC'
#ifndef struct_s_YG0fmBFfsyHj5FdUrtbgBC
#define struct_s_YG0fmBFfsyHj5FdUrtbgBC

struct s_YG0fmBFfsyHj5FdUrtbgBC
{
  int32_T mConstr;
  int32_T mConstrOrig;
  int32_T mConstrMax;
  int32_T nVar;
  int32_T nVarOrig;
  int32_T nVarMax;
  int32_T ldA;
  emxArray_real_T_29640 Aineq;
  emxArray_real_T_120 bineq;
  emxArray_real_T_9880 Aeq;
  real_T beq[40];
  emxArray_real_T_247 lb;
  emxArray_real_T_247 ub;
  emxArray_int32_T_247 indexLB;
  emxArray_int32_T_247 indexUB;
  emxArray_int32_T_247 indexFixed;
  int32_T mEqRemoved;
  int32_T indexEqRemoved[40];
  emxArray_real_T_111891 ATwset;
  emxArray_real_T_453 bwset;
  int32_T nActiveConstr;
  emxArray_real_T_453 maxConstrWorkspace;
  int32_T sizes[5];
  int32_T sizesNormal[5];
  int32_T sizesPhaseOne[5];
  int32_T sizesRegularized[5];
  int32_T sizesRegPhaseOne[5];
  int32_T isActiveIdx[6];
  int32_T isActiveIdxNormal[6];
  int32_T isActiveIdxPhaseOne[6];
  int32_T isActiveIdxRegularized[6];
  int32_T isActiveIdxRegPhaseOne[6];
  emxArray_boolean_T_453 isActiveConstr;
  emxArray_int32_T_453 Wid;
  emxArray_int32_T_453 Wlocalidx;
  int32_T nWConstr[5];
  int32_T probType;
  real_T SLACK0;
};

#endif                                 // struct_s_YG0fmBFfsyHj5FdUrtbgBC

#ifndef struct_emxArray_real_T_246
#define struct_emxArray_real_T_246

struct emxArray_real_T_246
{
  real_T data[246];
  int32_T size;
};

#endif                                 // struct_emxArray_real_T_246

// Custom Type definition for MATLAB Function: '<S2>/NLMPC'
#ifndef struct_s_4B8jbk60U8ZWFI1LxShFzC
#define struct_s_4B8jbk60U8ZWFI1LxShFzC

struct s_4B8jbk60U8ZWFI1LxShFzC
{
  emxArray_real_T_247 grad;
  emxArray_real_T_246 Hx;
  boolean_T hasLinear;
  int32_T nvar;
  int32_T maxVar;
  real_T beta;
  real_T rho;
  int32_T objtype;
  int32_T prev_objtype;
  int32_T prev_nvar;
  boolean_T prev_hasLinear;
  real_T gammaScalar;
};

#endif                                 // struct_s_4B8jbk60U8ZWFI1LxShFzC

#ifndef struct_s_LP9wk1co4RSPM0xk4tXznB
#define struct_s_LP9wk1co4RSPM0xk4tXznB

struct s_LP9wk1co4RSPM0xk4tXznB
{
  int32_T ldq;
  emxArray_real_T_453x453 QR;
  emxArray_real_T_453x453 Q;
  emxArray_int32_T_453 jpvt;
  int32_T mrows;
  int32_T ncols;
  emxArray_real_T_453 tau;
  int32_T minRowCol;
  boolean_T usedPivoting;
};

#endif                                 // struct_s_LP9wk1co4RSPM0xk4tXznB

#ifndef struct_emxArray_real_T_80
#define struct_emxArray_real_T_80

struct emxArray_real_T_80
{
  real_T data[80];
  int32_T size;
};

#endif                                 // struct_emxArray_real_T_80

// Custom Type definition for MATLAB Function: '<S2>/NLMPC'
#ifndef struct_s_hNyiAhpzUrzCIC7G3ZO0E
#define struct_s_hNyiAhpzUrzCIC7G3ZO0E

struct s_hNyiAhpzUrzCIC7G3ZO0E
{
  anonymous_function objfun;
  anonymous_function nonlin;
  real_T f_1;
  emxArray_real_T_80 cIneq_1;
  real_T cEq_1[40];
  real_T f_2;
  emxArray_real_T_80 cIneq_2;
  real_T cEq_2[40];
  int32_T nVar;
  int32_T mIneq;
  int32_T mEq;
  int32_T numEvals;
  boolean_T SpecifyObjectiveGradient;
  boolean_T SpecifyConstraintGradient;
  boolean_T isEmptyNonlcon;
  boolean_T hasLB[46];
  boolean_T hasUB[46];
  boolean_T hasBounds;
  int32_T FiniteDifferenceType;
};

#endif                                 // struct_s_hNyiAhpzUrzCIC7G3ZO0E

extern "C"
{
  static real_T rtGetInf(void);
  static real32_T rtGetInfF(void);
  static real_T rtGetMinusInf(void);
  static real32_T rtGetMinusInfF(void);
}                                      // extern "C"

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

// Class declaration for model MPC_controller
class MPC_controller final
{
  // public data and function members
 public:
  // Block signals and states (default storage) for system '<Root>'
  struct DW {
    s_LP9wk1co4RSPM0xk4tXznB QRManager;
    s_U0bKKPZx63yLz5SynYPvR CholManager;
    s_YG0fmBFfsyHj5FdUrtbgBC WorkingSet;
    s_YG0fmBFfsyHj5FdUrtbgBC b_WorkingSet;
    s_YG0fmBFfsyHj5FdUrtbgBC c_WorkingSet;
    s_AiLncvKJfAMbGh9HSVCzlG memspace;
    s_aAq9pdCdNustb4CQC7xpeC TrialState;
    coder_internal_stickyStruct_9 FcnEvaluator;
    real_T x_Delay_DSTATE[44];         // '<S3>/x_Delay'
    real_T mv_Delay_DSTATE[11];        // '<S3>/mv_Delay'
    real_T A_data[2040];
    real_T JacCineqTrans_data[3680];
    real_T JacCeqTrans[1840];
    real_T unusedExpr[2116];
    real_T b_varargin_1_data[3680];
    real_T Jx[1600];
    real_T b_Jx[3200];
    real_T b_Jx_data[3200];
    real_T tmp_data[800];
    real_T a__4_data[3680];
    real_T JacEqTrans_tmp[1840];
    real_T y_data[205209];
    real_T B_data[111891];
    real_T varargin_1_data[6400];
    real_T UnitDelay_DSTATE;           // '<Root>/Unit Delay'
    real_T slack_delay_DSTATE;         // '<S3>/slack_delay'
    boolean_T icLoad;                  // '<S3>/x_Delay'
    boolean_T icLoad_e;                // '<S3>/mv_Delay'
    boolean_T icLoad_m;                // '<S3>/slack_delay'
  };

  // Constant parameters (default storage)
  struct ConstP {
    // Expression: min(3,PredictionHorizon+1):(PredictionHorizon+1)
    //  Referenced by: '<S3>/Constant'

    real_T Constant_Value[9];

    // Expression: 2:max(2,PredictionHorizon)
    //  Referenced by: '<S3>/Constant1'

    real_T Constant1_Value[9];
  };

  // External inputs (root inport signals with default storage)
  struct ExtU {
    real_T x[4];                       // '<Root>/x'
    real_T ref[4];                     // '<Root>/ref'
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
  MPC_controller(MPC_controller const&) = delete;

  // Assignment Operator
  MPC_controller& operator= (MPC_controller const&) & = delete;

  // Move Constructor
  MPC_controller(MPC_controller &&) = delete;

  // Move Assignment Operator
  MPC_controller& operator= (MPC_controller &&) = delete;

  // Real-Time Model get method
  MPC_controller::RT_MODEL * getRTM();

  // External inputs
  ExtU rtU;

  // External outputs
  ExtY rtY;

  // model initialize function
  void initialize();

  // model step function
  void step();

  // Constructor
  MPC_controller();

  // Destructor
  ~MPC_controller();

  // private data and function members
 private:
  // Block states
  DW rtDW;

  // private member function(s) for subsystem '<Root>'
  void mtimes(const real_T A_data[], const int32_T A_size[2], real_T C_data[],
              int32_T C_size[2]);
  void znlmpc_getXUe(const real_T z[46], const real_T x[4], real_T X_1[44],
                     real_T U[11], real_T *e);
  void all(const boolean_T x[40], boolean_T y[4]);
  boolean_T any(const boolean_T x[8]);
  void eML_blk_kernel_anonFcn2(const real_T runtimedata_x[4], const real_T
    runtimedata_OutputMin[40], const real_T runtimedata_OutputMax[40], const
    real_T z[46], real_T varargout_1_data[], int32_T varargout_1_size[2], real_T
    varargout_2[40], real_T varargout_3_data[], int32_T varargout_3_size[2],
    real_T varargout_4[1840]);
  void factoryConstruct(int32_T nVarMax, int32_T mConstrMax, int32_T mIneq,
                        int32_T mNonlinIneq, s_aAq9pdCdNustb4CQC7xpeC *obj);
  void factoryConstruct_h53b(int32_T MaxVars, int32_T *obj_grad_size, int32_T
    *obj_Hx_size, boolean_T *obj_hasLinear, int32_T *obj_nvar, int32_T
    *obj_maxVar, real_T *obj_beta, real_T *obj_rho, int32_T *obj_objtype,
    int32_T *obj_prev_objtype, int32_T *obj_prev_nvar, boolean_T
    *obj_prev_hasLinear, real_T *obj_gammaScalar);
  void factoryConstruct_h53bm(int32_T mIneqMax, int32_T nVarMax, int32_T
    mConstrMax, s_YG0fmBFfsyHj5FdUrtbgBC *obj);
  int32_T checkVectorNonFinite(int32_T N, const real_T vec_data[], int32_T iv0);
  int32_T checkVectorNonFinite_n(const real_T vec[40]);
  void evalObjAndConstrAndDerivatives(int32_T obj_next_next_next_next_next_va,
    const s_GSKgPzH92oA7AAcXEvWMnG *obj_next_next_next_next_next_ne, const
    s_OOgWGXXQYnSElkPXvuQxeH *obj_next_next_next_next_next__0, const real_T x[46],
    real_T grad_workspace_data[], real_T Cineq_workspace_data[], int32_T ineq0,
    real_T Ceq_workspace[40], real_T JacIneqTrans_workspace_data[], int32_T
    iJI_col, int32_T ldJI, real_T JacEqTrans_workspace_data[], int32_T ldJE,
    real_T *fval, int32_T *status);
  void modifyOverheadPhaseOne_(s_YG0fmBFfsyHj5FdUrtbgBC *obj);
  void setProblemType(s_YG0fmBFfsyHj5FdUrtbgBC *obj, int32_T PROBLEM_TYPE);
  void initActiveSet(s_YG0fmBFfsyHj5FdUrtbgBC *obj);
  void factoryConstruct_h5(int32_T maxRows, int32_T maxCols, int32_T *obj_ldq,
    int32_T obj_QR_size[2], real_T obj_Q_data[], int32_T obj_Q_size[2], int32_T
    obj_jpvt_data[], int32_T *obj_jpvt_size, int32_T *obj_mrows, int32_T
    *obj_ncols, int32_T *obj_tau_size, int32_T *obj_minRowCol, boolean_T
    *obj_usedPivoting);
  void factoryConstruct_h53(int32_T MaxDims, int32_T obj_FMat_size[2], int32_T
    *obj_ldm, int32_T *obj_ndims, int32_T *obj_info, real_T *obj_scaleFactor,
    boolean_T *obj_ConvexCheck, real_T *obj_regTol_, real_T *obj_workspace_,
    real_T *obj_workspace2_);
  void computeGradLag(real_T workspace_data[], int32_T ldA, int32_T nVar, const
                      real_T grad_data[], int32_T mIneq, const real_T
                      AineqTrans_data[], const real_T AeqTrans_data[], const
                      int32_T finiteFixed_data[], int32_T mFixed, const int32_T
                      finiteLB_data[], int32_T mLB, const int32_T finiteUB_data[],
                      int32_T mUB, const real_T lambda_data[]);
  real_T computePrimalFeasError(const real_T x[46], int32_T mLinIneq, int32_T
    mNonlinIneq, const real_T cIneq_data[], const real_T cEq[40], const int32_T
    finiteLB_data[], int32_T mLB, const real_T lb[46], const int32_T
    finiteUB_data[], int32_T mUB);
  void computeDualFeasError(int32_T nVar, const real_T gradLag_data[], boolean_T
    *gradOK, real_T *val);
  void saveJacobian(s_aAq9pdCdNustb4CQC7xpeC *obj, int32_T nVar, int32_T mIneq,
                    const real_T JacCineqTrans_data[], int32_T ineqCol0, const
                    real_T JacCeqTrans_data[], int32_T ldJ);
  real_T computeComplError(const int32_T *fscales_lineq_constraint_size, const
    int32_T *fscales_cineq_constraint_size, const real_T xCurrent[46], int32_T
    mIneq, const real_T cIneq_data[], const int32_T finiteLB_data[], int32_T mLB,
    const real_T lb[46], const int32_T finiteUB_data[], int32_T mUB, const
    real_T lambda_data[], int32_T iL0);
  void computeGradLag_e(real_T workspace_data[], int32_T ldA, int32_T nVar,
                        const real_T grad_data[], int32_T mIneq, const real_T
                        AineqTrans_data[], const real_T AeqTrans_data[], const
                        int32_T finiteFixed_data[], int32_T mFixed, const
                        int32_T finiteLB_data[], int32_T mLB, const int32_T
                        finiteUB_data[], int32_T mUB, const real_T lambda_data[]);
  void computeDualFeasError_k(int32_T nVar, const real_T gradLag_data[],
    boolean_T *gradOK, real_T *val);
  void updateWorkingSetForNewQP(const real_T xk[46], s_YG0fmBFfsyHj5FdUrtbgBC
    *WorkingSet, int32_T mIneq, int32_T mNonlinIneq, const real_T cIneq_data[],
    const real_T cEq[40], int32_T mLB, const real_T lb[46], int32_T mUB, int32_T
    mFixed);
  void xswap(int32_T n, real_T x_data[], int32_T ix0, int32_T iy0);
  real_T xnrm2(int32_T n, const real_T x_data[], int32_T ix0);
  real_T xzlarfg(int32_T n, real_T *alpha1, real_T x_data[], int32_T ix0);
  void xgemv(int32_T m, int32_T n, const real_T A_data[], int32_T ia0, int32_T
             lda, const real_T x_data[], int32_T ix0, real_T y_data[]);
  void xgerc(int32_T m, int32_T n, real_T alpha1, int32_T ix0, const real_T
             y_data[], real_T A_data[], int32_T ia0, int32_T lda);
  void xzlarf(int32_T m, int32_T n, int32_T iv0, real_T tau, real_T C_data[],
              int32_T ic0, int32_T ldc, real_T work_data[]);
  void qrf(real_T A_data[], const int32_T A_size[2], int32_T m, int32_T n,
           int32_T nfxd, real_T tau_data[]);
  void qrpf(real_T A_data[], const int32_T A_size[2], int32_T m, int32_T n,
            int32_T nfxd, real_T tau_data[], int32_T jpvt_data[]);
  void xgeqp3(real_T A_data[], const int32_T A_size[2], int32_T m, int32_T n,
              int32_T jpvt_data[], real_T tau_data[], int32_T *tau_size);
  void factorQRE(s_LP9wk1co4RSPM0xk4tXznB *obj, const real_T A_data[], int32_T
                 mrows, int32_T ncols, int32_T ldA);
  void xorgqr(int32_T m, int32_T n, int32_T k, real_T A_data[], const int32_T
              A_size[2], int32_T lda, const real_T tau_data[]);
  void xgemv_d(int32_T m, int32_T n, const real_T A_data[], int32_T lda, const
               real_T x_data[], real_T y_data[]);
  void sortLambdaQP(real_T lambda_data[], int32_T WorkingSet_nActiveConstr,
                    const int32_T WorkingSet_sizes[5], const int32_T
                    WorkingSet_isActiveIdx[6], const int32_T
                    WorkingSet_Wid_data[], const int32_T
                    WorkingSet_Wlocalidx_data[], real_T workspace_data[]);
  void test_exit(s7RdrPWkr8UPAUyTdDJkLaG *Flags, s_AiLncvKJfAMbGh9HSVCzlG
                 *memspace, sG8JZ69axY52WWR6RKyApQC *MeritFunction, const
                 int32_T *fscales_lineq_constraint_size, const int32_T
                 *fscales_cineq_constraint_size, s_YG0fmBFfsyHj5FdUrtbgBC
                 *WorkingSet, s_aAq9pdCdNustb4CQC7xpeC *TrialState,
                 s_LP9wk1co4RSPM0xk4tXznB *QRManager, const real_T lb[46]);
  boolean_T BFGSUpdate(int32_T nvar, real_T Bk[2116], const real_T sk_data[],
                       real_T yk_data[], real_T workspace_data[]);
  void factorQRE_o(s_LP9wk1co4RSPM0xk4tXznB *obj, int32_T mrows, int32_T ncols);
  void countsort(int32_T x_data[], int32_T xLen, int32_T workspace_data[],
                 int32_T xMin, int32_T xMax);
  void removeConstr(s_YG0fmBFfsyHj5FdUrtbgBC *obj, int32_T idx_global);
  int32_T RemoveDependentEq_(s_AiLncvKJfAMbGh9HSVCzlG *memspace,
    s_YG0fmBFfsyHj5FdUrtbgBC *workingset, s_LP9wk1co4RSPM0xk4tXznB *qrmanager);
  void RemoveDependentIneq_(s_YG0fmBFfsyHj5FdUrtbgBC *workingset,
    s_LP9wk1co4RSPM0xk4tXznB *qrmanager, s_AiLncvKJfAMbGh9HSVCzlG *memspace);
  void xgeqrf(real_T A_data[], const int32_T A_size[2], int32_T m, int32_T n,
              real_T tau_data[], int32_T *tau_size);
  void factorQR_p(s_LP9wk1co4RSPM0xk4tXznB *obj, const real_T A_data[], int32_T
                  mrows, int32_T ncols, int32_T ldA);
  void factorQR(s_LP9wk1co4RSPM0xk4tXznB *obj, int32_T mrows, int32_T ncols);
  void xgemv_dff(int32_T m, int32_T n, const real_T A_data[], int32_T lda, const
                 real_T x_data[], real_T y_data[]);
  void xgemv_df(int32_T n, const real_T A_data[], int32_T lda, const real_T
                x_data[], real_T y_data[]);
  real_T maxConstraintViolation(s_YG0fmBFfsyHj5FdUrtbgBC *obj, const real_T
    x_data[]);
  void xgemv_dffo(int32_T m, int32_T n, const real_T A_data[], int32_T lda,
                  const real_T x_data[], int32_T ix0, real_T y_data[]);
  real_T maxConstraintViolation_i(s_YG0fmBFfsyHj5FdUrtbgBC *obj, const real_T
    x_data[], int32_T ix0);
  boolean_T feasibleX0ForWorkingSet(real_T workspace_data[], const int32_T
    workspace_size[2], real_T xCurrent_data[], s_YG0fmBFfsyHj5FdUrtbgBC
    *workingset, s_LP9wk1co4RSPM0xk4tXznB *qrmanager);
  void RemoveDependentIneq__b(s_YG0fmBFfsyHj5FdUrtbgBC *workingset,
    s_LP9wk1co4RSPM0xk4tXznB *qrmanager, s_AiLncvKJfAMbGh9HSVCzlG *memspace);
  void xgemv_dffoyl(int32_T m, int32_T n, const real_T A_data[], int32_T lda,
                    const real_T x_data[], real_T y_data[]);
  void xgemv_dffoy(int32_T n, const real_T A_data[], int32_T lda, const real_T
                   x_data[], real_T y_data[]);
  real_T maxConstraintViolation_in(s_YG0fmBFfsyHj5FdUrtbgBC *obj, const real_T
    x_data[]);
  void PresolveWorkingSet(s_aAq9pdCdNustb4CQC7xpeC *solution,
    s_AiLncvKJfAMbGh9HSVCzlG *memspace, s_YG0fmBFfsyHj5FdUrtbgBC *workingset,
    s_LP9wk1co4RSPM0xk4tXznB *qrmanager);
  void xgemv_dffoyl1(int32_T m, int32_T n, const real_T A[2116], int32_T lda,
                     const real_T x_data[], real_T y_data[]);
  void computeGrad_StoreHx(s_4B8jbk60U8ZWFI1LxShFzC *obj, const real_T H[2116],
    const real_T f_data[], const real_T x_data[]);
  real_T computeFval_ReuseHx(const s_4B8jbk60U8ZWFI1LxShFzC *obj, real_T
    workspace_data[], const real_T f_data[], const real_T x_data[]);
  void xrotg(real_T *a, real_T *b, real_T *c, real_T *s);
  void deleteColMoveEnd(s_LP9wk1co4RSPM0xk4tXznB *obj, int32_T idx);
  boolean_T strcmp_c(const char_T a[7]);
  void xgemm(int32_T m, int32_T n, int32_T k, const real_T A[2116], int32_T lda,
             const real_T B_data[], int32_T ib0, int32_T ldb, real_T C_data[],
             int32_T ldc);
  void xgemm_k(int32_T m, int32_T n, int32_T k, const real_T A_data[], int32_T
               ia0, int32_T lda, const real_T B_data[], int32_T ldb, real_T
               C_data[], int32_T ldc);
  void fullColLDL2_(s_U0bKKPZx63yLz5SynYPvR *obj, int32_T LD_offset, int32_T
                    NColsRemain);
  void partialColLDL3_(s_U0bKKPZx63yLz5SynYPvR *obj, int32_T LD_offset, int32_T
                       NColsRemain);
  int32_T xpotrf(int32_T n, real_T A_data[], int32_T lda);
  void xgemv_dffoyl1j(int32_T m, int32_T n, const real_T A_data[], int32_T ia0,
                      int32_T lda, const real_T x_data[], real_T y_data[]);
  void factor(s_U0bKKPZx63yLz5SynYPvR *obj, const real_T A[2116], int32_T ndims,
              int32_T ldA);
  void solve(const s_U0bKKPZx63yLz5SynYPvR *obj, real_T rhs_data[]);
  void factor_g(s_U0bKKPZx63yLz5SynYPvR *obj, const real_T A[2116], int32_T
                ndims, int32_T ldA);
  void solve_i(const s_U0bKKPZx63yLz5SynYPvR *obj, real_T rhs_data[]);
  void compute_deltax(const real_T H[2116], s_aAq9pdCdNustb4CQC7xpeC *solution,
                      s_AiLncvKJfAMbGh9HSVCzlG *memspace, const
                      s_LP9wk1co4RSPM0xk4tXznB *qrmanager,
                      s_U0bKKPZx63yLz5SynYPvR *cholmanager, const
                      s_4B8jbk60U8ZWFI1LxShFzC *objective, boolean_T
                      alwaysPositiveDef);
  real_T xnrm2_n(int32_T n, const real_T x_data[]);
  void xgemv_dffoyl1jt(int32_T m, int32_T n, const real_T A_data[], int32_T lda,
                       const real_T x_data[], real_T y_data[]);
  void feasibleratiotest(const real_T solution_xstar_data[], const real_T
    solution_searchDir_data[], real_T workspace_data[], const int32_T
    workspace_size[2], int32_T workingset_nVar, int32_T workingset_ldA, const
    real_T workingset_Aineq_data[], const real_T workingset_bineq_data[], const
    real_T workingset_lb_data[], const int32_T workingset_indexLB_data[], const
    int32_T workingset_sizes[5], const int32_T workingset_isActiveIdx[6], const
    boolean_T workingset_isActiveConstr_data[], const int32_T
    workingset_nWConstr[5], boolean_T isPhaseOne, real_T *alpha, boolean_T
    *newBlocking, int32_T *constrType, int32_T *constrIdx);
  void checkUnboundedOrIllPosed(s_aAq9pdCdNustb4CQC7xpeC *solution, const
    s_4B8jbk60U8ZWFI1LxShFzC *objective);
  void addBoundToActiveSetMatrix_(s_YG0fmBFfsyHj5FdUrtbgBC *obj, int32_T TYPE,
    int32_T idx_local);
  void addAineqConstr(s_YG0fmBFfsyHj5FdUrtbgBC *obj, int32_T idx_local);
  void checkStoppingAndUpdateFval(int32_T *activeSetChangeID, const real_T
    f_data[], s_aAq9pdCdNustb4CQC7xpeC *solution, s_AiLncvKJfAMbGh9HSVCzlG
    *memspace, const s_4B8jbk60U8ZWFI1LxShFzC *objective,
    s_YG0fmBFfsyHj5FdUrtbgBC *workingset, s_LP9wk1co4RSPM0xk4tXznB *qrmanager,
    real_T options_ObjectiveLimit, int32_T runTimeOptions_MaxIterations,
    boolean_T updateFval);
  void iterate(const real_T H[2116], const real_T f_data[],
               s_aAq9pdCdNustb4CQC7xpeC *solution, s_AiLncvKJfAMbGh9HSVCzlG
               *memspace, s_YG0fmBFfsyHj5FdUrtbgBC *workingset,
               s_LP9wk1co4RSPM0xk4tXznB *qrmanager, s_U0bKKPZx63yLz5SynYPvR
               *cholmanager, s_4B8jbk60U8ZWFI1LxShFzC *objective, const char_T
               options_SolverName[7], real_T options_StepTolerance, real_T
               options_ObjectiveLimit, int32_T runTimeOptions_MaxIterations);
  void linearForm_(boolean_T obj_hasLinear, int32_T obj_nvar, real_T
                   workspace_data[], const real_T H[2116], const real_T f_data[],
                   const real_T x_data[]);
  real_T computeFval(const s_4B8jbk60U8ZWFI1LxShFzC *obj, real_T workspace_data[],
                     const real_T H[2116], const real_T f_data[], const real_T
                     x_data[]);
  void phaseone(const real_T H[2116], const real_T f_data[],
                s_aAq9pdCdNustb4CQC7xpeC *solution, s_AiLncvKJfAMbGh9HSVCzlG
                *memspace, s_YG0fmBFfsyHj5FdUrtbgBC *workingset,
                s_LP9wk1co4RSPM0xk4tXznB *qrmanager, s_U0bKKPZx63yLz5SynYPvR
                *cholmanager, s_4B8jbk60U8ZWFI1LxShFzC *objective,
                somzaGboVhDG7PNQS6E98jD *options, const somzaGboVhDG7PNQS6E98jD *
                runTimeOptions);
  void driver_o(const real_T H[2116], const real_T f_data[],
                s_aAq9pdCdNustb4CQC7xpeC *solution, s_AiLncvKJfAMbGh9HSVCzlG
                *memspace, s_YG0fmBFfsyHj5FdUrtbgBC *workingset,
                s_LP9wk1co4RSPM0xk4tXznB *qrmanager, s_U0bKKPZx63yLz5SynYPvR
                *cholmanager, s_4B8jbk60U8ZWFI1LxShFzC *objective,
                somzaGboVhDG7PNQS6E98jD *options, somzaGboVhDG7PNQS6E98jD
                *runTimeOptions);
  void addAeqConstr(s_YG0fmBFfsyHj5FdUrtbgBC *obj, int32_T idx_local);
  boolean_T soc(const real_T Hessian[2116], const real_T grad_data[],
                s_aAq9pdCdNustb4CQC7xpeC *TrialState, s_AiLncvKJfAMbGh9HSVCzlG
                *memspace, s_YG0fmBFfsyHj5FdUrtbgBC *WorkingSet,
                s_LP9wk1co4RSPM0xk4tXznB *QRManager, s_U0bKKPZx63yLz5SynYPvR
                *CholManager, s_4B8jbk60U8ZWFI1LxShFzC *QPObjective, const
                somzaGboVhDG7PNQS6E98jD *qpoptions);
  void normal(const real_T Hessian[2116], const real_T grad_data[],
              s_aAq9pdCdNustb4CQC7xpeC *TrialState, sG8JZ69axY52WWR6RKyApQC
              *MeritFunction, s_AiLncvKJfAMbGh9HSVCzlG *memspace,
              s_YG0fmBFfsyHj5FdUrtbgBC *WorkingSet, s_LP9wk1co4RSPM0xk4tXznB
              *QRManager, s_U0bKKPZx63yLz5SynYPvR *CholManager,
              s_4B8jbk60U8ZWFI1LxShFzC *QPObjective, const
              somzaGboVhDG7PNQS6E98jD *qpoptions);
  void relaxed(const real_T Hessian[2116], const real_T grad_data[],
               s_aAq9pdCdNustb4CQC7xpeC *TrialState, sG8JZ69axY52WWR6RKyApQC
               *MeritFunction, s_AiLncvKJfAMbGh9HSVCzlG *memspace,
               s_YG0fmBFfsyHj5FdUrtbgBC *WorkingSet, s_LP9wk1co4RSPM0xk4tXznB
               *QRManager, s_U0bKKPZx63yLz5SynYPvR *CholManager,
               s_4B8jbk60U8ZWFI1LxShFzC *QPObjective, somzaGboVhDG7PNQS6E98jD
               *qpoptions);
  boolean_T step_k(int32_T *STEP_TYPE, real_T Hessian[2116], const real_T lb[46],
                   s_aAq9pdCdNustb4CQC7xpeC *TrialState, sG8JZ69axY52WWR6RKyApQC
                   *MeritFunction, s_AiLncvKJfAMbGh9HSVCzlG *memspace,
                   s_YG0fmBFfsyHj5FdUrtbgBC *WorkingSet,
                   s_LP9wk1co4RSPM0xk4tXznB *QRManager, s_U0bKKPZx63yLz5SynYPvR *
                   CholManager, s_4B8jbk60U8ZWFI1LxShFzC *QPObjective,
                   somzaGboVhDG7PNQS6E98jD *qpoptions);
  void evalObjAndConstr(int32_T obj_next_next_next_next_next_va, const
                        s_GSKgPzH92oA7AAcXEvWMnG
                        *obj_next_next_next_next_next_ne, const
                        s_OOgWGXXQYnSElkPXvuQxeH
                        *obj_next_next_next_next_next__0, const real_T x[46],
                        real_T Cineq_workspace_data[], int32_T ineq0, real_T
                        Ceq_workspace[40], real_T *fval, int32_T *status);
  void computeLinearResiduals(const real_T x[46], int32_T nVar, real_T
    workspaceIneq_data[], const int32_T *workspaceIneq_size, int32_T mLinIneq,
    const real_T AineqT_data[], const real_T bineq_data[], int32_T ldAi);
  real_T computeMeritFcn(real_T obj_penaltyParam, real_T fval, const real_T
    Cineq_workspace_data[], int32_T mIneq, const real_T Ceq_workspace[40],
    boolean_T evalWellDefined);
  void linesearch(boolean_T *evalWellDefined, const real_T bineq_data[], int32_T
                  WorkingSet_nVar, int32_T WorkingSet_ldA, const real_T
                  WorkingSet_Aineq_data[], s_aAq9pdCdNustb4CQC7xpeC *TrialState,
                  real_T MeritFunction_penaltyParam, real_T MeritFunction_phi,
                  real_T MeritFunction_phiPrimePlus, real_T
                  MeritFunction_phiFullStep, int32_T
                  FcnEvaluator_next_next_next_nex, const
                  s_GSKgPzH92oA7AAcXEvWMnG *FcnEvaluator_next_next_next_n_0,
                  const s_OOgWGXXQYnSElkPXvuQxeH
                  *FcnEvaluator_next_next_next_n_1, boolean_T socTaken, real_T
                  *alpha, int32_T *exitflag);
  void driver(const real_T bineq_data[], const real_T lb[46],
              s_aAq9pdCdNustb4CQC7xpeC *TrialState, sG8JZ69axY52WWR6RKyApQC
              *MeritFunction, const coder_internal_stickyStruct_9 *FcnEvaluator,
              s_AiLncvKJfAMbGh9HSVCzlG *memspace, s_YG0fmBFfsyHj5FdUrtbgBC
              *WorkingSet, s_LP9wk1co4RSPM0xk4tXznB *QRManager,
              s_U0bKKPZx63yLz5SynYPvR *CholManager, s_4B8jbk60U8ZWFI1LxShFzC
              *QPObjective, const int32_T *fscales_lineq_constraint_size, const
              int32_T *fscales_cineq_constraint_size, real_T Hessian[2116]);
  void fmincon(const s_GSKgPzH92oA7AAcXEvWMnG *fun_workspace_runtimedata, const
               sXyXDxkiKhsfpX9ivkpx9WG *fun_workspace_userdata, const real_T x0
               [46], const real_T Aineq_data[], const real_T bineq_data[], const
               int32_T *bineq_size, const real_T lb[46], const
               s_GSKgPzH92oA7AAcXEvWMnG *nonlcon_workspace_runtimedata, const
               sXyXDxkiKhsfpX9ivkpx9WG *nonlcon_workspace_userdata, real_T x[46],
               real_T *fval, real_T *exitflag, real_T *output_iterations, real_T
               *output_funcCount, char_T output_algorithm[3], real_T
               *output_constrviolation, real_T *output_stepsize, real_T
               *output_lssteplength, real_T *output_firstorderopt);

  // Real-Time Model
  RT_MODEL rtM;
};

// Constant parameters (default storage)
extern const MPC_controller::ConstP rtConstP;

//-
//  These blocks were eliminated from the model due to optimizations:
//
//  Block '<S4>/Matrix Dimension Check' : Unused code path elimination
//  Block '<S5>/Matrix Dimension Check' : Unused code path elimination
//  Block '<S6>/Matrix Dimension Check' : Unused code path elimination
//  Block '<S7>/Matrix Dimension Check' : Unused code path elimination
//  Block '<S8>/Matrix Dimension Check' : Unused code path elimination
//  Block '<S9>/Matrix Dimension Check' : Unused code path elimination
//  Block '<S10>/Matrix Dimension Check' : Unused code path elimination
//  Block '<S11>/Matrix Dimension Check' : Unused code path elimination
//  Block '<S12>/Matrix Dimension Check' : Unused code path elimination
//  Block '<S13>/Matrix Dimension Check' : Unused code path elimination
//  Block '<S14>/Matrix Dimension Check' : Unused code path elimination
//  Block '<S15>/Matrix Dimension Check' : Unused code path elimination
//  Block '<S16>/Matrix Dimension Check' : Unused code path elimination
//  Block '<S17>/Matrix Dimension Check' : Unused code path elimination
//  Block '<S18>/Matrix Dimension Check' : Unused code path elimination
//  Block '<S19>/Matrix Dimension Check' : Unused code path elimination
//  Block '<S20>/Vector Dimension Check' : Unused code path elimination
//  Block '<S21>/Vector Dimension Check' : Unused code path elimination
//  Block '<S22>/Vector Dimension Check' : Unused code path elimination
//  Block '<S23>/Vector Dimension Check' : Unused code path elimination
//  Block '<S1>/mv.init_zero' : Unused code path elimination
//  Block '<S1>/x.init_zero' : Unused code path elimination
//  Block '<S2>/Reshape' : Reshape block reduction
//  Block '<S2>/Reshape1' : Reshape block reduction
//  Block '<S2>/mo or x Conversion' : Eliminate redundant data type conversion
//  Block '<S2>/mo or x Conversion1' : Eliminate redundant data type conversion
//  Block '<S2>/mo or x Conversion10' : Eliminate redundant data type conversion
//  Block '<S2>/mo or x Conversion11' : Eliminate redundant data type conversion
//  Block '<S2>/mo or x Conversion12' : Eliminate redundant data type conversion
//  Block '<S2>/mo or x Conversion13' : Eliminate redundant data type conversion
//  Block '<S2>/mo or x Conversion14' : Eliminate redundant data type conversion
//  Block '<S2>/mo or x Conversion15' : Eliminate redundant data type conversion
//  Block '<S2>/mo or x Conversion16' : Eliminate redundant data type conversion
//  Block '<S2>/mo or x Conversion17' : Eliminate redundant data type conversion
//  Block '<S2>/mo or x Conversion18' : Eliminate redundant data type conversion
//  Block '<S2>/mo or x Conversion19' : Eliminate redundant data type conversion
//  Block '<S2>/mo or x Conversion2' : Eliminate redundant data type conversion
//  Block '<S2>/mo or x Conversion3' : Eliminate redundant data type conversion
//  Block '<S2>/mo or x Conversion4' : Eliminate redundant data type conversion
//  Block '<S2>/mo or x Conversion5' : Eliminate redundant data type conversion
//  Block '<S2>/mo or x Conversion6' : Eliminate redundant data type conversion
//  Block '<S2>/mo or x Conversion7' : Eliminate redundant data type conversion
//  Block '<S2>/mo or x Conversion8' : Eliminate redundant data type conversion
//  Block '<S2>/mo or x Conversion9' : Eliminate redundant data type conversion
//  Block '<S3>/reshape_mv' : Reshape block reduction
//  Block '<S3>/reshape_x' : Reshape block reduction


//-
//  The generated code includes comments that allow you to trace directly
//  back to the appropriate location in the model.  The basic format
//  is <system>/block_name, where system is the system number (uniquely
//  assigned by Simulink) and block_name is the name of the block.
//
//  Use the MATLAB hilite_system command to trace the generated code back
//  to the model.  For example,
//
//  hilite_system('<S3>')    - opens system 3
//  hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
//
//  Here is the system hierarchy for this model
//
//  '<Root>' : 'MPC_controller'
//  '<S1>'   : 'MPC_controller/Nonlinear MPC Controller'
//  '<S2>'   : 'MPC_controller/Nonlinear MPC Controller/MPC'
//  '<S3>'   : 'MPC_controller/Nonlinear MPC Controller/xmvs_router'
//  '<S4>'   : 'MPC_controller/Nonlinear MPC Controller/MPC/MPC Preview Signal Check'
//  '<S5>'   : 'MPC_controller/Nonlinear MPC Controller/MPC/MPC Preview Signal Check1'
//  '<S6>'   : 'MPC_controller/Nonlinear MPC Controller/MPC/MPC Preview Signal Check10'
//  '<S7>'   : 'MPC_controller/Nonlinear MPC Controller/MPC/MPC Preview Signal Check11'
//  '<S8>'   : 'MPC_controller/Nonlinear MPC Controller/MPC/MPC Preview Signal Check12'
//  '<S9>'   : 'MPC_controller/Nonlinear MPC Controller/MPC/MPC Preview Signal Check13'
//  '<S10>'  : 'MPC_controller/Nonlinear MPC Controller/MPC/MPC Preview Signal Check14'
//  '<S11>'  : 'MPC_controller/Nonlinear MPC Controller/MPC/MPC Preview Signal Check15'
//  '<S12>'  : 'MPC_controller/Nonlinear MPC Controller/MPC/MPC Preview Signal Check16'
//  '<S13>'  : 'MPC_controller/Nonlinear MPC Controller/MPC/MPC Preview Signal Check3'
//  '<S14>'  : 'MPC_controller/Nonlinear MPC Controller/MPC/MPC Preview Signal Check4'
//  '<S15>'  : 'MPC_controller/Nonlinear MPC Controller/MPC/MPC Preview Signal Check5'
//  '<S16>'  : 'MPC_controller/Nonlinear MPC Controller/MPC/MPC Preview Signal Check6'
//  '<S17>'  : 'MPC_controller/Nonlinear MPC Controller/MPC/MPC Preview Signal Check7'
//  '<S18>'  : 'MPC_controller/Nonlinear MPC Controller/MPC/MPC Preview Signal Check8'
//  '<S19>'  : 'MPC_controller/Nonlinear MPC Controller/MPC/MPC Preview Signal Check9'
//  '<S20>'  : 'MPC_controller/Nonlinear MPC Controller/MPC/MPC Scalar Signal Check1'
//  '<S21>'  : 'MPC_controller/Nonlinear MPC Controller/MPC/MPC Scalar Signal Check2'
//  '<S22>'  : 'MPC_controller/Nonlinear MPC Controller/MPC/MPC Vector Signal Check1'
//  '<S23>'  : 'MPC_controller/Nonlinear MPC Controller/MPC/MPC Vector Signal Check11'
//  '<S24>'  : 'MPC_controller/Nonlinear MPC Controller/MPC/NLMPC'

#endif                                 // RTW_HEADER_MPC_controller_h_

//
// File trailer for generated code.
//
// [EOF]
//
