#include <cstdio>
#include <vector>
#include <cstring>

using namespace std;

#define Nmax (1<<19)
#define non(x) ( (x) > N? (x) - N : (x) + N)
#define pb push_back
 
int N,M,Q[Nmax];
vector<int> A[Nmax],B[Nmax];
bool viz[Nmax], zero[Nmax], S[Nmax], ok(true);

int oposite(int z) {
    if (z == 2)
        return 0;
    else if(z == 0)
        return 2;
    return 1;
}

void add_edge(int x, int y) {
    x=x<0?-x+N:x;
    y=y<0?-y+N:y;
    
    A[non(x)].pb(y);
    A[non(y)].pb(x);
    B[y].pb(non(x));
    B[x].pb(non(y));
}

void DFP(int x)
{
    viz[x] = true;
    for(vector<int>::iterator it = A[x].begin(); it != A[x].end(); ++it)
        if(!viz[*it])
            DFP(*it);
    Q[++Q[0]] = x;
}
 
void DFM(int x)
{
    if(S[x])
        ok = false;
    viz[x] = S[non(x)] = true;
    for(vector<int>::iterator it = B[x].begin(); it != B[x].end(); ++it)
        if(!viz[*it])
            DFM(*it);
}
 
int main()
{
    int x, y, z;
    scanf("%d%d", &N, &M);
    for (int i = 1; i <= M; ++i) {
        scanf("%d%d%d", &x, &y, &z);
        z = oposite(z);
        viz[x] = viz[y] = true;
        if (z == 0) {
            add_edge(-x, -y);
            add_edge(-x, y);
            add_edge(x, -y);
        } else if(z == 1) {
            add_edge(x, y);
            add_edge(-x, -y);
        } else {
            add_edge(x, y);
            add_edge(-x, y);
            add_edge(x, -y);
        }
    }

    for (int i = 1; i <= N; ++i)
        if (!viz[i]) {
            zero[i] = true;
        }

    memset(Q, 0, sizeof(Q)); 
    memset(viz,0,sizeof(viz));
    for(int i=1;i<=N*2;++i)
        if(!viz[i])
            DFP(i);
     
    memset(viz,0,sizeof(viz));
    for(int i = N*2;i;--i)
        if(!viz[Q[i]] && !viz[non(Q[i])])
            DFM(Q[i]);
    
    if(ok) {
        int res = 0;
        for (int i = 1; i <= N; ++i)
            S[i] ^= 1;
        for (int i = 1; i <= N; ++i) {
            //printf("%d ", S[i]);
            res += (S[i] == 1);
        }
        //printf("\n");
        printf("%d\n", res);
    }
    else 
        printf("impossible");
     
    return 0;
}