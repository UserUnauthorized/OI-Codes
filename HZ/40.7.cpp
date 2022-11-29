//Luogu - P3979
//HZ - 40.7
#include <bits/stdc++.h>

#ifdef LOCAL

#include<debug.h>

#else
#define debug(...)
#endif
using namespace std;
constexpr int maxn = 1e5 + 5;

template<typename T>
struct read_ {
    typedef T value_type;
    typedef T &reference;
    typedef T *pointer;

    inline value_type operator()() {
        value_type result(0);
        bool positive(true);
        int input(getchar());

        while (input < '0' || input > '9') {
            positive = true;
            while ((input < '0' || input > '9') && input != '-')
                input = getchar();

            if (input == '-') {
                positive = false;
                input = getchar();
            }
        }

        while (input >= '0' && input <= '9') {
            result = (result << 3) + (result << 1) + (input & 15);
            input = getchar();
        }

        return positive ? result : -result;
    }

    inline void operator()(reference object) {
        object = this->operator()();
    }

    inline void operator()(pointer object) {
        *object = this->operator()();
    }

    template<class ... Args>
    void operator()(Args...args) {
        this->operator()(std::initializer_list<pointer>{args...});
    }

    template<typename ...Args>
    void operator()(reference first, Args &...args) {

    }

    void operator()(std::initializer_list<pointer> args) {
        for (pointer iter: args)
            *iter = this->operator()();
    }
};

read_<int> read;

struct TREE {
    int l, r;
    int min;
    int lazy;
} tree[maxn << 2];

void init();

void initDfs(int x, int from);

void build(int id, int l, int r);

void update(int id, int l, int r, int key);

int query(int id, int l, int r);

int n, m, p, root, source[maxn], dfn[maxn], size[maxn], bin[20], top[maxn], nodeId[maxn], dep[maxn], son[maxn], father[20][maxn];
vector<int> edge[maxn];

struct IN {
    int operator[](int x);
} in;

struct OUT {
    int operator[](int x);
} out;

struct DFS {
    int _cnt_;

    void operator()(int x, int TOP);
} dfs;

int main() {
    init();
    initDfs(1, 0);
    dfs(1, 1);
    build(1, 1, n);
    while (m--) {
        int opt(read());
        if (opt == 1) {
            read(root);
        } else if (opt == 2) {
            int x(read()), y(read()), z(read());
            while (top[x] != top[y]) {
                if (dep[top[x]] < dep[top[y]])
                    swap(x, y);
                update(1, dfn[top[x]], dfn[x], z);
                x = father[0][top[x]];
            }

            if (dfn[x] > dfn[y])
                swap(x, y);

            update(1, dfn[x], dfn[y], z);
        } else if (opt == 3) {
            int x(read());
            if (x == root) {
                printf("%d\n", tree[1].min);
                continue;
            } else if (in[x] <= in[root] && out[root] <= out[x]) {
                int y = root, d = dep[root] - dep[x] - 1;
                for (int i = 0; i <= p; ++i)
                    if (bin[i] & d)
                        y = father[i][y];
                printf("%d\n", min(query(1, 1, in[y] - 1), query(1, out[y] + 1, n)));
            } else {
                printf("%d\n", query(1, in[x], out[x]));
            }
        }
    }
    return 0;
}


void init() {
    read(&n, &m);
    p = (int) log2(n);

    for (int i = 1; i < n; ++i) {
        int u(read()), v(read());
        edge[u].emplace_back(v);
        edge[v].emplace_back(u);
    }

    for (int i = 1; i <= n; ++i)
        read(source[i]);

    read(root);

    bin[0] = 1;
    for (int i = 1; i <= p; ++i)
        bin[i] = bin[i - 1] << 1;
}

void initDfs(int x, int from) {
    father[0][x] = from;
    dep[x] = dep[from] + 1;
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

void build(int id, int l, int r) {
    tree[id].l = l;
    tree[id].r = r;

    if (l == r) {
        tree[id].min = source[nodeId[r]];
        return;
    }

    int mid((l + r) >> 1);

    build(id << 1, l, mid);
    build(id << 1 | 1, mid + 1, r);

    tree[id].min = min(tree[id << 1].min, tree[id << 1 | 1].min);
}

void update(int id, int l, int r, int key) {
    if (l <= tree[id].l && tree[id].r <= r) {
        tree[id].min = tree[id].lazy = key;
        return;
    }

    if (tree[id].lazy) {
        tree[id << 1].min = tree[id << 1 | 1].min = tree[id << 1].lazy = tree[id << 1 | 1].lazy = tree[id].lazy;
        tree[id].lazy = 0;
    }

    int mid((tree[id].l + tree[id].r) >> 1);

    if (l <= mid)
        update(id << 1, l, r, key);
    if (r > mid)
        update(id << 1 | 1, l, r, key);

    tree[id].min = min(tree[id << 1].min, tree[id << 1 | 1].min);
}

int query(int id, int l, int r) {
    if (l > r)
        return INT_MAX;

    if (l <= tree[id].l && tree[id].r <= r)
        return tree[id].min;

    if (tree[id].lazy) {
        tree[id << 1].min = tree[id << 1 | 1].min = tree[id << 1].lazy = tree[id << 1 | 1].lazy = tree[id].lazy;
        tree[id].lazy = 0;
    }

    int mid((tree[id].l + tree[id].r) >> 1);

    if (r <= mid)
        return query(id << 1, l, r);
    else if (l > mid)
        return query(id << 1 | 1, l, r);
    else
        return min(query(id << 1, l, r), query(id << 1 | 1, l, r));
}

void DFS::operator()(int x, int TOP) {
    ::top[x] = TOP;
    ::dfn[x] = ++_cnt_;
    ::nodeId[_cnt_] = x;

    if (!::son[x])
        return;

    this->operator()(son[x], TOP);

    for (const int &iter: edge[x])
        if (!dfn[iter])
            this->operator()(iter, iter);
}

int IN::operator[](int x) {
    return ::dfn[x];
}

int OUT::operator[](int x) {
    return ::dfn[x] + ::size[x] - 1;
}
