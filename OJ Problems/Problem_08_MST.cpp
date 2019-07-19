// OJ Problem #8
// MST

#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>

const int MAXN = 5e5 + 9;
const int MOD = 1000000007;

int f[MAXN];

int find(int u) {
    int v = u;
    while (v != f[v]) v = f[v];
    while (u != f[u]) {
        int w = f[u];
        f[u] = v;
        u = w;
    }
    return v;
}

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) f[i] = i;
    std::pair<std::pair<int, int>, int> now;
    scanf("%d%d%d", &now.first.first, &now.first.second, &now.second);
    int cnt = 0;
    long long tot = 0;
    
    int ans = 1;
    for (int i = 1; i <= m; ++i) {
        std::pair<std::pair<int, int>, int> nxt;
        int nans = ans;
        if (i < m) {
            scanf("%d%d%d", &nxt.first.first, &nxt.first.second, &nxt.second);
            if (nxt.second == now.second) {
                std::pair<int, int> u = std::make_pair(find(now.first.first), find(now.first.second));
                std::pair<int, int> v = std::make_pair(find(nxt.first.first), find(nxt.first.second));
                if (u.first != u.second && u == v) {
                    nans = ans << 1;
                    while (nans >= MOD) nans -= MOD;
                }
                std::swap(v.first, v.second);
                if (u.first != u.second && u == v) {
                    nans = ans << 1;
                    while (nans >= MOD) nans -= MOD;
                }
            }
        }
        if (find(now.first.first) != find(now.first.second)) {
            f[f[now.first.first]] = f[now.first.second];
            ++cnt;
        }
        
        else tot += 1LL * now.second;
        now = nxt;
        
        printf("%d %lld %d\n", n - 1 - cnt, tot, ans);
        ans = nans;
    }
    return 0;
}