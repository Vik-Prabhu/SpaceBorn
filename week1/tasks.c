#include "main.h"
#include "tasks.h"


task_t tasks[MAX_TASKS];

void create_task(uint8_t id, const char* name, uint8_t priority) {
    if (id < MAX_TASKS) {
        tasks[id].id = id;
        strncpy(tasks[id].name, name, sizeof(tasks[id].name) - 1);
        tasks[id].name[sizeof(tasks[id].name) - 1] = '\0'; // Ensure null-termination
        tasks[id].priority = priority;
    }
}

