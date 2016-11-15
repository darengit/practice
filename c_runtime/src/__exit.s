.text
.global __exit

__exit:
    mov $1, %eax # syscall #1
    int $0x80 #interrupt 0x80, syscall
    retq
