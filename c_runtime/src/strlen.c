int strlen(const char *s) {
    int l=0;
    while(*(s+l)) ++l;
    return l;
}
