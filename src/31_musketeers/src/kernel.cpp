extern "C"{
    #include "libc/stdint.h"
    #include "libc/stddef.h"
    #include "libc/stdbool.h"
    #include "libc/limits.h"
    #include "libc/stdio.h"
    #include "common.h"
    #include "descriptor_tables.h"
    #include "input.h"
    #include "monitor.h"
    #include "isr.h"
}



extern "C" int kernel_main(void);
int kernel_main(){
    asm volatile("sti");

while(1){}

    return 0;
}