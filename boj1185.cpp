// boj 1185 유럽 여행
#include <iostream>
#include <vector>
#include <queue>
#include <utility>

using namespace std;

struct Edge {
    int u, v, weight;

    bool operator<(const Edge& other) const {
        return weight > other.weight;
    }
};

int prim_opt(int n, int start_vertex, vector<vector<pair<int, int>>>& adj_list) {
    int mst_weight = 0;
    vector<bool> visited(n + 1, false);
    visited[start_vertex] = true;

    priority_queue<Edge> pq;
    for (const auto& edge : adj_list[start_vertex]) {
        pq.push({start_vertex, edge.first, edge.second});
    }

    while (!pq.empty()) {
        Edge edge = pq.top();
        pq.pop();

        if (!visited[edge.v]) {
            visited[edge.v] = true;
            mst_weight += edge.weight;
        

            for (const auto& next_edge : adj_list[edge.v]) {
                if (!visited[next_edge.first]) {
                    pq.push({edge.v, next_edge.first, next_edge.second});
                }
            }
        }
    }
        return mst_weight;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, e;
    cin >> n >> e;

    vector<vector<pair<int, int>>> graph(n + 1);
    vector<int> city_cost(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        cin >> city_cost[i];
    }

    int min_cost_index = 1;
    for (int i = 2; i <= n; i++) {
        if (city_cost[i] < city_cost[min_cost_index]) {
            min_cost_index = i;
        }
    }

    for (int i = 0; i < e; i++) {
        int startidx, endidx, weight;
        cin >> startidx >> endidx >> weight;
        graph[startidx].push_back({endidx, (2 * weight) + city_cost[startidx] + city_cost[endidx]});
        graph[endidx].push_back({startidx, (2 * weight) + city_cost[startidx] + city_cost[endidx]});
    }

    int res = prim_opt(n, min_cost_index, graph);
    cout << res + city_cost[min_cost_index] << "\n";
    return 0;
}