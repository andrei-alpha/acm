#include <cstdio>
#include <algorithm>

using namespace std;

#define Nmax 200010

int m, n, k, O[Nmax], V[Nmax];
long long S[Nmax];
long long A[1<<20];
long long add[1<<20];

void update(int nod, int left, int right, int x, int y, int val) {
  if (x <= left && right <= y) {
    A[nod] += val;
    add[nod] += val;
    return;
  }

  int ln = (nod << 1);
  int rn = ln + 1;
  int mid = (left + right) >> 1;

  add[ln] += add[nod];
  A[ln] += add[nod];
  add[rn] += add[nod];
  A[rn] += add[nod];
  add[nod] = 0;

  if (x <= mid)
    update(ln, left, mid, x, y, val);
  if (y > mid)
    update(rn, mid + 1, right, x, y, val);
  
  A[nod] = max(A[ln], A[rn]); 
}

long long query(int nod, int left, int right, int x, int y) {
  if (x <= left && right <= y)
    return A[nod];

  int ln = (nod << 1);
  int rn = ln + 1;
  int mid = (left + right) >> 1;
  
  add[ln] += add[nod];
  A[ln] += add[nod];
  add[rn] += add[nod];
  A[rn] += add[nod];
  add[nod] = 0;

  long long res = -Nmax;
  if (x <= mid)
    res = max(res, query(ln, left, mid, x, y));
  if (y > mid)
    res = max(res, query(rn, mid + 1, right, x, y));
  
  return res;
} 

int main() {
  scanf("%d %d", &n, &k);

  int minv = Nmax;
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &O[i]);
    minv = min(minv, O[i]);
  }

  long long res = 0;
  for (int i = 1; i <= n; ++i) {
    V[i] = minv;
    res += O[i] - V[i];
  }

  long long sum = 0;
  for (int i = 1; i <= n; ++i) {
    sum = sum + V[i] - (i - k >= 0 ? V[i - k] : 0);
    if (i >= k)
      S[++S[0]] = sum;
  }
  m = S[0];

  for (int i = 1; i <= m; ++i) {
    update(1, 1, m, i, i, +S[i]);
  }
  
  for (int i = 1; i <= n; ++i) {
    int maxv = -query(1, 1, m, max(1, i - k + 1), min(m, i)) - 1;
    maxv = min(maxv, O[i] - V[i]);
    V[i] += maxv;
    res -= maxv;
    
    update(1, 1, m, max(1, i - k + 1), min(m, i), +maxv);
  }

  printf("%lld\n", res);
  for (int i = 1; i <= n; ++i)
    printf("%d ", V[i]);
  printf("\n");

  return 0; 
}
