#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#define pb push_back
#define mp make_pair

using namespace std;

int v1[200000], v2[200000];
vector<pair<string, int> > V; 

int main() {
  int n;

  scanf("%d\n", &n);
  for (int i = 1; i <= n; ++i) {
    string fn, ln;
    cin >> fn >> ln;
    V.pb( mp(fn, i) );
    V.pb( mp(ln, i) );
  }

  sort(V.begin(), V.end());
    
  for (int i = 0; i < V.size(); ++i) {
    int id = V[i].second;
    if (!v1[id]) {
      v1[id] = i;
    } else {
      v2[id] = i;
    }
  }

  bool ok = true;
  int last = -1;
  for (int i = 1; i <= n; ++i) {
    int x;
    scanf("%d\n", &x);
    
    if ( max(v1[x], v2[x]) < last) {
      ok = false;
      break;
    }
    else {
      if (last < min(v1[x], v2[x]))
        last = min(v1[x], v2[x]);
      else
        last = max(v1[x], v2[x]); 
    }
  }
  
  if (ok)
    printf("YES\n");
  else
    printf("NO\n");

  return 0;
}
