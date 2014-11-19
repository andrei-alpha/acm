#include <cstdio>
#include <string>
#include <iostream>
#include <queue>
#include <map>
#include <set>

#define mp make_pair
#define pb push_back

using namespace std;

struct cmp{
  bool operator() (const pair<int, string> &x, const pair<int, string> &y) {
    if (x.first != y.first)
      return x.first < y.first;
    return x.second > y.second;
  }
};

map<string, bool> viz;
map<string, int> Cnt;
set< pair<int, string>, cmp> Que;
vector< vector<string> > History(1005);

void add_word(string hash) {
  Cnt[hash] += 1;

  /*set<pair<int, string> >::iterator it = Que.begin();
  if (it->first <= Cnt[hash] || Que.size() < 20) {
    while (Que.size() >= 19 && it->first < Cnt[hash]) {
      Que.erase(it);
      it = Que.begin();
    }
    Que.insert( mp(Cnt[hash], hash) );
  }*/
}

void add_word_real(string hash) {
  Que.insert( mp(Cnt[hash], hash) );
}

void rm_word(string hash) {
  Cnt[hash] -= 1;

  /*set<pair<int, string> >::iterator it = Que.begin();
  if (it->first <= Cnt[hash] || Que.size() < 20) {
    while (Que.size() >= 19 && it->first < Cnt[hash]) {
      Que.erase(it);
      it = Que.begin();
    }
    Que.insert( mp(Cnt[hash], hash) );
  }*/
}

void rm_word_real(string hash) {
  Que.insert( mp(Cnt[hash], hash) );
}

void query(int n) {
  int last = 999999;
  int rem = n;  
  map<string, bool> viz;

  cout << "<top " << n << ">\n";
  for (set<pair<int, string> >::reverse_iterator it = Que.rbegin(); it != Que.rend(); ++it) {
    if (Cnt[it->second] != it->first)
      continue;
    if (viz[it->second])
      continue;
    viz[it->second] = true;
    
    if (rem <= 0 && last != it->first)
      break;
    
    cout << it->second << " " << it->first << "\n";
    
    last = it->first;
    --rem;
  }
  cout << "</top>\n"; 
}

int main() {
  int day = 1;
  string s;
  bool isText = false;
  
  while (cin >> s) {
    if (s == "<text>") {
      isText = true;
      ++day;
      //cout << "begin text\n";
    } else if (s == "</text>") {
      isText = false;
    
      if (day > 7) {
        for (int i = 0; i < History[day - 7].size(); ++i)
          rm_word(History[day - 7][i]);
        viz.clear();
        for (int i = 0; i < History[day - 7].size(); ++i) {
          if (viz[History[day - 7][i]])
            continue;
          rm_word_real(History[day - 7][i]);
        }
        History[day - 7].clear();
      }

      viz.clear();
      for (int i = 0; i < History[day].size(); ++i) {
        if (viz[History[day][i]])
          continue;
        add_word_real(History[day][i]);
      }

    } else if (s == "<top") {
      int n;
      cin >> n;
      cin >> s;
      query(n);
    } else if (isText && s.size() >= 4) {
      //cout << "add word\n";
      History[day].push_back(s);
      add_word(s);
    }
  } 

  return 0;
  //hash<string> hash;
  //cout << hash("ahaha");
}
