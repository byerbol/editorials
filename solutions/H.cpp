#include <bits/stdc++.h>

using i64 = long long;

constexpr int LOG = 17;
constexpr i64 inf = 1E18;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, q;
    std::cin >> n >> q;
    
    std::vector<int> d(n + 1), c(n + 1);
    for (int i = 1; i <= n; i++) {
        std::cin >> d[i] >> c[i];
    }
    
    std::vector up(LOG, std::vector<int>(n + 1));
    std::vector sum(LOG, std::vector<i64>(n + 1));
    
    std::vector<int> stk;
    for (int i = n; i >= 1; i--) {
        while (!stk.empty() && d[stk.back()] <= d[i]) {
            stk.pop_back();
        }
        up[0][i] = stk.empty() ? 0 : stk.back();
        sum[0][i] = c[i];
        stk.push_back(i);
    }
    sum[0][0] = inf;
    
    for (int k = 1; k < LOG; k++) {
        for (int v = 0; v <= n; v++) {
            up[k][v] = up[k - 1][up[k - 1][v]];
            sum[k][v] = std::min(inf, sum[k - 1][v] + sum[k - 1][up[k - 1][v]]);
        }
    }
    
    while (q--) {
        int r;
        i64 v;
        std::cin >> r >> v;
        
        for (int k = LOG - 1; k >= 0; k--) {
            if (sum[k][r] < v) {
                v -= sum[k][r];
                r = up[k][r];
            }
        }
        std::cout << r << "\n";
    }
    
    return 0;
}
