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
#define N_MAX (1<<10)
#define K_MAX 300

typedef vector<int> VI;
typedef pair<int,int> pi;
typedef pair<short int,short int> ps;
typedef vector<string> VS;
template<class T> string toString(T n) {ostringstream ost;ost<<n;ost.flush();return ost.str();}

const int N = 300;
char buffer[N_MAX];
ll Dp[N_MAX][N_MAX], Sum[N_MAX][N_MAX];

II void scan() {
	#ifndef ONLINE_JUDGE
		freopen(IN, "r", stdin);
		freopen(OUT, "w", stdout);
	#endif
}

II void compute() {
	Dp[0][0] = 1;
	Sum[0][0] = 1;

	FOR(k, 1, K_MAX)
	FOR(i, 0, N - k)
	FOR(j, 0, i) {
		if(!Dp[i][j])
			continue;

		Dp[i + k][j + 1] += Dp[i][j];
	}
	
	FOR(i, 0, N)
	FOR(j, 1, N) {
		Sum[i][j] = Sum[i][j - 1] + Dp[i][j];
	}
}

II int parse_int(char buffer[], int &ind) {
	int res = 0;
	bool ok = false;

	for(;buffer[ind] != '\0' && (buffer[ind] < '0' || buffer[ind] > '9'); ++ind);
	for(;buffer[ind] >= '0' && buffer[ind] <= '9'; ++ind) {
		ok = true;
		res = res * 10 + buffer[ind] - '0';
	}
	
	return ok ? res : -1;
}

II void solve() {
	if( fgets(buffer, N_MAX, stdin) == 0)
		exit(0);
	
	VI param;
	
	for(int ind = 0;;) {
		int x = parse_int(buffer, ind);
		if(x == -1)
			break;
		param.pb(x);
	}

	switch( Size(param) ) {
		case 1: { 
			printf("%lld\n", Sum[ param[0] ][N]); 
			break; 
		}
		case 2: { 
			int rigth = param[1] > 300 ? 300 : param[1];
			printf("%lld\n", Sum[ param[0] ][ rigth ]); 
			break;
		}
		case 3: {
			int rigth = param[2] > 300 ? 300 : param[2];			

			if(param[1] > 300)
				printf("0\n");
			else if(param[1] == 0)
				printf("%lld\n", Sum[ param[0] ][ rigth ]);
			else
				printf("%lld\n", Sum[ param[0] ][ rigth ] - Sum[ param[0] ][ param[1] - 1 ]);
			break;
		}
		default: { 
			exit(0);
		}
	}
}

int main() {
	scan();
	compute();
	for(;;) 
		solve();
	return 0;
}

