#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;
vector<int> countZeroRuns(const vector<int>& arr) {
    vector<int> result;
    int count = 0;

    for (int x : arr) {
        if (x == 0) count++;
        else {
            if (count > 0) result.push_back(count);
            count = 0;
        }
    }
    if (count > 0) result.push_back(count);

    return result;
}

int main() {
    int n, k;
    cin >> n >> k;

    vector<int> arr(n);
    for (int i = 0; i < n; i++) cin >> arr[i];

    int first = 0, last = n - 1;
    while (first < n && arr[first] == 0) first++;
    while (last >= 0 && arr[last] == 0) last--;

    vector<int> mid;
    for (int i = first; i <= last; ++i) mid.push_back(arr[i]);

    vector<int> runs = countZeroRuns(mid);

    vector<long double> coef(k);
    for (int i = 0; i < k; i++) {
        cin >> coef[i];
    }

    int R = runs.size();
    int K = min(k, R);

    const long double NEG = -1e300L;
    vector<long double> dp(K + 1, NEG);
    dp[0] = 0.0L;

    for (int i = 0; i < R; i++) {
        int len = runs[i];
        for (int j = min(i + 1, K); j >= 1; j--) {
            long double candidate = dp[j - 1] + (long double)len * coef[j - 1];
            if (candidate > dp[j]) dp[j] = candidate;
        }
    }

    long double ans = 0.0L;
    for (int j = 0; j <= K; j++)
        if (dp[j] > ans) ans = dp[j];

    cout << fixed << setprecision(10) << ans << '\n';
}
