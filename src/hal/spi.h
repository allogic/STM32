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
#define SPI_CR1_CRCNEXT  (1 << 12)
#define SPI_CR1_CRCEN    (1 << 13)

#define SPI_CR1_CPHA_POS     (0)
#define SPI_CR1_CPOL_POS     (1)
#define SPI_CR1_LSBFIRST_POS (7)

#define SPI_CPHA_CLK_TRANSITION_1 (0 << SPI_CR1_CPHA_POS)
#define SPI_CPHA_CLK_TRANSITION_2 (1 << SPI_CR1_CPHA_POS)

#define SPI_CPOL_CLK_TO_0_WHEN_IDLE (0 << SPI_CR1_CPOL_POS)
#define SPI_CPOL_CLK_TO_1_WHEN_IDLE (1 << SPI_CR1_CPOL_POS)

#define SPI_LSBFIRST (1 << SPI_CR1_LSBFIRST_POS)

#define SPI_CR1_BR_MASK (SPI_CR1_BR0 | SPI_CR1_BR1 | SPI_CR1_BR2)
#define SPI_CR1_BR_POS  (3)

#define SPI_BAUD_DIV2   (0b000 << SPI_CR1_BR_POS)
#define SPI_BAUD_DIV4   (0b001 << SPI_CR1_BR_POS)
#define SPI_BAUD_DIV8   (0b010 << SPI_CR1_BR_POS)
#define SPI_BAUD_DIV16  (0b011 << SPI_CR1_BR_POS)
#define SPI_BAUD_DIV32  (0b100 << SPI_CR1_BR_POS)
#define SPI_BAUD_DIV64  (0b101 << SPI_CR1_BR_POS)
#define SPI_BAUD_DIV128 (0b110 << SPI_CR1_BR_POS)
#define SPI_BAUD_DIV256 (0b111 << SPI_CR1_BR_POS)

#define SPI_CR2_SSOE (1 << 2)

void spi_init_master(spi_t* spi, uint32_t baud, uint32_t clk_pol, uint32_t clk_pha, uint32_t lsbfirst);

#endif
