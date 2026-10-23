#include <iostream>

using namespace std;

struct Node {
    int val;
    int index;
};

Node st[200005];
int top = -1;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (cin >> n) {
        for (int i = 1; i <= n; i++) {
            int x;
            cin >> x;

            while (top > -1 && st[top].val >= x) {
                top--;
            }

            if (top == -1) {
                cout << 0 << " ";
            } else {
                cout << st[top].index << " ";
            }

            top++;
            st[top].val = x;
            st[top].index = i;
        }
    }

    return 0;
}