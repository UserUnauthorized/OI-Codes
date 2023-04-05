//SPOJ - 375
#include<bits/stdc++.h>

using namespace std;
constexpr int maxn = 1e4 + 5;

inline int read();

void init();

void initDfs(int x, int from);

void dfs(int x, int TOP);

void build(int id, int l, int r);

void insert(int id, int pos, int key);

int query(int id, int l, int r);

int n, cnt(0), T;
int weight[maxn], source[maxn], to[maxn], top[maxn], head[maxn], size[maxn], dfn[maxn], nodeId[maxn], son[maxn], dep[maxn], father[maxn];

struct EDGE {
    int next;
    int to;

    EDGE() : next(0), to(0) {};

    EDGE(int _next, int _to) : next(_next), to(_to) {};
} edge[maxn << 1];

struct TREE {
    int l, r;
    int max;
} tree[maxn << 2];

int main() {
    cin >> T;
    while (T--) {
        init();
        initDfs(1, 0);
        dfs(1, 1);
        build(1, 1, n);

        for (string order; order != "DONE"; cin >> order) {
            if (order == "CHANGE") {
                int id(read()), key(read());
                insert(1, dfn[to[id]], key);
            } else if (order == "QUERY") {
                int x(read()), y(read());

                int result(INT_MIN);

                while (top[x] != top[y]) {
                    if (dep[top[x]] < dep[top[y]])
                        swap(x, y);
                    result = max(result, query(1, dfn[top[x]], dfn[x]));
                    x = father[top[x]];
                }

                if (dfn[x] > dfn[y])
                    swap(x, y);

                if (dfn[x] != dfn[y])
                    result = max(result, query(1, dfn[x] + 1, dfn[y]));

                printf("%d\n", result);
            }
        }
    }


    return 0;
}

void init() {
    memset(weight, 0, sizeof(weight));
    memset(source, 0, sizeof(source));
    memset(to, 0, sizeof(to));
    memset(top, 0, sizeof(top));
    memset(head, 0, sizeof(head));
    memset(size, 0, sizeof(size));
    memset(dfn, 0, sizeof(dfn));
    memset(nodeId, 0, sizeof(nodeId));
    memset(son, 0, sizeof(son));
    memset(dep, 0, sizeof(dep));
    memset(father, 0, sizeof(father));

    n = read();

    for (int i = 1; i < n; ++i) {
        int a(read()), b(read());
        weight[i] = read();

        edge[i << 1] = EDGE(head[a], b);
        edge[i << 1 | 1] = EDGE(head[b], a);

        head[a] = i << 1;
        head[b] = i << 1 | 1;
    }

    source[0] = source[1] = INT_MIN;
}

inline int read() {
    int ch(getchar()), result(0);
    bool positive(true);

    while ((ch < '0' || ch > '9') && ch != '-')
        ch = getchar();

    if (ch == '-') {
        positive = false;
        ch = getchar();
    }

    while (ch >= '0' && ch <= '9') {
        result = (result << 3) + (result << 1) + (ch & 15);
        ch = getchar();
    }

    return positive ? result : -result;
}

void initDfs(int x, int from) {
    dep[x] = dep[from] + 1;
    father[x] = from;
    size[x] = 1;

    for (int i = head[x]; i != 0; i = edge[i].next) {
        const EDGE &e = edge[i];

        if (e.to == from)
            continue;

        to[i >> 1] = e.to;
        source[e.to] = weight[i >> 1];
        initDfs(e.to, x);

        size[x] += size[e.to];

        if (size[e.to] > size[son[x]])
            son[x] = e.to;
    }
}

void dfs(int x, int TOP) {
    top[x] = TOP;
    dfn[x] = ++cnt;
    nodeId[cnt] = x;

    if (!son[x])
        return;

    dfs(son[x], TOP);

    for (int i = head[x]; i != 0; i = edge[i].next) {
        const EDGE &e = edge[i];
        if (e.to != son[x] && e.to != father[x])
            dfs(e.to, e.to);
    }
}

void build(int id, int l, int r) {
    tree[id].l = l;
    tree[id].r = r;

    if (l == r) {
        tree[id].max = source[nodeId[r]];
        return;
    }

    int mid((l + r) >> 1);

    build(id << 1, l, mid);
    build(id << 1 | 1, mid + 1, r);

    tree[id].max = max(tree[id << 1].max, tree[id << 1 | 1].max);
}

void insert(int id, int pos, int key) {
    if (tree[id].l == tree[id].r) {
        tree[id].max = key;
        return;
    }

    int mid((tree[id].l + tree[id].r) >> 1);

    if (pos <= mid)
        insert(id << 1, pos, key);
    else
        insert(id << 1 | 1, pos, key);

    tree[id].max = max(tree[id << 1].max, tree[id << 1 | 1].max);
}

int query(int id, int l, int r) {
    if (l <= tree[id].l && tree[id].r <= r)
        return tree[id].max;

    int mid((tree[id].l + tree[id].r) >> 1);

    if (r <= mid)
        return query(id << 1, l, r);
    else if (l > mid)
        return query(id << 1 | 1, l, r);
    else
        return max(query(id << 1, l, r), query(id << 1 | 1, l, r));
}

