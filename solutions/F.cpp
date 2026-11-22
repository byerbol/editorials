#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n;
    std::cin >> n;
    
    std::vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        std::cin >> b[i];
    }
    
    std::vector<int> dp(n + 1), ndp(n + 1);
    std::vector<int> ok(n);
    for (int i = 0; i < n; i++) {
        std::fill(ok.begin(), ok.end(), 0);
        for (int j = i, mx = 0; j >= 0; j--) {
            mx = std::max(mx, a[j]);
            if (mx > b[i]) {
                break;
            }
            ok[j] = a[j] == b[i];
        }
        for (int j = i, mx = 0; j < n; j++) {
            mx = std::max(mx, a[j]);
            if (mx > b[i]) {
                break;
            }
            ok[j] = a[j] == b[i];
        }
        
        ndp[0] = 0;
        for (int j = 0; j < n; j++) {
            ndp[j + 1] = std::max(ndp[j], dp[j + 1] + ok[j]);
        }
        std::swap(dp, ndp);
    }
    
    std::cout << dp[n] << "\n";
    
    return 0;
}
