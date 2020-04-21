#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>
using namespace std;

vector<int> M[500 * 1000];
int colored[500 * 1000] = {0};
int n, m;
bool oddCycle = false;

/*void dfs(int origin, int v, int odd_length) {
    if(v == origin && odd_length) {
        oddCycle = true;
    }
    if(!colored[v]) {
        colored[v] = 1;
        for (auto &u : M[v]) {
            dfs(origin, u, !odd_length);
        }

    }
}*/
void dfs(int origin, int v, int color) {
    if(colored[v] == -1) {
        colored[v] = color;
        for (auto &u : M[v]) {
            dfs(origin, u, !color);
        }
    } else if (color != colored[v]) {
        cout << "NIE";
        exit(0);
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    cin >> m;
    for (int i = 0; i < m; ++i) {
        int x, y;
        cin >> x >> y;
        x--, y--;
        M[x].push_back(y);
        M[y].push_back(x);
    }
    for(int i = 0; i < n; ++i) {
        colored[i] = -1;
    }
    for(int i = 0; i < n; ++i) {
        if(oddCycle) break;
        if(colored[i] == -1) {
            dfs(i, i, 0);
        }
    }
    if(oddCycle) cout << "NIE";
    else cout << "TAK";
    return 0;
}



