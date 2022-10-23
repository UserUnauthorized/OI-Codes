//Luogu - P3865
#include <bits/stdc++.h>

using namespace std;

int N, M, sourceNumber[100010], sparseTable[100010][20], lg[100010];

inline int read();

void init();

void build();

int query(const int &, const int &);

int main() {
    init();
    build();
    for (int i = 1; i <= M; ++i) {
        int l(read()), r(read());
        printf("%d\n", query(l, r));
    }
    return 0;
}

void init() {
    //读入数据
    N = read();
    M = read();
    for (int i = 1; i <= N; ++i)
        sourceNumber[i] = read();

    //预处理log2
    //lg[1] = 0;
    for (int i = 2; i <= N; ++i)
        lg[i] = lg[i >> 1] + 1;
    //初始化ST数组
    for (int i = 1; i <= N; ++i)
        sparseTable[i][0] = sourceNumber[i];
}

void build() {
    for (int i = 2; i <= N; i <<= 1)
        for (int j = 1; j + i - 1 <= N; ++j)
            sparseTable[j][lg[i]] = max(sparseTable[j][lg[i] - 1], sparseTable[j + (i >> 1)][lg[i] - 1]);
}

int query(const int &l, const int &r) {
    int n = 1;
    while ((n << 1) <= r - l + 1)n <<= 1;
    return max(sparseTable[l][lg[n]], sparseTable[r - n + 1][lg[n]]);
}

inline int read() {
    char ch(0);
    int x(0);
    while (ch < '0' || ch > '9')ch = getchar();
    while (ch >= '0' && ch <= '9') {
        x = (x << 3) + (x << 1) + (ch - '0');
        ch = getchar();
    }
    return x;
}