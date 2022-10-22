//HZ - 39.3
#include <bits/stdc++.h>

using namespace std;

constexpr int maxn = 100005;

struct TREE {
    int l, r;
    long long min;
} tree[maxn << 2];

struct EDGE {
    int next;
    int to;
} edge[maxn];

int n, Q, root, cnt = 0, bin[20], head[maxn], value[maxn], source[maxn], fa[maxn][18], dep[maxn], in[maxn], out[maxn];

void dfs(int, int);
inline void addEdge(int, int);
void init();
void build(int, int, int);
void update(int, int, long long);
long long query(int, int, int);

int main() {
    init();
    dfs(root, 0);
}

void init() {
    memset(tree, 0, sizeof(tree));
    memset(edge, 0, sizeof(edge));
    memset(head, 0, sizeof(head));
    memset(value, 0, sizeof(value));
    memset(source, 0, sizeof(source));
    memset(in, 0, sizeof(in));
    memset(out, 0, sizeof(out));
    memset(dep, 0, sizeof(dep));
    memset(bin, 0, sizeof(bin));

    bin[0] = 1;
    for (int i = 1; i <= 16; ++i)
        bin[i] = bin[i - 1] << 1;

    scanf("%d%d", &n, &Q);

    for (int i = 1; i <= n; ++i) {
        int f;
        scanf("%d%d", &f, value + i);
        if (f == 0)root = i;
        addEdge(f, i);
    }

    cnt = 0;
}

inline void addEdge(int u, int v) {
    edge[++cnt].next = head[u];
    edge[cnt].to = v;
    head[u] = cnt;
}

void dfs(int x, int f) {
    in[x] = ++cnt;
    source[cnt] = value[x];
    dep[x] = dep[f] + 1;
    fa[x][0] = f;
    for (int i = 1; i <= 16; ++i) {
        fa[x][i] = fa[fa[x][i - 1]][i - 1];
    }
    for (int i = head[x]; i; i = edge[i].next) {
        dfs(edge[i].to, x);
    }
    out[x] = cnt;
}

void build(int id, int l, int r) {
    tree[id].l = l;
    tree[id].r = r;

    if (l == r) {
        tree[id].min = source[r];
        return;
    }

    int mid = (l + r) >> 1;
    build(id << 1, l, mid);
    build(id << 1 | 1, mid + 1, r);

    tree[id].min = min(tree[id << 1].min, tree[id << 1 | 1].min);
}

void update(int id, int pos, long long key) {
    if (tree[id].l == tree[id].r) {
        tree[id].min = key;
        return;
    }

    int mid = (tree[id].l + tree[id].r) >> 1;
    if (pos <= mid)update(id << 1, pos, key);

    tree[id].min = min(tree[id << 1].min, tree[id << 1 | 1].min);
}

long long query(int id, int l, int r) {
    if (l <= tree[id].l && tree[id].r <= r) {
        return tree[id].min;
    }

    int mid = (tree[id].l + tree[id].r) >> 1;
    if (l > mid)return query(id << 1 | 1, l, r);
    else if (r <= mid)return query(id << 1, l, r);
    else return min(query(id << 1 | 1, l, r),query(id << 1, l, r));
}