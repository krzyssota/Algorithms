/*
#include <bits/stdc++.h>

using namespace std;
using ULL = unsigned long long;

const int N_MAX = 100*1000;
int n, m;

struct S {
    ULL pre[3];
    ULL suf[3];
    ULL sum;
    ULL res;

    S(ULL p0, ULL p1, ULL p2, ULL s0, ULL s1, ULL s2, ULL _sum, ULL _res) {
        pre[0] = p0;
        pre[1] = p1;
        pre[2] = p2;
        pre[0] = s0;
        pre[1] = s1;
        pre[2] = s2;
        sum = _sum;
        res = _res;
    }
    S() = default;
};


S t[2 * N_MAX];

void build() {  // build the tree
    for (int i = n - 1; i > 0; --i) t[i] = t[i<<1] + t[i<<1|1];
}

void modify(int p, int value) {  // set value at position p
    for (t[p += n] = value; p > 1; p >>= 1) t[p>>1] = t[p] + t[p^1];
}

int query(int l, int r) {  // sum on interval [l, r)
    int res = 0;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
        if (l&1) res += t[l++];
        if (r&1) res += t[--r];
    }
    return res;
}



int p(int x) {
    int y = 1;
    while(x > y) {
        y = y * 2;
    }
    return y;
}


void clean(int node, int l, int r) {
    if(l <= r) {
        D[node] = 0;
        int m = (l+r)/2;
        if(l != r) {
            clean(2 * node, l, m);
            clean(2 * node + 1, m + 1, l);
        }
    }
}
void init(int n) {
    clean(1, 1, n);
}

void _update(int node, int l, int r, int i, int value){
    if(l > r || r < i) { // bledne podanie arg lub i-tego elementu nie ma w tym poddrzewie/fragmencie tablicy
        return;
    } else if (l == r && r == i) {
        D[node] = value%mod;
    } else {

        int m = (l + r) / 2;
        if (i <= m){
            _update(2*node, l, m, i, value);
        } else {
            _update(2*node + 1, m+1, r, i, value);
        }
        D[node] = (D[2*node] + D[2*node + 1])%mod;
    }
}
void update(int i, int value){
    _update(1, 1, n, i, value);
}

int _query(int node, int l, int r, int i) {
    if(l > r || i < l){ // odcinek 1..i znajduje sie na lewo od zasięgu (liści) rozważanego odcinka l..r
        return 0;
    } else if (r <= i){ // odc 1..i zawiera w sobie rozwazany odcinke l..r co oznacza ze suma w wezle bedzie brana cala
        return D[node];
    } else {
        int m = (l+r)/2;
        return (_query(2*node, l, m, i) + _query(2*node + 1, m+1, r, i))%mod;
    }
}

int query(int i, int j){ // od i włącznie do j włącznie
    if(i <= j) {
        return (_query(1, 1, n, j) - _query(1, 1, n, i-1))%mod; // i-ty element sie wlicza
        */
/* } else if ( i == j){
             return _query(1, 1, n, j) - _query(1, 1, n, i-1);*//*

    } else {
        return 0;
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;



    for(int i = 1; i <= n; ++i) {

    }

    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        cout << query(a, b);
    }


    return 0;
}



*/
