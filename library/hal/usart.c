#include <hal/usart.h>

#include <clock.h>

void usart_set_baudrate(usart_t* usart, uint32_t baud) {
	uint32_t clock = clock_get_usart_clk_freq(usart);

	usart->BRR = (clock + (baud / 2)) / baud;
}

void usart_set_databits(usart_t* usart, uint32_t bits) {
	if (bits == 8) {
		usart->CR1 &= ~USART_CR1_M;
	} else {
		usart->CR1 |= USART_CR1_M;
	}
}

void usart_set_stopbits(usart_t* usart, uint32_t bits) {
	usart->CR2 &= ~USART_CR2_STOP_MASK;
	usart->CR2 |= bits;
}

void usart_set_parity(usart_t* usart, uint32_t parity) {
	usart->CR1 &= ~USART_CR1_PARTIY_MASK;
	usart->CR2 |= parity;
}

void usart_set_mode(usart_t* usart, uint32_t mode) {
	usart->CR1 &= ~USART_CR1_MODE_MASK;
	usart->CR1 |= mode;
}

void usart_enable_tx_interrupt(usart_t* usart) {
	usart->CR1 |= USART_CR1_TXEIE;
}

void usart_enable_rx_interrupt(usart_t* usart) {
	usart->CR1 |= USART_CR1_RXNEIE;
}

void usart_disable_tx_interrupt(usart_t* usart) {
	usart->CR1 &= ~USART_CR1_TXEIE;
}

void usart_disable_rx_interrupt(usart_t* usart) {
	usart->CR1 &= ~USART_CR1_RXNEIE;
}

void usart_enable(usart_t* usart) {
	usart->CR1 |= USART_CR1_UE;
}

void usart_disable(usart_t* usart) {
	usart->CR1 &= ~USART_CR1_UE;
}

void usart_send(usart_t* usart, uint8_t data) {
	while ((usart->SR & USART_SR_TXE) == 0);
	usart->DR = data;
}

uint8_t usart_recv(usart_t* usart) {
	while ((usart->SR & USART_SR_RXNE) == 0);
	return usart->DR;
}
