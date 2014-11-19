#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

#define Nmax 2100
#define pb push_back
#define mp make_pair 

bool viz[Nmax];
int d1[Nmax][Nmax], d2[Nmax][Nmax];
int t[Nmax], cnt[Nmax];

vector< pair<int, pair<int, int> > > V;
vector< vector< pair<int, int> > > edges(Nmax);

int rep(int x) {
  if (t[x] == x)
    return x;
  return t[x] = rep(t[x]);
}

void add(int x, int y) {
  if (cnt[x] > cnt[y]) {
    cnt[x] += cnt[y];
    t[y] = x;
  } else {
    cnt[y] += cnt[x];
    t[x] = y;
  }
}

void dfs(int nod, int source, int dist) {
  if (viz[nod])
    return;
  viz[nod] = true;
  d2[source][nod] = d2[nod][source] = dist;

  for (int i = 0; i < edges[nod].size(); ++i) {
    dfs(edges[nod][i].first, source, dist + edges[nod][i].second);
  }
}

int main() {
  int n;
  bool ok = true;
  scanf("%d", &n);

  for (int i = 1; i <= n; ++i)
  for (int j = 1; j <= n; ++j) {
    scanf("%d", &d1[i][j]);
    if (i != j)
      V.pb( mp(d1[i][j], mp(i, j)));
  }

  sort(V.begin(), V.end());

  for (int i = 1; i <= n; ++i)
    cnt[i] = 1, t[i] = i;

  for (int i = 0; i < V.size(); ++i) {
    int x = V[i].second.first;
    int y = V[i].second.second;
    
    // We cannot have an zero edge
    if (!V[i].first)
      ok = false;

    if (rep(x) != rep(y)) {
      add(rep(x), rep(y));
      edges[x].pb( mp(y, V[i].first) );
      edges[y].pb( mp(x, V[i].first) );
    }
  }

  for (int i = 1; i <= n; ++i) {
    memset(viz, 0, sizeof(viz));
    dfs(i, i, 0);
  }
  
  for (int i = 1; i <= n; ++i)
  for (int j = 1; j <= n; ++j)
    if (d1[i][j] != d2[i][j])
      ok = false;
  
  if (ok)
    printf ("YES\n");
  else
    printf("NO\n");
  
  return 0;
}


  
