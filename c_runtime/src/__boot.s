.text
.global _start

_start:
    movq (%rsp),%rdi
    movq %rsp,%rsi
    callq __main
#    retq
