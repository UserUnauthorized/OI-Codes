//HZ - 41.2
//Luogu - P1182
//Luogu - P2884
#include <bits/stdc++.h>

using namespace std;

inline int read();

inline void write(int *);

constexpr int maxn = 100005;
int n(read()), m(read()),ans, source[maxn];
int l(INT_MIN), r(0);

void init();


bool check(const int &);

int main() {
    init();

    while (l < r) {
        int mid = (l + r) >> 1;
        if (check(mid)) {
            r = mid;
        } else {
            l = mid + 1;

        }
    }
    printf("%d", l);
}

void init() {
    memset(source, 0, sizeof(source));
    for (int i = 1; i <= n; ++i) {
        write(source + i);
        r += source[i];
        l = max(source[i], l);
    }
}

inline int read() {
    char ch(getchar());
    int result(0);
    while (ch < '0' || ch > '9')
        ch = getchar();
    while (ch >= '0' && ch <= '9') {
        result = (result << 3) + (result << 1) + (ch ^ 48);
        ch = getchar();
    }
    return result;
}

inline void write(int *result) {
    char ch(getchar());
    while (ch < '0' || ch > '9')
        ch = getchar();
    while (ch >= '0' && ch <= '9') {
        *result = (*result << 3) + (*result << 1) + (ch ^ 48);
        ch = getchar();
    }
}

bool check(const int &x) {
    unsigned long long sum(0), count(0);
    for (int i = 1; i <= n; ++i) {
        if (sum + source[i] <= x) {
            sum += source[i];
        } else {
            ++count;
            sum = source[i];
        }
    }
    return count < m;
}