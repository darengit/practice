.text
.global write

write:
    mov $4,%rax # arg1 syscall number, 4=write()
    int $0x80   # interrupt 0x80, syscall
    retq
