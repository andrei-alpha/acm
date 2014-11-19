#include <cstdio>
#include <cstring>

#define Nmax 3010

int best, n;
int Sol[Nmax], Q[Nmax], V[Nmax], S[Nmax];

bool viz[Nmax];

int one_day_more() {
  int sum = 0;
  for (int i = 1; i <= n; ++i)
    if (!viz[i])
      sum += V[i];
  return sum;
}

void back(int cnt, bool dir, int sum) {
  if (cnt == n) {
    //printf("%d\n", sum);
    //for (int i = 1; i <= Q[0]; ++i)
    //  printf("%d ", Q[i]);
    //printf("\n");
    
    if (best > sum) {
      best = sum;
      memcpy(Sol, Q, sizeof(Q));
    }
    return;
  }

  if (dir == 0) {
    bool found = false;
    for (int i = Q[Q[0]] - 1; i >= 1; --i) {
      if(viz[i])
        continue;
      
      found = true;
      viz[i] = true;
      Q[++Q[0]] = i;
      int move = Q[Q[0]-1] - i + 1;
      back(cnt + 1, dir, sum + one_day_more() * move + V[i] * (move - 1));
      --Q[0];
      viz[i] = false;
    }
    if (!found)
      dir = 1;
  }  
  if (dir == 1) {
    bool found = false;
    for (int i = Q[Q[0]] + 1; i <= n; ++i) {
      if (viz[i])
        continue;
      
      found = true;
      viz[i] = true;
      Q[++Q[0]] = i;
      int move = i - Q[Q[0]-1] + 1;
      back(cnt + 1, 1, sum + one_day_more() * move + V[i] * (move - 1));
      //back(cnt + 1, 0, sum + one_day_more() * move + V[i] * (move - 1));
      --Q[0];
      viz[i] = false; 
    }
  }
}

int main() {
  best = 99999999;
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i)
    scanf("%d", &V[i]);
  for (int i = 1; i <= n; ++i)
    S[i] = S[i - 1] + V[i];

  back(0, 1, 0);

  printf("%d\n", best);
  for (int i = 1; i <= n; ++i)
    printf("%d ", Q[i]);
  printf("\n");

  return 0;
}
