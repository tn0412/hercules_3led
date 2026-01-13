################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/my_lib/led_ctrl.c 

OBJS += \
./Core/Src/my_lib/led_ctrl.o 

C_DEPS += \
./Core/Src/my_lib/led_ctrl.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/my_lib/%.o Core/Src/my_lib/%.su Core/Src/my_lib/%.cyclo: ../Core/Src/my_lib/%.c Core/Src/my_lib/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-my_lib

clean-Core-2f-Src-2f-my_lib:
	-$(RM) ./Core/Src/my_lib/led_ctrl.cyclo ./Core/Src/my_lib/led_ctrl.d ./Core/Src/my_lib/led_ctrl.o ./Core/Src/my_lib/led_ctrl.su

.PHONY: clean-Core-2f-Src-2f-my_lib

