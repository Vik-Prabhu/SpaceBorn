#ifndef MUTEX_H
#define MUTEX_H

#include <stdatomic.h>

typedef struct {
    atomic_flag flag;
} Mutex;

#define MUTEX_INIT { .flag = ATOMIC_FLAG_INIT }

void mutex_lock(Mutex *m);
void mutex_unlock(Mutex *m);
int  mutex_trylock(Mutex *m);   // returns 1 if locked, 0 if already taken

#endif