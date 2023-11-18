#include <hal/registers.h>
#include <hal/peripherals.h>
#include <hal/gpio.h>
#include <hal/clock.h>

#include <delay.h>
#include <term.h>
#include <printf.h>

int main(void) {
	term_init();

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

	while (1) {
		gpio_write(GPIOD, 12, !gpio_read(GPIOD, 12));
		gpio_write(GPIOD, 13, !gpio_read(GPIOD, 13));
		gpio_write(GPIOD, 14, !gpio_read(GPIOD, 14));
		gpio_write(GPIOD, 15, !gpio_read(GPIOD, 15));

		delay_ms(1000);

		printf("HELLO!\r\n");
	}

	return 0;
}
