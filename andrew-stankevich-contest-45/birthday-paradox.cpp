#include <map>
#include <cstdio>
#include <cstdlib>
#include <bitset>

using namespace std;

bitset<1<<28> viz;

int main() {
  srand((int)time(0));
   
  printf("Generating numbers from 0 to %d\n", 1<<28);
  for (int i = 1; ; ++i) {
    int x = rand() & ((1<<28)-1);
    
    if (x < 0)
      return -1;

    if (viz[x]) {
      printf("%d numbers until colision\n", i);
      return 0;
    }

    viz[x] = true;
  }

  return 0;
}

