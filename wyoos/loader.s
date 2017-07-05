.set MAGIC, 0x1badb002
.set FLAGS, (1<<0 | 1<<1)
.set CHECKSUM, -(MAGIC+FLAGS)

.section .multiboot
    .long MAGIC
    .long FLAGS
    .long CHECKSUM

.section .text
.extern wyoosmain
.extern callCtors
.global loader

loader:
    mov $stack_ptr, %esp
    call callCtors
    push %eax
    push %ebx
    call wyoosmain

_stop:
    cli
    hlt
    jmp _stop

.section .bss
.space 4*1024*1024;
stack_ptr:
