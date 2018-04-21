################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../LCD.c \
../i2c.c \
../longdelay.c \
../main.c \
../rs232.c \
../rtc.c \
../spi.c 

OBJS += \
./LCD.o \
./i2c.o \
./longdelay.o \
./main.o \
./rs232.o \
./rtc.o \
./spi.o 

C_DEPS += \
./LCD.d \
./i2c.d \
./longdelay.d \
./main.d \
./rs232.d \
./rtc.d \
./spi.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


