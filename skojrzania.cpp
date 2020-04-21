#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <set>
#include <unordered_map>

using namespace std;
int n, m;

unsigned perfect_match(set<tuple<int, int, int>>& edges) {
    unsigned result = 0;
    unordered_set <int> discarded;
    while(!edges.empty()) {
        auto it = edges.begin();
        int a = get<0>(*it), b = get<1>(*it);
        if((discarded.find(a) != discarded.end()) || (discarded.find(b) != discarded.end())) { // at least one end is in discarded
            edges.erase(it);
        } else {
            result += get<2>(*it);
            discarded.insert(a);
            discarded.insert(b);
        }
    }
    return result;
}


int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    if(n%2 == 1) {
        cout << -1;
        return 0;
    }
    set<tuple<int, int, int>> edges;
    unsigned edges_from_first = 0;

    for (int i = 0; i < m; ++i) {
        int a, b, w;
        cin >> a >> b >> w;
        if(a == 1 || b == 1) edges_from_first++;
        if(a > b) swap(a, b);
        edges.emplace(a, b, w);
    }
    if(!edges_from_first) {
        cout << -1;
        return 0;
    }
    unsigned minimum = UINT32_MAX;
    for(unsigned int i = 0; i < edges_from_first; ++i) {
        set<tuple<int, int, int>> edges_copy = edges;
        for(int j = 0; j < i; ++j) {
           edges_copy.erase(edges_copy.begin());
        }
        unsigned w = perfect_match(edges_copy);
        minimum = min(minimum, w);
    }
    cout << minimum;


    return 0;
}




