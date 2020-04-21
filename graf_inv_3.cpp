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
    vector<vector<int>> components;
    int idx;

    int curr_max = 0, component_len = 0;
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        g.push_back(x);

        component_len++;
        curr_max = max(g[i - 1], curr_max);

        if (i == curr_max || i == n) {
            while(component_len--) components[idx].push_back()
            sort(g.begin() + i - component_len, g.begin() + i);
            lengths.push_back(component_len);
            component_len = 0;
        }
    }

    cout << lengths.size() << endl;

    int j = 0;
    for (int component_length : lengths) {
        cout << component_length << " ";
        for (int k = 0; k < component_length; k++) {
            cout << g[j + k] << " ";
        }
        cout << endl;
        j += component_length;
    }
}