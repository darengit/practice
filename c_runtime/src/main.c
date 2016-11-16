/*
 * This is the closest thing to the actual user code
 * note that it doesn't include any libraries, other than
 * the kernel, everything that's necessary to run this simple
 * program is included in this directory. and we will link
 * against it.
 */

extern void write(int fp, char * buf, int len);

int strln(const char *s) {
    int l=0;
    while(*(s+l)) ++l;
    return l;
}

void println(char *s) {
    write(1, s, strln(s));
    write(1, "\n", 1);
}

int main(int argc, char **argv, char **envp) {
    println("*** command line args ***");
    for(int i=1; i<argc; ++i) println(argv[i]);

    println("*** environment ***");
    while(*envp) println(*envp++);

    return argc;
}
