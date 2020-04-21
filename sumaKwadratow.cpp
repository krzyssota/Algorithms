#include <bits/stdc++.h>

using namespace std;

const int N_MAX = 300*1000;
int n;
using ull = unsigned long long;
set<int> arr;
unsigned pary = 0;

void insert(int x) {
    arr.insert(x);
    auto it = arr.find(x);
    auto it2 = it;
    set<ull>::iterator nxt;
    set<ull>::iterator prev;
    if(it == arr.begin()) {
        nxt = ++it;
        suma += power(*nxt, x);
    } else if(++it2 == arr.end()) {
        --it2;
        prev = --it2;
        suma += power(x, *prev);
    } else {
        prev = --it;
        ++it;
        nxt = ++it;
        suma -= power((*nxt), (*prev));
        suma += power(x, (*prev));
        suma += power((*nxt),x);
    }
}


int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    int x;
    cin >> x;
    arr.insert(x);

    for (int i = 1; i < n; ++i) {
        char c;
        int c_, x;
        cin >> c >> c_ >> x;
        if(c == '+') {
            insert(x);
        } else {
            remove(x);
        }
        cout << suma << endl;
    }



    return 0;
}



