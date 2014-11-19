#include <cstdio>
#include <cstdlib>
#include <vector>
#include <map>

using namespace std;

#define mp make_pair
#define pb push_back
#define Nmax (1<<14)
#define oo 599999999

typedef pair<int, pair<int, int> > State;

int n, a, b, c, m;
map<State, int> D;
map<State, pair< pair<int, int>, pair<int, int> > > T;

inline int fun(int i, int j) {
  i -= 1; j -= 1;
  return (a*i + b*j + c*(i^j)) % m;
}

int compute(int nod, int left, int right, int x, int y) {
  State state = mp(nod, mp(x, y));
  if (x && (x < left || x > right))
      return D[state] = oo;
  if (y && (y < left || y > right))
      return D[state] = oo;

  if (D.find(state) != D.end())
    return D[state];

  int ln = (nod<<1);
  int rn = (ln+1);
  int mid = (left + right) >> 1;

  int swapx = -1, swapy = -1;
  if (x)
    swapx = (left <= x && x <= mid ? 0 : 1);
  if (y)
    swapy = (left <= y && y <= mid ? 1 : 0);
  
  //fprintf(stderr, "nod=%d left=%d right=%d x=%d y=%d swapx=%d swapy=%d\n", nod, left, right, x, y, swapx, swapy);

  if (swapx != -1 && swapy != -1 && swapx != swapy)
    return D[state] = oo;

  if (left + 1 == right) {
    if (swapx == -1 && swapy == -1) 
      return D[state] = min( fun(right, left), fun(left, right) );
    return D[state] = (swapx ? fun(right, left) : fun(left, right));
  }

  int res = oo;
  // swap node
  if (swapx || swapx == -1) {
    for (int lastLeft = mid + 1; lastLeft <= right; ++lastLeft)
    for (int firstRight = left; firstRight <= mid; ++firstRight) {
      int val = compute(ln, left, mid, firstRight, y) + compute(rn, mid + 1, right, x, lastLeft)
        + fun(lastLeft, firstRight);
      if (val < res) {
        //if (nod == 1)
        //  fprintf(stderr, "#SWP choose %d %d %d %d cost=%d add=%d\n", x, lastLeft, firstRight, y, val, fun(lastLeft, firstRight));
        res = val, T[state] = mp( mp(x, lastLeft), mp(firstRight, y) );
      }
    }
  }

  // don't swap
  if (!swapx || swapx == -1) {
    for (int lastLeft = left; lastLeft <= mid; ++lastLeft)
    for (int firstRight = mid + 1; firstRight <= right; ++firstRight) {
      int val = compute(ln, left, mid, x, lastLeft) + compute(rn, mid + 1, right, firstRight, y)
        + fun(lastLeft, firstRight);
      if (val < res) {
        //if (nod == 1)
        //  fprintf(stderr, "#NOT choose %d %d %d %d cost=%d add=%d\n", x, lastLeft, firstRight, y, val, fun(lastLeft, firstRight));
        res = val, T[state] = mp( mp(x, lastLeft), mp(firstRight, y) );
      }
    }
  }

  //fprintf(stderr, "nod=%d left=%d right=%d x=%d y=%d res=%d\n", nod, left, right, x, y, res);
  
  res = min(res, oo);
  return D[state] =  res;
}

void print(int nod, int left, int right, int x, int y) {
  State state = mp(nod, mp(x, y));
  if (left == right) {
    printf("%d ", left - 1);
    return;
  }

  int ln = (nod<<1);
  int rn = (ln+1);
  int mid = (left + right) >> 1; 

  if (left + 1 == right) {
    if (x == left) {
      print(ln, left, mid, 0, 0);
      print(rn, mid + 1, right, 0, 0);
    } else {
      print(rn, mid + 1, right, 0, 0);
      print(ln, left, mid, 0, 0);
    }
    return;
  }

  int first = (T[state].first.first ? T[state].first.first : T[state].first.second);
  int second = (T[state].second.first ? T[state].second.first : T[state].second.second);

  //fprintf(stderr, "nod=%d left=%d right=%d x=%d y=%d first=%d second=%d ", nod, left, right, x, y, first, second); 

  if (first < second) {
    //fprintf(stderr, "NOT\n");
    print(ln, left, mid, T[state].first.first, T[state].first.second);
    print(rn, mid + 1, right, T[state].second.first, T[state].second.second);
  } else {
    //fprintf(stderr, "SWP\n");
    print(rn, mid + 1, right, T[state].first.first, T[state].first.second);
    print(ln, left, mid, T[state].second.first, T[state].second.second);
  }
}

void solve() {
  D.clear();
  T.clear();  

  int res = compute(1, 1, n, 0, 0);
  printf("%d\n", res);
  print(1, 1, n, 0, 0);
  printf("\n");
}

int main() {
  freopen("elegant.in", "r", stdin);
  freopen("elegant.out", "w", stdout);

  while (true) {
    scanf("%d", &n);
    if (!n)
      break;
    scanf("%d%d%d%d", &a, &b, &c, &m);
    solve();
  }
}
