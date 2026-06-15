#include "main.h"
#include "tasks.h"
#include "spsc_q.h"
#include "mutex.h"
#include "priority_sch.h"

SPSCQueue task_queue;
extern task_t tasks[MAX_TASKS];

static int tests_run = 0;
static int tests_failed = 0;

static bool check_step(const char *step, bool condition) {
    if (!condition) {
        printf("  step failed: %s\n", step);
    }
    return condition;
}

static void report_test(const char *name, bool passed) {
    tests_run++;
    printf("[%s] %s\n", passed ? "PASS" : "FAIL", name);
    if (!passed) {
        tests_failed++;
    }
}

static bool test_task_creation(void) {
    create_task(0, "Task A", 1);
    create_task(1, "Task B", 2);
    create_task(2, "Task C", 3);

    if (!check_step("task 0 fields", tasks[0].id == 0 && strcmp(tasks[0].name, "Task A") == 0 && tasks[0].priority == 1)) {
        return false;
    }
    if (!check_step("task 1 fields", tasks[1].id == 1 && strcmp(tasks[1].name, "Task B") == 0 && tasks[1].priority == 2)) {
        return false;
    }
    if (!check_step("task 2 fields", tasks[2].id == 2 && strcmp(tasks[2].name, "Task C") == 0 && tasks[2].priority == 3)) {
        return false;
    }

    printf("Task module output:\n");
    for (int i = 0; i < 3; i++) {
        printf("  Task ID: %u, Name: %s, Priority: %u\n", tasks[i].id, tasks[i].name, tasks[i].priority);
    }

    return true;
}

static bool test_spsc_queue(void) {
    queue_init(&task_queue);

    uint32_t value = 0;

    if (!check_step("pop from empty queue should fail", !queue_pop(&task_queue, &value))) {
        return false;
    }
    if (!check_step("push 10", queue_push(&task_queue, 10))) {
        return false;
    }
    if (!check_step("push 20", queue_push(&task_queue, 20))) {
        return false;
    }
    if (!check_step("push 30", queue_push(&task_queue, 30))) {
        return false;
    }

    if (!check_step("pop should return 10", queue_pop(&task_queue, &value) && value == 10)) {
        return false;
    }
    if (!check_step("pop should return 20", queue_pop(&task_queue, &value) && value == 20)) {
        return false;
    }
    if (!check_step("pop should return 30", queue_pop(&task_queue, &value) && value == 30)) {
        return false;
    }
    if (!check_step("queue should be empty again", !queue_pop(&task_queue, &value))) {
        return false;
    }

    printf("Queue module output:\n");
    printf("  Pushed values: 10, 20, 30\n");
    printf("  Popped values: 10, 20, 30\n");

    return true;
}

static bool test_mutex(void) {
    Mutex lock = MUTEX_INIT;

    if (!check_step("trylock on free mutex should succeed", mutex_trylock(&lock) == 0)) {
        return false;
    }
    if (!check_step("second trylock should fail", mutex_trylock(&lock) == 1)) {
        return false;
    }
    mutex_unlock(&lock);
    mutex_lock(&lock);
    if (!check_step("trylock while locked by lock() should fail", mutex_trylock(&lock) == 1)) {
        return false;
    }
    mutex_unlock(&lock);

    printf("Mutex module output:\n");
    printf("  trylock when free: success\n");
    printf("  trylock when locked: blocked as expected\n");
    printf("  lock/unlock sequence: completed\n");

    return true;
}

static bool test_priority_scheduler(void) {
    PriorityScheduler scheduler;
    task_t* next = NULL;

    scheduler_init(&scheduler);

    if (!check_step("add task 0", scheduler_add_task(&scheduler, &tasks[0]))) {
        return false;
    }
    if (!check_step("add task 1", scheduler_add_task(&scheduler, &tasks[1]))) {
        return false;
    }
    if (!check_step("add task 2", scheduler_add_task(&scheduler, &tasks[2]))) {
        return false;
    }

    next = scheduler_pick_next(&scheduler);
    if (!check_step("highest priority should be task 2", next != NULL && next->id == 2)) {
        return false;
    }
    if (!check_step("mark task 2 done", scheduler_mark_done(&scheduler, 2))) {
        return false;
    }

    next = scheduler_pick_next(&scheduler);
    if (!check_step("next should be task 1", next != NULL && next->id == 1)) {
        return false;
    }
    if (!check_step("mark task 1 done", scheduler_mark_done(&scheduler, 1))) {
        return false;
    }

    next = scheduler_pick_next(&scheduler);
    if (!check_step("next should be task 0", next != NULL && next->id == 0)) {
        return false;
    }
    if (!check_step("mark task 0 done", scheduler_mark_done(&scheduler, 0))) {
        return false;
    }

    if (!check_step("no pending tasks left", !scheduler_has_pending(&scheduler))) {
        return false;
    }

    printf("Priority scheduler output:\n");
    printf("  Run order by priority: Task 2 -> Task 1 -> Task 0\n");

    return true;
}

int main() {

    report_test("task creation", test_task_creation());
    report_test("spsc queue", test_spsc_queue());
    report_test("mutex", test_mutex());
    report_test("priority scheduler", test_priority_scheduler());

    printf("\nSummary: %d run, %d failed\n", tests_run, tests_failed);

    return tests_failed == 0 ? 0 : 1;
}