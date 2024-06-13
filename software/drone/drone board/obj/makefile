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
-include Code/HAL/MPU6050/subdir.mk
-include Code/HAL/Config/subdir.mk
-include Code/HAL/ADXL345/subdir.mk
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
Drone\ Board.hex \

SECONDARY_LIST += \
Drone\ Board.lst \

SECONDARY_SIZE += \
Drone\ Board.siz \


# All Target
all: Drone\ Board.elf secondary-outputs

# Tool invocations
Drone\ Board.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GNU RISC-V Cross C Linker'
	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -msave-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused  -g -T "D:\codes\PROJECTS\fourth year\GP\repo\QuadRaptor\software\drone\drone board\Code\MCAL\Linker\Link.ld" -nostartfiles -Xlinker --gc-sections -Wl,-Map,"Drone Board.map" --specs=nano.specs --specs=nosys.specs -o "Drone Board.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

Drone\ Board.hex: Drone\ Board.elf
	@echo 'Invoking: GNU RISC-V Cross Create Flash Image'
	riscv-none-embed-objcopy -O ihex "Drone Board.elf"  "Drone Board.hex"
	@echo 'Finished building: $@'
	@echo ' '

Drone\ Board.lst: Drone\ Board.elf
	@echo 'Invoking: GNU RISC-V Cross Create Listing'
	riscv-none-embed-objdump --all-headers --demangle --disassemble "Drone Board.elf" > "Drone Board.lst"
	@echo 'Finished building: $@'
	@echo ' '

Drone\ Board.siz: Drone\ Board.elf
	@echo 'Invoking: GNU RISC-V Cross Print Size'
	riscv-none-embed-size --format=berkeley "Drone Board.elf"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(SECONDARY_FLASH)$(SECONDARY_LIST)$(SECONDARY_SIZE)$(ASM_DEPS)$(S_UPPER_DEPS)$(C_DEPS) "Drone Board.elf"
	-@echo ' '

secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents

-include ../makefile.targets
