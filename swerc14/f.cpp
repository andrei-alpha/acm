#include <cstdio>
#include <cstring>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

struct stone
{
	int x, y, w, h;
};

struct el
{
	int beg, end, id;
	bool operator<(const el& e) const
	{
		return beg < e.beg;
	}
};

int n;
stone st[50020];

// [beg/end][x/y] [coord]
//
map<int, vector<el> > mp[2][2];

vector<int> g[50020];

void add_ed(const vector<el> &a, const vector<el> &b)
{
	int i = 0;
	int j = 0;
	while (i < (int) a.size() && j < (int) b.size())
	{
		while (i < (int) a.size() && a[i].end < b[j].beg)
		{
			++i;
		}
		while (j < (int) b.size() && b[j].end < a[i].beg)
		{
			++j;
		}
		if (i < (int) a.size() && j < (int) b.size() && a[i].beg >= b[j].beg && a[i].beg <= b[j].end)
		{
			g[ a[i].id ].push_back(b[j].id);
			g[ b[j].id ].push_back(a[i].id);
		}
		else if (i < (int) a.size() && j < (int) b.size() && b[j].beg >= a[i].beg && b[j].beg <= a[i].end)
		{
			g[ a[i].id ].push_back(b[j].id);
			g[ b[j].id ].push_back(a[i].id);
		}
		if (i < (int) a.size() && j < (int) b.size() && a[i].end <= b[j].end)
		{
			++i;
		}
		else
		{
			++j;
		}
	}
}

bool us[50020];

long long dfs(int v)
{
	if (us[v])
		return 0;
	us[v] = 1;
	//~ printf("SM %d\n", v);
	long long sm = (long long) st[v].w * st[v].h;
	for (int i = 0; i < (int) g[v].size(); ++i)
	{
		//~ printf("ED %d %d\n", v, g[v][i]);
		sm += dfs(g[v][i]);
	}
	return sm;
}

int main()
{
	scanf("%d", &n);
	for (int i = 0; i < n; ++i)
	{
		scanf("%d %d %d %d", &st[i].x, &st[i].y, &st[i].w, &st[i].h);
		
		el ex;
		ex.beg = st[i].x;
		ex.end = st[i].x + st[i].w;  // pop at end.
		ex.id = i;
		mp[0][1][st[i].y].push_back(ex);
		mp[1][1][st[i].y + st[i].h].push_back(ex);
		
		el ey;
		ey.beg = st[i].y;
		ey.end = st[i].y + st[i].h;
		ey.id = i;
		mp[0][0][st[i].x].push_back(ey);
		mp[1][0][st[i].x + st[i].w].push_back(ey);
	}
	
	for (int i = 0; i < 2; ++i)
	{
		for (int j = 0; j < 2; ++j)
		{
			for (map<int, vector<el> >::iterator it = mp[i][j].begin(); it != mp[i][j].end(); ++it)
			{
				sort(it->second.begin(), it->second.end());
			}
		}
	}
	
	for (int i = 0; i < 1; ++i)  // fake
	{
		for (int j = 0; j < 2; ++j)
		{
			for (map<int, vector<el> >::iterator it = mp[i][j].begin(); it != mp[i][j].end(); ++it)
			{
				if (mp[1-i][j][it->first].size())
				{
					add_ed(mp[i][j][it->first], mp[1-i][j][it->first]);
				}
			}
		}
	}
	
	long long mx = 0;
	memset(us, 0, sizeof(us));
	for (int i = 0; i < n; ++i)
	{
		long long k;
		mx = max(mx, (k=dfs(i)));
		//~ printf("WTF %d %lld\n", i, k);
	}
	
	printf("%lld\n", mx);
	
	return 0;
}
