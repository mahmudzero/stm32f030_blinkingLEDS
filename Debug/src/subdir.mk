################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/main.c \
../src/syscalls.c \
../src/system_stm32f0xx.c 

OBJS += \
./src/main.o \
./src/syscalls.o \
./src/system_stm32f0xx.o 

C_DEPS += \
./src/main.d \
./src/syscalls.d \
./src/system_stm32f0xx.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -mfloat-abi=soft -DSTM32 -DSTM32F0 -DSTM32F030R8Tx -DDEBUG -DSTM32F030 -DUSE_STDPERIPH_DRIVER -I"/Users/mahmudahmad/Desktop/Development/STM/testing/CPAL_Driver/inc" -I"/Users/mahmudahmad/Desktop/Development/STM/testing/StdPeriph_Driver/inc" -I"/Users/mahmudahmad/Desktop/Development/STM/testing/inc" -I"/Users/mahmudahmad/Desktop/Development/STM/testing/CMSIS/device" -I"/Users/mahmudahmad/Desktop/Development/STM/testing/CMSIS/core" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


