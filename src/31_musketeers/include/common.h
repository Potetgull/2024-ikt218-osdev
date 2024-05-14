#include <libc/stdint.h>
#ifndef COMMON_H
#define COMMON_H

void outb(uint16_t port, uint8_t value);
uint8_t inb(uint16_t port);
uint16_t inw(uint16_t port);

size_t strlen(const char* str); // Declaration of strlen function
void* memset(void* ptr, int value, size_t num); // Declaration of memset function
void* memcpy(void* dest, const void* src, size_t num); // Declaration of memcpy function

#endif
