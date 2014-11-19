#include <cstdio>
#include <cstring>

const int mod = 175781251;

long long qpow(long long v, long long st)
{
	long long r = 1;
	while (st)
	{
		if (st & 1)
		{
			r = r * v;
			if (r >= mod)
				r %= mod;
		}
		v = v * v;
		if (v >= mod)
			v %= mod;
		st = st / 2;
	}
	return r;
}

int n;

long long com[1024][1024];

long long p3[1024];

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
	FILE *fin = fopen("bipartite.in", "r");
	FILE *fout = fopen("bipartite.out", "w");
	
	memset(com, -1, sizeof(com));
	p3[0] = 1;
	for (int i = 1; i <= 1000; ++i)
	{
		p3[i] = p3[i - 1] * 3;
		if (p3[i] >= mod)
			p3[i] %= mod;
	}
	while (fscanf(fin, "%d", &n) == 1)
	{
		if (n == 0)
			break;
		
		long long ans = 0;
		for (int k = 0; k <= n; ++k)
		{
			//~ printf("OP %d\n", k);
			// size of r is k;
			long long ways = gc(n, k);
			long long sl = 1;
			if (k == 0 || k == n)
			{
				ans++;
				if (ans >= mod)
					ans %= mod;
				continue;
			}
			for (int i = 0; i < k; ++i)
			{
				//~ printf("WTF %d\n", i);
				long long p = 0;
				for (int j = 0; j < n - k; ++j)
				{
					p += p3[j] * 2LL;
					if (p >= mod)
						p %= mod;
				}
				sl *= p;
				if (sl >= mod)
					sl %= mod;
			}
			ans = ans + ways * sl;
			if (ans >= mod)
				ans %= mod;
		}
		//~ printf("AN %d %lld\n", n, ans);
		ans = ans * qpow(2, mod - 2);
		if (ans >= mod)
			ans %= mod;
		fprintf(fout, "%lld\n", ans);
	}
	
	return 0;
}
