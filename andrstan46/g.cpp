#include <cstdio>
#include <cstring>

const int mod = 242121643;
long long com[1024][1024];
long long gc(int n, int k)
{
	//~ printf("GC %d %d\n", n, k);
	if (n < 0)
		return 0;
	if (n == k || k == 0)
		return 1;
	if (com[n][k] != -1)
		return com[n][k];
	com[n][k] = gc(n - 1, k) + gc(n - 1, k - 1);
	if (com[n][k] >= mod)
		com[n][k] %= mod;
	return com[n][k];
}

int main()
{
	memset(com, -1, sizeof(com));
	FILE *fin = fopen("game.in", "r");
	FILE *fout = fopen("game.out", "w");
	
	int n, k;
	int a[1024];
	int c1 = 0;
	while (fscanf(fin, "%d %d", &n, &k) == 2)
	{
		if (n == 0)
			break;
		c1 = 0;
		for (int i = 0; i < n; ++i)
		{
			fscanf(fin, "%d", &a[i]);
			if (a[i] == 1)
				++c1;
		}
		
		int re = n - c1;
		long long sl = 0;
		//~ printf("%d %d\n", c1, re);
		for (int i = 1; i <= c1 && i <= k; i += 2)
		{
			sl += gc(c1, i) * gc(re, k - i);
			if (sl >= mod)
				sl %= mod;
		}
		fprintf(fout, "%d\n", (int) sl);
	}
	
	return 0;
}
