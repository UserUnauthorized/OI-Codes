//Luogu - P1972
//HZ - 17.3
#include<bits/stdc++.h>

using namespace std;

struct Query {
    int pos;
    int l;
    int r;
    int result;
} query[1000005];

int num[1000005], pos = 1, n, m, c[1000005], lastPos[1000005], result[1000005];

void init();

inline int read();

inline int lowbit(int);

bool cmp_r(const Query &a, const Query &b);

int sum(int);

void insert(int, int);

int main() {
    init();
    sort(query, query + m, cmp_r);
    for (int i = 0; i < m; ++i) {
        while (pos <= query[i].r) {
            if (lastPos[num[pos]]) {
                insert(lastPos[num[pos]], -1);
            }
            insert(pos, 1);
            lastPos[num[pos]] = pos;
            ++pos;
        }
        result[query[i].pos] = sum(query[i].r) - sum(query[i].l - 1);
    }
    for (int i = 0; i < m; ++i)
        printf("%d\n", result[i]);
    return 0;
}

void init() {
    memset(query, 0, sizeof(query));
    memset(num, 0, sizeof(num));
    memset(c, 0, sizeof(c));
    memset(lastPos, 0, sizeof(lastPos));
    memset(result, 0, sizeof(result));
    n = read();
    for (int i = 1; i <= n; ++i)
        num[i] = read();
    m = read();
    for (int i = 0; i < m; ++i)
        query[i].l = read(), query[i].r = read(), query[i].pos = i;
}

inline int read() {
    char ch(getchar());
    int x(0);
    while (ch < '0' || ch > '9')ch = getchar();
    while (ch >= '0' && ch <= '9') {
        x = (x << 3) + (x << 1) + ch - '0';
        ch = getchar();
    }
    return x;
}

inline int lowbit(int x) {
    return (x & (-x));
}

bool cmp_r(const Query &a, const Query &b) {
    return a.r < b.r;
}

int sum(int x) {
    int result(0);
    while (x > 0) {
        result += c[x];
        x -= lowbit(x);
    }
    return result;
}

void insert(int x, int key) {
    while (x <= n) {
        c[x] += key;
        x += lowbit(x);
    }
}
