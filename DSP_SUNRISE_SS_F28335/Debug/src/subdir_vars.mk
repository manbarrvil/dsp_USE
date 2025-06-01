################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Add inputs and outputs from these tool invocations to the build variables 
CMD_SRCS += \
../src/DSP2833x_Headers_nonBIOS.cmd 

ASM_SRCS += \
../src/DSP2833x_ADC_cal.asm \
../src/DSP2833x_CodeStartBranch.asm \
../src/DSP2833x_usDelay.asm 

C_SRCS += \
../src/ADC_configuration.c \
../src/DMA_configuration.c \
../src/DSP2833x_Adc.c \
../src/DSP2833x_CpuTimers.c \
../src/DSP2833x_DMA.c \
../src/DSP2833x_DefaultIsr.c \
../src/DSP2833x_ECan.c \
../src/DSP2833x_GlobalVariableDefs.c \
../src/DSP2833x_Gpio.c \
../src/DSP2833x_PieCtrl.c \
../src/DSP2833x_PieVect.c \
../src/DSP2833x_SysCtrl.c \
../src/GPIO_configuration.c \
../src/PLL_Park_transformations.c \
../src/State_machine.c \
../src/calculations.c \
../src/dq_current_ctrl.c \
../src/dq_power_ctrl.c \
../src/dq_statcom_ctrl.c \
../src/dq_vsg_ctrl.c \
../src/eCAN_Configuration.c \
../src/ePWM_configuration.c \
../src/main.c 

C_DEPS += \
./src/ADC_configuration.d \
./src/DMA_configuration.d \
./src/DSP2833x_Adc.d \
./src/DSP2833x_CpuTimers.d \
./src/DSP2833x_DMA.d \
./src/DSP2833x_DefaultIsr.d \
./src/DSP2833x_ECan.d \
./src/DSP2833x_GlobalVariableDefs.d \
./src/DSP2833x_Gpio.d \
./src/DSP2833x_PieCtrl.d \
./src/DSP2833x_PieVect.d \
./src/DSP2833x_SysCtrl.d \
./src/GPIO_configuration.d \
./src/PLL_Park_transformations.d \
./src/State_machine.d \
./src/calculations.d \
./src/dq_current_ctrl.d \
./src/dq_power_ctrl.d \
./src/dq_statcom_ctrl.d \
./src/dq_vsg_ctrl.d \
./src/eCAN_Configuration.d \
./src/ePWM_configuration.d \
./src/main.d 

OBJS += \
./src/ADC_configuration.obj \
./src/DMA_configuration.obj \
./src/DSP2833x_ADC_cal.obj \
./src/DSP2833x_Adc.obj \
./src/DSP2833x_CodeStartBranch.obj \
./src/DSP2833x_CpuTimers.obj \
./src/DSP2833x_DMA.obj \
./src/DSP2833x_DefaultIsr.obj \
./src/DSP2833x_ECan.obj \
./src/DSP2833x_GlobalVariableDefs.obj \
./src/DSP2833x_Gpio.obj \
./src/DSP2833x_PieCtrl.obj \
./src/DSP2833x_PieVect.obj \
./src/DSP2833x_SysCtrl.obj \
./src/DSP2833x_usDelay.obj \
./src/GPIO_configuration.obj \
./src/PLL_Park_transformations.obj \
./src/State_machine.obj \
./src/calculations.obj \
./src/dq_current_ctrl.obj \
./src/dq_power_ctrl.obj \
./src/dq_statcom_ctrl.obj \
./src/dq_vsg_ctrl.obj \
./src/eCAN_Configuration.obj \
./src/ePWM_configuration.obj \
./src/main.obj 

ASM_DEPS += \
./src/DSP2833x_ADC_cal.d \
./src/DSP2833x_CodeStartBranch.d \
./src/DSP2833x_usDelay.d 

OBJS__QUOTED += \
"src\ADC_configuration.obj" \
"src\DMA_configuration.obj" \
"src\DSP2833x_ADC_cal.obj" \
"src\DSP2833x_Adc.obj" \
"src\DSP2833x_CodeStartBranch.obj" \
"src\DSP2833x_CpuTimers.obj" \
"src\DSP2833x_DMA.obj" \
"src\DSP2833x_DefaultIsr.obj" \
"src\DSP2833x_ECan.obj" \
"src\DSP2833x_GlobalVariableDefs.obj" \
"src\DSP2833x_Gpio.obj" \
"src\DSP2833x_PieCtrl.obj" \
"src\DSP2833x_PieVect.obj" \
"src\DSP2833x_SysCtrl.obj" \
"src\DSP2833x_usDelay.obj" \
"src\GPIO_configuration.obj" \
"src\PLL_Park_transformations.obj" \
"src\State_machine.obj" \
"src\calculations.obj" \
"src\dq_current_ctrl.obj" \
"src\dq_power_ctrl.obj" \
"src\dq_statcom_ctrl.obj" \
"src\dq_vsg_ctrl.obj" \
"src\eCAN_Configuration.obj" \
"src\ePWM_configuration.obj" \
"src\main.obj" 

C_DEPS__QUOTED += \
"src\ADC_configuration.d" \
"src\DMA_configuration.d" \
"src\DSP2833x_Adc.d" \
"src\DSP2833x_CpuTimers.d" \
"src\DSP2833x_DMA.d" \
"src\DSP2833x_DefaultIsr.d" \
"src\DSP2833x_ECan.d" \
"src\DSP2833x_GlobalVariableDefs.d" \
"src\DSP2833x_Gpio.d" \
"src\DSP2833x_PieCtrl.d" \
"src\DSP2833x_PieVect.d" \
"src\DSP2833x_SysCtrl.d" \
"src\GPIO_configuration.d" \
"src\PLL_Park_transformations.d" \
"src\State_machine.d" \
"src\calculations.d" \
"src\dq_current_ctrl.d" \
"src\dq_power_ctrl.d" \
"src\dq_statcom_ctrl.d" \
"src\dq_vsg_ctrl.d" \
"src\eCAN_Configuration.d" \
"src\ePWM_configuration.d" \
"src\main.d" 

ASM_DEPS__QUOTED += \
"src\DSP2833x_ADC_cal.d" \
"src\DSP2833x_CodeStartBranch.d" \
"src\DSP2833x_usDelay.d" 

C_SRCS__QUOTED += \
"../src/ADC_configuration.c" \
"../src/DMA_configuration.c" \
"../src/DSP2833x_Adc.c" \
"../src/DSP2833x_CpuTimers.c" \
"../src/DSP2833x_DMA.c" \
"../src/DSP2833x_DefaultIsr.c" \
"../src/DSP2833x_ECan.c" \
"../src/DSP2833x_GlobalVariableDefs.c" \
"../src/DSP2833x_Gpio.c" \
"../src/DSP2833x_PieCtrl.c" \
"../src/DSP2833x_PieVect.c" \
"../src/DSP2833x_SysCtrl.c" \
"../src/GPIO_configuration.c" \
"../src/PLL_Park_transformations.c" \
"../src/State_machine.c" \
"../src/calculations.c" \
"../src/dq_current_ctrl.c" \
"../src/dq_power_ctrl.c" \
"../src/dq_statcom_ctrl.c" \
"../src/dq_vsg_ctrl.c" \
"../src/eCAN_Configuration.c" \
"../src/ePWM_configuration.c" \
"../src/main.c" 

ASM_SRCS__QUOTED += \
"../src/DSP2833x_ADC_cal.asm" \
"../src/DSP2833x_CodeStartBranch.asm" \
"../src/DSP2833x_usDelay.asm" 


