#include <iostream>
#include <algorithm>
#include <bits/stdc++.h>

using namespace std;
using LL = unsigned long long;
#define getBeg get<0>
#define getEnd get<1>
#define getVal get<2>

int n;
set<int> s;
map<int, int> m;
vector<tuple<int, int, LL>> projects;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;

    for (int i = 1; i <= n; ++i) {
        int a, b, v;
        cin >> a >> b >> v;
        s.insert(a);
        s.insert(b);
        projects.emplace_back(a, b, v);
    }
    int ind = 1;
    for(auto a : s) {
        m[a] = ind;
        ind++;
    }
    for(auto& tuple : projects) {
        getEnd(tuple) = m[getEnd(tuple)];
        getBeg(tuple) = m[getBeg(tuple)];
    }
    sort(projects.begin(), projects.end());
    LL dp[ind+1];
    for (int j = 0; j <= ind; ++j) {
        dp[j] = 0;
    }
  /*  for(auto& p : projects) {
        auto a = getBeg(p);
        auto b = getEnd(p);
        auto v = getVal(p);
        dp[b+1] = max(dp[b+1], dp[a] + v);
    }*/
    auto p = projects.begin();
    for (int t = 1; t <= ind; ++t) {
        auto a = getBeg(*p);
        auto b = getEnd(*p);
        auto v = getVal(*p);
        if(a == t) { // project starts today
            while(a == t) {
                dp[b + 1] = max(dp[b + 1], dp[a] + v);
                dp[t + 1] = max(dp[t + 1], dp[t]);
                p = next(p);
                a = getBeg(*p);
                b = getEnd(*p);
                v = getVal(*p);
            }
        } else {
            dp[t+1] = max(dp[t+1], dp[t]);
        }
    }

    cout << dp[ind];


    return 0;
}



