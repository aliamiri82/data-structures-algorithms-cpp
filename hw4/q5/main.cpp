#include <iostream>

using namespace std;

long long h[500000];
long long s[500000];
long long p[500000];
long long diff[500000];
int L[500000];
int R[500000];
int st[500000];

void solve() {
    int n;
    if (!(cin >> n)) return;

    for (int i = 0; i < n; i++) {
        cin >> h[i] >> s[i] >> p[i];
        diff[i] = 0;
    }
    diff[n] = 0;

    int top = -1;
    for (int i = 0; i < n; i++) {
        while (top >= 0 && h[st[top]] <= h[i]) {
            top--;
        }
        if (top >= 0) {
            L[i] = st[top];
        } else {
            L[i] = 0;
        }
        st[++top] = i;
    }

    top = -1;
    for (int i = n - 1; i >= 0; i--) {
        while (top >= 0 && h[st[top]] <= h[i]) {
            top--;
        }
        if (top >= 0) {
            R[i] = st[top];
        } else {
            R[i] = n - 1;
        }
        st[++top] = i;
    }

    for (int i = 0; i < n; i++) {
        if (L[i] <= i - 1) {
            diff[L[i]] += p[i];
            diff[i] -= p[i];
        }
        if (i + 1 <= R[i]) {
            diff[i + 1] += p[i];
            diff[R[i] + 1] -= p[i];
        }
    }

    long long current_attack = 0;
    for (int i = 0; i < n; i++) {
        current_attack += diff[i];

        if (current_attack <= 0) {
            cout << 0 << " ";
        } else {
            long long time = (s[i] + current_attack - 1) / current_attack;
            cout << time << " ";
        }
    }
    cout << "\n";
}

int main() {
    int q;
    if (cin >> q) {
        while (q--) {
            solve();
        }
    }
    return 0;
}