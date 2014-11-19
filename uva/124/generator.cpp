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

bool viz[100][100];

void generate() {

	vector<char> stack;
	memset(viz, 0, sizeof(viz));

	for(int i = 'a'; i <= 'a' + 13; ++i) {
		stack.pb(i);
		
		printf("%c ",i);
	}
	printf("\n");
	
	for(int i = 1; i <= 50; ++i) {
		int a = rand() % Size(stack);
		int b = rand() % Size(stack);
		
		if(a > b) swap(a, b);

		if(a == b || viz[a][b]) {
			--i;
			continue;
		}

		viz[a][b] = true;
		printf("%c %c ",stack[a], stack[b]);
	}
	printf("\n");
		
}

int main() {
    freopen("test.out", "w", stdout);

    for(int i = 1;i <= 10; ++i)
        generate();

    return 0;
}

