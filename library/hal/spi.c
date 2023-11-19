#include <hal/spi.h>

void spi_set_master_mode(spi_t* spi) {
	spi->CR1 |= SPI_CR1_MSTR;
	spi->CR2 |= SPI_CR2_SSOE;
}

void spi_set_slave_mode(spi_t* spi) {
	spi->CR1 &= ~SPI_CR1_MSTR;
	spi->CR2 &= ~SPI_CR2_SSOE;
}

void spi_set_bidirectional(spi_t* spi) {
	spi->CR1 |= SPI_CR1_BIDIMODE;
}

void spi_set_unidirectional(spi_t* spi) {
	spi->CR1 &= ~SPI_CR1_BIDIMODE;
}

void spi_set_clk_prescaler(spi_t* spi, uint32_t prescaler) {
	spi->CR1 &= ~SPI_CR1_BR_MASK;
	spi->CR1 |= prescaler;
}

void spi_set_clk_phase(spi_t* spi, uint32_t phase) {
	spi->CR1 &= ~SPI_CR1_CPHA_MASK;
	spi->CR1 |= phase;
}

void spi_set_clk_polarity(spi_t* spi, uint32_t polarity) {
	spi->CR1 &= ~SPI_CR1_CPOL_MASK;
	spi->CR1 |= polarity;
}

void spi_set_full_duplex(spi_t* spi) {
	spi->CR1 &= ~SPI_CR1_RXONLY;
}

void spi_set_receive_only(spi_t* spi) {
	spi->CR1 |= SPI_CR1_RXONLY;
}

void spi_set_frame_format(spi_t* spi, uint32_t format) {
	spi->CR1 &= ~SPI_CR1_LSBFIRST_MASK;
	spi->CR1 |= format;
}

void spi_set_frame_size(spi_t* spi, uint32_t size) {
	spi->CR2 &= ~SPI_CR1_DFF_MASK;
	spi->CR2 |= size;
}

void spi_set_nss_high(spi_t* spi) {
	spi->CR1 |= SPI_CR1_SSI;
}

void spi_set_nss_low(spi_t* spi) {
	spi->CR1 &= ~SPI_CR1_SSI;
}

void spi_enable_software_slave_mgmt(spi_t* spi) {
	spi->CR1 |= SPI_CR1_SSM;
}

void spi_disable_software_slave_mgmt(spi_t* spi) {
	spi->CR1 &= ~SPI_CR1_SSM;
}

void spi_enable_tx_interrupt(spi_t* spi) {
	spi->CR2 |= SPI_CR2_TXEIE;
}

void spi_enable_rx_interrupt(spi_t* spi) {
	spi->CR2 |= SPI_CR2_RXNEIE;
}

void spi_disable_tx_interrupt(spi_t* spi) {
	spi->CR2 &= ~SPI_CR2_TXEIE;
}

void spi_disable_rx_interrupt(spi_t* spi) {
	spi->CR2 &= ~SPI_CR2_RXNEIE;
}

void spi_enable_crc(spi_t* spi) {
	spi->CR1 |= SPI_CR1_CRCEN;
}

void spi_disable_crc(spi_t* spi) {
	spi->CR1 &= ~SPI_CR1_CRCEN;
}

void spi_enable(spi_t* spi) {
	spi->CR1 |= SPI_CR1_SPE;
}

void spi_disable(spi_t* spi) {
	spi->CR1 &= ~SPI_CR1_SPE;
}

void spi_write(spi_t* spi, uint16_t data) {
	spi->DR = data;
}

uint16_t spi_read(spi_t* spi) {
	return spi->DR & 0xFFFF;
}

void spi_send(spi_t* spi, uint16_t data) {
	while ((spi->SR & SPI_SR_TXE) == 0);
	spi->DR = data;
}

uint16_t spi_recv(spi_t* spi) {
	while ((spi->SR & SPI_SR_RXNE) == 0);
	return spi->DR & 0xFFFF;
}

uint16_t spi_xfer(spi_t* spi, uint16_t data) {
	while ((spi->SR & SPI_SR_TXE) == 0);
	spi->DR = data;
	while ((spi->SR & SPI_SR_RXNE) == 0);
	return spi->DR & 0xFFFF;
}
