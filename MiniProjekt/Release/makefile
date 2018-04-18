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
MiniProjekt.lss \

FLASH_IMAGE += \
MiniProjekt.hex \

EEPROM_IMAGE += \
MiniProjekt.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: MiniProjekt.elf secondary-outputs

# Tool invocations
MiniProjekt.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,MiniProjekt.map -Wl,-u,vfprintf -lprintf_flt -lm -mmcu=atmega32 -o "MiniProjekt.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

MiniProjekt.lss: MiniProjekt.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S MiniProjekt.elf  >"MiniProjekt.lss"
	@echo 'Finished building: $@'
	@echo ' '

MiniProjekt.hex: MiniProjekt.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex MiniProjekt.elf  "MiniProjekt.hex"
	@echo 'Finished building: $@'
	@echo ' '

MiniProjekt.eep: MiniProjekt.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex MiniProjekt.elf  "MiniProjekt.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: MiniProjekt.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 MiniProjekt.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(ASM_DEPS)$(EEPROM_IMAGE)$(FLASH_IMAGE)$(ELFS)$(LSS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS) MiniProjekt.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
