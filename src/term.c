#include <hal/registers.h>
#include <hal/peripherals.h>
#include <hal/clock.h>
#include <hal/usart.h>
#include <hal/gpio.h>
#include <hal/vectors.h>

#include <term.h>
#include <printf.h>

static uint32_t s_cursor_pos;

static uint8_t s_cmd_buffer[TERM_CMD_BUFFER_SIZE];
static uint8_t s_arg_buffer[TERM_ARG_BUFFER_SIZE];

static void term_init_gpio(void);
static void term_init_usart(void);

static void term_handle_byte(uint8_t byte);
static void term_exec_buffer(void);

static void term_usart2_isr(void);

void _putchar(char byte);

void term_init(void) {
	term_init_gpio();
	term_init_usart();
}

void _putchar(char byte) {
	usart_send_blocking(USART2, byte);
}

static void term_init_gpio(void) {
	clock_enable_gpio(GPIOA);

	gpio_set_mode(GPIOA, 2, GPIO_MODE_AF);
	gpio_set_mode(GPIOA, 3, GPIO_MODE_AF);

	gpio_set_output_type(GPIOA, 3, GPIO_OUTPUT_OD);
	gpio_set_output_speed(GPIOA, 3, GPIO_SPEED_HIGH);

	gpio_set_af(GPIOA, 2, 7);
	gpio_set_af(GPIOA, 3, 7);
}

static void term_init_usart(void) {
	clock_enable_usart(USART2);

	usart_set_baudrate(USART2, 115200);
	usart_set_databits(USART2, 8);
	usart_set_stopbits(USART2, USART_STOP_1);
	usart_set_parity(USART2, USART_PARTIY_NONE);
	usart_set_mode(USART2, USART_MODE_TX_RX);

	vectors_register_isr(NVIC_USART2_IRQ, term_usart2_isr);
	vectors_enable_irq(NVIC_USART2_IRQ);

	usart_enable_rx_interrupt(USART2);
	usart_enable(USART2);

	usart_send_blocking(USART2, 'F');
	usart_send_blocking(USART2, 'U');
	usart_send_blocking(USART2, 'C');
	usart_send_blocking(USART2, 'K');
}

static void term_handle_byte(uint8_t byte) {
	if ((byte == TERM_CHAR_BS) || (byte == TERM_CHAR_DEL)) {
		if (s_cursor_pos > 0) {
			s_cursor_pos--;

			s_cmd_buffer[s_cursor_pos] = 0;

			printf(TERM_CSI_CUB(1) " " TERM_CSI_CUB(1));
		}
	} else if (byte == TERM_CHAR_CR) {
		s_cursor_pos = 0;

		printf("\r\n");

		term_exec_buffer();
	} else if (byte >= TERM_CHAR_SPACE && (byte < TERM_CHAR_DEL)) {
		if (s_cursor_pos < (TERM_CMD_BUFFER_SIZE - 1)) {
			s_cmd_buffer[s_cursor_pos] = byte;

			s_cursor_pos++;

			printf("%c", byte);
		}
	}
}

static void term_exec_buffer(void) {

}

static void term_usart2_isr(void) {
	if (USART2->SR & USART_SR_RXNE) {
		term_handle_byte(USART2->DR & USART_DR_MASK);
	}
}
