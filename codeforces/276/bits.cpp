#include <cstdio>
#include <cstring>

int t, A[70], B[70];
unsigned long long a, b, c;

void decode(int A[], unsigned long long x) {
  for (int p = 0; p <= 63; ++p)
    if (x & 1LL<<(63-p))
      A[p] = 1;
    else
      A[p] = 0;
}

int main() {
  scanf("%d", &t);
  for (;t--;) {
    scanf("%lld %lld\n", &a, &b);

    ++b;
    memset(A, 0, sizeof(A));
    memset(B, 0, sizeof(B));
    decode(A, a);
    decode(B, b);
/*
    for (int i = 0; i <= 63; ++i)
      printf("%d", A[i]);
    printf("\n");
   for (int i = 0; i <= 63; ++i)
      printf("%d", B[i]);
    printf("\n");
*/
    c = 0;
    bool dif = false;
    for (int p = 0; p <= 63; ++p) {
      if (!dif)
        c += (1LL<<(63-p)) * A[p];
      else
        c += 1LL<<(63-p);
      if (A[p] != B[p])
        dif = true;
    }
    printf("%lld\n", c);
  }

  return 0;
}
