#include <core/attributes.h>

#include <hal/registers.h>
#include <hal/peripherals.h>
#include <hal/vectors.h>
#include <hal/clock.h>
#include <hal/fpu.h>

extern uint32_t g_flash;
extern uint32_t g_ram;
extern uint32_t g_stack;

uint32_t g_sys_ticks;

static void hardfault_handler(void);
static void systick_handler(void);

void reset_handler(void);
int main(void);

void* const g_rovector[16] SECTION(".rovector") = {
	&g_stack,          // 0x00
	reset_handler,     // 0x04
	0,                 // 0x08
	hardfault_handler, // 0x0C
	0,                 // 0x10
	0,                 // 0x14
	0,                 // 0x18
	0,                 // 0x1C
	0,                 // 0x20
	0,                 // 0x24
	0,                 // 0x28
	0,                 // 0x2C
	0,                 // 0x30
	0,                 // 0x34
	0,                 // 0x38
	systick_handler,   // 0x3C
};

void* g_vector[97] SECTION(".vector");

OPTIMIZE("-O0") void reset_handler(void) {
	for (uint32_t i = 0; i < 97; ++i) {
		g_vector[i] = (i < 16) ? g_rovector[i] : 0;
	}

	SCB->VTOR = (uint32_t)&g_ram;
	SCB->CPACR |= (FPU_FULL_ACCESS << FPU_CPACR_CP10_POS) | (FPU_FULL_ACCESS << FPU_CPACR_CP11_POS);

	clock_reset();
	clock_init_pll_168mhz();

	main();

	while (1);
}

void vectors_register_isr(uint32_t position, void (*isr)(void)) {
	g_vector[16 + position] = isr;
}

void vectors_enable_irq(uint8_t channel) {
	NVIC->ISER[channel >> 5] = 1 << (channel & 0x1F);
}

void vectors_disable_irq(uint8_t channel) {
	NVIC->ICER[channel >> 5] = 1 << (channel & 0x1F);
}

static void hardfault_handler(void) {

}

static void systick_handler(void) {
	g_sys_ticks++;
}
