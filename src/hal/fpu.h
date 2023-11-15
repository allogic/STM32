#ifndef STM32F4_HAL_FPU_H
#define STM32F4_HAL_FPU_H

#define FPU_CPACR_CP100 (1 << 20)
#define FPU_CPACR_CP101 (1 << 21)

#define FPU_CPACR_CP110 (1 << 22)
#define FPU_CPACR_CP111 (1 << 23)

#define FPU_CPACR_CP10_MASK (FPU_CPACR_CP100 | FPU_CPACR_CP101)
#define FPU_CPACR_CP10_POS  (20)

#define FPU_CPACR_CP11_MASK (FPU_CPACR_CP110 | FPU_CPACR_CP111)
#define FPU_CPACR_CP11_POS  (22)

#define FPU_ACCESS_DENIED     (0b00)
#define FPU_PRIVILEGED_ACCESS (0b01)
#define FPU_FULL_ACCESS       (0b11)

#endif