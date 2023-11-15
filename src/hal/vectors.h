#ifndef STM32F4_HAL_VECTORS_H
#define STM32F4_HAL_VECTORS_H

#include <stdint.h>

extern uint32_t g_sys_ticks;

#define NVIC_USART2_IRQ 38

void vectors_register_isr(uint32_t position, void (*isr)(void));

void vectors_enable_irq(uint8_t channel);
void vectors_disable_irq(uint8_t channel);

#endif
