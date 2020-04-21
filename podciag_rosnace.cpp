#include <bits/stdc++.h>

using namespace std;
using ull = unsigned long long;

const int N_MAX = 1;
int n;
ull result;

/*
void g(unsigned ind){
    for (auto & x : t[1]) {
        if(x.first < ind) {
            result += x.second;
        } else {
            break;
        }
    }
}

void f(){
    for(auto x : t[1]) {
        result += x.second;
    }
    for(auto x : t[2]) {
        result += x.second;
        unsigned ind = x.first;
        g(ind);
    }
}
*/

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;

    result = n;
    ull ones = 0;
    ull twos = 0;
    ull one_twos = 0;


    for (int i = 1; i <= n; ++i) {
        int x;
        cin >> x;
        if (x == 1) {
            ones++;
        } else if (x == 2) {
            twos++;
            one_twos += ones;
            result += ones;
        } else {
            result += ones + twos + one_twos;
        }
    }
    cout << result << endl;


    return 0;
}



