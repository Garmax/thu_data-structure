// OJ Problem #9
// Shortest Path

#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <queue>
#include <vector>

const int MAXN = 1009;
const int INF = 1e9;
const int dr[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

int d[MAXN][MAXN], g[MAXN][MAXN];
char s[MAXN];

std::priority_queue<std::pair<int, std::pair<int, int> > > que;

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 0; i <= n + 1; ++i)
        for (int j = 0; j <= m + 1; ++j)
            g[i][j] = -1;
    for (int i = 1; i <= n; ++i) {
        scanf("%s", s + 1);
        for (int j = 1; j <= m; ++j) {
            if (s[j] >= '0' && s[j] <= '9')
                g[i][j] = s[j] - '0';
            d[i][j] = INF;
        }
    }
    int inix, iniy;
    scanf("%d%d", &inix, &iniy);
    d[inix][iniy] = 0;
    que.push(std::make_pair(0, std::make_pair(inix, iniy)));
    while (!que.empty()) {
        int w = -que.top().first;
        int x = que.top().second.first;
        int y = que.top().second.second;
        que.pop();
        if (d[x][y] < w) continue;
        for (int i = 0; i < 4; ++i) {
            int xx = x + dr[i][0], yy = y + dr[i][1];
            if (g[xx][yy] != -1) {
                int v = std::max(1, g[xx][yy] - g[x][y] + 1);
                if (d[xx][yy] > d[x][y] + v) {
                    d[xx][yy] = d[x][y] + v;
                    que.push(std::make_pair(-d[xx][yy], std::make_pair(xx, yy)));
                }
            }
        }
    }
    for (int i = 1; i <= n; ++i, printf("\n"))
        for (int j = 1; j <= m; ++j)
            printf("%d ", d[i][j] < INF? d[i][j]: -1);
    return 0;
}