################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Code/Service/Wrapper/subdir.mk
-include Code/Service/FreeRTOS/portable/MemMang/subdir.mk
-include Code/Service/FreeRTOS/portable/GCC/RISC-V/subdir.mk
-include Code/Service/FreeRTOS/portable/Common/subdir.mk
-include Code/Service/FreeRTOS/subdir.mk
-include Code/MCAL/Wrapper/subdir.mk
-include Code/MCAL/Startup/subdir.mk
-include Code/MCAL/Peripheral/src/subdir.mk
-include Code/MCAL/Debug/subdir.mk
-include Code/MCAL/Core/subdir.mk
-include Code/MCAL/Config/subdir.mk
-include Code/HAL/Wrapper/subdir.mk
-include Code/HAL/NRF2401/subdir.mk
-include Code/HAL/Config/subdir.mk
-include Code/APP/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_FLASH += \
App\ Board.hex \

SECONDARY_LIST += \
App\ Board.lst \

SECONDARY_SIZE += \
App\ Board.siz \


# All Target
all: App\ Board.elf secondary-outputs

# Tool invocations
App\ Board.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GNU RISC-V Cross C Linker'
	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused  -g -T "D:\codes\PROJECTS\fourth year\GP\repo\QuadRaptor\software\drone\application board\Code\MCAL\Linker\Link.ld" -nostartfiles -Xlinker --gc-sections -Wl,-Map,"App Board.map" --specs=nano.specs -u _printf_float --specs=nosys.specs -o "App Board.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

App\ Board.hex: App\ Board.elf
	@echo 'Invoking: GNU RISC-V Cross Create Flash Image'
	riscv-none-embed-objcopy -O ihex "App Board.elf"  "App Board.hex"
	@echo 'Finished building: $@'
	@echo ' '

App\ Board.lst: App\ Board.elf
	@echo 'Invoking: GNU RISC-V Cross Create Listing'
	riscv-none-embed-objdump --all-headers --demangle --disassemble "App Board.elf" > "App Board.lst"
	@echo 'Finished building: $@'
	@echo ' '

App\ Board.siz: App\ Board.elf
	@echo 'Invoking: GNU RISC-V Cross Print Size'
	riscv-none-embed-size --format=berkeley "App Board.elf"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(SECONDARY_FLASH)$(SECONDARY_LIST)$(SECONDARY_SIZE)$(ASM_DEPS)$(S_UPPER_DEPS)$(C_DEPS) "App Board.elf"
	-@echo ' '

secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents

-include ../makefile.targets
