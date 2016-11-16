/*
 * The entry point of this entire program
 * is __boot.s, which i've kept minimal
 * and use this __main() to parse the
 * arguments to main() from the stack
 */

extern int main(int argc, char **argv, char **envp);
extern void __exit(int exitcode);

void __main(void *stack) {
    int argc = *((int *)stack);
    char **argv = (char **)stack+1;
    char **envp = argv+argc+1;
    int ret = main(argc, argv, envp);
    __exit(ret);
}
