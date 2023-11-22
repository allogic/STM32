#ifndef STM32F4_CONTAINER_QUEUE_H
#define STM32F4_CONTAINER_QUEUE_H

#include <stdbool.h>
#include <stdint.h>
#include <string.h>

typedef struct {
    uint32_t value_size;
    uint32_t value_count;
    uint32_t buffer_size;
    uint32_t read_index;
    uint32_t read_offset;
    uint32_t write_index;
    uint32_t write_offset;
    uint32_t count;
    void* buffer;
} queue_t;

void queue_init(queue_t* queue, uint32_t value_size, uint32_t value_count, uint32_t buffer_size, void* buffer);

void queue_push(queue_t* queue, void* data);
void queue_pop(queue_t* queue, void* data);

bool queue_empty(queue_t* queue);
uint32_t queue_count(queue_t* queue);

#endif
