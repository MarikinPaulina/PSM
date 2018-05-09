################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../LCD.c \
../OW.c \
../longdelay.c \
../main.c \
../rs232.c \
../spi.c \
../termo.c 

OBJS += \
./LCD.o \
./OW.o \
./longdelay.o \
./main.o \
./rs232.o \
./spi.o \
./termo.o 

C_DEPS += \
./LCD.d \
./OW.d \
./longdelay.d \
./main.d \
./rs232.d \
./spi.d \
./termo.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=11059200UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


