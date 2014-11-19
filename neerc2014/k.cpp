#include <cstdio>
#include <cstring>
#include <vector>
#include <set>
using namespace std;

int n;
int c[2048][2048];
int p[2048][2048];

typedef pair<int, int> pii;

vector<pii> ed;

set<int> s[2048];

void add_edge(int a, int b)
{
	ed.push_back(make_pair(a, b));
	
	set<int> op = s[a];
	if (!s[a].size())
		op = s[b];
	s[a].clear();
	s[b].clear();
	for (set<int>::iterator it = op.begin(); it != op.end(); ++it)
	{
		int k = (*it);
		if (k == a || k == b)
			continue;
		if (p[k][a] < p[k][b])
			s[a].insert(k);
		else
			s[b].insert(k);
	}
	
	for (int i = 1; i <= n; ++i)
	{
		if (s[i].size())
		{
			int be = 0;
			for (set<int>::iterator it = s[i].begin(); it != s[i].end(); ++it)
			{
				int k = (*it);
				if (be == 0 || p[i][k] < p[i][be])
					be = k;
			}
			if (be)
				add_edge(i, be);
		}
	}
}

int main()
{
	int t, T;
	scanf("%d", &T);
	for (t = 0; t < T; ++t)
	{
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i)
		{
			for (int j = 1; j <= n; ++j)
			{
				scanf("%d", &c[i][j]);
				p[i][c[i][j]] = j;
			}
		}
		
		for (int i = 1; i <= n; ++i)
			s[i].clear();
		for (int i = 2; i <= n; ++i)
		{
			s[1].insert(i);
		}
		ed.clear();
		add_edge(c[1][1], c[1][2]);
		for (int i = 0; i < (int) ed.size(); ++i)
		{
			printf("%d %d\n", ed[i].first, ed[i].second);
		}
		printf("\n");
	}
	return 0;
}
