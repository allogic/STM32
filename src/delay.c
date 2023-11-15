#include <hal/vectors.h>

#include <delay.h>

void delay_ms(uint32_t ms) {
	uint32_t start = g_sys_ticks;
    while ((g_sys_ticks - start) < ms);
}
