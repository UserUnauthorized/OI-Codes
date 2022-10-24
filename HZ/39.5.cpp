//HZ - 39.5
#include <bits/stdc++.h>

using namespace std;

constexpr int maxn = 50004;

constexpr int maxp = 16;

int n, p, Q, source[maxn], Max[maxn][maxp], Min[maxn][maxp];

void init();

int RMQ(int, int);

int main() {
    init();
    int a, b;
    for (int i = 0; i < Q; ++i) {
        scanf("%d%d", &a, &b);
        printf("%d\n", RMQ(a, b));
    }
    return 0;
}

void init() {
    memset(source, 0, sizeof(source));
    memset(Max, 0, sizeof(Max));
    memset(Min, 0, sizeof(Min));

    scanf("%d%d", &n, &Q);
    p = (int) log2(n);

    for (int i = 1; i <= n; ++i) {
        scanf("%d", source + i);
    }

    for (int i = 1; i <= n; ++i) {
        Min[i][0] = Max[i][0] = source[i];
    }
    for (int j = 1; j <= p; ++j) {
        for (int i = 1; i + (1 << (j - 1)) <= n; ++i) {
            Max[i][j] = max(Max[i][j - 1], Max[i + (1 << (j - 1))][j - 1]);
            Min[i][j] = min(Min[i][j - 1], Min[i + (1 << (j - 1))][j - 1]);
        }
    }

}

int RMQ(int l, int r) {
    int k(0);
    while ((1 << (k + 1)) <= r - l + 1)
        ++k;
    return max(Max[l][k], Max[r - (1 << k) + 1][k]) - min(Min[l][k], Min[r - (1 << k) + 1][k]);
}