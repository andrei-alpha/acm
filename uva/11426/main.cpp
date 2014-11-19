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
#define N_MAX 4000004
#define K_MAX (1<<22)

typedef vector<int> VI;
typedef pair<int,int> pi;
typedef pair<short int,short int> ps;
typedef vector<string> VS;
template<class T> string toString(T n) {ostringstream ost;ost<<n;ost.flush();return ost.str();}

ll sum[K_MAX],dp[K_MAX];
int primes[K_MAX],phi[K_MAX];
bool viz[K_MAX];

II void scan() {
	#ifndef ONLINE_JUDGE
		freopen(IN,"r",stdin);
		freopen(OUT,"w",stdout);
	#endif
}

II void totient(int N) {
	//computes the euler totien function for numbers less than N
		
	phi[1] = 1;

	for(int i = 2; i <= N; ++i) {
		if(viz[i])
			continue;

		primes[++primes[0]] = i;
		phi[i] = i - 1;		

		for(int j = i + i; j <= N; j += i) {
			viz[j] = true;
			
			if( j % (i * i) == 0)
				phi[j] = phi[j / i] * i;
			else
				phi[j] = phi[i] * phi[j / i];
		}
	}
}

II void compute(int N) {

	for(int i = 1; i <= N; ++i) {
		
		int cnt = 1;
		for(int j = i; j <= N; ++cnt, j += i)
			dp[j] += 1LL * i * phi[cnt];
		dp[i] -= i; //we want up to n - 1
	}

	for(int i = 1; i <= N; ++i)
		sum[i] = sum[i - 1] + dp[i];
}

II void solve() {
	int N;
	
	scanf("%d\n",&N);
	
	if(!N)
		exit(0);
	printf("%lld\n", sum[N]);	
}

int main() {
	scan();
	totient(N_MAX);
	compute(N_MAX);
	
	for(;;)
		solve();
	return 0;
}
