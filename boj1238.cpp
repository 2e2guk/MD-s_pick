// boj 1238 파티
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const int INF = 987654321;

vector<int> dijkstra_opt(int start, vector<vector<pair<int, int>>>& graph) {
    int n = graph.size();
    vector<int> dist(n + 1, INF);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    dist[start] = 0;
    pq.push({dist[start], start});

    while (!pq.empty()) {
        int current_dist = pq.top().first;
        int current_vertex = pq.top().second;
        pq.pop();
        if (dist[current_vertex] < current_dist) continue;

        for (const auto& edge : graph[current_vertex]) {
            int neighbor_vertex = edge.first;
            int edge_weight = edge.second;
            int new_dist = current_dist + edge_weight;
            if (new_dist < dist[neighbor_vertex]) {
                dist[neighbor_vertex] = new_dist;
                pq.push({new_dist, neighbor_vertex});
            }
        }
    }
    return dist;
}
int dijkstra_opt_target(int start, int target, vector<vector<pair<int, int>>>& graph) {
    int n = graph.size();
    vector<int> dist(n + 1, INF);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    dist[start] = 0;
    pq.push({dist[start], start});
    int target_shortest_path = -1;

    while (!pq.empty()) {
        int current_dist = pq.top().first;
        int current_vertex = pq.top().second;
        pq.pop();
        if (current_vertex == target) {
            target_shortest_path = current_dist;
            break;
        }
        if (dist[current_vertex] < current_dist) continue;

        for (const auto& edge : graph[current_vertex]) {
            int neighbor_vertex = edge.first;
            int edge_weight = edge.second;
            int new_dist = current_dist + edge_weight;
            if (new_dist < dist[neighbor_vertex]) {
                dist[neighbor_vertex] = new_dist;
                pq.push({new_dist, neighbor_vertex});
            }
        }
    }
    return target_shortest_path;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, M, target;
    cin >> N >> M >> target;
    vector<int> from_target(N + 1, 0);
    vector<int> to_target;
    vector<vector<pair<int, int>>> graph(N + 1);
    for (int i = 0; i < M; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].push_back({v, w});
    }
    from_target = dijkstra_opt(target, graph);
    for (int i = 0; i <= N; i++) {
        to_target.push_back(dijkstra_opt_target(i, target, graph));
    }
    vector<int> path_time;
    for (int i = 1; i <= N; i++) {
        path_time.push_back(from_target[i] + to_target[i]);
    }
    cout << *max_element(path_time.begin(), path_time.end());
    return 0;
}