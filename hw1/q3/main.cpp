#include <iostream>
#include <vector>

using namespace std;

static vector<long long> merge_sorted(const vector<long long>& a, const vector<long long>& b) {
    vector<long long> result;
    result.reserve(a.size() + b.size());

    size_t i = 0, j = 0;
    while (i < a.size() && j < b.size()) {
        if (a[i] <= b[j]) {
            result.push_back(a[i]);
            ++i;
        } else {
            result.push_back(b[j]);
            ++j;
        }
    }
    while (i < a.size()) {
        result.push_back(a[i]);
        ++i;
    }
    while (j < b.size()) {
        result.push_back(b[j]);
        ++j;
    }
    return result;
}

static void sort_subarray(vector<long long>& arr, int i, int k) {
    int n = static_cast<int>(arr.size());
    if (i < 0  ||k < 0  ||i + k > n) {
        throw runtime_error("Invalid i or k range");
    }

    int base = i;
    int size = k;

    auto sift_down = [&](int root, int limit) {
        while (true) {
            int left = 2 * root + 1;
            int right = left + 1;
            int largest = root;

            if (left < limit && arr[base + left] > arr[base + largest]) {
                largest = left;
            }
            if (right < limit && arr[base + right] > arr[base + largest]) {
                largest = right;
            }
            if (largest == root) break;

            long long tmp = arr[base + root];
            arr[base + root] = arr[base + largest];
            arr[base + largest] = tmp;

            root = largest;
        }
    };

    for (int start = (size / 2) - 1; start >= 0; --start) {
        sift_down(start, size);
    }

    for (int end = size - 1; end > 0; --end) {
        long long tmp = arr[base];
        arr[base] = arr[base + end];
        arr[base + end] = tmp;
        sift_down(0, end);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    if (!(cin >> n)) return 0;
    if (!(cin >> k)) return 0;

    vector<long long> arr(n);
    for (int idx = 0; idx < n; ++idx) {
        cin >> arr[idx];
    }

    for (int start = 0; start < n; start += k) {
        int chunk_len = (start + k <= n) ? k : (n - start);
        sort_subarray(arr, start, chunk_len);
    }

    vector<long long> result;
    if (n > 0) {
        int first_chunk_len = (k < n) ? k : n;
        result.assign(arr.begin(), arr.begin() + first_chunk_len);

        for (int start = k; start < n; start += k) {
            int chunk_len = (start + k <= n) ? k : (n - start);
            vector<long long> chunk;
            chunk.reserve(chunk_len);
            for (int t = 0; t < chunk_len; ++t) {
                chunk.push_back(arr[start + t]);
            }
            result = merge_sorted(result, chunk);
        }
    }

    for (size_t idx = 0; idx < result.size(); ++idx) {
        if (idx) cout << ' ';
        cout << result[idx];
    }
    cout << '\n';
    return 0;
}