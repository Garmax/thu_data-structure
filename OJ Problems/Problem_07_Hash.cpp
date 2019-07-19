// OJ Problem #7
// Hash

#include <cstdio>
#include <cstdlib>
#include <string>
#include <map>
#include <vector>

const int SEED = 131311;
const int SEEDF = 51329;
const int MAXN = 50009;

std::map<std::string, int> num;
std::map<unsigned long long, int> F_, S_;
std::vector<int> g[MAXN];
int a[MAXN];
unsigned long long F[MAXN], S[MAXN];

void dfs(int u) {
    F[u] = S[u] = 0;
    for (int i = 0; i < (int)g[u].size(); ++i) {
        dfs(g[u][i]);
        F[u] = F[u] * SEED + 1LL * a[g[u][i]];
        S[u] = S[u] * SEED + S[g[u][i]];
    }
    F[u] = F[u] * SEEDF + 1LL * a[u];
    S[u] = S[u] * SEEDF + 1LL * a[u];
    if (F_.count(F[u]) == 0) F_[F[u]] = 0;
    ++F_[F[u]];
    if (S_.count(S[u]) == 0) S_[S[u]] = 0;
    ++S_[S[u]];
}

int main() {
    int n, Q;
    scanf("%d%d", &n, &Q);
    num["root"] = 0;
    a[0] = 13;
    for (int i = 1; i <= n; ++i) {
        char s[103];
        scanf("%s", s);
        int u = num[s];
        scanf("%s", s);
        num[s] = i;
        scanf("%s", s);
        a[i] = s[0] == 'M'? 13: 11;
        g[u].push_back(i);
    }
    dfs(0);
    while (Q--) {
        char s[103];
        scanf("%s", s);
        if (s[0] == 'F') {
            char c[103];
            scanf("%s", c);
            printf("%d\n", F_[F[num[c]]] - 1);
        }
        else {
            char c[103];
            scanf("%s", c);
            printf("%d\n", S_[S[num[c]]] - 1);
        }
    }
    return 0;
}