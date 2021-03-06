# Declare constants for the multiboot header.
.set ALIGN,    1<<0             # align loaded modules on page boundaries
.set MEMINFO,  1<<1             # provide memory map
.set FLAGS,    ALIGN | MEMINFO  # this is the Multiboot 'flag' field
.set MAGIC,    0x1BADB002       # 'magic number' lets bootloader find the header
.set CHECKSUM, -(MAGIC + FLAGS) # checksum of above, to prove we are multiboot

# Declare a header as in the Multiboot Standard.
.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM


# The kernel entry point.
.section .text
.global _start
.type _start, @function
_start:
       movl $stack_top, %esp

       pushl $0
       pushl %eax 
       pushl $0
       pushl %ebx

	# Call the global constructors.
	call _init

	# Transfer control to the main kernel.
	call kernel_main

	# Hang if kernel_main unexpectedly returns.
	cli
1:	hlt
	jmp 1b
.size _start, . - _start

.global gdt_flush
.type gdt_flush, @function
gdt_flush:
	lgdt (gp)
	mov $0x10, %ax
	mov %ax, %ds
	mov %ax, %es
	mov %ax, %fs
	mov %ax, %gs
	mov %ax, %ss
	jmp $0x08,$flush2
flush2:
	ret
	
.global idt_load
.type idt_load, @function
idt_load:
    lidt (idtp)
    ret

.global isr0
.global isr1
.global isr2
.global isr3
.global isr4
.global isr5
.global isr6
.global isr7
.global isr8
.global isr9
.global isr10
.global isr11
.global isr12
.global isr13
.global isr14
.global isr15
.global isr16
.global isr17
.global isr18
.global isr19
.global isr20
.global isr21
.global isr22
.global isr23
.global isr24
.global isr25
.global isr26
.global isr27
.global isr28
.global isr29
.global isr30
.global isr31

#  0: Divide By Zero Exception
isr0:
    cli
   push $0
    push $0
    jmp isr_common_stub

#  1: Debug Exception
isr1:
    cli
    push $0
    push $1
    jmp isr_common_stub

#  2: Non Maskable Interrupt Exception
isr2:
    cli
    push $0
    push $2
    jmp isr_common_stub

#  3: Int 3 Exception
isr3:
    cli
    push $0
    push $3
    jmp isr_common_stub

#  4: INTO Exception
isr4:
    cli
    push $0
    push $4
    jmp isr_common_stub

#  5: Out of Bounds Exception
isr5:
    cli
    push $0
    push $5
    jmp isr_common_stub

#  6: Invalid Opcode Exception
isr6:
    cli
    push $0
    push $6
    jmp isr_common_stub

#  7: Coprocessor Not Available Exception
isr7:
    cli
    push $0
    push $7
    jmp isr_common_stub

#  8: Double Fault Exception (With Error Code!)
isr8:
    cli
    push $8
    jmp isr_common_stub

#  9: Coprocessor Segment Overrun Exception
isr9:
    cli
    push $0
    push $9
    jmp isr_common_stub

# 10: Bad TSS Exception (With Error Code!)
isr10:
    cli
    push $10
    jmp isr_common_stub

# 11: Segment Not Present Exception (With Error Code!)
isr11:
    cli
    push $11
    jmp isr_common_stub

# 12: Stack Fault Exception (With Error Code!)
isr12:
    cli
    push $12
    jmp isr_common_stub

# 13: General Protection Fault Exception (With Error Code!)
isr13:
    cli
    push $13
    jmp isr_common_stub

# 14: Page Fault Exception (With Error Code!)
isr14:
    cli
    push $14
    jmp isr_common_stub

# 15: Reserved Exception
isr15:
    cli
    push $0
    push $15
    jmp isr_common_stub

# 16: Floating Point Exception
isr16:
    cli
    push $0
    push $16
    jmp isr_common_stub

# 17: Alignment Check Exception
isr17:
    cli
    push $0
    push $17
    jmp isr_common_stub

# 18: Machine Check Exception
isr18:
    cli
    push $0
    push $18
    jmp isr_common_stub

# 19: Reserved
isr19:
    cli
    push $0
    push $19
    jmp isr_common_stub

# 20: Reserved
isr20:
    cli
    push $0
    push $20
    jmp isr_common_stub

# 21: Reserved
isr21:
    cli
    push $0
    push $21
    jmp isr_common_stub

# 22: Reserved
isr22:
    cli
    push $0
    push $22
    jmp isr_common_stub

# 23: Reserved
isr23:
    cli
    push $0
    push $23
    jmp isr_common_stub

# 24: Reserved
isr24:
    cli
    push $0
    push $24
    jmp isr_common_stub

# 25: Reserved
isr25:
    cli
    push $0
    push $25
    jmp isr_common_stub

# 26: Reserved
isr26:
    cli
    push $0
    push $26
    jmp isr_common_stub

# 27: Reserved
isr27:
    cli
    push $0
    push $27
    jmp isr_common_stub

# 28: Reserved
isr28:
    cli
    push $0
    push $28
    jmp isr_common_stub

# 29: Reserved
isr29:
    cli
    push $0
    push $29
    jmp isr_common_stub

# 30: Reserved
isr30:
    cli
    push $0
    push $30
    jmp isr_common_stub

# 31: Reserved
isr31:
    cli
    push $0
    push $31
    jmp isr_common_stub

.extern fault_handler

# Save processor state, set up kernel mode segments, call C fault handler and restore stack frame
isr_common_stub:
   pusha
   push %ds
   push %es
   push %fs
   push %gs
   mov $0x10, %ax   # Load the Kernel Data Segment descriptor!
   mov %ax, %ds
   mov %ax, %es
   mov %ax, %fs
   mov %ax, %gs
   mov %esp, %eax   # Push us the stack
   push %eax
   call fault_handler
   pop %eax
   mov %eax, %esp
   pop %gs
   pop %fs
   pop %es
   pop %ds
   popa
   add $8, %esp     # Cleans up the pushed error code and pushed ISR number
   iret           # pops 5 things at once: CS, EIP, EFLAGS, SS, and ESP! 

# Interrupt Requests
.global irq0
.global irq1
.global irq2
.global irq3
.global irq4
.global irq5
.global irq6
.global irq7
.global irq8
.global irq9
.global irq10
.global irq11
.global irq12
.global irq13
.global irq14
.global irq15

# Start IRQs from IDT entry 32
irq0:
   cli
   push $0
   push $32
   jmp irq_common_stub

irq1:
   cli
   push $0
   push $33
   jmp irq_common_stub

irq2:
   cli
   push $0
   push $34
   jmp irq_common_stub

irq3:
   cli
   push $0
   push $33
   jmp irq_common_stub

irq4:
   cli
   push $0
   push $34
   jmp irq_common_stub

irq5:
   cli
   push $0
   push $35
   jmp irq_common_stub

irq6:
   cli
   push $0
   push $36
   jmp irq_common_stub

irq7:
   cli
   push $0
   push $37
   jmp irq_common_stub

irq8:
   cli
   push $0
   push $38
   jmp irq_common_stub

irq9:
   cli
   push $0
   push $39
   jmp irq_common_stub

irq10:
   cli
   push $0
   push $40
   jmp irq_common_stub

irq11:
   cli
   push $0
   push $41
   jmp irq_common_stub

irq12:
   cli
   push $0
   push $42
   jmp irq_common_stub

irq13:
   cli
   push $0
   push $43
   jmp irq_common_stub

irq14:
   cli
   push $0
   push $44
   jmp irq_common_stub

irq15:
   cli
   push $0
   push $45
   jmp irq_common_stub

.extern irq_handler

irq_common_stub:
    pusha
    push %ds
    push %es
    push %fs
    push %gs
    mov $0x10, %ax
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %gs
    mov %esp, %eax
    push %eax

    call irq_handler

    pop %eax
    mov %eax, %esp
    pop %gs
    pop %fs
    pop %es
    pop %ds
    popa
    add $8, %esp
    iret

.global pd_install
.type pd_install, @function
pd_install:
   mov page_directory, %eax
   mov %eax, %cr3

   mov %cr0, %eax
   or $0x80000001, %eax
   mov %eax, %cr0


# Reserve a stack for the initial thread.
.section .bss
.align 16
stack_bottom:
.skip 16384 # 16 KiB
stack_top:
