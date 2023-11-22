#include <hal/registers.h>
#include <hal/peripherals.h>
#include <hal/gpio.h>
#include <hal/spi.h>

#include <clock.h>
#include <vectors.h>
#include <printf.h>

#include <intercom.h>

typedef enum {
	SPI_STATE_INIT,
	SPI_STATE_READ,
	SPI_STATE_WRITE,
	SPI_STATE_DATA,
} spi_state_t;

static void intercom_init_gpio(void);
static void intercom_init_spi(void);

void intercom_init(void) {
	intercom_init_gpio();
	intercom_init_spi();
}

void intercom_read(uint8_t slave, uint8_t index, void* data) {
	gpio_write(GPIOB, slave, 0);

	spi_xfer(SPI1, SPI_STATE_READ);
	spi_xfer(SPI1, index);

	uint8_t a = spi_xfer(SPI1, index);
	uint8_t b = spi_xfer(SPI1, index);
	uint8_t c = spi_xfer(SPI1, index);
	uint8_t d = spi_xfer(SPI1, index);

	uint32_t size = (d << 24) | (c << 16) | (b << 8) | a;

	spi_xfer(SPI1, index);

	for (uint32_t i = 0; i < size; ++i) {
		*(((uint8_t*)data) + i) = spi_xfer(SPI1, index);
	}

	gpio_write(GPIOB, slave, 1);
}

static void intercom_init_gpio(void) {
	clock_enable_gpio(GPIOB);

	gpio_set_mode(GPIOB, 0, GPIO_MODE_OUTPUT); // CS
	gpio_set_mode(GPIOB, 1, GPIO_MODE_OUTPUT); // CS

	gpio_set_mode(GPIOB, 3, GPIO_MODE_AF); // SCK
	gpio_set_mode(GPIOB, 4, GPIO_MODE_AF); // MISO
	gpio_set_mode(GPIOB, 5, GPIO_MODE_AF); // MOSI

	gpio_set_output_speed(GPIOB, 0, GPIO_SPEED_HIGH);
	gpio_set_output_speed(GPIOB, 1, GPIO_SPEED_HIGH);
	gpio_set_output_speed(GPIOB, 3, GPIO_SPEED_HIGH);
	gpio_set_output_speed(GPIOB, 4, GPIO_SPEED_HIGH);
	gpio_set_output_speed(GPIOB, 5, GPIO_SPEED_HIGH);

	gpio_set_pull(GPIOB, 0, GPIO_PULL_UP);
	gpio_set_pull(GPIOB, 1, GPIO_PULL_UP);

	gpio_write(GPIOB, 0, 1);
	gpio_write(GPIOB, 1, 1);

	gpio_set_af(GPIOB, 3, 5);
	gpio_set_af(GPIOB, 4, 5);
	gpio_set_af(GPIOB, 5, 5);
}

static void intercom_init_spi(void) {
	clock_enable_spi(SPI1);

	spi_set_master_mode(SPI1);
	spi_set_clk_prescaler(SPI1, SPI_CLK_DIV256);
	spi_set_clk_phase(SPI1, SPI_CLK_PHASE_0);
	spi_set_clk_polarity(SPI1, SPI_CLK_POLARITY_0);
	spi_set_full_duplex(SPI1);
	spi_set_frame_format(SPI1, SPI_FRAME_FORMAT_LSBFIRST);
	spi_set_frame_size(SPI1, SPI_FRAME_SIZE_8);

	spi_enable(SPI1);
}
