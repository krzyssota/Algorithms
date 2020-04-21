#include <bits/stdc++.h>

using namespace std;
using ull = unsigned long long;

const int N_MAX = 500 * 1000;
int n;
uint64_t s[11] = {0};

uint64_t count(int x) {
    switch (x) {
        case 1:
            return 0;
        case 2:
            return (s[1] * (s[1] - 1)) / 2;
        case 3:
            return s[1] * s[2];
        case 4:
            return s[1] * s[3] + (s[2] * (s[2] - 1)) / 2;
        case 5:
            return s[1] * s[4] + s[2] * s[3];
        case 6:
            return s[1] * s[5] + s[2] * s[4] + (s[3] * (s[3] - 1)) / 2;
        case 7:
            return s[1] * s[6] + s[2] * s[5] + s[3] * s[4];
        case 8:
            return s[1] * s[7] + s[2] * s[6] + s[3] * s[5] + (s[4] * (s[4] - 1)) / 2;
        case 9:
            return s[1] * s[8] + s[2] * s[7] + s[3] * s[6] + s[4] * s[5];
        case 10:
            return s[1] * s[9] + s[2] * s[8] + s[3] * s[7] + s[4] * s[6] + (s[5] * (s[5] - 1)) / 2;
        default:
            return -1;

    }
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    uint64_t result = 0;
    for (int i = 1; i <= n; ++i) {
        int x;
        cin >> x;
        result += count(x);
        s[x]++;
    }
    cout << result;

    /*uint64_t result = 0;

    auto it = s.end();
    it--;
    while(it != s.begin()) {

        for (int j = 1; j < it->first; ++j) {
            for (int pos = it->second-1; pos >= 1; pos--) {

                auto tmp = s.lower_bound(make_pair(it->first - j, pos));
                if (tmp != s.end() && tmp->first < it->first) {

                    for (int k = 1; k < tmp->first; ++k) {
                        for (int pos2 = tmp->second-1; pos2 >= 1; pos2--) {

                            auto tmp2 = s.lower_bound(make_pair(tmp->first - k, pos2));
                            if (tmp2 != s.end() && tmp2->first < tmp->first) {

                            }
                        }
                    }

                }
            }
        }
    }*/

    return 0;
}



