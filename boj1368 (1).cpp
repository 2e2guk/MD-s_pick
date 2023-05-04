// boj 1368 물대기
// 3624KB, 12ms
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

int prim_opt(int start, const vector<vector<int>>& adj_matrix, const vector<int>& rice_paddy) {
    int n = adj_matrix.size();
    int mst_weight = 0;
    vector<bool> visited(n, false);
    priority_queue<Edge> pq;

    // 각 정점을 방문하는 데 드는 비용을, 가상의 0번 정점을 만들어서, 각 정점까지 이어지는 간선의 비용으로 치환한다.
    // 이렇게 하면 자동으로 가장 방문 비용이 작은 정점부터 시작할 수 있다. 
    for (int i = 1; i < n; i++) {
        pq.push({0, i, rice_paddy[i]});
    }

    while (!pq.empty()) {
        Edge edge = pq.top();
        pq.pop();
        
        if (!visited[edge.v]) {
            visited[edge.v] = true;
            mst_weight += edge.weight;
            
            for (int j = 1; j < n; j++) {
                if (!visited[j] && adj_matrix[edge.v][j] < rice_paddy[j]) {
                    pq.push({edge.v, j, adj_matrix[edge.v][j]});
                }
            }
        }
    }
    
    return mst_weight;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    // 논에 물을 대는 데 필요한 비용을 저장할 vector
    vector<int> rice_paddy(n + 1, 0);
    vector<vector<int>> adj_matrix(n + 1, vector<int>(n + 1, 0));
    for (int i = 1; i <= n; i++) {
        cin >> rice_paddy[i];
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> adj_matrix[i][j];
        }
    }
    int min_cost = prim_opt(0, adj_matrix, rice_paddy);
    cout << min_cost;
    return 0;
}
