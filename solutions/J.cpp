#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int t, n;
    std::cin >> t >> n;
    
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    
    std::vector<int> cnt(t);
    int r = n - 1;
    while (cnt[a[r]] == 0) {
        cnt[a[r]]++;
        r--;
    }
    
    std::vector<bool> pre(t);
    int bl = 0, br = r;
    for (int l = 0; l < n; l++) {
        int x = a[l];
        if (pre[x]) {
            break;
        }
        while (cnt[x] > 0) {
            r++;
            cnt[a[r]]--;
        }
        cnt[x]++;
        pre[x] = true;
        if (r - (l + 1) < br - bl) {
            bl = l + 1;
            br = r;
        }
    }
    
    std::cout << bl << " " << br << "\n";
    
    return 0;
}
