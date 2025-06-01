#include "DSP2833x_Device.h"
#include "DSP2833x_Examples.h"
#include "type_structs.h"

#pragma CODE_SECTION (VSG_comp,"ramfuncs")

struct uvsg VSG_comp(double P_ref, double Q_ref, struct ADC_conv ADC_p, struct PLL_output PLL_Park, double runFSM)
{
//variable for omega_o, vdq pu, idq pu, electromotive force, integrators, omega base, dq currente references LPF
    /* Update the states
     * int1 = incremento de omega pu
     * int2 = theta rads
     * int3 = incremento de tension pu
     * int4 = omega filtrada */
	static double omega_ref=0, vd_pu=0, vq_pu=0, id_pu=0, iq_pu=0, p_pu_ref = 0.0, q_pu_ref = 0.0, e=1.0, int1=0, int2=0, int3=0, int4=omega_b, i_d_ref_ant=0, i_q_ref_ant=0;
// structure of the uvsg
	struct uvsg u;
// active and reactive power error
	static double ep = 0.0, eq = 0.0;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////PI VSG CONTROLLER///////////////
//voltage and current in pu
	vd_pu=PLL_Park.V_d*0.003061862178479; //Conversion to pu 1/Ubdq U_bdq = 326.5986
	vq_pu=PLL_Park.V_q*0.003061862178479; //Conversion to pu 1/Ubdq U_bdq = 326.5986
	id_pu=PLL_Park.I_d*0.02449414855676; //Conversion to pu 1/I_bdq I_bdq = 40.8248
	iq_pu=PLL_Park.I_q*0.02449414855676; //Conversion to pu 1/I_bdq I_bdq = 40.8248

//active and reactive power refernces in pu
	p_pu_ref = P_ref*0.00005; //Conversion to pu Sb = 20000
	q_pu_ref = Q_ref*0.00005; //Conversion to pu Sb = 20000

// omega_o is 1 pu
	if (runFSM>0.5){
		omega_ref=1;
	}
// omega o is computed from the PLL
	else{
		omega_ref=PLL_Park.omega*0.0031830988618379; //omega_o p.u 1/(2*pi*50)
	}

// actual power computation in pu
	u.p_s=id_pu*vd_pu+iq_pu*vq_pu;
	u.q_s=id_pu*vq_pu-iq_pu*vd_pu;

// Outputs of the active power control
//TyphoonSim //omega VSG rads omega_vsg = (Kp_p*e_p + x_p + omega_base)*2.0*M_PI*50.0;
	ep = (p_pu_ref-u.p_s);
	u.omega=(Kp_p*ep + int1 + omega_ref)*omega_b;
//TyphoonSim //theta VSG theta_vsg= theta;
	u.theta=int2;
//compute sin and cos
	u.sin=sin(u.theta);
	u.cos=cos(u.theta);

// Outputs of the reactive power control
// electromotive force pu e = e_o + Kp_q*e_q + x_q;
	eq = (q_pu_ref-u.q_s);
	u.DV=Kp_q*eq + int3;
	e=1.0 + u.DV;
	u.e_q = -e*E_0; //electromotive force in V

// Virtual  current reference computation in pu
	u.i_d_ref=-(Xv*e + Rv*vd_pu + Xv*vq_pu)/(Rv*Rv + Xv*Xv);
	u.i_q_ref=-(Rv*e + Rv*vq_pu - Xv*vd_pu)/(Rv*Rv + Xv*Xv);

// LPF filter implementation for current references // 2.4 ms
    u.i_d_ref=u.i_d_ref*0.02+i_d_ref_ant*0.98;
    u.i_q_ref=u.i_q_ref*0.02+i_q_ref_ant*0.98;
	i_d_ref_ant=u.i_d_ref;
	i_q_ref_ant=u.i_q_ref;

// current reference in A
	u.i_d_ref=u.i_d_ref*40.824799999999939;
	u.i_q_ref=u.i_q_ref*40.824799999999939;

//Integrator of the APCL and RPCL
//TyphoonSim integrator PI active adn reactive power x_p = x_p + Ki_p*Ts_Control*e_p; x_q = x_q + Ki_q*Ts_Control*e_q;
	if (runFSM>0.5){
		int1=int1+Ki_p*ep*Ts;
		int3=int3+Ki_q*eq*Ts;
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
