#include<iostream>
#include<stdio.h>
using namespace std;

int main (void) {
	char c;
	while (scanf("%c", &c) != EOF) {
		if (c == '\n')
			printf("\n");
		else
			printf("%c", c - 7);
	}
	return 0;
}
