#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

int n, m[200020], r[200020];

int main()
{
	scanf("%d", &n);
	int mw, rw;
	mw = rw = 0;
	for (int i = 0; i < n; i++)
	{
		scanf("%d %d", &m[i], &r[i]);
		if (m[i] > r[i])
		{
			++mw;
		}
		else if (r[i] > m[i])
			++rw;
	}
	
	if (mw > (double) n / 2)
	{
		printf("0\n");
		return 0;
	}
	if (mw == 0)
	{
		printf("-1\n");
		return 0;
	}
	
	int rcnt = 0;
	for (rcnt = 0; rcnt < n; ++rcnt)
	{
		if (mw > (double) (n-rcnt) / 2)
			break;
	}
	
	vector< pair<int, int> > vp;
	for (int i = 0; i + 1 < n; ++i)
	{
		int cw0 = 0;
		int cw1 = 0;
		if (m[i] > r[i])
			++cw0;
		if (m[i + 1] > r[i + 1])
			++cw0;
		if (m[i] + m[i + 1] > r[i] + r[i + 1])
			++cw1;
		if (cw0 <= cw1)
		{
			vp.push_back(make_pair(i, i + 1));
			if ((int) vp.size() == rcnt)
			{
				break;
			}
			++i;
		}
	}
	
	if ((int) vp.size() < rcnt)
	{
		printf("-1\n");
		return 0;
	}
	
	printf("%d\n", (int) vp.size());
	for (int i = 0; i < (int) vp.size(); i++)
	{
		printf("%d %d\n", vp[i].first + 1, vp[i].second + 1);
	}
	
	return 0;
}
