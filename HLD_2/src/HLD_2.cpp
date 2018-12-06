#include <bits/stdc++.h>
using namespace std;

#define N 1024
typedef long long LL;
int tree[N][N];

struct treeNode {
	int par;
	int depth;
	int size;
	int pos_segbase;
	int chain;
} node[N];

struct Edge {
	int weight;
	int deeper_end;
} edge[N];

struct segTree {
	int base_array[N], tree[6*N];
} st;

// e: edge ID, u,v are nodes, w is weight.
void readEdge(int e, int u, int v, int w) {
	tree[u-1][v-1] = e-1;
	tree[v-1][u-1] = e -1;
}




int main() {

	return 0;
}
