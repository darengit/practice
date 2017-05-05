#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define BUFSIZE 4096*1024 // at this buffer size on linux i/o time is much less than computation time
#define CHARSET_SIZE 256

// function to divid entire range of chars to symbols that can form a word
// and delimiters
void initializeIssym(bool issym[CHARSET_SIZE], char *chrs) {
    for(int i='0'; i<='9'; ++i)
        issym[i] = true;

    for(int i='a'; i<='z'; ++i)
        issym[i] = true;

    for(int i='A'; i<='Z'; ++i)
        issym[i] = true;

    for(int i=0; chrs[i]; ++i)
        issym[(int)chrs[i]] = true;
}

// return true if the counts of symbols in the word just read can be constructed from input characters
/*
bool isvalid(unsigned short cnts[CHARSET_SIZE], unsigned short chrs_cnts[CHARSET_SIZE]) {
    for(int i=0; i<CHARSET_SIZE; ++i) {
        if(cnts[i]>chrs_cnts[i])
            return false;
    }
    return true;
}
*/

// attempt to use read() with a large buffersize on linux platform, turns out the
// improvement in i/o time is not significant compared to computation time
size_t myread(char *buf, size_t bufsize, FILE *f) {
#ifdef linux
    ssize_t sz = read(f, buf, bufsize);
    if(sz<0) {
        perror("ERROR read(): ");
        exit(1);
    }
    return sz;
#else
    return fread(buf, 1, bufsize, f);
#endif
}

int main(int argc, char *argv[]) {
    if(argc < 3) {
        fprintf(stderr, "usage: %s <charset> <input_file>\n", argv[0]);
        exit(1);
    }

    char *chrs = argv[1];
    char *filename = argv[2];
    size_t maxlen = strlen(chrs);

    bool issym[CHARSET_SIZE] = {false};
    initializeIssym(issym, chrs);
    unsigned short chrs_cnts[CHARSET_SIZE] = {0};
    for(int i=0; chrs[i]; ++i)
        ++chrs_cnts[(int)chrs[i]];
    unsigned short cur[CHARSET_SIZE];
    memset(cur,0,CHARSET_SIZE*sizeof(unsigned short));

    FILE *f = fopen(filename, "r");
    if(!f) {
        perror("ERROR fopen: ");
        return 1;
    }

    char buf[BUFSIZE];
    long valid=0, w=0;
    int prev_delim = -1;
    bool isvalid = true;

    while(true) {
        size_t sz = myread(buf, BUFSIZE, f);
        if(!sz) 
            break;

        // our critical loop
        // the most time consuming operation
        // is  memset()
        for(size_t i=0; i<sz; ++i) {
            if(issym[(int)buf[i]]) { // is a symbol in a word
                if(isvalid)
                    isvalid = ++cur[(int)buf[i]] <= chrs_cnts[(int)buf[i]];
            } else { // is a delimiter
                size_t len = i-prev_delim-1;
                if(len) {
                    if(len<=maxlen && isvalid)
                        ++valid;
                    ++w;
                    memset(cur,0,CHARSET_SIZE*sizeof(unsigned short));
                }
                prev_delim = i;
                isvalid = true;
            }
        }

        prev_delim -= sz;
    }

    fclose(f);

    printf("%ld valid words\n%ld total words\n", valid, w);

    if(!w) {
        fprintf(stderr, "counted 0 words total, exiting before division by 0\n");
        exit(1);
    }

    printf("%lf\n", 1.0*valid/w);

    return 0;
}
