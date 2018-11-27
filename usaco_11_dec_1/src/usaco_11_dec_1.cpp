#include <bits/stdc++.h>
using namespace std;

vector<int> res;
set<int> visited;

void dfs(unordered_map<int, set<int>>& graph, int u) {
	if(visited.find(u) != visited.end()) {
		return;
	}
	visited.insert(u);
	for (auto v : graph[u]) {
		dfs(graph, v);
	}
	res.push_back(u);
}

int main() {
	freopen("photo.out", "w", stdout);
	unordered_map<int, vector<int>> input;
	vector<int> v;
	int n;
	cin >> n;
	int cowId;
	for (int j = 0; j < 5; j++) {
		for (int i = 0; i < n; i ++) {
			cin >> cowId;
			input[cowId].push_back(i);
		}
	}

//	for (auto x : input) {
//		cout << x.first << " : ";
//		for (auto i : x.second) {
//			cout << i << " ";
//		}
//		cout << endl;
//	}
//	cout << endl;

	for(auto i : input) {
		v.push_back(i.first);
	}

	unordered_map<int, set<int>> graph;
	for (int i = 0; i < (int)v.size(); i++) {
		for (int j = i+1; j < (int)v.size(); j++){
			int xfront = 0, yfront = 0;
			for (int k = 0; k < 5; k ++) {
				if (input[v[i]][k] < input[v[j]][k]) {
					xfront ++;
				} else {
					yfront ++;
				}
				if (xfront >=3) {
					graph[v[i]].insert(v[j]);
				} else if (yfront >=3) {
					graph[v[j]].insert(v[i]);
				}
			}
		}
	}

//	for (auto x : graph) {
//		cout << x.first << " : ";
//		for (auto i : x.second) {
//			cout << i << " ";
//		}
//		cout << endl;
//	}
//	cout << endl;
	for(int i = 0; i < (int)v.size(); i++) {
		if (visited.find(v[i]) != visited.end()) {continue;}
		dfs(graph, v[i]);
	}
	reverse(res.begin(), res.end());
	for (auto i : res) {
		cout << i << endl;
	}
	cout <<endl;



	return 0;
}
