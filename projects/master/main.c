#include <hal/registers.h>
#include <hal/peripherals.h>
#include <hal/gpio.h>
#include <hal/spi.h>

#include <clock.h>
#include <delay.h>
#include <term.h>
#include <printf.h>

#include <intercom.h>

static void led_init(void) {
	clock_enable_gpio(GPIOD);

	gpio_set_mode(GPIOD, 12, GPIO_MODE_OUTPUT);
	gpio_set_mode(GPIOD, 13, GPIO_MODE_OUTPUT);
	gpio_set_mode(GPIOD, 14, GPIO_MODE_OUTPUT);
	gpio_set_mode(GPIOD, 15, GPIO_MODE_OUTPUT);

	gpio_set_output_type(GPIOD, 12, GPIO_OUTPUT_PP);
	gpio_set_output_type(GPIOD, 13, GPIO_OUTPUT_PP);
	gpio_set_output_type(GPIOD, 14, GPIO_OUTPUT_PP);
	gpio_set_output_type(GPIOD, 15, GPIO_OUTPUT_PP);

	gpio_set_output_speed(GPIOD, 12, GPIO_SPEED_HIGH);
	gpio_set_output_speed(GPIOD, 13, GPIO_SPEED_HIGH);
	gpio_set_output_speed(GPIOD, 14, GPIO_SPEED_HIGH);
	gpio_set_output_speed(GPIOD, 15, GPIO_SPEED_HIGH);

	gpio_set_pull(GPIOD, 12, GPIO_PULL_NONE);
	gpio_set_pull(GPIOD, 13, GPIO_PULL_NONE);
	gpio_set_pull(GPIOD, 14, GPIO_PULL_NONE);
	gpio_set_pull(GPIOD, 15, GPIO_PULL_NONE);
}

int main(void) {
	term_init();
	led_init();
	intercom_init();

	printf("Hello I am the master device\r\n");

	while (1) {
		//gpio_write(GPIOD, 12, !gpio_read(GPIOD, 12));
		//gpio_write(GPIOD, 13, !gpio_read(GPIOD, 13));
		//gpio_write(GPIOD, 14, !gpio_read(GPIOD, 14));
		//gpio_write(GPIOD, 15, !gpio_read(GPIOD, 15));

		//delay_ms(1000);

		term_update();

		uint32_t x;
		intercom_read(0, 0, &x);
		printf("0 = 0 = %u\r\n", x);

		uint32_t y;
		intercom_read(0, 1, &y);
		printf("0 = 1 = %u\r\n", y);

		char z[32];
		memset(z, 0, sizeof(z));
		intercom_read(0, 2, z);
		printf("0 = 2 = %s\r\n", z);

		char w[32];
		memset(w, 0, sizeof(w));
		intercom_read(0, 3, w);
		printf("0 = 3 = %s\r\n", w);
	}

	return 0;
}
