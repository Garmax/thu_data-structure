// OJ Problem #3
// Bracket Lists

#include <cstdio>
#include <cstdlib>
#include <deque>
#include <algorithm>
#include <map>

const char LEFT[7] = "([{<"; 
const char RIGHT[7] = ")]}>";

std::deque<std::pair<int, int> > que, match;
std::map<int, int> cp;

int get_representation(char c) {
    for (int i = 0; i < 4; ++i)
        if (c == LEFT[i]) return i + 1;
    for (int i = 0; i < 4; ++i)
        if (c == RIGHT[i]) return -i - 1;
    return 0;
}

int main() {
    int n;
    scanf("%d", &n);
    int L = 0, R = 0;
    while (n--) {
        int op;
        scanf("%d", &op);
        if (op == 1) {
            char s[13];
            scanf("%s", s);
            int rpr = get_representation(s[0]);
            if (rpr < 0 && !match.empty() && match.back().second + rpr == 0) {
                cp[R] = match.back().first;
                cp[match.back().first] = R;
                que.push_back(std::make_pair(R++, rpr));
                match.pop_back();
            }
            else {
                match.push_back(std::make_pair(R, rpr));
                que.push_back(std::make_pair(R, rpr));
                ++R;
            }
        }
        else if (op == 2) {
            char s[13];
            scanf("%s", s);
            int rpr = get_representation(s[0]);
            if (rpr > 0 && !match.empty() && match.front().second + rpr == 0) {
                --L;
                cp[L] = match.front().first;
                cp[match.front().first] = L;
                que.push_front(std::make_pair(L, rpr));
                match.pop_front();
            }
            else {
                --L;
                match.push_front(std::make_pair(L, rpr));
                que.push_front(std::make_pair(L, rpr));
            }
        }
        else if (op == 3) {
            if (!match.empty() && que.back().first == match.back().first) match.pop_back();
            else 
                match.push_back(std::make_pair(cp[que.back().first], -que.back().second));
            que.pop_back();
        }
        else if (op == 4) {
            if (!match.empty() && que.front().first == match.front().first) match.pop_front();
            else 
                match.push_front(std::make_pair(cp[que.front().first], -que.front().second));
            que.pop_front();
        }
        printf("%d\n", match.empty());
    }
    return 0;
}