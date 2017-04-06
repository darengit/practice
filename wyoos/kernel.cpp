void print(char *out) {
    unsigned short *primitive_io = (unsigned short *)0xb8000;
    for(int i=0; out[i]; ++i)
        primitive_io[i] = primitive_io[i]&0xFF00 | out[i];
}

extern "C" void wyoosmain() {
    print("wyoos.org (write your own OS)");

    while(true);
}
