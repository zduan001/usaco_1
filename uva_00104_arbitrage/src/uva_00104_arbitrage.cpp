#include <bits/stdc++.h>
using namespace std;



int main() {
	int n;
	float rate;
	while(cin >> n) {
		vector<vector<float>> w (n, vector<float>(0));
		for (int i = 0; i < n; i ++) {
			for (int j = 0; j < n; j ++) {
				if (i == j) {
					w[i].push_back(1.0f);
					continue;
				}
				cin >> rate;
				w[i].push_back(rate);
			}
		}

		cout << endl;
		for (int i = 0; i < n; i ++) {
			for (int j = 0; j < n; j++) {
				cout << w[i][j] << " ";
			}
			cout << endl;
		}
		cout << " -------------------------------- " << endl;

		vector<vector<int>> p(n, vector<int>(n, 0));
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				p[i][j]= i;
			}
		}

		for (int k = 0; k < n; k++) {
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					if (i == j) continue;
					if (w[i][k] * w[k][j] > w[i][j]) {
						w[i][j] = w[i][k] * w[k][j];
						p[i][j] = k;
					}
				}
			}
			for (int i = 0; i < n; i ++) {
				for (int j = 0; j < n; j++) {
					cout << w[i][j] << " ";
				}
				cout << endl;
			}
			cout << " -------------------------------- " << endl;
		}

		for (int i = 0; i < n; i ++) {
			for (int j = 0; j < n; j++) {
				cout << w[i][j] << " ";
			}
			cout << endl;
		}
		cout << " -------------------------------- " << endl;

		for (int i = 0; i < n; i ++) {
			for (int j = 0; j < n; j++) {
				cout << p[i][j] << " ";
			}
			cout << endl;
		}
		cout << " -------------------------------- " << endl;

		int max_length = n+1;
		vector<int> res;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (w[i][j] * w[j][i] > 1.0) {
					vector<int> trace;
					int x = i;
					trace.push_back(x);
					while(p[x][j] != x) {
						trace.push_back(p[x][j]);
						x = p[x][j];
					}
					trace.push_back(j);
					if ((int)trace.size() < max_length) {
						res = trace;
					}
				}
			}
		}

		for (auto i : res) {
			cout << i << " ";
		}
		cout << endl;
	}

	return 0;
}