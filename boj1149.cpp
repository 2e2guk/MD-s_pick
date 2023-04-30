// boj 1149 RGB거리
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int N;
    cin >> N;
    vector<vector<int>> P(N + 1, vector<int>(3, 0));
    vector<vector<int>> D(N + 1, vector<int>(3, 0));

    for (int i = 1; i <= N; i++) {
        cin >> P[i][0] >> P[i][1] >> P[i][2];
    }

    for (int i = 1; i <= N; i++) {
        D[i][0] = min(D[i - 1][1], D[i - 1][2]) + P[i][0];
        D[i][1] = min(D[i - 1][0], D[i - 1][2]) + P[i][1];
        D[i][2] = min(D[i - 1][0], D[i - 1][1]) + P[i][2];
    }

    int min_cost = min({D[N][0], D[N][1], D[N][2]});
    cout << min_cost << endl;

    return 0;
}
