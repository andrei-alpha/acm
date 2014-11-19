#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

#define Nmax 3010

int n, V[Nmax];
long long S[Nmax], D[Nmax], C[Nmax];
unsigned long long VV[Nmax], UU[Nmax], RCV[Nmax], RCU[Nmax], der[Nmax], brem[Nmax], br2[Nmax];
unsigned long long pVV[Nmax], pUU[Nmax], pRCV[Nmax], pRCU[Nmax], pder[Nmax];
bool dec[Nmax];

void solve() {
  memset(C, 100, sizeof(C));
  memset(D, 100, sizeof(D));
  C[0] = -S[n];  
  D[0] = -S[n];

  for (int i = 1; i <= n; ++i) {
    memset(dec, 0, sizeof(dec));
    for (int x = 1; x <= i; ++x) {
      long long right = S[i] - S[x];
      if (V[x] * 2LL * (i-x) >= right)
        dec[x] = true;
      else
        dec[x] = false;
    }
    //~ long long remleft = S[i], remright = 0;
    long long rem = 0;
    memset(VV, 0, sizeof(VV));
    memset(UU, 0, sizeof(VV));
    memset(RCV, 0, sizeof(VV));
    memset(RCU, 0, sizeof(VV));
    memset(der, 0, sizeof(VV));
    memset(brem, 0, sizeof(VV));
    memset(br2, 0, sizeof(VV));
    
    for (int x = 1; x <= i; ++x) {
		brem[x] = rem;
      if (dec[x]) {
		  rem -= V[x];
        VV[x] = 2LL * rem + V[x];
        RCV[x] = 2;
        der[x] = -V[x];
        //~ printf("DER %d %d :: %lld\n", i, x, der[x]);
      } else {
		  VV[x] = rem;
		  RCV[x] = 1;
		  der[x] = 0;
	  }
    }
    
    rem = 0;
    for (int x = i - 1; x >= 1; --x)
    {
		br2[x] = rem;
        if (!dec[x]) {
          rem -= V[x];
          UU[x] = 2 * rem + V[x];
          //printf("pick %d %lld\n", x, val);
          RCU[x] = 2;
        } else {
          UU[x] = rem;
          RCU[x] = 1;
          //printf("don't pick %d %lld\n", x, val);
        }
      }
    
    pVV[0] = pUU[0] = pRCV[0] = pRCU[0] = pder[0] = 0;
    for (int x = 1; x <= i; ++x) 
    {
		pVV[x] = pVV[x - 1] + VV[x];
		pUU[x] = pUU[x - 1] + UU[x];
		pRCV[x] = pRCV[x - 1] + RCV[x];
		pRCU[x] = pRCU[x - 1] + RCU[x];
		pder[x] = pder[x - 1] + der[x];
	}

    for (int back = 1; back <= i; ++back) {
      // how much to go back, to remove
      long long myrem = S[i] - S[back-1];
      long long myval = D[back-1] + (long long)(3 * (i - back) + (i - back + 1) + 1) * (S[n] - S[i]);

      //printf("[%d-%d] %d total=%d %lld\n", back + 1, i, back, 2 * (i - back) + 2 * (i - back), val);

      //C[i] = min(C[i], val_firstpass + val_secondpass);
      myval += pVV[i] - pVV[back - 1];
      myval += (myrem - brem[back]) * (pRCV[i] - pRCV[back - 1]);
      
      myrem = myrem + (pder[i] - pder[back - 1]);
      myval += pUU[i - 1] - pUU[back - 1];
      myval += (myrem) * (pRCU[i - 1] - pRCU[back - 1]);

      C[i] = min(C[i], myval);
    }
    D[i] = min(C[i], D[i-1] + V[i] + 2LL * (S[n] - S[i]));
  }
}

int main() {
	freopen("ebola.in", "r", stdin);
	freopen("ebola.out", "w", stdout);
  while(true) {    
    scanf("%d", &n);
    if (!n)
      break;    

    for (int i = 1; i <= n; ++i) {
      scanf("%d", &V[i]);
      S[i] = S[i - 1] + V[i];
    }

    solve();
    printf("%lld\n", C[n]);
  }
}
