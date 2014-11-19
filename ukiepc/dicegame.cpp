#include <cstdio>
#define err 1e-7

int sum(int n) {
	return n * (n + 1) / 2;
}

int main() {
	int a1,a2,a3,a4,b1,b2,b3,b4;
	scanf("%d %d %d %d", &a1, &b1, &a2, &b2);
	scanf("%d %d %d %d", &a3, &b3, &a4, &b4);

	double sum1 = double(sum(b1) - sum(a1 - 1)) / (b1 - a1 + 1) 
		+ double(sum(b2) - sum(a2 - 1)) / (b2 - a2 + 1);
	double sum2 = double(sum(b3) - sum(a3 - 1)) / (b3 - a3 + 1)
		+ double(sum(b4) - sum(a4 - 1)) / (b4 - a4 + 1);

	if (sum1 > sum2 + 1e-7)
		printf("Gunnar\n");
	else if(sum2 > sum1 + 1e-7)
		printf("Emma\n");
	else
		printf("Tie\n");
}