#include <cstdio>
#include <cstring>
#include <vector>
#include <bitset>
#include <queue>
#include <map>

using namespace std;

#define Nmax 1010
#define Rmax 122
#define Tmax 100100
#define pb push_back
#define mp make_pair

typedef pair<int, int> state;

vector< vector< pair<int, int> > > V(Nmax);
bool viz[Nmax];
int Best[Nmax], C[Nmax][Nmax], oldC[Nmax][Nmax];
long long D[Rmax][Rmax];
bitset<(1<<14)> inQue;
int oldS[Nmax], S[Nmax];

int tests, c, d, n, m, s, t;

struct comp{
  bool operator() (int x, int y) { return Best[x] > Best[y]; }
};

struct comp2{ 
  bool operator() (state x, state y) { return D[x.first][x.second] > D[y.first][y.second]; }
};
priority_queue<int, vector<int>, comp> Que; 
priority_queue<state, vector<state>, comp2> Que2;

int nodes = 0;

inline int hash_state(pair<int, int> state) {
  int x = (state.first << 7) + state.second;
}

void dijkastra(int src, int dest) {
  D[src][src] = 0;
  Que2.push( mp(src, src) );
  inQue[ hash_state( mp(src, src) ) ] = true;
  nodes = 0;
  
  long long res = 1<<30;
  for (;!Que2.empty();) {
    state st = Que2.top();
    int nod = st.first;
    int last = st.second;
    Que2.pop();
    inQue[ hash_state(st) ] = false;

    if (nod == dest) {
      res = min(res, D[nod][last]);
      continue;
    }

    //fprintf(stderr, "state# nod=%d last=%d total=%lld\n", nod, last, D[nod][last]);

    for (int i = 0; i < V[nod].size(); ++i) {
      int next = V[nod][i].first;
      int cost = V[nod][i].second;
      
      if (S[nod] == -1)
        continue;

      long long price = 0;
      int rem = cost;  

      if (S[last] < S[nod]) {
        price += min(t - C[last][nod], cost) * S[last];
        rem -= min(t - C[last][nod], cost);
        price += 1LL * rem * S[nod]; 
      } else {
        price += 1LL * rem * S[nod];
      }
      
      state newSt = mp(next, nod);
      
      //fprintf(stderr, ": nod=%d price=%lld cost=%d total=%lld\n", next, price, cost, D[next][nod]); 
      // We always refuel in the transformed complete graph
      if (D[next][nod] == -1 || D[next][nod] > D[nod][last] + price) {
        D[next][nod] = D[nod][last] + price;

        if (!inQue[ hash_state(newSt) ]) {
          inQue[ hash_state(newSt) ] = true;
          Que2.push(newSt);
        }
      }      
    }
  }

  //fprintf(stderr, "res=%lld\n", res);
  printf("%lld\n", res);
}

void dijkastra_init(int src) {
  memset(Best, 100, sizeof(Best));
  Best[src] = 0;
  Que.push(src);
  viz[src] = true;

  for (;!Que.empty();) {
    int nod = Que.top();
    Que.pop();
    viz[nod] = false;

    for (int i = 0; i < V[nod].size(); ++i) {
      int next = V[nod][i].first;
      int cost = V[nod][i].second;

      if (Best[next] > Best[nod] + cost) {
        Best[next] = Best[nod] + cost;
        
        if (!viz[next]) {
          viz[next] = true;
          Que.push(next);  
        }
      }
    }
  }
  
  memcpy(C[src], Best, sizeof(Best));
}

int main() {
  scanf("%d", &tests);

  for(;tests--;) {
    scanf("%d%d%d", &n, &m, &s);
    scanf("%d", &t);
    //fprintf(stderr, "n=%d m=%d s=%d t=%d\n", n, m, s, t);
    
    V.clear();
    V.resize(n + 2);
    memset(S, -1, sizeof(S));
    memset(D, -1, sizeof(D));
    memset(C, 100, sizeof(C));

    int a, b, f;
    for (int i = 1; i <= m; ++i) {
      scanf("%d %d %d", &a, &b, &f);
  
      V[a].pb( mp(b, f) );
      V[b].pb( mp(a, f) );
    }
  
    int x, p;
    for (int i = 1; i <= s; ++i) {
      scanf("%d %d", &x, &p);
      S[x] = p;
      dijkastra_init(i);
    }
    scanf("%d %d", &c, &d);
    dijkastra_init(d);
    S[d] = 0;

    int nextId = 0;
    map<int, int> NodeMap;
  
    for (int i = 1; i <= n; ++i) {
      if (S[i] == -1)
        continue;

      NodeMap[i] = nextId++;
    }
    memcpy(oldS, S, sizeof(S));
    memset(S, -1, sizeof(S));
    for (int i = 1; i <= n; ++i)
      if (oldS[i] != -1)
        S[ NodeMap[i] ] = oldS[i];

    memcpy(oldC, C, sizeof(C));
    memset(C, -1, sizeof(C));
    for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= n; ++j)  
      if (oldS[i] != -1 && oldS[j] != -1)
        C[ NodeMap[i] ][ NodeMap[j] ] = oldC[i][j];
        
    V.clear();
    V.resize(n + 2);

    for (int i = 0; i <= s; ++i) {
      for (int j = i + 1; j <= s; ++j) {
        if (C[i][j] <= t) {
          //fprintf(stderr, "add edge %d %d %d\n", i, j, C[i][j]);

          V[i].pb( mp(j, C[i][j]) );
          V[j].pb( mp(i, C[i][j]) );  
        }
      }
    }

    //fprintf(stderr, "rem test %d...\n", tests);
    dijkastra( NodeMap[c], NodeMap[d] );
  }
}
