/* Interfaces the CPU's built-in PS2 controller, to handle keyboard input */
#include <kernel/system.h>
#include <stdint.h>

/* I/O ports */
#define DATA_PORT 0x60
#define SR_PORT 0x64 // status register
#define CR_PORT 0x64 // command register

char scancode_set[128] = {
    0, 27 /* escape */, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
    '-', '=', '\t', '\b' /* backspace */, 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']',
    '\n' /* enter */, 0 /* left-control */, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k',
    'l', ';', '\'', '`', 0 /* left-shift */, '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm',
    ',', ',', '/', 0 /* right shift */, '*',
    0 /* left alt */,
    ';',
    0 /* Caps lock */,
    /* F1 - F12 */
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0 /* Num Lock */,
    0,	/* Scroll Lock */
    0,	/* Home key */
    0,	/* Up Arrow */
    0,	/* Page Up */
    '-',
    0,	/* Left Arrow */
    0,
    0,	/* Right Arrow */
    '+',
    0,	/* 79 - End key*/
    0,	/* Down Arrow */
    0,	/* Page Down */
    0,	/* Insert Key */
    0,	/* Delete Key */
    0,   0,   0,
    0,	/* F11 Key */
    0,	/* F12 Key */
    0,	/* All other keys are undefined */
};

void ps2_initialize()
{
    // TODO
}

void ps2_irq(struct regs* r)
{
    uint8_t scancode = inportb(DATA_PORT);

    if (scancode & 0x80)
    {
        /* key has been released */
    }
    else
        keyboard_write(scancode_set[scancode]);

}
