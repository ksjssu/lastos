#include "spinlock.h"
#include <stdatomic.h>
#include <sched.h>

void spinlock_init(spinlock_t *lock) {
    atomic_store(&lock->flag, 0);
}

void spinlock_acquire(spinlock_t *lock) {
    while (atomic_exchange(&lock->flag, 1)) {
        while (atomic_load(&lock->flag)) {
            sched_yield();
        }
    }
}

void spinlock_release(spinlock_t *lock) {
    atomic_store(&lock->flag, 0);
}

