#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

typedef long long llong;

string f0 = "What are you doing at the end of the world? Are you busy? Will you save us?";
string g0 = "What are you doing while sending \"";
string g1 = "\"? Are you busy? Will you send \"";
string g2 = "\"?";


char f(const vector<llong>& lens, llong n, llong k) {
	if(!n)
		return (k<f0.size() ? f0[k] : '.');

	if(k<g0.size())
		return g0[k];
	if(k<g0.size()+lens[n-1])
		return f(lens, n-1, k-g0.size());
	if(k<g0.size()+lens[n-1]+g1.size())
		return g1[k-g0.size()-lens[n-1]];
	if(k>=g0.size()+lens[n-1]*2+g1.size()+g2.size())
		return '.';
	if(k>=g0.size()+lens[n-1]*2+g1.size())
		return g2[k-g0.size()-lens[n-1]*2-g1.size()];
	return f(lens, n-1, k-g0.size()-lens[n-1]-g1.size());
}


int main() {
	llong q;
	cin >> q;
	vector<vector<llong>> qs(q, vector<llong>(2));

	llong nmax=0;
	llong kmax=0;
	for(int i=0; i<q; ++i) {
		cin >> qs[i][0] >> qs[i][1];
		--qs[i][1];
		nmax = max(nmax, qs[i][0]);
		kmax = max(kmax, qs[i][1]);
	}

	vector<llong> lens;
	lens.push_back(f0.size());
	while(lens.back() < kmax)
		lens.push_back(g0.size()+g1.size()+g2.size()+2*lens.back());

	for(int i=0;i<q;++i) {
		llong n=qs[i][0];
		llong k=qs[i][1];

		if(n>=lens.size()) {
			if(k<n*g0.size()) {
				cout << g0[k%g0.size()];
				continue;
			} else {
				llong tmp = (n-lens.size()+1);
				k -= tmp*g0.size();
				n = lens.size()-1;
			}
		}

		cout << f(lens, n,k);


	}
	return 0;
}
