#include <bits/stdc++.h>
using namespace std;
using LL = long long;

static const LL N = 1e5 + 2;
static LL n, m;
static LL graph[N][3] = {{0}};
static LL dp[N];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    if (n & 1) {
        cout << -1;
        return 0;
    }
    for (LL i = 0; i < n; i++) dp[i] = INT_MAX;
    for (LL u, v, w, i = 0; i < m; i++) {
        cin >> v >> u >> w;
        if (u < v) swap(u, v);
        graph[v][u - v] = w;
    }
    dp[0] = 0;
    for (LL i = 1; i <= n / 2 + 1; i++) {
        if (graph[2*i - 1][1]) {
            dp[i] = min(dp[i], dp[i - 1] + graph[2*i - 1][1]);
        }
        if (graph[2*i - 1][2] && graph[2*i][2]) {
            dp[i + 1] = dp[i - 1] + graph[2*i - 1][2] + graph[2*i][2];
        }
    }

    cout << ((dp[n / 2] < INT_MAX) ? dp[n / 2] : -1);

    return 0;
}
