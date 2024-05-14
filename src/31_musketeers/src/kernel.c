#include "libc/stdint.h"
#include "libc/stddef.h"
#include "libc/stdbool.h"
#include <multiboot2.h>
#include <descriptor_tables.h>
#include <monitor.h>
#include <kernel/pit.h>
#include "isr.h"
#include "input.h"
#include "kernel/memory.h"
#include "kernel/pit.h"


struct multiboot_info {
    uint32_t size;
    uint32_t reserved;
    struct multiboot_tag *first;
};

extern uint32_t end; // This is defined in arch/i386/linker.ld

int kernel_main();

void keyboard_handler(registers_t regs){
            // Read from keyboard
        unsigned char scan_code = inb(0x60);
        char f[2] = {'\0', '\0'};               //define array with \0 as end. Our write uses \0 to determine end of array.
        f[0] = scancode_to_ascii(&scan_code);   //Puts the returned char in the array's first slot, meaning a \0 is followed immediately after.
        //This is done to avoid unknown data surrounding the address to be passed to the write function. Our write function receives an address, not a value.
        
        monitor_write(f);                       //receives the address of the array and writes out the character.

        // Disable
        asm volatile("cli");
}


int main(uint32_t magic, struct multiboot_info* mb_info_addr) {

    
    monitor_clear();                //clears the terminal monitor

    init_descriptor_tables();       //runs init gdt, init idt and init irq

    // Initialize the kernel's memory manager using the end address of the kernel.
    init_kernel_memory(&end); // <------ THIS IS PART OF THE ASSIGNMENT

    // Initialize paging for memory management.
    init_paging(); // <------ THIS IS PART OF THE ASSIGNMENT

    // Print memory information.
    print_memory_layout(); // <------ THIS IS PART OF THE ASSIGNMENT

		// Initialize PIT
    init_pit(); // <------ THIS IS PART OF THE ASSIGNMENT

    monitor_write("Hello, world!"); //prints string "Hello, world"
    asm volatile("sti");            //Enables interrupts

    init_pit(1000);               // Initialise timer to 1000Hz


    asm volatile ("int $0x0");      //Throws interrupt 0-2
    asm volatile ("int $0x1");
    asm volatile ("int $0x2");

    register_irq_handler(IRQ1, keyboard_handler, NULL); //Registers an IRQ handler for IRQ1 with the keyboard_handler function. IRQ1 will now jump to the keyboard_handler function.


    // Call cpp kernel_main (defined in kernel.cpp)
    return kernel_main();
}

