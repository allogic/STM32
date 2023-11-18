#include <hal/registers.h>
#include <hal/peripherals.h>
#include <hal/gpio.h>
#include <hal/spi.h>

#include <clock.h>
#include <vectors.h>
#include <printf.h>

#include <intercom.h>

static void intercom_init_gpio(void);
static void intercom_init_spi(void);

static void intercom_spi1_handler(void);

void intercom_init(void) {
	intercom_init_gpio();
	intercom_init_spi();
}

static void intercom_init_gpio(void) {
	clock_enable_gpio(GPIOA);

	gpio_set_mode(GPIOA, 4, GPIO_MODE_INPUT); // NSS
	gpio_set_mode(GPIOA, 5, GPIO_MODE_AF); // SCK
	gpio_set_mode(GPIOA, 6, GPIO_MODE_AF); // MISO
	gpio_set_mode(GPIOA, 7, GPIO_MODE_AF); // MOSI

	gpio_set_pull(GPIOA, 4, GPIO_PULL_NONE);
	gpio_set_pull(GPIOA, 5, GPIO_PULL_NONE);
	gpio_set_pull(GPIOA, 6, GPIO_PULL_NONE);
	gpio_set_pull(GPIOA, 7, GPIO_PULL_NONE);

	gpio_set_af(GPIOA, 5, 5);
	gpio_set_af(GPIOA, 6, 5);
	gpio_set_af(GPIOA, 7, 5);
}

static void intercom_init_spi(void) {
	clock_enable_spi(SPI1);

	spi_set_slave_mode(SPI1);
	spi_set_clk_prescaler(SPI1, SPI_CLK_DIV64);
	spi_set_clk_phase(SPI1, SPI_CLK_PHASE_0);
	spi_set_clk_polarity(SPI1, SPI_CLK_POLARITY_0);
	spi_set_full_duplex(SPI1);
	spi_set_frame_format(SPI1, SPI_FRAME_FORMAT_LSBFIRST);
	spi_set_frame_size(SPI1, SPI_FRAME_SIZE_8);

	vectors_register_isr(NVIC_SPI1_IRQ, intercom_spi1_handler);
	vectors_enable_irq(NVIC_SPI1_IRQ);

	spi_enable_rx_interrupt(SPI1);
	spi_enable(SPI1);
}

static void intercom_spi1_handler(void) {
	if (SPI1->SR & SPI_SR_RXNE) {
		printf("Received:%X\r\n", (uint8_t)(SPI1->DR & 0xFF));
	}
}
