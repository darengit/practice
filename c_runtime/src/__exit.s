.text
.global __exit

__exit:
    movq $0x3c, %rax # syscall 60 which is exit
    syscall
