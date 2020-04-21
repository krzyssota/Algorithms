#include <iostream>
#include <string>
#include <sstream>
using namespace std;

/*void naglowek(int n){

    for( int i = -1; i < 2*n ; i++){

        if(i != -1) cout << i%n << ' ';
        else cout << "  ";
    }
    cout << endl;
    for( int i = -1; i < 2*n ; i++){
        if(i != -1) cout << '-' << '-';
        else cout << ' ';
    }
    cout << endl;
}*/

int main() {

    int n;

    string str;
    std::ios::sync_with_stdio(false);
    std::cin >> n;



    int ciag[n];
    int l[n+1][n], p[n+1][n];

    for (int j = 0; j <= n; ++j) {
        for (int i = 0; i < n; ++i) {
           l[j][i] = 0;
           p[j][i] = 0;
        }
    }

    for(int i = 0; i < n; i++){
        l[1][i] = 1;
        cin >> ciag[i];
    }


    for(int dl = 2; dl <= n; dl++) {
        for (int pocz = 0; pocz <= n - dl; pocz++){
            if(ciag[pocz] < ciag[pocz+1]){
                l[dl][pocz] = (l[dl][pocz] + l[dl-1][pocz + 1])%1000000000;
            }
            if(ciag[pocz] < ciag[pocz + dl -1]){
                l[dl][pocz] = (l[dl][pocz] + p[dl-1][pocz + 1])%1000000000;
            }

            if(ciag[pocz + dl - 1] > ciag[pocz]){
                p[dl][pocz] = (p[dl][pocz] + l[dl-1][pocz])%1000000000;
            }
            if(ciag[pocz + dl - 1] > ciag[pocz + dl-2]){
                p[dl][pocz] = (p[dl][pocz] + p[dl-1][pocz])%1000000000;
            }
        }
    }
    cout << (l[n][0] + p[n][0])%1000000000 << '\n';

/*    // debug
    for (int j = 1; j <= n; ++j) {
        cout << j << '|';
        int i = 0;
        for (; i < n; ++i) {
            cout  << l[j][i] << ' ';
        }
        for(; i < 2*n; i++){
            cout  << p[j][i%n] << ' ';
        }
        cout << '\n';
    }*/

    return 0;
}

