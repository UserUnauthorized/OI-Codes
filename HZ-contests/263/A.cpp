//HZ - 263.1
#include <bits/stdc++.h>

using namespace std;

int T, n, m, ans;

void init();
inline void read(int &);

int main() {
    read(T);

    for (; T > 0; --T) {
        n = m = ans = 0;
        read(n);
        read(m);
        if (m == 1) {
            printf("%d\n", 1);
            continue;
        }
        for (int x = 0; x * m <= n; ++x)
            if (((n - x * m) % (m * (m - 1) / 2)) == 0)
                ++ans;
        printf("%d\n",ans);
    }
    return 0;
}

inline void read(int &x) {
    char ch(0);
    while (ch < '0' || ch > '9')ch = getchar();
    while (ch >= '0' && ch <= '9') {
        x = (x << 3) + (x << 1) + (ch ^ 48);
        ch = getchar();
    }
}