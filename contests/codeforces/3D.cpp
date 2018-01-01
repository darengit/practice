#include <iostream>
#include <queue>

using namespace std;

typedef long long llong;

int main() {
	ios::sync_with_stdio(false);

	priority_queue<vector<llong>> starCosts;

	string parens;
	cin >> parens;

	int left=0,right=0,stars=0;

	llong costl,costr, ans=0;
	for(int i=0; i<parens.size(); ++i) {
		switch (parens[i]) {
		case '(':
			++left;
			break;
		case ')':
			++right;
			break;
		default:
			++stars;
			cin >> costl >> costr;
			starCosts.push({costr-costl, i, costl, costr});
		}

		if(right+stars>left) {
			if(starCosts.empty()) {
				cout << -1;
				return 0;
			}

			parens[starCosts.top()[1]]='(';
			ans += starCosts.top()[2];
			starCosts.pop();
			++left;
			--stars;
		}

	}
	
	if(right+stars!=left) {
		cout << -1 << endl;
		return 0;
	}

	while(starCosts.size()) {
		parens[starCosts.top()[1]]=')';
		ans += starCosts.top()[3];
		starCosts.pop();
	}

	cout << ans << endl;
	cout << parens;
	return 0;
}
