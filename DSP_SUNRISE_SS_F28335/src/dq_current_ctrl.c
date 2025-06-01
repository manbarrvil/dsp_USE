#include "DSP2833x_Device.h"
#include "DSP2833x_Examples.h"
#include "type_structs.h"
#include "DSP28x_Project.h"

struct duty_cycle Park_inverse(struct PLL_output, struct duty_cycle);

#pragma CODE_SECTION (DQCURRENT_comp,"ramfuncs")
// function DQCURRENT_comp
// Input: Structure--> ADC_conv. DC voltage measurement V_h
// Input: Structure--> PLL_output. omega computation from PLL, voltages and current in dq
// Input:theta angle. Is it required?
// Input:omega.
// Input:d current reference
// Input:q current reference
// Input:flag for enabling integrator
struct duty_cycle DQCURRENT_comp(struct ADC_conv ADC_p, struct PLL_output PLL_dq, double i_d_ref, double i_q_ref, int flag)

{
// Static variables for integrator
    static double y_d = 0, y_q=0;
	//static double int2 = 0, int3=0;
// Static variables for error
	static double e_d = 0, e_q=0;
// Structure duty_cycle assigns to variable s and eta
	struct duty_cycle s={0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, eta={0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////7
	    ///////////PI DQ CURRENT CONTROLLER///////////////

// Initialization and reset of integrator
	if (flag == 0){
	    y_d = 0.0;
	    y_q = 0.0;
	}

// error in dq axes
	e_d = i_d_ref - PLL_dq.I_d;
	e_q = i_q_ref - PLL_dq.I_q;

//Computation of the eta signals: PI ctrl+cross-coupling-term cancellation+feedforward signals
//Typhon sim //modulating signal computation eta_d = (2/v_dc) * (Kp_i*e_d + y_d -   L*omega*is_dq[1] + vs_dq[0]); eta_q = (2/v_dc )* (Kp_i*e_q + y_q +  L*oemga*is_dq[0] + vs_dq[1]);
	s.eta_d = (2.0/ADC_p.V_h)*(Kp_i*e_d + y_d - PLL_dq.omega*(L)*PLL_dq.I_q + PLL_dq.V_d);
	s.eta_q = (2.0/ADC_p.V_h)*(Kp_i*e_q + y_q + PLL_dq.omega*(L)*PLL_dq.I_d + PLL_dq.V_q);

// Refresh static variables
	if (flag == 1){
	    //TyphoonSim //integrator y_d = y_d + Ki_i*Ts_Control*e_d; y_q = y_q + Ki_i*Ts_Control*e_q;
	    y_d = y_d + Ki_i*e_d*Ts;
	    y_q = y_q + Ki_i*e_q*Ts;
	}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////7

// eta transformation from abc to dq
	eta = Park_inverse(PLL_dq, s);
// Return structure eta. Output of the function DQCURRENT_comp
	return eta;
}


