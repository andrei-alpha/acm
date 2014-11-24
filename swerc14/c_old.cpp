#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <algorithm>

using namespace std;

#define Vmax 200000
#define Nmax (1<<18)

int V[Nmax], Q[Nmax], n, m;
bool has[Nmax], viz[Nmax];


int main() {
  srand((int)time(0));
  //scanf("%d%d", &n, &m);
  n = 20000;
  m = 200000;
  
  int x;
  for (int i = 1; i <= n; ++i) {
    //scanf("%d", &x);
    x = rand() % Vmax + 1;
    if (!has[x]) {
      --i;
      continue;
    }

    has[x] = true;
    V[++V[0]] = x;
  }

  memcpy(viz, has, sizeof(has));
  
  sort(V+1, V+n+1);
  // Wish me luck
  for (int i = 1; i <= 100; ++i)
    Q[++Q[0]] = V[i];
  for (int i = n / 2 - 50; i <= n / 2 + 50; ++i)
    Q[++Q[0]] = V[i];
  for (int i = n - 100; i <= n; ++i)
    Q[++Q[0]] = V[i];
  for (int i = 1; i <= 100; ++i)
    Q[++Q[0]] = V[rand() % n + 1];
  sort(Q+1, Q+Q[0]+1);

  for (int i = 1; i <= n; ++i)
  for (int j = 1; j <= Q[0]; ++j) {
    if (Q[j] + V[i] > Vmax)
      break;
    viz[ Q[j] + V[i] ] = true;
  }

  int res = 0;
  for (int i = 1; i <= m; ++i) {
    x = rand() % Vmax + 1;
    if (viz[x]) {
      ++res;
      continue;
    }

    /*for (int k1 = 1; k1 <= n; ++k1)
    for (int k2 = 1; k2 <= n; ++k2)
      if (!viz[ V[k1] + V[k2] ]) {
        printf("Incorect!!!!!!!!!!!!\n");
        return 0;
      }*/
  }

  printf("%d\n", res);
  return 0;
}
