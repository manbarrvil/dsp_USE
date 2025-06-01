// Libraries
#include "DSP28x_Project.h"
#include "type_structs.h"
#include <string.h>

// Constants. Interruptions
#define SEQ1_ADC_INT_ENABLE     1
#define SEQ2_ADC_INT_ENABLE     1


// Peripherals
interrupt void adc_SEQ1_isr(void);                                                                          // ADC Interrupt SEQ1
interrupt void adc_SEQ2_isr(void);                                                                          // ADC Interrupt SEQ2
void Setup_ePWM(void);                                                                                      // ePWM Configuration
void Setup_DMA(Uint16 *ADC_read, Uint16 *duty);                                                             // DMA Configuration
void Setup_ADC(void);                                                                                       // ADC Configuration
struct ADC_conv Conversion_ADC(Uint16 *ADC_read);                                                           // ADC Conversion
//void Setup_eCAN(void);                                                                                      // eCAN Configuration
void MBXwrA(void);                                                                                          // This function initializes all 32 MBOXes of CAN-A
long long mailbox_read(int16);                                                                              // Reads the message in a specified mailbox
//struct CAN_read eCAN_RW(struct ADC_conv, struct rms rms_calc, struct powers power, struct PLL_output, struct state_m);
void Setup_GPIO(void);                                                                                      // GPIO Configuration

// Memory addresses needed to copy code from Flash to RAM
extern unsigned int RamfuncsLoadStart;
extern unsigned int RamfuncsLoadEnd;
extern unsigned int RamfuncsLoadEnd;
extern unsigned int RamfuncsRunStart;

// Control functions based on PLL: Outputs are structure duty_cycle. Bold name of the function. Parenthesis (input of the function)
struct duty_cycle DQSTATCOM_comp(struct ADC_conv ADC_p, struct PLL_output PLL_dq, double vh_ref, double Q_ref, int flag);
struct duty_cycle DQCURRENT_comp(struct ADC_conv ADC_p, struct PLL_output PLL_dq, double i_d_ref, double i_q_ref, int flag);
struct duty_cycle DQPOWER_comp(struct ADC_conv ADC_p, struct PLL_output PLL_dq,  double P_ref, double Q_ref, int flag);

// Control functions based on VSG: Outputs are structure duty_cycle. Bold name of the function. Parenthesis (input of the function)
//struct uvsg VSG_comp(double enable_P_ref, double P_pu_ref, double Q_pu_ref, struct ADC_conv ADC_p, struct PLL_output PLL_Park, double runFSM);
struct uvsg VSG_comp(double P_ref, double Q_ref, struct ADC_conv ADC_p, struct PLL_output PLL_Park, double runFSM);

// PLL & Park transformation fucntions
struct PLL_output PLL_dq(struct ADC_conv, struct uvsg u, int startAC);     // PLL and Park transformation. Output structure PLL_dq
struct duty_cycle Park_inverse(struct PLL_output, struct duty_cycle);      // Park Inverse. Output duty_cycle

// Fault State Machine (FSM)
void enable_ePWM(int enableAC);  // Enable/Disable ePWM. Input is enable AC from
//struct state_m state_mach(struct ADC_conv ADC_p, struct rms rms_v, double runFSM, double driver_fault, double V_q, double omega, struct CAN_read limites);  // State machine
struct state_m state_mach(struct ADC_conv ADC_p, struct rms rms_v, double runFSM, double driver_fault, double V_q, double omega, struct references limites);  // State machine

void reset_drivers(int reset); //Reset drivers

// Auxiliary computations
struct powers power_computation (struct ADC_conv ADC); // Powers Calculation
struct rms rms_calculation(struct ADC_conv); // RMS Calculation

// Global variables
#pragma DATA_SECTION(ADC_read,"DMARAML4");
Uint16 ADC_read[12];                // ADC Registers
#pragma DATA_SECTION(duty,"DMARAML4");
Uint16 duty[4];
//struct powers p={0,0,0,0,0,0,0,0,0,0,0,0,0};
struct powers p={0,0,0};
//struct powers p_f={0,0,0,0,0,0,0,0,0,0,0,0,0};
float buffer[400];
int buffer_counter=0, selector;
//double etas=0;
//struct CAN_read consignas = {0,0,0,0,0,0,0,600,0,0,0,0,0,0,0};
                             //4,800,280,90,180,580,30,30,200,
                             //280,380,30};
struct references setpoints = {0,0,0,0,0,0,600}; //start_FSM, start_AC,id_ref,iq_ref,p_ref,q_ref,vh_ref
long long read_register;
int ADC_counter=0;
struct rms rms_values;
struct ADC_conv ADC_processed;
struct PLL_output PLL_Park= (const struct PLL_output){0}; //Input in function DQCURRENT_comp. Assingned as structure PLL_output
struct uvsg uvsg_out= {0,0,0,0,0,0,0,0,1,0,0,0,0,0};
struct duty_cycle eta;
struct state_m state;


// Main function
void main(void)
{
    // DSP Initialization
    InitSysCtrl();

    EALLOW;
    SysCtrlRegs.MAPCNF.bit.MAPEPWM = 1; // Enables ePWM remap to Peripheral Frame 3 (accessible by DMA)
    EDIS;

    // Location of the memory from the flash to the RAM
    memcpy(&RamfuncsRunStart, &RamfuncsLoadStart, &RamfuncsLoadEnd - &RamfuncsLoadStart);

    // Initialization of the flash memory
    InitFlash();

    // Define ADCCLK clock frequency to 25 MHz
    EALLOW;
    SysCtrlRegs.HISPCP.all = 0x3; // 25 MHz
    EDIS;

    // GPIOs Initialization and Configuration
    InitGpio();
    Setup_GPIO();

    // Disable Interrupts
    DINT;

    // PIE Initialization
    InitPieCtrl();

    // Disable interrupts flags
    IER = 0x0000;
    IFR = 0x0000;

    // PIE Initializations with ISR
    InitPieVectTable();

    // Mapping interrupts to ISR
    EALLOW;
    PieVectTable.SEQ1INT = &adc_SEQ1_isr;
    PieVectTable.SEQ2INT = &adc_SEQ2_isr;
    EDIS;

    // DMA Init
    DMAInitialize();
    Setup_DMA(ADC_read, duty);

    // ADC Initialization
    InitAdc();
    Setup_ADC();

    // PIE Interrupts
    PieCtrlRegs.PIEIER1.bit.INTx1 = SEQ1_ADC_INT_ENABLE;
    PieCtrlRegs.PIEIER1.bit.INTx2 = SEQ2_ADC_INT_ENABLE;

    // ePWM Initialization
    EALLOW;
    SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 0;
    EDIS;

    Setup_ePWM();

    EALLOW;
    SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 1;
    EDIS;

    // eCAN Initialization
//    InitECana(); // Initialize eCAN-A module
//    InitECanGpio();
//    Setup_eCAN();

    // Enable Interrupt groups 1/3 that corresponds to ePWM and ADC
    IER |= M_INT3;
    IER |= M_INT1;

    // Enable Interrupts
    EINT;
    ERTM;

    // Loop forever
    while(1)    {
        if (ADC_counter >2000){
            ADC_counter=0;

// Uncomment if CAN parameters are wanted in debug for TYPHOON
//#if DEVICE != 4 //|| DEVICE =! 11
//            consignas=eCAN_RW(ADC_processed, rms_values, p, PLL_Park, state);
//#endif

        }

    }

}

// ADC Interrupt 1
#pragma CODE_SECTION(adc_SEQ1_isr,"ramfuncs")
interrupt void adc_SEQ1_isr(void)
{
    // Reinitialize for next ADC sequence
    AdcRegs.ADCTRL2.bit.RST_SEQ1 = 1;
    AdcRegs.ADCST.bit.INT_SEQ1_CLR = 1;
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}


// ADC Interrupt 2
#pragma CODE_SECTION(adc_SEQ2_isr,"ramfuncs")
interrupt void adc_SEQ2_isr(void)
{
    ADC_counter++;

// Typhoon activates GIPO12 for enabling switching the VSC
#if DEVICE == 4
    if(GpioDataRegs.GPADAT.bit.GPIO12==0){GpioDataRegs.GPASET.bit.GPIO12=1;}
            else{GpioDataRegs.GPACLEAR.bit.GPIO12=1;}
#endif

// Calibration. Input ADC_read.  Analog channels reading
    ADC_processed = Conversion_ADC(ADC_read);
// rms computation. Input ADC converts to Volts and Amps
    rms_values = rms_calculation(ADC_processed);
// power computation
    #if (CTRL == 2 || CTRL == 3 || CTRL == 5|| CTRL == 11)
        p = power_computation(ADC_processed);
    #endif
// PLL and Park transformation. Execution of the functon PLL_dq in PLL_Park_transformations.c
    //PLL_Park = PLL_dq(ADC_processed,uvsg_out,consignas.start_AC);
    PLL_Park = PLL_dq(ADC_processed,uvsg_out,setpoints.start_AC);

// State machine
    #if (CTRL == 2 || CTRL == 3 || CTRL == 4 || CTRL == 11)
        //state = state_mach(ADC_processed, rms_values, consignas.start_FSM, 0, PLL_Park.V_q, PLL_Park.omega, consignas);
        state = state_mach(ADC_processed, rms_values, setpoints.start_FSM, 0, PLL_Park.V_q, PLL_Park.omega, setpoints);
    #elif (CTRL == 5)
    //state = state_mach(ADC_processed, rms_values, consignas.start_FSM, 0, PLL_Park.V_q, uvsg_out.omega, consignas);
    state = state_mach(ADC_processed, rms_values, setpoints.start_FSM, 0, PLL_Park.V_q, uvsg_out.omega, setpoints);
    #else
        state.PWM_enabled=1;
    #endif
    #if (FSM == 0)
            state.PWM_enabled=1;
    #endif
// enable/disable ePWM
    //enable_ePWM(state.PWM_enabled && consignas.start_AC);
    enable_ePWM(state.PWM_enabled && setpoints.start_AC);
    // Driver reset
    reset_drivers(state.Reset_Drivers);

    #if (CTRL == 2)   // dq current controller based on PLL
        //eta=DQCURRENT_comp(ADC_processed, PLL_Park, consignas.i_d_ref, consignas.i_q_ref, state.PWM_enabled && consignas.start_AC);
        eta=DQCURRENT_comp(ADC_processed, PLL_Park, setpoints.id_ref, setpoints.iq_ref, state.PWM_enabled && setpoints.start_AC);

    #elif (CTRL == 3)  // dq power controller based on PLL
        //eta=DQPOWER_comp(ADC_processed, PLL_Park, consignas.P_pu_ref, consignas.Q_pu_ref, state.PWM_enabled && consignas.start_AC);
        eta=DQPOWER_comp(ADC_processed, PLL_Park, setpoints.p_ref, setpoints.q_ref, state.PWM_enabled && setpoints.start_AC);

    #elif (CTRL == 11)   // dq statcom controller based on PLL
        //eta=DQSTATCOM_comp(ADC_processed, PLL_Park, consignas.V_h_ref, consignas.Q_pu_ref, state.PWM_enabled && consignas.start_AC);
        eta=DQSTATCOM_comp(ADC_processed, PLL_Park, setpoints.vdc_ref, setpoints.q_ref, state.PWM_enabled && setpoints.start_AC);

    #endif

    #if (CTRL == 5)   // PI-CC
        //uvsg_out = VSG_comp(consignas.enable_P_ref, consignas.P_pu_ref, consignas.Q_pu_ref, ADC_processed, PLL_Park, state.PWM_enabled && consignas.start_AC);
        uvsg_out = VSG_comp(setpoints.p_ref, setpoints.q_ref, ADC_processed, PLL_Park, state.PWM_enabled && setpoints.start_AC);
        //p.P3f=uvsg_out.p_s*20000;
        //p.Q3f=uvsg_out.q_s*20000;
        //eta=DQCURRENT_comp(ADC_processed, PLL_Park,  uvsg_out.i_d_ref, uvsg_out.i_q_ref, state.PWM_enabled && consignas.start_AC);
        eta=DQCURRENT_comp(ADC_processed, PLL_Park, uvsg_out.i_d_ref, uvsg_out.i_d_ref, state.PWM_enabled && setpoints.start_AC);


    #endif

 // Establishing the comparison values
 // carrier based PWM
        duty[0]=(int) PWM_TIMER_TBPRD*((eta.eta_c+1)*0.5);
        duty[2]=(int) PWM_TIMER_TBPRD*((eta.eta_a+1)*0.5);
        duty[3]=(int) PWM_TIMER_TBPRD*((eta.eta_b+1)*0.5);
#if wires == 3
        duty[1]=0;
#else
        duty[1]=(int) PWM_TIMER_TBPRD*((eta.eta_n+1)*0.5);
#endif

// Reinitialize for next ADC sequence
    AdcRegs.ADCTRL2.bit.RST_SEQ2 = 1;
    AdcRegs.ADCST.bit.INT_SEQ2_CLR = 1;
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}




