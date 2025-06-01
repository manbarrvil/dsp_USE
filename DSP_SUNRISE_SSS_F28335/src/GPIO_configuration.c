#include "DSP2833x_Device.h"
#include "DSP2833x_Examples.h"
#include "type_structs.h"

// GPIO Configuration
void Setup_GPIO(void)
{
#if (DEVICE == 4)       // TYPHOON
	EALLOW;
	// Phase a: ePWM3
	GpioCtrlRegs.GPAPUD.bit.GPIO4 = 0;
	GpioCtrlRegs.GPAPUD.bit.GPIO5 = 0;
	GpioCtrlRegs.GPAMUX1.bit.GPIO4 = 1;
	GpioCtrlRegs.GPAMUX1.bit.GPIO5 = 1;
	// Phase b: ePWM4
	GpioCtrlRegs.GPAPUD.bit.GPIO6 = 0;
	GpioCtrlRegs.GPAPUD.bit.GPIO7 = 0;
	GpioCtrlRegs.GPAMUX1.bit.GPIO6 = 1;
	GpioCtrlRegs.GPAMUX1.bit.GPIO7 = 1;
	// Phase c: ePWM1
	GpioCtrlRegs.GPAPUD.bit.GPIO0 = 0;
	GpioCtrlRegs.GPAPUD.bit.GPIO1 = 0;
	GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 1;
	GpioCtrlRegs.GPAMUX1.bit.GPIO1 = 1;
	// Phase n:   ePWM2
	GpioCtrlRegs.GPAPUD.bit.GPIO2 = 0;
	GpioCtrlRegs.GPAPUD.bit.GPIO3 = 0;
	GpioCtrlRegs.GPAMUX1.bit.GPIO2 = 1;
	GpioCtrlRegs.GPAMUX1.bit.GPIO3 = 1;
	// Enable/disable
	GpioCtrlRegs.GPAMUX1.bit.GPIO10 = 0;
	GpioCtrlRegs.GPADIR.bit.GPIO10 = 1;
	GpioCtrlRegs.GPAMUX1.bit.GPIO11 = 0;
	GpioCtrlRegs.GPADIR.bit.GPIO11 = 1;
	GpioCtrlRegs.GPAMUX1.bit.GPIO12 = 0;
	GpioCtrlRegs.GPADIR.bit.GPIO12 = 1;
	GpioCtrlRegs.GPBMUX2.bit.GPIO61 = 0;
	GpioCtrlRegs.GPBDIR.bit.GPIO61 = 1;
	EDIS;
	// Execution time
    GpioCtrlRegs.GPAMUX1.bit.GPIO14 = 0;
    GpioCtrlRegs.GPADIR.bit.GPIO14 = 1;

#endif
}

#pragma CODE_SECTION (enable_ePWM,"ramfuncs")
void enable_ePWM(int enableAC, int enableDC)
{


#if (DEVICE == 4)		// TYPHOON

	if (enableAC == 1)	{
		GpioDataRegs.GPASET.bit.GPIO11 = 1;

		//GpioDataRegs.GPBSET.bit.GPIO61 = 1;
	}else{
		GpioDataRegs.GPACLEAR.bit.GPIO11 = 1;
		//GpioDataRegs.GPBCLEAR.bit.GPIO61 = 1;
	}

#endif
}

#pragma CODE_SECTION (reset_drivers,"ramfuncs")
void reset_drivers(int reset)


{
#if (DEVICE == 5 || DEVICE == 6) // VSC
    if (reset == 1){
        GpioDataRegs.GPASET.bit.GPIO10 = 1;
    }
    else{
        GpioDataRegs.GPACLEAR.bit.GPIO10 = 1;
    }
#endif

}

