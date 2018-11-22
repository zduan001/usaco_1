#include <bits/stdc++.h>
using namespace std;

int main() {
	int n;
	int case_num = 1;
	while(cin >> n) {
		unordered_map<string, int> map_x;
		unordered_map<int, string> reverse_map;
		vector<vector<int>> graph;
		if( n == 0) return 0;
		int index = 0;
		for (int i = 0; i < n; i++) {
			int count;
			cin >> count;
			string s;
			vector<string> ne;
			for (int j = 0; j < count; j++) {
				cin >> s;
				ne.push_back(s);
			}
			vector<int> ne_n;
			for (int j = 0; j < ne.size(); j++) {
				if (map_x.find(ne[j]) == map_x.end()) {
					map_x[ne[j]] = index;
					reverse_map[index] = ne[j];
					index++;
				}
				ne_n.push_back(map_x[ne[j]]);
			}
			graph.push_back(ne_n);
//			cout << "row size" << ne_n.size() <<endl;
//			for (int j = 0; j < ne_n.size(); j++) {
//				cout << ne_n[j] << " ";
//			}
//			cout << endl;
		}
		// construct graph;
		vector<vector<bool>> w(index, vector<bool>(index, false));

		for (auto row: graph) {

			for (int j = 0; j < row.size() -1; j ++) {
				w[row[j]][row[j+1]] = true;
//				w[row[j+1]][row[j]] = true;
//				cout << row[j] << " ";
			}
//			cout << endl;
		}

		int m;
		cin >> m;
		string s1, s2;
		for (int i = 0; i < m; i++) {
			cin >> s1 >> s2;
			w[map_x[s1]][map_x[s2]] = true;
//			w[map_x[s2]][map_x[s1]] = true;
		}

//		for (auto item : map_x) {
//			cout << item.first << "  " << item.second<<endl;
//		}
//
//		for (int i = 0; i < index; i++) {
//			for (int j = 0; j < index; j++) {
//				cout << w[i][j] << " ";
//			}
//			cout << endl;
//		}
//
//		cout << " ----------------------------------- " << endl;

		for (int k = 0; k < index; k++) {
			for (int i = 0; i < index; i ++) {
				for (int j = 0; j < index; j++) {
					if (!w[i][j]) {
						w[i][j] = w[i][k] && w[k][j];
					}
				}
			}
		}

		int count = 0;
		vector<string> sample;
		for (int i = 0; i < index; i++) {
			for (int j = i+1; j < index; j++) {
				if (!w[i][j] && !w[j][i]) {
					count ++;
					string tmp;
					tmp = "(" + reverse_map[i] + "," + reverse_map[j] + ")" + " ";
					sample.push_back(tmp);
				}
			}
		}

//		for (int i = 0; i < index; i++) {
//			for (int j = 0; j < index; j++) {
//				cout << w[i][j] << " ";
//			}
//			cout << endl;
//		}
		if (count > 0) {
			cout << "Case " << case_num << ", " << count << " concurrent events:" << endl;
			for (int i = 0; i < (int)sample.size(); i ++) {
				cout << sample[i];
				if (i == 1 || i == (int)sample.size() -1) {
//					cout << " ";
					break;
				}
			}
		} else {
			cout << "Case " << case_num << ", no concurrent events.";
		}
		cout << endl;



		case_num++;

	}
	return 0;
}
