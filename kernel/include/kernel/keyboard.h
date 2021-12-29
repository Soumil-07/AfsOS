#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

/* Installs keyboard interrupts/handling code */
void keyboard_install();

/* This routine is called when the user presses a key on the keyboard. Could be called by the PS/2 driver or a future USB driver */
void keyboard_write(char c);

#endif // _KEYBOARD_H_
