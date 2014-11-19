#include <cstdio>
#include <vector>

#define Sqrt 450
#define Nmax 200100

int d[500][500];

int p, n, m;
char a[Nmax], b[Nmax];

int main() {
  fgets(a, Nmax, stdin);
  fgets(b, Nmax, stdin);
  n = strlen(a) - 1;
  m = strlen(n) - 1;

  int start1, start2, cnt1, cnt2;
  for (cnt1 = 0, start1 = 0; start1 < n; ++cnt1, start1 += Sqrt)
  for (cnt2 = 0, start2 = 0; start2 < m; ++cnt2, start2 += Sqrt) {
    if (start1 + Sqrt > n || start2 + Sqrt > m)
      break;
    
    int cnt = 0;
    for (int i = 0; i < Sqrt; ++i)
      if (a[start1 + i] != b[start2 + i])
        ++cnt;
    d[cnt1][cnt2] = cnt;
  }

  scanf("%d\n", &p);
  for (int i = 0; i < p; ++p) {
    int p1, p2, len;
    scanf("%d%d%d", &p1, &p2, &len);
    
    int res = 0;
    int i = p1, j = p2;
    
    for (;i % Sqrt; ++i 
  }

