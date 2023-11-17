#include <core/attributes.h>
#include <core/macros.h>

#include <hal/registers.h>
#include <hal/peripherals.h>
#include <hal/clock.h>
#include <hal/usart.h>
#include <hal/gpio.h>
#include <hal/vectors.h>

#include <term.h>
#include <printf.h>

typedef enum {
    ANSI_STATE_INIT,
    ANSI_STATE_ESCAPE,
    ANSI_STATE_BRACKET,
    ANSI_STATE_NUMERIC,
	ANSI_STATE_ALPHANUMERIC,
    ANSI_STATE_SEMICOLON
} ansi_state_t;

static ansi_state_t s_ansi_state = ANSI_STATE_INIT;

static uint32_t s_cursor_pos;
static uint32_t s_line_length;

static ALIGN(4) uint8_t s_line_buffer[TERM_LINE_BUFFER_SIZE];
static ALIGN(4) uint8_t s_arg_buffer[TERM_ARG_BUFFER_SIZE];

static void term_init_gpio(void);
static void term_init_usart(void);

static bool term_byte_is_ctrl_code(uint8_t byte);
static bool term_byte_is_printable(uint8_t byte);
static bool term_byte_is_numeric(uint8_t byte);
static bool term_byte_is_alphanumeric(uint8_t byte);

static void term_move_cursor_back(void);
static void term_move_cursor_forward(void);

static void term_select_prev_cmd(void);
static void term_select_next_cmd(void);

static void term_handle_ansi(uint8_t byte);
static void term_exec_buffer(void);

static void term_usart2_handler(void);

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

	vectors_register_isr(NVIC_USART2_IRQ, term_usart2_handler);
	vectors_enable_irq(NVIC_USART2_IRQ);

	usart_enable_rx_interrupt(USART2);
	usart_enable(USART2);
}

static bool term_byte_is_ctrl_code(uint8_t byte) {
	return byte < TERM_CHAR_SPACE;
}

static bool term_byte_is_printable(uint8_t byte) {
	return (byte >= TERM_CHAR_SPACE) && (byte < TERM_CHAR_DEL);
}

static bool term_byte_is_numeric(uint8_t byte) {
	return (byte >= TERM_CHAR_0) && (byte <= TERM_CHAR_9);
}

static bool term_byte_is_alphanumeric(uint8_t byte) {
	return (((byte >= TERM_CHAR_AU) && (byte <= TERM_CHAR_ZU)) || ((byte >= TERM_CHAR_AL) && (byte <= TERM_CHAR_ZL)));
}

static void term_move_cursor_back(void) {
	if ((s_cursor_pos > 0) && (s_cursor_pos <= s_line_length)) {
		s_cursor_pos--;

		printf(TERM_MOVE_CURSOR_BACK);
	}
}

static void term_move_cursor_forward(void) {
	if (s_cursor_pos < s_line_length) {
		s_cursor_pos++;

		printf(TERM_MOVE_CURSOR_FORWARD);
	}
}

static void term_select_prev_cmd(void) {

}

static void term_select_next_cmd(void) {

}

static void term_handle_ansi(uint8_t byte) {
	switch (s_ansi_state) {
		case ANSI_STATE_INIT: {
			if (byte == TERM_CHAR_ESC) {
				s_ansi_state = ANSI_STATE_ESCAPE;
			} else if (byte == TERM_CHAR_CR) {
				s_cursor_pos = 0;
				s_line_length = 0;
	
				printf("\r\n");
	
				term_exec_buffer();
			} else if (byte == TERM_CHAR_BS) {
				if (s_cursor_pos > 0) {
					s_cursor_pos--;

					uint32_t delta = s_line_length - s_cursor_pos;
					for (uint32_t i = 0; i < delta; ++i) {
						s_line_buffer[s_cursor_pos + i] = s_line_buffer[s_cursor_pos + i + 1];
					}

					printf(TERM_MOVE_CURSOR_BACK);
					printf(TERM_STORE_CURSOR_POS);
					printf(TERM_ERASE_FROM_CURSOR_TO_EOL);
					printf("%s", s_line_buffer + s_cursor_pos);
					printf(TERM_RESTORE_CURSOR_POS);
				}
			} else if (term_byte_is_printable(byte)) {
				if (s_line_length < (TERM_LINE_BUFFER_SIZE - 1)) {
					s_line_buffer[s_cursor_pos] = byte;

					s_cursor_pos++;
					s_line_length = MAX(s_line_length, s_cursor_pos);

					uint32_t delta = s_line_length - s_cursor_pos;
					for (uint32_t i = delta; i >= 0; --i) {
						s_line_buffer[s_cursor_pos + i + 1] = s_line_buffer[s_cursor_pos + i];
					}

					printf("%c", byte);
					printf(TERM_STORE_CURSOR_POS);
					//printf(TERM_ERASE_FROM_CURSOR_TO_EOL);
					printf("%s", s_line_buffer + s_cursor_pos);
					printf(TERM_RESTORE_CURSOR_POS);
				}
			}

			break;
		}
		case ANSI_STATE_ESCAPE: {
			if (byte == TERM_CHAR_LSQBR) {
				s_ansi_state = ANSI_STATE_BRACKET;
			} else {
				s_ansi_state = ANSI_STATE_INIT;
			}

			break;
		}
		case ANSI_STATE_BRACKET: {
			if (term_byte_is_numeric(byte)) {
				s_ansi_state = ANSI_STATE_NUMERIC;
			} else if (term_byte_is_alphanumeric(byte)) {
				if (byte == TERM_CHAR_DU) {
					term_move_cursor_back();
				} else if (byte == TERM_CHAR_CU) {
					term_move_cursor_forward();
				} else if (byte == TERM_CHAR_AU) {
					term_select_prev_cmd();
				} else if (byte == TERM_CHAR_BU) {
					term_select_next_cmd();
				}

				s_ansi_state = ANSI_STATE_INIT;
			} else {
				s_ansi_state = ANSI_STATE_INIT;
			}

			break;
		}
		case ANSI_STATE_NUMERIC: {
			if (byte == TERM_CHAR_SEMICOLON) {
				s_ansi_state = ANSI_STATE_SEMICOLON;
			} else {
				s_ansi_state = ANSI_STATE_INIT;
			}

			break;
		}
		case ANSI_STATE_ALPHANUMERIC: {
			s_ansi_state = ANSI_STATE_INIT;

			break;
		}
		case ANSI_STATE_SEMICOLON: {
			if (term_byte_is_numeric(byte)) {
				s_ansi_state = ANSI_STATE_NUMERIC;
			} else {
				s_ansi_state = ANSI_STATE_INIT;
			}

			break;
		}
	}
}

static void term_exec_buffer(void) {
	printf("EXEC LINE: [%s]\r\n", s_line_buffer);
	memset(s_line_buffer, 0, TERM_LINE_BUFFER_SIZE);
}

static void term_usart2_handler(void) {
	if (USART2->SR & USART_SR_RXNE) {
		term_handle_ansi(USART2->DR & USART_DR_MASK);
	}
}
