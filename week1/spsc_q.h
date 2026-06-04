#include "main.h"

#ifndef QUEUE_SIZE
    #define QUEUE_SIZE 1024
#endif

typedef struct {
    uint32_t buffer[QUEUE_SIZE];
    _Atomic uint32_t read;
    _Atomic uint32_t write;
} SPSCQueue;

void queue_init(SPSCQueue* q);
bool queue_push(SPSCQueue* q, uint32_t item);
bool queue_pop(SPSCQueue* q , uint32_t* out);