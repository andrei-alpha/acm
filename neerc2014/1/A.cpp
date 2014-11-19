#include <stdio.h>
#include <algorithm>

#define maxdim 100005
#define maxbucket 400

using namespace std;

int n, m, q;
int starts_here[maxdim], belongsto[maxdim], sol[maxdim], bucati, bucket_size, begins[maxdim];
int T[maxdim], Rg[maxdim], flip[maxdim];
pair<int, int> E[maxdim];
vector<pair<pair<int, int>, int>> Q[maxbucket];

inline int root(int nod) {
	int R;
	for (R = nod; R != T[R];) {
		R = T[R];
	}
	
	return R;
}

inline void unify(int x, int y, int inverse) {
	if (Rg[x] > Rg[y]) {
		T[y] = x;
		flip[y] ^= inverse;
	} else {
		T[x] = y;
		flip[x] ^= inverse;
	}
	
	if (Rg[x] == Rg[y]) {
		++Rg[y];
	}
}

inline int get_flip(int nod) {
	int R; int r = flip[nod];
	for (R = nod; R != T[R];) {
		R = T[R];
		r ^= flip[R];
	}
	return r;
}

inline int baga(const pair<int, int> &p) {
	
	int x = p.first, y = p.second;
	if (root(x) == root(y)) {
		return get_flip(x) != get_flip(y);
	} else {
		unify(root(x), root(y), get_flip(x) == get_flip(y));
	}
	
	return 1;
}

int auxT[maxdim], auxRg[maxdim], auxFlip[maxdim];

inline void solve() {
	
	for (int bucata = 1; bucata <= bucati; ++bucata) {
		
		sort(Q[bucata].begin(), Q[bucata].end());
		
		for (int i = 1; i <= m; ++i) {
			T[i] = i, Rg[i] = 1, flip[i] = 0;
		}
		
		int ok = 1; int p = begins[bucata+1]-1;
		for (auto &q : Q[bucata]) {
			while (p < m && p < q.first.first) {
				++p;
				ok &= baga(E[p]);
			}
			
			for (int i = q.first.second; belongsto[i] == bucata && i <= q.first.first; ++i) {
				auxT[E[i].first] = T[E[i].first]; auxRg[E[i].first] = Rg[E[i].first]; auxFlip[E[i].first] = flip[E[i].first];
				auxT[E[i].second] = T[E[i].second]; auxRg[E[i].second] = Rg[E[i].second]; auxFlip[E[i].second] = flip[E[i].second];
			}
			
			int myok = ok;
			for (int i = q.first.second; belongsto[i] == bucata && i <= q.first.first; ++i) {
				myok &= baga(E[i]);
			}
			
			for (int i = q.first.second; belongsto[i] == bucata && i <= q.first.first; ++i) {
				T[E[i].first] = auxT[E[i].first]; Rg[E[i].first] = auxRg[E[i].first]; flip[E[i].first] = auxFlip[E[i].first];
				T[E[i].second] = auxT[E[i].second]; Rg[E[i].second] = auxRg[E[i].second]; flip[E[i].second] = auxFlip[E[i].second];
			}
			
			sol[q.second] = myok;
		}
	}
}

int main() {
	
	#ifndef ONLINE_JUDGE
	freopen("a.in", "r", stdin);
	#endif // ONLINE_JUDGE
	
	scanf("%d %d %d", &n, &m, &q);
	for (int i = 1; i <= m; ++i) {
		int x, y;
		scanf("%d %d", &x, &y);
		E[i].first = x, E[i].second = y;
	}
	
	bucket_size = 1;
	while (bucket_size * bucket_size < m) {
		++bucket_size;
	}
	
	int bucket = 1; bucati = 0;
	while (bucket <= m) {
		starts_here[bucket] = ++bucati;
		begins[bucati] = bucket;
		bucket += bucket_size;
	}
	begins[bucati+1] = m+1;
	for (int i = 1; i <= m; ++i) {
		belongsto[i] = starts_here[i] ? starts_here[i] : belongsto[i-1];
	}
	
	for (int i = 1; i <= q; ++i) {
		int x, y;
		scanf("%d %d", &x, &y);
		Q[belongsto[x]].push_back(make_pair(make_pair(y, x), i));
	}
	
	solve();
	
	for (int i = 1; i <= q; ++i) {
		if (sol[i]) {
			printf("Possible\n");
		} else {
			printf("Impossible\n");
		}
	}

	return 0;
}
