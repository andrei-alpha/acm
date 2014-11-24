#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

#define mp make_pair
#define pb push_back
#define Nmax (1<<14)

vector< pair<int, pair<int, int> > > Edges;
vector< vector< pair<int, int> > > A;

int n, m;
bool viz[Nmax];
int Dist[Nmax], Dstart[Nmax], Dend[Nmax];

struct comp{ bool operator() (int i, int j) { return Dist[i] > Dist[j];} };
priority_queue<int, vector<int>, comp> Q;

void Dijkastra(int start) {
  memset(Dist, 90, sizeof(Dist));
  memset(viz, 0, sizeof(viz));

  Dist[start] = 0;
  viz[start] = true;
  Q.push(start);

  for(;!Q.empty();) {
    int nod = Q.top();
    Q.pop();
    viz[nod] = false;

    for (int j = 0; j < A[nod].size(); ++j) {
      int next = A[nod][j].first;
      int dist = A[nod][j].second;

      if (Dist[next] > Dist[nod] + dist) {
        Dist[next] = Dist[nod] + dist;

        if (!viz[next]) {
          viz[next] = true;
          Q.push(next);
        }
      }
    }
  }

  if (start == 0)
    memcpy(Dstart, Dist, sizeof(Dist));
  else
    memcpy(Dend, Dist, sizeof(Dist));
}

int main() {
  scanf("%d%d", &n, &m);
  A.resize(Nmax);

  int x, y, d;
  for (int i = 1; i <= m; ++i) {
    scanf("%d%d%d", &x, &y, &d);
    Edges.pb( mp(x, mp(y, d) ) );
    A[x].pb( mp(y, d) );
    A[y].pb( mp(x, d) );
  }

  Dijkastra(0);
  Dijkastra(n-1);

  int best = Dstart[n-1];
  int res = 0;

  for (int i = 0; i < m; ++i) {
    int x = Edges[i].first;
    int y = Edges[i].second.first;
    int d = Edges[i].second.second;

    if (Dstart[x] + d + Dend[y] == best || Dstart[y] + d + Dend[x] == best)
      res += d;
  }

  printf("%d\n", 2 * res);

  return 0;
}
