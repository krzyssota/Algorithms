#include <iostream>
#include <array>
#include <algorithm>
#include <map>


using LL = unsigned long long;
using namespace std;
static const int mod = 1e9;

class intervalTree {
public:
    int n;
     int* D;

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
       /* } else if ( i == j){
            return _query(1, 1, n, j) - _query(1, 1, n, i-1);*/
        } else {
            return 0;
        }
    }

    /*int _lookup(int node, int l, int r, int i) {
        if (l == r && r == i) {
            return D[node];
        } else {
            int m = (l + r) / 2;
            if (i <= m){
                return  _lookup(2*node, l, m, i);
            } else {
                return  _lookup(2*node + 1, m+1, r, i);
            }
        }
    }

        int lookup(int i) {
            return _lookup(1, 1, n, i);
        }*/

};

int main(){
    std::ios::sync_with_stdio(false);
    int n, k;
    cin >> n;
    cin >> k;

    int A[n+1], A_p[n+1];
    for(int i = 1; i <= n; i++){
        cin >> A[i];
        A_p[A[i]] = i;
    }

    intervalTree trees[k+1];

    for(int i = 1; i <= k; i++){

        intervalTree iT;
        iT.D = new int[4*n];
        iT.n = n;
        iT.init(n);

        trees[i] = iT;
    }


    for (int i = n; i >= 1; --i) {
        int wartosc = i;
        int indeks = A_p[i];
        trees[1].update(indeks, 1);
        for (int j = 2; j <= k; ++j) {
            trees[j].update(indeks, trees[j-1].query(1, indeks-1));
        }
        /*//debug
        for(int i = 1; i <= k; i++){
            for(int j = 1; j <= n; j++){
                cout << trees[i].lookup(j) << ' ';
            }
            cout << endl;
        }
        cout << endl;*/
    }

    cout << trees[k].query(1, n) << endl;

    for(int i = 1; i <= k; i++){
        delete[] trees[i].D;
    }

    return 0;
}

