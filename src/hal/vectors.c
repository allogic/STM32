#include <core/attributes.h>

#include <hal/registers.h>
#include <hal/peripherals.h>
#include <hal/vectors.h>
#include <hal/clock.h>
#include <hal/fpu.h>

extern uint32_t __flash__;
extern uint32_t __ram__;
extern uint32_t __stack__;

extern uint32_t __vector_init__;
extern uint32_t __vector_start__;
extern uint32_t __vector_end__;

extern uint32_t __text_start__;
extern uint32_t __text_end__;

extern uint32_t __data_init__;
extern uint32_t __data_start__;
extern uint32_t __data_end__;

extern uint32_t __bss_start__;
extern uint32_t __bss_end__;

uint32_t g_sys_ticks;

static void nmi_handler(void);
static void hardfault_handler(void);
static void memmanage_handler(void);
static void busfault_handler(void);
static void usagefault_handler(void);
static void systick_handler(void);

void reset_handler(void);
int main(void);

void* g_vector[97] SECTION(".vector") = {
	&__stack__,         // 0x00
	reset_handler,      // 0x04
	nmi_handler,        // 0x08
	hardfault_handler,  // 0x0C
	memmanage_handler,  // 0x10
	busfault_handler,   // 0x14
	usagefault_handler, // 0x18
	0,                  // 0x1C
	0,                  // 0x20
	0,                  // 0x24
	0,                  // 0x28
	0,                  // 0x2C
	0,                  // 0x30
	0,                  // 0x34
	0,                  // 0x38
	systick_handler,    // 0x3C
};

OPTIMIZE("-O0") void reset_handler(void) {
	uint32_t* src;
	uint32_t* dst;

	src = &__vector_init__;
	dst = &__vector_start__;
	while (dst < &__vector_end__) {
		*dst++ = *src++;
	}

	src = &__data_init__;
	dst = &__data_start__;
	while (dst < &__data_end__) {
		*dst++ = *src++;
	}

	dst = &__bss_start__;
	while (dst < &__bss_end__) {
		*dst++ = 0;
	}

	SCB->VTOR = (uint32_t)&__vector_start__;
	SCB->CPACR |= (FPU_FULL_ACCESS << FPU_CPACR_CP10_POS) | (FPU_FULL_ACCESS << FPU_CPACR_CP11_POS);

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

static void nmi_handler(void) {

}

static void hardfault_handler(void) {

}

static void memmanage_handler(void) {

}

static void busfault_handler(void) {

}

static void usagefault_handler(void) {

}

static void systick_handler(void) {
	g_sys_ticks++;
}
