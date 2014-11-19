#include <cstdio>
#include <algorithm>

using namespace std;

#define Nmax 200100

int n;
int A[Nmax], B[Nmax], V1[Nmax], V2[Nmax], pi[Nmax];

inline int mod(int x) {
	if (x < 0)
		x += 360000;
	return x;
}

void make_prefix(int A[])
{
    int q = 0;
    pi[1] = 0;
    for (int i = 2; i <= n; ++i)
    {
        while (q && A[q+1] != A[i])
            q = pi[q];
        if (A[q+1] == A[i])
            ++q;
        pi[i] = q;
    }
}

bool comp(int A[], int B[]) {
	make_prefix(A);
	int q = 0;
	for (int i = 1; i <= n + n; ++i)
    {       
        while (q && A[q+1] != B[i > n ? i - n : i])
            q = pi[q];
        if (A[q+1] == B[i > n ? i - n : i])
            ++q;
        if (q == n)
        	return true; 
    }
	return false;
}

void print(int A[]) {
	//printf("digits: %d\n", A[0]);
	for (int i = 1; i <= n; ++i)
		printf("%d ", A[i]);
	printf("\n");
}

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i)
		scanf("%d", &V1[i]);
	for (int i = 1; i <= n; ++i)
		scanf("%d", &V2[i]);

	sort(V1+1,V1+n+1);
	sort(V2+1,V2+n+1);

	for (int i = 1; i <= n; ++i) {
		A[i] = (i == 1 ? mod(V1[1] - V1[n]) : V1[i] - V1[i-1]);
		B[i] = (i == 1 ? mod(V2[1] - V2[n]) : V2[i] - V2[i-1]);
	}

	if (comp(A, B))
		printf("possible\n");
	else
		printf("impossible\n");
	return 0;
}