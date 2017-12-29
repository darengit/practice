#include <iostream>
#include <vector>

using namespace std;

int main() {
	int n,k;
	cin >> n >> k;
	vector<int> a(k);
	vector<bool> seen(n+1);

	for(int i=0; i<k; ++i)
		cin >> a[i];

	int prevIdx=-1,cur=1;

	for(int i=0; i<k; ++i) {
		seen[a[i]]=true;
		if(a[i]==cur) {
			++cur;
			for(;prevIdx>=0 && a[prevIdx]<=cur;--prevIdx) {
				if(a[prevIdx]==cur)
					++cur;
			}
		} else {
			if(prevIdx>=0 && a[i]>a[prevIdx]) {
				cout << -1;
				return 0;
			} else {
				prevIdx=i;
			}
		}
	}

	for(int i: a)
		cout << i << " ";

	if(prevIdx>=0)
	for(int i=a[prevIdx]-1; i>=cur; seen[i--]=true)
		cout << i << " ";

	while(prevIdx>=0) {
		int idx=prevIdx;
		while(prevIdx>=0 && a[prevIdx]<=a[idx]) --prevIdx;
		if(prevIdx>=0)
		for(int i=a[prevIdx]-1; i>a[idx]; seen[i--]=true)
			cout << i << " ";
	}

	for(int i=n; i>0; --i)
	if(!seen[i])
		cout << i << " ";

	return 0;
}
