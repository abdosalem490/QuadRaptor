################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Code/Service/FreeRTOS/croutine.c \
../Code/Service/FreeRTOS/event_groups.c \
../Code/Service/FreeRTOS/list.c \
../Code/Service/FreeRTOS/queue.c \
../Code/Service/FreeRTOS/stream_buffer.c \
../Code/Service/FreeRTOS/tasks.c \
../Code/Service/FreeRTOS/timers.c 

OBJS += \
./Code/Service/FreeRTOS/croutine.o \
./Code/Service/FreeRTOS/event_groups.o \
./Code/Service/FreeRTOS/list.o \
./Code/Service/FreeRTOS/queue.o \
./Code/Service/FreeRTOS/stream_buffer.o \
./Code/Service/FreeRTOS/tasks.o \
./Code/Service/FreeRTOS/timers.o 

C_DEPS += \
./Code/Service/FreeRTOS/croutine.d \
./Code/Service/FreeRTOS/event_groups.d \
./Code/Service/FreeRTOS/list.d \
./Code/Service/FreeRTOS/queue.d \
./Code/Service/FreeRTOS/stream_buffer.d \
./Code/Service/FreeRTOS/tasks.d \
./Code/Service/FreeRTOS/timers.d 


# Each subdirectory must supply rules for building sources it contributes
Code/Service/FreeRTOS/%.o: ../Code/Service/FreeRTOS/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused  -g -I"D:\codes\PROJECTS\fourth year\GP\repo\QuadRaptor\software\drone\drone board\Code\MCAL\Debug" -I"D:\codes\PROJECTS\fourth year\GP\repo\QuadRaptor\software\drone\drone board\Code\HAL\ADXL345" -I"D:\codes\PROJECTS\fourth year\GP\repo\QuadRaptor\software\drone\drone board\Code\HAL\HC_SR04" -I"D:\codes\PROJECTS\fourth year\GP\repo\QuadRaptor\software\drone\drone board\Code\HAL\BMP280" -I"D:\codes\PROJECTS\fourth year\GP\repo\QuadRaptor\software\drone\drone board\Code\HAL\Config" -I"D:\codes\PROJECTS\fourth year\GP\repo\QuadRaptor\software\drone\drone board\Code\HAL\HMC5883L" -I"D:\codes\PROJECTS\fourth year\GP\repo\QuadRaptor\software\drone\drone board\Code\HAL\MPU6050" -I"D:\codes\PROJECTS\fourth year\GP\repo\QuadRaptor\software\drone\drone board\Code\HAL\ESC" -I"D:\codes\PROJECTS\fourth year\GP\repo\QuadRaptor\software\drone\drone board\Code\HAL\Wrapper" -I"D:\codes\PROJECTS\fourth year\GP\repo\QuadRaptor\software\drone\drone board\Code\Lib" -I"D:\codes\PROJECTS\fourth year\GP\repo\QuadRaptor\software\drone\drone board\Code\MCAL\Core" -I"D:\codes\PROJECTS\fourth year\GP\repo\QuadRaptor\software\drone\drone board\Code\MCAL\Config" -I"D:\codes\PROJECTS\fourth year\GP\repo\QuadRaptor\software\drone\drone board\Code\MCAL\Wrapper" -I"D:\codes\PROJECTS\fourth year\GP\repo\QuadRaptor\software\drone\drone board\Code\APP" -I"D:\codes\PROJECTS\fourth year\GP\repo\QuadRaptor\software\drone\drone board\Code\Middleware\Error_Log" -I"D:\codes\PROJECTS\fourth year\GP\repo\QuadRaptor\software\drone\drone board\Code\Middleware\PID" -I"D:\codes\PROJECTS\fourth year\GP\repo\QuadRaptor\software\drone\drone board\Code\Middleware\Matrix" -I"D:\codes\PROJECTS\fourth year\GP\repo\QuadRaptor\software\drone\drone board\Code\Middleware\SensorFusion" -I"D:\codes\PROJECTS\fourth year\GP\repo\QuadRaptor\software\drone\drone board\Code\MCAL\Peripheral\inc" -I"D:\codes\PROJECTS\fourth year\GP\repo\QuadRaptor\software\drone\drone board\Code\Service\FreeRTOS" -I"D:\codes\PROJECTS\fourth year\GP\repo\QuadRaptor\software\drone\drone board\Code\Service" -I"D:\codes\PROJECTS\fourth year\GP\repo\QuadRaptor\software\drone\drone board\Code\Service\Wrapper" -I"D:\codes\PROJECTS\fourth year\GP\repo\QuadRaptor\software\drone\drone board\Code\Service\FreeRTOS\include" -I"D:\codes\PROJECTS\fourth year\GP\repo\QuadRaptor\software\drone\drone board\Code\Service\FreeRTOS\portable" -I"D:\codes\PROJECTS\fourth year\GP\repo\QuadRaptor\software\drone\drone board\Code\Service\FreeRTOS\portable\Common" -I"D:\codes\PROJECTS\fourth year\GP\repo\QuadRaptor\software\drone\drone board\Code\Service\FreeRTOS\portable\GCC\RISC-V" -I"D:\codes\PROJECTS\fourth year\GP\repo\QuadRaptor\software\drone\drone board\Code\Service\FreeRTOS\portable\GCC\RISC-V\chip_specific_extensions\RV32I_PFIC_no_extensions" -I"D:\codes\PROJECTS\fourth year\GP\repo\QuadRaptor\software\drone\drone board\Code\Service\FreeRTOS\portable\MemMang" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


