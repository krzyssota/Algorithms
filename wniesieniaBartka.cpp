#include <iostream>
#include <vector>
#include <map>

using namespace std;


struct Edges {
    map<int ,int> m;
    long long deg;
    long long pairs;
    void add(int w) {
        m[w]++;
        deg++;
        pairs += m[w] - 1;
    }
    long long wzn() {
        if (deg == 0) return 0;
        return deg * (deg - 1) / 2 - pairs;
    }
};

vector<Edges> v(500001);

int main() {
    ios_base::sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    int a, b, w;
    for (int i = 1; i <= m; i++) {
        cin >> a >> b >> w;
        v[a].add(w);
        v[b].add(w);
    }
    long long result = 0;
    for (auto e: v) {
        result += e.wzn();
    }
    cout << result << endl;
    return 0;
}
