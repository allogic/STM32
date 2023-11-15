#ifndef STM32F4_HAL_REGISTERS_H
#define STM32F4_HAL_REGISTERS_H

#include <stdint.h>

#include <core/attributes.h>

typedef volatile struct PACKED {
	uint32_t ISER[8];
	uint32_t RESERVED0[24];
	uint32_t ICER[8];
	uint32_t RESERVED1[24];
	uint32_t ISPR[8];
	uint32_t RESERVED2[24];
	uint32_t ICPR[8];
	uint32_t RESERVED3[24];
	uint32_t IABR[8];
	uint32_t RESERVED4[56];
	uint8_t IP[60];
	uint32_t RESERVED5[644];
	uint32_t STIR;
} nvic_t;

typedef volatile struct PACKED {
	uint32_t ACR;
	uint32_t KEYR;
	uint32_t OPTKEYR;
	uint32_t SR;
	uint32_t CR;
	uint32_t OPTCR;
} flash_t;

typedef volatile struct PACKED {
	uint32_t CR;
	uint32_t CSR;
} pwr_t;

typedef volatile struct PACKED {
	uint32_t CR;
	uint32_t PLLCFGR;
	uint32_t CFGR;
	uint32_t CIR;
	uint32_t AHB1RSTR;
	uint32_t AHB2RSTR;
	uint32_t AHB3RSTR;
	uint32_t RESERVED0;
	uint32_t APB1RSTR;
	uint32_t APB2RSTR;
	uint32_t RESERVED1;
	uint32_t RESERVED2;
	uint32_t AHB1ENR;
	uint32_t AHB2ENR;
	uint32_t AHB3ENR;
	uint32_t RESERVED3;
	uint32_t APB1ENR;
	uint32_t APB2ENR;
	uint32_t RESERVED4;
	uint32_t RESERVED5;
	uint32_t AHB1LPENR;
	uint32_t AHB2LPENR;
	uint32_t AHB3LPENR;
	uint32_t RESERVED6;
	uint32_t APB1LPENR;
	uint32_t APB2LPENR;
	uint32_t RESERVED7;
	uint32_t RESERVED8;
	uint32_t BDCR;
	uint32_t CSR;
	uint32_t RESERVED9;
	uint32_t RESERVED10;
	uint32_t SSCGR;
	uint32_t PLLI2SCFGR;
} rcc_t;

typedef volatile struct PACKED {
	uint32_t MODER;
	uint32_t OTYPER;
	uint32_t OSPEEDR;
	uint32_t PUPDR;
	uint32_t IDR;
	uint32_t ODR;
	uint32_t BSRR;
	uint32_t LCKR;
	uint32_t AFRL;
	uint32_t AFRH;
} gpio_t;

typedef volatile struct PACKED {
	uint32_t CTRL;
	uint32_t LOAD;
	uint32_t VAL;
	uint32_t CALIB;
} systick_t;

typedef volatile struct PACKED {
	uint32_t CPUID;
	uint32_t ICSR;
	uint32_t VTOR;
	uint32_t AIRCR;
	uint32_t SCR;
	uint32_t CCR;
	uint8_t  SHP[12];
	uint32_t SHCSR;
	uint32_t CFSR;
	uint32_t HFSR;
	uint32_t DFSR;
	uint32_t MMFAR;
	uint32_t BFAR;
	uint32_t AFSR;
	uint32_t PFR[2];
	uint32_t DFR;
	uint32_t ADR;
	uint32_t MMFR[4];
	uint32_t ISAR[5];
	uint32_t RESERVED0[5];
	uint32_t CPACR;
} scb_t;

typedef volatile struct PACKED {
	uint32_t SR;
	uint32_t DR;
	uint32_t BRR;
	uint32_t CR1;
	uint32_t CR2;
	uint32_t CR3;
	uint32_t GTPR;
} usart_t;

#endif
