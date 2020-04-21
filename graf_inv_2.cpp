#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;
int n;
vector<int> g;
vector<int> lengths;


int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;

    int curr_max = 0, component_len = 0;
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        g.push_back(x);

        component_len++;
        curr_max = max(g[i - 1], curr_max);

        if (i != n && i == curr_max) {
            sort(g.begin() + i - component_len, g.begin() + i);
            lengths.push_back(component_len);
            component_len = 0;
        }
    }
    sort(g.begin() + n - component_len, g.begin() + n);
    lengths.push_back(component_len);

    cout << lengths.size() << endl;

    int j = 0;
    for (int component_length : lengths) {
        cout << component_length << " ";
        for (int k = 1; k <= component_length; k++) {
            cout << g[j] << " ";
            j++;
        }
        cout << endl;
    }
}