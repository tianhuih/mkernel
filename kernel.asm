bits 32

section .text			;multiboot specs

	align 4
				;dd defines a double word of size 4 bytes
	dd 0x1BADB002		;magic num to identify the header
	dd 0x00			;flags
	dd -(0x1BADB002 + 0x00)	;checksum -  m+f+c must be zero

section .text

global start
extern kmain 			;defined in kernel.c file

start: 
	cli 			;clear interrupts
	mov esp, stack_space	;set stack pointer 
	call kmain
	hlt			;halt the CPU

section .bss
resb 8192			;reserves 8k for stack 
stack_space: 
