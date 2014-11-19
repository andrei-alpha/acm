#include <cstdio>

int main() {
  int x;
  scanf("%d", &x);
  if (x % 2) {
    printf("9 %d\n", x - 9);
  } else {
    printf("4 %d\n", x - 4);
  }
  return 0;
}

