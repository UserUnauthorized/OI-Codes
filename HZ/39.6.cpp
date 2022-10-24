//HZ - 39.6
#include <bits/stdc++.h>

using namespace std;

constexpr int maxn = 80004;

struct EDGE {
    int next;
    int to;
    int weight;
} edge[maxn];

int n, m, Q, cnt = 0, head[maxn], st[maxn << 1][18], source[maxn << 1], dfn[maxn], dep[maxn], len[maxn];

void init();

void addEdge(int, int, int);

void dfs(int, int);

int MIN(const int &, const int &);

int LCA(int, int);

int main() {
    init();
    dfs(1, 0);

    for (int i = 1; i <= cnt; ++i) {
        st[i][0] = source[i];
    }

    for (int j = 1; j <= (int) log2(cnt); ++j)
        for (int i = 1; i + (1 << j) <= cnt; ++i)
            st[i][j] = MIN(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);

    for (int i = 0; i < Q; ++i) {
        int a, b;
        scanf("%d%d", &a, &b);
        int lca(LCA(a, b));
        printf("%d\n", len[a] + len[b] - (len[lca] << 1));
    }
    return 0;
}

void init() {
    memset(edge, 0, sizeof(edge));
    memset(head, 0, sizeof(head));
    memset(source, 0, sizeof(source));
    memset(dep, 0, sizeof(dep));
    memset(len, 0, sizeof(len));
    memset(dfn, 0, sizeof(dfn));

    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; ++i) {
        int a, b, w;
        char rubbish(0);
        scanf("%d%d%d", &a, &b, &w);
        while (rubbish != 'E' && rubbish != 'S' && rubbish != 'N' && rubbish != 'W')
            rubbish = getchar();
        addEdge(a, b, w);
        addEdge(b, a, w);
    }

    scanf("%d", &Q);
    cnt = 0;
}

void addEdge(int u, int v, int w) {
    edge[++cnt].next = head[u];
    edge[cnt].weight = w;
    edge[cnt].to = v;
    head[u] = cnt;
}

void dfs(int x, int fa) {
    source[++cnt] = x;
    dfn[x] = cnt;
    dep[x] = dep[fa] + 1;

    for (int i = head[x]; i; i = edge[i].next) {
        int to(edge[i].to);
        if (to == fa)
            continue;
        len[to] = len[x] + edge[i].weight;
        dfs(to, x);
        source[++cnt] = x;
    }
}

int MIN(const int &a, const int &b) {
    if (dep[a] > dep[b])return b;
    else return a;
}

int LCA(int a, int b) {
    int l(dfn[a]), r(dfn[b]);
    if (l > r)
        swap(l, r);
    //int k((int) log2(r - l + 1));
    int k(0);
    while ((1 << (k + 1)) <= r - l + 1)
        ++k;
    return MIN(st[l][k], st[r - (1 << k) + 1][k]);
}