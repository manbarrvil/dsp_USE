#include "DSP2833x_Device.h"
#include "DSP2833x_Examples.h"
#include "type_structs.h"

// ADC Configuration
void Setup_ADC(void)
{

#if (DEVICE == 4) // TYPHOON

	AdcRegs.ADCTRL3.bit.SMODE_SEL = 0x0; // Setup sequential sampling mode
	AdcRegs.ADCMAXCONV.all = 0x0037; // 12 conversions in total (8 -> SEQ1 y 4 -> SEQ2)

	AdcRegs.ADCCHSELSEQ1.bit.CONV00 = 0x2; // Setup conv from ADCINA2
	AdcRegs.ADCCHSELSEQ1.bit.CONV01 = 0x8; // Setup conv from ADCINB0
	AdcRegs.ADCCHSELSEQ1.bit.CONV02 = 0x1; // Setup conv from ADCINA1
	AdcRegs.ADCCHSELSEQ1.bit.CONV03 = 0x0; // Setup conv from ADCINA0
	AdcRegs.ADCCHSELSEQ2.bit.CONV04 = 0xB; // Setup conv from ADCINB3
	AdcRegs.ADCCHSELSEQ2.bit.CONV05 = 0xC; // Setup conv from ADCINB4
	AdcRegs.ADCCHSELSEQ2.bit.CONV06 = 0xD; // Setup conv from ADCINB5
	AdcRegs.ADCCHSELSEQ2.bit.CONV07 = 0xE; // Setup conv from ADCINB6
	AdcRegs.ADCCHSELSEQ3.bit.CONV08 = 0xF; // Setup conv from ADCINB7
	AdcRegs.ADCCHSELSEQ3.bit.CONV09 = 0x3; // Setup conv from ADCINA3
	AdcRegs.ADCCHSELSEQ3.bit.CONV10 = 0x4; // Setup conv from ADCINA4
	AdcRegs.ADCCHSELSEQ3.bit.CONV11 = 0x5; // Setup conv from ADCINA5

    AdcRegs.ADCTRL2.all = 0;
    AdcRegs.ADCTRL2.bit.EPWM_SOCA_SEQ1 = 1;
    AdcRegs.ADCTRL2.bit.INT_ENA_SEQ1 = 1;
    AdcRegs.ADCTRL2.bit.EPWM_SOCB_SEQ2 = 1;
    AdcRegs.ADCTRL2.bit.INT_ENA_SEQ2 = 1;
#endif

}

// Calibration and conversion
#pragma CODE_SECTION(Conversion_ADC,"ramfuncs")
struct ADC_conv Conversion_ADC(Uint16 *ADC_read)
{
	struct ADC_conv s;
#if (DEVICE==4) // TYPHOON

//First operation: per unit. ADC_read/4096. Signal 0÷1
//Second operation: center signal at 0. Subtract -0.5 from the value per unit. Signal -0.5÷0.5
//Third operation: Rebuild analog signal value in Typhoon. Multiply by 10. Signal -5÷5 V
//Fourth operation: Apply Typhoon Conversion Scaling defined in the SCADA. 20 A/1V for AC current measurements. 100 V/1 V for AC  voltage measurements.
//Fifth operation: Offset and gain correction

	s.I_h = (double) ((ADC_read[9]*0.000244140625 - 0.5)*10*10 + OFF_IH)*GAIN_IH;	// I_h
    s.I_n = (double) ((ADC_read[10]*0.000244140625 - 0.5)*10*20 + OFF_IN)*GAIN_IN;  // I_n
	s.I_l = (double) ((ADC_read[0]*0.000244140625 - 0.5)*10*10 + OFF_IL)*GAIN_IL;	// I_l
	s.V_l = (double) ((ADC_read[2]*0.000244140625 - 0.5)*10*50 + OFF_VL)*GAIN_VL;	// V_l
	s.V_h = (double) ((ADC_read[1]*0.000244140625 - 0.5)*10*200 + OFF_VH)*GAIN_VH;	// V_h
	s.I_c = (double) ((ADC_read[3]*0.000244140625 - 0.5)*10*20 + OFF_IC)*GAIN_IC;	// I_c
	s.V_c = (double) ((ADC_read[4]*0.000244140625 - 0.5)*10*100 + OFF_VC)*GAIN_VC;	// V_c
	s.I_b = (double) ((ADC_read[5]*0.000244140625 - 0.5)*10*20 + OFF_IB)*GAIN_IB;	// I_b
	s.V_b = (double) ((ADC_read[6]*0.000244140625 - 0.5)*10*100 + OFF_VB)*GAIN_VB;	// V_b
	s.I_a = (double) ((ADC_read[7]*0.000244140625 - 0.5)*10*20 + OFF_IA)*GAIN_IA;	// I_a
	s.V_a = (double) ((ADC_read[8]*0.000244140625 - 0.5)*10*100 + OFF_VA)*GAIN_VA;	// V_a

#endif
	return s;

}



