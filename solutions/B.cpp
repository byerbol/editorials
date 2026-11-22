#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n;
    std::cin >> n;
    
    std::vector<int> c(n);
    for (int i = 0; i < n; i++) {
        std::cin >> c[i];
    }
    
    std::sort(c.begin(), c.end(), std::greater<>());
    
    int ans = 0;
    for (int i = 0; i < n; i++) {
        if (c[i] >= i + 1) {
            ans = i + 1;
        }
    }
    
    std::cout << ans << "\n";
    
    return 0;
}
