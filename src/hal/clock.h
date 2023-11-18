#ifndef STM32F4_HAL_CLOCK_H
#define STM32F4_HAL_CLOCK_H

#include <stdint.h>

#include <hal/registers.h>

#define HSI_FREQ (16000000)
#define HSE_FREQ (8000000)
#define LSI_FREQ (32000)
#define LSE_FREQ (32768)

void clock_reset(void);

void clock_init_hsi_16mhz(void);
void clock_init_hse_8mhz(void);
void clock_init_pll_168mhz(void);

void clock_enable_gpio(gpio_t* gpio);
void clock_enable_usart(usart_t* usart);
void clock_enable_spi(spi_t* spi);

uint32_t clock_get_usart_clk_freq(usart_t* usart);

#endif
