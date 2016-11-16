.text
.global write

write:
    movq $1,%rax # arg1 syscall number, 1=write()
    syscall # x86_64 syscall, same parameter registers as c function call which saves work =)
    retq
