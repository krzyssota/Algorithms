


#include <bits/stdc++.h>

using namespace std;

using ull = unsigned long long;

string word;
ull hashes[300000] = {0};
int n, m;
ull powers[300000] = {0};
static const ull p = 31;
static const ull q = 1e9 + 9;

ull getHash(int i) {
    if (i >= 0 && i < 300000) return hashes[i];
    return 0;
}

ull count_hash(int i, int j) {
    if(i >= 0 && i < n && i == j) return (word[i]-'a'+1);

    ull hash_i = getHash(i);
    ull hash_j = (getHash(j + 1) * powers[j - i + 1]) % q;
    if (hash_i < hash_j) hash_i += q;
    return (hash_i - hash_j);
}

int longer(int a, int b, int c, int d) {
    if (b - a > d - c)
        return 1;
    if (b - a < d - c)
        return 2;
    else
        return 0;
}

int lin_search(int a, int b, int c, int d) {
    if (a == b && c == d) {
        if (word[a] > word[c])
            return 1;
        if (word[a] < word[c])
            return 2;
        else
            return 0;
    }

    int i = 0;
    while (i <= b-a && count_hash(a, a + i) == count_hash(c, c + i)) ++i;

    if(i > b-a)
        return 0;
    if (word[a+i] > word[c+i])
        return 1;
    if (word[a+i] < word[c+i])
        return 2;
}

// ITER 1
int binsearch(int a, int b, int c, int d) { // first difference in hash
    if (a == b && c == d) {
        if (word[a] > word[c])
            return 1;
        if (word[a] < word[c])
            return 2;
        else
            return 0;
    }
    int l = 0, r = b - a;
    while (l < r) {
        int m = (l + r) / 2;
        if (count_hash(a, a + m) != count_hash(c, c + m)) {
            r = m;
        } else {
            l = m + 1;
        }
    }

    if (word[a] > word[c])
        return 1;
    if (word[a] < word[c])
        return 2;
    else
        return 0;

   /* for (int i = p; i <= b - a; ++i) {
        if (count_hash(a, a + i) != count_hash(c, c + i)) {
            if (word[a + i] > word[c + i]) {
                return 1;
            } else {
                return 2;
            }
        }
    }
    return 0;*/
}

/*
 // REC
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
*/

int greater_word(int a, int b, int c, int d) {
    int common_len = min(b - a, d - c);

    //switch (debug ? lin_search(a, a + common_len, c, c + common_len) : binsearch(a, a + common_len, c, c + common_len)) {
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
    }

    for (int i = word.length() - 1; i >= 0; --i) {
        hashes[i] = ((getHash(i + 1) * p) % q + (word[i] - 'a' + 1)) % q;
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
