#include "libc/stdint.h"
#include "libc/stddef.h"
#include "libc/stdbool.h"
#include <multiboot2.h>
#include <descriptor_tables.h>
#include <monitor.h>
#include <timer.h>
#include "isr.h"
#include "input.h"


struct multiboot_info {
    uint32_t size;
    uint32_t reserved;
    struct multiboot_tag *first;
};


int kernel_main();

void keyboard_handler(registers_t regs){
            // Read from keyboard
        unsigned char scan_code = inb(0x60);
        char f[2] = {'\0', '\0'};
        f[0] = scancode_to_ascii(&scan_code);
        
        monitor_write(f);

        // Disable
        asm volatile("cli");
}

int main(uint32_t magic, struct multiboot_info* mb_info_addr) {
    
    init_descriptor_tables();

    monitor_clear();
    monitor_write("Hello, world!");
    asm volatile("sti");

    init_timer(1000); // Initialise timer to 1000Hz

    //sleep_busy(1000);

    asm volatile ("int $0x0");
    asm volatile ("int $0x1");
    asm volatile ("int $0x2");
    asm volatile ("int $0x3");
    asm volatile ("int $0x4");
    asm volatile ("int $0x5");
    register_irq_handler(IRQ1, keyboard_handler, NULL);


    // Call cpp kernel_main (defined in kernel.cpp)
    return kernel_main();
}

