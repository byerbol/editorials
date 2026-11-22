#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, k;
    std::cin >> n >> k;
    
    std::vector<int> lang(n);
    for (int i = 0; i < n; i++) {
        std::cin >> lang[i];
    }
    
    std::vector<std::vector<int>> adj(n);
    for (int i = 1; i < n; i++) {
        int b;
        std::cin >> b;
        adj[b].push_back(i);
    }
    
    std::vector<int> dep(n), tin(n), tout(n), maxd(n), ord;
    std::vector<int> onPath(k);
    std::vector<bool> top(n);
    int timer = 0;
    std::vector<std::pair<int, int>> stk{{0, 0}};
    while (!stk.empty()) {
        auto &[v, i] = stk.back();
        if (i == 0) {
            tin[v] = timer++;
            ord.push_back(v);
            maxd[v] = dep[v];
            top[v] = onPath[lang[v]] == 0;
            onPath[lang[v]]++;
        }
        if (i < int(adj[v].size())) {
            int u = adj[v][i++];
            dep[u] = dep[v] + 1;
            stk.push_back({u, 0});
        } else {
            tout[v] = timer;
            onPath[lang[v]]--;
            int x = v;
            stk.pop_back();
            if (!stk.empty()) {
                int p = stk.back().first;
                maxd[p] = std::max(maxd[p], maxd[x]);
            }
        }
    }
    
    int D = *std::max_element(dep.begin(), dep.end()) + 1;
    std::vector<std::vector<int>> level(D);
    for (int v : ord) {
        level[dep[v]].push_back(tin[v]);
    }
    
    std::vector<std::vector<int>> cd(k);
    std::vector<std::vector<std::vector<int>>> ct(k);
    {
        std::vector<std::vector<int>> byLang(k);
        for (int v : ord) {
            byLang[lang[v]].push_back(v);
        }
        for (int c = 0; c < k; c++) {
            auto &a = byLang[c];
            std::stable_sort(a.begin(), a.end(), [&](int x, int y) {
                return dep[x] < dep[y];
            });
            for (int v : a) {
                if (cd[c].empty() || cd[c].back() != dep[v]) {
                    cd[c].push_back(dep[v]);
                    ct[c].emplace_back();
                }
                ct[c].back().push_back(tin[v]);
            }
        }
    }
    
    auto count = [&](const std::vector<int> &a, int l, int r) {
        return int(std::lower_bound(a.begin(), a.end(), r) - std::lower_bound(a.begin(), a.end(), l));
    };
    
    int bestP = -1, bestS = 0;
    for (int v = 0; v < n; v++) {
        if (!top[v]) {
            continue;
        }
        int c = lang[v];
        int P = 0, A = 0;
        int j = std::lower_bound(cd[c].begin(), cd[c].end(), dep[v]) - cd[c].begin();
        for (; j < int(cd[c].size()) && cd[c][j] <= maxd[v]; j++) {
            int d = cd[c][j];
            int s = count(level[d], tin[v], tout[v]);
            int t = ct[c][j].size();
            P += std::min(s, t);
            A += count(ct[c][j], tin[v], tout[v]);
        }
        int S = P - A;
        if (P > bestP || (P == bestP && S < bestS)) {
            bestP = P;
            bestS = S;
        }
    }
    
    std::cout << bestP << " " << bestS << "\n";
    
    return 0;
}
