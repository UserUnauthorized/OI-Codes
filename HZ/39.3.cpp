//HZ - 39.3
#include <bits/stdc++.h>
//#include <D:\OI\OI-Codes\Template\debug.h>

using namespace std;
//using namespace DEBUG;

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
    build(1, 1, n);

    for (; Q > 0; --Q) {
        char order = getchar();
        while (order != 'V' && order != 'E' && order != 'Q')
            order = getchar();
        if (order == 'V') {
            int x;
            long long y;
            scanf("%d%lld", &x, &y);
            //debug(order, x, y, in[x]);
            update(1, in[x], y);
        } else if (order == 'E') {
            int x;
            scanf("%d", &x);
            root = x;
        } else {
            int x;
            scanf("%d", &x);
            //debug(order, x);
            if (x == root) {
                printf("%lld\n", tree[1].min);
            } else if (in[x] <= in[root] && out[root] <= out[x]) {
                int y = root, d = dep[root] - dep[x] - 1;
                for (int i = 0; i <= 16; ++i) {
                    if (bin[i] & d) y = fa[y][i];
                }
                printf("%lld\n", min(query(1, 1, in[y] - 1), query(1, out[y] + 1, n)));
            } else {
                printf("%lld\n", query(1, in[x], out[x]));
            }
        }
    }
    return 0;
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
        if (f == 0) {
            root = i;
            continue;
        }
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
        if (bin[i] <= dep[x])fa[x][i] = fa[fa[x][i - 1]][i - 1];
        else break;
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
        //debug(id, tree[id].min, key, tree[id].l, tree[id].r, pos);
        return;
    }

    int mid = (tree[id].l + tree[id].r) >> 1;
    if (pos <= mid)update(id << 1, pos, key);
    else update(id << 1 | 1, pos, key);

    tree[id].min = min(tree[id << 1].min, tree[id << 1 | 1].min);
}

long long query(int id, int l, int r) {
    if (l > r)
        return LONG_LONG_MAX;

    if (l <= tree[id].l && tree[id].r <= r) {
        return tree[id].min;
    }

    int mid = (tree[id].l + tree[id].r) >> 1;
    if (l > mid)return query(id << 1 | 1, l, r);
    else if (r <= mid)return query(id << 1, l, r);
    else return min(query(id << 1 | 1, l, r), query(id << 1, l, r));
}