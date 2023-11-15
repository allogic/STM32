#ifndef STM32F4_HAL_GPIO_H
#define STM32F4_HAL_GPIO_H

#include <stdbool.h>
#include <stdint.h>

#include <hal/registers.h>

#define GPIO_MODE_INPUT  (0b00)
#define GPIO_MODE_OUTPUT (0b01)
#define GPIO_MODE_AF     (0b10)
#define GPIO_MODE_ANALOG (0b11)

#define GPIO_OUTPUT_PP (0b00)
#define GPIO_OUTPUT_OD (0b01)

#define GPIO_SPEED_LOW       (0b00)
#define GPIO_SPEED_MEDIUM    (0b01)
#define GPIO_SPEED_HIGH      (0b10)
#define GPIO_SPEED_VERY_HIGH (0b11)

#define GPIO_PULL_NONE (0b00)
#define GPIO_PULL_UP   (0b01)
#define GPIO_PULL_DOWN (0b10)

void gpio_set_mode(gpio_t* gpio, uint32_t pin, uint32_t mode);
void gpio_set_output_type(gpio_t* gpio, uint32_t pin, uint32_t type);
void gpio_set_output_speed(gpio_t* gpio, uint32_t pin, uint32_t speed);
void gpio_set_pull(gpio_t* gpio, uint32_t pin, uint32_t pull);
void gpio_set_af(gpio_t* gpio, uint32_t pin, uint8_t af);

bool gpio_read(gpio_t* gpio, uint32_t pin);
void gpio_write(gpio_t* gpio, uint32_t pin, bool value);

#endif
