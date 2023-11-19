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

void intercom_init(void) {
	intercom_init_gpio();
	intercom_init_spi();
}

void intercom_transfer(void) {
	static uint8_t data = 0xBB;

	printf("Data:%X\r\n", data);

	data = spi_xfer(SPI1, data);
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

	spi_enable(SPI1);
}
