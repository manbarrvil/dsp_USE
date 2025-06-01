//This file computes all Park transformations and PLL implementation
#include "DSP2833x_Device.h"
#include "DSP2833x_Examples.h"
#include "type_structs.h"

//dq transformation function
// output: structure PLL_output
// input: structure ADC conversion
// Input: structure of the uvsg. This is for the VSG
// Input: startAC. This is for the VSG
#pragma CODE_SECTION(PLL_dq,"ramfuncs")
struct PLL_output PLL_dq(struct ADC_conv ADC_p, struct uvsg u, int startAC)
{
// Static variables. Integrator of the APCL
    static double int0 = 0;

// Structures PLL_output assigns to variable s
    static struct PLL_output s;

// CTRL 5 is the VSG
#if (CTRL == 5)
    // Compute variables
    s.alfa_V = 0.666666666667*ADC_p.V_a -0.333333333333*ADC_p.V_b -0.333333333333*ADC_p.V_c;
    s.beta_V = 0.577350269189915*ADC_p.V_b - 0.577350269189915*ADC_p.V_c;

    s.alfa_I = 0.666666666667*ADC_p.I_a -0.333333333333*ADC_p.I_b -0.333333333333*ADC_p.I_c;
    s.beta_I = 0.577350269189915*ADC_p.I_b - 0.577350269189915*ADC_p.I_c;

    s.sin = u.sin;
    s.cos = u.cos;

    s.V_d =  (s.alfa_V*s.cos + s.beta_V*s.sin);
    s.V_q = (-s.alfa_V*s.sin + s.beta_V*s.cos);
    s.I_d =  (s.alfa_I*s.cos + s.beta_I*s.sin);
    s.I_q = (-s.alfa_I*s.sin + s.beta_I*s.cos);

    s.omega = 1.8*s.V_d + int0;

//   Refresh static variables
    if (startAC > 0.5)
    {
        int0=0;
    }
    else{
        int0 = int0 + s.V_d*717.1314741*Ts;
    }
    // Return structure
    return s;


#else
// Rest of the controllers based on PLL
// integrator int1 for theta in the PLL, omega and omega filtered
    static double int1 = 0, omega = 0.0, omega_f = 0.0;
// Compute voltage and current variables in alfabeta
    s.alfa_V = 0.666666666667*ADC_p.V_a -0.333333333333*(ADC_p.V_b +ADC_p.V_c);
    s.beta_V = 0.577350269189915*(ADC_p.V_b - ADC_p.V_c);

    s.alfa_I = 0.666666666667*ADC_p.I_a -0.333333333333*(ADC_p.I_b +ADC_p.I_c);
    s.beta_I = 0.577350269189915*(ADC_p.I_b - ADC_p.I_c);
// Define sine and cosine from theta
    s.sin = sin(int1);
    s.cos = cos(int1);
//Compute the dq voltages and currents from alfabeta
    s.V_d =  (s.alfa_V*s.cos + s.beta_V*s.sin);
    s.V_q = (-s.alfa_V*s.sin + s.beta_V*s.cos);
    s.I_d =  (s.alfa_I*s.cos + s.beta_I*s.sin);
    s.I_q = (-s.alfa_I*s.sin + s.beta_I*s.cos);
    s.theta = int1;
// Computation of omega. PI controller for Vd component. TyhpoonSim: //omega_pll = K_p_pll*e_q + y_q; y_q= y_q + K_i_pll*Ts_Control*e_q;
    omega = K_p_pll*s.V_d + int0;
// omega filter with a LPF tuned at 200HZ
    omega_f=omega*0.01+0.99*omega_f;
    s.omega = omega_f;

// Refresh static variables. Integrator of vd
    int0 = int0 + s.V_d*K_i_pll*Ts;
//Integrator of omega. Typhoonsim. theta = theta + Ts_Control*omega_pll;;
    int1 = int1 + omega*Ts;
// Reset of theta every 2*pi
    if (int1 >= 6.283185307179586)
    {
        int1 = int1 - 6.283185307179586;
    }

// Return structure
    return s;
#endif
}

// Inverse of the Park Transformation function
// output: structure duty_cycle
// input: PLL_output
// Input: structure duty_cycle
#pragma CODE_SECTION(Park_inverse,"ramfuncs")
struct duty_cycle Park_inverse(struct PLL_output PLL_dq, struct duty_cycle eta_dq)
{
// Structures duty_cycle assigns to variable eta_abc
    struct duty_cycle eta_abc;

// Compute variables
// eta computed  dq.
    eta_abc.eta_d = eta_dq.eta_d;
    eta_abc.eta_q = eta_dq.eta_q;
// eta computed alpha-beta.
    eta_abc.eta_alfa = eta_dq.eta_d*PLL_dq.cos - eta_dq.eta_q*PLL_dq.sin;
    eta_abc.eta_beta = eta_dq.eta_d*PLL_dq.sin + eta_dq.eta_q*PLL_dq.cos;
// eta computed abc.
    eta_abc.eta_a = eta_abc.eta_alfa;
    eta_abc.eta_b = -0.5*eta_abc.eta_alfa + 0.866025403784439*eta_abc.eta_beta;
    eta_abc.eta_c = -0.5*eta_abc.eta_alfa - 0.866025403784439*eta_abc.eta_beta;

// Saturation of the eta signal
    if (eta_abc.eta_a > 0.99) {eta_abc.eta_a = 0.99;}
    if (eta_abc.eta_a < -0.99) {eta_abc.eta_a = -0.99;}
    if (eta_abc.eta_b > 0.99) {eta_abc.eta_b = 0.99;}
    if (eta_abc.eta_b < -0.99) {eta_abc.eta_b = -0.99;}
    if (eta_abc.eta_c > 0.99) {eta_abc.eta_c = 0.99;}
    if (eta_abc.eta_c < -0.99) {eta_abc.eta_c = -0.99;}

// Return structure eta_abc
    return eta_abc;
}






