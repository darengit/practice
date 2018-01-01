#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
	int cherryPickup(vector<vector<int>>&& grid) {

		int n=grid.size();

		for(auto& v: grid)
		for(auto& i: v) if(i<0) i=-n*n;

		vector<vector<vector<int>>> dp(n*2-1, vector<vector<int>>(n, vector<int>(n, -n*n)));

		dp[n-1][0][0]=grid[0][0];

		for(int i=0; i<2*n-1; ++i) { //ith slash diagnal, r+c=i
		for(int j=1-n; j<n; ++j) { //jth back slash diagnal, c-r=j

			int r=-1;
			int c=-1;

			if((i+j)%2==0) c=(i+j)/2;
			if((i-j)%2==0) r=(i-j)/2;

			if(r>=0 && r<n && c>=0 && c<n && grid[r][c]>=0) {
cout << i << " " << j << " " << r << " " << c << endl;

			for(int row=r,col=c; row>=0 && col<n; --row,++col) {
				if(grid[row][col]==-1) continue;

				

				int d = j+n-1;
				if(d>0 && r<n-1 && grid[r+1][c]>=0) {
					if(row==r) 
						dp[d-1][row+1][col] = max(dp[d-1][row+1][col], dp[d][row][col]+grid[row+1][col]);
					else if(grid[row+1][col]>=0)
						dp[d-1][row+1][col] = max(dp[d-1][row+1][col], dp[d][row][col]+grid[row+1][col]+grid[r+1][c]);

					if(col<n-1 && grid[row][col+1]>=0)
						dp[d-1][row][col+1] = max(dp[d-1][row][col+1], dp[d][row][col]+grid[row][col+1]+grid[r+1][c]);
				}

				if(d<2*n-2 && c<n-1 && grid[r][c+1]>=0 ) {
					int newr=row+1,newc=col;

					if(newr<n)
					if(newc-newr==j+1) {
						if(grid[newr][newc]>=0)
							dp[d+1][newr][newc] = max(dp[d+1][newr][newc], dp[d][row][col]+grid[newr][newc]);
					} else if (newc-newr>j+1) {
						if(grid[newr][newc]>=0)
							dp[d+1][newr][newc] = max(dp[d+1][newr][newc], dp[d][row][col]+grid[newr][newc]+grid[r][c+1]);
					}

					
					newr=row, newc=col+1;
					if(newc<n)
					if(newc-newr==j+1) {
						if(grid[newr][newc]>=0)
							dp[d+1][newr][newc] = max(dp[d+1][newr][newc], dp[d][row][col]+grid[newr][newc]);
					} else if (newc-newr>j+1) {
						if(grid[newr][newc]>=0)
							dp[d+1][newr][newc] = max(dp[d+1][newr][newc], dp[d][row][col]+grid[newr][newc]+grid[r][c+1]);
					}

				}

			}
			}
		}
		}


for(auto& m: dp) {
for(auto& v: m) {
for(auto& i: v)
	cout << i << " ";
cout << endl;


}
cout << endl;
}


		return max(dp[n-1][n-1][n-1],0);
	}
};

int main() {
Solution s;

cout << s.cherryPickup(vector<vector<int>> {{0,1,-1},{1,0,-1},{1,1,1}}) << endl;
cout << s.cherryPickup(vector<vector<int>> {{1,1,-10},{1,-10,1},{-10,1,1}}) << endl;

return 0;
}

