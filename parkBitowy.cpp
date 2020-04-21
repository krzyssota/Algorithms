#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <assert.h>

using namespace std;

const int MAX_N = 500002;
const int LOG_MAX = 20;
int n, m, logn;
int parent[MAX_N] = {-1};
int lchild[MAX_N] = {-1};
int rchild[MAX_N] = {-1};
int depth[MAX_N] = {0};
int links[LOG_MAX][MAX_N];
std::pair<int, int> far[MAX_N], farUp[MAX_N], farDown[MAX_N];


/*
 n (2 ≤ n ≤ 500 000), oznaczająca liczbę
polanek w Parku Bitowym. Każdy z kolejnych n wierszy zawiera dwie liczby całkowite
 ai oraz bi (ai, bi ∈ {−1, 1, 2, . . . , n}), oznaczające, że z polanki numer i
 prowadzą ścieżki na polanki numer ai oraz bi.
 Wartość−1 oznacza, że dana ścieżka nie istnieje.
 Dane wejściowe zawierają wszystkie krawędzie konieczne do jednoznacznego
 zbudowania drzewa ukorzenionego w polance numer 1.

W kolejnym wierszu wejścia znajduje się jedna liczba całkowita
 m (1 ≤ m ≤ 500 000), oznaczająca liczbę poleceń, które Bajtek otrzymał od Bajtyny.
 Każdy z następnych m wierszy zawiera dwie liczby całkowite
 a oraz d (1 ≤ a ≤ n, 0 ≤ d < n).
 */

void setDepthRec(int u, int currDepth){
    if(u != -1) {
        depth[u] = currDepth;
        setDepthRec(lchild[u], currDepth + 1);
        setDepthRec(rchild[u], currDepth + 1);
    }
}

void fillLinks() {
    for (int i = 0; i <= logn; ++i) {
        for (int node = 1; node <= n; ++node) {
            if (i == 0) { // distance 2^0 = 1
                links[i][node] = parent[node];
            } else {
                if (links[i - 1][node] != -1) {
                    // two smaller jumps = one larger jump
                    links[i][node] = links[i - 1][links[i - 1][node]];
                } else {
                    // branch with non-existing nodes
                    links[i][node] = -1;
                }

            }
        }
    }
}


/*
int fastpow(int a, int n) {
    if (n == 0) {
        return 1;
    } else if (n == 1) {
        return a;
    } else {
        int w = fastpow(a, floor(n / 2));
        w = w * w;
        if (n % 2 == 1) {
            w = w * a;
        }
        return w;
    }
}
*/

int ancestor(int u, int h) {
    int result = u;
    int i = logn;
    int pow = 1 << i;
    while (h > 0) {
        if (pow > h){
            --i;
            pow >>= 1;
            //pow /= 2;
        } else {
            result = links[i][result];
            h -= pow;
        }
    }
    return result;
}

int lowestCommonAncestor(int u, int v){
    int du = depth[u];
    int dv = depth[v];

    if(du < dv){
        v = ancestor(v, dv-du);
        dv = depth[v];

    } else {
        u = ancestor(u, du-dv);
        du = depth[u];
    }

    if(u == v) return u;
    int i = logn;
    while(i >= 0){
        if(links[i][u] != links[i][v]){
            u = links[i][u];
            v = links[i][v];
        }
        --i;
    }
    return parent[u];
}

void setFarDownRec(int u){
    if(u != -1){
        setFarDownRec(lchild[u]);
        setFarDownRec(rchild[u]); //preorder

        pair<int, int> a, b, c;
        a = {0, u};
        (lchild[u] == -1) ? b = {-1, u}
                          : b = {farDown[lchild[u]].first + 1, farDown[lchild[u]].second};
        (rchild[u] == -1) ? c = {-1, u}
                          : c = {farDown[rchild[u]].first + 1, farDown[rchild[u]].second};
        farDown[u] = max(a, max(b, c));
        /*if(b.first >= farDown[u].first){
            farDown[u] = b;
        }
        if(c.first >= farDown[u].first){
            farDown[u] = c;
        }*/
    }
}
void setFarUpRec(int u){
    if(u != -1){
        pair<int, int> a, b, c;

        a = {0, u};

        (parent[u] == -1) ? b = {-1, u}
                          : b = {farUp[parent[u]].first + 1, farUp[parent[u]].second};

        int sibling = -1;
        if(parent[u] != -1){ // not a root
            if(lchild[parent[u]] != u){
                sibling = lchild[parent[u]];
            } else {
                sibling = rchild[parent[u]];
            }
        }
        (sibling == -1) ? c = {-1, u}
                        : c = {farDown[sibling].first + 2, farDown[sibling].second};

        farUp[u] = max(a, max(b, c));
        /*if(b.first >= farUp[u].first){
            farUp[u] = b;
        }
        if(c.first >= farDown[u].first){
            farUp[u] = c;
        }*/

        setFarUpRec(lchild[u]);
        setFarUpRec(rchild[u]); // preorder
    }
}
void fillFar(){
    for(int i = 1; i <= n; ++i) {
        far[i] = max(farUp[i], farDown[i]);
    }
}

int giveDistantNode(int u, int d){
    int dmax = far[u].first;
    int v = far[u].second;

    if(d > dmax) return -1; // no node this far from u

    // lowest common ancestor for u and its furthest node
    int l = lowestCommonAncestor(u, v);

    int d1 = depth[u] - depth[l];
    //int d2 = depth[v] - depth[lchild];

    if(d <= d1){
        return ancestor(u, d);
    } else {
        return ancestor(v, dmax - d);
    }
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(nullptr);
    int i;
    cin >> n;
    logn = floor(log2(n));
    parent[1] = -1;
    depth[1] = 0;

    for(i = 1; i <= n; i++){
        cin >> lchild[i] >> rchild[i];
        if(lchild[i] != -1){
            parent[lchild[i]] = i;
        }
        if(rchild[i] != -1){
            parent[rchild[i]] = i;
        }
    }

    setDepthRec(1, 0);
    fillLinks();

    setFarDownRec(1);
    setFarUpRec(1);
    fillFar();

    cin >> m;
    for(i = 1; i <= m; i++){
        int u, d;
        cin >> u >> d;
        cout << giveDistantNode(u, d) << endl;
    }
    return 0;
}
