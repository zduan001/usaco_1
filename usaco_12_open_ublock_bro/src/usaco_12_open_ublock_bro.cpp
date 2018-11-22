#include <bits/stdc++.h>

using namespace std;
typedef pair<int,int> pii;

bool answer = false;
int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};
set<pair<pii, pii>> visited;
vector<set<pii>> blocks;
int min_x, min_y, max_x, max_y;


bool separated(set<pii> first, set<pii> second){
	int top = 20, left = 20, bottom = 0, right = 0;
	for (auto i : first) {
		top = min(top, i.first);
		left = min(left, i.second);
		bottom = max(bottom, i.first);
		right = max(right, i.second);
	}

	int top_2 = 20, left_2 = 20, bottom_2 = 0, right_2 = 0;
	for (auto i : first) {
		top_2 = min(top_2, i.first);
		left_2 = min(left_2, i.second);
		bottom_2 = max(bottom_2, i.first);
		right_2 = max(right_2, i.second);
	}

	return (max(top, top_2) > min(bottom, bottom_2) &&
			max(left, left_2) > min(right, right_2));
}

bool checkOverlap(set<pii> first, set<pii> second){
	for(auto i : second){
		if(first.find(i) != first.end()){
			return true;
		}
	}

	return false;
}

void cinEverything(int N, set<pii>& pieces){
//	int left = 0 , right = , top = 0, bottom = 20;
	for(int i = 0; i < N; i++){
		int one, two;
		cin >> one >> two;
		pieces.insert(make_pair(one, two));
		min_x = min(min_x, one);
		min_y = min(min_y, two);
		max_x = max(max_x, one);
		max_y = max(max_y, two);
	}
}

set<pair<int,int>> shift(set<pii> block, pii shift){
	set<pair<int, int>> res;

	for(auto itr : block){
		int first = itr.first + shift.first;
		int second = itr.second + shift.second;
		res.insert(make_pair(first, second));
	}
	return res;
}

void print_out() {
	int n = max_x - min_x;
	int m = max_y - min_x;
	vector<vector<char>> board(n+1, vector<char>(m+1, '.'));
	for (int i = 0; i < (int)blocks.size(); i++) {
		for (auto j : blocks[i]){
			int x = j.first - min_x;
			int y = j.second - min_y;
			board[x][y] = (char)(i + '1');
		}
	}

	for (int i = 0; i < board.size(); i++) {
		for (int j = 0; j < board.size(); j++) {
			cout << board[i][j] << " ";
		}
		cout << endl;
	}
}

void DFS(vector<set<pii>> blocks, pair<pii, pii> cur){
	cout << cur.first.first << " "
			<< cur.first.second << " "
			<< cur.second.first << " "
			<< cur.second.second << endl;
	if(answer) return;

	if (cur.first.first < -20 ||
			cur.first.second < -20 ||
			cur.first.first > 30 ||
			cur.first.second > 30 ||
			cur.second.first < -20 ||
			cur.second.second < -20 ||
			cur.second.first > 30 ||
			cur.second.second > 30) {
		return;
	}

	if(separated(blocks[0], shift(blocks[1], cur.first)) &&
			separated(blocks[0], shift(blocks[2], cur.second)) &&
			separated(shift(blocks[1], cur.first), shift(blocks[2], cur.second))){
		answer = true;
		cout << "1 : " << separated(blocks[0], shift(blocks[1], cur.first)) << endl;
		cout << "2 : " << separated(blocks[0], shift(blocks[2], cur.second)) << endl;
		cout << "3 : " << separated(shift(blocks[1], cur.first), shift(blocks[2], cur.second)) << endl;
		print_out();
		cout << " ------------------------------- " << endl;
		return;
	} else {
		if (checkOverlap(blocks[0], shift(blocks[1], cur.first)) ||
				checkOverlap(blocks[0], shift(blocks[2], cur.second)) ||
				checkOverlap(shift(blocks[1], cur.first), shift(blocks[2], cur.second))){
			return;
		}
	}

	if(visited.find(cur) != visited.end()){
		return;
	}
	visited.insert(cur);

	for(int i = 0; i < 4; i++){
		cur.first.first += dx[i];
		cur.first.second += dy[i];
		DFS(blocks, cur);
		cur.first.first -= dx[i];
		cur.first.second -= dy[i];
		cur.second.first += dx[i];
		cur.second.second += dy[i];
		DFS(blocks, cur);
		cur.second.first -= dx[i];
		cur.second.second -= dy[i];
	}
}



int main() {
	int N1, N2, N3;
	cin >> N1 >> N2 >> N3;
	set<pair<int, int>> first, second, third;

	cinEverything(N1, first);
	cinEverything(N2, second);
	cinEverything(N3, third);
	blocks = {first, second, third};
//	cout << separated(blocks[0], blocks[2]);
//	print_out();
	print_out();
	answer = false;
	DFS(blocks, {{0,0}, {0,0}});

	cout << answer << endl;

	return 0;
}
