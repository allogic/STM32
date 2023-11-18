#ifndef STM32F4_HAL_SPI_H
#define STM32F4_HAL_SPI_H

#include <stdint.h>

#include <hal/registers.h>

#define SPI_CR1_CPHA     (1 << 0)
#define SPI_CR1_CPOL     (1 << 1)
#define SPI_CR1_MSTR     (1 << 2)
#define SPI_CR1_BR0      (1 << 3)
#define SPI_CR1_BR1      (1 << 4)
#define SPI_CR1_BR2      (1 << 5)
#define SPI_CR1_SPE      (1 << 6)
#define SPI_CR1_LSBFIRST (1 << 7)
#define SPI_CR1_RXONLY   (1 << 10)
#define SPI_CR1_DFF      (1 << 11)
#define SPI_CR1_CRCNEXT  (1 << 12)
#define SPI_CR1_CRCEN    (1 << 13)
#define SPI_CR1_BIDIOE   (1 << 14)
#define SPI_CR1_BIDIMODE (1 << 15)

#define SPI_CR1_CPHA_MASK (SPI_CR1_CPHA)
#define SPI_CR1_CPHA_POS  (0)

#define SPI_CR1_CPOL_MASK (SPI_CR1_CPOL)
#define SPI_CR1_CPOL_POS  (1)

#define SPI_CR1_MSTR_MASK (SPI_CR1_MSTR)
#define SPI_CR1_MSTR_POS  (2)

#define SPI_CR1_BR_MASK (SPI_CR1_BR0 | SPI_CR1_BR1 | SPI_CR1_BR2)
#define SPI_CR1_BR_POS  (3)

#define SPI_CR1_LSBFIRST_MASK (SPI_CR1_LSBFIRST)
#define SPI_CR1_LSBFIRST_POS  (7)

#define SPI_CR1_DFF_MASK (SPI_CR1_DFF)
#define SPI_CR1_DFF_POS  (11)

#define SPI_CLK_POLARITY_0 (0 << SPI_CR1_CPHA_POS)
#define SPI_CLK_POLARITY_1 (1 << SPI_CR1_CPHA_POS)

#define SPI_CLK_PHASE_0 (0 << SPI_CR1_CPOL_POS)
#define SPI_CLK_PHASE_1 (1 << SPI_CR1_CPOL_POS)

#define SPI_MODE_SLAVE  (0 << SPI_CR1_MSTR_POS)
#define SPI_MODE_MASTER (1 << SPI_CR1_MSTR_POS)

#define SPI_CLK_DIV2   (0b000 << SPI_CR1_BR_POS)
#define SPI_CLK_DIV4   (0b001 << SPI_CR1_BR_POS)
#define SPI_CLK_DIV8   (0b010 << SPI_CR1_BR_POS)
#define SPI_CLK_DIV16  (0b011 << SPI_CR1_BR_POS)
#define SPI_CLK_DIV32  (0b100 << SPI_CR1_BR_POS)
#define SPI_CLK_DIV64  (0b101 << SPI_CR1_BR_POS)
#define SPI_CLK_DIV128 (0b110 << SPI_CR1_BR_POS)
#define SPI_CLK_DIV256 (0b111 << SPI_CR1_BR_POS)

#define SPI_FRAME_FORMAT_MSBFIRST (1 << SPI_CR1_LSBFIRST_POS)
#define SPI_FRAME_FORMAT_LSBFIRST (1 << SPI_CR1_LSBFIRST_POS)

#define SPI_FRAME_SIZE_8  (0 << SPI_CR1_DFF_POS)
#define SPI_FRAME_SIZE_16 (1 << SPI_CR1_DFF_POS)

#define SPI_CR2_SSOE   (1 << 2)
#define SPI_CR2_RXNEIE (1 << 6)
#define SPI_CR2_TXEIE  (1 << 7)

#define SPI_SR_RXNE (1 << 0)
#define SPI_SR_TXE  (1 << 1)

void spi_set_mode(spi_t* spi, uint32_t mode);
void spi_set_bidirectional(spi_t* spi);
void spi_set_unidirectional(spi_t* spi);
void spi_set_clk_prescaler(spi_t* spi, uint32_t prescaler);
void spi_set_clk_phase(spi_t* spi, uint32_t phase);
void spi_set_clk_polarity(spi_t* spi, uint32_t polarity);
void spi_set_full_duplex(spi_t* spi);
void spi_set_receive_only(spi_t* spi);
void spi_set_frame_format(spi_t* spi, uint32_t format);
void spi_set_frame_size(spi_t* spi, uint32_t size);

void spi_enable_tx_interrupt(spi_t* spi);
void spi_enable_rx_interrupt(spi_t* spi);

void spi_disable_tx_interrupt(spi_t* spi);
void spi_disable_rx_interrupt(spi_t* spi);

void spi_enable_crc(spi_t* spi);
void spi_disable_crc(spi_t* spi);

void spi_enable(spi_t* spi);
void spi_disable(spi_t* spi);

void spi_write(spi_t* spi, uint16_t data);

void spi_send(spi_t* spi, uint16_t data);
uint16_t spi_recv(spi_t* spi);
uint16_t spi_xfer(spi_t* spi, uint16_t data);

#endif
