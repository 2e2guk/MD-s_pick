// boj 27945 슬슬 가지를 먹기 않으면 죽는다
// 실행 시간 280ms 메모리 17364KB
#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <set>

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

    void unionSets(int x, int y) {
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

pair<int, vector<Edge>> kruskal_opt(int n, const vector<Edge>& edges) {
    int mst_cost = 0;
    UnionFind uf(n);
    vector<Edge> mst_edges;
    priority_queue<Edge> pq(edges.begin(), edges.end());
    int edge_count = 0;

    while (!pq.empty() && edge_count < n - 1) {
        Edge edge = pq.top();
        pq.pop();

        if (uf.find(edge.u) != uf.find(edge.v)) {
            uf.unionSets(edge.u, edge.v);
            mst_cost += edge.weight;
            mst_edges.push_back(edge);
            edge_count++;
        }
    }

    return make_pair(mst_cost, mst_edges);
}

// MEX란, 주어진 집합에 포함되지 않은 가장 작은 양의 정수이다.
// 예를 들어 주어진 집합이 {0, 1, 2, 4, 5}라고 가정해보자.
// 이 경우, 3은 집합에 포함되지 않은 가장 작은 양의 정수이므로 MEX는 3이다.
int find_mex(const set<int>& weights) {
    int mex = 1;
    for (const auto& weight : weights) {
        if (weight == mex) {
            mex++;
        } else {
            break;
        }
    }
    return mex;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;

    vector<Edge> edges(m);

    for (int i = 0; i < m; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].weight;
    }

    pair<int, vector<Edge>> MST = kruskal_opt(n, edges);

    set<int> weights;
    for (const auto& edge : MST.second) {
        weights.insert(edge.weight);
    }

    int mex = find_mex(weights);
    cout << mex;

    return 0;
}
