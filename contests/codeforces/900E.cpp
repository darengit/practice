#include <bits/stdc++.h>

using namespace std;

int main() {
	int n,m;
	string s;

	cin >> n >> s >> m;

	vector<int> dpMarks(n);
	vector<bool> dpEnds(n);

	int l=0,r=0,marks=0;

	for(int i=0; i<n; ++i) {
		marks += s[i]=='?';
		if(i>=m) marks-=s[i-m]=='?';
		dpMarks[i]=marks;
	}

	while(r<n) {
		int lastValidChr = l;
		for(;(s[r]=='?' || (s[r]-'a')^(r-l)%2==0) && r<n; ++r) {
			if(r-l+1>=m) {
				dpEnds[r] = (r-l-m)%2 || dpMarks[r]==m;
			}
			if(s[r]!='?') lastValidChr=r;
		}
/*
		--r,++l;
		while(r>l && s[r]=='?') --r;
		r=max(r,l);
		*/
		l=lastValidChr+1;
	}

	vector<int> dpMaxT(n);
	vector<int> dpMinMarks(n);

	for(int i=0; i<n; ++i) {
		if(i-m+1==0 && dpEnds[i]) {
			dpMaxT[i]=dpEnds[i];
			dpMinMarks[i]=dpMarks[i];
		} else if(i-m>=0) {
			dpMaxT[i]=dpMaxT[i-1];
			dpMinMarks[i] = dpMinMarks[i-1];

			if(dpEnds[i])
			if(dpMaxT[i-m]==dpMaxT[i])
				dpMaxT[i]=dpMaxT[i-m]+1, dpMinMarks[i]=dpMinMarks[i-m]+dpMarks[i];
			else if(dpMaxT[i-m]+1==dpMaxT[i] && dpMinMarks[i-m]+dpMarks[i]<dpMinMarks[i])
				dpMinMarks[i] = dpMinMarks[i-m]+dpMarks[i];

		}
	}

	cout << dpMinMarks[n-1];
	return 0;
}
