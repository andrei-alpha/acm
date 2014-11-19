#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

#define nmax (1<<16)
#define pb push_back
#define mp make_pair

int n,m,e;
int L[nmax], R[nmax];
bool viz[nmax];
vector< vector<int> > V(nmax);

bool dfs(int nod) {
	if (viz[nod])
		return false;
	viz[nod] = true;

	for (int i = 0; i < V[nod].size(); ++i)
		if (!L[ V[nod][i] ]) {
			L[ V[nod][i] ] = nod;
			R[nod] = V[nod][i];
			return true;
		}
	for (int i = 0; i < V[nod].size(); ++i)
		if (dfs(L[V[nod][i]])) {
			L[ V[nod][i] ] = nod;
			R[nod] = V[nod][i];
			return true;
		}
	return false;
}

int main() {
	freopen("cuplaj.in", "r", stdin);
	freopen("cuplaj.out", "w", stdout);

	scanf("%d%d%d", &n, &m, &e);

	int x, y;
	for (int i = 1; i <= e; ++i) {
		scanf("%d%d", &x, &y);
		V[x].pb(y);
	}

	bool ok = true;
	int res = 0;

	while(ok) {
		ok = false;
		memset(viz, 0, sizeof(viz));
		for (int i = 1; i <= n; ++i)
			if (!R[i] && dfs(i)) {
				 ok = true;
				 ++res;
			}
	}

	printf ("%d\n", res);
	for (int i = 1; i <= n; ++i)
		if (R[i]) {
			printf("%d %d\n", i, R[i]);
		}
	return 0;
}
