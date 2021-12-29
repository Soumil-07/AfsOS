#ifndef _PS2_H_
#define _PS2_H_

#include <kernel/system.h>

void ps2_initialize();

void ps2_irq(struct regs* r);

#endif // _PS2_H_
