#include <stdio.h>

#include <kernel/tty.h>
#include <kernel/gdt.h>
#include <kernel/idt.h>
#include <kernel/isrs.h>
#include <kernel/irq.h>
#include <kernel/timer.h>
#include <kernel/keyboard.h>

void kernel_main(void) {
	/* initialize kernel tty */
	terminal_initialize();
	printf("Hello, kernel World!\n");

	/* setup Global Descriptor Table */
	gdt_install();

	/* setup Interrupt Descriptor Table */
	idt_install();

	/* setup ISRs, IRQs and the PIT */
	isrs_install();
	/* install the interrupt for the PS/2 keyboard */
	keyboard_install();
	irq_install();
	timer_install();
	/* now that we have interrupt handlers, allow interrupts */
	__asm__ __volatile__ ("sti");
	// test the CPU exception handler by dividing by 0
	/* int test = 0;
	asm volatile ("div %b0" : "+a"(test)); */

	for(;;);


}
