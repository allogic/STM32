#include <core/attributes.h>

#include <container/queue.h>

#include <hal/registers.h>
#include <hal/peripherals.h>
#include <hal/usart.h>
#include <hal/gpio.h>

#include <clock.h>
#include <vectors.h>
#include <term.h>
#include <printf.h>

static uint32_t s_line_length;

static ALIGN(4) uint8_t s_char_buffer[TERM_CHAR_QUEUE_SIZE];

static queue_t s_char_queue;

static ALIGN(4) uint8_t s_line_buffer[TERM_LINE_BUFFER_SIZE];
static ALIGN(4) uint8_t s_arg_buffer[TERM_ARG_BUFFER_SIZE];

static void term_init_gpio(void);
static void term_init_usart(void);

static bool term_data_is_ctrl_code(uint8_t data);
static bool term_data_is_printable(uint8_t data);

static void term_handle_return(void);
static void term_handle_backspace(void);
static void term_handle_print(uint8_t data);

static void term_handle_data(uint8_t data);
static void term_exec_buffer(void);

static void term_usart2_handler(void);

void _putchar(char byte) {
	usart_send(USART2, byte);
}

void term_init(void) {
	queue_init(&s_char_queue, sizeof(uint8_t), TERM_CHAR_QUEUE_SIZE, sizeof(s_char_buffer), s_char_buffer);

	term_init_gpio();
	term_init_usart();
}

void term_update(void) {
	while (!queue_empty(&s_char_queue)) {
		uint8_t data;

		queue_pop(&s_char_queue, &data);

		term_handle_data(data);
	}
}

static void term_init_gpio(void) {
	clock_enable_gpio(GPIOA);

	gpio_set_mode(GPIOA, 2, GPIO_MODE_AF); // TX
	gpio_set_mode(GPIOA, 3, GPIO_MODE_AF); // RX

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

	vectors_register_isr(NVIC_USART2_IRQ, term_usart2_handler);
	vectors_enable_irq(NVIC_USART2_IRQ);

	usart_enable_rx_interrupt(USART2);
	usart_enable(USART2);
}

static bool term_data_is_ctrl_code(uint8_t data) {
	return data < ' ';
}

static bool term_data_is_printable(uint8_t data) {
	return (data >= ' ') && (data <= '~');
}

static void term_handle_return(void) {
	printf("\r\n");

	term_exec_buffer();

	memset(s_line_buffer, 0, s_line_length);

	s_line_length = 0;
}

static void term_handle_backspace(void) {
	if (s_line_length > 0) {
		s_line_buffer[s_line_length--] = 0;
	}
}

static void term_handle_print(uint8_t data) {
	if (s_line_length < (TERM_LINE_BUFFER_SIZE - 1)) {
		s_line_buffer[s_line_length++] = data;

		printf("%c", data);
	}
}

static void term_handle_data(uint8_t data) {
	if (term_data_is_ctrl_code(data)) {
		if (data == TERM_CTRL_CR) {
			term_handle_return();
		} else if (data == TERM_CTRL_BS) {
			term_handle_backspace();
		}
	} else if (term_data_is_printable(data)) {
		term_handle_print(data);
	}
}

static void term_exec_buffer(void) {
	
}

static void term_usart2_handler(void) {
	if (!usart_rx_buffer_empty(USART2)) {
		uint8_t data = usart_read(USART2);

		queue_push(&s_char_queue, &data);
	}
}
