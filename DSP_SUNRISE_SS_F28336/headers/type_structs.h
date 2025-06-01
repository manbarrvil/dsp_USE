#define PWM_TIMER_TBPRD 		3750 	// 20 kHz -> 50 us
#define EPWM_MIN_DB  			8 	// Dead-band of 0.1us for ePWM (Table 3.15)
#define Ts						50e-6   // Execution rate of the microcontroller
#define DEVICE          4	// Device number for ADC calibration parameters
    // DEVICE   4           TYPHOON

#define wires           3 //numer of operative wires into the VSC
/////////////////////////////////////////////////////////////////////////
#define CTRL            11
/*  CTRL code
    2 -> dq current controller
    3 -> active an reactive power controller
    11 -> STATCOM. DC bus voltage controller and reactive power controller
    5 -> Grid-Forming PI-VSG (PQ in W/var) */

//////////////////////////////////////////////////////////////////////////

#define     EXT_SYNC            0       // EXT_SYNC = 0 -> EXTERNAL SYNC OFF (MASTER),      EXT_SYNC = 1 -> EXTERNAL SYNC ON (SLAVE)
#define     FSM                 1       // Enable FSM

//Calibration depending on the device
#if DEVICE==4  // TYPHOON

#define     GAIN_IN         1 //gain for the neutral current of the VSC
#define     OFF_IN          0 //offset for the neutral current of the VSC
#define 	GAIN_IH			1 //gain for the  current in the hv side of DC/DC converter
#define		OFF_IH			0 //offset  for the  current in the hv side of DC/DC converter
#define		GAIN_IL			1 //gain for the  current in the lv side of DC/DC converter
#define		OFF_IL			0 //offset  for the  current in the hv side of DC/DC converter
#define		GAIN_VL			1 //gain for the  voltage in the lv side of DC/DC converter
#define		OFF_VL			0 //offset  for the  current in the lv side of DC/DC converter
#define		GAIN_VH			1 //gain for the  voltage in the hv side of DC/DC converter
#define		OFF_VH			0 //offset  for the  current in the hv side of DC/DC converter
#define		GAIN_IC			1 //gain for the current c of the VSC
#define		OFF_IC			0 //offset for the current c of the VSC
#define		GAIN_VC			1 //gain for the voltage c of the VSC
#define		OFF_VC			0 //offset for the voltage c of the VSC
#define		GAIN_IB			1 //gain for the current b of the VSC
#define		OFF_IB			0 //offset for the current b of the VSC
#define		GAIN_VB			1 //gain for the voltage b of the VSC
#define		OFF_VB			0 //offset for the voltage b of the VSC
#define		GAIN_IA			1 //gain for the current a of the VSC
#define		OFF_IA			0 //offset for the current c of the VSC
#define		GAIN_VA			1 //gain for the voltage a of the VSC
#define		OFF_VA			0 //offset for the voltage b of the VSC

#endif

// Limits of operation in the electrical magnitudes for protecting the VSC
#define V_pk_min 		34000         //34000 Square of the minimum voltage (184 v rms )
#define V_pk_max        65000       //65000 Square of the maximum voltage (255 V rms)
#define V_h_min         500     //680 Minimum DC bus voltage
#define V_h_max         775         //770 Maximum DC bus voltage
#define I_pk_max        50          //40 Maximum peak current
#define omega_min 		200         //200 Minimum of the angular frequency
#define omega_max 		450         //450 Maximum of the angular frequency

// Transformation parameters
// Rotation matrix
#define c120          -0.5 //cosine of 120º. Help to reduce the number of sine and cosine operations in transforms
#define s120          0.866025403784439 //sin of 120º

// PLL control gains
#define K_p_pll         1.8
#define K_i_pll         717.1314741 // 1.8/0.00251

// Current controller gains dq
#define Kp_i			5
#define Ki_i			200

// Filter Parameters
#define L           0.005

// CTRL 11 parameters DC-Control
#define Kp_dc           0.22
#define Ki_dc           2.2

// Virtual Synchronous generator gains
#define Xv              0.1 //Virtual reactance
#define Rv              0.0 //Virtual resistance
#define Kp_q            0.1 //Proportional gain reactive power control loop
#define Ki_q            1 //Integral gain reactive power control loop
#define omega_b         314.1592653589793 //base angular frequency rads
#define Kp_p            0.075 // Proportional gain active power control loop 1/(2H). H inertia constant
#define Ki_p            0.1 // Integral gain active power control loop
#define omega_base_inv  0.003183098861838 //inverse base angular frequency rads
#define omega_base      314.1592653589793 //base angular frequency rads
#define E_0             325.2691193458119 //Virtual electromotive force. V

// import math.h
#define __BSD_VISIBLE
#include "math.h"

// Definition of structures
//////////////////////////////////////////////////////////////////////////
//PLL
struct PLL_output{
	double theta, omega, V_d, V_q, I_d, I_q, sin, cos, alfa_I, beta_I, alfa_V, beta_V;
};

//powers
struct powers{
	double P3f, Q3f;
};

//dc/ac conversion
struct ADC_conv{
    double I_h, I_l, V_l, V_h, I_c, V_c, I_b, V_b, I_a, V_a, I_n;
};

//dq to abc transformation
struct dq_abc{
    double da, qa, db, qb, dc, qc;
};

//modulating signals
struct duty_cycle{
	double eta_z, eta_d, eta_q, eta_a, eta_b, eta_c, eta_alfa, eta_beta, eta_pk, eta_n;
};

//state machine for protecting the VSC
struct state_m{
	double PWM_enabled, Fault_Type, Reset_Drivers;
};


//References
struct references{
    int start_FSM, start_AC;
    double id_ref, iq_ref, p_ref, q_ref, vdc_ref;
};

//dq components
struct dq{
    double d, q;
};

//alpha-beta components
struct afbt{
    double af, bt;
};

//abc componets
struct abc{
    double a, b, c;
};

//abcn, alfabeta, dq components
struct signal{
    double a, b, c, n, alfa, beta, d, q;
};

//rms components
struct rms{
	double ia_rms, ib_rms, ic_rms, in_rms, va_rms, vb_rms, vc_rms;
};

//virtual synchronous generator
struct uvsg{
    double omega, theta, e_q, omega_rads, DV, p_s, q_s, sin, cos, i_d_ref, i_q_ref;

};

//////////////////////////////////////////////////////////////////////////

