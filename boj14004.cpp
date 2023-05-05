// boj 14004 가장 긴 증가하는 부분 수열 4
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void go(int p, const vector<int>& v, const vector<int>& a) {
    if (p == -1) {
        return;
    }
    go(v[p], v, a);
    cout << a[p] << ' ';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    vector<int> d(n, 0);
    vector<int> v(n, -1);
    for (int i = 0; i < n; i++) {
        d[i] = 1;
        for (int j = 0; j < i; j++) {
            if (a[j] < a[i] && d[j] + 1 > d[i]) {
                d[i] = d[j] + 1;
                v[i] = j;
            }
        }
    }

    int ans = *max_element(d.begin(), d.end());
    int p = find(d.begin(), d.end(), ans) - d.begin();
    cout << ans << "\n";
    go(p, v, a);

    return 0;
}
