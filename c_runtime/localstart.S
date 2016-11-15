.global _start

_start:
    call main
    movl $1, %eax #put 1 as argument, syscall 1 is SYS_exit
    xorl %ebx,%ebx #set %ebx to 0, this will be exit status
    int $0x80 #interrupt 80 is syscall, which will take %eax and %ebx as arguments
