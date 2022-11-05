//HZ - 263.1
#include <bits/stdc++.h>

using namespace std;

inline void read(long long &);

long long T, n, m;

int main() {
    read(T);

    while (T--) {
        n = m = 0;
        read(n);
        read(m);
        if (m == 1) {
            printf("%d\n", 1);
            continue;
        }
        if ((2 * n) % m != 0) {
            printf("%d\n", 0);
            continue;
        }
        int a(2 * n / m), b(m - 1);
        bool flagA(!(a & 1)), flagB(!(b & 1));
        if (flagA && flagB) {
            printf("%d\n", a / b + 1);
        } else if (flagA) {
            printf("%d\n", ((a / b) >> 1) + 1);
        } else if (flagB) {
            printf("%d\n", 0);
        } else {
            printf("%d\n", ((a / b + 1) >> 1));
        }
    }
    return 0;
}

inline void read(long long &x) {
    char ch(0);
    while (ch < '0' || ch > '9')ch = getchar();
    while (ch >= '0' && ch <= '9') {
        x = (x << 3) + (x << 1) + (ch ^ 48);
        ch = getchar();
    }
}