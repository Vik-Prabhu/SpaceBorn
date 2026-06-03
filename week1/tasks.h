
#ifndef TASKS_H
#define TASKS_H

typedef struct {
    uint8_t id;
    char name[20];
    uint8_t priority;
} task_t;

void create_task(uint8_t id, const char* name, uint8_t priority);


#endif // TASKS_H    