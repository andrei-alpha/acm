#include<iostream>
#include<list>
using namespace std;

int n;

int generate (int m) {
	list<int> list;
	for (int i = 1; i <= n; ++i) 
		list.push_back(i);
	while (list.size() > 1) {
		list.pop_front();
		for (int i = 1; i < m; ++i) {
			list.push_back(list.front());
			list.pop_front();
		}
	}
	return list.front();
}

int main (void) {
	while (cin >> n) {
		if (n == 0)
			return 0;;
		int m = 1;
		int reg = 0;
		while (1) {
			reg = generate(m);
			if (reg == 13)
				break;
			m++;
		}
		cout << m << endl;
	}
	return 0;
}
