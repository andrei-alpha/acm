#include<iostream>
#include<stdio.h>

#define INT_MAX 2147483647

using namespace std;

int stick[53];
int dp[53][53];

int solve(int left, int right) {
	if (left + 1 == right)
		return dp[left][right] = 0;
	if (dp[left][right] != -1)
		return dp[left][right];
	int cost = 0;
	int min = INT_MAX;
	for (int cut = left + 1; cut < right; ++cut) {
		cost = solve(left, cut) + solve(cut, right) + (stick[right] - stick[left]); 
		if (cost < min)
			min = cost;
	}
	return dp[left][right] = min;
}

int main (void) {
	int stickLen, cuts;
	while (scanf("%d", &stickLen) != EOF) {
		if (stickLen == 0)
			break;
		scanf("%d", &cuts);
		stick[0] = 0;
		stick[cuts + 1] = stickLen;
		for (int i = 1; i < cuts + 1; ++i)
			scanf("%d", &stick[i]);
		int n = sizeof (stick) / sizeof (int);
		for (int i = 0; i < 53; ++i) 
			for (int j = 0; j < 53; ++j)
				dp[i][j] = -1;
		cout << "The minimum cutting is " << solve(0, n-1);
	}	
	return 0;
}
