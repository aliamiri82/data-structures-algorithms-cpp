#include <iostream>

using namespace std;

int head[200005];
int to[200005];
int nxt[200005];
int edge_count = 0;

int tin[200005];
int tout[200005];
int timer = 0;

void add_edge(int u, int v) {
    to[edge_count] = v;
    nxt[edge_count] = head[u];
    head[u] = edge_count;
    edge_count++;
}
void dfs(int u) {
    timer++;
    tin[u] = timer;

    int i = head[u];
    while (i != -1) {
        dfs(to[i]);
        i = nxt[i];
    }
    tout[u] = timer;
}
bool is_ancestor(int u, int v) {
    if (tin[u] <= tin[v] && tout[u] >= tout[v]) {
        return true;
    }
    return false;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    for (int i = 0; i <= n; i++) {
        head[i] = -1;
    }
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        add_edge(u, v);
    }
    dfs(1);
    int q;
    cin >> q;
    while (q--) {
        int u, v;
        cin >> u >> v;
        if (is_ancestor(u, v)) {
            cout << "YES" << "\n";
        } else {
            cout << "NO" << "\n";
        }
    }
    return 0;
}