#include <stdio.h>

#include <kernel/tty.h>
#include <kernel/gdt.h>
#include <kernel/idt.h>
#include <kernel/isrs.h>

void kernel_main(void) {
	/* initialize kernel tty */
	terminal_initialize();
	printf("Hello, kernel World!\n");

	/* setup Global Descriptor Table */
	gdt_install();

	/* setup Interrupt Descriptor Table */
	idt_install();

	isrs_install();

	/* test ISRs */
	putchar(5 / 0);
}
