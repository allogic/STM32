#include <container/queue.h>

void queue_init(queue_t* queue, uint32_t value_size, uint32_t value_count, uint32_t buffer_size, void* buffer) {
    queue->value_size = value_size;
    queue->value_count = value_count;
    queue->buffer_size = buffer_size;
    queue->read_index = 0;
    queue->read_offset = 0;
    queue->write_index = 0;
    queue->write_offset = 0;
    queue->count = 0;
    queue->buffer = buffer;
}

void queue_push(queue_t* queue, void* data) {
    memcpy(((uint8_t*)queue->buffer) + queue->write_offset, data, queue->value_size);

    queue->write_index += 1;
    queue->write_offset += queue->value_size;
    queue->count += 1;

    if (queue->write_offset >= queue->buffer_size) {
        queue->write_index = 0;
        queue->write_offset = 0;
    }
}

void queue_pop(queue_t* queue, void* data) {
    memcpy(data, ((uint8_t*)queue->buffer) + queue->read_offset, queue->value_size);

    queue->read_index += 1;
    queue->read_offset += queue->value_size;
    queue->count -= 1;

    if (queue->read_offset >= queue->buffer_size) {
        queue->read_index = 0;
        queue->read_offset = 0;
    }
}

bool queue_empty(queue_t* queue) {
    return queue->count == 0;
}

uint32_t queue_count(queue_t* queue) {
    return queue->count;
}
