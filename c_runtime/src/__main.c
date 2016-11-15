void __main(int argc, char *stack) {
    char **argv = &stack;
    char **envp = argv+argc+1;
    int ret = main(argc, argv, envp);
    __exit(ret);
}
