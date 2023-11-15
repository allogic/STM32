#include <hal/registers.h>
#include <hal/peripherals.h>
#include <hal/clock.h>
#include <hal/usart.h>
#include <hal/gpio.h>
#include <hal/vectors.h>

#include <terminal.h>

static void terminal_init_gpio(void);
static void terminal_init_usart(void);

static void terminal_usart2_isr(void);

void terminal_init(void) {
	terminal_init_gpio();
	terminal_init_usart();
}

static void terminal_init_gpio(void) {
	clock_enable_gpio(GPIOA);

	gpio_set_mode(GPIOA, 2, GPIO_MODE_AF);
	gpio_set_mode(GPIOA, 3, GPIO_MODE_AF);

	gpio_set_output_type(GPIOA, 3, GPIO_OUTPUT_OD);
	gpio_set_output_speed(GPIOA, 3, GPIO_SPEED_HIGH);

	gpio_set_af(GPIOA, 2, 7);
	gpio_set_af(GPIOA, 3, 7);
}

static void terminal_init_usart(void) {
	clock_enable_usart(USART2);

	usart_set_baudrate(USART2, 115200);
	usart_set_databits(USART2, 8);
	usart_set_stopbits(USART2, USART_STOP_1);
	usart_set_parity(USART2, USART_PARTIY_NONE);
	usart_set_mode(USART2, USART_MODE_TX_RX);

	vectors_register_isr(NVIC_USART2_IRQ, terminal_usart2_isr);
	vectors_enable_irq(NVIC_USART2_IRQ);

	usart_enable_rx_interrupt(USART2);
	usart_enable(USART2);

	usart_send_blocking(USART2, 'F');
	//usart_send_blocking(USART2, 'U');
	//usart_send_blocking(USART2, 'C');
	//usart_send_blocking(USART2, 'K');
}

static void terminal_usart2_isr(void) {
	if (USART2->SR & USART_SR_RXNE) {
		uint8_t value = USART2->DR & USART_DR_MASK;

		if (value == 'A') {
			value = 'B';
		}
	}
}
