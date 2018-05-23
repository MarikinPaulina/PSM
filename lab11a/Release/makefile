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
lab11a.lss \

FLASH_IMAGE += \
lab11a.hex \

EEPROM_IMAGE += \
lab11a.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: lab11a.elf secondary-outputs

# Tool invocations
lab11a.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,lab11a.map -Wl,-u,vfprintf -lprintf_flt -lm -mmcu=atmega32 -o "lab11a.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

lab11a.lss: lab11a.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S lab11a.elf  >"lab11a.lss"
	@echo 'Finished building: $@'
	@echo ' '

lab11a.hex: lab11a.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex lab11a.elf  "lab11a.hex"
	@echo 'Finished building: $@'
	@echo ' '

lab11a.eep: lab11a.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex lab11a.elf  "lab11a.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: lab11a.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 lab11a.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(ASM_DEPS)$(EEPROM_IMAGE)$(FLASH_IMAGE)$(ELFS)$(LSS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS) lab11a.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
