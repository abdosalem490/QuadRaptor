################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Code/MCAL/Peripheral/src/ch32v20x_adc.c \
../Code/MCAL/Peripheral/src/ch32v20x_bkp.c \
../Code/MCAL/Peripheral/src/ch32v20x_can.c \
../Code/MCAL/Peripheral/src/ch32v20x_crc.c \
../Code/MCAL/Peripheral/src/ch32v20x_dbgmcu.c \
../Code/MCAL/Peripheral/src/ch32v20x_dma.c \
../Code/MCAL/Peripheral/src/ch32v20x_exti.c \
../Code/MCAL/Peripheral/src/ch32v20x_flash.c \
../Code/MCAL/Peripheral/src/ch32v20x_gpio.c \
../Code/MCAL/Peripheral/src/ch32v20x_i2c.c \
../Code/MCAL/Peripheral/src/ch32v20x_iwdg.c \
../Code/MCAL/Peripheral/src/ch32v20x_misc.c \
../Code/MCAL/Peripheral/src/ch32v20x_opa.c \
../Code/MCAL/Peripheral/src/ch32v20x_pwr.c \
../Code/MCAL/Peripheral/src/ch32v20x_rcc.c \
../Code/MCAL/Peripheral/src/ch32v20x_rtc.c \
../Code/MCAL/Peripheral/src/ch32v20x_spi.c \
../Code/MCAL/Peripheral/src/ch32v20x_tim.c \
../Code/MCAL/Peripheral/src/ch32v20x_usart.c \
../Code/MCAL/Peripheral/src/ch32v20x_wwdg.c 

OBJS += \
./Code/MCAL/Peripheral/src/ch32v20x_adc.o \
./Code/MCAL/Peripheral/src/ch32v20x_bkp.o \
./Code/MCAL/Peripheral/src/ch32v20x_can.o \
./Code/MCAL/Peripheral/src/ch32v20x_crc.o \
./Code/MCAL/Peripheral/src/ch32v20x_dbgmcu.o \
./Code/MCAL/Peripheral/src/ch32v20x_dma.o \
./Code/MCAL/Peripheral/src/ch32v20x_exti.o \
./Code/MCAL/Peripheral/src/ch32v20x_flash.o \
./Code/MCAL/Peripheral/src/ch32v20x_gpio.o \
./Code/MCAL/Peripheral/src/ch32v20x_i2c.o \
./Code/MCAL/Peripheral/src/ch32v20x_iwdg.o \
./Code/MCAL/Peripheral/src/ch32v20x_misc.o \
./Code/MCAL/Peripheral/src/ch32v20x_opa.o \
./Code/MCAL/Peripheral/src/ch32v20x_pwr.o \
./Code/MCAL/Peripheral/src/ch32v20x_rcc.o \
./Code/MCAL/Peripheral/src/ch32v20x_rtc.o \
./Code/MCAL/Peripheral/src/ch32v20x_spi.o \
./Code/MCAL/Peripheral/src/ch32v20x_tim.o \
./Code/MCAL/Peripheral/src/ch32v20x_usart.o \
./Code/MCAL/Peripheral/src/ch32v20x_wwdg.o 

C_DEPS += \
./Code/MCAL/Peripheral/src/ch32v20x_adc.d \
./Code/MCAL/Peripheral/src/ch32v20x_bkp.d \
./Code/MCAL/Peripheral/src/ch32v20x_can.d \
./Code/MCAL/Peripheral/src/ch32v20x_crc.d \
./Code/MCAL/Peripheral/src/ch32v20x_dbgmcu.d \
./Code/MCAL/Peripheral/src/ch32v20x_dma.d \
./Code/MCAL/Peripheral/src/ch32v20x_exti.d \
./Code/MCAL/Peripheral/src/ch32v20x_flash.d \
./Code/MCAL/Peripheral/src/ch32v20x_gpio.d \
./Code/MCAL/Peripheral/src/ch32v20x_i2c.d \
./Code/MCAL/Peripheral/src/ch32v20x_iwdg.d \
./Code/MCAL/Peripheral/src/ch32v20x_misc.d \
./Code/MCAL/Peripheral/src/ch32v20x_opa.d \
./Code/MCAL/Peripheral/src/ch32v20x_pwr.d \
./Code/MCAL/Peripheral/src/ch32v20x_rcc.d \
./Code/MCAL/Peripheral/src/ch32v20x_rtc.d \
./Code/MCAL/Peripheral/src/ch32v20x_spi.d \
./Code/MCAL/Peripheral/src/ch32v20x_tim.d \
./Code/MCAL/Peripheral/src/ch32v20x_usart.d \
./Code/MCAL/Peripheral/src/ch32v20x_wwdg.d 


# Each subdirectory must supply rules for building sources it contributes
Code/MCAL/Peripheral/src/%.o: ../Code/MCAL/Peripheral/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused  -g -I"D:\codes\PROJECTS\fourth year\GP\repo\QuadRaptor\software\drone\drone board\Code\MCAL\Debug" -I"D:\codes\PROJECTS\fourth year\GP\repo\QuadRaptor\software\drone\drone board\Code\HAL\ADXL345" -I"D:\codes\PROJECTS\fourth year\GP\repo\QuadRaptor\software\drone\drone board\Code\HAL\Battery" -I"D:\codes\PROJECTS\fourth year\GP\repo\QuadRaptor\software\drone\drone board\Code\HAL\BMP280" -I"D:\codes\PROJECTS\fourth year\GP\repo\QuadRaptor\software\drone\drone board\Code\HAL\Config" -I"D:\codes\PROJECTS\fourth year\GP\repo\QuadRaptor\software\drone\drone board\Code\HAL\HMC5883L" -I"D:\codes\PROJECTS\fourth year\GP\repo\QuadRaptor\software\drone\drone board\Code\HAL\MPU6050" -I"D:\codes\PROJECTS\fourth year\GP\repo\QuadRaptor\software\drone\drone board\Code\HAL\Temp" -I"D:\codes\PROJECTS\fourth year\GP\repo\QuadRaptor\software\drone\drone board\Code\HAL\Wrapper" -I"D:\codes\PROJECTS\fourth year\GP\repo\QuadRaptor\software\drone\drone board\Code\Lib" -I"D:\codes\PROJECTS\fourth year\GP\repo\QuadRaptor\software\drone\drone board\Code\MCAL\Core" -I"D:\codes\PROJECTS\fourth year\GP\repo\QuadRaptor\software\drone\drone board\Code\MCAL\Config" -I"D:\codes\PROJECTS\fourth year\GP\repo\QuadRaptor\software\drone\drone board\Code\MCAL\Wrapper" -I"D:\codes\PROJECTS\fourth year\GP\repo\QuadRaptor\software\drone\drone board\Code\APP" -I"D:\codes\PROJECTS\fourth year\GP\repo\QuadRaptor\software\drone\drone board\Code\MCAL\Peripheral\inc" -I"D:\codes\PROJECTS\fourth year\GP\repo\QuadRaptor\software\drone\drone board\Code\Service\FreeRTOS" -I"D:\codes\PROJECTS\fourth year\GP\repo\QuadRaptor\software\drone\drone board\Code\Service" -I"D:\codes\PROJECTS\fourth year\GP\repo\QuadRaptor\software\drone\drone board\Code\Service\Wrapper" -I"D:\codes\PROJECTS\fourth year\GP\repo\QuadRaptor\software\drone\drone board\Code\Service\FreeRTOS\include" -I"D:\codes\PROJECTS\fourth year\GP\repo\QuadRaptor\software\drone\drone board\Code\Service\FreeRTOS\portable" -I"D:\codes\PROJECTS\fourth year\GP\repo\QuadRaptor\software\drone\drone board\Code\Service\FreeRTOS\portable\Common" -I"D:\codes\PROJECTS\fourth year\GP\repo\QuadRaptor\software\drone\drone board\Code\Service\FreeRTOS\portable\GCC\RISC-V" -I"D:\codes\PROJECTS\fourth year\GP\repo\QuadRaptor\software\drone\drone board\Code\Service\FreeRTOS\portable\GCC\RISC-V\chip_specific_extensions\RV32I_PFIC_no_extensions" -I"D:\codes\PROJECTS\fourth year\GP\repo\QuadRaptor\software\drone\drone board\Code\Service\FreeRTOS\portable\MemMang" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


