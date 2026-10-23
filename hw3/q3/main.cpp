#include <iostream>
#include <cmath>

using namespace std;

struct Stack {
    int arr[100];
    int ptr = -1;

    void push(int x) {
        arr[++ptr] = x;
    }

    int pop() {
        if (ptr == -1) return -1;
        return arr[ptr--];
    }

    int get(int idx) {
        return arr[idx];
    }

    bool empty() {
        return ptr == -1;
    }
};

char board[8][8];

bool check(int r, int c, Stack& st) {
    if (board[r][c] == '*') return false;

    for (int i = 0; i < r; i++) {
        int prev_c = st.get(i);
        if (prev_c == c || abs(r - i) == abs(c - prev_c)) {
            return false;
        }
    }
    return true;
}

int main() {

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            cin >> board[i][j];
        }
    }

    Stack st;
    int r = 0, c = 0;
    long long ans = 0;

    while (1) {
        bool placed = false;
        while (c < 8) {
            if (check(r, c, st)) {
                st.push(c);
                placed = true;
                r++;
                c = 0;
                break;
            }
            c++;
        }

        if (!placed) {
            if (st.empty()) break;
            r--;
            c = st.pop() + 1;
        } else {
            if (r == 8) {
                ans++;
                r--;
                c = st.pop() + 1;
            }
        }
    }

    cout << ans << endl;

    return 0;
}