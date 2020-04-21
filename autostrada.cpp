#include <iostream>
#include <map>
#include <vector>

using namespace std;

map<int, int>& segments(){
    static map<int, int> segments;
    return segments;
}
vector<int> keysToDelete;
map<int, int>& keysToSet(){
    static map<int, int> keysToSet_;
    return keysToSet_;
}
int n, m, l, r, counter = 0;
char color;

void insert(int l, int r, bool white){
    map<int, int>::iterator dummyIT = segments().upper_bound(r);
    map<int, int>::reverse_iterator i(dummyIT); // wskazuje na element poprzedni - przed pierwszym wiekszym
    int tmp, left, right;

    for(; i != segments().rend() && right >= l; i++){
        left = i->first; right = i->second;

        if(left < l && right > r){
            keysToSet()[left] = l - 1;
            keysToSet()[r + 1] = right;
            counter -= r - l + 1;
        }
        else if(left < l && right >= l){
            counter -= right - l + 1;
            keysToSet()[left] = l - 1;
        }
        else if(left >= l && right > r){
            keysToDelete.push_back(left);
            counter -= r - left + 1;
            keysToSet()[r + 1] = right;
        }
        else if(left >= l){
            keysToDelete.push_back(left);
            counter -= right - left + 1;
        }
    }

    tmp = keysToDelete.size();
    while(tmp > 0){
        tmp --;
        segments().erase(keysToDelete[tmp]);
        keysToDelete.pop_back();
    }

    for(auto it = keysToSet().begin(); it != keysToSet().end(); it++)
        segments()[it->first] = it->second;

    keysToSet().clear();

    if(white){
        segments()[l] = r;
        counter += r - l + 1;
    }
}

int main(){
    ios_base::sync_with_stdio(0);

    cin >> n >> m;

    for(int i = 0; i < m; i++){
        cin >> l >> r >> color;
        insert(l, r, color == 'B');
        cout << counter << endl;
    }
}



/*#include <iostream>
#include<set>

using namespace std;

const int NMAX = 1000000;
int lazy[3 * NMAX + 1][2] = {{0}};
int D[3 * NMAX + 1][2] = {{0}};

class intervalTree {
public:
    int n;


    void clean(int node, int l, int r) {
        if (l <= r) {
            D[node][0] = r - l + 1;
            D[node][1] = 0;
            int m = (l + r) / 2;
            if (l != r) {
                clean(2 * node, l, m);
                clean(2 * node + 1, m + 1, l);
            }
        }
    }

    void init(int n) {

        *//*for (int i = 0; i <= 4 * n; ++i) {
            for (int j = 0; j < 2; ++j) {
                lazy[i][j] = 0;
            }
        }*//*


        clean(1, 1, n);
    }

    void printLazy() {
        for (int i = 1; i <= 7; ++i) {
            cout << "d " << i << ": " << D[i][0] << " " << D[i][1] << endl;
            cout << "lazy " << i << ": " << lazy[i][0] << " " << lazy[i][1] << endl;
        }
    }

    void _update(int node, int nstart, int nend, int color, int L,
                 int R) {// l, r current node interval; L, R interval painted
        //this->printLazy();
        if (lazy[node][0] != 0 || lazy[node][1] != 0) {
            // This node needs to be updated
            D[node][0] = lazy[node][0];    // Update it
            D[node][1] = lazy[node][1];    // Update it
            if (nstart != nend) {
                lazy[int(node << 1)][0] = lazy[node][0] / 2 + lazy[node][0] % 2;                  // Mark child as lazy
                lazy[int(node << 1)][1] = lazy[node][1] / 2 + lazy[node][1] % 2;                  // Mark child as lazy
                lazy[(int(node << 1) | 1)][0] = lazy[node][0] / 2;                // Mark child as lazy
                lazy[(int(node << 1) | 1)][1] = lazy[node][1] / 2;                // Mark child as lazy
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
                lazy[int(node << 1)][color] = (nend - nstart + 1) / 2 + (nend - nstart + 1) % 2;
                lazy[int(node << 1)][!color] = 0;
                lazy[(int(node << 1) | 1)][color] = (nend - nstart + 1) / 2;
                lazy[(int(node << 1) | 1)][!color] = 0;
            }
        } else {
            //pushDown(node);
            if (nstart != nend) {
                int nmiddle = (nend + nstart) / 2;
                _update(int(node << 1), nstart, nmiddle, color, L, R);
                _update((int(node << 1) | 1), nmiddle + 1, nend, color, L, R);
                D[node][0] = D[int(node << 1)][0] + D[(int(node << 1) | 1)][0];
                D[node][1] = D[int(node << 1)][1] + D[(int(node << 1) | 1)][1];
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
                lazy[int(node << 1)][0] = lazy[node][0] / 2 + lazy[node][0] % 2;                  // Mark child as lazy
                lazy[int(node << 1)][1] = lazy[node][1] / 2 + lazy[node][1] % 2;                  // Mark child as lazy
                lazy[(int(node << 1) | 1)][0] = lazy[node][0] / 2;                // Mark child as lazy
                lazy[(int(node << 1) | 1)][1] = lazy[node][1] / 2;                // Mark child as lazy
            }
            lazy[node][0] = lazy[node][1] = 0;                                  // Reset it
        } else if (L <= nstart && nend <= R) {
            return D[node][1]; // whites
        } else {
            int nmiddle = (nend + nstart) / 2;
            return _query(int(node << 1), nstart, nmiddle, L, R) + _query((int(node << 1) | 1), nmiddle + 1, nend, L, R);
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
        if (color == 'C') autobahn.update(0, start, ending); // black
        else autobahn.update(1, start, ending); // white
        cout << D[1][1] << endl;
    }
    return 0;
}*/


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
                        newStart = prevStart*//*
*/
/*std::min(prevStart, start)*//*
*/
/*, newEnding = std::min(nextEnding, ending);
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
 *//*


*/
