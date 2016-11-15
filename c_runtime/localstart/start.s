.global _start

_start:
    call main
    movl %eax,%ebx
    movl $1,%eax #put 1 as argument, syscall 1 is SYS_exit
    int $0x80 #interrupt 80 is syscall, which will take %eax and %ebx as arguments
