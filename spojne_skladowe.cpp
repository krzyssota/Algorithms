#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>
using namespace std;

int n;
using ll = long long;
using ull = unsigned long long;
typedef struct element {
    struct element *parent;
    ll value;
    size_t sz;
    unsigned long long OR;
} element;

vector<ull> v;

/*int find(element x) {

    if (x.parent != NULL)
        x.parent = find(x.parent);

    return p[i];
}*/


/*void Union(element x, element y) {
    int xroot = find(x);
    int yroot = find(y);

    // Attach smaller rank tree under root of high rank tree
    // (Union by Rank)
    if (x.sz < y.sz) {
        x.parent = &y;
        y.OR = (y.OR)|x.value;
    }
    else {
        y.parent = &x;
        x.OR = (x.OR)|y.value;
    }
}*/

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    int result = 0;
    for (int i = 0; i < n; ++i) {
        ull x;
        cin >> x;
        if(x == 0) {
            result++;
        } else {
            for(int k = v.size()-1; k >= 0; --k) {
                if(v[k] && x&v[k]) {
                    x = x|v[k];
                    v.erase(find(v.begin(), v.end(), v[k]));
                }
            }
            v.push_back(x);
        }
    }

//    for (int j = 0; j < v.size(); ++j) {
//        if(v[j]) result += 1;
//    }
    result += v.size();
    cout << result;

    return 0;
}



