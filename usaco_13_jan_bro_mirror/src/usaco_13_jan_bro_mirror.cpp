#include <bits/stdc++.h>


using namespace std;

typedef pair<int,int> pii;

pii turn(pii input, char mirror){
	int x = input.first;
	int y = input.second;
	if (mirror == '/') {
		if (x == 1 && y == 0) {
			return {0, 1};
		}
		if (x == 0 && y == 1) {
			return {1,0};
		}
		if (x == -1 && y == 0) {
			return {0, -1};
		}
		if (x == 0 && y == -1) {
			return {-1, 0};
		}
	} else if (mirror == '\\') {
		if (x == 1 && y == 0) {
			return {0, -1};
		}
		if (x == 0 && y == 1) {
			return {-1,0};
		}
		if (x == -1 && y == 0) {
			return {0, 1};
		}
		if (x == 0 && y == -1) {
			return {1, 0};
		}
	}
	return {0,0};
}

//bool canToggle(pii input1, pii input2, char mirror) {
//	mirror = mirror == '/' ? '\\' : '/';
//	pii output = turn(input1, mirror);
//	return output.first == input2.frist && output.second == input2.second;
//}

bool find(int index) {}

int main() {
	freopen("mirrors.in", "r", stdin);
	freopen("mirrors.out", "w", stdout);
	int n, x, y;
	cin >> n >> x >> y;
	int max_x = 0, max_y = 0, min_x = 0, min_y = 0;
	map<pii, char> map;
	for (int k = 0; k < n; k++) {
		int i, j;
		char m;
		cin >> i >> j >> m;
		map[{i,j}] = m;
		max_x = max(max_x, i);
		max_y = max(max_y, j);
		min_x = min(min_x, i);
		min_y = min(min_y, j);
	}

	pii directions[4] = {{1,0}, {0,1}, {-1,0}, {0,-1}};
	pii start = {0,0};
	set<pii> visited;
	for (int k = 0; k < 4; k++) {
		pii dir = directions[k];
		start = {0,0};
		while(start.first <=max_x && start.second <= max_y && start.first >= 0 && start.second >= 0) {
			visited.insert(start);
			if (map.find(start) != map.end()) {
				dir = turn(start, map[start]);

			}
			start.first += dir.first;
			start.second = dir.second;
		}
	}

	return 0;
}
