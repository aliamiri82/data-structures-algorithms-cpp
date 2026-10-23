#include <iostream>

using namespace std;

void merge(int arr[], int w[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    int* L = new int[n1];
    int* R = new int[n2];
    int* L_w = new int[n1];
    int* R_w = new int[n2];

    for (int i = 0; i < n1; i++) {
        L[i] = arr[left + i];
        L_w[i] = w[left + i];
    }
    for (int j = 0; j < n2; j++) {
        R[j] = arr[mid + 1 + j];
        R_w[j] = w[mid + 1 + j];
    }

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            w[k] = L_w[i];
            i++;
        } else {
            arr[k] = R[j];
            w[k] = R_w[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        w[k] = L_w[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = R[j];
        w[k] = R_w[j];
        j++;
        k++;
    }

    delete[] L;
    delete[] R;
    delete[] L_w;
    delete[] R_w;
}

void mergeSort(int arr[], int w[], int left, int right) {
    if (left >= right) return;
    int mid = left + (right - left) / 2;
    mergeSort(arr, w, left, mid);
    mergeSort(arr, w, mid + 1, right);
    merge(arr, w, left, mid, right);
}

int getLowerBound(int arr[], int n, long long val) {
    int left = 0, right = n - 1;
    int ans = n;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] >= val) {
            ans = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    return ans;
}

int getUpperBound(int arr[], int n, long long val) {
    int left = 0, right = n - 1;
    int ans = n;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] > val) {
            ans = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    long long k;
    if (!(cin >> n >> k)) return 0;

    int* s = new int[n];
    int* w = new int[n];

    for (int i = 0; i < n; i++) cin >> s[i];
    for (int i = 0; i < n; i++) cin >> w[i];

    mergeSort(s, w, 0, n - 1);

    long long* prefix_w = new long long[n + 1];
    prefix_w[0] = 0;
    for (int i = 0; i < n; i++) {
        prefix_w[i + 1] = prefix_w[i] + w[i];
    }

    int q;
    cin >> q;
    while (q--) {
        long long l, r;
        cin >> l >> r;

        long long min_start_time = l - k + 1;

        int idx_start = getLowerBound(s, n, min_start_time);
        int idx_end = getUpperBound(s, n, r);

        if (idx_start < idx_end) {
            cout << (prefix_w[idx_end] - prefix_w[idx_start]) << "\n";
        } else {
            cout << 0 << "\n";
        }
    }

    delete[] s;
    delete[] w;
    delete[] prefix_w;

    return 0;
}