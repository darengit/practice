#include <iostream>
#include <vector>

using namespace std;

int main() {
	int n;
	cin >> n;

	int x=0;
	vector<int> nums(n);

	for(int i=0; i<n; ++i) {
		cin >> nums[i];
		for(int j=0; j<i; ++j)
			x = (nums[j]>nums[i] ? !x : x);
	}

	int m;
	cin >> m;

	int l,r,w;
	vector<int> res(m);
	for(int i=0; i<m; ++i) {
		cin >> l >> r;
		w=r-l+1;
		x = (w/2%2 ? !x : x);
		res[i]=x;
	}

	for(int i: res)
		cout << (i ? "odd" : "even") << endl;

	return 0;
}
