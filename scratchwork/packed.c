#include <stdio.h>


struct unpacked {
  char m1;
  long m2;
  short m3;
  int m4;
};

struct packed {
  char m1;
  long m2;
  short m3;
  int m4;
}__attribute__((packed));

struct packed1 {
  char m1;
  long m2;
  short m3;
  int m4;
}__attribute__((packed, aligned(1)));

struct packed2 {
  char m1;
  long m2;
  short m3;
  int m4;
}__attribute__((packed, aligned(2)));

struct packed4 {
  char m1;
  long m2;
  short m3;
  int m4;
}__attribute__((packed, aligned(4)));

struct packed8 {
  char m1;
  long m2;
  short m3;
  int m4;
}__attribute__((packed, aligned(8)));

struct packed16 {
  char m1;
  long m2;
  short m3;
  int m4;
}__attribute__((packed, aligned(16)));


int main() {
  printf("unpacked:  %lu\n", sizeof(struct unpacked));
  printf("packed:    %lu\n", sizeof(struct packed));
  printf("packed1:   %lu\n", sizeof(struct packed1));   printf("packed2:   %lu\n", sizeof(struct packed2));
  printf("packed4:   %lu\n", sizeof(struct packed4));
  printf("packed8:   %lu\n", sizeof(struct packed8));
  printf("packed16:  %lu\n", sizeof(struct packed16));
}
