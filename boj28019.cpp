#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <unordered_map>
#include <algorithm>
#include <limits>

using namespace std;

const long long LLONG_MAX = numeric_limits<long long>::max();

class UnionFind {
public:
    UnionFind(int n) {
        rank.resize(n + 1, 0);
        parent.resize(n + 1);
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
        if (rank[rootX] > rank[rootY]) {
            parent[rootY] = rootX;
        } else {
            parent[rootX] = rootY;
            if (rank[rootX] == rank[rootY]) {
                rank[rootY]++;
            }
        }
    }
private:
    vector<int> rank;
    vector<int> parent;
};

struct Edge {
    int u, v;
    long long weight;

    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }

};

pair<long long, vector<Edge>> kruskal_opt(int n, const vector<Edge>& edges) {
    vector<Edge> mst_edges;
    long long mst_weight = 0;
    UnionFind uf(n);
    priority_queue<Edge> pq(edges.begin(), edges.end());

    while (!pq.empty()) {
        Edge edge = pq.top();
        pq.pop();
        if (uf.find(edge.u) != uf.find(edge.v)) {
            mst_weight += edge.weight;
            mst_edges.push_back(edge);
            uf.UnionSets(edge.u, edge.v);
        }
    }
    return make_pair(mst_weight, mst_edges);
}

vector<vector<pair<int, long long>>> create_adj_list(int n, const vector<Edge>& mst_edges) {
    vector<vector<pair<int, long long>>> adj_list(n + 1);
    for (const auto& edge : mst_edges) {
        adj_list[edge.u].emplace_back(edge.v, edge.weight);
        adj_list[edge.v].emplace_back(edge.u, edge.weight);
    }
    return adj_list;
}

long long dfs(int node, int parent, const vector<vector<pair<int, long long>>>& adj, long long cur_sum) {
    if (adj[node].size() == 1 && adj[node][0].first == parent) {
        return cur_sum;
    }

    long long max_subtree_dist = 0;
    for (const auto& [neighbor, weight] : adj[node]) {
        if (neighbor != parent) {
            max_subtree_dist = max(max_subtree_dist, dfs(neighbor, node, adj, cur_sum + weight));
        }
    }

    return max_subtree_dist;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, e, start;
    cin >> n >> e;
    vector<Edge> edges;

    for (int i = 0; i < e; i++) {
        Edge edge;
        cin >> edge.u >> edge.v >> edge.weight;
        edges.push_back(edge);
    }
    cin >> start;

    pair<long long, vector<Edge>> mst = kruskal_opt(n, edges);

    vector<vector<pair<int, long long>>> adj_list = create_adj_list(n, mst.second);

    long long max_dist = dfs(start, -1, adj_list, 0);

    cout << mst.first * 2 - max_dist;
    return 0;
}

