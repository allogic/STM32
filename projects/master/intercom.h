#ifndef STM32F4_INTERCOM_H
#define STM32F4_INTERCOM_H

void intercom_init(void);

void intercom_read(uint8_t slave, uint8_t index, void* data);

#endif
