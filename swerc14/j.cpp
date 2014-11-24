#include <cstdio>
#include <cstring>
#include <map>
using namespace std;

const int mod = 1000000007;
const int base = 31;
const int base2 = 100003;

int ha, wa, hb, wb;

char s[2048][2048];
char t[2048][2048];

long long hrow[2048][2048];
long long hln[2048][2048];

long long hcol[2048][2048];
long long hsl[2048][2048];

long long bpow[2048];
long long bpow2[2048];

map<long long, int> mp;

int main()
{
	bpow[0] = 1;
	for (int i = 1; i < 2040; ++i)
		bpow[i] = (bpow[i - 1] * base) % mod;
	scanf("%d %d %d %d", &ha, &wa, &hb, &wb);
	
	bpow2[0] = 1;
	for (int i = 1; i < 2040; ++i)
		bpow2[i] = (bpow2[i - 1] * base2) % mod;

	scanf("%d %d %d %d", &ha, &wa, &hb, &wb);
	for (int i = 0; i < ha; ++i)
		scanf("%s", s[i]);
	for (int i = 0; i < hb; ++i)
		scanf("%s", t[i]);
	
	for (int i = 0; i < hb; ++i)
	{
		for (int j = 0; j < wb; ++j)
		{
			if (j == 0)
				hrow[i][j] = t[i][j];
			else
				hrow[i][j] = hrow[i][j - 1] * base + t[i][j];
			if (hrow[i][j] >= mod)
				hrow[i][j] %= mod;
		}
	}
	for (int i = 0; i < hb; ++i)
	{
		for (int j = wa - 1; j < wb; ++j)
		{
			if (j > wa - 1)
			{
				long long mi = hrow[i][j - wa] * bpow[wa];
				if (mi >= mod) mi %= mod;
				hln[i][j] = hrow[i][j] - mi + mod;
				if (hln[i][j] >= mod)
					hln[i][j] %= mod;
			}
			else
				hln[i][j] = hrow[i][j];
		}
	}
	
	for (int j = wa - 1; j < wb; ++j)
	{
		for (int i = 0; i < hb; ++i)
		{
			if (i == 0)
				hcol[i][j] = hln[i][j];
			else
			{
				hcol[i][j] = hcol[i - 1][j] * base2 + hln[i][j];
				if (hcol[i][j] >= mod)
					hcol[i][j] %= mod;
			}
		}
	}
	for (int j = wa - 1; j < wb; ++j)
	{
		for (int i = ha - 1; i < hb; ++i)
		{
			if (i > ha - 1)
			{
				long long mi = hcol[i - ha][j] * bpow2[ha];
				if (mi >= mod)
					mi %= mod;
				hsl[i][j] = hcol[i][j] - mi + mod;
				if (hsl[i][j] >= mod)
					hsl[i][j] %= mod;
				mp[hsl[i][j]]++;
			}
			else
			{
				hsl[i][j] = hcol[i][j];
				mp[hsl[i][j]]++;
			}
		}
	}
	
	// end!


	for (int i = 0; i < ha; ++i)
	{
		for (int j = 0; j < wa; ++j)
		{
			if (j == 0)
				hrow[i][j] = s[i][j];
			else
				hrow[i][j] = hrow[i][j - 1] * base + s[i][j];
			if (hrow[i][j] >= mod)
				hrow[i][j] %= mod;
		}
	}
	for (int i = 0; i < ha; ++i)
	{
		for (int j = wa - 1; j < wa; ++j)
		{
			if (j > wa - 1)
			{
				long long mi = hrow[i][j - wa] * bpow[wa];
				if (mi >= mod) mi %= mod;
				hln[i][j] = hrow[i][j] - mi + mod;
				if (hln[i][j] >= mod)
					hln[i][j] %= mod;
			}
			else
				hln[i][j] = hrow[i][j];
		}
	}
	
	for (int j = wa - 1; j < wa; ++j)
	{
		for (int i = 0; i < ha; ++i)
		{
			if (i == 0)
				hcol[i][j] = hln[i][j];
			else
			{
				hcol[i][j] = hcol[i - 1][j] * base2 + hln[i][j];
				if (hcol[i][j] >= mod)
					hcol[i][j] %= mod;
			}
		}
	}
	int ans = 0;
	for (int j = wa - 1; j < wa; ++j)
	{
		for (int i = ha - 1; i < ha; ++i)
		{
			if (i > ha - 1)
			{
				long long mi = hcol[i - ha][j] * bpow2[ha];
				if (mi >= mod)
					mi %= mod;
				hsl[i][j] = hcol[i][j] - mi + mod;
				if (hsl[i][j] >= mod)
					hsl[i][j] %= mod;
			}
			else
				hsl[i][j] = hcol[i][j];
			//~ printf("POST %d %d %lld __ %lld\n", i, j, hsl[i][j], hcol[i][j]);
			ans = mp[hsl[i][j]];
		}
	}
	
	printf("%d\n", ans);
	return 0;
}
