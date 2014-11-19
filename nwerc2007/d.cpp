#include <cstdio>
#include <cstring>
#include <vector>
 
#define Nmax 10
#define mp make_pair
#define pb push_back
 
using namespace std;
 
int res, t, n, m;
int mat[Nmax][Nmax], sol[Nmax][Nmax];
int viz[Nmax][Nmax];
vector< pair<int, int> > Ends;
 
const int xx[] = {-1, 0, 1, 0};
const int yy[] = {0, 1, 0, -1};
 
bool inBounds(int x, int y) {
  if (x < 1 || x > n || y < 1 || y > m)
    return false;
  return true;
}
 
int cntReach(int x, int y, int type) {
  int cnt = 0;
  for (int k = 0; k < 4; ++k)
    if (inBounds(x + xx[k], y + yy[k]) && mat[x + xx[k]][y + yy[k]] == type)
      ++cnt;
  return cnt;
}
 
void fill(bool viz[Nmax][Nmax], int x, int y) {
  if (!inBounds(x, y) || viz[x][y] || mat[x][y] != 0)
    return;
  viz[x][y] = true;
  for (int k = 0; k < 4; ++k)
    fill(viz, x + xx[k], y + yy[k]);
}

bool check() {
  for (int i = 1; i <= n; ++i)
  for (int j = 1; j <= m; ++j)
    if (mat[i][j] == 1 && cntReach(i, j, 0) < 1)
      return false;
  
  bool viz[Nmax][Nmax];
  memset(viz, 0, sizeof(viz));
  bool done = false;
  for (int i = 1; !done && i <= n; ++i)
  for (int j = 1; !done && j <= m; ++j)
    if (mat[i][j] == 0) {
      fill(viz, i, j);
      done = true;
    }
  
  for (int i = 1; i <= n; ++i)
  for (int j = 1; j <= m; ++j)
    if (mat[i][j] == 0 && !viz[i][j]) {
      return false;
    }
  
  return true;
}

void place_beds() {
/*  
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j)
      printf("%c", mat[i][j] == 0 ? '.' : '?');
    printf("\n");
  }
  printf("\n");
*/
  int count = 0;

  for (int j = 0; j < Ends.size(); ++j) {
    int x = Ends[j].first;
    int y = Ends[j].second;
    if (viz[x][y] > 1 || mat[x][y] > 0)
      continue;

    if ( ((x == 1 || x == n) && cntReach(x, y - 1, 0) >= 2 &&
                                cntReach(x, y + 1, 0) >= 2) ||
         ((y == 1 || y == m) && cntReach(x - 1, y, 0) >= 2 &&
                                cntReach(x + 1, y, 0) >= 2) ) {
      mat[x][y] = 1;
      ++count;
    }
  }
 
 
  for (int i = 1; i <= n; ++i)
  for (int j = 1; j <= m; ++j) {
    if ( mat[i][j] == -1 && cntReach(i, j, 0) >= 1) {
      ++count;
      mat[i][j] = 1;
    }
  }

  for (int i = n; i >= 1; --i)
  for (int j = 1; j <= m; ++j) {
    if (mat[i][j] == 0) {
      mat[i][j] = 1;
      if ( check() ) {
        ++count;
      } else {
        mat[i][j] = 0;
      }
    }
  }

  // place exit
  bool done = false;
  for (int i = 1; i <= n && !done; ++i) {
    if (mat[i][1] == 0) {
      mat[i][1] = 2;
      done = true;
    } else if (mat[i][m] == 0) {
      mat[i][1] = 2;
      done = true;
    }
  }
  for (int j = 1; j <= m && !done; ++j) {
    if (mat[1][j] == 0) {
      mat[1][j] = 2;
      done = true;
    } else if (mat[n][j] == 0) {
      mat[n][j] = 2;
      done = true;
    }
  }
  for (int i = 1; i <= n && !done; ++i) {
    if (mat[i][1] == 1) {
      mat[i][1] = 2;
      done = true;
      --count;
    } else if (mat[i][m] == 1) {
      mat[i][1] = 2;
      done = true;
      --count;
    }
  }
  for (int j = 1; j <= m && !done; ++j) {
    if (mat[1][j] == 1) {
      mat[1][j] = 2;
      done = true;
      --count;
    } else if (mat[n][j] == 1) {
      mat[n][j] = 2;
      done = true;
      --count;
    }
  }
/*
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j)
      printf("%c", mat[i][j] == 1 ? 'B' : (mat[i][j] == 2 ? 'E' : '.'));
    printf("\n");
  }
  printf("%d\n", count);
*/
 if (done && res < count) {
    res = count;
    memcpy(sol, mat, sizeof(mat));
  }
}
 
bool hardcode() {
  memset(sol, -1, sizeof(sol));
 
  if (n == 1 && m == 1) {
    sol[1][1] = 2;
    return true;
  }
  if (n == 1) {
    sol[1][1] = sol[1][m] = 1;
    sol[1][2] = 2;
    return true;
  }
  if (m == 1) {
    sol[1][1] = sol[n][1] = 1;
    sol[2][1] = 2;
    return true;
  }
  if (n == 3) {
    sol[1][1] = sol[3][1] = 1;
    sol[2][1] = 2;
    for (int j = 2; j <= m; ++j)
      sol[1][j] = sol[3][j] = 1;
    return true;
  }
  if (m == 3) {
    sol[1][1] = sol[1][3] = 1;
    sol[1][2] = 2;
    for (int i = 2; i <= n; ++i)
      sol[i][1] = sol[i][3] = 1;
    return true;
  }
  if (n == 2) {
    sol[1][1] = 2;
    for (int j = 1; j <= m; ++j)
      sol[2][j] = 1;
    return true;
  }
  if (m == 2) {
    sol[1][1] = 2;
    for (int i = 1; i <= n; ++i)
      sol[i][2] = 1;
    return true;
  }
  return false;
}
 
int main() {
  scanf("%d", &t);
  for(;t--;) {
    res = -1;
    scanf("%d%d", &n, &m);
   
    bool solved = hardcode();
    for (int rows = 0; !solved && rows < (1<<n); ++rows)
    for (int cols = 0; !solved && cols < (1<<m); ++cols) {
      memset(mat, -1, sizeof(mat));
      memset(viz, 0, sizeof(viz));
      int countr = 0, countc = 0;
      Ends.clear();
 
      if (!rows || !cols)
        continue;
 
      for (int ri = 1; ri <= n; ++ri) {
        if (rows & (1<<(ri-1))) {
          ++countr;
          Ends.pb( mp(ri, 1) );
          ++viz[ri][1];
          Ends.pb( mp(ri, m) );
          ++viz[ri][m];
 
          for (int j = 1; j <= m; ++j) {
            mat[ri][j] = 0;
          }
        }
      }
      for (int cj = 1; cj <= m; ++cj) {
        if (cols & (1<<(cj-1))) {
          ++countc;
          Ends.pb( mp(1, cj) );
          ++viz[1][cj];
          Ends.pb( mp(n, cj) );
          ++viz[n][cj];
         
          for (int i = 1; i <= n; ++i) {
            mat[i][cj] = 0;
          }
        }
      }
       
      // don't need more than 4 cols or rows
      if (countc > 3 || countr > 3)
        continue;

      bool ok = true;
      for (int i = 1; i <= n; ++i)
      for (int j = 1; j <= m; ++j)
        if (viz[i][j] > 1)
          ok = false;
      if(!ok)
        continue;
 
      place_beds();
    }
 
    //printf("\nfor %d %d sol=%d\n", n, m, res);
    for (int i = 1; i <= n; ++i) {
      for (int j = 1; j <= m; ++j)
        printf("%c", sol[i][j] == 1 ? 'B' : (sol[i][j] == 2 ? 'E' : '.'));
      printf("\n");
    }
  }
}

