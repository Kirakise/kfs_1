bits 32

section .multiboot
        dd 0x1BADB002
        dd 0x0

section .text
global start
extern kernel_entry

start:
        cli
        mov esp, stack_space
        call kernel_entry
        hlt

section .bss
resb 16000
stack_space:
