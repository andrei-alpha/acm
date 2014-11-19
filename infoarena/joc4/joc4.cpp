#include <cstdio>
#include <vector>
#include <cstring>

using namespace std;

#define Nmax 502
#define pb push_back

int n, m;
bool viz[Nmax];
short Cap[Nmax][Nmax], T[Nmax], Que[Nmax];
vector< vector<int> > V(Nmax);

void add_edge(int x, int y) {
	V[x + n].pb(y);
	V[y].pb(x + n);
	V[y + n].pb(x);
	V[x].pb(y + n);
	Cap[x + n][y] = 1;
	Cap[y + n][x] = 1;
}

bool bfs(int src, int dst) {
	memset(T, 0, sizeof(T));
	memset(viz, 0, sizeof(viz));

	Que[Que[0]=1] = src;
	viz[src] = true;

	for (int i = 1; i <= Que[0]; ++i) {
		int nod = Que[i];
		for (int j = 0; j < (int)V[nod].size(); ++j) {
			int next = V[nod][j];
			if (!viz[next] && Cap[nod][next]) {
				viz[next] = true;
				T[next] = nod;
				Que[++Que[0]] = next;
			}
		}
	}

	return viz[dst];
}

int flow(int src, int dst) {
	int res = 0;
	
	while (bfs(src, dst)) {
		// we know the minimum flow is always 1
		for (int x = dst; T[x]; x = T[x]) {
			Cap[T[x]][x] -= 1;
			Cap[x][T[x]] += 1;
		}
 		++res;
	}

	return res;
}

int main() {
	freopen("joc4.in", "r", stdin);
	freopen("joc4.out", "w", stdout);

	int a, b;
	scanf("%d%d%d%d", &n, &m, &a, &b);
	
	int x, y;
	for (int i = 1; i <= m; ++i) {
		scanf("%d%d", &x, &y);
		add_edge(x, y);
	}

	for (int i = 1; i <= n; ++i) {
		V[i].pb(i + n);
		Cap[i][i + n] = 1;
	}

	printf("%d\n", flow(a + n, b));
}