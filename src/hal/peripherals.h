#ifndef STM32F4_HAL_PERIPHERALS_H
#define STM32F4_HAL_PERIPHERALS_H

#define SYSTICK ((systick_t*)0xE000E010)
#define NVIC ((nvic_t*)0xE000E100)
#define SCB ((scb_t*)0xE000ED00)

#define FLASH ((flash_t*)0x40023C00)

#define PWR ((pwr_t*)0x40007000)

#define RCC ((rcc_t*)0x40023800)

#define GPIOA ((gpio_t*)0x40020000)
#define GPIOB ((gpio_t*)0x40020400)
#define GPIOC ((gpio_t*)0x40020800)
#define GPIOD ((gpio_t*)0x40020C00)
#define GPIOE ((gpio_t*)0x40021000)
#define GPIOF ((gpio_t*)0x40021400)
#define GPIOG ((gpio_t*)0x40021800)
#define GPIOH ((gpio_t*)0x40021C00)
#define GPIOI ((gpio_t*)0x40022000)
#define GPIOJ ((gpio_t*)0x40022400)
#define GPIOK ((gpio_t*)0x40022800)

#define USART1 ((usart_t*)0x40011000)
#define USART2 ((usart_t*)0x40004400)
#define USART3 ((usart_t*)0x40004800)
#define UART4  ((usart_t*)0x40004C00)
#define UART5  ((usart_t*)0x40005000)
#define USART6 ((usart_t*)0x40011400)
#define UART7  ((usart_t*)0x40007800)
#define UART8  ((usart_t*)0x40007C00)

#endif
