#include <bits/stdc++.h>

using i64 = long long;

template <typename T>
struct Fenwick {
    int n;
    std::vector<T> a;
    
    Fenwick(int n_ = 0) {
        init(n_);
    }
    
    void init(int n_) {
        n = n_;
        a.assign(n, T{});
    }
    
    void add(int x, const T &v) {
        for (int i = x + 1; i <= n; i += i & -i) {
            a[i - 1] = a[i - 1] + v;
        }
    }
    
    T sum(int x) {
        T ans{};
        for (int i = x; i > 0; i -= i & -i) {
            ans = ans + a[i - 1];
        }
        return ans;
    }
    
    T rangeSum(int l, int r) {
        return sum(r) - sum(l);
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, k;
    std::cin >> n >> k;
    
    std::vector<i64> a(n + 1);
    Fenwick<i64> fa(n), fia(n);
    for (int i = 1; i <= n; i++) {
        std::cin >> a[i];
        fa.add(i - 1, a[i]);
        fia.add(i - 1, i * a[i]);
    }
    
    auto S = [&](int x, int y) -> i64 {
        return x > y ? 0 : fa.rangeSum(x - 1, y);
    };
    auto T = [&](int x, int y) -> i64 {
        return x > y ? 0 : fia.rangeSum(x - 1, y);
    };
    
    int q;
    std::cin >> q;
    
    std::vector<int> p(k);
    std::vector<i64> v(k);
    while (q--) {
        int t;
        std::cin >> t;
        
        if (t == 1) {
            for (int j = 0; j < k; j++) {
                std::cin >> p[j];
                v[j] = a[p[j]];
            }
            for (int j = 0; j < k; j++) {
                i64 nv = v[(j + 1) % k];
                i64 d = nv - a[p[j]];
                a[p[j]] = nv;
                fa.add(p[j] - 1, d);
                fia.add(p[j] - 1, p[j] * d);
            }
        } else {
            int l, r, m;
            std::cin >> l >> r >> m;
            
            int len = r - l + 1;
            int s = std::min(m, len - m + 1);
            
            i64 ans = 0;
            ans += T(l, l + s - 2) - 1LL * (l - 1) * S(l, l + s - 2);
            ans += 1LL * s * S(l + s - 1, r - s + 1);
            ans += 1LL * (r + 1) * S(r - s + 2, r) - T(r - s + 2, r);
            
            std::cout << ans << "\n";
        }
    }
    
    return 0;
}
