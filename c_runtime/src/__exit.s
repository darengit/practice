.text
.global __exit

__exit:
    #movq %rdi, %rbx
    mov $60, %eax # syscall #60
    #int $0x80 #interrupt 0x80, syscall
    syscall
    #retq
