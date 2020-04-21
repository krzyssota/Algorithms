#include <bits/stdc++.h>

using namespace std;
using ull = unsigned long long;

const int N_MAX = 200*1000;
int repr[11] = {0};
pair<ull, int> dist[11];
int fac[N_MAX + 1] = {0};
vector<int> g[N_MAX+1];
/*int visited[N_MAX+1][11];*/
int n;

void dfs(int u, int parent, ull distance, int factory){
    /*visited[u][factory] = true;*/
    if(fac[u] == factory && dist[factory].first < distance){
        dist[factory] = make_pair(distance, u);
    }
    for(auto v : g[u]) {
        if(v != parent/* && !visited[v][factory]*/) {
            dfs(v, u, distance+1, factory);
        }
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;

    for (int i = 1; i <= n; ++i) {
        int x;
        cin >> x;
        fac[i] = x;
        if(repr[x] == 0) repr[x] = i;
    }
    for (int j = 1; j < n; ++j) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    for (int k = 1; k <= 10; ++k) {
        int representant = repr[k];
        if(representant != 0){
            dfs(representant, -1, 0, k);
            auto tmp = dist[k];
            dist[k] = make_pair(0, 0);
            dfs(tmp.second, -1, 0, k);
        }
    }
    ull max_ = 0;
    for (int k = 1; k <= 10; ++k) {
        max_ = max(max_, dist[k].first);
    }
    cout << max_;

    return 0;
}