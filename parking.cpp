#include <bits/stdc++.h>

using namespace std;
using ull = unsigned long long;

const int N_MAX = 500*1000;
int n, m;
int marked[N_MAX + 1]; // 1->car, 2->visited, 3->vis+car
vector<int> g[N_MAX+1];

void dfs(int u, int parent) {
    if(marked[u] == 1) marked[u] = 3;
    else marked[u] = 2; // marked[u] == 0

    if(marked[u] != 1 && marked[u] != 3) {
        for(auto v : g[u]) {
            if(v != parent && marked[v] != 2 && marked[v] != 3) dfs(v, u);
        }
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;

    for (int i = 1; i <= n; ++i) {
        cin >> marked[i];
    }
    for (int j = 1; j <= m; ++j) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs(1, -1);

    for (int k = 1; k <= n; ++k) {
        if(marked[k] == 3) cout << k << endl;
    }


    return 0;
}



