// boj 11053 가장 긴 증가하는 부분 수열 
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int N;
    cin >> N;
    vector<int> A(N);
    vector<int> D(N, 1);

    for (int i = 0; i < N; i++) {
        cin >> A[i];
    }

    for (int i = 1; i < N; i++) {
        for (int j = 0; j < i; j++) {
            if (A[j] < A[i]) {
                D[i] = max(D[i], D[j] + 1);
            }
        }
    }

    int max_length = *max_element(D.begin(), D.end());
    cout << max_length;

    return 0;
}
