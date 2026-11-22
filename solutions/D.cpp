#include <bits/stdc++.h>

using i64 = long long;

constexpr int W = 500;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int r, c, m;
    std::cin >> r >> c >> m;
    
    std::vector<std::bitset<W>> water(r);
    for (int i = 0; i < r; i++) {
        std::string s;
        std::cin >> s;
        for (int j = 0; j < c; j++) {
            water[i][j] = s[j] == '.';
        }
    }
    
    std::string sig;
    std::cin >> sig;
    
    auto cur = water;
    std::vector<std::bitset<W>> nxt(r);
    for (char ch : sig) {
        for (int i = 0; i < r; i++) {
            std::bitset<W> b;
            if (ch == 'E' || ch == '?') {
                b |= cur[i] << 1;
            }
            if (ch == 'W' || ch == '?') {
                b |= cur[i] >> 1;
            }
            if ((ch == 'N' || ch == '?') && i + 1 < r) {
                b |= cur[i + 1];
            }
            if ((ch == 'S' || ch == '?') && i > 0) {
                b |= cur[i - 1];
            }
            nxt[i] = b & water[i];
        }
        std::swap(cur, nxt);
    }
    
    int ans = 0;
    for (int i = 0; i < r; i++) {
        ans += cur[i].count();
    }
    std::cout << ans << "\n";
    
    return 0;
}
