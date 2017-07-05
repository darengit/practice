void print(const char *out) {
    unsigned short *primitive_io = (unsigned short *)0xb8000;
    for(int i=0; out[i]; ++i)
        primitive_io[i] = primitive_io[i]&0xFF00 | out[i];
}

typedef void (*ctor)();
extern "C" ctor start_ctors;
extern "C" ctor end_ctors;
extern "C" void callCtors() {
    for(ctor *c=&start_ctors; c!=&end_ctors; ++c)
        (*c)();
}

extern "C" void wyoosmain() {
    print("wyoos.org (write your own OS)");

    while(true);
}
