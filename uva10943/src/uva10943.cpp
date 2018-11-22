#include <bits/stdc++.h>
#define MOD 1000000
using namespace std;

int main() {
	int n, k;
	while(1) {
		cin >> n >> k;
		if (!n && !k) {return 0;}
		vector<vector<int>> dp(k+1, vector<int>(n+1,1));
		for (int i = 2; i <= k; i++) {
			for (int j = 0; j <= n; j++) {
				int count = 0;
				for(int l = 0; l <= j; l++) {
					count += dp[i-1][j-l];
					count %= MOD;
				}
				dp[i][j] = count;
			}
		}
//		for(int i = 0; i<=k; i++) {
//			for(int j = 0; j<=n; j++) {
//				cout << dp[i][j] << " ";
//			}
//			cout << endl;
//		}
		cout << dp[k][n] << endl;

	}
	cout << endl;
	return 0;
}