//HZ - 17.7
#include<bits/stdc++.h>

using namespace std;

int s[302][302][102], f[302][302], n, m, q;

void init();
inline int lowbit(int);
void update(int, int, int);
int sum(int, int, int);

int main() {
    init();
    for (int i = 0; i < q; ++i) {
        int t;
        scanf("%d", &t);
        if (t == 2) {
            int x1, x2, y1, y2, key;
            scanf("%d%d%d%d%d", &x1, &x2, &y1, &y2, &key);
            printf("%d\n", sum(x2, y2, key) - sum(x1 - 1, y2, key) - sum(x2, y1 - 1, key) + sum(x1 - 1, y1 - 1, key));
        } else if (t == 1) {
            int x, y, key;
            scanf("%d%d%d", &x, &y, &key);
            update(x, y, key);
        }
    }
    return 0;
}

void init() {
    memset(s, 0, sizeof(s));
    memset(f, 0, sizeof(f));
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            int key;
            scanf("%d", &key);
            update(i, j, key);
        }
    }
    scanf("%d", &q);
}

inline int lowbit(int x) {
    return x & (-x);
}

void update(int x, int y, int key) {
    for (int i = x; i <= n; i += lowbit(i)) {
        for (int j = y; j <= m; j += lowbit(j)) {
            --s[i][j][f[x][y]];
            ++s[i][j][key];
        }
    }
    f[x][y] = key;
}

int sum(int x, int y, int key) {
    if (x <= 0 || y <= 0)return 0;
    int result(0);
    for (; x > 0; x -= lowbit(x)) {
        for (int i = y; i > 0; i -= lowbit(i)) {
            result += s[x][i][key];
        }
    }
    return result;
}
