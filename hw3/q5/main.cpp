#include <iostream>

using namespace std;

struct Node {
    int r, c, h;
};

Node heap[1000005];
int hsz = 0;

void push(Node x) {
    int i = hsz++;
    heap[i] = x;
    while (i > 0) {
        int p = (i - 1) / 2;
        if (heap[p].h <= heap[i].h) break;
        Node temp = heap[i];
        heap[i] = heap[p];
        heap[p] = temp;
        i = p;
    }
}

Node pop() {
    Node ret = heap[0];
    heap[0] = heap[--hsz];
    int i = 0;
    while (true) {
        int l = 2 * i + 1;
        int r = 2 * i + 2;
        int s = i;
        if (l < hsz && heap[l].h < heap[s].h) s = l;
        if (r < hsz && heap[r].h < heap[s].h) s = r;
        if (s == i) break;
        Node temp = heap[i];
        heap[i] = heap[s];
        heap[s] = temp;
        i = s;
    }
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    int* grid = new int[n * m];
    bool* vis = new bool[n * m];

    for (int i = 0; i < n * m; i++) {
        cin >> grid[i];
        vis[i] = false;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (i == 0 || i == n - 1 || j == 0 || j == m - 1) {
                int idx = i * m + j;
                push({i, j, grid[idx]});
                vis[idx] = true;
            }
        }
    }

    long long ans = 0;
    int dr[] = {0, 0, 1, -1};
    int dc[] = {1, -1, 0, 0};

    while (hsz > 0) {
        Node curr = pop();

        for (int k = 0; k < 4; k++) {
            int nr = curr.r + dr[k];
            int nc = curr.c + dc[k];
            int nidx = nr * m + nc;

            if (nr >= 0 && nr < n && nc >= 0 && nc < m && !vis[nidx]) {
                vis[nidx] = true;
                if (grid[nidx] < curr.h) {
                    ans += (curr.h - grid[nidx]);
                }
                int nh = (grid[nidx] > curr.h) ? grid[nidx] : curr.h;
                push({nr, nc, nh});
            }
        }
    }

    cout << ans << endl;

    delete[] grid;
    delete[] vis;
    return 0;
}