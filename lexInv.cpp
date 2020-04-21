#include <bits/stdc++.h>

using namespace std;

using ull = unsigned long long;

string word;
ull hashes[300001] = {0};
int n, m;
ull powers[300001] = {0};
ull inverse[300001]{0};
static const ull p = 31;
static const ull q = 1e9 + 9;
//static const ull q = 1e9+7;
//static const ull q = 9940796521526383;

// source: https://www.techiedelight.com/extended-euclidean-algorithm-implementation/
tuple<ull, ull, ull> extended_gcd(ull a, ull b) {
    if (a == 0)
        return make_tuple(b, 0, 1);

    ull gcd, x, y;

    // unpack tuple  returned by function into variables
    tie(gcd, x, y) = extended_gcd(b % a, a);

    return make_tuple(gcd, (y - (b / a) * x), x);
}


ull getHash(int i) {
    if (0 <= i && i <= 30000) return hashes[i];
    return 0;
}

ull count_hash(int i, int j) {

     ull hash_i = getHash(i-1);
     ull hash_j = getHash(j);
     if(hash_j < hash_i) hash_j += q;
     return ((hash_j - hash_i) * inverse[i])%q;
}

int longer(int a, int b, int c, int d) {

    if (b - a > d - c)
        return 1;
    if (b - a < d - c)
        return 2;
    else
        return 0;

}

int binsearch(int a, int b, int c, int d) { // first difference in hash
    // assert(b-a == d-c);
    if (a == b && c == d) {
        if (word[a] > word[c])
            return 1;
        if (word[a] < word[c])
            return 2;
        else
            return 0;
    }

    int m_ab = (a + b) / 2;
    int m_cd = (c + d) / 2;

    if (count_hash(a, m_ab) != count_hash(c, m_cd))
        return binsearch(a, m_ab, c, m_cd);
    else
        return binsearch(m_ab + 1, b, m_cd + 1, d);
}

/*int binsearch(int a, int b, int c, int d) { // first difference in hash
    int l = a, r = b;
    while(l < r) {
        int m_ab = (a + b) / 2;
        int m_cd = (c + d) / 2;
        if (count_hash(a, m_ab) != count_hash(c, m_cd)) {
            r = m_ab, b = m_ab, d = m_cd;
        } else {
            l = m_ab+1, a = m_ab+1, c = m_cd+1;
        }
    }
    if (word[a] > word[c])
        return 1;
    if (word[a] < word[c])
        return 2;
    else
        return 0;
}*/


int greater_word(int a, int b, int c, int d) {
    int common_len = min(b - a, d - c);

    switch (binsearch(a, a + common_len, c, c + common_len)) {
        case 1:
            return 1;
        case 2:
            return 2;
        case 0: {
            return longer(a, b, c, d);
        }
    }
}


void init() {
    powers[0] = 1;
    for (int i = 0; i < word.length(); ++i) {
        powers[i + 1] = (powers[i] * p) % q;

        auto ans = extended_gcd(powers[i], q);
        ull x = get<1>(ans);
        x = (x % q + q) % q;
        inverse[i] = x;
    }

    for (int i = 0; i < word.length(); ++i) {
        hashes[i] = (getHash(i - 1) + ((word[i] - 'a' + 1) * powers[i]) % q) % q;
    }
}

int main() {
    std::ios::sync_with_stdio(false);

    cin >> n >> m;
    cin >> word;

    init();

    while (m--) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        --a, --b, --c, --d;


        switch (greater_word(a, b, c, d)) {
            case 1:
                cout << ">\n";
                break;
            case 2:
                cout << "<\n";
                break;
            case 0:
                cout << "=\n";
                break;
            default :
                break;
        }
    }
    return 0;
}