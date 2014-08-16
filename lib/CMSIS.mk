CMSIS_VERSION = 4.1

MCU_FAMILY_LOWERCASE = $(shell echo $(MCU_FAMILY) | tr '[:upper:]' '[:lower:]')
MCU_MODEL_FAMILY_LOWERCASE  = $(shell echo $(MCU_MODEL_FAMILY) | tr '[:upper:]' '[:lower:]')

CMSIS = ./lib/CMSIS/$(CMSIS_VERSION)

CSRC += $(CMSIS)/Device/ST/$(MCU_FAMILY)/Source/Templates/system_$(MCU_FAMILY_LOWERCASE).c

ASMSRC += $(CMSIS)/Device/ST/$(MCU_FAMILY)/Source/Templates/gcc/startup_$(MCU_MODEL_FAMILY_LOWERCASE).s

INCDIR += $(CMSIS)/Device/ST/$(MCU_FAMILY)/Include \
           $(CMSIS)/Include
