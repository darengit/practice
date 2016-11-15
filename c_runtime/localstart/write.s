.text
.global write

write:
    movq %rdi,%rbx
    movq %rsi,%rcx
    movl $4,%eax # arg1 syscall number, 4=write()
    int $0x80   # interrupt 0x80, syscall
    retq
