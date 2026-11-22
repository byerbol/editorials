#include <bits/stdc++.h>

using i64 = long long;

struct Fenwick {
    int n;
    std::vector<int> a;
    
    Fenwick(int n_ = 0) : n(n_), a(n_) {}
    
    void add(int x, int v) {
        for (int i = x + 1; i <= n; i += i & -i) {
            a[i - 1] ^= v;
        }
    }
    
    int sum(int x) {
        int ans = 0;
        for (int i = x; i > 0; i -= i & -i) {
            ans ^= a[i - 1];
        }
        return ans;
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, q;
    std::cin >> n >> q;
    
    std::vector<int> a(n);
    std::array<Fenwick, 2> fen{Fenwick(n), Fenwick(n)};
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
        fen[i % 2].add(i, a[i]);
    }
    
    while (q--) {
        int t, x, y;
        std::cin >> t >> x >> y;
        
        if (t == 1) {
            int i = x - 1;
            fen[i % 2].add(i, a[i] ^ y);
            a[i] = y;
        } else {
            int l = x - 1, r = y - 1;
            if ((r - l + 1) % 2 == 0) {
                std::cout << 0 << "\n";
            } else {
                auto &f = fen[l % 2];
                std::cout << (f.sum(r + 1) ^ f.sum(l)) << "\n";
            }
        }
    }
    
    return 0;
}
