#include <stdio.h>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <string>
#include <unordered_map>
#include <map>
#include <iostream>

#define maxdim 105

using namespace std;

#define buff_size 3000000
char buff[buff_size+5]; int ch = buff_size;

inline bool is_letter(const char &x) {
    
    return (x >= 'a' && x <= 'z') || (x >= 'A' && x <= 'Z');
}
inline bool is_separator(const char &x) {
    
    return x == '.' || x == ',' || x == ':' || x == ';' || x == '?' || x == '!' || x == '*' || x == '#';
}
inline bool is_number(const char &x) {
    
    return x >= '0' && x <= '9';
}

string next_token() {
    
    string aux;
    cin >> aux;
    return aux;
    
    if (ch == buff_size) {
        fread(buff, 1, buff_size, stdin);
        ch = 0;
    }
    if (buff[ch] == 0) {
        return string();
    }
    
    while (!is_letter(buff[ch]) && !is_separator(buff[ch]) && !is_number(buff[ch])) {
        buff[ch] = 0;
        ++ch;
        if (ch == buff_size) {
            fread(buff, 1, buff_size, stdin);
            ch = 0;
        }
        if (buff[ch] == 0) {
            return string();
        }
    }
    
    string r;
    while (is_letter(buff[ch]) || is_separator(buff[ch]) || is_number(buff[ch])) {
        r += buff[ch];
        buff[ch] = 0;
        ++ch;
        if (ch == buff_size) {
            fread(buff, 1, buff_size, stdin);
            ch = 0;
        }
    }
    
    return r;
}

inline int get_int(const string &s) {
    int r = 0;
    for (int i = 0; i < (int)s.size(); ++i) {
        r = r * 10 + s[i] - '0';
    }
    return r;
}

inline char _to_lc(const char &x) {
    if (x >= 'A' && x <= 'Z') {
        return x - 'A' + 'a';
    }
    return x;
}

inline string to_lc(string word) {
    string newWord;
    for (int i = 0; i < word.size(); ++i)
        newWord.push_back(_to_lc(word[i]));
    return newWord;
}

inline unsigned long long to(string word) {
    hash<string> str_hash;
    return str_hash(word);
}

int n;

unordered_map<unsigned long long, bool> known;

inline void baga(const vector<string> &sentence) {

    for (int i = 0; i < (int)sentence.size(); ++i) {
        string seq;
        for (int j = i; j < (int)sentence.size() && j < i + n; ++j) {
            if (j != i)
                seq.push_back(' ');
            seq += to_lc(sentence[j]);
            known[to(seq)] = true;
        }

        known[to(to_lc(sentence[i]))] = true;
    }
}

inline string concat(const vector<string> &sentence) {
    
    string r;
    for (int i = 0; i < (int)sentence.size(); ++i) {
        r.append(sentence[i]);
        if (i != (int)sentence.size()-1) {
            r += ' ';
        }
    }
    
    return r;
}

inline bool check_all(const vector<string> &sentence) {
    
    for (int i = 0; i < (int)sentence.size(); ++i) {
        string seq;
        for (int j = i; j < (int)sentence.size() && j < i + n; ++j) {
            if (j != i)
                seq.push_back(' ');
            seq += to_lc(sentence[j]);
        }
        if (!known[to(seq)]) {
            return false;
        }
    }
    
    return true;
}

inline void check_sentence(const vector<string> &sentence) {
    
    int knows_words = 1;
    for (string word : sentence) {
        
        if (!known[to(to_lc(word))]) {
            printf("What does the word \"%s\" mean?\n", word.c_str());
            knows_words = 0;
        }
        known[to(to_lc(word))] = true;
    }
    
    if ((!knows_words || !check_all(sentence)) && (int)sentence.size() > 1) {
        printf("What does the sentence \"%s\" mean?\n", concat(sentence).c_str());
    }
}

int main() {
    string n_string; int test = 0;
    for (; ;) {
        n_string = next_token();
        if (n_string.empty()) {
            break;
        }
        ++test;
        
        if (test != 1) {
            printf("\n");
        }
        
        printf("Learning case %d\n", test);
        
        n = get_int(n_string);
        
        //insert word joe
        string j = "joe";
        vector<string> aux;
        aux.push_back(j);
        baga(aux);
        
        vector<string> sentence;
        sentence.reserve(105);
        //add the before known sentences
        for (; ;) {
            string word = next_token();
            if ((int)word.size() > 1 || is_letter(word[0])) {
                sentence.push_back(word);
                continue;
            }
            if (word.size() == 1 && is_separator(word[0]) && word[0] != '*' && word[0] != '#') {
                //finish sentence
                baga(sentence);
                sentence.clear();
                continue;
            }
            if (word[0] == '*') {
                baga(sentence);
                sentence.clear();
                break;
            }
        }
        
        //solve the next sentences
        for (; ;) {
            string word = next_token();
            if ((int)word.size() > 1 || is_letter(word[0])) {
                sentence.push_back(word);
                aux.clear();
                aux.push_back(word);
                check_sentence(aux);
                baga(aux);
                
                continue;
            }
            if (word.size() == 1 && is_separator(word[0]) && word[0] != '*' && word[0] != '#') {
                //finish sentence
                check_sentence(sentence);
                baga(sentence);
                sentence.clear();
                continue;
            }
            if (word[0] == '#') {
                check_sentence(sentence);
                sentence.clear();
                break;
            }
        }
        
        known.clear();
    }
    
    return 0;
}
