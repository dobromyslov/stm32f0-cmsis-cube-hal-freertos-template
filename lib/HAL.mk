HAL_VERSION = 1.0.1

HAL = ./lib/$(MCU_FAMILY)_HAL_Driver/$(HAL_VERSION)

CSRC += $(HAL)/Src/stm32f0xx_hal.c \
         $(HAL)/Src/stm32f0xx_hal_adc.c \
         $(HAL)/Src/stm32f0xx_hal_adc_ex.c \
         $(HAL)/Src/stm32f0xx_hal_can.c \
         $(HAL)/Src/stm32f0xx_hal_cec.c \
         $(HAL)/Src/stm32f0xx_hal_comp.c \
         $(HAL)/Src/stm32f0xx_hal_cortex.c \
         $(HAL)/Src/stm32f0xx_hal_crc.c \
         $(HAL)/Src/stm32f0xx_hal_crc_ex.c \
         $(HAL)/Src/stm32f0xx_hal_dac.c \
         $(HAL)/Src/stm32f0xx_hal_dac_ex.c \
         $(HAL)/Src/stm32f0xx_hal_dma.c \
         $(HAL)/Src/stm32f0xx_hal_flash.c \
         $(HAL)/Src/stm32f0xx_hal_flash_ex.c \
         $(HAL)/Src/stm32f0xx_hal_gpio.c \
         $(HAL)/Src/stm32f0xx_hal_i2c.c \
         $(HAL)/Src/stm32f0xx_hal_i2c_ex.c \
         $(HAL)/Src/stm32f0xx_hal_i2s.c \
         $(HAL)/Src/stm32f0xx_hal_irda.c \
         $(HAL)/Src/stm32f0xx_hal_iwdg.c \
         $(HAL)/Src/stm32f0xx_hal_msp_template.c \
         $(HAL)/Src/stm32f0xx_hal_pcd.c \
         $(HAL)/Src/stm32f0xx_hal_pcd_ex.c \
         $(HAL)/Src/stm32f0xx_hal_pwr.c \
         $(HAL)/Src/stm32f0xx_hal_pwr_ex.c \
         $(HAL)/Src/stm32f0xx_hal_rcc.c \
         $(HAL)/Src/stm32f0xx_hal_rcc_ex.c \
         $(HAL)/Src/stm32f0xx_hal_rtc.c \
         $(HAL)/Src/stm32f0xx_hal_rtc_ex.c \
         $(HAL)/Src/stm32f0xx_hal_smartcard.c \
         $(HAL)/Src/stm32f0xx_hal_smartcard_ex.c \
         $(HAL)/Src/stm32f0xx_hal_smbus.c \
         $(HAL)/Src/stm32f0xx_hal_spi.c \
         $(HAL)/Src/stm32f0xx_hal_tim.c \
         $(HAL)/Src/stm32f0xx_hal_tim_ex.c \
         $(HAL)/Src/stm32f0xx_hal_tsc.c \
         $(HAL)/Src/stm32f0xx_hal_uart.c \
         $(HAL)/Src/stm32f0xx_hal_uart_ex.c \
         $(HAL)/Src/stm32f0xx_hal_usart.c \
         $(HAL)/Src/stm32f0xx_hal_wwdg.c

INCDIR += $(HAL)/Inc
