#include<iostream>
#include<stdio.h>
using namespace std;

int main (void) {
	int MAX = 7490;
	long ways[MAX];
	int coins[] = {1, 5, 10, 25, 50};
	int n;
	ways[0] = 1;
	int size = sizeof(coins) / sizeof(int);
	for (int i = 0; i < size; ++i) {
		for (int j = coins[i]; j < MAX; ++j) {
			if (j - coins[i] >= 0)
				ways[j] += ways[j - coins[i]];
		}
	}
	while(scanf("%d", &n) != EOF) {
		cout << ways[n];
	}
	return 0;
}
