#include <bits/stdc++.h>

using namespace std;

static const int W = 0;
static const int B = 1;

static const int N = 1e6;

static int colour[2][4*N] = {{0}};

inline int left(int x) { return (int)(x << 1); };
inline int right(int x) { return (int)((int)(x << 1) | 1); };

void push_down(int x) {
    if (colour[W][x] && colour[B][x]) {
        return;
    }
    colour[W][left(x)] = colour[W][x]/2 + (colour[W][x] % 2);
    colour[W][right(x)] = colour[W][x]/2;
    colour[B][left(x)] = colour[B][x]/2 + (colour[B][x] % 2);
    colour[B][right(x)] = colour[B][x]/2;
}

void pull_up(int x) {
    colour[W][x] = colour[W][left(x)] + colour[W][right(x)];
    colour[B][x] = colour[B][left(x)] + colour[B][right(x)];
}

void update(int x, int l, int r, int L, int R, int k) {
    if (r < L || l > R) return;
    if (r <= R && l >= L) {
        colour[k][x] = r - l + 1;
        colour[!k][x] = 0;
        return;
    }
    push_down(x);
    int m = (l + r)/2;
    update(left(x), l, m, L, R, k);
    update(right(x), m + 1, r, L, R, k);
    pull_up(x);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    colour[B][1] = n;
    colour[W][1] = 0;

    int a, b;
    char c;
    for (int i = 0; i < m; i++) {
        cin >> a >> b >> c;
        update(1, 1, n, a, b, ((c == 'C') ? B : W));
        cout << colour[W][1] << endl;
    }

    return 0;
}