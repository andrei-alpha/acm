#include<iostream>
using namespace std;

int main (void) {
	int nr;
	cin >> nr;
	for (int i = 1; i <= nr; ++i) {
		int a, b, sum = 0;
		cin >> a >> b;
		for (int j = a; j <= b; ++j) {
			if (j % 2 == 1)
				sum += j;
		}
		cout << "Case " << i << ": " << sum << endl;
	}
	return 0;
}
