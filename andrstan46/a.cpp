#include <cstdio>
#include <cstring>
#include <map>
#include <algorithm>
using namespace std;

struct el
{
	long long a, b, c;
	bool operator<(const el& e) const
	{
		if (a != e.a)
			return a < e.a;
		if (b != e.b)
			return b < e.b;
		return c < e.c;
	}
};

int n;
map<el, int> cnt;

long long x[3020], y[3020];

long long di(long long x, long long y)
{
	return x * x + y * y;
}

int main()
{
	FILE *fin = fopen("astronomy.in", "r");
	FILE *fout = fopen("astronomy.out", "w");
	
	while (fscanf(fin, "%d", &n) == 1)
	{
		//~ printf("%d\n", n);
		if (n == 0)
			break;
		cnt.clear();
		for (int i = 0; i < n; ++i)
		{
			fscanf(fin, "%lld %lld", &x[i], &y[i]);
		}
		
		for (int i = 0; i < n; ++i)
		{
			for (int j = i + 1; j < n; ++j)
			{
				el e;
				long long xx = x[j] - x[i];
				long long yy = y[j] - y[i];
				e.a = di(x[i], y[i]);
				e.b = di(x[j], y[j]);
				e.c = di(xx, yy);
				if (e.a > e.b)
					swap(e.a, e.b);
				cnt[e]++;
			}
		}
		
		int q = 0;
		fscanf(fin, "%d", &q);
		for (int i = 0; i < q; i++)
		{
			el e;
			fscanf(fin, "%lld %lld %lld", &e.a, &e.b, &e.c);
			if (e.a > e.b)
				swap(e.a, e.b);
			fprintf(fout, "%d\n", cnt[e]);
		}
		
	}
	
	return 0;
}
