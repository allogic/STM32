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

typedef struct {
	void* data;
	uint32_t size;
} spi_variable_t;

static uint32_t s_dummy_x = 42;
static uint32_t s_dummy_y = 666;
static char s_dummy_z[32] = "Hello World";
static char s_dummy_w[32] = "I'm a dummy string";

static spi_variable_t s_variables[] = {
	{ &s_dummy_x, sizeof(s_dummy_x) },
	{ &s_dummy_y, sizeof(s_dummy_y) },
	{ s_dummy_z, sizeof(s_dummy_z) },
	{ s_dummy_w, sizeof(s_dummy_w) },
};

static void intercom_init_gpio(void);
static void intercom_init_spi(void);

static void intercom_spi1_handler(void);
static void intercom_spi3_handler(void);

void intercom_init(void) {
	intercom_init_gpio();
	intercom_init_spi();
}

static void intercom_init_gpio(void) {
	clock_enable_gpio(GPIOA);
	clock_enable_gpio(GPIOB);
	clock_enable_gpio(GPIOC);

	gpio_set_mode(GPIOA, 15, GPIO_MODE_AF); // NSS
	gpio_set_mode(GPIOB, 3, GPIO_MODE_AF); // SCK
	gpio_set_mode(GPIOB, 4, GPIO_MODE_AF); // MISO
	gpio_set_mode(GPIOB, 5, GPIO_MODE_AF); // MOSI

	gpio_set_mode(GPIOA, 4, GPIO_MODE_AF); // NSS
	gpio_set_mode(GPIOC, 10, GPIO_MODE_AF); // SCK
	gpio_set_mode(GPIOC, 11, GPIO_MODE_AF); // MISO
	gpio_set_mode(GPIOC, 12, GPIO_MODE_AF); // MOSI

	gpio_set_af(GPIOA, 15, 5);
	gpio_set_af(GPIOB, 3, 5);
	gpio_set_af(GPIOB, 4, 5);
	gpio_set_af(GPIOB, 5, 5);

	gpio_set_af(GPIOA, 4, 6);
	gpio_set_af(GPIOC, 10, 6);
	gpio_set_af(GPIOC, 11, 6);
	gpio_set_af(GPIOC, 12, 6);
}

static void intercom_init_spi(void) {
	clock_enable_spi(SPI1);
	clock_enable_spi(SPI3);

	spi_set_slave_mode(SPI1);
	spi_set_clk_prescaler(SPI1, SPI_CLK_DIV256);
	spi_set_clk_phase(SPI1, SPI_CLK_PHASE_0);
	spi_set_clk_polarity(SPI1, SPI_CLK_POLARITY_0);
	spi_set_full_duplex(SPI1);
	spi_set_frame_format(SPI1, SPI_FRAME_FORMAT_LSBFIRST);
	spi_set_frame_size(SPI1, SPI_FRAME_SIZE_8);

	spi_set_slave_mode(SPI3);
	spi_set_clk_prescaler(SPI3, SPI_CLK_DIV256);
	spi_set_clk_phase(SPI3, SPI_CLK_PHASE_0);
	spi_set_clk_polarity(SPI3, SPI_CLK_POLARITY_0);
	spi_set_full_duplex(SPI3);
	spi_set_frame_format(SPI3, SPI_FRAME_FORMAT_LSBFIRST);
	spi_set_frame_size(SPI3, SPI_FRAME_SIZE_8);

	vectors_register_isr(NVIC_SPI1_IRQ, intercom_spi1_handler);
	vectors_register_isr(NVIC_SPI3_IRQ, intercom_spi3_handler);

	vectors_enable_irq(NVIC_SPI1_IRQ);
	vectors_enable_irq(NVIC_SPI3_IRQ);

	spi_enable_rx_interrupt(SPI1);
	spi_enable_rx_interrupt(SPI3);

	spi_enable(SPI1);
	spi_enable(SPI3);
}

static void intercom_spi1_handler(void) {
	static spi_state_t state = SPI_STATE_INIT;

	if (!spi_rx_buffer_empty(SPI1)) {
		switch (state) {
			case SPI_STATE_INIT: {
				state = spi_read(SPI1);

				spi_write(SPI1, 0xFF);

				break;
			}
			case SPI_STATE_READ: {
				static uint32_t offset = 0;

				uint8_t index = spi_read(SPI1);

				uint8_t data = (s_variables[index].size >> offset) & 0xFF;

				spi_write(SPI1, data);

				offset += 8;

				if (offset > 32) {
					offset = 0;
					state = SPI_STATE_DATA;
				}

				break;
			}
			case SPI_STATE_WRITE: {
				// TODO

				break;
			}
			case SPI_STATE_DATA: {
				static uint32_t offset = 0;

				uint8_t index = spi_read(SPI1);

				uint8_t data = *(((uint8_t*)s_variables[index].data) + offset);

				offset += 1;

				if (offset > s_variables[index].size) {
					offset = 0;
					state = SPI_STATE_INIT;
				}

				spi_write(SPI1, data);

				break;
			}
		}
	}
}

static void intercom_spi3_handler(void) {
	// TODO
}
