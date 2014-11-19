#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

int n, s, dt;

int fin = -1;
int par[200020];
long long ti[200020];
int d[200020], l[200020], h[200020];

struct el
{
	el() {}
	el(long long s, long long t, long long o)
	{
		sk = s;
		ti = t;
		ow = o;
	}
	long long sk, ti, ow;
	bool operator<(const el& e) const
	{
		if (sk != e.sk)
			return sk < e.sk;
		return ti > e.ti;
	}
};

vector<el> vp[21];

int main()
{
	scanf("%d %d %d", &n, &s, &dt);
	for (int i = 0; i < n; i++)
	{
		scanf("%d %d %d", &d[i], &l[i], &h[i]);
	}
	
	fin = -1;
	for (int cd = 0, i = 0; cd <= 1000025; ++cd)
	{
		// start from cd, cd + 1, cd + 2, ..., cd + 20
		vector<el> ne;
		while (i < n && d[i] == cd)
		{
			// calc
			ti[i] = (1LL << 60);
			if (s >= l[i])
			{
				ti[i] = 0;
				par[i] = fin;
			}
			else
			{
				for (int j = 0; j < 21; ++j)
				{
					vector<el>::iterator ps = lower_bound(vp[(cd + j)%21].begin(), vp[(cd+j)%21].end(), el(l[i], 1LL << 60, -1));
					if (ps != vp[(cd+j)%21].end())
					{
						//~ printf("FOUND %d %d :: %d [%d] %d %d\n", i, j, ps->sk, l[i], ps->ti, ps->ow);
						if ( ((ps->ti) >> (20-j)) < ti[i])
						{
							ti[i] = min(ti[i], (ps->ti) >> (20-j));
							par[i] = ps->ow;
						}
					}
				}
			}
			ne.push_back(el(h[i] - ti[i], ti[i] + dt, i));
			//~ printf("II %d %d %d\n", i, ti[i], h[i] - ti[i]);
			++i;
		}
		int ni = (cd) % 21;
		if (vp[ni].size() && vp[ni][ vp[ni].size() - 1].sk > s)
		{
			s = vp[ni][ vp[ni].size() - 1].sk;
			fin = vp[ni][ vp[ni].size() - 1].ow;
		}
		vp[ni].clear();
		sort(ne.begin(), ne.end());
		for (int j = (int) ne.size() - 1; j >= 0; --j)
		{
			if (!vp[ni].size() || vp[ni].back().ti > ne[j].ti)
				vp[ni].push_back(ne[j]);
		}
		sort(vp[ni].begin(), vp[ni].end());
	}
	
	printf("%d ", s);
	vector<int> ans;
	while (fin != -1)
	{
		ans.push_back(fin);
		fin = par[fin];
	}
	printf("%d\n", (int) ans.size());
	for (int i = ans.size() - 1; i > 0; --i)
		printf("%d ", ans[i] + 1);
	if (ans.size())
		printf("%d\n", ans[0] + 1);
	
	return 0;
}
