#include "intervalTree.h"
using LL = unsigned long long;
using std;

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
            D[node] = value;
        } else {

            int m = (l + r) / 2;
            if (i <= m){
                _update(2*node, l, m, i, value);
            } else {
                _update(2*node + 1, m+1, r, i, value);
            }
            D[node] = D[2*node] + D[2*node + 1];
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
            return _query(2*node, l, m, i) + _query(2*node + 1, m+1, r, i);
        }
    }

    int query(int i, int j){ // od i włącznie do j włącznie
        if(i <= j) {
            return _query(1, 1, n, j) - _query(1, 1, n, i-1); // i-ty element sie wlicza
            /* } else if ( i == j){
                 return _query(1, 1, n, j) - _query(1, 1, n, i-1);*/
        } else {
            return 0;
        }
    }

    /* DEBUG
     int _lookup(int node, int l, int r, int i) {
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

    return 0;
}
