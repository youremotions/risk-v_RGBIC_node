################################################################################
# MRS Version: 2.1.0
# Automatically-generated file. Do not edit!
################################################################################
-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include User/subdir.mk
-include Startup/subdir.mk
-include Peripheral/src/subdir.mk
-include Debug/subdir.mk
-include Core/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_FLASH += \
risk-v_RGBIC_node.hex \

SECONDARY_LIST += \
risk-v_RGBIC_node.lst \

SECONDARY_SIZE += \
risk-v_RGBIC_node.siz \


# All Target
all: 
	$(MAKE) --no-print-directory main-build 

main-build: risk-v_RGBIC_node.elf secondary-outputs

# Tool invocations
risk-v_RGBIC_node.elf: $(OBJS) $(USER_OBJS)
	@	riscv-none-embed-gcc -march=rv32ecxw -mabi=ilp32e -msmall-data-limit=0 -msave-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized -g -T "c:/Users/theoy/Documents/GitHubSourceTreeClones/risk-v_RGBIC_node/risk-v_RGBIC_node/Ld/Link.ld" -nostartfiles -Xlinker --gc-sections -Wl,-Map,"risk-v_RGBIC_node.map" --specs=nano.specs --specs=nosys.specs -o "risk-v_RGBIC_node.elf" $(OBJS) $(USER_OBJS) $(LIBS) -lprintf
risk-v_RGBIC_node.hex: risk-v_RGBIC_node.elf
	@	riscv-none-embed-objcopy -O ihex "risk-v_RGBIC_node.elf" "risk-v_RGBIC_node.hex"
risk-v_RGBIC_node.lst: risk-v_RGBIC_node.elf
	@	riscv-none-embed-objdump --all-headers --demangle --disassemble -M xw "risk-v_RGBIC_node.elf" > "risk-v_RGBIC_node.lst"
risk-v_RGBIC_node.siz: risk-v_RGBIC_node.elf
	riscv-none-embed-size --format=berkeley "risk-v_RGBIC_node.elf"

# Other Targets
clean:
	-$(RM) $(OBJS)$(SECONDARY_FLASH)$(SECONDARY_LIST)$(SECONDARY_SIZE)$(S_DEPS)$(S_UPPER_DEPS)$(ASM_DEPS)$(ASM_UPPER_DEPS)$(C_DEPS) risk-v_RGBIC_node.elf

secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents

-include ../makefile.targets