#include "libc/stdint.h"
#include "libc/stddef.h"

#include "isr.h"
#include "monitor.h"
#include "common.h"

isr_t interrupt_handlers[256];

void register_interrupt_handler(uint8_t n, isr_t handler, void* context)
{
    int_handlers[n].handler = handler;
    int_handlers[n].data = context;
}

// This gets called from our ASM interrupt handler stub.
void isr_handler(registers_t regs)
{
   monitor_write("\nrecieved interrupt: ");
   monitor_write_dec(regs.int_no);
   monitor_put('\n');
}

// Initialize IRQ handlers
void init_irq() {
  for (int i = 0; i < 16; i++) {
    irq_handlers[i].data = NULL;
    irq_handlers[i].handler = NULL;
    irq_handlers[i].num = i;
  }
}

// Register an IRQ handler
void register_irq_handler(int irq, isr_t handler, void* ctx) {
  irq_handlers[irq].handler = handler;
  irq_handlers[irq].data = ctx;
}

void irq_handler(registers_t regs)
{
   // Send an EOI (end of interrupt) signal to the PICs.
   // If this interrupt involved the slave.
   if (regs.int_no >= 40)
   {
       // Send reset signal to slave.
       outb(0xA0, 0x20);
   }
   // Send reset signal to master. (As well as slave, if necessary).
   outb(0x20, 0x20);

   if (regs.int_no >= 32)
   {
    isr_t handler = irq_handlers[regs.int_no].handler;
    handler(&regs, NULL);
   }

   if (interrupt_handlers[regs.int_no] != 0)
   {
       isr_t handler = interrupt_handlers[regs.int_no];
       handler(&regs, NULL);
   }
}