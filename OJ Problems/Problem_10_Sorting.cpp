// OJ Problem #10
// Sorting

#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>

const int MAXN = 3e6 + 9;

char s[MAXN];

std::string a[MAXN];
int b[MAXN], b_[MAXN];

int cnt[256];

void sort(int L, int R, int pos) {
    for (int i = 0; i < 256; ++i) cnt[i] = 0;
    for (int i = L; i < R; ++i)
        ++cnt[a[b[i]][pos]];
    for (int i = 1; i < 256; ++i) cnt[i] += cnt[i - 1];
    for (int i = L; i < R; ++i)
        b_[--cnt[a[b[i]][pos]] + L] = b[i];
    for (int i = L; i < R; ++i)
        b[i] = b_[i];
    for (int i = L; i < R; ) {
        int j = i + 1;
        for (; j < R && a[b[i]][pos] == a[b[j]][pos]; ++j);
        if (j - i > 1) sort(i, j, pos + 1);
        i = j;
    }
}

int lower_bound(int L, int R, int p) {
    while (L <= R) {
        int mid = (L + R) >> 1;
        if (a[b[mid]][p] < s[p]) L = mid + 1;
        else R = mid - 1;
    }
    return L;
}

int upper_bound(int L, int R, int p) {
    while (L <= R) {
        int mid = (L + R) >> 1;
        if (a[b[mid]][p] > s[p]) R = mid - 1;
        else L = mid + 1;
    }
    return L;
}

std::pair<int, int> find(int n) {
    int L = 0, R = n;
    for (int i = 0; s[i] != '\0'; ++i) {
        L = lower_bound(L, R - 1, i);
        R = upper_bound(L, R - 1, i);
        //if (L >= n || a[b[L]][i] != s[i]) break;
    }
    return std::make_pair(L, R);
}

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%s", s);
        a[i] = s;
        b[i] = i;
    }
    sort(0, n, 0);
    for (int i = 0; i < n; ++i)
        printf("%d%c", b[i] + 1, i == n - 1? '\n': ' ');
    int m;
    scanf("%d", &m);
    while (m--) {
        scanf("%s", s);
        printf("%d%c", find(n).first + 1, m == 0? '\n': ' ');
    }
    scanf("%d", &m);
    while (m--) {
        scanf("%s", s);
        std::pair<int, int> rst = find(n);
        printf("%d%c", rst.second - rst.first, m == 0? '\n': ' ');
    }
    return 0;
}