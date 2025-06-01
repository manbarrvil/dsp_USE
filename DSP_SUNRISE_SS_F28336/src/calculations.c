#include "DSP2833x_Device.h"
#include "DSP2833x_Examples.h"
#include "type_structs.h"
#include <math.h>

#pragma CODE_SECTION(rms_calculation,"ramfuncs")
struct rms rms_calculation(struct ADC_conv ADC)
{
    static struct rms rms_out;     // RMS output struct
//
    #if (wires == 3)
        double Vi[6]={0,0,0,0,0,0};            // ADC measurements
        double Vi2[6]={0,0,0,0,0,0};
        static double rms2[6]={0,0,0,0,0,0};           // RMS vector
//        static double rms0[7]={0,0,0,0,0,0,0};         // Filtered RMS vector
        static double Sum[6]={0,0,0,0,0,0};
//        unsigned int n_meas = 6;            // Length of ADC measurements
        Vi[0]=ADC.V_a;
        Vi[1]=ADC.V_b;
        Vi[2]=ADC.V_c;
        Vi[3]=ADC.I_a;
        Vi[4]=ADC.I_b;
        Vi[5]=ADC.I_c;
    #endif

    static unsigned int i=0;

    // RMS output struct assignment
        unsigned int j=0;
        for(j=0;j<6;j++){
            if (i>=400){     // 400 -> Sample time 50e-6, f=50Hz
                rms2[j] = Sum[j]*0.0025;    // Mean
                Sum[j] = 0.0;
            }
            Vi2[j] = Vi[j]*Vi[j];        // Square of the measurement
            Sum[j] = Vi2[j] + Sum[j];}
            rms_out.va_rms = rms2[0];
            rms_out.vb_rms = rms2[1];
            rms_out.vc_rms = rms2[2];
            rms_out.ia_rms = rms2[3];
            rms_out.ib_rms = rms2[4];
            rms_out.ic_rms = rms2[5];

        #if (wires == 3)
            if (i>=400){i=0;}     // 40 -> Sample time 50e-6, f=50Hz
            //if (SCH==3){
            rms_out.in_rms = 0;
            i++;//}
        #endif
	return rms_out;
}


#pragma CODE_SECTION(power_computation,"ramfuncs")

struct powers power_computation (struct ADC_conv ADC){
      struct powers p = {0,0};
      p.P3f = (ADC.V_a*ADC.I_a + ADC.V_b*ADC.I_b + ADC.V_c*ADC.I_c);
      p.Q3f = ((ADC.V_a-ADC.V_b)*ADC.I_c + (ADC.V_b-ADC.V_c)*ADC.I_a + (ADC.V_c-ADC.V_a)*ADC.I_b)/1.732050807568877;
    return p;
}

