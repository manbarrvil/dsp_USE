################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/ti/ccs1260/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./src/ADC_configuration.obj" \
"./src/DMA_configuration.obj" \
"./src/DSP2833x_ADC_cal.obj" \
"./src/DSP2833x_Adc.obj" \
"./src/DSP2833x_CodeStartBranch.obj" \
"./src/DSP2833x_CpuTimers.obj" \
"./src/DSP2833x_DMA.obj" \
"./src/DSP2833x_DefaultIsr.obj" \
"./src/DSP2833x_ECan.obj" \
"./src/DSP2833x_GlobalVariableDefs.obj" \
"./src/DSP2833x_Gpio.obj" \
"./src/DSP2833x_PieCtrl.obj" \
"./src/DSP2833x_PieVect.obj" \
"./src/DSP2833x_SysCtrl.obj" \
"./src/DSP2833x_usDelay.obj" \
"./src/GPIO_configuration.obj" \
"./src/PLL_Park_transformations.obj" \
"./src/State_machine.obj" \
"./src/calculations.obj" \
"./src/dq_current_ctrl.obj" \
"./src/dq_power_ctrl.obj" \
"./src/dq_statcom_ctrl.obj" \
"./src/dq_vsg_ctrl.obj" \
"./src/eCAN_Configuration.obj" \
"./src/ePWM_configuration.obj" \
"./src/main.obj" \
"../F28335.cmd" \
"../src/DSP2833x_Headers_nonBIOS.cmd" \
$(GEN_CMDS__FLAG) \
-llibc.a \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include src/subdir_vars.mk
-include subdir_rules.mk
-include src/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(SV7A_DEPS)),)
-include $(SV7A_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
DSP_SUNRISE_SS_F28336.out 

EXE_OUTPUTS__QUOTED += \
"DSP_SUNRISE_SS_F28336.out" 


# All Target
all: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@$(MAKE) --no-print-directory -Onone "DSP_SUNRISE_SS_F28336.out"

# Tool invocations
DSP_SUNRISE_SS_F28336.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: "$@"'
	@echo 'Invoking: C2000 Linker'
	"C:/ti/ccs1260/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/bin/cl2000" -v28 -ml -mt --float_support=fpu32 -g --diag_warning=225 --diag_wrap=off --display_error_number --abi=coffabi -z -m"DSP_SUNRISE_SS_F28336.map" --stack_size=0x300 --warn_sections -i"C:/ti/ccs1260/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/lib" -i"C:/ti/ccs1260/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/include" --reread_libs --diag_wrap=off --display_error_number --xml_link_info="DSP_SUNRISE_SS_F28336_linkInfo.xml" --rom_model -o "DSP_SUNRISE_SS_F28336.out" $(ORDERED_OBJS)
	@echo 'Finished building target: "$@"'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXE_OUTPUTS__QUOTED)
	-$(RM) "src\ADC_configuration.obj" "src\DMA_configuration.obj" "src\DSP2833x_ADC_cal.obj" "src\DSP2833x_Adc.obj" "src\DSP2833x_CodeStartBranch.obj" "src\DSP2833x_CpuTimers.obj" "src\DSP2833x_DMA.obj" "src\DSP2833x_DefaultIsr.obj" "src\DSP2833x_ECan.obj" "src\DSP2833x_GlobalVariableDefs.obj" "src\DSP2833x_Gpio.obj" "src\DSP2833x_PieCtrl.obj" "src\DSP2833x_PieVect.obj" "src\DSP2833x_SysCtrl.obj" "src\DSP2833x_usDelay.obj" "src\GPIO_configuration.obj" "src\PLL_Park_transformations.obj" "src\State_machine.obj" "src\calculations.obj" "src\dq_current_ctrl.obj" "src\dq_power_ctrl.obj" "src\dq_statcom_ctrl.obj" "src\dq_vsg_ctrl.obj" "src\eCAN_Configuration.obj" "src\ePWM_configuration.obj" "src\main.obj" 
	-$(RM) "src\ADC_configuration.d" "src\DMA_configuration.d" "src\DSP2833x_Adc.d" "src\DSP2833x_CpuTimers.d" "src\DSP2833x_DMA.d" "src\DSP2833x_DefaultIsr.d" "src\DSP2833x_ECan.d" "src\DSP2833x_GlobalVariableDefs.d" "src\DSP2833x_Gpio.d" "src\DSP2833x_PieCtrl.d" "src\DSP2833x_PieVect.d" "src\DSP2833x_SysCtrl.d" "src\GPIO_configuration.d" "src\PLL_Park_transformations.d" "src\State_machine.d" "src\calculations.d" "src\dq_current_ctrl.d" "src\dq_power_ctrl.d" "src\dq_statcom_ctrl.d" "src\dq_vsg_ctrl.d" "src\eCAN_Configuration.d" "src\ePWM_configuration.d" "src\main.d" 
	-$(RM) "src\DSP2833x_ADC_cal.d" "src\DSP2833x_CodeStartBranch.d" "src\DSP2833x_usDelay.d" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

