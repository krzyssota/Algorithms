#include <bits/stdc++.h>

using namespace std;
using LL = long long;

const int N_MAX = 1;
int n;

struct tree {
    int v;
    vector<tree*> children;
};

int dfs(tree& t) {

}
int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    set<tuple<int*, int, int, int>> g;
    int neigh[n];
    for (int i = 0; i < n; ++i) {
        neigh[i] = 0;
    }

    for (int i = 0; i < n; ++i) {
        int x, y, d;
        cin >> x >> y >> d;
    }
    return 0;
}






/*
#include <bits/stdc++.h>

using namespace std;
using LL = long long;

const int N_MAX = 1;
int n;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    set<tuple<int*, int, int, int>> g;
    int neigh[n];
    for (int i = 0; i < n; ++i) {
        neigh[i] = 0;
    }

    for (int i = 0; i < n; ++i) {
        int x, y, d;
        cin >> x >> y >> d;
        neigh[x]++;
        neigh[y]++;
        g.emplace(&neigh[x], d, x, y);
        g.emplace(&neigh[y], d, y, x);
    }
    while(g.size() > 2) {
        auto it = g.begin();
        int mi = get<1>(*it);
        while(get<0>(*it) == 1) {

        }
    }


    return 0;
}



*/
