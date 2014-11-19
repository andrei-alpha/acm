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
#include <tr1/unordered_map> 

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
#define H_MAX (1<<20)
#define Mod 637013

typedef vector<int> VI;
typedef pair<int,int> pi;
typedef pair<short int,short int> ps;
typedef vector<string> VS;
template<class T> string toString(T n) {ostringstream ost;ost<<n;ost.flush();return ost.str();}

tr1::unordered_map<string, int> C;
bool viz[H_MAX];

II void scan() {
	#ifndef ONLINE_JUDGE
		freopen(IN, "r", stdin);
		freopen(OUT, "w", stdout);
	#endif	
}

II int get_hash(string word) {
	int res = 0;
	FORit(it, word)
		res = (res * 29 + *it - 'a') % Mod;
	return res;
}

II void solve() {
	string word;	
	int res = 1;

	while( cin >> word && Size(word) ) {
		int best = 1;		

		//changing
		for(int i = 0; i < Size(word); ++i) {
			string last = word;
			
			for(int ch = 'a'; ch < word[i]; ++ch) {
				last[i] = ch;

				if( !viz[ get_hash(last) ] )
					continue;

				if(C.find(last) != C.end())
					best = max(best, C[last] + 1);

				last[i] = word[i];
			}
		}	

		//adding
		for(int i = 0; i <= Size(word); ++i) {
			char step = (i < Size(word) ? word[i] - 1 : 'z');
			string last = word.substr(0, i);
			last.pb('a');
			last += (i < Size(word) ? word.substr(i, Size(word) - i) : "");
	
			for(int ch = 'a'; ch <= step; ++ch) {
				last[i] = ch;
		
				//cout << last << " from " << word << "\n";
				if( !viz[ get_hash(last) ])
					continue;

				if(C.find(last) != C.end())
					best = max(best, C[last] + 1);
			} 
		}

		//delete 
		for(int i = 0; i < Size(word); ++i) {
			string last = "";
			last += (i != 0 ? word.substr(0, i)  : "");
			last += (i != Size(word) - 1 ? word.substr(i + 1, Size(word) - i) : "");

			//cout << last << " from " << word << "\n";
			if( !viz[ get_hash(last) ])
				continue;

			if(C.find(last) != C.end())
				best = max(best, C[last] + 1);
		}

		C[word] = best;
		viz[ get_hash(word) ] = true;
		res = max(res, best);
	}

	printf("%d\n", res);
}

int main() {
	scan();
	solve();
	return 0;
}

