//HZ - 40.1
//Luogu - P2590
#include<bits/stdc++.h>

using namespace std;
constexpr int maxn = 3e4 + 5, maxp = 25;

struct NODE {
    int max, sum;

    NODE() : max(-1e9), sum(0) {};

    NODE(int _n) : max(_n), sum(_n) {};

    NODE(int _max, int _sum) : max(_max), sum(_sum) {};

    NODE operator+(const NODE &object) const {
        return NODE(std::max(this->max, object.max), this->sum + object.sum);
    }
};

void initDfs(int x, int from);

void dfs(int x, int TOP);

void init();

inline int read();

void build(int id, int l, int r);

void insert(int id, int pos, int key);

NODE query(int id, int l, int r);

int LCA(int a, int b);

vector<int> edge[maxn];
int n, Q, p, cnt(0);
int weight[maxn], dfn[maxn], pos[maxn], size[maxn], son[maxn], dep[maxn], top[maxn], father[maxp][maxn];

struct TREE {
    int l, r;
    NODE data;
} tree[maxn << 2];

int main() {
    init();
    initDfs(1, 0);
    dfs(1, 1);
    build(1, 1, n);

    while (Q--) {
        string order;
        cin >> order;
        if (order == "CHANGE") {
            int pos(read()), key(read());
            insert(1, dfn[pos], key);
        } else {
            int x(read()), y(read());

            NODE result;

            while (top[x] != top[y]) {
                if (dep[top[x]] < dep[top[y]])
                    swap(x, y);
                result = result + query(1, dfn[top[x]], dfn[x]);
                x = father[0][top[x]];
            }

            if (dfn[x] > dfn[y])
                swap(x, y);

            result = result + query(1, dfn[x], dfn[y]);

            if (order == "QMAX")
                printf("%d\n", result.max);
            else
                printf("%d\n", result.sum);
        }
    }
    return 0;
}

void init() {
    memset(weight, 0, sizeof(weight));
    memset(dfn, 0, sizeof(dfn));
    memset(pos, 0, sizeof(pos));
    memset(size, 0, sizeof(size));
    memset(son, 0, sizeof(son));
    memset(dep, 0, sizeof(dep));
    memset(father, 0, sizeof(father));

    n = read();

    p = (int) log2(n);

    for (int i = 1; i < n; ++i) {
        int a(read()), b(read());
        edge[a].emplace_back(b);
        edge[b].emplace_back(a);
    }

    for (int i = 1; i <= n; ++i)
        weight[i] = read();

    Q = read();
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
    father[0][x] = from;
    size[x] = 1;

    for (int i = 1; i <= p; ++i)
        father[i][x] = father[i - 1][father[i - 1][x]];

    for (const int &iter: edge[x]) {
        if (iter == from)
            continue;
        initDfs(iter, x);

        size[x] += size[iter];

        if (size[iter] > size[son[x]])
            son[x] = iter;
    }
}

void dfs(int x, int TOP) {
    top[x] = TOP;
    dfn[x] = ++cnt;
    pos[cnt] = x;

    if (!son[x])
        return;

    dfs(son[x], TOP);

    for (const int &iter: edge[x])
        if (iter != son[x] && iter != father[0][x])
            dfs(iter, iter);
}

int LCA(int a, int b) {
    if (dep[a] > dep[b])
        swap(a, b);

    for (int t(dep[b] - dep[a]), j(0); t > 0; ++j, t >>= 1)
        if (t & 1)
            b = father[j][b];

    if (a == b)
        return a;

    for (int j = p; j >= 0 && a != b; --j) {
        if (father[j][a] != father[j][b]) {
            a = father[j][a];
            b = father[j][b];
        }
    }

    return father[0][a];
}

void build(int id, int l, int r) {
    tree[id].l = l;
    tree[id].r = r;

    if (l == r) {
        tree[id].data = NODE(weight[pos[r]]);
        return;
    }

    int mid((l + r) >> 1);

    build(id << 1, l, mid);
    build(id << 1 | 1, mid + 1, r);

    tree[id].data = tree[id << 1].data + tree[id << 1 | 1].data;
}

NODE query(int id, int l, int r) {
    if (l <= tree[id].l && tree[id].r <= r)
        return tree[id].data;

    int mid((tree[id].l + tree[id].r) >> 1);

    if (r <= mid)
        return query(id << 1, l, r);
    if (l > mid)
        return query(id << 1 | 1, l, r);

    return query(id << 1, l, r) + query(id << 1 | 1, l, r);
}

void insert(int id, int pos, int key) {
    if (tree[id].l == tree[id].r) {
        tree[id].data = NODE(key);
        return;
    }

    int mid((tree[id].l + tree[id].r) >> 1);

    if (pos <= mid)
        insert(id << 1, pos, key);
    else
        insert(id << 1 | 1, pos, key);

    tree[id].data = tree[id << 1].data + tree[id << 1 | 1].data;
}
