#include <iostream>
using namespace std;
unsigned long mod = 1000000000;

int main(){
    std::ios::sync_with_stdio(false);
    int n, d;
    cin >> n;
    cin >> d;
    int B[n+1][2]; // input
    for(int i = 1; i <= n; ++i){
        int x, y;
        cin >> x;
        cin >> y;
        B[i][0] = x;
        B[i][1] = y;
    }

    unsigned long M[2][n+1];
    M[0][0] = 0;
    M[1][0] = 0;
    for (int j = 1; j <= n; ++j) {
        M[0][j] = (M[0][B[j][0]] +  M[0][B[j][1]] + 2)%mod;
    }
    int i;
    for(i = 1; i <= d-1; ++i){
        for (int j = 1; j <= n; ++j) {
            M[i%2][j] = (M[(i-1)%2][B[j][0]] +  M[(i-1)%2][B[j][1]])%mod;
        }
    }
    cout << M[(i-1)%2][n]%mod;

   /* unsigned long M[2][n+1];
    for(int i = 0; i <= 1; ++i) {
        for (int j = 0; j <= n; ++j) {
            M[i][j] = 0;
        }
    }
    M[0][n] = 1;

    unsigned long suma = 0;

    for(int i = 0; i < n; ++i) {
        for (int j = 1; j <= n; ++j) {
            M[(i+1)%2][B[j][0]] += M[i%2][j];
            M[(i+1)%2][B[j][1]] += M[i%2][j];
        }
        for (int j = 0; j <= n; ++j) {
            if(i+1 >= d) {
                suma = (suma + M[(i + 1) % 2][j])%mod;
            }
            M[i%2][j] = 0;
        }
    }*/

    return 0;

}