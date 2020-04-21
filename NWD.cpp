#include <bits/stdc++.h>

using namespace std;
using LL = long long;

int n;
int members;
unordered_map<int, pair<int, int>> divisors;
unordered_map<int, int> spf; // smallest prime factors

void print_gcd() {
    unsigned res = 1;
    for (auto d : divisors) {
        if (d.second.first == members) {
            for (int i = 1; i <= d.second.second; ++i) {
                res = res * d.first;
            }
        }
    }
    cout << res << endl;
}

void calc_spf(unsigned x) { // only odd arguments
    unsigned og_x = x;
    int i = 3;
    while (true) {
        if (x % i == 0) {
            x = x / i;
            spf[og_x] = i;
            break;
        } else {
            i += 2;
        }
    }

    /*// for every multiplicity of x
    for (auto y : spf) {
        if (y.first == y.second && y.second % x == 0) {
            spf[y.first] = x;
        }
    }*/
}

void add(unsigned x) {
    if (x != 1) {
        do {
            unsigned div;
            if (x & 1) {
                auto it = spf.find(x);
                if (it == spf.end()) {
                    calc_spf(x);
                    div = spf[x];
                } else {
                    div = it->second;
                }
            } else {
                div = 2;
            }
            int power = 0;
            while (x % div == 0) {
                x = x / div;
                power++;
            }

            auto it2 = divisors.find(div);
            if (it2 == divisors.end()) {
                divisors[div] = {1, power};
            } else {
                it2->second.first += 1;
                it2->second.second = std::min(it2->second.second, power);
            }
        } while (x > 1);
    }
}

void substract(unsigned x) {

}


int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    members = 0;

    for (int i = 0; i < n; ++i) {
        char c;
        unsigned x;
        cin >> c >> x;
        if (c == '+') {
            members++;
            add(x);
        } else {
            members--;
            substract(x);
        }
        print_gcd();
    }


    return 0;
}



