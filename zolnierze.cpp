#include <bits/stdc++.h>

using namespace std;
using LL = long long;

const int N_MAX = 1;
int n;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    vector<pair<int, int>> sold;
    sold.emplace_back(-1, -1);
    for (int j = 1; j <= n; ++j) {
        if(j == 1) {
            sold.emplace_back(-1, 2);
        } else if (j == n) {
            sold.emplace_back(n-1, -1);
        } else {
            sold.emplace_back(j-1, j+1);
        }
    }
    sold.emplace_back(-1, -1);

    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        int l = sold[x].first;
        int p = sold[x].second;
        cout << l << ' ' << p << endl;
        if(p != -1) {
            sold[p].first = l;
        }
        if(l != -1) {
            sold[l].second = p;
        }

    }


    return 0;
}



