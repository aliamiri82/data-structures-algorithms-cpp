#include <iostream>
using namespace std;

int main() {
    int m, n;
    cin >> n >> m;
    int arr[n];
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        arr[i] = arr[i] % m;
    }

    int last_oshkol[m], new_oshkol[m];

    for (int i = 0; i < m; i++) {
        last_oshkol[i] = 0;
        new_oshkol[i] = 0;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (last_oshkol[j] == 1) {
                new_oshkol[(j + arr[i]) % m] = 1;
            }
        }
        new_oshkol[arr[i]] = 1;
        for (int l = 0; l < m; l++) {
            last_oshkol[l] = new_oshkol[l];
        }
        if (last_oshkol[0] == 1) {
            cout << "YES" << endl;
            return 0;
        }

    }
    cout << "NO" << endl;
}
