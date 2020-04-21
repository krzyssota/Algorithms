#include <bits/stdc++.h>

using namespace std;
static const int N = 200001;
int n;

vector<vector<pair<int, int>>> graph;   // index - from, p.fst - to, p.scd - dist

uint64_t max_dist;
uint64_t min_dist;
int d1, d2;
int start;

uint64_t distances[N];

void DFS(int curr) {
    for (auto p : graph[curr]) {
        if (distances[p.first] == 0 && p.first != start) {
            distances[p.first] = p.second + distances[curr];

            DFS(p.first);
        }
    }
}

void DFS2(int curr) {
    for (auto p : graph[curr]) {
        if (distances[curr] > distances[p.first]) {
            if (max(distances[d1] - distances[p.first], distances[p.first]) < min_dist) {
                min_dist = max(distances[d1] - distances[p.first], distances[p.first]);
                start = p.first;
            } else if (max(distances[d1] - distances[p.first], distances[p.first])
                       <= min_dist && p.first < curr) {
                start = p.first;
            }

            DFS2(p.first);
        }
    }
}

void find_max() {
    for (size_t i = 1; i < n; i++) {
        if (distances[i] > max_dist) {
            d1 = i;
            max_dist = distances[i];
        }
    }

    max_dist = 0;
}

void clear_dist() {
    for (size_t i = 1; i < n; i++) {
        distances[i] = 0;
    }
}

int main() {
    ios::sync_with_stdio(false);

    cin >> n;
    n++;
    graph.reserve(n);

    for (int i = 2; i < n; i++) {
        int temp1, temp2, dist;
        cin >> temp1 >> temp2 >> dist;

        graph[temp1].emplace_back(temp2, dist);
        graph[temp2].emplace_back(temp1, dist);
    }

    start = 1;
    DFS(start);
    find_max();
    d2 = d1;
    clear_dist();

    start = d2;
    DFS(start);
    find_max();

    min_dist = UINT64_MAX;

    DFS2(d1);

    cout << start << '\n';

    return 0;
}