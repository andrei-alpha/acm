#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

struct vert
{
	int x, y;
};

int n[2];
vector<vert> v[2];

int main()
{
	for (int p = 0; p < 2; ++p)
	{
		scanf("%d", &n[p]);
		v[p].resize(n[p]);
		for (int i = 0; i < n[p]; ++i)
		{
			scanf("%d %d", &v[p][i].x, &v[p][i].y);
		}
		
		bool ch = 1;
		while (ch)
		{
			ch = 0;
			for (int i = 0; i <= 4000; ++i)
			{
				int cnt = 0;
				for (int j = 0; j < (int) v[p].size(); ++j)
				{
					if (v[p][j].x == i)
					{
						++cnt;
					}
				}
				if (cnt == 0)
				{
					for (int j = 0; j < (int) v[p].size(); ++j)
					{
						if (v[p][j].x > i)
						{
							ch = 1;
							--v[p][j].x;
						}
					}
				}
				if (cnt > 2)
				{
					printf("no\n");
					return 0;
				}
			}

			for (int i = 0; i <= 4000; ++i)
			{
				int cnt = 0;
				for (int j = 0; j < (int) v[p].size(); ++j)
				{
					if (v[p][j].y == i)
					{
						++cnt;
					}
				}
				if (cnt == 0)
				{
					for (int j = 0; j < (int) v[p].size(); ++j)
					{
						if (v[p][j].y > i)
						{
							ch = 1;
							--v[p][j].y;
						}
					}
				}
				if (cnt > 2)
				{
					printf("no\n");
					return 0;
				}
			}
		}
	}
	
	if (v[0].size() != v[1].size())
	{
		printf("no\n");
		return 0;
	}
	//~ printf("GOT HERE!\n");
	//~ for (int i = 0; i < (int) v[0].size(); ++i)
	//~ {
		//~ printf("%d %d\n", v[0][i].x, v[0][i].y);
	//~ }
	//~ printf("\n\n");
	//~ for (int i = 0; i < (int) v[1].size(); ++i)
	//~ {
		//~ printf("%d %d\n", v[1][i].x, v[1][i].y);
	//~ }
	for (int r= 0; r < 4; ++r)
	{
		for (int s = 0; s < (int) v[0].size(); ++s)
		{
			bool ok = true;
			for (int i = 0; i < (int) v[1].size() && ok; ++i)
			{
				int j = (s + i) % v[1].size();
				if (v[1][i].x != v[0][j].x || v[1][i].y != v[0][j].y)
				{
					ok = false;
				}
			}
			if (ok)
			{
				printf("yes\n");
				return 0;
			}
		}
		// rot(v[0]);
		int m = ((int) v[0].size() / 2) - 1;
		for (int i = 0; i < (int) v[0].size(); ++i)
		{
			int nx = v[0][i].y;
			int ny = m - v[0][i].x;
			v[0][i].x = nx;
			v[0][i].y = ny;
		}
	}
	
	printf("no\n");
	return 0;
}
