#include <bits/stdc++.h>
using namespace std;

vector<int> cuts;

int recur(map<pair<int,int>, int>& map, int l , int r) {
	if ((r -l) <= 1) {return 0;}
	if (map.find({l,r}) != map.end()) {return map[{l,r}];}
	int cost = INT_MAX;
	for(int i = l +1; i< r; i++) {
		cost = min(cost, recur(map, l, i) + recur(map, i, r));
	}
	return map[{l,r}] = cost+ cuts[r] - cuts[l];
}

int main() {
	int length;
	while(1) {
		cin >> length;
		if (!length) {return 0;}
		int n, tmp;
		cin >> n;
		cuts.clear();

		cuts.push_back(0);
		for(int i = 0; i < n; i++) {
			cin >> tmp;
			cuts.push_back(tmp);
		}
		cuts.push_back(length);
		map<pair<int,int>, int> mem;
		cout << "The minimum cutting is " << recur(mem, 0, n+1) << "." << endl;
	}

	return 0;
}