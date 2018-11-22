#include <bits/stdc++.h>
using namespace std;

int main() {
	freopen("paint.in", "r", stdin);
	freopen("paint.out", "w", stdout);
	int n, k;
	cin >> n >> k;
	int cur = 0;
	int l;
	char d;
	vector<pair<int,int>> intervals;
	for (int i = 0; i< n; i++) {
		cin >> l >> d;
		int end = d == 'R' ? cur + l : cur -l;
		intervals.push_back({min(cur, end), max(cur, end)});
		cur = end;
	}
	sort(intervals.begin(), intervals.end());

//	for (auto i : intervals) {
//		cout << i.first << "  " << i.second;
//		cout << endl;
//	}
//	cout << endl;
	multiset<int> backlog;
	int start = 0, top, res = 0;
	for (auto inter : intervals) {
		if (backlog.empty()) {
			backlog.insert(inter.second);
			if (backlog.size() == k) {
				start = inter.first;
			}
			continue;
		}

		while(*backlog.begin() < inter.first) {
			int top = *backlog.begin();
			backlog.erase(backlog.begin());
			if (backlog.size() == k -1) {
				res += (top - start);
//				cout << "res : " << res << endl;
//				break;
			}
		}

		backlog.insert(inter.second);
		if (backlog.size()== k ) {
			start = inter.first;
		}
	}

	while(backlog.size() >= k) {
		top = *backlog.begin();
		backlog.erase(backlog.begin());
		if (backlog.size() == k -1) {
			res += (top - start);
		}
	}

	cout << res << endl;

	return 0;
}