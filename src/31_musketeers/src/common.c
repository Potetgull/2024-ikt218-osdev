#include <common.h>
#include <libc/stddef.h> // Include necessary headers


void outb(uint16_t port, uint8_t value)
{
    asm volatile ("outb %1, %0" : : "dN" (port), "a" (value));
}

uint8_t inb(uint16_t port)
{
   uint8_t ret;
   asm volatile("inb %1, %0" : "=a" (ret) : "dN" (port));
   return ret;
}

uint16_t inw(uint16_t port)
{
   uint16_t ret;
   asm volatile ("inw %1, %0" : "=a" (ret) : "dN" (port));
   return ret;
}


// Implementation of strlen function
size_t strlen2(const char* str) {
    size_t len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}

// Implementation of memset function
void* memset2(void* ptr, int value, size_t num) {
    unsigned char* p = ptr;
    while (num-- > 0) {
        *p++ = (unsigned char)value;
    }
    return ptr;
}

// Implementation of memcpy function
void* memcpy2(void* dest, const void* src, size_t num) {
    unsigned char* d = dest;
    const unsigned char* s = src;
    while (num-- > 0) {
        *d++ = *s++;
    }
    return dest;
}