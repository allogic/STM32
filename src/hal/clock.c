#include <hal/peripherals.h>
#include <hal/rcc.h>
#include <hal/flash.h>
#include <hal/pwr.h>
#include <hal/systick.h>
#include <hal/clock.h>

static uint32_t s_sys_clk_freq;
static uint32_t s_ahb_clk_freq;
static uint32_t s_apb1_clk_freq;
static uint32_t s_apb2_clk_freq;

void clock_reset(void) {
	RCC->CR |= RCC_CR_HSION;
	while ((RCC->CR & RCC_CR_HSIRDY) == 0);

	RCC->CFGR = 0x00000000;

	RCC->CR &= ~(RCC_CR_HSEON | RCC_CR_CSSON | RCC_CR_PLLON);

	RCC->PLLCFGR = 0x24003010;

	RCC->CR &= ~RCC_CR_HSEBYP;

	RCC->CIR = 0x00000000;
}

void clock_init_hsi_16mhz(void) {
	FLASH->ACR |= FLASH_ACR_DCEN | FLASH_ACR_ICEN | FLASH_ACR_PRFTEN | FLASH_LATENCY_0WS;

	s_sys_clk_freq = HSI_FREQ;
	s_ahb_clk_freq = s_sys_clk_freq / 1;
	s_apb1_clk_freq = s_sys_clk_freq / 1;
	s_apb2_clk_freq = s_sys_clk_freq / 1;

	SYSTICK->LOAD = (s_sys_clk_freq / 1000) - 1;
	SYSTICK->VAL = 0;
	SYSTICK->CTRL = SYSTICK_CTRL_ENABLE | SYSTICK_CTRL_TICKINT | SYSTICK_CTRL_CLKSOURCE;
}

void clock_init_hse_8mhz(void) {
	RCC->CR |= RCC_CR_HSEON;
	while ((RCC->CR & RCC_CR_HSERDY) == 0);

	RCC->CFGR &= ~RCC_CFGR_HPRE_MASK;
	RCC->CFGR |= RCC_CFGR_HPRE_DIV1;

	RCC->CFGR &= ~RCC_CFGR_PPRE1_MASK;
	RCC->CFGR |= RCC_CFGR_PPRE1_DIV1;

	RCC->CFGR &= ~RCC_CFGR_PPRE2_MASK;
	RCC->CFGR |= RCC_CFGR_PPRE2_DIV1;

	FLASH->ACR |= FLASH_ACR_DCEN | FLASH_ACR_ICEN | FLASH_ACR_PRFTEN | FLASH_LATENCY_0WS;

	RCC->CFGR &= ~RCC_CFGR_SW_MASK;
	RCC->CFGR |= RCC_CFGR_SW_HSE;
	while ((RCC->CFGR & RCC_CFGR_SWS_HSE) != RCC_CFGR_SWS_HSE);

	s_sys_clk_freq = HSE_FREQ;
	s_ahb_clk_freq = s_sys_clk_freq / 1;
	s_apb1_clk_freq = s_sys_clk_freq / 1;
	s_apb2_clk_freq = s_sys_clk_freq / 1;

	SYSTICK->LOAD = (s_sys_clk_freq / 1000) - 1;
	SYSTICK->VAL = 0;
	SYSTICK->CTRL = SYSTICK_CTRL_ENABLE | SYSTICK_CTRL_TICKINT | SYSTICK_CTRL_CLKSOURCE;
}

void clock_init_pll_168mhz(void) {
	uint32_t pllm = 8;
	uint32_t plln = 336;
	uint32_t pllp = 2;
	uint32_t pllq = 4;

	RCC->CR |= RCC_CR_HSEON;
	while ((RCC->CR & RCC_CR_HSERDY) == 0);

	RCC->APB1ENR |= RCC_APB1ENR_PWREN;

	PWR->CR |= PWR_CR_VOS;

	RCC->CFGR &= ~RCC_CFGR_HPRE_MASK;
	RCC->CFGR |= RCC_CFGR_HPRE_DIV1;

	RCC->CFGR &= ~RCC_CFGR_PPRE1_MASK;
	RCC->CFGR |= RCC_CFGR_PPRE1_DIV4;

	RCC->CFGR &= ~RCC_CFGR_PPRE2_MASK;
	RCC->CFGR |= RCC_CFGR_PPRE2_DIV2;

	RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLM_MASK;
	RCC->PLLCFGR |= (pllm << RCC_PLLCFGR_PLLM_POS);

	RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLN_MASK;
	RCC->PLLCFGR |= (plln << RCC_PLLCFGR_PLLN_POS);

	RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLP_MASK;
	RCC->PLLCFGR |= (pllp << RCC_PLLCFGR_PLLP_POS);

	RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLQ_MASK;
	RCC->PLLCFGR |= (pllq << RCC_PLLCFGR_PLLQ_POS);

	RCC->PLLCFGR |= RCC_PLLCFGR_PLLSRC;

	RCC->CR |= RCC_CR_PLLON;
	while ((RCC->CR & RCC_CR_PLLRDY) == 0);

	FLASH->ACR |= FLASH_ACR_DCEN | FLASH_ACR_ICEN | FLASH_ACR_PRFTEN | FLASH_LATENCY_5WS;

	RCC->CFGR &= ~RCC_CFGR_SW_MASK;
	RCC->CFGR |= RCC_CFGR_SW_PLL;
	while ((RCC->CFGR & RCC_CFGR_SWS_MASK) != RCC_CFGR_SWS_PLL);

	s_sys_clk_freq = (HSE_FREQ * (plln / pllm)) / pllp;
	s_ahb_clk_freq = s_sys_clk_freq / 1;
	s_apb1_clk_freq = s_sys_clk_freq / 4;
	s_apb2_clk_freq = s_sys_clk_freq / 2;

	SYSTICK->LOAD = (s_sys_clk_freq / 1000) - 1;
	SYSTICK->VAL = 0;
	SYSTICK->CTRL = SYSTICK_CTRL_ENABLE | SYSTICK_CTRL_TICKINT | SYSTICK_CTRL_CLKSOURCE;
}

void clock_enable_gpio(gpio_t* gpio) {
	switch ((uint32_t)gpio) {
		case (uint32_t)GPIOA: RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN; break;
		case (uint32_t)GPIOB: RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN; break;
		case (uint32_t)GPIOC: RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN; break;
		case (uint32_t)GPIOD: RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN; break;
		case (uint32_t)GPIOE: RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN; break;
		case (uint32_t)GPIOF: RCC->AHB1ENR |= RCC_AHB1ENR_GPIOFEN; break;
		case (uint32_t)GPIOG: RCC->AHB1ENR |= RCC_AHB1ENR_GPIOGEN; break;
		case (uint32_t)GPIOH: RCC->AHB1ENR |= RCC_AHB1ENR_GPIOHEN; break;
		case (uint32_t)GPIOI: RCC->AHB1ENR |= RCC_AHB1ENR_GPIOIEN; break;
		case (uint32_t)GPIOJ: RCC->AHB1ENR |= RCC_AHB1ENR_GPIOJEN; break;
		case (uint32_t)GPIOK: RCC->AHB1ENR |= RCC_AHB1ENR_GPIOKEN; break;
	}
}

void clock_enable_usart(usart_t* usart) {
	switch ((uint32_t)usart) {
		case (uint32_t)USART1: RCC->APB2ENR |= RCC_APB2ENR_USART1; break;
		case (uint32_t)USART2: RCC->APB1ENR |= RCC_APB1ENR_USART2; break;
		case (uint32_t)USART3: RCC->APB1ENR |= RCC_APB1ENR_USART3; break;
		case (uint32_t)UART4:  RCC->APB1ENR |= RCC_APB1ENR_USART4; break;
		case (uint32_t)UART5:  RCC->APB1ENR |= RCC_APB1ENR_USART5; break;
		case (uint32_t)USART6: RCC->APB2ENR |= RCC_APB2ENR_USART6; break;
		case (uint32_t)UART7:  RCC->APB1ENR |= RCC_APB1ENR_USART7; break;
		case (uint32_t)UART8:  RCC->APB1ENR |= RCC_APB1ENR_USART8; break;
	}
}

uint32_t clock_get_usart_clk_freq(usart_t* usart) {
	if ((usart == USART1) || (usart == USART6)) {
		return s_apb2_clk_freq;
	} else {
		return s_apb1_clk_freq;
	}
}
