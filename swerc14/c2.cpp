#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

int n, m;

vector<int> solve(map<int, int> &v, int mx)
{
	vector<int> sl(mx, 0);
	if (v.size() <= 2)
	{
		//~ for (int i = 0; i < (int) v.size(); ++i)
		for (map<int, int>::iterator i = v.begin(); i != v.end(); ++i)
		{
			//~ for (int j = i; j < (int) v.size(); ++j)
			for (map<int, int>::iterator j = v.begin(); j != v.end(); ++j)
			{
				if (i->first + j->first <= mx)
				{
					if (i == j)
					{
						sl[i->first + j->first] += (i->second) * (i->second + 1) / 2;
					}
					else
						sl[i->first + j->first] += (i->second) * (j->second);
				}
			}
		}
		//~ printf("WTF %d\n", (int) v.size());
		//~ for (int i = 0; i < (int) v.size(); ++i)
		//~ {
			//~ printf("%d ", v[i]);
		//~ }
		//~ printf("\n");
		//~ for (int i = 0; i < 5; ++i)
			//~ printf("xx %d %d\n", i, sl[i]);
		return sl;
	}

	//~ vector<int> odd, even;
	map<int, int> odd, even;
	for (map<int, int>::iterator i = v.begin(); i != v.end(); ++i)
	{
		if (i->first <= mx)
		{
			if (i->first & 1)
				odd[i->first] += i->second;
				//~ odd.push_back(v[i]);
			else
				even[i->first] += i->second;
				//~ even.push_back(v[i]);
		}
	}
	//~ sort(odd.begin(), odd.end());
	//~ odd.resize(unique(odd.begin(), odd.end()) - odd.begin());
//~ 
	//~ sort(even.begin(), even.end());
	//~ even.resize(unique(even.begin(), even.end()) - even.begin());
	
	// odd + even first.
	map<int, int> ne;
	for (map<int, int>::iterator i = even.begin(); i != even.end(); ++i)
	{
		ne[i->first / 2] += i->second;
		//~ ne.push_back(even[i] / 2);
	}
	for (map<int, int>::iterator i = odd.begin(); i != odd.end(); ++i)
	{
		ne[i->first / 2] += i->second;
		//~ ne.push_back(even[i] / 2);
	}
	vector<int> ts = solve(ne, mx / 2);
	for (int i = 0; i < (int) ts.size(); ++i)
	{
		if (2 * i + 1 <= mx)
			sl[2 * i + 1] += ts[i];
	}
	
	//~ printf("OE SL! __ %d :: %d %d\n", (int) v.size(), (int) odd.size(), (int) even.size());
	//~ for (int i = 0; i < (int) v.size(); ++i)
	//~ {
		//~ printf("%d ", v[i]);
	//~ }
	//~ printf("\n");
	//~ for (int i = 0; i <= 10; ++i)
	//~ {
		//~ printf("SS %d %d __ %d\n", i, sl[i], ts[i]);
	//~ }
	
	// even + even;
	ne.clear();
	for (map<int, int>::iterator i = even.begin(); i != even.end(); ++i)
	{
		ne[i->first / 2] += i->second;
		//~ ne.push_back(even[i] / 2);
	}

	ts = solve(ne, mx / 2);
	for (int i = 0; i < (int) ts.size(); ++i)
	{
		if (2 * i <= mx)
		{
			sl[2 * i] += ts[i];
		}
		if (2 * i + 1 <= mx)
		{
			sl[2 * i + 1] -= ts[i];
		}
	}
	
	//~ printf("EE SL! __ %d :: %d %d\n", (int) v.size(), (int) odd.size(), (int) even.size());
	//~ for (int i = 0; i < (int) v.size(); ++i)
	//~ {
		//~ printf("%d ", v[i]);
	//~ }
	//~ printf("\n");
	//~ for (int i = 0; i <= 10; ++i)
	//~ {
		//~ printf("SS %d %d __ %d\n", i, sl[i], ts[i]);
	//~ }
	
	// odd + odd
	ne.clear();
	for (map<int, int>::iterator i = odd.begin(); i != odd.end(); ++i)
	{
		ne[i->first / 2] += i->second;
		//~ ne.push_back(even[i] / 2);
	}
	ts = solve(ne, mx / 2);
	for (int i = 0; i < (int) ts.size(); ++i)
	{
		if (2 * i + 2 <= mx)
			sl[2 * i + 2] += ts[i];
		if (2 * i + 1 <= mx)
			sl[2 * i + 1] -= ts[i];
	}
	//~ printf("OO SL! __ %d :: %d %d\n", (int) v.size(), (int) odd.size(), (int) even.size());
	//~ for (int i = 0; i < (int) v.size(); ++i)
	//~ {
		//~ printf("%d ", v[i]);
	//~ }
	//~ printf("\n");
	//~ for (int i = 0; i <= 10; ++i)
	//~ {
		//~ printf("SS %d %d __ %d\n", i, sl[i], ts[i]);
	//~ }
	
	return sl;
}

int a[1 << 20];
int main()
{
	scanf("%d", &n);
	
	map<int, int> st;
	for (int i = 0; i < n; ++i)
	{
		int s;
		scanf("%d", &s);
		a[i] = s;
		st[s]++;
		//~ printf("NM %d %d\n", i, st[i]);
	}
	
	vector<int> sl = solve(st, 200000);
	//~ for (int i = 0; i < 20; ++i)
	//~ {
		//~ printf("S %d %d\n", i, sl[i]);
	//~ }
	for (int i = 0; i < n; ++i)
	{
		sl[ st[i] ]++;
	}
	for (int i = 0; i < n; ++i)
	{
		sl[a[i]]++;
	}
	int c = 0;
	scanf("%d", &m);
	for (int i = 0; i  < m; ++i)
	{
		int a;
		scanf("%d", &a);
		if (sl[a])
			++c;
	}
	printf("%d\n", c);
	
	
	return 0;
}
