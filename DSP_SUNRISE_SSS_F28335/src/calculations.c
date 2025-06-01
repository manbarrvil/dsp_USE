#include "DSP2833x_Device.h"
#include "DSP2833x_Examples.h"
#include "type_structs.h"
#include <math.h>

#pragma CODE_SECTION(rms_calculation,"ramfuncs")
struct rms rms_calculation(struct ADC_conv ADC)
{
    static struct rms rms_out;     // RMS output struct

    #if (wires == 3)
        double Vi[6]={0,0,0,0,0,0};            // ADC measurements
        double Vi2[6]={0,0,0,0,0,0};
        static double rms2[6]={0,0,0,0,0,0};           // RMS vector
        static double rms0[7]={0,0,0,0,0,0,0};         // Filtered RMS vector
        static double Sum[6]={0,0,0,0,0,0};
        unsigned int n_meas = 6;            // Length of ADC measurements
        Vi[0]=ADC.V_a;
        Vi[1]=ADC.V_b;
        Vi[2]=ADC.V_c;
        Vi[3]=ADC.I_a;
        Vi[4]=ADC.I_b;
        Vi[5]=ADC.I_c;
    #elif (wires == 4)
        double Vi[7]={0,0,0,0,0,0,0};
        double Vi2[7]={0,0,0,0,0,0,0};
        static double rms2[7]={0,0,0,0,0,0,0};
        static double Sum[7]={0,0,0,0,0,0,0};
        unsigned int n_meas = 7;
        Vi[0]=ADC.V_a;
        Vi[1]=ADC.V_b;
        Vi[2]=ADC.V_c;
        Vi[3]=ADC.I_a;
        Vi[4]=ADC.I_b;
        Vi[5]=ADC.I_c;
        Vi[6]=ADC.I_n;
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
        #elif (wires == 4)

                if (i>=400){     // 400 -> Sample time 50e-6, f=50Hz
                    rms2[6] = Sum[6]*0.0025;    // Mean
                    Sum[6] = 0.0;
                    i=0;
                }
                Vi2[6] = Vi[6]*Vi[6];        // Square of the measurement
                Sum[6] = Vi2[6] + Sum[6];
                rms_out.in_rms = rms2[6];
                i++;
        #endif
	return rms_out;
}


#pragma CODE_SECTION(power_calc,"ramfuncs")

struct powers power_computation (struct ADC_conv ADC){
    struct powers p = {0,0,0,0,0,0,0,0,0,0,0,0,0};
    static double Pa_ant = 0, Pb_ant = 0, Pc_ant = 0, Qa_ant = 0, Qb_ant = 0, Qc_ant = 0;
#if (CTRL == 2 || CTRL == 3)
    p.P3f = (ADC.V_a*ADC.I_a + ADC.V_b*ADC.I_b + ADC.V_c*ADC.I_c);
    p.Q3f = ((ADC.V_a-ADC.V_b)*ADC.I_c + (ADC.V_b-ADC.V_c)*ADC.I_a + (ADC.V_c-ADC.V_a)*ADC.I_b);
#else
    p.Pa = ADC.V_a*ADC.I_a;     p.Qa = 0.577350269189626*(ADC.V_b-ADC.V_c)*ADC.I_a;
    p.Pb = ADC.V_b*ADC.I_b;     p.Qb = 0.577350269189626*(ADC.V_c-ADC.V_a)*ADC.I_b;
    p.Pc = ADC.V_c*ADC.I_c;     p.Qc = 0.577350269189626*(ADC.V_a-ADC.V_b)*ADC.I_c;

    p.Pa = p.Pa*0.0005+0.9995*Pa_ant; p.Qa = p.Qa*0.0005+0.9995*Qa_ant;
    p.Pb = p.Pb*0.0005+0.9995*Pb_ant; p.Qb = p.Qb*0.0005+0.9995*Qb_ant;
    p.Pc = p.Pc*0.0005+0.9995*Pc_ant; p.Qc = p.Qc*0.0005+0.9995*Qc_ant;

    Pa_ant = p.Pa; Qa_ant = p.Qa;
    Pb_ant = p.Pb; Qb_ant = p.Qb;
    Pc_ant = p.Pc; Qc_ant = p.Qc;
#endif
    return p;
}

