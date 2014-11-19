#include<iostream>
#include<fstream>
#include<sstream>
#include<stdio.h>
#include<string.h>
#include<string>
#include<algorithm>
#include<iterator>
#include<vector>
using namespace std;

void dfs(bool vis[], int u, int matrix[][3]) {
	int size = sizeof(matrix[u]) / sizeof(int);
	for (int i = 0; i < size; ++i) {
		if (!vis[i] && matrix[u][i] == 1) {
			vis[i] = true;
			dfs(vis, i, matrix);
		}
	}
}

int main (void) {
	while (true) {
		int nodes;
		cin >> nodes;
		if (nodes == 0)
			break;
		int matrix[3][3];
		for (int i = 0; i < nodes; ++i)
			for (int j = 0; j < nodes; ++j)
				matrix[i][j] = 0;
		vector<int> row (nodes, nodes + nodes);
		vector<int> col (nodes, nodes + nodes);
		row.resize(nodes);
		col.resize(nodes);
		cout << "row ";
		for (vector<int>::iterator it = row.begin(); it != row.end(); ++it)
			cout << (*it);
		while (true) {
			int from;
			cin >> from;
			if (from == 0)
				break;
			while (true) {
				int to;
				cin >> to;
				if (to == 0)
					break;
				matrix[from - 1][to - 1] = 1;
			}
		}
		int n;
		cin >> n;
		bool vis[nodes];
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < nodes; ++j) 
				vis[j] = false;
			int startNode;
			cin >> startNode;
			startNode -= 1;
			dfs(vis, startNode, matrix);
			int cnt = 0;
			vector<int> res;
			int sizeMatrix = sizeof(matrix[startNode]) / sizeof(int);
			for (int node = 0; node < sizeMatrix; ++node) 
				if (!vis[node]) {
					++cnt;
					res.push_back(node + 1);
				}
			cout << cnt;
			for (vector<int>::iterator it = res.begin(); it != res.end(); ++it) 
				cout << " " << (*it);
			cout << endl;
		}
		break;
	}
	return 0;
}

