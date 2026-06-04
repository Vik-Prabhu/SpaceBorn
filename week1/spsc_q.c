#include "spsc_q.h"

void queue_init(SPSCQueue* q) {
    q->read = 0;
    q->write = 0;
}

// producer owns write pointer
bool queue_push(SPSCQueue* q, uint32_t item) {

    uint32_t write = atomic_load_explicit(&q->write, memory_order_relaxed);
    uint32_t next_write = (write + 1) % QUEUE_SIZE;
    if (next_write != atomic_load_explicit(&q->read, memory_order_acquire)) { // Check if queue is not full
        q->buffer[write] = item;
        atomic_store_explicit(&q->write, next_write, memory_order_release); // Move the write index ahead
        return true;
    }
    printf("Queue is full. Cannot push item: %u\n", item);
    return false;
}

//consumer owns read pointer
bool queue_pop(SPSCQueue* q, uint32_t* out) {
    if (q->read == q->write) { // Check if queue is not empty
        printf("Queue is empty. Cannot pop item.\n");
        return false;
    }
    uint32_t read = atomic_load_explicit(&q->read, memory_order_relaxed); // Read value at read index
    *out = q->buffer[read]; // Output value at read index
    atomic_store_explicit(&q->read, (read + 1) % QUEUE_SIZE, memory_order_release); // Move the read index ahead
    return true;
}