#include <stdarg.h>
#include <stdio.h>

int mx(int, ...);

int main() {
	printf("max of 2,0,1: %d\n", mx(3,2,0,1));
}

int mx(int nargs, ...) {
	va_list ap;

	va_start(ap, nargs);
	int res = va_arg(ap,int);
	for(int i=1; i<nargs; ++i) {
		int tmp = va_arg(ap,int);
		if(tmp > res) res = tmp;
	}

	return res;
}
