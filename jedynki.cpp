#include <iostream>
#include <algorithm>
#include <bits/stdc++.h>

using namespace std;
using LL = long long;

int n;
bool bitmask[1000*1000] = {0};
unsigned ones = 0;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;

    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        while(bitmask[x]) {
            bitmask[x] = 0;
            ones--;
            x++;
        }
        bitmask[x] = 1;
        ones++;
        cout << ones << endl;
    }


    return 0;
}



