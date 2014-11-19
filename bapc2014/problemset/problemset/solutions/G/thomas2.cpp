// Solution to Growling Gears
// Author: Thomas Beuman

// Time complexity: O(n*log(a+b))
// Memory: O(1)

// @EXPECTED_RESULTS@: CORRECT

// Solution method: ternary search

#include <cstdio>
using namespace std;

int a, b, c;

double eps = 0.1;

double T (double R)
{	return -a*R*R + b*R + c;
}

int main()
{	int runs, run, n, i, best;
	double lb, ub, R1, R2, Tmax;
	scanf("%d", &runs);
	for (run = 0; run < runs; run++)
	{	scanf("%d", &n);
		best = 0;
		Tmax = 0;
		for (i = 1; i <= n; i++)
		{	scanf("%d %d %d", &a, &b, &c);
			lb = 0;
			// Exponential search
			for (ub = 1; T(ub) > T(lb); ub *= 2);
			// Ternary search
			while (true)
			{	R1 = (2*lb+ub)/3;
				R2 = (lb+2*ub)/3;
				if (T(R1) - T(lb) < eps) // Close enough
					break;
				if (T(R1) > T(R2))
					ub = R2;
				else
					lb = R1;
			}
			if (T(lb) > Tmax)
			{	Tmax = T(lb);
				best = i;
			}
		}
		printf("%d\n", best);
	}
	return 0;
}
