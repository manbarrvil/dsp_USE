#include "DSP2833x_Device.h"
#include "DSP2833x_Examples.h"
#include "type_structs.h"
#include "DSP28x_Project.h"

// Function Park_inverse defined in file PLL_Pak_transformations.c
struct duty_cycle Park_inverse(struct PLL_output, struct duty_cycle);		// Park Inverse
double ctrl_z3(struct ADC_conv ADC_p);

#pragma CODE_SECTION (CTRL1_comp,"ramfuncs")
struct duty_cycle CTRL1_comp(struct ADC_conv ADC_p, struct PLL_output PLL_dq, double theta, double omega, double etass, double i_q_ref, int flag)
{
// Static variables for integrator
	static double int2 = 0, int3=0;

	if (flag == 0){
		int2 = 0.0;
		int3 = 0.0;
	}

// Structures
	struct duty_cycle s={0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, eta={0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

	// Compute variables
#if CTRL_Z == 1
	s.eta_z = ctrl_z3(ADC_p);
	s.eta_d = (2.0/ADC_p.V_h)*(-omega*(0.005)*PLL_dq.I_q + PLL_dq.V_d + K_i_p*(etass - PLL_dq.I_d) + int2);
	s.eta_q = (2.0/ADC_p.V_h)*( omega*(0.005)*PLL_dq.I_d + PLL_dq.V_q + K_i_p*(i_q_ref - PLL_dq.I_q) + int3);
#else
    s.eta_d = (2.0/ADC_p.V_h)*(-omega*(0.005)*PLL_dq.I_q + PLL_dq.V_d + K_i_p*(etass - PLL_dq.I_d) + int2);
    s.eta_q = (2.0/ADC_p.V_h)*( omega*(0.005)*PLL_dq.I_d + PLL_dq.V_q + K_i_p*(i_q_ref - PLL_dq.I_q) + int3);
#endif

	// Refresh static variables
	if (flag == 1){
		int2 = int2 + K_i_i*(etass - PLL_dq.I_d)*Ts;
		int3 = int3 + K_i_i*(i_q_ref - PLL_dq.I_q)*Ts;
	}

	eta = Park_inverse(PLL_dq, s);
	// Return structure
	return eta;
}


