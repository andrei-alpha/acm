#include <cstdio>
#include <vector>
#include <cstdlib>
#include <cstring>

using namespace std;

#define abs(x) (x)<0?-(x):(x)
#define MaxTry 1000
#define Nmax (1<<19)
#define pb push_back
 
int N,M;
bool viz[Nmax], Sol[Nmax], S[Nmax], mark[Nmax], change[Nmax], ok(true);
vector< pair<int, int> > Exp;

bool eval_term(pair <int, int> T) {
    int x, y;
     
    x = S[abs(T.first)];
    y = S[abs(T.second)];
     
    if (T.first < 0)
        x ^= 1;
    if (T.second < 0)
        y ^= 1;
         
    return (x | y);
}

void add_edge(int x, int y) {
    Exp.pb( make_pair(x, y) );
}

int main()
{
    int x, y, z, p, best = 999999;
    scanf("%d%d", &N, &M);
    for (int i = 1; i <= M; ++i) {
        scanf("%d%d%d", &x, &y, &z);
        if (z == 0) {
            add_edge(-x, -y);
            add_edge(-x, y);
            add_edge(x, -y);
            mark[x] = mark[y] = true;
        } else if(z == 1) {
            change[x] = change[y] = true;
            add_edge(x, y);
            add_edge(-x, -y);
        } else {
            S[x] = S[y] = 1;
            mark[x] = mark[y] = true;
            add_edge(x, y);
            add_edge(-x, y);
            add_edge(x, -y);
        }
    }

    for (int i = 1; i <= N; ++i)
        if (!change[i])
            mark[i] = true;

    for (int step = 0; step <= max(1000, N * MaxTry); step++) {
        int curr_res = 1;
        for (int i = 0; i < Exp.size(); i++) {
            curr_res &= eval_term(Exp[i]);
            if (curr_res == 0) {
                p = i;
                break;
            }
        }
         
        if (curr_res == 1) {
            int res = 0;
            for (int i = 1; i <= N; ++i)
                res += (S[i] == 1);
            if (res < best) {
                best = res;
                memcpy(Sol, S, sizeof(S));
            }
            for (int i = 1; i <= N; ++i)
                if (!mark[i])
                    S[i] = rand() % 2;
            continue;
        }
        
        if (rand() % 2 == 0 && !mark[abs(Exp[p].first)])
            S[abs(Exp[p].first)] ^= 1;
        else
            S[abs(Exp[p].second)] ^= 1;
    }
    if (best < N) {
        printf("%d\n", best);
    } else {
        printf("impossible");
    }

    return 0;
}