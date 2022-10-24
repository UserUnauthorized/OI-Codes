//HZ - 39.10
#include <bits/stdc++.h>

using namespace std;
constexpr int maxn = 10004, maxp = 20;

struct EDGE {
    int next;
    int to;

    EDGE() : next(-1), to(-1) {};

    EDGE(int _next, int _to) : next(_next), to(_to) {};
} edge[maxn];

int T, n, p, bin[maxp], degree[maxn], head[maxn], deep[maxn], fa[maxp][maxn];

void init();

void dfs(int, int);

int main() {
    bin[0] = 1;
    for (int i = 1; i < maxp; ++i)
        bin[i] = bin[i - 1] << 1;
    scanf("%d", &T);
    while (T--) {
        init();
        for (int i = 1; i <= n; ++i) {
            if (!degree[i]) {
                dfs(i, 0);
                break;
            }
        }
        int a, b;
        scanf("%d%d", &a, &b);
        if (deep[a] > deep[b])
            swap(a, b);
        int d = deep[b] - deep[a];
        for (int i = 0; i <= p; ++i)
            if (bin[i] & d)
                b = fa[i][b];
        if (a == b) {
            printf("%d\n", a);
            continue;
        }
        for (int i = p; i >= 0 && b != a; --i) {
            if (fa[i][a] != fa[i][b]) {
                a = fa[i][a];
                b = fa[i][b];
            }
        }
        printf("%d\n", fa[0][a]);
    }
}

void init() {
    memset(fa, 0, sizeof(fa));
    memset(head, 0xff, sizeof(head));
    memset(deep, 0, sizeof(deep));
    memset(degree, 0, sizeof(degree));

    scanf("%d", &n);
    p = (int) log2(n);

    for (int i = 1; i < n; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        edge[i] = EDGE(head[u], v);
        head[u] = i;

        ++degree[v];
    }
}

void dfs(int x, int from) {
    fa[0][x] = from;
    deep[x] = deep[from] + 1;
    for (int i = 1; i <= p; ++i) {
        fa[i][x] = fa[i - 1][fa[i - 1][x]];
    }
    for (int i = head[x]; i != -1; i = edge[i].next) {
        EDGE &e = edge[i];
        dfs(e.to, x);
    }
}