#include "mutex.h"

void mutex_lock(Mutex *m) {
    while (atomic_flag_test_and_set_explicit(&m->flag, memory_order_acquire))
        ;
}

void mutex_unlock(Mutex *m) {
    atomic_flag_clear_explicit(&m->flag, memory_order_release);
}

int mutex_trylock(Mutex *m) {
    // returns 0 if we got it, 1 if already locked
    return atomic_flag_test_and_set_explicit(&m->flag, memory_order_acquire) ? 1 : 0;
}