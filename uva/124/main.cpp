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
typedef pair<char, char> pc;
typedef pair<short int,short int> ps;
typedef vector<string> VS;
template<class T> string toString(T n) {ostringstream ost;ost<<n;ost.flush();return ost.str();}

vector<pc> Cons;
string Vars, Stack;
vector< vector<char> > First;
char buffer[N_MAX];
int cnt, pos[N_MAX];

II void scan() {
	#ifndef ONLINE_JUDGE
		freopen(IN, "r", stdin);
		freopen(OUT, "w", stdout);
	#endif	
}

II void back(int step) { 
	if(step == Size(Vars) ) {
		++cnt;
		cout << Stack << "\n";
	}

	FORit(it, Vars) 
		if(pos[*it] == -1) {
			pos[*it] = step;
			
			bool ok = true;
	
			FORit(it2, First[*it])
				if(pos[*it2] != -1) {
					ok = false;
					break;
				}

			if(ok) {
				Stack.pb(*it);
				back(step + 1);
				Stack.resize( Size(Stack) - 1 );
			}

			pos[*it] = -1;
		}
	
}


II void solve() {
	Vars.resize(0);	
	Cons.resize(0);
	First.resize(N_MAX);
	FOR(i, 'a', 'z')
		First[i].resize(0);

	memset(pos, -1, sizeof(pos) );

	if( fgets(buffer, N_MAX, stdin) == 0)
		exit(0);

	for(int i = 0;i < strlen(buffer); ++i)
		if(buffer[i] >= 'a' && buffer[i] <= 'z')
			Vars.pb( buffer[i] );

	if( fgets(buffer, N_MAX, stdin) == 0)
		exit(0);
	for(int i = 0;i < strlen(buffer); ++i)
		if(buffer[i] >= 'a' && buffer[i] <= 'z') {
			Cons.pb( mp(buffer[i], buffer[i + 2]) );
			First[ buffer[i] ].pb(buffer[i + 2]); 
			i += 2;
		}

	if( Size(Vars) < 2 || Size(Cons) < 1)
		exit(0);

	sort( all(Vars) );

	if(cnt)
		printf("\n"); 	

	cnt = 0;
	back(0);
}

int main() {
	scan();
	for(;;) 
		solve();
	return 0;
}

