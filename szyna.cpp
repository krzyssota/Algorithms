#include <bits/stdc++.h>

using namespace std;
using ull = unsigned long long;

const int N_MAX = 500*1000;
int n;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;

    unordered_set<int> seen;
    uint64_t result = 0;
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        if(seen.find(x) != seen.end()) {
            seen.clear();
            result++;
        } else {
            seen.insert(x);
        }
    }

    cout << result;

    return 0;
}



