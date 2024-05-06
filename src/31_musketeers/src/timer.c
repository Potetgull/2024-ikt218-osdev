#include "timer.h"
#include "isr.h"
#include "monitor.h"
#include "libc/stddef.h"

uint32_t tick = 0;

static void timer_callback(registers_t regs)
{
   tick++;
   monitor_write("Tick: ");
   monitor_write_dec(tick);
   monitor_write("\n");
}

void init_timer(uint32_t frequency)
{
   // Firstly, register our timer callback.
   register_irq_handler(IRQ0, timer_callback, NULL);

   // The value we send to the PIT is the value to divide it's input clock
   // (1193180 Hz) by, to get our required frequency. Important to note is
   // that the divisor must be small enough to fit into 16-bits.
   uint32_t divisor = (uint8_t)1193180 / frequency;

   // Send the command byte.
   outb(0x43, 0x36);

   // Divisor has to be sent byte-wise, so split here into upper/lower bytes.
   uint8_t l = (uint8_t)(divisor & 0xFF);
   uint8_t h = (uint8_t)( (divisor>>8) & 0xFF );

   // Send the frequency divisor.
   outb(0x40, l);
   outb(0x40, h);
}


void sleep_busy(uint32_t milliseconds){
    uint32_t start_tick = tick;
    uint32_t ticks_to_wait = milliseconds * TICKS_PER_MS;
    uint32_t elapsed_ticks = 0;
    
    while (elapsed_ticks < ticks_to_wait) {
        while (tick == start_tick + elapsed_ticks) {};
        elapsed_ticks++;
    }    
}