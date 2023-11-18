#ifndef STM32F4_VECTORS_H
#define STM32F4_VECTORS_H

#include <string.h>
#include <stdint.h>

extern uint32_t g_sys_ticks;

#define NVIC_USART1_IRQ 37
#define NVIC_USART2_IRQ 38
#define NVIC_USART3_IRQ 39
#define NVIC_USART4_IRQ 52
#define NVIC_USART5_IRQ 53
#define NVIC_USART6_IRQ 71

#define NVIC_SPI1_IRQ 35
#define NVIC_SPI2_IRQ 36
#define NVIC_SPI3_IRQ 51

void vectors_register_isr(uint32_t position, void (*isr)(void));

void vectors_enable_irq(uint8_t channel);
void vectors_disable_irq(uint8_t channel);

#endif
