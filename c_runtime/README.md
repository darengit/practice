custom barebone c runtime
=========================

This is basically copied from sources on the internet. However vast majority of examples
are for 32bit systems. Here I've made the necessary changes for this to run on 64bit ubuntu.
The major differences are that the initial stack configuration upon entering _start
is slightly different. syscalls are made completely differently. and argument registers
are different. syscall and normal routine calls use the same register convention which
make wrapper functions for syscalls which we can call from c very convenient.

i customized the exit value to be the number of commandline arguments, use:
```
bin/a.out
echo $?
```
to verify that all aspects of the program is running properly. however due to this
non zero exit value 'make run' will say that the program errors at the end, ignore this.

There are only a few lines of assembly in 3 routines, one to put the initial stack into an argument
register and then call our initial c function. and one for each syscall we need, write and exit.

use `strip bin/a.out` to see how small your can get the executable to be. also use `objdump -d bin/a.out`
to examine the executable. You can see that its a lot similar vs. using default c runtime.
