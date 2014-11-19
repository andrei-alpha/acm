#include<iostream>
using namespace std;

int main (void) {
	char first, second, third;
	int b[3], g[3], c[3], min, aux;
	while (cin >> b[0] >> g[0] >> c[0] >> b[1] >> g[1] >> c[1] >> b[2] >> g[2] >> c[2]) {
		min = b[1] + b[2] + g[0] + g[1] + c[0] + c[2];
		first = 'B'; second = 'C'; third = 'G';       //BCG
		aux = b[1] + b[2] + g[0] + g[2] + c[0] + c[1];
		if (aux < min) {
			min = aux;
			first = 'B'; second = 'G'; third = 'C';   //BGC
		}
		aux = b[0] + b[2] + g[0] + g[1] + c[1] + c[2];
		if (aux < min) {
			min = aux;
			first = 'C'; second = 'B'; third = 'G';   //CBG
		}			
		aux = b[0] + b[1] + g[0] + g[2] + c[1] + c[2];
		if (aux < min) {
			min = aux;
			first = 'C'; second = 'G'; third = 'B';   //CGB
		}
		aux = b[0] + b[2] + g[1] + g[2] + c[0] + c[1];
		if (aux < min) {
			min = aux;
			first = 'G'; second = 'B'; third = 'C';   //GBC
		}
		aux = b[0] + b[1] + g[1] + g[2] + c[0] + c[2];
		if (aux < min) {
			min = aux;
			first = 'G'; second = 'C'; third = 'B';   //GCB
		}
		cout << first << second << third << " " << min << endl;
	}
	return 0;
}
