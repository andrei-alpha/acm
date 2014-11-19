#include <stdio.h>
#include <cstring>
#include <unordered_map>
#include <iostream>

#define maxdim 100005

using namespace std;

char sir[maxdim];
int change[26][maxdim];
unordered_map<int, int> len;

inline int bits(int x) {
	int r = 0;
	while (x) {
		++r;
		x &= (x-1);
	}
	return r;
}

int main() {
	
	freopen("jingles.in", "r", stdin);
	freopen("jingles.out", "w", stdout);
	
	int tests;
	scanf("%d\n", &tests);
	
	while (tests--) {
		
		scanf("%s", sir+1);
		int n = strlen(sir+1);
		
		for (int i = 1; i <= n; ++i) {
			for (int ch = 0; ch < 26; ++ch) {
				change[ch][i] = change[ch][i-1];
			}
			change[sir[i]-'a'][i] = i;
		}
		
		for (int i = 1; i <= n; ++i) {
			
			int j = i, conf = 0;
			while (j > 0) {
				
				int first_ch = 0, best_first = 0;
				for (int ch = 0; ch < 26; ++ch) {
					if (conf & (1<<ch)) {
						continue;
					}
					
					if (change[ch][j-1] >= best_first) {
						best_first = change[ch][j-1];
						first_ch = ch;
					}
				}
				
				conf |= (1<<(sir[j]-'a'));
				len[conf] = max(len[conf], i - best_first);
				
				j = best_first;
			}
		}
		
		long long sum = 0;
		for (pair<int, int> p : len) {
			sum += bits(p.first) * p.second;
		}
		printf("%d ", (int)len.size());
		cout << sum << "\n";
		
		len.clear();
	}
	
	return 0;
}
