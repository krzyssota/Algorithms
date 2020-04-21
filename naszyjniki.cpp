#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
#include <cassert>

using namespace std;

const int N_MAX = 100000;
const int L_MAX = 200000;
int n, l;
#define _max first
#define _consecutive second

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    cin >> l;

    unordered_map<int, pair<int, int>> MAP;
    vector<vector<int>> M;
    M.reserve(n);
    for (int i = 0; i < l; ++i) {
        M.emplace_back();
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < l; j++) {
            int x;
            cin >> x;
            M[j].push_back(x);
        }
    }
    int m = 0;
    for (int k = 0; k < l; k++) {

        for (auto &el : M[k]) {

            auto it = MAP.find(el);
            if (it == MAP.end()) {
                MAP[el] = {1, k};
                m = max(m, 1);
            } else {
                auto &val = MAP[el];
                if (val.second == k) { // already seen in this column
                    continue;

                } else if (val.second == k - 1) { // last occurrence in previous column
                    int consecutive = val.first + 1;
                    m = max(m, consecutive);
                    MAP[el] = {consecutive, k};

                } else { // no seen in previous column
                    MAP[el] = {1, k};

                }
            }
        }
    }

        cout << m;

        return 0;
    }



