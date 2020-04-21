#include <bits/stdc++.h>

using namespace std;

const int N_MAX = 300*1000;
int n, d;
using ull = unsigned long long;
set<int> arr;
unsigned pary = 0;

void insert(int x) {

    arr.insert(x);

    auto it = arr.find(x-d);
    auto it2 = arr.find(x+d);
    if(it != arr.end() && (*it) == x-d) {
        pary++;
    }
    if(it2 != arr.end() && (*it2) == x+d) {
        pary++;
    }
}

void remove(int x) {

    auto it = arr.find(x-d);
    auto it2 = arr.find(x+d);
    if(it != arr.end() && (*it) == x-d) {
        pary--;
    }
    if(it2 != arr.end() && (*it2) == x+d) {
        pary--;
    }
    arr.erase(x);

}




int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> d;

    int one, x;
    cin >> one >> x;
    insert(x);
    cout << "NIE" << endl;

    for (int i = 1; i < n; ++i) {
        int sth;
        cin >> sth;
        if(sth == -1) {
            cin >> x;
            remove(x);
        } else {
            cin >> x;
            insert(x);
        }
        if(pary == 0) cout << "NIE";
        else cout << "TAK";
        cout << endl;
    }

    return 0;
}



