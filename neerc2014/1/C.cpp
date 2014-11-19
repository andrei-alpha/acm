#include <stdio.h>
#include <vector>
#include <unordered_map>
#include <cstring>
#include <string>
#include <algorithm>
#include <iostream>

#define maxdim 300005

using namespace std;

int n;
char sir[105];
int height[maxdim], chain[maxdim], chains, position[maxdim], father_of_chain[maxdim];
vector<int> G[maxdim], nodes[maxdim];
vector<pair<unsigned long long, string>> P[maxdim];
unordered_map<unsigned long long, vector<pair<int, string>>> M[maxdim];

void dfs(int nod) {
	
	height[nod] = 1; int heaviest = 0;
	for (int son : G[nod]) {
		dfs(son);
		height[nod] += height[son];
		if (height[son] > height[heaviest]) {
			heaviest = son;
		}
		father_of_chain[chain[son]] = nod;
	}
	
	if (!heaviest) {
		chain[nod] = ++chains;
	} else {
		chain[nod] = chain[heaviest];
	}
	nodes[chain[nod]].push_back(nod);
}

int main() {

	#ifndef ONLINE_JUDGE
	freopen("c.in", "r", stdin);
	#endif // ONLINE_JUDGE
	
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		int t, prop;
		scanf("%d %d", &t, &prop);
		G[t].push_back(i);
		while (prop--) {
			
			unsigned long long h = 0;
			scanf("%s", sir+1); int len = strlen(sir+1);
			int j;
			for (j = 1; j <= len && sir[j] != '='; ++j) {
				h = h * 257 + sir[j];
			}
			j += 1;
			
			string value;
			while (j <= len) {
				value.push_back(sir[j]);
				++j;
			}
			
			P[i].push_back(make_pair(h, value));
		}
	}
	
	dfs(1);
	father_of_chain[chain[1]] = 0;
	
	for (int i = 1; i <= chains; ++i) {
		reverse(nodes[i].begin(), nodes[i].end());
		for (int j = 0; j < (int)nodes[i].size(); ++j) {
			position[nodes[i][j]] = j+1;
		}
		for (int j = 0; j < (int)nodes[i].size(); ++j) {
			for (auto &p : P[nodes[i][j]]) {
				M[i][p.first].push_back(make_pair(j+1, p.second));
			}
		}
	}
	
	int queries;
	scanf("%d", &queries);
	while (queries--) {
		int nod; string k;
		cin >> nod >> k;
		
		unsigned long long h = 0;
		for (int i = 0; i < (int)k.size(); ++i) {
			h = h * 257 + k[i];
		}
		
		string sol = string("N/A");
		while (nod > 0) {
			
			int poz = position[nod];
			if (M[chain[nod]].find(h) == M[chain[nod]].end()) {
				nod = father_of_chain[chain[nod]];
				continue;
			}
			
			vector<pair<int, string>> &V = M[chain[nod]][h];
			vector<pair<int, string>>::iterator it = lower_bound(V.begin(), V.end(), make_pair(poz+1, string()));
			if (it != V.begin()) {
				--it;
				sol = it->second;
				break;
			}
			
			nod = father_of_chain[chain[nod]];
		}
		
		cout << sol << "\n";
		cout.flush();
	}

	return 0;
}
