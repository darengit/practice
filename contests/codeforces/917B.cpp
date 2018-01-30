#include <bits/stdc++.h>
typedef long long llong;

using namespace std;

void fillDp(auto& graph, auto& dp, int first, int second, char lastChar) {
    if(dp[first][second][lastChar-'a']>=0) return;

    for(int i=0; i<graph[first].size(); ++i)
    if(graph[first][i]>=lastChar) {
        fillDp(graph, dp, second, i, graph[first][i]);
        if(dp[second][i][graph[first][i]-'a']==0) {
            dp[first][second][lastChar-'a']=1;
            return;
        }
    }

    dp[first][second][lastChar-'a']=0;
    return;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n,m;
    cin >> n >> m;

	vector<vector<char>> graph(n, vector<char>(n));
    for(int i=0; i<m; ++i) {
        int v,u; char c;
        cin >> v >> u >> c;
        graph[--v][--u]=c;
    }

    vector<vector<vector<int>>> dp(n, vector<vector<int>>(n, vector<int>(26,-1)));

    for(int i=0; i<n; ++i)
    for(int j=0; j<n; ++j)
        fillDp(graph, dp, i, j, 'a');

    for(int i=0; i<n; ++i) {
        for(int j=0; j<n; ++j) {
            cout << (dp[i][j][0]==1 ? "A" : "B");
        }
        cout << endl;
    }

    return 0;
}
