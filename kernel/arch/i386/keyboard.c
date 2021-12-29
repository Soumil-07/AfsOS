#include <kernel/keyboard.h>
#include <kernel/irq.h>
#include <kernel/ps2.h>
#include <stdio.h>

void keyboard_install()
{
   irq_install_handler(1, ps2_irq);
}

void keyboard_write(char c)
{
   putchar(c);
}
