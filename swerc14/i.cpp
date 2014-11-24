#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int k;
int nums[512];
char ops[512];

bool c[512][512][2];
long long v[512][512][2];

long long getDP(int l, int r, int t);

long long op(char o, int l, int r, int k, int t)
{
	if (o == '+')
	{
		if (t)
		{
			long long bsol = -(1LL << 62);
			for (int i = 0; i < 2; ++i)
			{
				for (int j = 0; j < 2; ++j)
				{
					bsol = max(bsol, getDP(l, k, i) + getDP(k + 1, r, j));
				}
			}
			return bsol;
		}
		else
		{
			long long bsol = (1LL << 62);
			for (int i = 0; i < 2; ++i)
			{
				for (int j = 0; j < 2; ++j)
				{
					bsol = min(bsol, getDP(l, k, i) + getDP(k + 1, r, j));
				}
			}
			return bsol;
		}
	}
	if (o == '-')
	{
		if (t)
		{
			long long bsol = -(1LL << 62);
			for (int i = 0; i < 2; ++i)
			{
				for (int j = 0; j < 2; ++j)
				{
					bsol = max(bsol, getDP(l, k, i) - getDP(k + 1, r, j));
				}
			}
			return bsol;
		}
		else
		{
			long long bsol = (1LL << 62);
			for (int i = 0; i < 2; ++i)
			{
				for (int j = 0; j < 2; ++j)
				{
					bsol = min(bsol, getDP(l, k, i) - getDP(k + 1, r, j));
				}
			}
			return bsol;
		}
	}
	if (o == '*')
	{
		if (t)
		{
			long long bsol = -(1LL << 62);
			for (int i = 0; i < 2; ++i)
			{
				for (int j = 0; j < 2; ++j)
				{
					bsol = max(bsol, getDP(l, k, i) * getDP(k + 1, r, j));
				}
			}
			return bsol;
		}
		else
		{
			long long bsol = (1LL << 62);
			for (int i = 0; i < 2; ++i)
			{
				for (int j = 0; j < 2; ++j)
				{
					bsol = min(bsol, getDP(l, k, i) * getDP(k + 1, r, j));
				}
			}
			return bsol;
		}
	}
	return 0;
}

long long getDP(int l, int r, int t)
{
	if (l == r)
	{
		return nums[l];
	}
	if (c[l][r][t])
		return v[l][r][t];
	
	long long bsol;
	if (t)  // max
		bsol = -(1LL << 62);
	else  // min
		bsol = (1LL << 62);
	for (int k = l; k < r; ++k)
	{
		if (ops[k] != '?')
		{
			if (t)
			{
				bsol = max(bsol, op(ops[k], l, r, k, t));
			}
			else
			{
				bsol = min(bsol, op(ops[k], l, r, k, t));
			}
		}
		else if (ops[k] == '?')
		{
			if (t)
			{
				bsol = max(bsol, op('+', l, r, k, t));
				bsol = max(bsol, op('-', l, r, k, t));
				bsol = max(bsol, op('*', l, r, k, t));
			}
			else
			{
				bsol = min(bsol, op('+', l, r, k, t));
				bsol = min(bsol, op('-', l, r, k, t));
				bsol = min(bsol, op('*', l, r, k, t));
			}
		}
	}
	c[l][r][t] = 1;
	v[l][r][t] = bsol;
	return bsol;
}

long long ia(long long x)
{
	if (x < 0) return -x;
	return x;
}

int main()
{
	char buf[512];
	scanf("%d", &k);
	for (int i = 0; i < k; ++i)
	{
		scanf("%d", &nums[i]);
		nums[k + i] = nums[i];
		scanf("%s", buf);
		ops[i] = ops[k + i] = buf[0];
	}
	
	memset(c, 0, sizeof(c));
	//~ for (int i = 0; i < 2 * k; ++i)
	//~ {
		//~ printf("%d %c ", nums[i], ops[i]);
	//~ }
	//~ printf("\n");
	
	for (int i = 0; i < k; ++i)
	{
		printf("%lld%lld", ia(getDP(i, i + k - 1, 0)), ia(getDP(i, i + k - 1, 1)));
		//~ printf("%d %d\n", nums[i], nums[i + k]);
	}
	printf("\n");
}
