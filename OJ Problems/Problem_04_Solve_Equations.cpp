// OJ Problem #4
// Solve Equations

#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>

const int MAXN = 5009;
const double EPS = 1e-8;

double a[MAXN][MAXN];

int sign(double u) {
    return u < -EPS? -1: u > EPS;
}

bool Gauss(int n){
    for (int i = 1; i < n; ++i) {
        int max = i;
        if (n <= 100)
            for (int j = i + 1; j < n; ++j)
                if (fabs(a[i][i]) > fabs(a[max][i]) + EPS) max = i;
        if (max != i)
            for (int j = 1; j <= n; ++j)
                std::swap(a[i][j], a[max][j]);
        if (sign(a[i][i]) != 0) {
            for (int j = i + 1; j < n; ++j)
                for (int k = n; k >= i; --k)
                    a[j][k] -= a[j][i] / a[i][i] * a[i][k];
        }
    }
    for (int i = n - 1; i > 0; --i) {
        if (sign(a[i][i]) == 0) return false;
        a[i][n] /= a[i][i];
        for (int j = i - 1; j > 0; --j)
            a[j][n] -= a[i][n] * a[j][i];
    }
    return true;
}

int main() {
    int Cases;
    scanf("%d", &Cases);
    while (Cases--) {
        char s[13];
        scanf("%s", s);
        int n;
        if (s[0] == 'R') {
            scanf("%d", &n);
            for (int i = 1; i <= n; ++i)
                for (int j = 1; j <= n; ++j) {
                    int k;
                    scanf("%d", &k);
                    a[i][j] = k * 1.0;
                }
            ++n;
            for (int i = 1; i < n; ++i) {
                int k;
                scanf("%d", &k);
                a[i][n] = k * 1.0;
            }
        }
        else {
            int m;
            scanf("%d%d", &n, &m);
            ++n;
            for (int i = 1; i <= n; ++i)
                for (int j = 1; j <= n; ++j) a[i][j] = 0.0;
            while (m--) {
                int x, y, d;
                scanf("%d%d%d", &x, &y, &d);
                a[x][y] = d * 1.0;
            }
            for (int i = 1; i < n; ++i) {
                int k;
                scanf("%d", &k);
                a[i][n] = k * 1.0;
            }
        }
        if (Gauss(n)) {
            for (int i = 1; i < n; ++i)
                printf("%.9f ", a[i][n]);
            printf("\n");
        }
        else printf("0\n");
    }
    return 0;
}