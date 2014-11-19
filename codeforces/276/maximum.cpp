#include <algorithm>
#include <cstdio>

using namespace std;

#define Nmax (1<<21)

int n;
bool viz[Nmax];
int V[Nmax], nextSmall[Nmax];

int main() {
  scanf("%d", &n);
  int x;
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &x);
    V[i] = x;
    viz[x] = true;
  }
/*
  int bestx = 0;
  for (int i = 1; i <= n; ++i)
  for (int j = i + 1; j <= n; ++j)
    if (V[i] > V[j])
      bestx = max(bestx, V[i] % V[j]);
  fprintf(stderr, "sol=%d\n", bestx);
*/
  for (int i = 1; i <= 2000000; ++i)
    nextSmall[i] = (viz[i] ? i : nextSmall[i - 1]);
  
  int best = 0;
  for (int i = 1000000; i >= max(best, 1); --i) {
    if (!viz[i])
      continue;
    
    for (int j = i * 2; j - i <= 1000000; j += i) {
      int rem = nextSmall[j - 1] - (j - i);
      if (rem <= 0)
        continue;
      //printf("match %d with %d\n", i, nextSmall[j - 1]);
      best = max(best, rem);
    }
  }
  printf("%d\n", best);

  return 0;
}
  
