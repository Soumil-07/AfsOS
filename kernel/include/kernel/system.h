#ifndef _SYSTEM_H_
#define _SYSTEM_H_

unsigned char inportb (unsigned short _port);

void outportb (unsigned short _port, unsigned char _data);

/* Represents the stackframe after an IRQ */
struct regs
{
    unsigned int gs, fs, es, ds;      /* pushed the segs last */
    unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;  /* pushed by 'pusha' */
    unsigned int int_no, err_code;    /* our 'push byte #' and ecodes do this */
    unsigned int eip, cs, eflags, useresp, ss;   /* pushed by the processor automatically */ 
};

#endif // _SYSTEM_H_
