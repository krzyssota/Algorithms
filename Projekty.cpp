#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
/*

5 3 3
10
500
150
200
100
1 2
1 3
4 5

 */

int n, m, k;
int projects[100000];
int realCosts[100000];
std::vector<int> children[500000];

int dfs(int v){
    if(realCosts[v] == 0){
        realCosts[v] = projects[v];
        for(int child:children[v]){
            realCosts[v] = std::max(realCosts[v], dfs(child));
        }
    }
    return realCosts[v];
}

int main(){
    ios_base::sync_with_stdio(0);
    cin >> n >> m >> k;

    int i;
    for(i = 0; i < n; i++){
        realCosts[i] = 0;
        cin >> projects[i];
    }
    for(i = 0; i < m; i++){
        int parent, child;
        cin >> parent >> child;
        children[parent-1].push_back(child-1);
    }
    for(i = 0; i < n; i++){
        dfs(i);
    }
    sort(realCosts, realCosts+n);
    cout << realCosts[k-1] << endl;
    return 0;
}