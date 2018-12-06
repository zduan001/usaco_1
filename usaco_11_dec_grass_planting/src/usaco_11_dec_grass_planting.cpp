#include <bits/stdc++.h>
using namespace std;
#define MAX_N 110000
typedef pair<int, int> pii;

vector<vector<int>> adj;
vector<unordered_map<int,int>> weight;
int parent[MAX_N], heavy[MAX_N];
int depth[MAX_N], size[MAX_N];
int chain[MAX_N], head[MAX_N];

void DFS(int u) {
	size[u] = 1;
	for (auto v : adj[u]) {
		if (v == parent[u]) continue;

		parent[v] = u;
		depth[v] = depth[u]+1;
		DFS(v);

		size[u] += size[v];
		if (heavy[u] == -1 || size[v] > size[heavy[u]]) {
			heavy[u] = v;
		}
	}
}

void heavylight_DFS(int N) {
	memset(heavy, -1, sizeof(heavy));

	parent[0] = -1;
	depth[0] = 0;
	DFS(0);

	// set the chain id for each node.
	// set head for each node.
	int c = 0;
	for (int i = 0; i < N; i++) {
		if (parent[i] == -1 || heavy[parent[i]] != i) {
			for (int k = i; k != -1; k = heavy[k]) {
				chain[k] = c;
				head[k] = i;
			}
			c++;
		}
	}
}

int lca_2(int u, int v) {
	while(chain[u] != chain[v]) {
		if (depth[head[u]] > depth[head[v]]) {
			swap(u,v);
		}
		int chainhead = parent[head[v]];
		while(v != chainhead) {
			weight[parent[v]][v]++;
			weight[v][parent[v]]++;
			v = parent[v];
		}
	}
	if (depth[u] > depth[v]) {
		swap(u, v);
	}
	while(v != u) {
		weight[u][v]++;
		weight[v][u]++;
		v = parent[v];
	}
	return u;
}

void plan(int u, int v) {
	lca_2(u, v);
}

int query(int u, int v) {
	return weight[u][v];
}

void printout(int N) {
	int i;

	printf("\n");
	printf("heavy: \n");
	printf("(i,j): i ----(heavy edge)---- j\n\n");

	for (i = 0; i < N; i++) {
		printf("(%d, %d)\n", i, heavy[i]);
	}

	printf("\n");
	printf("CHAIN: \n");
	printf("(i, j): Node i is in group (heavy-path group) number j\n\n");

	for (i = 0; i < N; i++) {
		printf("(%d, %d)\n", i, chain[i]);
	}

	printf("\n");
	printf("HEADER: \n");
	printf("(i, j): Node i goes up all the way to the highest node (j) which is in the same group\n\n");

	for (i = 0; i < N; i++)
			printf("(%d, %d)\n", i, head[i]);
}


int main() {
	freopen("grass.out", "w", stdout);
	int n, q;
	cin >> n >> q;
	adj.assign(n, vector<int>());
	weight.assign(n, unordered_map<int,int>());
	int u, v;
	for (int i = 0; i < n-1; i++) {
		cin >> u >> v;
		adj[u - 1].push_back(v - 1);
		adj[v - 1].push_back(u - 1);
	}
	heavylight_DFS(n);
//	printout(n);

	char t;
	for (int i = 0 ; i < q; i++) {
		cin >> t >> u >> v;
		if (t == 'P') {
			plan(u-1,v-1);
		} else {
			cout << query(u-1, v-1) << endl;
		}
	}

	return 0;
}
