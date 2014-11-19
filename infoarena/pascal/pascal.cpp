#include <cstdio>
#define Nmax 5000500
#define Pmax 3

int r,d;
int fact[Pmax][Nmax];

// i!/((i-j)!*j!)

void ciur(int r, const int primes[], bool divs[]) {
    for (int i = 0; i < 3; ++i) {
        if (!divs[i])
            continue;
        for (int j = 1; j <= r / primes[i]; ++j) {
            fact[i][j * primes[i]] = fact[i][j] + 1;
        }
    }
}

int main()
{
    freopen("pascal.in", "r", stdin);
    freopen("pascal.out", "w", stdout);
    scanf("%d%d", &r, &d);

    int res = 0;
    const int primes[] = {2, 3, 5};
    bool divs[] = {0, 0, 0};
    int cnts[] = {0, 0, 0};
    
    for (int i = 0; i < Pmax; ++i)
        if (!(d % primes[i]))
            divs[i] = true;

    ciur(r, primes, divs);

    for (int j = 1; j <= r/2; ++j) {
        for (int i = 0; i < Pmax; ++i) {
            if (!divs[i])
                continue;
            
            cnts[i] -= fact[i][j];
            cnts[i] += fact[i][r-j+1];
        }            

        int x = 0;
        switch (d) {
            case 2: { x = bool(cnts[0]); break; }
            case 3: { x = bool(cnts[1]); break; }
            case 4: { x = bool(cnts[0] >= 2); break; }
            case 5: { x = bool(cnts[2]); break; }
            case 6: { x = bool(cnts[0] && cnts[1]); break; }
        }
        res += (j*2 < r) ? 2*x : x;
    }
    printf("%d\n", res);

    return 0;
}   