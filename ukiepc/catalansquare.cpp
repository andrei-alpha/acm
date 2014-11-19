#include <cstdio>
#include <cstring>
#define Nmax 5001
#define Cmax 1000
#define Base 10000

int C[Nmax][Cmax], temp[Cmax], S[Cmax];

void add(int A[], int B[])
{
      int i, t = 0;
      for (i=1; i<=A[0] || i<=B[0] || t; i++, t/=Base)
              A[i] = (t += A[i] + B[i]) % Base;
      A[0] = i - 1;
}

void mul(int A[], int B)
{
      int i, t = 0;
      for (i = 1; i <= A[0] || t; i++, t /= Base)
              A[i] = (t += A[i] * B) % Base;
      A[0] = i - 1;
}

void div(int A[], int B)
{
      int i, t = 0;
      for (i = A[0]; i > 0; i--, t %= B)
              A[i] = (t = t * Base + A[i]) / B;
      for (; A[0] > 1 && !A[A[0]]; A[0]--);
}

void mul(int A[], int B[])
{
      int i, j, t, C[Cmax];
      memset(C, 0, sizeof(C));
      for (i = 1; i <= A[0]; i++)
      {
              for (t=0, j=1; j <= B[0] || t; j++, t/=Base)
                      C[i+j-1]=(t+=C[i+j-1]+A[i]*B[j])%Base;
              if (i + j - 2 > C[0]) C[0] = i + j - 2;
      }
      memcpy(A, C, sizeof(C));
}

void print(int A[]) {
	//printf("digits: %d\n", A[0]);
	for (int i = A[0]; i >= 1; --i)
		if (i == A[0])
			printf("%d", A[i]);
		else
			printf("%04d", A[i]);
	printf("\n");
}

int main() {
	int n;
	scanf("%d", &n);

	C[0][0] = C[0][1] = C[1][0] = C[1][1] = 1;

	for (int i = 2; i <= n; ++i) {
		memcpy(C[i], C[i-1], sizeof(C[i-1]));
		mul(C[i], 2 * (2 * i - 1));
		div(C[i], i + 1);
	}

	memcpy(temp, C[n], sizeof(C[n]));
	for (int k = 0; k <= n; ++k) {
		if (k >= 2) {
			// upgrade C[k] -> C[k+1]
			mul(temp, 2 * (2 * k - 1));
			div(temp, k + 1);
		}
		if (k >= 1)	{
			//downgrade C[n-k] -> C[n-k-1]
			mul(temp, (n - k + 1) + 1);
			div(temp, 2 * (2 * (n - k + 1) - 1));
		}
		add(S, temp);
	}

	print(S);
}