#include "DSP2833x_Device.h"
#include "DSP2833x_Examples.h"
#include "type_structs.h"
#include "DSP28x_Project.h"

struct duty_cycle DQPOWER_comp(struct ADC_conv, struct PLL_output, double P_ref, double Q_ref, int flag);

#pragma CODE_SECTION (DQSTATCOM_comp,"ramfuncs")
// function DQSTATCOM_comp
// Input: Structure--> ADC_conv. Required for the function DQPOWER_comp. DC voltage for the function DQSTATCOM_comp
// Input: Structure--> PLL_output. omega computation from PLL, voltages and currents in dq for the function DQCURRENT_comp. Voltages in dq for the function DQPOWER_comp
// Input: dc voltage reference V
// Input: reactive power reference var
// Input:flag for resetting integrators
// Output: eta_abc
struct duty_cycle DQSTATCOM_comp(struct ADC_conv ADC_p, struct PLL_output PLL_dq, double vh_ref, double Q_ref, int flag)
{
// Correspondence between TyphoonSim <---> CCS
// y_dc <---> y_dc
// e_dc <---> e_dc
// Kp_dc <---> Kp_dc
// Ki_dc <---> Ki_dc
// v_dc_ref<---> vh_ref1
// v_dc <---> ADC_p.V_h
// p_ref <---> P_ref
// Ts_Control <---> Ts

// Static variables integrator dc, active power reference, initial voltage reference, error voltage dc, variable for the square of the voltages
	static double  y_dc = 0, P_ref = 0, vh_ref1 = 600.0, e_dc = 0.0, vh_2=0.0;
// Structure duty_cycle assigns to variable eta
	struct duty_cycle  eta={0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////7
	        ///////////PI DC VOLTAGE CONTROLLER///////////////

// Initialization and reset of integrator. Variable flag is used for reset. If flag is equal to 1, integrator is exectuded. Otherwise is zero
	if (flag == 0){
	    y_dc = 0.0;
	}

// Creation of a ramp for progressively increasing the dc voltage reference
	if (vh_ref > vh_ref1)
	{
	    vh_ref1 = vh_ref1 + 0.002;
	}
    if (vh_ref < vh_ref1)
    {
        vh_ref1 = vh_ref1 - 0.002;
    }

// Computation of the active power reference
// Typhon sim:e_dc = pow(v_dc_ref,2) - pow(v_dc,2);
//Typhon sim: p_ref =-( Kp_dc*e_dc + y_dc);
    vh_ref = vh_ref1*vh_ref1;
    vh_2 = ADC_p.V_h*ADC_p.V_h;
    e_dc = vh_ref - vh_2;
    P_ref = -(Kp_dc*e_dc + y_dc);

// Reset of the integrator. Variable flag is used for reset. If flag is equal to 1, integrator is exectuded. Otherwise is zero
	if (flag == 1){
	    //Typhoonsim y_dc = y_dc + Ki_dc*Ts_Control*e_dc;
	    y_dc = y_dc + Ki_dc*e_dc*Ts;
	}
	///////////PI DC VOLTAGE CONTROLLER///////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////7

// Return structure eta. Output of the function DQPOWER_comp
	eta = DQPOWER_comp(ADC_p, PLL_dq, P_ref, Q_ref, flag);
	// Return structure
	return eta;
}

