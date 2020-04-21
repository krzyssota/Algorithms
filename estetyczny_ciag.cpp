#include <iostream>
#include <algorithm>
#include <bits/stdc++.h>

using namespace std;
using LL = long long;

int n;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    vector<int> vec;

    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        vec.push_back(x);
    }
    sort(vec.begin(), vec.end());
    unsigned max_len = 1;
    unsigned curr_len = 1;
    for(int i = 1; i < n; ++i) {
        if(abs(vec[i] - vec[i-1]) <= 1) {
            curr_len++;
        } else {
            max_len = max(max_len, curr_len);
            curr_len = 1;
        }
    }
    max_len = max(max_len, curr_len);

    cout << max_len;


    return 0;
}



