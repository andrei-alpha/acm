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
typedef pair<double,double> pd;
typedef pair<short int,short int> ps;
typedef vector<string> VS;
template<class T> string toString(T n) {ostringstream ost;ost<<n;ost.flush();return ost.str();}

int N, Tests;
vector<pd> Points(N_MAX);
double Dist[N_MAX];
bool viz[N_MAX];

II void scan() {
	#ifndef ONLINE_JUDGE
		freopen(IN,"r",stdin);
		freopen(OUT,"w",stdout);
	#endif

	scanf("%d", &Tests);
}

II double dist(pd a, pd b) {
	double dist = (a.f - b.f) * (a.f - b.f) + (a.s - b.s) * (a.s - b.s);
	return sqrt(dist);
}

II void solve() {
	CC(viz);	
	
	scanf("%d", &N);
	FOR(i, 1, N)
		scanf("%lf %lf\n", &Points[i].f, &Points[i].s);
	
	double res = 0;
	viz[1] = true;
	
	FOR(i, 1, N)
		Dist[i] = dist(Points[1], Points[i]);

	FOR(i, 2, N) {
		int pos = 0;
		double best = oo;

		FOR(j, 1, N)
			if(!viz[j] && Dist[j] < best)
				best = Dist[j], pos = j;

		viz[pos] = true;
		res += Dist[pos];
	
		FOR(j, 1, N)
			Dist[j] = min(Dist[j], dist(Points[pos], Points[j]) );
	}

	printf("%.2lf\n", res);
}

int main() {
	scan();
	FOR(i, 1, Tests) {
		if(i != 1)
			printf("\n");
		solve();
	}
	return 0;
}
