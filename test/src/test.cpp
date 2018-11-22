#include <bits/stdc++.h>

using namespace std;
vector<int> parent;
map<int, vector<pair<int, int>>> graph;
map<pair<int, int>, int> weights;

vector<int> Dijkstra(int T){
	priority_queue<pair<int, int>> pq;
	vector<int> distance (T, 1076000);
	parent.clear();

	for(int i = 0; i < T; i++){
		parent.push_back(i);
	}

	pq.push(make_pair(0, 0));
	distance[0] = 0;

	while(!pq.empty()){
		pair<int, int> front = pq.top();
		pq.pop();

		if(front.first * -1 > distance[front.second]) continue;

		for(auto n : graph[front.second]){
			if(distance[front.second] + n.second < distance[n.first]){
				distance[n.first] = distance[front.second] + n.second;
				pq.push(make_pair(distance[n.first] * -1, n.first));
				parent[n.first] = front.second;

//				for(int i = 0; i < (int) parent.size(); i++){
//					cout << parent[i] << " ";
//				}
//
//				cout << endl;
			}
		}
	}

	return distance;
}

int findIndex(int u, int v){
	int weight;

	for(int i = 0; i < (int) graph[u].size(); i++){
		if(graph[u][i].first == v){
			weight = graph[u][i].second;
		}
	}
	return weight;
}

pair<int, int> thing(int N){
	int maximum = 0;
	int i = N - 1;
	int u, v;

	while(i != parent[i]){
		int weight = findIndex(parent[i], i);

		if(weight > maximum){
			maximum = weight;
			u = parent[i];
			v = i;
		}

		i = parent[i];
	}

	return make_pair(u, v);
}

void changeWeight(pair<int, int> ii){
	for(int i = 0; i < (int) graph[ii.first].size(); i++){
		if(graph[ii.first][i].first == ii.second){
			graph[ii.first][i].second *= 2;
//			cout << ii.first << " " << ii.second << " " << graph[ii.first][i].second << endl;
			return;
		}
	}
}

int main() {
	int N, M;
	cin >> N >> M;

	for(int i = 0; i < N;  i++){
		graph.insert(make_pair(i, vector<pair<int, int>> ()));
	}

	for(int i = 0; i < M; i++){
		int start, end, weight;
		cin >> start >> end >> weight;
		graph[start - 1].push_back(make_pair(end - 1, weight));
		graph[end - 1].push_back(make_pair(start - 1, weight));
		weights.insert(make_pair(make_pair(start - 1, end - 1), weight));
	}

	auto first = Dijkstra(N);
	auto ii = thing(N);
	changeWeight(ii);
	auto second = Dijkstra(N);

	cout << second[N - 1] - first[N - 1] << endl;

	return 0;
}
