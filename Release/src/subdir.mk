################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/cr_cpp_config.cpp \
../src/cr_startup_lpc13uxx.cpp 

C_SRCS += \
../src/LEDCube.c \
../src/animations.c \
../src/crp.c \
../src/driver.c 

OBJS += \
./src/LEDCube.o \
./src/animations.o \
./src/cr_cpp_config.o \
./src/cr_startup_lpc13uxx.o \
./src/crp.o \
./src/driver.o 

C_DEPS += \
./src/LEDCube.d \
./src/animations.d \
./src/crp.d \
./src/driver.d 

CPP_DEPS += \
./src/cr_cpp_config.d \
./src/cr_startup_lpc13uxx.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__NEWLIB__ -DNDEBUG -D__CODE_RED -DCORE_M3 -D__USE_CMSIS=CMSIS_CORE_LPC13Uxx -DCPP_USE_HEAP -D__LPC13UXX__ -I"C:\Users\Stcupp\Documents\LPCXpresso_7.5.0_254\LEDCUBE2\LEDCUBE\inc" -I"C:\Users\Stcupp\Documents\LPCXpresso_7.5.0_254\LEDCUBE2\CMSIS_CORE_LPC13Uxx\inc" -O2 -g -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C++ Compiler'
	arm-none-eabi-c++ -D__NEWLIB__ -DNDEBUG -D__CODE_RED -DCORE_M3 -D__USE_CMSIS=CMSIS_CORE_LPC13Uxx -DCPP_USE_HEAP -D__LPC13UXX__ -I"C:\Users\Stcupp\Documents\LPCXpresso_7.5.0_254\LEDCUBE2\LEDCUBE\inc" -I"C:\Users\Stcupp\Documents\LPCXpresso_7.5.0_254\LEDCUBE2\CMSIS_CORE_LPC13Uxx\inc" -O2 -Os -g -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fno-rtti -fno-exceptions -mcpu=cortex-m3 -mthumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


