// OJ Problem #5
// Encoding

#include <cstdio>
#include <cstdlib>
#include <queue>
#include <algorithm>
#include <set>
#include <iostream>

using std::cout;
using std::endl;

std::priority_queue<long long> heap;
std::multiset<int> min, max;

long long calc() {
    long long ans = 0;
    while (heap.size() > 1) {
        long long now = heap.top();
        heap.pop();
        now += heap.top();
        heap.pop();
        heap.push(now);
        ans -= now;
    }
    return ans;
}

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        int k;
        scanf("%d", &k);
        min.insert(k);
        max.insert(-k);
        heap.push(-k);
    }
    cout << calc() << endl;
    char s[13];
    scanf("%s", s);
    if (s[0] == 'B') return 0;
    int m;
    scanf("%d", &m);
    while (m--) {
        scanf("%s", s);
        if (s[0] == 'D') {
            int now = *max.begin();
            max.erase(max.begin());
            min.erase(min.find(-now));
        }
        else if (s[0] == 'E') {
            int now = *min.begin();
            min.erase(min.begin());
            max.erase(max.find(-now));
        }
        else {
            int k;
            scanf("%d", &k);
            min.insert(k);
            max.insert(-k);
        }
    }
    while (!heap.empty()) heap.pop();
    for (std::multiset<int>::iterator it = max.begin(); it != max.end(); ++it)
        heap.push(*it);
    cout << calc() << endl;
    return 0;
}