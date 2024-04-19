#pragma once

#ifndef COMMON_H
#define COMMON_H

typedef long unsigned int size_t;
typedef long unsigned int uint32_t;
typedef unsigned short uint16_t;
typedef unsigned char uint8_t;
typedef long int int32_t;
typedef short int16_t;
typedef signed char int8_t;

void outb(uint16_t port, uint8_t value);
uint8_t inb(uint16_t port);
uint16_t inw(uint16_t port);
#endif
