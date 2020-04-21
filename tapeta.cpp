#include <iostream>
using namespace std;

int main() {

    string tapeta;
    cin >> tapeta;

    int min = 1000000;
    int poprzednik = 0;
    int wynik = 1;

    while(poprzednik < tapeta.length() && tapeta[poprzednik] == '*') poprzednik++;

    if(poprzednik == tapeta.length()){
        cout << wynik;
        return 0;
    }

    bool rozne = false;

    for(int i = poprzednik+1; i < tapeta.length(); i++){

        if(tapeta[i] != '*'){
            if(tapeta[i] != tapeta[poprzednik]){
                if((i-poprzednik) < min){
                    min = i-poprzednik;
                }
                rozne = true;
            }
            poprzednik = i;
        }
    }

    if(rozne) wynik = tapeta.length() - min + 1;

    cout << wynik;

    return 0;
}