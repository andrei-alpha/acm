#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

#define pb push_back
#define mp make_pair
#define Nmax 1100

int n,k;
vector<int> V[Nmax];
int St[Nmax];
int mark[Nmax], Cnt[Nmax], Cycle[Nmax];
bool make[Nmax], viz[Nmax];

void dfs(int nod, int &ind) {
	if (viz[nod])
		return;
	viz[nod] = true;
	St[++St[0]] = nod;

	for (int i = 0; i < V[nod].size(); ++i) {
		int next = V[nod][i];

		if (viz[next]) {
			if (!mark[next]) {
				// found a new cycle
				for (int i = St[0]; i >= 1; --i) {
					if (St[i] == next) {
						
						ind = ++Cnt[0];
						Cycle[ind] = St[0] - i + 1;
						break;
					}
				}
			} else {
				// found the cycle
				ind = mark[next];	
			}
		} else {
			dfs(next, ind);
		}
	}

	--St[0];
	mark[nod] = ind;
	++Cnt[ind];
}

int main() {
	scanf("%d%d", &n, &k);
	int x;
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &x);
		V[i].pb(x);
	}

	for (int i = 1; i <= n; ++i) {
		if (!viz[i]) {
			int ind = 0;
			dfs(i, ind);
		}
	}

	for (int i = 1; i <= Cnt[0]; ++i) {
		Cnt[i] -= Cycle[i];
		//printf("%d extra: %d\n", Cycle[i], Cnt[i]);
	}

	memset(viz, 0, sizeof(viz));

	viz[0] = true;
	for (int i = 1; i <= Cnt[0]; ++i) {
		for (int j = k; j >= 0; --j) {
			if (!viz[j])
				continue;

			viz[j + Cycle[i]] = true;
			for (int k = 1; k <= Cnt[i]; ++k)
				viz[j + Cycle[i] + k] = true;
		}
	}

	for (int i = k; i >= 0; --i) {
		if (viz[i]) {
			printf("%d\n", i);
			break;
		}
	}
	return 0;
}