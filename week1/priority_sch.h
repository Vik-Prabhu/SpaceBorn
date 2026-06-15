#ifndef PRIORITY_SCH_H
#define PRIORITY_SCH_H

#include "main.h"
#include "tasks.h"

typedef struct {
	task_t task;
	bool used;
	bool done;
} SchedulerEntry;

typedef struct {
	SchedulerEntry entries[MAX_TASKS];
} PriorityScheduler;

void scheduler_init(PriorityScheduler* sch);
bool scheduler_add_task(PriorityScheduler* sch, const task_t* task);
task_t* scheduler_pick_next(PriorityScheduler* sch);
bool scheduler_mark_done(PriorityScheduler* sch, uint8_t task_id);
bool scheduler_has_pending(const PriorityScheduler* sch);

#endif // PRIORITY_SCH_H
