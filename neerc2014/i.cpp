#include <cstdio>
#include <algorithm>

using namespace std;

int n, v[2010];

int main() {
  scanf("%d", &n);

  for (int i = 1; i <= n; ++i)
    scanf("%d", &v[i]);
  sort(v+1, v+n+1);
  
  int res = 1, sum = v[n];
  for (int i = 1; i < n; ++i)
    if (sum >= v[i]) {
      ++res;
      sum -= v[i];
    }

  printf("%d\n", res);
}
