#include <cstdio>
#include <algorithm>

using namespace std;

char line[500000];
long long v[11000];

int read(int &k) {
	for (;line[k] < '0' || line[k] > '9';++k)
		if (line[k] == '\0')
			return -1;
	int val = 0;
	bool found = false;
	for (;line[k] >= '0' && line[k] <= '9';++k) {
		val = val * 10 + line[k] - '0';
		found = true;
	}
	if (!found)
		return -1;
	return val;
}

void guess(int p1, int p2, int p3, int p4, int &a, int &b) {
	for (a = 1; a <= 1000; ++a)
	for (b = 1; b <= 1000; ++b)
		if (p3 == a * p1 + b * p2 && p4 == a * p2 + b * p3)
			return;
}

int main() {
	int d,p;

	while (scanf("%d %d", &d, &p) == 2) {
		fgets(line, 400000, stdin);

		v[0] = 0;
		int k = 0;
		while (true) {
			int x = read(k);
			if (x != -1)
				v[++v[0]] = x;
			else
				break;
		}

		if (v[1] > p) {
			printf("The spider is going to fall!\n");
			continue;
		}

		//unpredictable
		if (v[0] == d+1) {
			if (v[d+1] <= p) {
				printf("The spider may fall!\n");
				continue;
			}
			int x;
			for (x = 1;v[x + 1] <= p; ++x);
			printf("%d\n", d+1-x);
			continue;
		}

		int a,b;
		guess(v[1], v[2], v[3], v[4], a, b);

		for (;v[0] < d+1 && v[v[0]] <= p;++v[0])
			v[v[0]+1] = v[v[0]-1] * a + v[v[0]] * b;
		//printf("guess: %d %d\n", a,b);
		//for (int i = 1; i <= min(15LL, v[0]); ++i)
		//	printf("%lld ", v[i]);
		//printf("\n");

		//predictable
		if (v[v[0]] <= p) {
			printf("The spider may fall!\n");
			continue;
		}
		int x;
		for (x = 1;v[x + 1] <= p; ++x);
		printf("%d\n", d+1-x);
		continue;
	}

	return 0;
}
