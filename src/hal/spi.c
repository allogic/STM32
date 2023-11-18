#include <hal/spi.h>

void spi_init_master(spi_t* spi, uint32_t baud, uint32_t clk_pol, uint32_t clk_pha, uint32_t lsbfirst) {
	spi->CR1 &= ~(SPI_CR1_SPE | SPI_CR1_CRCEN | SPI_CR1_CRCNEXT);

	spi->CR1 |= SPI_CR1_MSTR;
	spi->CR1 |= baud;
	spi->CR1 |= clk_pol;
	spi->CR1 |= clk_pha;
	spi->CR1 |= lsbfirst;

	spi->CR2 |= SPI_CR2_SSOE;
}
