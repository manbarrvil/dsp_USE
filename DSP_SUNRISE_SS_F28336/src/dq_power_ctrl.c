#include "DSP2833x_Device.h"
#include "DSP2833x_Examples.h"
#include "type_structs.h"


struct duty_cycle DQCURRENT_comp(struct ADC_conv, struct PLL_output,  double i_d_ref, double i_q_ref, int flag_c);

#pragma CODE_SECTION (DQPOWER_comp,"ramfuncs")
// function DQPOWER_comp
// Input: Structure--> ADC_conv. Required for the function DQCURRENT_comp
// Input: Structure--> PLL_output. omega computation from PLL, voltages and currents in dq for the function DQCURRENT_comp. Voltages in dq for the function DQPOWER_comp
// Input: active power reference W
// Input: reactive power reference var
// Input:flag for resetting integrators
// Output: eta_abc
struct duty_cycle DQPOWER_comp(struct ADC_conv ADC_p, struct PLL_output PLL_dq, double P_ref, double Q_ref, int flag)

{
// Correspondence between TyphoonSim <---> CCS
// pq_ref[0] <---> P_ref
// pq_ref[1] <---> Q_ref
// is_d_ref <---> i_d_ref
// is_q_ref <---> i_q_ref
// vs_dq[0] <---> PLL_dq.V_d
// vs_dq[1] <---> PLL_dq.V_q


// Static variables for current references dq
	static double i_d_ref=0;
	static double i_q_ref=0;

// Structure duty_cycle assigns to variable eta
	struct duty_cycle  eta={0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////Current reference computation////////////////////////

//TyphoonSim is_d_ref = 2.0/3.0*(pq_ref[0]*vs_dq[0] - pq_ref[1]*vs_dq[1])/(pow(vs_dq[0],2) + pow(vs_dq[1],2) );
//TyphoonSim is_q_ref = 2.0/3.0*(pq_ref[0]*vs_dq[1] - pq_ref[1]*vs_dq[0])/(pow(vs_dq[0],2) + pow(vs_dq[1],2) );
	i_d_ref=0.66666666666667*((P_ref*PLL_dq.V_d)-(Q_ref*PLL_dq.V_q))/(PLL_dq.V_d*PLL_dq.V_d+PLL_dq.V_q*PLL_dq.V_q);
	i_q_ref=0.66666666666667*((P_ref*PLL_dq.V_q)-(Q_ref*PLL_dq.V_d))/(PLL_dq.V_d*PLL_dq.V_d+PLL_dq.V_q*PLL_dq.V_q);

	///////////////////////////////Current reference computation////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Return structure eta. Output of the function DQCURRENT_comp
	eta = DQCURRENT_comp(ADC_p, PLL_dq, i_d_ref, i_q_ref, flag);


	// Return structure
	return eta;
}





