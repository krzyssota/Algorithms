#include <iostream>
#include<set>
using namespace std;

const int NMAX = 1000000;
int lazy[3*NMAX+1][2];
int D[3*NMAX+1][2];

class intervalTree {
public:
    int n;
    /*int **lazy;
    int **D;*/

    void clean(int node, int l, int r) {
        if (l <= r) {
            D[node][0] = r-l+1;
            D[node][1] = 0;
            int m = (l + r) / 2;
            if (l != r) {
                clean(2 * node, l, m);
                clean(2 * node + 1, m + 1, l);
            }
        }
    }

    void init(int n) {
       /* lazy = new int*[4*n + 1];
        D = new int*[4*n + 1];
        *//*int **a = new int*[4*n];
        int **b = new int*[4*n];*//*
        for(int i = 0; i <= 4*n; ++i) {
            *//*a[i] = new int[2];
            b[i] = new int[2];
            D[i] = a[i];
            lazy[i] = b[i];*//*
            D[i] = new int[2];
            lazy[i] = new int[2];
            for (int j = 0; j < 2; ++j) {
                lazy[i][j] = 0;
            }
        }*/

        clean(1, 1, n);
    }

    void printLazy(){
        for(int i = 1; i <= 7; ++i) {
                cout << "d " << i << ": " << D[i][0] << " " << D[i][1] << endl;
                cout << "lazy " << i << ": " << lazy[i][0] << " " << lazy[i][1] << endl;
        }
    }

    void _update(int node, int nstart, int nend, int color, int L, int R) {// l, r current node interval; L, R interval painted
        //this->printLazy();
        if (lazy[node][0] != 0 || lazy[node][1] != 0) {
            // This node needs to be updated
            D[node][0] = lazy[node][0];    // Update it
            D[node][1] = lazy[node][1];    // Update it
            if (nstart != nend) {
                lazy[node * 2][0] = lazy[node][0]/2 + lazy[node][0]%2;                  // Mark child as lazy
                lazy[node * 2][1] = lazy[node][1]/2 + lazy[node][1]%2;                  // Mark child as lazy
                lazy[node * 2 + 1][0] = lazy[node][0]/2;                // Mark child as lazy
                lazy[node * 2 + 1][1] = lazy[node][1]/2;                // Mark child as lazy
            }
            lazy[node][0] = lazy[node][1] = 0;                                  // Reset it
        }
        if (nstart > nend || R < nstart) {
            return;
        } else if (L <= nstart && nend <= R) {
            D[node][color] = nend - nstart + 1;
            D[node][!color] = 0;
            if (nstart != nend) { // Not leaf node
                // node*2 interval length -> (nend-nstart+1)/2 + (nend-nstart+1)%2
                lazy[node * 2][color] = (nend-nstart+1)/2 + (nend-nstart+1)%2;
                lazy[node * 2][!color] = 0;
                lazy[node * 2 + 1][color] = (nend-nstart+1)/2;
                lazy[node * 2 + 1][!color] = 0;
            }
        } else {
            //pushDown(node);
            if (nstart != nend && nend <= n) {
                int nmiddle = (nend+nstart)/2;
                _update(2 * node, nstart, nmiddle, color, L, R);
                _update(2 * node + 1, nmiddle + 1, nend, color, L, R);
                D[node][0] = D[node * 2][0] + D[node * 2 + 1][0];
                D[node][1] = D[node * 2][1] + D[node * 2 + 1][1];
            }
            //pushUp(node);
        }
    }

    void update(int color, int L, int R) {
        _update(1, 1, n, color, L, R);
    }

    int _query(int node, int nstart, int nend, int L, int R) {
        if (nstart > nend || R < nstart) {
            return 0;
        }
        if (lazy[node][0] != 0 || lazy[node][1] != 0) {
            // This node needs to be updated
            D[node][0] = lazy[node][0];    // Update it
            D[node][1] = lazy[node][1];    // Update it
            if (nstart != nend) {
                lazy[node * 2][0] = lazy[node][0]/2 + lazy[node][0]%2;                  // Mark child as lazy
                lazy[node * 2][1] = lazy[node][1]/2 + lazy[node][1]%2;                  // Mark child as lazy
                lazy[node * 2 + 1][0] = lazy[node][0]/2;                // Mark child as lazy
                lazy[node * 2 + 1][1] = lazy[node][1]/2;                // Mark child as lazy
            }
            lazy[node][0] = lazy[node][1] = 0;                                  // Reset it
        }
        else if (L <= nstart && nend <= R) {
            return D[node][1]; // whites
        } else {
            int nmiddle = (nend+nstart)/2;
            return _query(2 * node, nstart, nmiddle, L, R) + _query(2 * node + 1, nmiddle + 1, nend, L, R);
        }
    }

    int query(int i, int j) { // od i włącznie do j włącznie
        if (i <= j) {
            return _query(1, 1, n, i, j);
        } else {
            return 0;
        }
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    int n, m;
    cin >> n;
    cin >> m;

    intervalTree autobahn;
    autobahn.n = n;
    autobahn.init(n);

    int start, ending;
    char color;
    for (int i = 0; i < m; ++i) {
        cin >> start >> ending >> color;
        if(color == 'C') autobahn.update(0, start, ending); // black
        else autobahn.update(1, start, ending); // white
        cout << autobahn.query(1, n) << endl;
    }
    return 0;
}


/*int main(){
    std::ios::sync_with_stdio(false);
    int n, m;
    cin >> n;
    cin >> m;
    std::set<pair<int, int>> autobahn;
    int whites = 0;

    //int A[n][3]; // 0->white, 1->black
    for(int i = 0; i < n; ++i){
        int start, ending;
        char color;
        cin >> start >> ending >> color;

        if(color == 'B') {
            int newStart, newEnding;

            if(autobahn.empty()){
                newStart = start;
                newEnding = ending;
            }

            auto it = autobahn.lower_bound(pair(start, ending)); // first not lesser

            if(it != autobahn.end()) {

                int nextStart = it->first, nextEnding = it->second;

                if (it != autobahn.begin()) { // there is sth before

                    auto itPrev = it--;
                    int prevStart = itPrev->first, prevEnding = itPrev->second;
                    //it++;
                    if(start <= prevEnding && nextStart <= ending){
                        newStart = prevStart*//*std::min(prevStart, start)*//*, newEnding = std::min(nextEnding, ending);
                    }
                    else if(1){}
                }
                else {
                     newStart = start;
                     newEnding = std::max(ending, nextEnding);
                     autobahn.erase(it);
                }
            }
            autobahn.insert(std::pair(newStart, newEnding));
        }

    }
    return 0;
}
 */

