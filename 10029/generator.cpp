using namespace std;

#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <string>
#include <algorithm>
#include <vector>

vector<string> V;

int main() {

	freopen("code.out", "w", stdout);
	
	for(int i = 1; i <= 25000; ++i) {
		string word;

		for(int j = 1;j <= 16; ++j)
			word.push_back( rand() % 26 + 'a' );
		V.push_back( word );
	}

	sort(V.begin(), V.end());

	for(int i = 0;i < 25000; ++i)
		cout << V[i] << "\n";
	return 0;
}
	
