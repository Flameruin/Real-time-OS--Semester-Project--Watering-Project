################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
CC3220S_LAUNCHXL.obj: ../CC3220S_LAUNCHXL.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.6.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=vfplib -me --include_path="C:/Users/haite/workspace_v7/Watering_Project" --include_path="C:/ti/simplelink_cc32xx_sdk_1_60_00_04/kernel/tirtos/packages/ti/sysbios/posix" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.6.LTS/include" --define=cc3220s -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="CC3220S_LAUNCHXL.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

build-51786255:
	@$(MAKE) --no-print-directory -Onone -f subdir_rules.mk build-51786255-inproc

build-51786255-inproc: ../release.cfg
	@echo 'Building file: "$<"'
	@echo 'Invoking: XDCtools'
	"C:/ti/xdctools_3_50_04_43_core/xs" --xdcpath="C:/ti/simplelink_cc32xx_sdk_1_60_00_04/source;C:/ti/simplelink_cc32xx_sdk_1_60_00_04/kernel/tirtos/packages;C:/ti/ccsv7/ccs_base;" xdc.tools.configuro -o configPkg -t ti.targets.arm.elf.M4 -p ti.platforms.simplelink:CC3220S -r release -c "C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.6.LTS" --compileOptions "-mv7M4 --code_state=16 --float_support=vfplib -me --include_path=\"C:/Users/haite/workspace_v7/Watering_Project\" --include_path=\"C:/ti/simplelink_cc32xx_sdk_1_60_00_04/kernel/tirtos/packages/ti/sysbios/posix\" --include_path=\"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.6.LTS/include\" --define=cc3220s -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on  " "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

configPkg/linker.cmd: build-51786255 ../release.cfg
configPkg/compiler.opt: build-51786255
configPkg/: build-51786255


