#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <set>
using namespace std;

int n;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    std::vector<std::pair<int, int>> pairs;
    for (int i = 0; i < n; ++i) {
        int x, y;
        cin >> x >> y;
        pairs.emplace_back(x, y);
    }
    sort(pairs.begin(), pairs.end());
    int curr_min = INT32_MAX;
    auto p1 = pairs.begin();
    auto p2 = next(p1);
    for (int j = 0; j < pairs.size()-1; j++) {
        int a,b,c,d;
        b = p1->second;
        c = p2->first;
        if(b >= c) {
            cout << "0";
            return 0;
        } else {
            curr_min = min(curr_min, c-b);
        }
        p1 = p2;
        p2++;
    }
    cout << curr_min;


    return 0;
}



