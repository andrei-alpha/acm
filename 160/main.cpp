using namespace std;

#include <set>
#include <map>
#include <list>
#include <deque>
#include <stack>
#include <queue>
#include <cmath>
#include <ctime>
#include <cctype>
#include <cstdio>
#include <vector>
#include <string>
#include <bitset>
#include <utility>
#include <iomanip>
#include <fstream>
#include <cstring>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <functional>

#define oo (1<<30)
#define f first
#define s second
#define II inline
#define db double
#define ll long long
#define pb push_back
#define mp make_pair
#define Size(V) ((ll)(V.size()))
#define all(V) (V).begin() , (V).end()
#define CC(V) memset((V),0,sizeof((V)))
#define CP(A,B) memcpy((A),(B),sizeof((B)))
#define FOR(i,a,b) for(int (i)=(a);(i)<=(b);++(i))
#define REP(i, N) for (int (i)=0;(i)<(int)(N);++(i))
#define FORit(it, x) for (__typeof((x).begin()) it = (x).begin(); it != (x).end(); ++it)
#define printll(x) printf("%lld",(x))
#define printsp() printf(" ")
#define newline() printf("\n")
#define readll(x) scanf("%lld",&(x))
#define debugll(x) fprintf(stderr,"%lld\n",(x))

#define IN "code.in"
#define OUT "code.out"
#define N_MAX (1<<7)

typedef vector<int> VI;
typedef pair<int,int> pi;
typedef pair<short int,short int> ps;
typedef vector<string> VS;
template<class T> string toString(T n) {ostringstream ost;ost<<n;ost.flush();return ost.str();}

int primes[N_MAX];

II void scan() {
	#ifndef ONLINE_JUDGE
		freopen(IN,"r",stdin);
		freopen(OUT,"w",stdout);
	#endif	
}

II void solve() {
	int N;

	scanf("%d\n",&N);
	if(!N)
		exit(0);

	CC(primes);
	for(int i = 2;i <= N; ++i) {
		
		int cnt, x = i;
		for(int j = 2;j * j <= x; ++j) {
			
			for(cnt = 0;!(x % j); x /= j, ++cnt);
			primes[j] += cnt;
		}
			
		if(x != 1)
			++primes[x];
	}

	printf("%3d! =", N);

	int cnt = 0;
	for(int i = 2; i <= 100; ++i) {
		if(primes[i] != 0) {
			if(cnt == 15) {
				cnt = 0;
				printf("\n      ");
			}

			++cnt;
			printf("%3d" ,primes[i]);
		}
	}

	printf("\n");
}

int main() {
	scan();

	for(;;)
		solve();
	return 0;
}

