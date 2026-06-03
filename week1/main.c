#include "main.h"
#include "tasks.h"


extern task_t tasks[MAX_TASKS];

int main() {
    create_task(0, "Task A", 1);
    create_task(1, "Task B", 2);
    create_task(2, "Task C", 3);

    for (int i = 0; i < 3; i++) {
            printf("Task ID: %d, Name: %s, Priority: %d\n", tasks[i].id, tasks[i].name, tasks[i].priority);
    }

    return 0;
}