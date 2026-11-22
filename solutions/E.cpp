#include <bits/stdc++.h>
using i64 = long long;
int main() {
    int n;
    std::cin >> n;
    std::vector<std::pair<i64, i64>> p(n);
    for (auto &[a, b] : p) std::cin >> a >> b;
    std::sort(p.begin(), p.end());
    i64 P = 0, best = LLONG_MIN, ans = LLONG_MIN;
    for (auto [a, b] : p) {
        best = std::max(best, a - P);
        P += b;
        ans = std::max(ans, P - a + best);
    }
    std::cout << ans << "\n";
}
