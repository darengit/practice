#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

int main() {
	int n,m,c;
	cin >> n >> m >> c;

	int l=-1,r;
	vector<int> game(n);

	for(int i=0; i<m; ++i) {
		int tmp;
		cin >> tmp;

		if(l== -1) {
			l=max(tmp*n/c-1,0);
			game[l]=tmp;
			r = l+1;
			cout << r;
		} else {
			if(tmp<=game[l] && tmp<game[r-1]) {
				if(l>0) {
					game[--l] = tmp;
					cout << l+1;
				} else {
					int idx=l;
					while(game[idx]==tmp) ++idx;
					game[idx] = tmp;
					cout << idx+1;
					r = max(idx+1,r);

				}
			} else if (tmp>=game[r-1] && tmp>game[l]) {
				if(r<n) {
					game[r++] = tmp;
					cout << r;
				} else {
					int idx=r-1;
					while(game[idx]==tmp) --idx;
					game[idx] = tmp;
					cout << idx+1;
					l = min(l,idx);
				}
			} else {
				int left=max(l-1,0),right=min(r,n-1);
				for(int j=l; j<r; ++j)
					if(game[j]<tmp) left=j;

				for(int j=r-1; j>=l; --j)
					if(game[j]>tmp) right=j;

				if(n-right > left) {
					game[right]=tmp;
					cout << right+1;
				} else {
					game[left]=tmp;
					cout << left+1;
				}

			}

		}

		cout << endl;

		if(l==0 && r==n) return 0;
	}

	return 0;
}
