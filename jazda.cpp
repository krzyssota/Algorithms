#include <bits/stdc++.h>

using namespace std;
using LL = long long;

const int N_MAX = 200 * 1000;
int n, m;
vector<int> graph[N_MAX+1];
bool marked[N_MAX + 1] = {0};

void dfs(int u, int parent) {

    for (auto v : graph[u]) {
        if (!marked[v]) {
            marked[v] = 1;
            dfs(v, u);
        } else if (v != parent) {
            cout << "TAK";
            exit(0);
        }
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;

    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    for (int i = 0; i < n; ++i) {
        if (!marked[i]){
            marked[i] = 1;
            dfs(i, -1);
        }
    }
    cout << "NIE" << endl;


    return 0;
}



