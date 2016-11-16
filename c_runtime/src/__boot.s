.text
.global _start

_start: 
    movq %rsp, %rdi # pass current stack pointer as only argument
    callq __main # call main which will properly exit and terminate process
