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

typedef vector<int> VI;
typedef pair<int,int> pi;
typedef pair<short int,short int> ps;
typedef vector<string> VS;
template<class T> string toString(T n) {ostringstream ost;ost<<n;ost.flush();return ost.str();}

const int x = 23;
const int y = 28;
const int z = 33;

II void scan() {
	#ifndef ONLINE_JUDGE
		freopen(IN,"r",stdin);
		freopen(OUT,"w",stdout);
	#endif
}

II void solve(int test) {
	int a,b,c,day;

	scanf("%d%d%d%d",&a,&b,&c,&day);
	
	if(a == -1)
		exit(0);

	for(;a > 0 || b > 0 || c > 0;) {
		a -= x;
		b -= y;
		c -= z;
	}

	for(;a != b || b != c || a <= day;) {
		if(a <= b && a <= c)
			a += x;
		else if(b <= a && b <= c)
			b += y;
		else
			c += z;
	}
	
	printf("Case %d: the next triple peak occurs in %d days.\n", test, a - day);
}

int main() {
	scan();
	for(int i = 1;;++i)
		solve(i);
	return 0;
}

