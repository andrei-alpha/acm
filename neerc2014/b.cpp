#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

#define Nmax 1100
#define pb push_back
#define mp make_pair

int V[Nmax], F[Nmax], Ind[Nmax], rem, k, n, m;
vector< vector<int> > T(Nmax);
vector< vector< pair<int, int> > > M(Nmax);
vector< pair<int, pair<int, int> > > Rems;

void match() {
  vector< pair<int, int> > Q;

  //printf("%d\n", rem);
  for (int i = 1; i <= n; ++i)
    if (F[i]) {
      //printf("%d\n", F[i]);
      Q.pb( mp(F[i], i) );
    }
  sort(Q.begin(), Q.end());

  int next = 0;
  for (int i = Q.size() - 1; i >= 0; --i) {
    if (next >= i)
      break;

    int add = min(m - Q[i].first, Q[next].first);
    int left = m - Q[i].first - add;  
  
    Q[next].first -= add;
    M[ Q[next].second ].pb( mp(add, Q[i].second) );
    M[ Q[i].second ].pb( mp(left + add, Q[next].second) );
    Rems.pb( mp(left, mp(Q[next].second, Q[i].second) ) );   

    Q[i].first = 0;
    rem -= left;
    
    if (!Q[next].first)
      ++next;
  }

  int unpaired = 0;
  for (int i = 0; i < Q.size(); ++i) {
    if (!Q[i].first)
      continue;
    ++unpaired;
    Rems.pb( mp(m - Q[i].first, mp(1, Q[i].second) ) ); 
    rem -= m - Q[i].first; 
  }

  if (unpaired > 1)
    fprintf(stderr, "WTF WTF!");
}

int main() {
  scanf("%d%d", &k, &n);
  m = k / n;

  for (int i = 1; i <= k; ++i) {
    scanf("%d", &V[i]);
    if (V[i] != -1) {
      F[V[i]] = (F[V[i]] + 1) % m;
      T[V[i]].pb(i);
    } else
      ++rem;
  }
  
  match();
  Rems.pb( mp(Nmax, mp(1, 1) ) );
  for (int c = 1; c <= n; ++c)
    M[c].pb( mp(Nmax, 1) );

  if (rem < 0) {
    printf("No\n");
    return 0;
  }
  printf("Yes\n");
  
  for (int i = 1; i <= k; ++i) {
    int c = V[i];
    if (c == -1) {
      if (Rems[ Ind[0] ].first <= 0)
        ++Ind[0];
      printf("%d %d\n", Rems[ Ind[0] ].second.first, Rems[ Ind[0] ].second.second);
      --Rems[Ind[0]].first;
    } else {
      if (M[c][ Ind[c] ].first <= 0)
        ++Ind[c];
      printf("%d %d\n", c, M[c][ Ind[c] ].second);
      --M[c][ Ind[c] ].first;
    }
  }

  return 0;
}
