#ifndef STM32F4_HAL_USART_H
#define STM32F4_HAL_USART_H

#include <stdbool.h>
#include <stdint.h>

#include <hal/registers.h>

#define USART_SR_RXNE (1 << 5)
#define USART_SR_TXE  (1 << 7)

#define USART_CR1_RE     (1 << 2)
#define USART_CR1_TE     (1 << 3)
#define USART_CR1_RXNEIE (1 << 5)
#define USART_CR1_TXEIE  (1 << 7)
#define USART_CR1_PS     (1 << 9)
#define USART_CR1_PCE    (1 << 10)
#define USART_CR1_M      (1 << 12)
#define USART_CR1_UE     (1 << 13)

#define USART_CR1_MODE_MASK (USART_CR1_RE | USART_CR1_TE)

#define USART_MODE_RX    (USART_CR1_RE)
#define USART_MODE_TX    (USART_CR1_TE)
#define USART_MODE_TX_RX (USART_CR1_RE | USART_CR1_TE)

#define USART_CR1_PARTIY_MASK (USART_CR1_PCE | USART_CR1_PS)

#define USART_PARTIY_NONE (0)
#define USART_PARTIY_EVEN (USART_CR1_PCE)
#define USART_PARTIY_ODD  (USART_CR1_PCE | USART_CR1_PS)

#define USART_CR2_STOP0 (1 << 12)
#define USART_CR2_STOP1 (1 << 13)

#define USART_CR2_STOP_MASK (USART_CR2_STOP0 | USART_CR2_STOP1)
#define USART_CR2_STOP_POS  (12)

#define USART_STOP_1   (0b00 << USART_CR2_STOP_POS)
#define USART_STOP_0_5 (0b01 << USART_CR2_STOP_POS)
#define USART_STOP_2   (0b10 << USART_CR2_STOP_POS)
#define USART_STOP_1_5 (0b11 << USART_CR2_STOP_POS)

void usart_set_baudrate(usart_t* usart, uint32_t baud);
void usart_set_databits(usart_t* usart, uint32_t bits);
void usart_set_stopbits(usart_t* usart, uint32_t bits);
void usart_set_parity(usart_t* usart, uint32_t parity);
void usart_set_mode(usart_t* usart, uint32_t mode);

void usart_enable_tx_interrupt(usart_t* usart);
void usart_enable_rx_interrupt(usart_t* usart);

void usart_disable_tx_interrupt(usart_t* usart);
void usart_disable_rx_interrupt(usart_t* usart);

bool usart_tx_buffer_empty(usart_t* usart);
bool usart_rx_buffer_empty(usart_t* usart);

void usart_enable(usart_t* usart);
void usart_disable(usart_t* usart);

void usart_write(usart_t* usart, uint8_t data);
uint8_t usart_read(usart_t* usart);

void usart_send(usart_t* usart, uint8_t data);
uint8_t usart_recv(usart_t* usart);

#endif
