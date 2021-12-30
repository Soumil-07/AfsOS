#include <stdio.h>

#include <kernel/tty.h>
#include <kernel/gdt.h>
#include <kernel/idt.h>
#include <kernel/isrs.h>
#include <kernel/irq.h>
#include <kernel/timer.h>
#include <kernel/keyboard.h>
#include <kernel/mmu.h>

#include <extern/multiboot.h>

char* mmap_types[] = {
	"Available",
	"Reserved",
	"ACPI Reclaimable",
	"NVS",
	"Bad RAM"
};

void kernel_main(multiboot_info_t* mbd, unsigned int magic) {
	/* initialize kernel tty */
	terminal_initialize();

	printf("Detecting memory map...\n");
	/* check bit 6 for a valid memory map */
	if (!(mbd->flags >> 6 & 0x1))
	{
		printf("Invalid memory map provided by the bootloader!\n");
		return;
	}

	for (int i = 0; i < mbd->mmap_length; i += sizeof(multiboot_memory_map_t))
	{
		multiboot_memory_map_t* mmmt = (multiboot_memory_map_t*) (mbd->mmap_addr + i);
		/* since this is a 32-bit kernel, we can safely ignore the upper 32 bits of mmmt->len */
		printf("Start Addr: %x | Length: %x | Size: %x | Type: %s\n", mmmt->addr_high << 32 | mmmt->addr_low, mmmt->len_low, mmmt->size, mmap_types[mmmt->type - 1]);
	}

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
	// test the CPU exception handler by dividing by 0
	/* int test = 0;
	asm volatile ("div %b0" : "+a"(test)); */
	/* now that we have interrupt handlers, allow interrupts */
	__asm__ __volatile__ ("sti");

	/* printf("Initializing paging...\n");
	paging_init(); */
	int cr3;
	__asm__("movl %%cr3,%0" : "=r"(cr3));

	printf("L4 page table at: %x\n", cr3);


	for(;;);


}
