#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <limits>

using namespace std;

int n;
long long required;
vector<pair<long long, int>> G[2];

struct cmp {
	inline bool operator() (const pair<long long, int> &a, const pair<long long, int> &b) {
		return a.first > b.first;
	}
};

int main() {

	#ifndef ONLINE_JUDGE
	freopen("d.in", "r", stdin);
	#endif // ONLINE_JUDGE
	
	cin >> n >> required;
	for (int i = 1; i <= n; ++i) {
		long long val; int type;
		cin >> val >> type;
		G[type].push_back(make_pair(val, i));
	}
	
	sort(G[0].begin(), G[0].end(), cmp());
	sort(G[1].begin(), G[1].end(), cmp());
	
	for (int type = 0; type < 2; ++type) {
		for (int i = 1; i < (int)G[type].size(); ++i) {
			G[type][i].first += G[type][i-1].first;
		}
	}
	
	int sol = numeric_limits<int>::max(), best_fixed = 0, rest = 0;
	for (int fixed = -1; fixed < (int)G[1].size(); ++fixed) {
		long long remaining = required - (fixed >= 0 ? G[1][fixed].first : 0);
		
		if (remaining <= 0) {
			if (fixed+1 <= sol) {
				sol = fixed+1;
				best_fixed = fixed+1;
				rest = 0;
				continue;
			}
		}
		
		auto itt = lower_bound(G[0].begin(), G[0].end(), make_pair(remaining, 0));
		if (itt != G[0].end()) {
			int in_sol = fixed + itt - G[0].begin() + 2;
			if (in_sol <= sol) {
				sol = in_sol;
				best_fixed = fixed+1;
				rest = itt - G[0].begin() + 1;
			}
		}
	}
	
	printf("%d %d\n", sol, best_fixed);
	for (int i = 0; i < best_fixed; ++i) {
		printf("%d ", G[1][i].second);
	}
	for (int i = 0; i < rest; ++i) {
		printf("%d ", G[0][i].second);
	}
	printf("\n");
	
	return 0;
}
