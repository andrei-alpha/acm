#include <stdio.h>
#include <vector>
#include <unordered_map>
#include <queue>
#include <algorithm>

using namespace std;

int robots, n, m, limit;
unordered_map<int, int> viz;
queue<int> Q;

char A[15][15], B[15][15];

inline int encode(const vector<int> &x, const vector<int> &y) {
	
	int code = x[0] * 10 + y[0];
	
	int ord[3] = {0, 0, 0};
	for (int i = 1; i < robots; ++i) {
		int ind = 0;
		for (int j = 1; j < robots; ++j) {
			if (x[i] > x[j] || (x[i] == x[j] && y[i] > y[j])) {
				++ind;
			}
		}
		ord[ind] = i;
	}
	for (int i = 0; i < robots-1; ++i) {
		code = code * 10 + x[ord[i]];
		code = code * 10 + y[ord[i]];
	}
	
	return code;
}

inline void decode(int code, vector<int> &x, vector<int> &y) {
	
	x.resize(robots), y.resize(robots);
	for (int i = robots-1; i >= 0; --i) {
		y[i] = code % 10; code /= 10;
		x[i] = code % 10; code /= 10;
	}
}

int dx[] = {-1, 0, 1, 0};
int dy[] = {0, 1, 0, -1};

int main() {

//	freopen("e.in", "r", stdin);
	
	scanf("%d %d %d %d\n", &robots, &m, &n, &limit);
	for (int i = 0; i < n; ++i) {
		scanf("%s", A[i]);
		for (int j = 0; j < m; ++j) {
			B[i][j] = A[i][j];
		}
	}
	
	vector<int> init_x, init_y;
	init_x.resize(1), init_y.resize(1); int destX, destY;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			
			if (A[i][j] >= '2' && A[i][j] <= '4') {
				init_x.push_back(i);
				init_y.push_back(j);
			}
			if (A[i][j] == '1') {
				init_x[0] = i, init_y[0] = j;
			}
			if (A[i][j] == 'X') {
				destX = i, destY = j;
			}
		}
	}
	
	int init_conf = encode(init_x, init_y); int sol = -1;
	viz[init_conf] = 0;
	Q.push(init_conf);
	while (!Q.empty()) {
		int conf = Q.front(); Q.pop();
		vector<int> x, y;
		decode(conf, x, y);
		
		if (x[0] == destX && y[0] == destY) {
			sol = viz[conf];
			break;
		}
		
		for (int i = 0; i < robots; ++i) {
			B[x[i]][y[i]] = 'W';
		}
		
		for (int i = 0; i < robots; ++i) {
			for (int d = 0; d < 4; ++d) {
				
				int nexti = x[i], nextj = y[i];
				while (1) {
					nexti += dx[d], nextj += dy[d];
					if (nexti < 0 || nexti >= n || nextj < 0 || nextj >= m || B[nexti][nextj] == 'W') {
						break;
					}
				}
				nexti -= dx[d], nextj -= dy[d];
				
				int prevx = x[i], prevy = y[i];
				x[i] = nexti, y[i] = nextj;
				
				int code = encode(x, y);
				if (viz.find(code) == viz.end() && viz[conf] < limit) {
					viz[code] = viz[conf]+1;
					Q.push(code);
				}
				
				x[i] = prevx, y[i] = prevy;
			}
		}
		
		for (int i = 0; i < robots; ++i) {
			B[x[i]][y[i]] = A[x[i]][y[i]];
		}
	}
	
	if (sol == -1) {
		printf("NO SOLUTION\n");
	} else {
		printf("%d\n", sol);
	}

	return 0;
}
