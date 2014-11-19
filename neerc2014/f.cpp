#include <cstdio>
#include <algorithm>

using namespace std;

#define Nmax 210000

int n, k;
int v[Nmax], ssr[Nmax], ssl[Nmax], sr[Nmax], sl[Nmax], r[Nmax], l[Nmax];

int main() {
  scanf("%d %d\n", &n, &k);
  for (int i = 1; i <= n; ++i)
    scanf("%d", &v[i]);

  for (int i = 1; i <= n; ++i) {
    ssl[i] = v[i] + ssl[i - 1];
    sl[i] = v[i] + ssl[i - 1] - (i - k >= 1 ? ssl[i - k] : 0);
    l[i] = max(l[i - 1], sl[i]);
  }

  for (int i = n; i >= 1; --i) {
    ssr[i] = v[i] + ssr[i + 1];
    sr[i] = v[i] + ssr[i + 1] - (i + k <= n ? ssr[i + k] : 0);
    r[i] = max(r[i + 1], sr[i]);

    //printf("%d %d\n", r[i], l[i]);
  }

  int res = r[1];
  for (int i = 1; i < n; ++i)
    res = max(res, l[i] + r[i + 1]);
  printf("%d\n", res);
  
  return 0;
}
