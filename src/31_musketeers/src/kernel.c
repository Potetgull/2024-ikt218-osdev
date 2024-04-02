#include "libc/stdint.h"
#include "libc/stddef.h"
#include "libc/stdbool.h"
#include <multiboot2.h>
#include <gdt.h>



struct multiboot_info {
    uint32_t size;
    uint32_t reserved;
    struct multiboot_tag *first;
};

void write_string( int colour, const char *string )     //Function to write strings. colour is a number between 0 and 15.
{
    volatile char *video = (volatile char*)0xB8000;     //writes to the terminal screen by VGA. This starts at this address. The next spots on the line are next in the address field.
    while( *string != 0 )
    {
        *video++ = *string++;
        *video++ = colour;
    }
}

int kernel_main();


int main(uint32_t magic, struct multiboot_info* mb_info_addr) {
    
    init_gdt();

    write_string(15, "  Hello World");      //call function. Write function leaves out first 2 letters. Add 2 spaces for now till its fixed.

    // Call cpp kernel_main (defined in kernel.cpp)
    return kernel_main();
}