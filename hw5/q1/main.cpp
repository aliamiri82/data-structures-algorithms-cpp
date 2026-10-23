#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

typedef long long ll;

const ll BIG = 1e17;
int n, m, s, t;
struct lule {
    int az, be, vazn, id;
};

vector<lule> hamme_luleha;
vector<pair<int, int>> hamsaye_ha[100005];
vector<pair<int, int>> hamsaye_aks[100005];
ll f_s[100005], f_t[100005];

void d_bezan(int shoro, ll fasele[], vector<pair<int, int>> g[]) {
    for (int i = 1; i <= n; i++) fasele[i] = BIG;
    fasele[shoro] = 0;
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> saf;
    saf.push({0, shoro});
    while (!saf.empty()) {
        ll d = saf.top().first;
        int u = saf.top().second;
        saf.pop();
        if (d > fasele[u]) continue;
        for (auto h : g[u]) {
            if (fasele[u] + h.second < fasele[h.first]) {
                fasele[h.first] = fasele[u] + h.second;
                saf.push({fasele[h.first], h.first});
            }
        }
    }
}

vector<pair<int, int>> g_kotah[100005];
int timer, tin[100005], low[100005];
bool ye_dune_ast[200005];

void dfs_pol(int u, int p_id = -1) {
    tin[u] = low[u] = ++timer;
    for (auto h : g_kotah[u]) {
        int v = h.first;
        int id = h.second;
        if (id == p_id) continue;
        if (tin[v]) {
            low[u] = min(low[u], tin[v]);
        } else {
            dfs_pol(v, id);
            low[u] = min(low[u], low[v]);
            if (low[v] > tin[u]) ye_dune_ast[id] = true;
        }
    }
}

int main() {
    cin >> n >> m >> s >> t;
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        hamme_luleha.push_back({u, v, w, i});
        hamsaye_ha[u].push_back({v, w});
        hamsaye_aks[v].push_back({u, w});
    }

    d_bezan(s, f_s, hamsaye_ha);
    d_bezan(t, f_t, hamsaye_aks);

    ll hadaksar = f_s[t];

    for (int i = 0; i < m; i++) {
        int u = hamme_luleha[i].az;
        int v = hamme_luleha[i].be;
        int w = hamme_luleha[i].vazn;
        if (f_s[u] + w + f_t[v] == hadaksar) {
            g_kotah[u].push_back({v, i});
            g_kotah[v].push_back({u, i});
        }
    }

    for (int i = 1; i <= n; i++) if (!tin[i]) dfs_pol(i);

    for (int i = 0; i < m; i++) {
        if (ye_dune_ast[i]) {
            cout << "YES" << "\n";
        } else {
            ll u = hamme_luleha[i].az;
            ll v = hamme_luleha[i].be;
            ll w = hamme_luleha[i].vazn;
            ll feseghli = hadaksar - 1 - f_s[u] - f_t[v];
            if (feseghli >= 1) {
                cout << "CAN " << w - feseghli << "\n";
            } else {
                cout << "NO" << "\n";
            }
        }
    }

    return 0;
}