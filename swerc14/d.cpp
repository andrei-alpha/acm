#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

int n, m;
vector<int> to[10020];
int from[10020];
bool us[10020];

bool augment(int v)
{
	//~ printf("AU %d _ %d\n", v, (int) to[v].size());
	if (us[v])
		return false;
	us[v] = 1;
	for (int i = 0; i < (int) to[v].size(); ++i)
	{
		//~ printf("ED %d %d\n", v, to[v][i]);
		if (from[ to[v][i] ] == -1)
		{
			from[ to[v][i] ] = v;
			return true;
		}
		if (augment(from[ to[v][i] ]))
		{
			from[ to[v][i] ] = v;
			return true;
		}
	}
	return false;
}

int max_match()
{
	memset(from, -1, sizeof(from));
	int ma = 0;
	for (int i = 0; i < n; ++i)
	{
		memset(us, 0, sizeof(us));
		if (augment(i))
		{
			++ma;
		}
	}
	return ma;
}

int main()
{
	scanf("%d %d", &n, &m);
	for (int i = 0; i < m; ++i)
	{
		int a, b;
		scanf("%d %d", &a, &b);
		if (a != b)
		{
			//~ printf("AD ED %d %d\n", a, b);
			to[a].push_back(b);
			//~ printf("ED %d %d\n", a, (int) to[a].size());
		}
	}
	
	//~ for (int i = 0 ;i < n; ++i)
		//~ printf("AA %d %d\n", i, (int) to[i].size());
	
	if (max_match() == n)
	{
		printf("YES\n");
	}
	else
		printf("NO\n");
	return 0;
}
