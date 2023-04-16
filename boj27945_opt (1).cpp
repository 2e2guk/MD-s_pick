// boj 27945 슬슬 가지를 먹지 않으면 죽는다.
// 실행 시간 252ms 메모리 17360KB
// 최적화 내용 : 가중치에 대한 정보를 set 대신 vector에 저장, MEX찾는 과정을 최적화.
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

    while (!pq.empty()) {
        Edge edge = pq.top();
        pq.pop();

        if (uf.find(edge.u) != uf.find(edge.v)) {
            uf.unionSets(edge.u, edge.v);
            mst_cost += edge.weight;
            mst_edges.push_back(edge);
        }
    }

    return make_pair(mst_cost, mst_edges);
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

    // MEX를 찾는 과정
    bool has_one = false;
    int mex = 1;

    for (const auto& edge : MST.second) {
        if (edge.weight == 1) {
            has_one = true;
        } else if (has_one && edge.weight != mex) {
            // 누락된 양의 정수인 MEX를 찾은 경우. 
            break;
        }
        mex++;
    }

    if (!has_one) {
        mex = 1;
    }

    cout << mex;

    return 0;
}
