#include <stdio.h>
#include <vector>
#include <cstring>

using namespace std;

int n, sol;
char N[30][30];
int ch[30], used[30], x[30];
long long val[30];

void back(int niv) {
	
	if (niv == ch[0] + 1) {
		
		for (int i = 1; i <= n; ++i) {
			if (x[N[i][1] - 'A'] == 0) {
				return;
			}
		}
		
		long long s = 0;
		for (int i = 1; i <= n; ++i) {
			val[i] = 0;
			int len = strlen(N[i]+1);
			for (int j = 1; j <= len; ++j) {
				val[i] = val[i] * 10 + x[N[i][j]-'A'];
			}
			if (i != n) {
				s += val[i];
			}
		}
		
		if (s == val[n]) {
			++sol;
		}
			
		return ;
	}
	
	for (int d = 0; d < 10; ++d) {
		if (!used[d]) {
			used[d] = 1;
			x[ch[niv]] = d;
			back(niv+1);
			used[d] = 0;
			x[ch[niv]] = 0;
		}
	}
}

int main() {

	//freopen("a.in", "r", stdin);
	
	scanf("%d\n", &n);
	
	vector<int> fr(26, 0);
	for (int i = 1; i <= n; ++i) {
		scanf("%s", N[i]+1);
		int len = strlen(N[i]+1);
		for (int j = 1; j <= len; ++j) {
			++fr[N[i][j]-'A'];
		}
	}
	
	for (int i = 0; i < 26; ++i) {
		if (fr[i] > 0) {
			ch[++ch[0]] = i;
		}
	}
	
	back(1);
	
	printf("%d\n", sol);

	return 0;
}
