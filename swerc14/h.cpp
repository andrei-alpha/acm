#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
#include <iostream>

using namespace std;

#define mp make_pair
#define pb push_back
#define Nmax (1012)

vector< vector< pair<int, int> > > A;
vector< pair<int, int> > V1, V2;

int start, end1, n, m;
bool own[Nmax], viz[2][Nmax][Nmax];
long long Dist[2][Nmax][Nmax], fee;

struct comp{ bool operator() (pair<int, pair<int, int> > x, pair<int, pair<int, int> > y) { return Dist[x.first][x.second.first][x.second.second] > Dist[y.first][y.second.first][y.second.second];} };
priority_queue<pair<int, pair<int, int> >, vector< pair<int, pair<int, int> > >, comp> Q;

void Dijkastra(int start) {
  memset(Dist, 90, sizeof(Dist));
  memset(viz, 0, sizeof(viz));

  Dist[0][0][start] = 0;
  viz[0][0][start] = true;
  Q.push( mp(0, mp(0, start) ) );

  for(;!Q.empty();) {
    int nod = Q.top().second.second;
	  int st = Q.top().first;
    int cnt = Q.top().second.first;   
	  Q.pop();
    viz[st][cnt][nod] = false;

    if (cnt == n - 1)
      continue;

    for (int j = 0; j < A[nod].size(); ++j) {
      int next = A[nod][j].first;
      long long dist = A[nod][j].second + fee;
	    int newSt = (own[next] ? st : 1);

	  Dist[st][cnt][nod] = min(Dist[st][cnt][nod], Dist[st][cnt - 1][nod] + dist); 
      if (Dist[newSt][cnt+1][next] > Dist[st][cnt][nod] + dist) {
        Dist[newSt][cnt+1][next] = Dist[st][cnt][nod] + dist;

        if (!viz[newSt][cnt+1][next]) {
          viz[newSt][cnt+1][next] = true;
          Q.push( mp(newSt, mp(cnt+1, next) ) );
        }
      }
    }
  }

  long long best1 = (1LL<<50), best2 = (1LL<<50);
  for (int cnt = 1; cnt <= n; ++cnt) {
    if (Dist[0][cnt][end1] != Dist[0][0][0] && Dist[0][cnt][end1] < best1) {
      V1.pb( mp(Dist[0][cnt][end1], cnt) );
      best1 = Dist[0][cnt][end1];
    }
    if (Dist[1][cnt][end1] != Dist[0][0][0] && Dist[1][cnt][end1] < best2) {
      V2.pb( mp(Dist[1][cnt][end1], cnt) );
      best2 = Dist[1][cnt][end1];
    }
  }
}

struct cmp{
	inline bool operator() (const pair<pair<int, int>, int> &a, const pair<pair<int, int>, int> &b) {
		return a.first.first > b.first.first;
	}
};

inline long long get_inters(pair<pair<int, int>, int> a, pair<pair<int, int>, int> b) {

	long long left = -1, middle, right = (1LL<<52);
	while (left <= right) {
		middle = (left + right) >> 1;
		long long vala = 1LL * a.first.first * middle + a.first.second;
		long long valb = 1LL * b.first.first * middle + b.first.second;
		
		if (vala < valb || (vala == valb && b.second == 1)) {
			right = middle - 1;
		} else {
			left = middle + 1;
		}
	}
	
	return left;
}

int main() {
	
//	freopen("h.in", "r", stdin);
  int ns;
  scanf("%d%d%d%d", &n, &m, &start, &end1);
  A.resize(Nmax);

  int x, y, d;
  for (int i = 1; i <= m; ++i) {
    scanf("%d%d%d", &x, &y, &d);
    A[x].pb( mp(y, d) );
    A[y].pb( mp(x, d) );
  }
  scanf("%d", &ns);
  for (int i = 1; i <= ns; ++i) {
    scanf("%d", &x);
    own[x] = true;
  }

  Dijkastra(start);

//  for (int i = 0; i < V1.size(); ++i)
//    printf("ours %dx + %d\n", V1[i].first, V1[i].second);
//  for (int i = 0; i < V2.size(); ++i)
//    printf("theirs %dx + %d\n", V2[i].first, V2[i].second);
//  for (int i = 0; i < V1.size(); ++i)
//    printf("ours %dx + %d\n", V1[i].first, V1[i].second);
//  for (int i = 0; i < V2.size(); ++i)
//    printf("theirs %dx + %d\n", V2[i].first, V2[i].second);

	
	vector<pair<pair<int, int>, int>> V;
	for (int i = 0; i < V1.size(); ++i)
		V.push_back(make_pair( mp(V1[i].second, V1[i].first), 0));
	for (int i = 0; i < V2.size(); ++i)
		V.push_back(make_pair( mp(V2[i].second, V2[i].first), 1));
	
	sort(V.begin(), V.end(), cmp());
	
	vector<int> st; vector<long long> first(V.size(), 0);
	for (int i = 0; i < (int)V.size(); ++i) {
		
		long long inters = 0;
		while (!st.empty() && get_inters(V[i], V[st.back()]) <= first[st.back()]) {
			st.pop_back();
		}
		
		if (!st.empty()) {
			inters = get_inters(V[i], V[st.back()]);
		}
		st.push_back(i);
		first[i] = inters;
	}
	
	if (V[st.back()].second == 0) {
		printf("Infinity\n");
	} else {
		//Impossible
		long long maxsol = -1;
		for (int i = 0; i < (int)st.size()-1; ++i) {
			if (V[st[i]].second == 0) {
				maxsol = first[st[i+1]] - 1;
			}
		}
		if (maxsol == -1) {
			printf("Impossible\n");
		} else {
			cout << maxsol << "\n";
		}
	}
/*
  if (fee == 0) {
    Dijkastra(start);

    if (Dist[0][end1] < Dist[1][end1])
      printf("%d\n", 0);
    else
      printf("Impossible\n");
  } else if (fee > (1LL<<50)) {
    printf("Infinity\n");
  } else {
    printf("%lld\n", fee);
  }
*/
  return 0;
}
