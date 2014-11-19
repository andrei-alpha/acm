#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

#define Nmax 30

bool viz[Nmax], use[Nmax];
int R[Nmax], L[Nmax];
vector< vector<int> > V(Nmax), G(Nmax);

bool pairup(int nod) {
	if (viz[nod])
		return false;
	viz[nod] = true;
	for (int i = 0;i < V[nod].size(); ++i) {
		int next = V[nod][i];
		if (!L[next] || pairup(L[next])) {
			L[next] = nod;
			R[nod] = next;
			return true;
		}
	}
	return false;
}

void dfs(int nod, bool side) {
	if (!side) {
		if (viz[nod])
			return;
		viz[nod] = true;
		for (int i = 0; i < V[nod].size(); ++i) {
			if (R[nod] != V[nod][i]) {
				dfs(V[nod][i], side ^ 1);
			}
		}
	} else {
		if (use[nod])
			return;
		use[nod] = true;
		for (int i = 0; i < G[nod].size(); ++i) {
			if (L[nod] == G[nod][i]) {
				dfs(G[nod][i], side ^ 1);
			}
		}
	}
}

int main() {
	int n, m;

	freopen("paznici.in", "r", stdin);
	freopen("paznici.out", "w", stdout);
	scanf("%d%d\n", &n, &m);
	
	char buffer[Nmax];
	for (int i = 1; i <= n; ++i) {
		fgets(buffer, Nmax, stdin);
		for (int j = 0; j < m; ++j)
			if (buffer[j] == '1') {
				V[i].push_back(j + 1);
				G[j + 1].push_back(i);
			}
	}

	for (int i = 1; i <= n; ++i)
		if (!pairup(i)) {
			memset(viz, 0, sizeof(viz));
			pairup(i);
		}
	
	memset(viz, 0, sizeof(viz));
	for (int i = 1; i <= n; ++i)
		if (!R[i])
			dfs(i, 0);

	for (int i = 1; i <= n; ++i)
		if (!viz[i])
			printf("%c", i - 1 + 'A');
	for (int i = 1; i <= m; ++i)
		if (use[i])
			printf("%c", i - 1 + 'a');
	printf("\n");

	return 0;
}