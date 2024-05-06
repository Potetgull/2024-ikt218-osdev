#ifndef TIMER_H
#define TIMER_H

#include "common.h"
#include "libc/stdint.h"

void init_timer(uint32_t frequency);
#define TICKS_PER_MS (1000/1000)
#endif