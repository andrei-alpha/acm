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

int N;
int A[N_MAX][N_MAX], Dist[N_MAX];
bool viz[N_MAX];

II void scan() {
	#ifndef ONLINE_JUDGE
		freopen(IN,"r",stdin);
		freopen(OUT,"w",stdout);
	#endif

	scanf("%d", &N);
}

struct comp{ bool operator() (int i, int j) { return Dist[i] > Dist[j]; } };
priority_queue<int, VI, comp> Que;

II void Dijkastra(int start) {
	memset(Dist, 100, sizeof(Dist) );
	CC(viz);	

	Dist[start] = 0;
	viz[start] = true;
	Que.push(start);

	for(int nod; !Que.empty(); ) {
		nod = Que.top();
		viz[nod] = false;
		Que.pop();
		
		FOR(j, 1, N)
			if(Dist[j] > Dist[nod] + A[nod][j]) {
				Dist[j] = Dist[nod] + A[nod][j];
				
				if(!viz[j]) {
					viz[j] = true;
					Que.push(j);
				}
		}
	}
	
}

II void solve() {
	string dist;
	
	memset(A, 100, sizeof(A));	

	FOR(i, 1, N)
		A[i][i] = 0;	

	FOR(i, 1, N)
	FOR(j, 1, i - 1) {
		cin >> dist;

		if(dist == "x")
			continue;

		A[i][j] = A[j][i] = atoi( dist.c_str() );
	}

	Dijkastra(1);

	int res = -oo;
	FOR(i, 1, N)
		res = max(res, Dist[i]);

	printf("%d\n", res);
}

int main() {
	scan();
	solve();
	return 0;
}


