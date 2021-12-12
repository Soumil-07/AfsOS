#ifndef _IDT_H_
#define _IDT_H_

void idt_set_gate(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags);

void idt_install();

#endif // _IDT_H_ 
