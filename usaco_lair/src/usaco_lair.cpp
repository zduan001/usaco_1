#include <bits/stdc++.h>
using namespace std;

int main() {
	int n, m;
	cin >> n >>m;
	vector<vector<int>> graph(n, vector<int>(n, 0));
	vector<tuple<int, int, int>> inputs;
	int u, v;
	char t;
	for (int i = 0; i <  m; i++) {
		cin >> u >> v >> t;
//		graph[u-1][v-1] = t =='T' ? 1 : -1;
		inputs.push_back({u-1, v-1, t == 'T'? 1 : -1});
	}
	for (int i = 0; i < n; i++) {
		graph[i][i] = 1;
	}

//	for (int i = 0; i < n; i++) {
//		for (int j = 0; j < n; j ++) {
//			cout << graph[i][j] << " ";
//		}
//		cout << endl;
//	}

	for (int k = 0; k < m; k++) {
		int u, v, w;
		tie(u, v, w) = inputs[k];
		graph[u][v] = w;
		for (int i = 0; i < n; i++) {
			if (graph[i][u] != 0) {
				graph[i][v] = graph[i][u] * w;
			}
			if (graph[v][i] != 0) {
				graph[u][i] = w * graph[v][i];
			}
		}

//		for (int i = 0; i < n; i++) {
//			for (int j = 0; j < n; j ++) {
//				cout << graph[i][j] << " ";
//			}
//			cout << endl;
//		}

		for (int i = 0; i < n; i++) {
			if (graph[i][i] == -1) {
				cout << k << endl;
				return 0;
			}
		}
	}

	return 0;
}
