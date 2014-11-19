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

typedef vector<int> VI;
typedef pair<int,int> pi;
typedef pair<short int,short int> ps;
typedef vector<string> VS;
template<class T> string toString(T n) {ostringstream ost;ost<<n;ost.flush();return ost.str();}

int N, M, Tests;
int C[N_MAX][N_MAX], A[N_MAX][N_MAX];
vector< vector<pi> > Pos(N_MAX);

const int xx[] = {-1, 0, 1, 0};
const int yy[] = {0, -1, 0, 1};

II void scan() {
	#ifndef ONLINE_JUDGE
		freopen(IN, "r", stdin);
		freopen(OUT, "w", stdout);
	#endif

	scanf("%d\n", &Tests);
}

II bool ok(int x, int y) {
	if(x < 1 || x > N)
		return false;
	if(y < 1 || y > M)
		return false;
	return true;
}

II void solve() {
	string name;

	cin >> name;
	scanf("%d %d", &N, &M);
	
	FOR(i, 0, 100)
		Pos[i].resize(0);

	FOR(i, 1, N)
	FOR(j, 1, M) {
		scanf("%d", &A[i][j]);

		Pos[ A[i][j] ].pb( mp(i, j) );
	}
	
	int res = 0;

	FOR(k, 0, 100) 
	FORit(it, Pos[k]) {
		int i = it->f;
		int j = it->s;

		C[i][j] = 1;

		REP(h, 4) 
			if( ok(i + xx[h], j + yy[h]) && A[i + xx[h]][j + yy[h]] < A[i][j]) {
				C[i][j] = max(C[i][j], C[i + xx[h]][j + yy[h]] + 1);
			}

		res = max(res, C[i][j]);
	}

	cout << name;
	printf(": %d\n", res);
}

int main() {
	scan();
	FOR(i, 1, Tests)
		solve();
	return 0;
}
