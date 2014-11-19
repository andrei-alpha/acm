#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <limits>

#define maxdim 200005

using namespace std;

int n, p;
int lson[maxdim], rson[maxdim], removals[maxdim], parent_of_node[maxdim], chosen_son[maxdim];
int first[maxdim], last[maxdim], is_removed[maxdim], chain[maxdim], father_of_chain[maxdim], chains;
int aib[maxdim];
long long sol, answer[maxdim];

inline int lsb(const int &x) {
	return x & -x;
}

inline void update(int poz, int val) {
	
	while (poz <= n) {
		aib[poz] += val;
		poz += lsb(poz);
	}
}

inline int query(int poz) {
	int r = 0;
	
	while (poz > 0) {
		r += aib[poz];
		poz -= lsb(poz);
	}
	
	return r;
}
inline int query(int left, int right) {
	return query(right) - query(left-1);
}
inline int height(int node) {
	return query(last[node]) - query(first[node]-1);
}

struct T {
	int key, priority;
	T *left, *right, *parent;
	
	T(int _key, int _pr, T* l, T* r) {
		key = _key;
		priority = _pr;
		left = l, right = r;
		parent = NULL;
	}
};
T *nil = new T(0, 0, NULL, NULL);

void rotleft(T* &n) {
	T *t = n->left;
	n->left = t->right, t->right = n;
	n->left->parent = n;
	t->right->parent = t;
	n = t;
}
void rotright(T* &n) {
	T *t = n->right;
	n->right = t->left, t->left = n;
	n->right->parent = n;
	t->left->parent = t;
	n = t;
}
void balance(T* &n) {
	if (n->left->priority > n->priority) {
		rotleft(n);
	} else if (n->right->priority > n->priority) {
		rotright(n);
	}
}

void insert(T* &n, int key, int priority) {
	if (n == nil) {
		n = new T(key, priority, nil, nil);
		return;
	}
	
	if (key <= n->key) {
		insert(n->left, key, priority);
	} else {
		insert(n->right, key, priority);
	}
	balance(n);
}

void erase(T* &n, int key) {
	if (n == nil)	return;
	
	if (key < n->key) {
		erase(n->left, key);
		n->left->parent = n;
		n->right->parent = n;
	} else if (key > n->key){
		erase(n->right, key);
		n->left->parent = n;
		n->right->parent = n;
	} else {
		if (n->left == nil && n->right == nil) {
			delete n, n = nil;
		} else {
			(n->left->priority > n->right->priority) ? rotleft(n) : rotright(n);
			n->left->parent = n;
			n->right->parent = n;
			erase(n, key);
			n->left->parent = n;
			n->right->parent = n;
		}
	}
}

void join(T* &R, T* Ts, T* Tg, int key) {
	R = new T(key, 0, Ts, Tg);
	erase(R, R->key);
}

void split(T* &R, T* &Ts, T* &Tg, int key) {
	insert(R, key, numeric_limits<int>::max());
	Ts = R->left, Tg = R->right;
	delete R, R = nil;
}

T* TNode[maxdim];
int niv[maxdim];

void dfs_init(int nod, int nivv) {
	niv[nod] = nivv;
	
	first[nod] = ++p;
	if (lson[nod]) {
		dfs_init(lson[nod], nivv+1);
	}
	if (rson[nod]) {
		dfs_init(rson[nod], nivv+1);
	}
	last[nod] = p;
	
	if (is_removed[nod])
		return;
	
	TNode[nod] = new T(nivv, rand(), nil, nil);
	father_of_chain[chain[lson[nod]]] = father_of_chain[chain[rson[nod]]] = nod;
	int lh = query(first[lson[nod]], last[lson[nod]]);
	int rh = query(first[rson[nod]], last[rson[nod]]);
	
	if (lh == 0 && rh == 0) {
		chain[nod] = ++chains;
	} else {
		if (lh >= rh) {
			chain[nod] = chain[lh];
			sol += lson[nod];
			chosen_son[nod] = lson[nod];
			join(TNode[nod], TNode[nod], TNode[lson], nivv);
		} else {
			chain[nod] = chain[rh];
			sol += rson[nod];
			chosen_son[nod] = rson[nod];
			join(TNode[nod], TNode[nod], TNode[rson], nivv);
		}
	}
}

int main() {
	
	for (;;) {
		scanf("%d", &n);
		if (n == 0) {
			break;
		}
		
		for (int i = 1; i <= n; ++i) {
			int x, y;
			scanf("%d %d", &x, &y);
			lson[i] = x, rson[i] = y;
			parent_of_node[x] = parent_of_node[y] = i;
		}
		parent_of_node[0] = 0;
		
		int rmvls;
		scanf("%d", &rmvls);
		for (int i = 1; i <= rmvls; ++i) {
			scanf("%d", &removals[i]);
			is_removed[removals[i]] = 1;
		}
		
		for (int i = 1; i <= n; ++i) {
			if (!is_removed[i]) {
				update(first[i], 1);
			}
		}
		
		p = 0;
		dfs_init(1, 1);
		
		for (int i = rmvls; i >= 1; --i) {
			answer[i] = sol;
				
			// add this node
			int node = removals[i];
			update(first[node], 1);
			is_removed[node] = 0;
			
			int parent = parent_of_node[node];
			if (is_removed[lson[parent]] || is_removed[rson[parent]]) {
				chain[node] = chain[parent];
				sol += node;
				node = father_of_chain[chain[node]];
			} else {
				if (lson[parent] == node && height(rson[parent]) == 1) {
					chain[rson[parent]] = ++chains;
					chain[lson[parent]] = chain[parent];
					father_of_chain[chains] = parent;
					sol += node - rson[parent];
					node = father_of_chain[chain[node]];
				} else {
					chain[node] = ++chains;
					father_of_chain[chains] = parent;
					node = father_of_chain[chain[parent]];
				}
			}
			
			while (node > 0) {
				
				if (chosen_son[node] != lson[node]) {
					if (height(lson[node]) >= height(rson[node])) {
//						father_of_chain[chain[lson[node]]] = 
					}
				}
			}
		}
		
		for (int i = 1; i <= rmvls; ++i) {
			cout << answer[i] << "\n";
		}
	}

	return 0;
}
