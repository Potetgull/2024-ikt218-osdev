#include "libc/stdint.h"
#include "libc/stddef.h"
#include "libc/stdbool.h"
#include <multiboot2.h>
#include <descriptor_tables.h>
#include <monitor.h>



struct multiboot_info {
    uint32_t size;
    uint32_t reserved;
    struct multiboot_tag *first;
};



int kernel_main();


int main(uint32_t magic, struct multiboot_info* mb_info_addr) {
    
    init_descriptor_tables();

    monitor_clear();
    monitor_write("Hello, world!");

    asm volatile ("int $0x0");
    asm volatile ("int $0x1");
    asm volatile ("int $0x2");
    asm volatile ("int $0x3");
    asm volatile ("int $0x4");
    asm volatile ("int $0x5");
    // Call cpp kernel_main (defined in kernel.cpp)
    return kernel_main();
}