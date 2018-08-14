################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.6.LTS

GEN_OPTS__FLAG := --cmd_file="configPkg/compiler.opt"
GEN_CMDS__FLAG := -l"configPkg/linker.cmd"

ORDERED_OBJS += \
"./CC3220S_LAUNCHXL.obj" \
"./application/ADC_Control.obj" \
"./application/GPIO_control.obj" \
"./application/I2C_Utils.obj" \
"./application/PWM_Control.obj" \
"./application/TSL2561.obj" \
"./application/UART_Utils.obj" \
"./application/i2c_control.obj" \
"./application/mian.obj" \
"./application/shared_variables.obj" \
"../CC3220S_LAUNCHXL_TIRTOS.cmd" \
$(GEN_CMDS__FLAG) \
-l"C:/ti/simplelink_cc32xx_sdk_1_60_00_04/source/ti/display/lib/display.aem4" \
-l"C:/ti/simplelink_cc32xx_sdk_1_60_00_04/source/ti/drivers/lib/drivers_cc32xx.aem4" \
-l"C:/ti/simplelink_cc32xx_sdk_1_60_00_04/source/third_party/fatfs/lib/fatfs.aem4" \
-l"C:/ti/simplelink_cc32xx_sdk_1_60_00_04/kernel/tirtos/packages/ti/dpl/lib/dpl_cc32xx.aem4" \
-l"C:/ti/simplelink_cc32xx_sdk_1_60_00_04/source/ti/devices/cc32xx/driverlib/ccs/Release/driverlib.a" \
-llibc.a \
-llibc.a \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include application/subdir_vars.mk
-include subdir_rules.mk
-include application/subdir_rules.mk
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
Watering_Project.out \

EXE_OUTPUTS__QUOTED += \
"Watering_Project.out" \

BIN_OUTPUTS += \
Watering_Project.bin \

BIN_OUTPUTS__QUOTED += \
"Watering_Project.bin" \


# All Target
all: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@$(MAKE) --no-print-directory -Onone "Watering_Project.out"

# Tool invocations
Watering_Project.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: "$@"'
	@echo 'Invoking: ARM Linker'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.6.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=vfplib -me --define=cc3220s -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on -z -m"Watering_Project.map" -i"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.6.LTS/lib" -i"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.6.LTS/include" --reread_libs --diag_wrap=off --display_error_number --warn_sections --xml_link_info="Watering_Project_linkInfo.xml" --rom_model -o "Watering_Project.out" $(ORDERED_OBJS)
	@echo 'Finished building target: "$@"'
	@echo ' '
	@$(MAKE) --no-print-directory post-build

Watering_Project.bin: $(EXE_OUTPUTS)
	@echo 'Building files: $(strip $(EXE_OUTPUTS__QUOTED))'
	@echo 'Invoking: ARM Hex Utility'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.6.LTS/bin/armhex"  -o "Watering_Project.bin" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building: $(strip $(EXE_OUTPUTS__QUOTED))'
	@echo ' '
	@$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(GEN_CMDS__QUOTED)$(GEN_MISC_FILES__QUOTED)$(BIN_OUTPUTS__QUOTED)$(GEN_FILES__QUOTED)$(EXE_OUTPUTS__QUOTED)$(GEN_OPTS__QUOTED)
	-$(RMDIR) $(GEN_MISC_DIRS__QUOTED)
	-$(RM) "CC3220S_LAUNCHXL.obj" "application\ADC_Control.obj" "application\GPIO_control.obj" "application\I2C_Utils.obj" "application\PWM_Control.obj" "application\TSL2561.obj" "application\UART_Utils.obj" "application\i2c_control.obj" "application\mian.obj" "application\shared_variables.obj" 
	-$(RM) "CC3220S_LAUNCHXL.d" "application\ADC_Control.d" "application\GPIO_control.d" "application\I2C_Utils.d" "application\PWM_Control.d" "application\TSL2561.d" "application\UART_Utils.d" "application\i2c_control.d" "application\mian.d" "application\shared_variables.d" 
	-@echo 'Finished clean'
	-@echo ' '

post-build:
	-C:/ti/ccsv7/utils/tiobj2bin/tiobj2bin Watering_Project.out Watering_Project.bin C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.6.LTS/bin/armofd C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.6.LTS/bin/armhex C:/ti/ccsv7/utils/tiobj2bin/mkhex4bin
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

