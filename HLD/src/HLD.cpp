#include <bits/stdc++.h>
using namespace std;

// followed : https://apps.topcoder.com/forums/?module=Thread&threadID=796128&start=0&mc=8
// TODO: there is no update() and query() implemented.
// TODO: sounds like segmented tree is needed too.

const int V = 100000;
vector<int> adj[V];
int parent[V], heavy[V];
int depth[V], size[V];
int chain[V], head[V];

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


int q[V], *qf, *qb;	// BFS queue

void heavylight_BFS(int N) {
	qf = qb = q;
	parent[0] = -1;
	depth[0] = 0;
	*qb++ = 0;
	while(qf < qb) {
		for (int i = *qf++, k = 0; k < adj[i].size(); k++) {
			int j = adj[i][k];
			if (j == parent[i]) continue;
			parent[j] = depth[i] + 1;
			*qb++ = j;
		}
	}

	memset(size, 0, sizeof(size));
	memset(heavy, 0, sizeof(heavy));

	for(int k = N-1; k > 0; k--) {
		int j = q[k], i = parent[q[k]];
		size[j]++;
		size[i] += size[j];
		if (heavy[i] == -i || size[j] > size[heavy[i]]) {
			heavy[i] = j;
		}
	}

	int tmp = 0;
	for (int i = 0; i < N; i++) {
		if (parent[i] = -1 || heavy[parent[i]] != i) {
			for (int k = i; k != -1; k = heavy[k]) {
				chain[k] = tmp;
				head[k] = i;
			}
			tmp++;
		}
	}
}

int lca_1(int u, int v) {
	while(chain[u] != chain[v]) {
		if (depth[head[u]] > depth[head[v]]) {
			u = parent[head[u]];
		} else {
			v = parent[head[v]];
		}
	}
	return depth[u] < depth[v] ? u : v;
}

int lca_2(int u, int v) {
	while(chain[u] != chain[v]) {
		if (depth[head[u]] > depth[head[v]]) {
			swap(u,v);
		}
		v = parent[head[v]];
	}
	if (depth[u] > depth[v]) {
		swap(u, v);
	}
	return u;
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
	int N, i, j;
	cin >> N;
	for (int k = 0; k < N; k++) {
		cin >> i >> j;
		adj[i-1].push_back(j-1);
		adj[j-1].push_back(i-1);
	}

	heavylight_DFS(N+1);

//	printout(N+1);

	printf("%d\n", lca_1(8, 4));
	printf("%d\n", lca_1(8, 7));

	return 0;
}
