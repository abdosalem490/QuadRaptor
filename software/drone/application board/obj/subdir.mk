################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../template.c 

OBJS += \
./template.o 

C_DEPS += \
./template.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused  -g -I"D:\codes\PROJECTS\fourth year\GP\repo\QuadRaptor\software\drone\application board\Code\HAL\Config" -I"D:\codes\PROJECTS\fourth year\GP\repo\QuadRaptor\software\drone\application board\Code\MCAL\Debug" -I"D:\codes\PROJECTS\fourth year\GP\repo\QuadRaptor\software\drone\application board\Code\HAL\Wrapper" -I"D:\codes\PROJECTS\fourth year\GP\repo\QuadRaptor\software\drone\application board\Code\Lib" -I"D:\codes\PROJECTS\fourth year\GP\repo\QuadRaptor\software\drone\application board\Code\MCAL\Core" -I"D:\codes\PROJECTS\fourth year\GP\repo\QuadRaptor\software\drone\application board\Code\MCAL\Config" -I"D:\codes\PROJECTS\fourth year\GP\repo\QuadRaptor\software\drone\application board\Code\MCAL\Wrapper" -I"D:\codes\PROJECTS\fourth year\GP\repo\QuadRaptor\software\drone\application board\Code\APP" -I"D:\codes\PROJECTS\fourth year\GP\repo\QuadRaptor\software\drone\application board\Code\Middleware\Error_Log" -I"D:\codes\PROJECTS\fourth year\GP\repo\QuadRaptor\software\drone\application board\Code\MCAL\Peripheral\inc" -I"D:\codes\PROJECTS\fourth year\GP\repo\QuadRaptor\software\drone\application board\Code\Service\FreeRTOS" -I"D:\codes\PROJECTS\fourth year\GP\repo\QuadRaptor\software\drone\application board\Code\Service" -I"D:\codes\PROJECTS\fourth year\GP\repo\QuadRaptor\software\drone\application board\Code\Service\Wrapper" -I"D:\codes\PROJECTS\fourth year\GP\repo\QuadRaptor\software\drone\application board\Code\Service\FreeRTOS\include" -I"D:\codes\PROJECTS\fourth year\GP\repo\QuadRaptor\software\drone\application board\Code\Service\FreeRTOS\portable" -I"D:\codes\PROJECTS\fourth year\GP\repo\QuadRaptor\software\drone\application board\Code\Service\FreeRTOS\portable\Common" -I"D:\codes\PROJECTS\fourth year\GP\repo\QuadRaptor\software\drone\application board\Code\Service\FreeRTOS\portable\GCC\RISC-V" -I"D:\codes\PROJECTS\fourth year\GP\repo\QuadRaptor\software\drone\application board\Code\Service\FreeRTOS\portable\GCC\RISC-V\chip_specific_extensions\RV32I_PFIC_no_extensions" -I"D:\codes\PROJECTS\fourth year\GP\repo\QuadRaptor\software\drone\application board\Code\Service\FreeRTOS\portable\MemMang" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

