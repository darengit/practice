.text
.global write

write:
    movq $1,%rax # arg1 syscall number, 1=write()
    syscall
    retq
