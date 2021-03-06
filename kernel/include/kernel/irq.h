#ifndef _IRQ_H_
#define _IRQ_H_

#include <kernel/system.h>

void irq_install();
void irq_install_handler(int irq, void (*handler)(struct regs *r));
void irq_uninstall_handler(int irq);

#endif
