#include <bits/stdc++.h>
using namespace std;

#define MAX_N 13
#define INF 2000000

class Solution {
public:
	int tsp(int c, int mask) {
	  if (mask == (1<<n)-1) return graph[c][0];  // return to close the loop
	  if (memo[c][mask] != -1) return memo[c][mask];
	  int ans = 2000000000;
	  for (int nxt = 1; nxt <= n; nxt++) // O(n) here
		if (!(mask & (1<<(nxt-1)))) // if coordinate nxt is not visited yet
		  ans = min(ans, graph[c][nxt] + tsp(nxt, mask | (1<<(nxt-1))));
	  return memo[c][mask] = ans;

//		bitset<5> y(mask);
//		bitset<8> x((1<<(n-1))-1);
//		cout << "start point: " << c << " mask is: " << y << " match mask is " << x << endl;
//		if(mask == (1<<(n-1))-1) {
//			cout << "last step length" << graph[c][0] << endl;
//			return graph[c][0];
//		}
//		if(memo[c][mask] != -1) return memo[c][mask];
//		int ans = INF;
//		for(int next = 1; next < n; next++) {
//			if(!(mask & (1<<(next-1)))) {
//				int tmp = tsp(next, mask | ( 1 << (next-1)));
//				if (graph[c][next] + tmp < ans) {
//					ans = graph[c][next] + tmp;
//					nxt[c] = next;
//				}
////				ans = min(ans, graph[c][next] + tsp(next, mask | (1 <<(next-1))));
//			}
//		}
////		cout << c << " " << ans << endl;
//		return memo[c][mask] = ans;
	}

    string shortestSuperstring(vector<string>& A) {
    	n = A.size();
    	vector<vector<string>> prefix_vec;
    	vector<vector<string>> suffix_vec;
    	for(int i = 0; i < n; i++) {
    		prefix_vec.push_back(prefix(A[i]));
    		suffix_vec.push_back(suffix(A[i]));
    	}
    	for (int i = 0; i < n; i++) {
    		for (int j = 0; j < n; j++) {
    			if (i == j) {continue;}
    			graph[i][j] = A[i].length() + A[j].length() + findoverlap(suffix_vec[i], prefix_vec[j]);
    		}
    	}

    	for (int i = 0; i < n; i++) {
    		for (int j = 0; j < n; j++) {
    			cout << graph[i][j] << " ";
    		}
    		cout << endl;
    	}
    	memset(memo, -1, sizeof memo);
    	memset(nxt, -1, sizeof nxt);
//    	tsp(0,0);
    	cout << tsp(0, 1) << endl;
    	for (int i = 0; i < n ; i ++) {
    		cout << nxt[i] << "  ";
    	}
    	cout << endl;
    	return "";
    }

private:
    int n, graph[MAX_N][MAX_N], memo[MAX_N][1<<(MAX_N-1)], nxt[MAX_N];
    int findoverlap(vector<string> suffix, vector<string> prefix) {
    	int res= 0;
    	for (auto suf : suffix) {
    		for (auto pre : prefix) {
    			int tmp = 0;
    			while(suffix[tmp] == prefix[tmp]) {
    				tmp++;
    			}
    			res = max (res, tmp);
    		}
    	}
    	return res;
    }

    vector<string> prefix(string s1) {

    	vector<string> res;
    	for (int i = 1; i <=s1.length(); i++) {
    		res.push_back(s1.substr(0, i));
    	}
    	return res;
    }
    vector<string> suffix(string s1) {
    	int l = s1.length();
    	vector<string> res;
    	for (int i = 1; i <= s1.length(); i++) {
    		res.push_back(s1.substr(l-i));
    	}
    	return res;
    }
};

int main() {
	Solution* s = new Solution();
	vector<string> input = {"catg","ctaagt","gcta","ttca","atgcatc"};
	s->shortestSuperstring(input);

	return 0;
}
