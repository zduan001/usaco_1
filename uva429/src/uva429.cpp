#include <bits/stdc++.h>
using namespace std;

bool diffByOne(string a, string b) {
	if (a.size() != b.size()) return false;
	int count = 0;
	for (int i = 0; i< (int)a.size(); i++) {
		if (a[i] != b[i]) {
			count ++;
		}
	}
	return count == 1;
}

int findDistance(
		unordered_map<string, vector<string>> graph,
		string s,
		string e) {

	queue<string> q;
	q.push(s);
	q.push("");
	int length = 0;
	unordered_set<string> visited;
	while(!q.empty()) {
		string tmp = q.front();
		visited.insert(tmp);
		q.pop();
		if (tmp == e) {break;}
		if (tmp == "") {
			if (q.empty()) {return -1;}
			q.push("");
			length++;
		}
		for(auto s : graph[tmp]) {
			if (visited.find(s) != visited.end()) {continue;}
			q.push(s);
		}
	}
	return length;
}

int main() {
	int n;
	cin >> n;
	for (int x = 0; x < n; x++) {
		vector<string> words;
		string tmp;
		string stop = "*";
		while(cin >> tmp) {
			if (tmp == stop) break;
			words.push_back(tmp);
		}

//		for(auto s : words) {
//			cout << s << " ";
//		}
//		cout << endl;

		unordered_map<string, vector<string>> graph;
		for(int j = 0; j < (int)words.size(); j++) {
			for (int k = j+1; k < (int)words.size(); k++) {
				if (diffByOne(words[k], words[j])) {
					graph[words[j]].push_back(words[k]);
					graph[words[k]].push_back(words[j]);
				}
			}
		}

//		for(auto i : graph) {
//			cout << i.first << "  " << i.second.size() << endl;
//		}

		string start, end;
		string line;
		cin.ignore();
		while(1)
		{
			getline(cin, line);
			if (line.size() == 0) break;
			istringstream iss(line);
			iss >> start >> end;
			cout <<start << " " << end << " " << findDistance(graph, start, end)<<endl;
		}
		cout << endl;
	}

	return 0;
}
