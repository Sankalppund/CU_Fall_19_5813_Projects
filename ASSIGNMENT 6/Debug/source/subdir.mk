################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/ADC_DAC.c \
../source/LookUp.c \
../source/Systick_timer.c \
../source/circular_buffer.c \
../source/dma.c \
../source/frts_task.c \
../source/logger.c \
../source/main.c \
../source/mtb.c \
../source/semihost_hardfault.c \
../source/ss_led_control.c 

OBJS += \
./source/ADC_DAC.o \
./source/LookUp.o \
./source/Systick_timer.o \
./source/circular_buffer.o \
./source/dma.o \
./source/frts_task.o \
./source/logger.o \
./source/main.o \
./source/mtb.o \
./source/semihost_hardfault.o \
./source/ss_led_control.o 

C_DEPS += \
./source/ADC_DAC.d \
./source/LookUp.d \
./source/Systick_timer.d \
./source/circular_buffer.d \
./source/dma.d \
./source/frts_task.d \
./source/logger.d \
./source/main.d \
./source/mtb.d \
./source/semihost_hardfault.d \
./source/ss_led_control.d 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -D__REDLIB__ -DCPU_MKL25Z128VLK4 -DCPU_MKL25Z128VLK4_cm0plus -DDEBUG -DFSL_RTOS_FREE_RTOS -DFRDM_KL25Z -DFREEDOM -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -DSDK_DEBUGCONSOLE_UART -D__MCUXPRESSO -D__USE_CMSIS -I../board -I../source -I../ -I../drivers -I../CMSIS -I../utilities -I../freertos -I../startup -O0 -fno-common -g -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


