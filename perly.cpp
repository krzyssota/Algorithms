#include <bits/stdc++.h>

using namespace std;
using ull = unsigned long long;

const int N_MAX = 100 * 1000;

int n;
struct sub_result {
    ull value = 0;
    bool prev = false;
    bool curr = false;
};

sub_result dpL[N_MAX+1];
sub_result dpR[N_MAX+1];
ull perly[N_MAX+1];

ull max3(ull a, ull b, ull c) {
    return max(max(a, b), c);
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;

    for (int i = 0; i < n; ++i) {
        cin >> perly[i];
    }

    if (n <= 3) {
        ull result = 0;
        for (int i = 0; i <= 2; ++i) {
            result += perly[i];
        }
        cout << result;
        return 0;
    }

    dpL[0].value = perly[0];
    dpL[0].curr = true;
    dpL[1].value = perly[0] + perly[1];
    dpL[1].curr = dpL[1].prev = true;
    for (int i = 2; i < n; i++) {
        ull exc_i = dpL[i - 1].value;
        ull exc_i_1 = dpL[i - 2].value + perly[i];
        ull exc_i_2 = dpL[i - 3].value + perly[i - 1] + perly[i];

        ull best = max3(exc_i, exc_i_1, exc_i_2);
        //1) Exclude arr[i],  i.e.,  sum[i] = sum[i-1]
        // 2) Exclude arr[i-1], i.e., sum[i] = sum[i-2] + arr[i]
        // 3) Exclude arr[i-2], i.e., sum[i-3] + arr[i] + arr[i-1]
        if (best == exc_i) {
            dpL[i].prev = dpL[i - 1].curr;
            dpL[i].curr = false;

        } else if (best == exc_i_1) {
            dpL[i].curr = true;
            dpL[i].prev = false;

        } else {
            dpL[i].curr = true;
            dpL[i].prev = true;
        }
        dpL[i].value = best;
    }

    dpR[n - 1].value = perly[n - 1];
    dpR[n - 1].curr = true;
    dpR[n - 2].value = perly[n - 1] + perly[n - 2];
    dpR[n - 2].curr = dpR[n - 2].prev = true;
    for (int i = n - 3; i >= 0; i--) {
        ull exclude_curr = dpR[i + 1].value;
        ull exclude_next = dpR[i + 2].value + perly[i];
        ull exclude_next_next = dpR[i + 3].value + perly[i + 1] + perly[i];

        ull curr_best = max3(exclude_curr, exclude_next, exclude_next_next);
        if (curr_best == exclude_curr) {
            dpR[i].prev = dpR[i + 1].curr;
            dpR[i].curr = false;

        } else if (exclude_next == curr_best) {
            dpR[i].curr = true;
            dpR[i].prev = false;

        } else {
            dpR[i].curr = true;
            dpR[i].prev = true;
        }
        dpR[i].value = curr_best;
    }

    ull max_ = 0;
    for (int i = 2; i <= n - 3; ++i) {
        if (dpL[i - 1].prev && dpL[i - 1].curr && dpR[i + 1].curr && dpR[i + 1].prev) { // [t][t] | | [t][t]
            max_ = max3(max_,
                        dpL[i - 2].value + perly[i] + dpR[i + 1].value,
                        dpL[i - 1].value + perly[i] + dpR[i + 2].value);

        } else if (dpL[i - 1].prev && dpL[i - 1].curr && dpR[i + 1].curr) { // [t][t] | | [t][ ]
            max_ = max(max_,
                       dpL[i - 1].value + perly[i] + dpR[i + 2].value);

        } else if (dpL[i - 1].curr && dpR[i + 1].curr && dpR[i + 1].prev) { // [ ][t] | | [t][t]
            max_ = max(max_,
                       dpL[i - 2].value + perly[i] + dpR[i + 1].value);
        } else {
            max_ = max(max_,
                       dpL[i - 1].value + perly[i] + dpR[i + 1].value);
        }
    }
    // i == 0, 1
    max_ = max(max_,
               perly[0] + perly[1] + perly[2] + dpR[4].value);
    // i = n-2, n-1
    max_ = max(max_,
               dpL[n - 5].value + perly[n - 3] + perly[n - 2] + perly[n - 1]);

    max_ = max3(max_, dpL[n - 1].value, dpR[0].value);
    cout << max_;

    return 0;
}



