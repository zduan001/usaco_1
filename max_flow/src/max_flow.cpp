#include <bits/stdc++.h>
#define INF 200000
#define MAX_V 20000

using namespace std;

typedef vector<int> vi;
typedef pair<int,int> pii;
vector<vi> res;
vi p;
int mf, f, s, t;

void augment(int v, int minEdge) {
	if (v == s) {
		f = minEdge;
		return;
	} else {
		if (p[v] != -1) {
			augment(p[v], min(minEdge, res[p[v]][v]));
			res[p[v]][v] -= f;
			res[v][p[v]] += f;
		}
	}
}

int main() {
	// reading in.
	int n;
	cin >> n;
	vector<pair<pii, pii>> hor;
	vector<pair<pii, pii>> ver;
	int a, b, c, d;
	for (int i = 0; i < n; i++) {
		cin >> a >> b >> c >> d;
		if (a == c) {
			ver.push_back({{a,b},{c,d}});
		} else {
			hor.push_back({{a,b},{c,d}});
		}
	}
	int total_size = ver.size() + hor.size() + 2;
	res.assign(total_size, vector<int>(total_size, 0));

	for (int i = 0; i < (int)ver.size(); i++) {
		for (int j = 0; j < (int)hor.size(); j ++) {
			int top = max(ver[i].first.second, ver[i].second.second);
			int bottom = min(ver[i].first.second, ver[i].second.second);
			int left = min(hor[j].first.first, hor[j].second.first);
			int right = max(hor[j].first.first, hor[j].second.first);
			if ((hor[j].first.second <= top && hor[j].first.second >= bottom) &&
					(ver[i].first.first <= right && ver[i].first.first >= left)){
				res[i][ver.size() + j] = 1;
			}
		}
	}

	for (int i = 0; i < (int)ver.size(); i++) {
		res[total_size - 2][i] = 1;
	}
	for (int j = 0; j < (int)hor.size(); j ++) {
		res[ver.size() + j][total_size -1] = 1;
	}

//	for (int i = 0; i < (int)ver.size(); i++) {
//		for (int j = 0; j < (int)hor.size(); j ++) {
//			int top = max(ver[i].first.second, ver[i].second.second);
//			int bottom = min(ver[i].first.second, ver[i].second.second);
//			if (hor[j].first.second <= top && hor[j].first.second >= bottom) {
//				res[ver.size() + j][i] = 1;
//			}
//		}
//	}
//
//	for (int i = 0; i < (int)hor.size(); i++) {
//		res[total_size - 2][ver.size() + i] = 1;
//	}
//	for (int j = 0; j < (int)ver.size(); j ++) {
//		res[j][total_size -1] = 1;
//	}

	mf = 0;
	s = total_size - 2;
	t = total_size - 1;
	while(1) {
		f = 0;
		vi dist(total_size, INF);
		dist[s] = 0;
		queue<int> q;
		q.push(s);
		p.assign(total_size, -1);
		while(!q.empty()) {
			int u = q.front();
			q.pop();
			if (u == t) break; // found t;
			for (int v = 0; v < total_size; v++) {
				if (res[u][v] > 0 && dist[v] == INF) {
					dist[v] = dist[u] + 1;
					q.push(v);
					p[v] = u;
				}
			}
		}
		augment(t, INF);
		if (f == 0) break;
		mf += f;
	}
	cout << n - mf<< endl;
	return 0;
}
