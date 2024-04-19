#ifndef MONITOR_H
#define MONITOR_H

#include "libc/stdint.h"

volatile uint16_t cursor_x = 0;
volatile uint16_t cursor_y = 0;
uint16_t *video_memory = (volatile char)0xB8000;

// Write a single character out to the screen.
void monitor_put(char c);

// Clear the screen to all black.
void monitor_clear();

// Output a null-terminated ASCII string to the monitor.
void monitor_write(char *c);

void monitor_write_hex(uint32_t n);

void monitor_write_dec(uint32_t n);

int32_t findstrlength(char *str);

static void move_cursor();

static void scroll();
#endif // MONITOR_H