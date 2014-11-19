#include <cstdio>
#include <cstdlib>

int test(const int b[10000]) {
  int sum = 0;
  for (int i = 1; i <= 10; ++i)
    sum += b[rand() % 9999];
  if (sum < 3)
    printf("ok baby!");
}

int main() {
  int a[10000];
  
  for (int i = 1; i < 10000; ++i)
    a[i] = i;
  for (int j = 1; j < 100000; ++j)
    test(a);

  for (int i = 1; i <= 10; ++i)
    printf("%d ", a[i]);

  return 0; 
}
