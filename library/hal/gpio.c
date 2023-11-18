#include <hal/gpio.h>

void gpio_set_mode(gpio_t* gpio, uint32_t pin, uint32_t mode) {
	gpio->MODER &= ~(0x3 << (2 * pin));
	gpio->MODER |= mode << (2 * pin);
}

void gpio_set_output_type(gpio_t* gpio, uint32_t pin, uint32_t type) {
	gpio->OTYPER &= ~(0x1 << pin);
	gpio->OTYPER |= type << pin;
}

void gpio_set_output_speed(gpio_t* gpio, uint32_t pin, uint32_t speed) {
	gpio->OSPEEDR &= ~(0x3 << (2 * pin));
	gpio->OSPEEDR |= speed << (2 * pin);
}

void gpio_set_pull(gpio_t* gpio, uint32_t pin, uint32_t pull) {
	gpio->PUPDR &= ~(0x3 << (2 * pin));
	gpio->PUPDR |= pull << (2 * pin);
}

void gpio_set_af(gpio_t* gpio, uint32_t pin, uint8_t af) {
	if (pin < 8) {
		gpio->AFRL &= ~(0xF << (4 * pin));
		gpio->AFRL |= af << (4 * pin);
	} else {
		gpio->AFRH &= ~(0xF << (4 * pin));
		gpio->AFRH |= af << (4 * pin);
	}
}

void gpio_write(gpio_t* gpio, uint32_t pin, uint8_t data) {
	if (data) {
		gpio->ODR |= (1 << pin);
	} else {
		gpio->ODR &= ~(1 << pin);
	}
}

uint8_t gpio_read(gpio_t* gpio, uint32_t pin) {
	return (gpio->IDR >> pin) & 0x1;
}
