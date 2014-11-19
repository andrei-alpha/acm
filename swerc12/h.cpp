
#include <vector>
#include <algorithm>
#include <cstdio>

using namespace std;

#define Nmax 5050
#define mp make_pair
#define pb push_back

int c, n, p;
int sh1[Nmax], sh2[Nmax];
vector< pair<double, pair<int, int> > > V;

int main() {
	scanf("%d", &c);
	scanf("%d%d", &n, &p);

	for (int i = 1; i <= n; ++i) {
		scanf("%d %d", &sh1[i], &sh2[i]);
	}
	for (int i = 1; i <= p; ++i) {
		int x, y, z;
		int cost = 0, profit = 0;

		scanf("%d", &x);
		for (int j = 0; j < x; ++j) {
			scanf("%d%d", &y, &z);
			cost += z * sh1[y];
			//printf("use %d*%d for %d\n", z, y, sh2[y] - sh1[y]);
			profit += z * (sh2[y] - sh1[y]);
		}
		printf("%d %d\n", cost, profit);

		if (profit > 0)
			V.pb( mp((cost * 1.0) / (profit * 1.0), mp(cost, profit)) );
	}

	sort(V.begin(), V.end());

	int res = 0;

	for (int i = 0; i < V.size(); ++i) {
		if (c >= V[i].second.first) {
			res += V[i].second.second;
			c -= V[i].second.first;
		}
	}
	printf("%d\n", res);

	return 0;
}