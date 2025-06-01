#include "DSP2833x_Device.h"
#include "DSP2833x_Examples.h"
#include "type_structs.h"

#pragma CODE_SECTION (state_mach,"ramfuncs")

//struct state_m state_mach(struct ADC_conv ADC_p, struct rms rms_v, double runFSM, double driver_fault, double V_q, double omega, struct CAN_read limites)
struct state_m state_mach(struct ADC_conv ADC_p, struct rms rms_v, double runFSM, double driver_fault, double V_q, double omega, struct references limites)

{
	// Static variables
	static double Fault_Type_in = 0;
	static double Reset_Drivers_in = 0;

	// Structures
	struct state_m s;
//0 There is no type of fault and the system enables the VSC to operate
//1 Overcurrent in the current injected by the VSC to the grid
//2 Grid Undervoltages
//3 Grid Overvoltages
//4 Grid Underfrequency
//5 Grid Overfrequency
//6 IGBTs driver fault
//7
//8
//9 Waiting to enable the state machine
//10 Bus DC undervoltage
//11 Bus DC overvoltage
//12 DC/DC converter undervoltage
//13 DC/DC converter overvoltage
//14 DC/DC converter overcurrent

	if ( (limites.start_FSM == 1.0) && (Fault_Type_in == 0.0) )
	{
		// DC Side
		if (ADC_p.V_h > V_h_min)
		{
			if (ADC_p.V_h < V_h_max)
			{
							if ( (fabs(ADC_p.I_a) < I_pk_max) && (fabs(ADC_p.I_b) < I_pk_max) && (fabs(ADC_p.I_c) < I_pk_max) && (fabs(ADC_p.I_n) < I_pk_max) )
							{
								if ( (rms_v.va_rms > V_pk_min) && (rms_v.vb_rms > V_pk_min) && (rms_v.vc_rms > V_pk_min ))
								{
									if ( (rms_v.va_rms < V_pk_max) && (rms_v.vb_rms < V_pk_max) && (rms_v.vc_rms < V_pk_max ))
									{
										if ( omega > omega_min )
										{
											if ( omega < omega_max )
											{
												if ( driver_fault == 0.0)
												{
												    /*if (((wires == 4)) || (wires == 3))
                                                        {*/
                                                        s.PWM_enabled = 1.0;
                                                        s.Fault_Type = 0.0;
                                                        s.Reset_Drivers = 0.0;
                                                        /*}
												    else
												    {
						                                s.PWM_enabled = 0.0;
						                                s.Fault_Type = 1.0;
						                                s.Reset_Drivers = 0.0;
												    }*/
												}
												else
												{
													s.PWM_enabled = 0.0;
													s.Fault_Type = 6.0;
													s.Reset_Drivers = 1.0;
												}
											}
											else
											{
												s.PWM_enabled = 0.0;
												s.Fault_Type = 5.0;
												s.Reset_Drivers = 0.0;
											}
										}

										else
										{
											s.PWM_enabled = 0.0;
											s.Fault_Type = 4.0;
											s.Reset_Drivers = 0.0;
										}
									}
									else
									{
										s.PWM_enabled = 0.0;
										s.Fault_Type = 3.0;
										s.Reset_Drivers = 0.0;
									}
								}
								else
								{
									s.PWM_enabled = 0.0;
									s.Fault_Type = 2.0;
									s.Reset_Drivers = 0.0;
								}
							}
							else
							{
								s.PWM_enabled = 0.0;
								s.Fault_Type = 1.0;
								s.Reset_Drivers = 0.0;
							}


			}
			else
			{
				s.PWM_enabled = 0.0;
				s.Fault_Type = 11.0;
				s.Reset_Drivers = 0.0;
			}
		}
		else
		{
			s.PWM_enabled = 0.0;
			s.Fault_Type = 10.0;
			s.Reset_Drivers = 0.0;
		}
	}
	else if ( limites.start_FSM == 0.0 )
	{
		s.PWM_enabled = 0.0;
		s.Fault_Type = 9.0;
		s.Reset_Drivers = 0.0;
	}

	else if ( (limites.start_FSM == 1.0) && (Fault_Type_in == 9.0) )
	{
		s.PWM_enabled = 0.0;
		s.Fault_Type = 0.0;
		s.Reset_Drivers = 0.0;
	}


	else
	{
		s.PWM_enabled = 0.0;
		s.Fault_Type = Fault_Type_in;
		s.Reset_Drivers = Reset_Drivers_in;
	}

	// Refresh static variables
	Fault_Type_in = s.Fault_Type;
	Reset_Drivers_in = s.Reset_Drivers;

	// Return structure
	return s;

}




