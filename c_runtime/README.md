custom barebone c runtime
=========================

This is basically copied from sources on the internet. However vast majority of examples
are for 32bit systems. Here I've made the necessary changes for this to run on 64bit ubuntu.
The major differences are that the initial stack configuration upon entering _start
is slightly different. syscalls are made completely differently. and argument registers
are different.

i customized the exit value to be the number of commandline arguments, use:
bin/a.out
echo $?
to verify that all aspects of the program is running properly. however due to this
non zero exit value 'make run' will say that the program errors at the end, ignore this.
