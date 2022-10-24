//HZ - 39.10
#include <bits/stdc++.h>

using namespace std;
constexpr int maxn = 10004, maxp = 16;

struct EDGE {
    int next;
    int to;

    EDGE() : next(-1), to(-1) {};

    EDGE(int _next, int _to) : next(_next), to(_next) {};
} edge[maxn << 1];

int T, n, p, head[maxn], fa[maxp][maxn];

void init();

void dfs(int, int);

int main() {
    scanf("%d", &T);
    while (T--) {
        init();
    }
}

void init() {
    memset(fa, 0, sizeof(fa));
    memset(head, 0xff, sizeof(head));

    scanf("%d", &n);
    p = (int) log2(n);

    for (int i = 1; i < n; ++i) {
        int a, b;
        scanf("%d%d", &a, &b);
        edge[i << 1] = EDGE(head[a], b);
        head[a] = i << 1;

        edge[i << 1 | 1] = EDGE(head[b], a);
        head[b] = i << 1 | 1;
    }
}

void dfs(int x, int from) {
    fa[0][x] = from;
    for (int i = 1; i <= p; ++i) {

    }
}