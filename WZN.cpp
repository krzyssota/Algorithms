#include <bits/stdc++.h>

using namespace std;
using LL = long long;

class Edge {
public:
    int a;
    int b;
    int w;;
    Edge(int x, int y, int weight) {
        a = x;
        b = y;
        w = weight;
    }
    Edge() = default;
};

const int N_MAX = 500 * 100;
unsigned marked[N_MAX] = {0};
unsigned deg[500*1000] = {0};
unordered_map<int, vector<int>> g;
unordered_map<int, Edge> e_map;
queue<int> q;
int result = 0;

int n, m;

void bfs() {

    while(!q.empty()) {

        auto prim_edge_id = q.front();
        q.pop();
        auto entry_edge = e_map[prim_edge_id];
        auto parent = entry_edge.a;
        auto u = entry_edge.b;
        auto entry_weight = entry_edge.w;

        for (auto sec_edge_id : g[u]) {

            auto secondary_edge = e_map[sec_edge_id];
            auto v = secondary_edge.b;
            auto weight = secondary_edge.w;

            if (v == parent) continue;
            if (marked[sec_edge_id] >= deg[sec_edge_id]) continue;

            if (entry_weight < weight) {
                result++;
                cout << parent << '-' << u << '-' << v << endl;
            }
            q.push(sec_edge_id);
        }
        marked[prim_edge_id]++;

    }
}

int bfs_init(int a, int b) {
    for (auto edge_id : g[a]) {
        q.push(edge_id);
    }
    for (auto edge_id : g[b]) {
        q.push(edge_id);
    }
    bfs();
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;


    int init_1;
    int init_2;
    int ind = 0;

    for (int i = 0; i < m; ++i) {
        int a, b, w;
        cin >> a >> b >> w;
        if (i == 0) {
            init_1 = a;
            init_2 = b;
        }
        e_map[ind] = Edge(a, b, w);
        g[a].push_back(ind);
        ind++;
        e_map[ind] = Edge(b, a, w);
        g[b].push_back(ind);
        ind++;
    }
    for (int i = 0; i < 2*m; ++i) {
        int a = e_map[i].a;
        int b = e_map[i].b;
        deg[i] += g[a].size()-1;
        //deg[i] += g[b].size()-1;
    }

    bfs_init(init_1, init_2);
    cout << result;


    return 0;
}



