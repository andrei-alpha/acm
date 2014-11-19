#include <cstdio>
#include <algorithm>

using namespace std;

int f[2010];

int main() {
  int n,k;
  scanf("%d%d", &k, &n);

  int x;
  for (int i = 1; i <= k; ++i) {
    scanf("%d\n", &x);
    ++f[x];
  }

  int res = 0;
  int start = -1, cap = n;
  
  for (int i = 2000; i >= 1;--i) {
    int val = min(cap, f[i]);
    f[i] -= val;
    cap -= val;
    if (start == -1 && val)
      start = i;

    if (!cap || (i == 2 && cap != n)) {
      //printf("%d %d\n", i, start);
      cap = n;
      res += 2 * start - 2;
      start = -1;
      
      if (f[i])
        ++i;
    }
  }

  printf("%d\n", res);
}
