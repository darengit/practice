#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <stdio.h>
#include <time.h>

int holdwater2pass(int *h, int l) {
	int m=0;
	int m_i=0;

	for(int i=0; i<l; ++i)
		if(h[i]>m) {
			m = h[i];
			m_i = i;
		}

	int tot = 0;
	int msf = 0; // max so far
	for(int i=0; i<m_i; ++i) {
		if(h[i]<msf)
			tot += msf-h[i];
		else if (h[i]>msf)
			msf = h[i];
	}

	msf = 0;
	for(int i=l-1; i>m_i; --i) {
		if(h[i]<msf)
			tot += msf-h[i];
		else if (h[i]>msf)
			msf = h[i];
	}
	return tot;
}

int holdwater1pass(int *h, int l) {
	int rmax=h[0];
	int i=0;
	int lmax=h[l];
	int j=l;

	bool increment_right = (rmax < lmax) ? true : false;

	int tot = 0;
	while (i<j-1) {
		if(increment_right) {
			if(h[++i]>rmax) {
				rmax = h[i];
				if(rmax>lmax)
					increment_right = false;
			} else
				tot += rmax-h[i];
		} else {
			if(h[--j]>lmax) {
				lmax = h[j];
				if(lmax>rmax)
					increment_right = true;
			} else
				tot += lmax-h[j];
		}
	}
	return tot;
}

int main() {

	for(int l=10; l<1000000000; l*=10) {
		int *heights = (int *)malloc(sizeof(int *)*l);
		for(int i=0; i<l; ++i)
			heights[i] = rand()%1024;

        clock_t start, end;

#ifdef TWO_PASS
		start = clock();
		int twopass = holdwater2pass(heights, l);
		end = clock();

		double rt2pass = (double)(end-start)/CLOCKS_PER_SEC;
#endif
#ifdef ONE_PASS
		start = clock();
		int onepass = holdwater1pass(heights, l);
		end = clock();

		double rt1pass = (double)(end-start)/CLOCKS_PER_SEC;
#endif
#ifdef TWO_PASS
#ifdef ONE_PASS
		assert(onepass == twopass);
#ifdef OUTPUT_EXECTIME
		printf("length %d 1pass %f 2pass %f\n", l, rt1pass, rt2pass);
#endif
#endif
#endif

	} 

}
