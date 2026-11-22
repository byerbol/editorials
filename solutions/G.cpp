#include <bits/stdc++.h>

using i64 = long long;

struct Info {
    int sum = 0;
    int pre = 0;
    int suf = 0;
    int ans = 0;
};

Info operator+(const Info &a, const Info &b) {
    Info c;
    c.sum = a.sum + b.sum;
    c.pre = std::max(a.pre, a.sum + b.pre);
    c.suf = std::max(b.suf, b.sum + a.suf);
    c.ans = std::max({a.ans + b.sum, a.sum + b.ans, a.pre + b.suf});
    return c;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n;
    std::cin >> n;
    
    std::string s;
    std::cin >> s;
    
    int sz = 1;
    while (sz < n) {
        sz *= 2;
    }
    std::vector<Info> t(2 * sz);
    for (int i = 0; i < n; i++) {
        if (s[i] == 'T') {
            t[sz + i] = {1, 1, 1, 1};
        } else {
            t[sz + i] = {-1, 0, 0, 0};
        }
    }
    for (int i = sz - 1; i >= 1; i--) {
        t[i] = t[2 * i] + t[2 * i + 1];
    }
    
    int q;
    std::cin >> q;
    
    while (q--) {
        int l, r;
        std::cin >> l >> r;
        l--;
        
        Info L, R;
        for (l += sz, r += sz; l < r; l /= 2, r /= 2) {
            if (l & 1) {
                L = L + t[l++];
            }
            if (r & 1) {
                R = t[--r] + R;
            }
        }
        std::cout << (L + R).ans << "\n";
    }
    
    return 0;
}
