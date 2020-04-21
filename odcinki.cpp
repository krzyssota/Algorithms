#include <bits/stdc++.h>

using namespace std;
using ull = unsigned long long;

const int N_MAX = 1;
int n;

ull counter = 0;
unordered_map<int, set<pair<int, bool>>> seg;

void count(int x, set<pair<int, bool>> ys) {
    auto it = ys.begin();
    ull local_cnt = 0;
    ull open = 1;
    it++;
    while(it != ys.end()){
        if(it->second) { // start
            local_cnt += open;
            open++;
        } else {
            open--;
        }
        it++;
    }
    counter += local_cnt;
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;

    for (int i = 0; i < n; ++i) {
        int x, y1, y2;
        cin >> x >> y1 >> y2;
        if(y1 > y2) swap(y1, y2);
        seg[x].emplace(y1, true);
        seg[x].emplace(y2, false);
    }
    for(auto& [x, ys] : seg) {
        count(x, ys);
    }
    cout << counter;


    return 0;
}



