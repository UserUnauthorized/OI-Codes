//HZ - 277.2
#include<bits/stdc++.h>

using namespace std;
int n, ans[20][20];
long long answer(0);

inline void read();

int main() {
    read();

    for (int i = 1; i <= n; ++i)
        ++ans[i / (int) pow(10, (int) (log10(i)))][i % 10];

    for (int i = 1; i <= 9; ++i) {
        for (int j = 1; j <= 9; ++j) {
            answer += ans[i][j] * ans[j][i];
        }
    }
    printf("%lld", answer);
    return 0;
}

inline void read() {
    int ch(getchar());
    while (ch < '0' || ch > '9')
        ch = getchar();
    while (ch >= '0' && ch <= '9') {
        n = (n << 3) + (n << 1) + (ch ^ 48);
        ch = getchar();
    }
}

