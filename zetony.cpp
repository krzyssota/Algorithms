#include <bits/stdc++.h>

using namespace std;
using ull = unsigned long long;

const int N_MAX = 1;
int n, z;
map<int, int> stacks;

void add(int x) {
    auto it = stacks.find(x);
    if(it == stacks.end()) {
        stacks[x] = 1;
    } else {
        it->second++;
    }
}

void divide() {
    auto it = stacks.end();
    it--;
    if(it->first&1) {
        int a = it->first/2;
        int b = it->first/2 + 1;
        add(a);
        add(b);
    } else {
        int a = it->first/2;
        int b = it->first/2;
        add(a);
        add(b);
    }
    if(it->second == 1) {
        stacks.erase(it);
    } else {
        it->second--;
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;


    for (int i = 1; i <= n; ++i) {
        int m;
        cin >> m;
        add(m);
    }
    cin >> z;
    for(int j = 1; j <= z; j++) {
        int k;
        cin >> k;
        for (int i = 0; i < k; ++i) {
            divide();
        }
        cout << stacks.size() << endl;
    }

    return 0;
}



