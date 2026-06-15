#include "priority_sch.h"

// Reset all scheduler slots so the scheduler starts empty.
void scheduler_init(PriorityScheduler* sch) {
	for (int i = 0; i < MAX_TASKS; i++) {
		sch->entries[i].used = false;
		sch->entries[i].done = false;
	}
}

// Add one task to the first free slot.
bool scheduler_add_task(PriorityScheduler* sch, const task_t* task) {
	for (int i = 0; i < MAX_TASKS; i++) {
		if (!sch->entries[i].used) {
			sch->entries[i].task = *task;
			sch->entries[i].used = true;
			sch->entries[i].done = false;
			return true;
		}
	}

	// No free slot was found.
	return false;
}

// Pick the highest-priority task that is still pending.
task_t* scheduler_pick_next(PriorityScheduler* sch) {
	int best_index = -1;

	for (int i = 0; i < MAX_TASKS; i++) {
		if (!sch->entries[i].used || sch->entries[i].done) {
			continue;
		}

		if (best_index == -1 ||
			sch->entries[i].task.priority > sch->entries[best_index].task.priority) {
			best_index = i;
		}
	}

	if (best_index == -1) {
		return NULL;
	}

	return &sch->entries[best_index].task;
}

// Mark one task as completed by task ID.
bool scheduler_mark_done(PriorityScheduler* sch, uint8_t task_id) {
	for (int i = 0; i < MAX_TASKS; i++) {
		if (sch->entries[i].used && sch->entries[i].task.id == task_id) {
			sch->entries[i].done = true;
			return true;
		}
	}

	// Task ID not found.
	return false;
}

bool scheduler_has_pending(const PriorityScheduler* sch) {
	for (int i = 0; i < MAX_TASKS; i++) {
		if (sch->entries[i].used && !sch->entries[i].done) {
			return true;
		}
	}

	return false;
}
