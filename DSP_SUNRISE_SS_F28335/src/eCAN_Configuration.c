#include "DSP2833x_Device.h"
#include "DSP2833x_Examples.h"
#include "type_structs.h"

static long long read_register=0;
static int32 transmit0=0,transmit0_2=0,transmit1=0,transmit1_2=0,transmit2=0,transmit2_2=0,transmit3=0,transmit3_2=0,transmit4=0,transmit4_2=0,transmit5=0,transmit5_2=0;
struct CAN_read lecturas={0};


void MBXwrA(void) // Funcion para variar la RAM del eCAN A
{
	int j;
	volatile struct MBOX *Mailbox  = (void *) 0x6100;

	for(j=0; j<32; j++)
	{
		Mailbox->MSGID.all = 0;
		Mailbox->MSGCTRL.all = 0;
		Mailbox->MDH.all = 0;
		Mailbox->MDL.all = 0;
		Mailbox = Mailbox + 1;

	}
}

long long mailbox_read(int16 MBXnbr) // Funcion para leer las 4 palabras de que reciben en cada mailbox
{
   volatile struct MBOX *Mailbox;
   long long r;
   Mailbox = &ECanaMboxes.MBOX0 + MBXnbr;
   r = ((long long) (Mailbox->MDH.all)<<32)| ((long long) (Mailbox->MDL.all));
   return r;

} // MSGID of a rcv MBX is transmitted as the MDL data.


void Setup_eCAN(void)
{
	EALLOW;
	MBXwrA();
	EDIS;

	// Se configuran las ID para los mensajes que se envian
#if DEVICE == 5
    // Write
    ECanaMboxes.MBOX0.MSGID.bit.STDMSGID = 100;
    ECanaMboxes.MBOX1.MSGID.bit.STDMSGID = 101;
    ECanaMboxes.MBOX2.MSGID.bit.STDMSGID = 102;
    ECanaMboxes.MBOX3.MSGID.bit.STDMSGID = 103;
    ECanaMboxes.MBOX4.MSGID.bit.STDMSGID = 104;
    ECanaMboxes.MBOX5.MSGID.bit.STDMSGID = 105;
    //ECanaMboxes.MBOX6.MSGID.bit.STDMSGID = 106;


    // Se configuran las ID para los mensajes que se reciben
    ECanaMboxes.MBOX16.MSGID.bit.STDMSGID = 91;
    ECanaMboxes.MBOX17.MSGID.bit.STDMSGID = 92;
    ECanaMboxes.MBOX18.MSGID.bit.STDMSGID = 93;
    ECanaMboxes.MBOX19.MSGID.bit.STDMSGID = 94;
    ECanaMboxes.MBOX20.MSGID.bit.STDMSGID = 95;
    ECanaMboxes.MBOX21.MSGID.bit.STDMSGID = 96;

    // Los mensajes serán de 8 bytes
    ECanaMboxes.MBOX0.MSGCTRL.bit.DLC = 8;
    ECanaMboxes.MBOX1.MSGCTRL.bit.DLC = 8;
    ECanaMboxes.MBOX2.MSGCTRL.bit.DLC = 8;
    ECanaMboxes.MBOX3.MSGCTRL.bit.DLC = 8;
    ECanaMboxes.MBOX4.MSGCTRL.bit.DLC = 8;
    ECanaMboxes.MBOX5.MSGCTRL.bit.DLC = 8;
    ECanaMboxes.MBOX6.MSGCTRL.bit.DLC = 8;
    ECanaMboxes.MBOX16.MSGCTRL.bit.DLC = 8;
    ECanaMboxes.MBOX17.MSGCTRL.bit.DLC = 8;
    ECanaMboxes.MBOX18.MSGCTRL.bit.DLC = 8;
    ECanaMboxes.MBOX19.MSGCTRL.bit.DLC = 8;
    ECanaMboxes.MBOX20.MSGCTRL.bit.DLC = 8;
    ECanaMboxes.MBOX21.MSGCTRL.bit.DLC = 8;

#elif DEVICE == 6
    // Write
    ECanaMboxes.MBOX0.MSGID.bit.STDMSGID = 120;
    ECanaMboxes.MBOX1.MSGID.bit.STDMSGID = 121;
    ECanaMboxes.MBOX2.MSGID.bit.STDMSGID = 122;
    ECanaMboxes.MBOX3.MSGID.bit.STDMSGID = 123;
    ECanaMboxes.MBOX4.MSGID.bit.STDMSGID = 124;
    ECanaMboxes.MBOX5.MSGID.bit.STDMSGID = 125;
    //ECanaMboxes.MBOX6.MSGID.bit.STDMSGID = 126;


    // Se configuran las ID para los mensajes que se reciben
    ECanaMboxes.MBOX16.MSGID.bit.STDMSGID = 111;
    ECanaMboxes.MBOX17.MSGID.bit.STDMSGID = 112;
    ECanaMboxes.MBOX18.MSGID.bit.STDMSGID = 113;
    ECanaMboxes.MBOX19.MSGID.bit.STDMSGID = 114;
    ECanaMboxes.MBOX20.MSGID.bit.STDMSGID = 115;

    // Los mensajes serán de 8 bytes
    ECanaMboxes.MBOX0.MSGCTRL.bit.DLC = 8;
    ECanaMboxes.MBOX1.MSGCTRL.bit.DLC = 8;
    ECanaMboxes.MBOX2.MSGCTRL.bit.DLC = 8;
    ECanaMboxes.MBOX3.MSGCTRL.bit.DLC = 8;
    ECanaMboxes.MBOX4.MSGCTRL.bit.DLC = 8;
    ECanaMboxes.MBOX5.MSGCTRL.bit.DLC = 8;
    ECanaMboxes.MBOX6.MSGCTRL.bit.DLC = 8;
    ECanaMboxes.MBOX16.MSGCTRL.bit.DLC = 8;
    ECanaMboxes.MBOX17.MSGCTRL.bit.DLC = 8;
    ECanaMboxes.MBOX18.MSGCTRL.bit.DLC = 8;
    ECanaMboxes.MBOX19.MSGCTRL.bit.DLC = 8;
    ECanaMboxes.MBOX20.MSGCTRL.bit.DLC = 8;

#elif (DEVICE == 4)
    ECanaMboxes.MBOX0.MSGID.bit.STDMSGID = 10;
    ECanaMboxes.MBOX1.MSGID.bit.STDMSGID = 11;
    ECanaMboxes.MBOX2.MSGID.bit.STDMSGID = 12;
    ECanaMboxes.MBOX3.MSGID.bit.STDMSGID = 13;
    ECanaMboxes.MBOX4.MSGID.bit.STDMSGID = 14;
    ECanaMboxes.MBOX5.MSGID.bit.STDMSGID = 15;
    //ECanaMboxes.MBOX6.MSGID.bit.STDMSGID = 16;


    // Se configuran las ID para los mensajes que se reciben
    ECanaMboxes.MBOX16.MSGID.bit.STDMSGID = 1;
    ECanaMboxes.MBOX17.MSGID.bit.STDMSGID = 2;
    ECanaMboxes.MBOX18.MSGID.bit.STDMSGID = 3;
    ECanaMboxes.MBOX19.MSGID.bit.STDMSGID = 4;
    ECanaMboxes.MBOX20.MSGID.bit.STDMSGID = 5;
    ECanaMboxes.MBOX21.MSGID.bit.STDMSGID = 96;



    // Los mensajes serán de 8 bytes
    ECanaMboxes.MBOX0.MSGCTRL.bit.DLC = 8;
    ECanaMboxes.MBOX1.MSGCTRL.bit.DLC = 8;
    ECanaMboxes.MBOX2.MSGCTRL.bit.DLC = 8;
    ECanaMboxes.MBOX3.MSGCTRL.bit.DLC = 8;
    ECanaMboxes.MBOX4.MSGCTRL.bit.DLC = 8;
    ECanaMboxes.MBOX5.MSGCTRL.bit.DLC = 8;
    //CanaMboxes.MBOX6.MSGCTRL.bit.DLC = 8;
    ECanaMboxes.MBOX16.MSGCTRL.bit.DLC = 8;
    ECanaMboxes.MBOX17.MSGCTRL.bit.DLC = 8;
    ECanaMboxes.MBOX18.MSGCTRL.bit.DLC = 8;
    ECanaMboxes.MBOX19.MSGCTRL.bit.DLC = 8;
    ECanaMboxes.MBOX20.MSGCTRL.bit.DLC = 8;
    ECanaMboxes.MBOX21.MSGCTRL.bit.DLC = 8;

#endif

	//Establece el orden de los bytes de la RAM asociada a mensajes que se transmiten
	EALLOW;
	ECanaRegs.CANMC.bit.DBO = 1;

	// Mailboxes 0-15 para escribir, mailboxes 16-31 para recibir
	ECanaRegs.CANMD.all = 0xFFFF0000;

	// Activa todos los mailboxes
	ECanaRegs.CANME.all = 0xFFFFFFFF;

	// Auto-Bus ON (CAN recovers automatically after too many errors in communication)
	ECanaRegs.CANMC.bit.ABO = 1;
	EDIS;

	// Habilita las interrupciones de los mailboxes

//	EALLOW;
//	ECanaRegs.CANMIM.all = 0x003F003F;
//	EDIS;

}

//#pragma CODE_SECTION (eCAN_RW,"ramfuncs")
struct CAN_read eCAN_RW(struct ADC_conv ADC_processed, struct rms rms_calc, struct powers p, struct PLL_output PLL_Park, struct state_m state)

{
	// Write to the mailbox RAM field of MBOX0 - 15

    transmit0=      (((int32)(ADC_processed.V_h*10))&0x0000FFFF)|(((int32)(state.Fault_Type)<<16)&0xFFFF0000);
    transmit0_2=    (((int32)(p.P3f))&0x0000FFFF)|(((int32)(p.Q3f)<<16)&0xFFFF0000);

    transmit1=      (((int32)(PLL_Park.V_d*10))&0x0000FFFF)|(((int32)(PLL_Park.V_q*10)<<16)&0xFFFF0000);
    transmit1_2=    (((int32)(PLL_Park.I_d*100))&0x0000FFFF)|(((int32)(PLL_Park.I_q*100)<<16)&0xFFFF0000);

    transmit2=      (((int32)(rms_calc.va_rms/2.0))&0x0000FFFF)|(((int32)(rms_calc.vb_rms/2.0)<<16)&0xFFFF0000);
    transmit2_2=    (((int32)(rms_calc.vc_rms/2.0))&0x0000FFFF)|(((int32)(testID)<<16)&0xFFFF0000);

    transmit3=      (((int32)(rms_calc.ia_rms*10/2.0))&0x0000FFFF)|(((int32)(rms_calc.ib_rms*10/2.0)<<16)&0xFFFF0000);
    transmit3_2=    (((int32)(rms_calc.ic_rms*10/2.0))&0x0000FFFF)|(((int32)(rms_calc.in_rms*10/2.0)<<16)&0xFFFF0000);

	transmit4=		(((int32)(ADC_processed.V_l*10))&0x0000FFFF)|(((int32)(ADC_processed.I_l*100)<<16)&0xFFFF0000);
	transmit4_2=0;

	transmit5=		(((int32)(PLL_Park.omega))&0x0000FFFF)|(((int32)(0)<<16)&0xFFFF0000);
	transmit5_2=	(((int32)(ADC_processed.I_h*100))&0x0000FFFF)|(((int32)(0)<<16)&0xFFFF0000);

	//transmit6=		(((int32)(p.p_pri_fil))&0x0000FFFF)|(((int32)(p.p_pri_fil)<<16)&0xFFFF0000);
	//transmit6_2=	(((int32)(p.p_losses))&0x0000FFFF)|(((int32)(p.p_HFPS)<<16)&0xFFFF0000);

	ECanaMboxes.MBOX0.MDL.all = transmit0; 		// Primeros 32 bits
	ECanaMboxes.MBOX0.MDH.all = transmit0_2;	// Ultimos 32 bits

	ECanaMboxes.MBOX1.MDL.all = transmit1;
	ECanaMboxes.MBOX1.MDH.all = transmit1_2;

	ECanaMboxes.MBOX2.MDL.all = transmit2;
	ECanaMboxes.MBOX2.MDH.all = transmit2_2;

	ECanaMboxes.MBOX3.MDL.all = transmit3;
	ECanaMboxes.MBOX3.MDH.all = transmit3_2;

	ECanaMboxes.MBOX4.MDL.all = transmit4;
	ECanaMboxes.MBOX4.MDH.all = transmit4_2;

	ECanaMboxes.MBOX5.MDL.all = transmit5;
	ECanaMboxes.MBOX5.MDH.all = transmit5_2;

	//ECanaMboxes.MBOX6.MDL.all = transmit6;
	//ECanaMboxes.MBOX6.MDH.all = transmit6_2;

	// Da la orden de transmitir los valores en RAM
	ECanaRegs.CANTA.all = 0x0000006F;   // Clear all TAn
	ECanaRegs.CANTRS.all = 0x0000006F;  // Da la orden de mandar a los 7 mailboxes de transmision

	// Se lee y se asigna el contenido de cada uno de los mailbox de recepcion

	read_register=mailbox_read(16);

	lecturas.start_FSM=read_register & 0x1;
	lecturas.start_AC=(read_register & 0x2)>>1;
	/*lecturas.start_DC=(read_register & 0x4)>>2;
	lecturas.sync=(read_register & 0x8)>>3;
	lecturas.enable_P_ref=(read_register & 0x10)>>4;
	lecturas.enable_HFPS=(read_register & 0x20)>>5;
	// lecturas.enable_resonant=(read_register & 0x40)>>6;
	lecturas.start_Primary=(read_register & 0x80)>>7;*/

	read_register=mailbox_read(17);

	lecturas.etas=((signed int)(read_register & 0xFFFF))*0.001;
	//lecturas.eta_dc=((signed int)(read_register>>16 & 0xFFFF))*0.001;
	lecturas.i_d_ref=((signed int)(read_register>>32 & 0xFFFF))*0.1;
	lecturas.i_q_ref=((signed int)(read_register>>48 & 0xFFFF))*0.1;

	read_register=mailbox_read(18);
	/*lecturas.V_h_min=((signed int)(read_register & 0xFFFF));
	lecturas.V_pk_min=((signed int)(read_register>>16 & 0xFFFF));
	lecturas.I_pk_max=((signed int)(read_register>>32 & 0xFFFF));
	lecturas.I_l_max=((signed int)(read_register>>48 & 0xFFFF));*/

	read_register=mailbox_read(19);
	lecturas.P_pu_ref=((signed int)(read_register & 0xFFFF))*0.001;
	lecturas.Q_pu_ref=((signed int)(read_register>>16 & 0xFFFF))*0.001;
	//lecturas.H=((signed int)(read_register>>32 & 0xFFFF));

	read_register=mailbox_read(20);

	lecturas.V_h_ref=(signed int)(read_register & 0xFFFF);
	//lecturas.V_uc_ref=(signed int)(read_register>>16 & 0xFFFF);
	lecturas.Pa_ref= ((signed int)(read_register>>32 & 0xFFFF));
    lecturas.Qa_ref= ((signed int)(read_register>>48 & 0xFFFF));

    read_register=mailbox_read(21);

    lecturas.Pb_ref=(signed int)(read_register & 0xFFFF);
    lecturas.Qb_ref=(signed int)(read_register>>16 & 0xFFFF);
    lecturas.Pc_ref= ((signed int)(read_register>>32 & 0xFFFF));
    lecturas.Qc_ref= ((signed int)(read_register>>48 & 0xFFFF));

	return lecturas;

}
