void println(char *s) {
    write(1, s, strlen(s));
    write(1, "\n", 1);
}

int main(int argc, char **argv, char **envp) {
    println("*** command line args ***");
    for(int i=1; i<argc; ++i) println(argv[i]);

    println("*** environment ***");
    while(*envp) println(*envp++);

    return argc;
}
