#include <bits/stdc++.h>

using namespace std;

using ull = uint64_t;
using coordinates = pair<ull, ull>;
using island_id = ull;
using dist = ull;
using que_elem = pair<dist, island_id>;
#define x_coord first.first
#define y_coord first.second
#define id second
#define N_MAX 200000


int n;
vector<pair<coordinates, island_id>> islands(N_MAX);
vector<dist> distances(N_MAX);
vector<vector<island_id>> neighbours(N_MAX);
vector<pair<ull, island_id>> x_coordinates;
vector<pair<ull, island_id>> y_coordinates;
priority_queue<pair<dist, island_id>> que;
vector<bool> colored(N_MAX);


dist hours_between(island_id id_1, island_id id_2) {
    return min(abs((long long)(islands[id_1].x_coord - islands[id_2].x_coord)), abs((long long)(islands[id_1].y_coord - islands[id_2].y_coord)));
}

int main() {
    std::ios::sync_with_stdio(false);
    cin >> n;

    for (int i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;
        islands.emplace_back(make_pair(a, b), i);
        distances[i] = UINT64_MAX;
        colored[i] = false;
    }

    for (int j = 0; j < n; ++j) {
        x_coordinates.emplace_back(islands[j].x_coord, j);
        y_coordinates.emplace_back(islands[j].y_coord, j);
    }
    sort(x_coordinates.begin(), x_coordinates.end());
    sort(y_coordinates.begin(), y_coordinates.end());

    neighbours[x_coordinates[0].id].push_back(x_coordinates[1].id);
    neighbours[y_coordinates[0].id].push_back(y_coordinates[1].id);
    for (int j = 1; j < n-1; ++j) {
        neighbours[x_coordinates[j].id].push_back(x_coordinates[j-1].id);
        neighbours[x_coordinates[j].id].push_back(x_coordinates[j+1].id);
        neighbours[y_coordinates[j].id].push_back(y_coordinates[j-1].id);
        neighbours[y_coordinates[j].id].push_back(y_coordinates[j+1].id);
    }
    neighbours[x_coordinates[n-1].id].push_back(x_coordinates[n-2].id);
    neighbours[y_coordinates[n-1].id].push_back(y_coordinates[n-2].id);

    // koniec prepreoccesingu
    que.emplace(distances[0], 0);
    while(!que.empty()) {
        auto curr_island = que.top();
        que.pop();

        if(colored[curr_island.id]) continue;
        colored[curr_island.id] = true;

        if(curr_island.id == n - 1) {
            cout << curr_island.first;
            break;
        }

        for(auto n_id : neighbours[curr_island.id]) {
            /*auto new_dist = distances[curr_island.id] + hours_between(curr_island.id, n_id);
            if(distances[n_id] == UINT32_MAX) {
                distances[n_id] = new_dist;
                que.emplace(distances[n_id], n_id);
            } else {
                if(distances[n_id] > new_dist) {
                    distances[n_id] = new_dist;
                    que.emplace(distances[n_id], n_id);
                }
            }*/
            if (!colored[n_id]) {
                auto new_dist = distances[curr_island.id] + hours_between(curr_island.id, n_id);
                distances[n_id] = min(distances[n_id], new_dist);
                que.emplace(distances[n_id], n_id);
            }
        }
    }

    return 0;
}