################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
lab5a.lss \

FLASH_IMAGE += \
lab5a.hex \

EEPROM_IMAGE += \
lab5a.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: lab5a.elf secondary-outputs

# Tool invocations
lab5a.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,lab5a.map -mmcu=atmega16 -o "lab5a.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

lab5a.lss: lab5a.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S lab5a.elf  >"lab5a.lss"
	@echo 'Finished building: $@'
	@echo ' '

lab5a.hex: lab5a.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex lab5a.elf  "lab5a.hex"
	@echo 'Finished building: $@'
	@echo ' '

lab5a.eep: lab5a.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex lab5a.elf  "lab5a.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: lab5a.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega16 lab5a.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(ASM_DEPS)$(EEPROM_IMAGE)$(FLASH_IMAGE)$(ELFS)$(LSS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS) lab5a.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
