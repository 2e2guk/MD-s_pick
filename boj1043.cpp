// boj 1043 거짓말
#include <iostream>
#include <vector>

using namespace std;

class UnionFind {
public:
    UnionFind(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++) {
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

int main() {
    int N, M, num_of_known, truth_teller, party_size, member;
    cin >> N >> M;

    UnionFind uf(N + 1);

    cin >> num_of_known;
    for (int i = 0; i < num_of_known; i++) {
        cin >> truth_teller;
        uf.unionSets(0, truth_teller);
    }

    vector<vector<int>> parties(M);

    for (int i = 0; i < M; i++) {
        cin >> party_size;
        if (party_size == 0) {
            continue;
        }

        cin >> member;
        parties[i].push_back(member);
        for (int j = 1; j < party_size; j++) {
            int temp;
            cin >> temp;
            parties[i].push_back(temp);
            uf.unionSets(member, temp);
        }
    }

    int max_lie_parties = 0;
    for (const auto& party : parties) {
        bool can_lie = true;
        for (const auto& person : party) {
            if (uf.find(person) == uf.find(0)) {
                can_lie = false;
                break;
            }
        }
        if (can_lie) {
            max_lie_parties++;
        }
    }

    cout << max_lie_parties << endl;

    return 0;
}
