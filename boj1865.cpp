// boj 1865 웜홀
#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int INF = 987654321;

vector<int> bellman_ford(int start, const vector<vector<pair<int, int>>>& graph) {
    int n = graph.size();
    vector<int> dist(n, INF);
    dist[start] = 0;

    for (int i = 0; i < n; i++) {
        for (int u = 0; u < n; u++) {
            if (dist[u] == INF) continue;

            for (const auto& edge : graph[u]) {
                int v = edge.first;
                int w = edge.second;
                if (dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    if (i == n - 1) {
                        return {};
                    }
                }
            }
        }
    }

    return dist;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int test_case_num;
    cin >> test_case_num;
    vector<string> ans;
    while (test_case_num--) {
        int n, m, w;
        cin >> n >> m >> w;

        vector<vector<pair<int, int>>> graph(n + 1);

        // 가상의 시작 지점 0에서 각 정점으로 가는 간선 추가
        for (int i = 1; i <= n; i++) {
            graph[0].push_back({i, 0});
        }

        for (int i = 0; i < m; i++) {
            int u, v, w;
            cin >> u >> v >> w;
            graph[u].push_back({v, w});
            graph[v].push_back({u, w});
        }
        // 웜홀 정보 입력
        while (w--) {
            int s, e, t;
            cin >> s >> e >> t;
            graph[s].push_back({e, -t});
        }

        vector<int> shortest_distances = bellman_ford(0, graph);

        if (shortest_distances.empty()) {
            ans.push_back("YES");
        } else {
            ans.push_back("NO");
        }
    }
    for (const auto& ele : ans) {
        cout << ele << "\n";
    }
    return 0;
}
