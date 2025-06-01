#include "DSP2833x_Device.h"
#include "DSP2833x_Examples.h"
#include "type_structs.h"

#pragma CODE_SECTION (VSG_comp,"ramfuncs")

struct uvsg VSG_comp(double enable_P_ref, double P_pu_ref, double Q_pu_ref, struct ADC_conv ADC_p, struct PLL_output PLL_Park, double runFSM)
{
//variable for omega_o, vdq pu, idq pu, electromotive force, integrators, omega base, dq currente references LPF
    /* Update the states
     * int1 = incremento de omega pu
     * int2 = theta rads
     * int3 = incremento de tension pu
     * int4 = omega filtrada */
	static double omega_o=0, v_d_pu=0, v_q_pu=0, i_d_pu=0, i_q_pu=0, e_q=0, int1=0, int2=0, int3=0, int4=omega_b, i_d_ref_ant=0, i_q_ref_ant=0;
// structure of the uvsg
	struct uvsg u;


	v_d_pu=PLL_Park.V_d*0.003061862178479; //Conversion to pu 1/Ubdq U_bdq = 326.5986
	v_q_pu=PLL_Park.V_q*0.003061862178479; //Conversion to pu 1/Ubdq U_bdq = 326.5986
	i_d_pu=PLL_Park.I_d*0.02449414855676; //Conversion to pu 1/I_bdq I_bdq = 40.8248
	i_q_pu=PLL_Park.I_q*0.02449414855676; //Conversion to pu 1/I_bdq I_bdq = 40.8248

// omega_o is 1 pu
	if (runFSM>0.5){
		omega_o=1;
	}
// omega o is computed from the PLL
	else{
		omega_o=PLL_Park.omega*0.0031830988618379; //omega_o p.u 1/(2*pi*50)
	}

// Power computation in pu
	u.p_s=i_d_pu*v_d_pu+i_q_pu*v_q_pu;
	u.q_s=i_d_pu*v_q_pu-i_q_pu*v_d_pu;

// Outputs of the active power control
//TyphoonSim //omega VSG rads omega_vsg = (Kp_p*e_p + x_p + omega_base)*2.0*M_PI*50.0;
	u.omega=(Kp_p*(P_pu_ref-u.p_s)+int1+omega_o)*omega_b;
//TyphoonSim //theta VSG theta_vsg= theta;
	u.theta=int2;
//compute sin and cos
	u.sin=sin(u.theta);
	u.cos=cos(u.theta);

// Outputs of the reactive power control
// electromotive force pu e = e_o + Kp_q*e_q + x_q;
	u.DV=Kp_q*(Q_pu_ref-u.q_s)+int3;
	e_q=1.0+u.DV;
	u.e_q = -e_q*E_0; //electromotive force in V

// Virtual  current reference computation in pu
	u.i_d_ref=-(Xv*e_q+Rv*v_d_pu+Xv*v_q_pu)/(Rv*Rv+Xv*Xv);
	u.i_q_ref=-(Rv*e_q+Rv*v_q_pu-Xv*v_d_pu)/(Rv*Rv+Xv*Xv);

// LPF filter implementation for current references // 2.4 ms
    u.i_d_ref=u.i_d_ref*0.02+i_d_ref_ant*0.98;
    u.i_q_ref=u.i_q_ref*0.02+i_q_ref_ant*0.98;
	i_d_ref_ant=u.i_d_ref;
	i_q_ref_ant=u.i_q_ref;

// current reference in A
	u.i_d_ref=u.i_d_ref*40.824799999999939;
	u.i_q_ref=u.i_q_ref*40.824799999999939;

//Integrator of the APCL and RPCL
	if (runFSM>0.5){
		int1=int1+Ki_p*(P_pu_ref-u.p_s)*Ts;
		int3=int3+Ki_q*(Q_pu_ref-u.q_s)*Ts;
	}
	else{
		int1=0;
		int3=0;
	}
    if (int2 > 6.283185307179586){
        int2=int2-6.283185307179586;
        }

    int2=int2+u.omega*Ts;


	u.omega_rads=int4+(-int4+u.omega)*Ts;

	return u;

}
