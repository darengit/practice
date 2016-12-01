#include <stdbool.h>

#include "benchmarquee.h"

int holdwater2pass(INPUT_TYPE input) {
    int *h = input.a;
    int l = input.l;

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
    //return 0;
	return tot;
}

int holdwater1pass(INPUT_TYPE input) {
    int *h = input.a;
    int l = input.l;

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

