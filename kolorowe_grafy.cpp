#include <bits/stdc++.h>

using namespace std;
using ull = unsigned long long;

const int N_MAX = 500*1000;
int n, m;
vector<pair<int, int>> g[N_MAX+1]; // edges: from i to pair->first color=pair->second
ull min_dist[N_MAX + 1][2];
bool marked[N_MAX + 1][2] = {{false}, {false}};


void bfs() {
    queue<tuple<int, int, ull>> q;
    marked[1][0] = marked[1][1] = true;
    for(auto edge : g[1]) {
        int u = edge.first;
        int color = edge.second;
        q.emplace(u, color, 1);
    }

    while(!q.empty()){
        auto tmp = q.front();
        q.pop();

        int u = get<0>(tmp);
        int col_parent_u = get<1>(tmp);
        ull dist = get<2>(tmp);

        if(!marked[u][col_parent_u]) min_dist[u][col_parent_u] = dist;
        else min_dist[u][col_parent_u] = std::min(min_dist[u][col_parent_u], dist);
        marked[u][col_parent_u] = true;

        for(auto edge : g[u]) {
            int v = edge.first;
            int col_u_v = edge.second;
            if (!marked[v][col_u_v] && col_u_v == !col_parent_u) {
                q.emplace(v, col_u_v, dist + 1);
            }
        }
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;

    for (int i = 1; i <= m; ++i) {
        int u, v, color;
        cin >> u >> v >> color;
        g[u].emplace_back(v, color);
        g[v].emplace_back(u, color);
    }
    bfs();
    for(int i = 2; i <= n; ++i) {
        if(!marked[i][0] && !marked[i][1]) cout << -1 << endl;
        else {
            ull min0 = (marked[i][0] ? min_dist[i][0] : UINT64_MAX);
            ull min1 = (marked[i][1] ? min_dist[i][1] : UINT64_MAX);
            cout << std::min(min0, min1) << endl;
        }
    }

    return 0;
}



