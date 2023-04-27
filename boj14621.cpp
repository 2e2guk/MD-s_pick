//boj 14621 나만 안되는 연애
#include <iostream>
#include <vector>
#include <queue>
#include <utility>

using namespace std;

class UnionFind {
public:
    UnionFind(int n) {
        parent.resize(n + 1);
        rank.resize(n + 1, 0);
        for (int i = 1; i <= n; i++) {
            parent[i] = i;
        }
    }
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }
    void UnionSets(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX != rootY) {
            if (rank[rootX] > rank[rootY]) {
                parent[rootY] = rootX;
            } else {
                parent[rootX] = rootY;
                if (rank[rootX] == rank[rootY]) {
                    rank[rootY]++;
                }
            }
        }
    }

private:
    vector<int> parent;
    vector<int> rank;
};
struct Edge {
    int u, v, weight;

    bool operator<(const Edge& other) const {
        return weight > other.weight;
    }
};
pair<int, vector<Edge>> kruskal_opt(int n, const vector<Edge>& edges, vector<bool>& gender) {
    UnionFind uf(n);
    int mst_weight = 0;
    vector<Edge> mst_edges;
    priority_queue<Edge> pq(edges.begin(), edges.end());
    
    while (!pq.empty()) {
        Edge edge = pq.top();
        pq.pop();
        if (uf.find(edge.u) != uf.find(edge.v) && (gender[edge.u] != gender[edge.v])) {
            mst_weight += edge.weight;
            mst_edges.push_back(edge);
            uf.UnionSets(edge.u, edge.v);
        }
    }
    if (mst_edges.size() == n - 1) {
        return make_pair(mst_weight, mst_edges);
    } else {
        return make_pair(-1, vector<Edge>());
    }
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, M;
    cin >> N >> M;
    vector<bool> gender(N + 1, false);
    vector<Edge> edges;
    for (int i = 0; i < N; i++) {
        char input;
        cin >> input;
        if (input == 'M') {
            gender[i + 1] = true;
        }
    }
    for (int i = 0; i < M; i++) {
        Edge edge;
        cin >> edge.u >> edge.v >> edge.weight;
        edges.push_back(edge);
    }
    pair<int, vector<Edge>> res = kruskal_opt(N, edges, gender);
    cout << res.first;
    return 0;
}
