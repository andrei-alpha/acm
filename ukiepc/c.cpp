#include <cstdio>
#include <algorithm>

using namespace std;

#define Nmax (1<<20)

int n, frec[Nmax];

int main() {
	scanf("%d", &n);
	int x;
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &x);
		++frec[x];
	}

	int res = n, rem = n;
	for (int i = 1; i <= 1000000; ++i) {
		rem -= frec[i];
		res = min(res, i + rem);
	}

	printf("%d\n", res);
	return 0;
}