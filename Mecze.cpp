#include <iostream>
#include <cstdio>
#include <math.h>
#include <array>
#include <algorithm>


int main(){
    std::ios::sync_with_stdio(false);
    int n, m;
    std::cin >> n;
    std::cin >> m;
    unsigned long long int T[n];
    for(int i = 0; i < n ; i++) T[i] = 0;

    unsigned long long int power = 1;
    for(int i = 0; i < m; i++){
        int j;
        for(j = 0; j < n/2; j++){
            int x;
            std::cin >> x;

            T[x-1] += power;
        }
        for(; j < n; j++){
            int x;
            std::cin >> x;
        }
        power = power*2;
    }
    std::sort(T, T + n);

    unsigned long long int x = T[0];
    bool difference = false;
    bool first = true;

    for(auto y:T){
        if(x == y && !first){
            difference = true;
        }
        x = y;
        if(first) first = !first;
    }
    if(!difference) std::cout << "TAK";
    else std::cout << "NIE";

    return 0;
}
