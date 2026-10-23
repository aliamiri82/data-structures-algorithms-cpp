#include <iostream>

using namespace std;

long long L_heap[200000];
long long R_heap[200000];
int L_size = 0;
int R_size = 0;
long long sum_L = 0;
long long sum_R = 0;
long long total_b = 0;

void push_L(long long val) {
    L_heap[++L_size] = val;
    int cur = L_size;
    while (cur > 1 && L_heap[cur] > L_heap[cur / 2]) {
        long long temp = L_heap[cur];
        L_heap[cur] = L_heap[cur / 2];
        L_heap[cur / 2] = temp;
        cur /= 2;
    }
}

long long pop_L() {
    long long res = L_heap[1];
    L_heap[1] = L_heap[L_size--];
    int cur = 1;
    while (cur * 2 <= L_size) {
        int next = cur * 2;
        if (next + 1 <= L_size && L_heap[next + 1] > L_heap[next]) next++;
        if (L_heap[cur] >= L_heap[next]) break;
        long long temp = L_heap[cur];
        L_heap[cur] = L_heap[next];
        L_heap[next] = temp;
        cur = next;
    }
    return res;
}

void push_R(long long val) {
    R_heap[++R_size] = val;
    int cur = R_size;
    while (cur > 1 && R_heap[cur] < R_heap[cur / 2]) {
        long long temp = R_heap[cur];
        R_heap[cur] = R_heap[cur / 2];
        R_heap[cur / 2] = temp;
        cur /= 2;
    }
}

long long pop_R() {
    long long res = R_heap[1];
    R_heap[1] = R_heap[R_size--];
    int cur = 1;
    while (cur * 2 <= R_size) {
        int next = cur * 2;
        if (next + 1 <= R_size && R_heap[next + 1] < R_heap[next]) next++;
        if (R_heap[cur] <= R_heap[next]) break;
        long long temp = R_heap[cur];
        R_heap[cur] = R_heap[next];
        R_heap[next] = temp;
        cur = next;
    }
    return res;
}

int main() {
    int q;
    cin >> q;

    while (q--) {
        int type;
        cin >> type;
        if (type == 1) {
            long long a, b;
            cin >> a >> b;
            total_b += b;

            if (L_size == 0 || a <= L_heap[1]) {
                push_L(a);
                sum_L += a;
            } else {
                push_R(a);
                sum_R += a;
            }

            if (L_size > R_size + 1) {
                long long val = pop_L();
                sum_L -= val;
                push_R(val);
                sum_R += val;
            } else if (R_size > L_size) {
                long long val = pop_R();
                sum_R -= val;
                push_L(val);
                sum_L += val;
            }
        } else {
            long long x = L_heap[1];
            long long res = (sum_R - R_size * x) + (L_size * x - sum_L) + total_b;
            cout << x << " " << res << "\n";
        }
    }

    return 0;
}