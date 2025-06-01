#include "DSP2833x_Device.h"
#include "DSP2833x_Examples.h"
#include "type_structs.h"



// Setup ePWM
void Setup_ePWM()
{
	// Phase c
	EPwm1Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1; 		// TBCLK = SYSCLKOUT
    EPwm1Regs.TBCTL.bit.CLKDIV = TB_DIV2;
	EPwm1Regs.TBPRD = PWM_TIMER_TBPRD; 				// f = 10 kHz
	EPwm1Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; 	// up-down
	EPwm1Regs.TBCTR = 0x0000;						// Start counter

	// Synchronization

#if EXT_SYNC == 1  // EXTERNAL SYNC ON

	EPwm1Regs.TBPHS.half.TBPHS = 0x0000;			// Phase = 0
	EPwm1Regs.TBCTL.bit.PHSEN = TB_ENABLE; 		// Slave module
	EPwm1Regs.TBCTL.bit.PRDLD = TB_SHADOW;
	EPwm1Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN; 	// Sync down-stream module

#else	// EXTERNAL SYNC OFF

	EPwm1Regs.TBPHS.half.TBPHS = 0x0000;			// Phase = 0
	EPwm1Regs.TBCTL.bit.PHSEN = TB_DISABLE; 		// Master module
	EPwm1Regs.TBCTL.bit.PRDLD = TB_SHADOW;
	EPwm1Regs.TBCTL.bit.SYNCOSEL = TB_CTR_ZERO; 	// Sync down-stream module

#endif

	EPwm1Regs.CMPA.half.CMPA = 1000;
	EPwm1Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
	EPwm1Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
	EPwm1Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
	EPwm1Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;

	EPwm1Regs.AQCTLA.bit.CAU = AQ_CLEAR;
	EPwm1Regs.AQCTLA.bit.CAD = AQ_SET;
	EPwm1Regs.AQCTLB.bit.CBU = AQ_SET;
	EPwm1Regs.AQCTLB.bit.CBD = AQ_CLEAR;

	EPwm1Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;	// Dead-band configuration
	EPwm1Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;
	EPwm1Regs.DBCTL.bit.IN_MODE = DBA_ALL;
	EPwm1Regs.DBRED = EPWM_MIN_DB;
	EPwm1Regs.DBFED = EPWM_MIN_DB;

	// ---------------------------------------------------------------------- //

	// DC/DC
	EPwm2Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1; 		// TBCLK = SYSCLKOUT
    EPwm2Regs.TBCTL.bit.CLKDIV = TB_DIV2;
	EPwm2Regs.TBPRD = PWM_TIMER_TBPRD; 				// f = 10 kHz
	EPwm2Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; 	// up-down
	EPwm2Regs.TBCTR = 0x0000;						// Start counter

	// Synchronization
	/* ------------------------------------------------------------ */
	EPwm2Regs.TBPHS.half.TBPHS = 0x0000;			// Phase = 0
	EPwm2Regs.TBCTL.bit.PHSEN = TB_ENABLE; 			// Slave module
	EPwm2Regs.TBCTL.bit.PRDLD = TB_SHADOW;
	EPwm2Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN; 		// Sync flow-through
	/* ------------------------------------------------------------ */

	EPwm2Regs.CMPA.half.CMPA = 1000;
	EPwm2Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
	EPwm2Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
	EPwm2Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
	EPwm2Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;

	EPwm2Regs.AQCTLA.bit.CAU = AQ_CLEAR;
	EPwm2Regs.AQCTLA.bit.CAD = AQ_SET;
	EPwm2Regs.AQCTLB.bit.CBU = AQ_SET;
	EPwm2Regs.AQCTLB.bit.CBD = AQ_CLEAR;

	EPwm2Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;	// Dead-band configuration
	EPwm2Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;
	EPwm2Regs.DBCTL.bit.IN_MODE = DBA_ALL;
	EPwm2Regs.DBRED = EPWM_MIN_DB;
	EPwm2Regs.DBFED = EPWM_MIN_DB;
	// ---------------------------------------------------------------------- //

	// Phase a
	EPwm3Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1; 		// TBCLK = SYSCLKOUT
    EPwm3Regs.TBCTL.bit.CLKDIV = TB_DIV2;
	EPwm3Regs.TBPRD = PWM_TIMER_TBPRD; 				// f = 10 kHz
	EPwm3Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; 	// up-down
	EPwm3Regs.TBCTR = 0x0000;						// Start counter

	// Synchronization
	/* ------------------------------------------------------------ */
	EPwm3Regs.TBPHS.half.TBPHS = 0x0000;			// Phase = 0
	EPwm3Regs.TBCTL.bit.PHSEN = TB_ENABLE; 			// Slave module
	EPwm3Regs.TBCTL.bit.PRDLD = TB_SHADOW;
	EPwm3Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN; 		// Sync flow-through
	/* ------------------------------------------------------------ */

	EPwm3Regs.CMPA.half.CMPA = 1000;
	EPwm3Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
	EPwm3Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
	EPwm3Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
	EPwm3Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;

	EPwm3Regs.AQCTLA.bit.CAU = AQ_CLEAR;
	EPwm3Regs.AQCTLA.bit.CAD = AQ_SET;
	EPwm3Regs.AQCTLB.bit.CBU = AQ_SET;
	EPwm3Regs.AQCTLB.bit.CBD = AQ_CLEAR;

	EPwm3Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;	// Dead-band configuration
	EPwm3Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;
	EPwm3Regs.DBCTL.bit.IN_MODE = DBA_ALL;
	EPwm3Regs.DBRED = EPWM_MIN_DB;
	EPwm3Regs.DBFED = EPWM_MIN_DB;

	// ---------------------------------------------------------------------- //

	// Phase b
	EPwm4Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1; 		// TBCLK = SYSCLKOUT
    EPwm4Regs.TBCTL.bit.CLKDIV = TB_DIV2;
	EPwm4Regs.TBPRD = PWM_TIMER_TBPRD; 				// f = 10 kHz
	EPwm4Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; 	// up-down
	EPwm4Regs.TBCTR = 0x0000;						// Start counter

	// Synchronization
	/* ------------------------------------------------------------ */
	EPwm4Regs.TBPHS.half.TBPHS = 0x0000;			// Phase = 0
	EPwm4Regs.TBCTL.bit.PHSEN = TB_ENABLE; 			// Slave module
	EPwm4Regs.TBCTL.bit.PRDLD = TB_SHADOW;
	EPwm4Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN; 		// Sync Sync flow-through
	/* ------------------------------------------------------------ */

	EPwm4Regs.CMPA.half.CMPA = 1000;
	EPwm4Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
	EPwm4Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
	EPwm4Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
	EPwm4Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;

	EPwm4Regs.AQCTLA.bit.CAU = AQ_CLEAR;
	EPwm4Regs.AQCTLA.bit.CAD = AQ_SET;
	EPwm4Regs.AQCTLB.bit.CBU = AQ_SET;
	EPwm4Regs.AQCTLB.bit.CBD = AQ_CLEAR;

	EPwm4Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;	// Dead-band configuration
	EPwm4Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;
	EPwm4Regs.DBCTL.bit.IN_MODE = DBA_ALL;
	EPwm4Regs.DBRED = EPWM_MIN_DB;
	EPwm4Regs.DBFED = EPWM_MIN_DB;

	// ---------------------------------------------------------------------- //

	// Interrupt
	EPwm5Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1; 		// TBCLK = SYSCLKOUT
	EPwm5Regs.TBCTL.bit.CLKDIV = TB_DIV1;
	EPwm5Regs.TBPRD = PWM_TIMER_TBPRD; 				// f = 10 kHz
	EPwm5Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; 	// up-down
	EPwm5Regs.TBCTR = 0x0000;						// Start counter

	// Synchronization
	/* ------------------------------------------------------------ */
	EPwm5Regs.TBPHS.half.TBPHS = 0x0000;			// Phase = 0
	EPwm5Regs.TBCTL.bit.PHSEN = TB_ENABLE; 			// Slave module
	EPwm5Regs.TBCTL.bit.PRDLD = TB_SHADOW;
	EPwm5Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN; 		// Sync flow-through
	/* ------------------------------------------------------------ */

	EPwm5Regs.ETSEL.all = 0;
	EPwm5Regs.ETSEL.bit.SOCBEN  = 1;				// enable SOCB
	EPwm5Regs.ETSEL.bit.SOCAEN  = 1;				// enable SOCB
	EPwm5Regs.ETSEL.bit.SOCASEL = 1;				// Enable event time-base counter equal to zero. (TBCTR = 0x0000)
	EPwm5Regs.ETSEL.bit.SOCBSEL = 1;				// Enable event time-base counter equal to zero. (TBCTR = 0x0000)
	EPwm5Regs.ETSEL.bit.INTEN = 0;					// Disable ePWM interrupt

	EPwm5Regs.ETPS.all = 0;
	EPwm5Regs.ETPS.bit.SOCAPRD = 1;					// Generate SOCB on first event
	EPwm5Regs.ETPS.bit.SOCBPRD = 1;					// Generate SOCB on first event
	// ---------------------------------------------------------------------- //

}
