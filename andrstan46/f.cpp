#include <cstdio>
#include <cstring>

const int mod = 998244353;

long long st[4][4];
long long r[4][4];

void mmult(long long a[4][4], long long b[4][4], long long c[4][4])
{
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			c[i][j] = 0;
			for (int k = 0; k < 4; ++k)
			{
				c[i][j] = c[i][j] + a[i][k] * b[k][j];
				if (c[i][j] >= mod)
					c[i][j] %= mod;
			}
		}
	}
}

void qpow(long long ste)
{
	long long t[4][4];
	memset(r, 0, sizeof(r));
	for (int i = 0; i < 4; ++i)
		r[i][i] = 1;
	
	while (ste)
	{
		if (ste & 1)
		{
			mmult(r, st, t);
			memcpy(r, t, sizeof(r));
		}
		
		mmult(st, st, t);
		memcpy(st, t, sizeof(st));
		ste = ste / 2;
	}
}

int main()
{
	FILE *fin = fopen("figure.in", "r");
	FILE *fout = fopen("figure.out", "w");
	
	int n;
	while (fscanf(fin, "%d", &n) == 1)
	{
		if (n == 0)
			break;
		memset(st, 0, sizeof(st));
		st[0][0] = 1;
		st[0][1] = 1;
		st[0][2] = 1;
		
		st[1][1] = 2;
		st[1][2] = 2;
		st[1][0] = 1;
		
		st[2][2] = 1;
		st[2][3] = 1;
		st[3][3] = 1;
		st[3][1] = 1;
		st[3][2] = 2;
		
		qpow(n);
		fprintf(fout, "%lld\n", r[0][0]);
	}
	
	return 0;
}
