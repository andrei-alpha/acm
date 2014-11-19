#include <stdio.h>
#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

char sir[105];
vector<vector<char>> scopes;
vector<pair<int, int>> place[30];

int main() {

	#ifndef ONLINE_JUDGE
	freopen("m.in", "r", stdin);
	#endif // ONLINE_JUDGE
	
	int lines;
	scanf("%d\n", &lines);
	
	vector<char> aux;
	scopes.push_back(aux);
	for (int i = 1; i <= lines; ++i) {
		fgets(sir+1, 100, stdin);
		
		int len = strlen(sir+1);
		for (int j = 1; j <= len; ++j) {
			if (sir[j] == '{') {
				scopes.push_back(aux);
			}
			if (sir[j] >= 'a' && sir[j] <= 'z') {
				int ind = sir[j] - 'a';
				if (!place[ind].empty()) {
					printf("%d:%d: warning: shadowed declaration of %c, the shadowed position is %d:%d\n", i, j, sir[j], place[ind].back().first, place[ind].back().second);
				}
				place[ind].push_back(make_pair(i, j));
				scopes.back().push_back(ind);
			}
			if (sir[j] == '}') {
				for (int ind : scopes.back()) {
					place[ind].pop_back();
				}
				scopes.pop_back();
			}
		}
	}

	return 0;
}
