//HZ - 40.6
//Luogu - P2680
#include <bits/stdc++.h>

#ifdef LOCAL

#include<debug.h>

#else
#define debug(...)
#endif
using namespace std;
constexpr int maxn = 3e5 + 5;

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

    void operator()(std::initializer_list<pointer> args) {
        for (pointer iter: args)
            *iter = this->operator()();
    }
};

read_<int> read;

class NODE {
public:
    int sum;
    int without;

    class EDGE {
    public:
        int id;
        int weight;

        EDGE() : id(0), weight(-1) {};

        EDGE(int _id, int _weight) : id(_id), weight(_weight) {};

        inline bool operator<(const EDGE &object) const;
    } max;

    NODE() : sum(0), without(-1), max() {};

    NODE(int _id, int _t) : sum(_t), without(0), max(_id, _t) {};

    friend NODE merge(const NODE &left, const NODE &right);
};

class SEGMENT {
public:
    typedef const int &const_reference;
    typedef const SEGMENT &const_self_reference;

    SEGMENT() : _l_(0), _r_(0) {};

    SEGMENT(int _l, int _r) : _l_(_l), _r_(_r) {};

    inline const_reference l() const;

    inline const_reference r() const;

    inline bool operator<(const_self_reference object) const;

private:
    int _l_, _r_;
};

typedef vector<SEGMENT> PATH;

struct TREE {
    int l, r;
    NODE data;
    int lazy;
} tree[maxn << 2];

struct EDGE {
    int next;
    int to;

    EDGE() : next(-1), to(0) {};

    EDGE(int _next, int _to) : next(_next), to(_to) {};
} edge[maxn << 1];

void init();

void initDfs(int x, int from);

class DFS {
public:
    void operator()(int x, int TOP);

private:
    int _cnt_;
} dfs;

void build(int id, int l, int r);

void update(int id, int l, int r, const int &w);

NODE query(int id, int l, int r);

int query(int id, int pos);

void update(PATH path, int w);

int n, m, head[maxn], weight[maxn], father[maxn], dep[maxn], dfn[maxn], size[maxn], son[maxn], top[maxn], source[maxn], nodeId[maxn];
NODE MAXCost;

int main() {
    init();
    initDfs(1, 0);
    cerr << "DEBUG" << endl;
    dfs(1, 1);
    build(1, 1, n);
    while (m--) {
        int x(read()), y(read());
        PATH now;
        NODE result;
        while (top[x] != top[y]) {
            if (dep[top[x]] < dep[top[y]])
                swap(x, y);
            result = merge(result, query(1, dfn[top[x]], dfn[x]));
            now.emplace_back(dfn[top[x]], dfn[x]);
            x = father[top[x]];
        }

        if (dfn[x] > dfn[y])
            swap(x, y);

        if (x != y) {
            result = merge(result, query(1, dfn[x] + 1, dfn[y]));
            now.emplace_back(dfn[x] + 1, dfn[y]);
        }

        if (result.sum > MAXCost.sum)
            MAXCost = result;

        update(now, result.max.weight);
    }

    printf("%d\n", max(MAXCost.sum - MAXCost.max.weight, query(1, MAXCost.max.id)));

    return 0;
}

void init() {
    memset(head, 0xff, sizeof(head));
    read(&n, &m);
    for (int i = 1; i < m; ++i) {
        const int a(read()), b(read());
        read(weight[i]);
        edge[i << 1] = EDGE(head[a], b);
        edge[i << 1 | 1] = EDGE(head[b], a);

        head[a] = i << 1;
        head[b] = i << 1 | 1;
    }
}

NODE merge(const NODE &left, const NODE &right) {
    NODE result;
    result.sum = left.sum + right.sum;
    result.without = max(left.without, right.without);
    result.max = max(left.max, right.max);
    return result;
}

void initDfs(int x, int from) {
    debug(x, from);
    father[x] = from;
    size[x] = 1;
    dep[x] = dep[from] + 1;

    for (int i = head[x]; i != -1; i = edge[i].next) {
        const EDGE &e = edge[i];

        if (e.to == from)
            continue;

        source[e.to] = weight[i >> 1];
        initDfs(e.to, x);

        size[x] += size[e.to];

        if (size[e.to] > size[son[x]])
            son[x] = e.to;
    }
}

void build(int id, int l, int r) {
    tree[id].l = l;
    tree[id].r = r;

    if (l == r) {
        tree[id].data = NODE(r, source[nodeId[r]]);
        return;
    }

    int mid((l + r) >> 1);

    build(id << 1, l, mid);
    build(id << 1 | 1, mid + 1, r);

    tree[id].data = merge(tree[id << 1].data, tree[id << 1 | 1].data);
}

void update(PATH path, int w) {
    sort(path.begin(), path.end());

    int r(1);
    for (const SEGMENT &s: path) {
        if (r < s.l()) {
            update(1, r, s.l() - 1, w);
            r = s.r() + 1;
        }
    }
}

void update(int id, int l, int r, const int &w) {
    if (l <= tree[id].l && tree[id].r <= r) {
        tree[id].data.without = max(tree[id].data.without, w);
        tree[id].lazy = max(tree[id].lazy, w);
        return;
    }

    if (tree[id].lazy) {
        tree[id << 1].data.without = max(tree[id << 1].data.without, tree[id].lazy);
        tree[id << 1].lazy = max(tree[id << 1].lazy, tree[id].lazy);
        tree[id << 1 | 1].data.without = max(tree[id << 1 | 1].data.without, tree[id].lazy);
        tree[id << 1 | 1].lazy = max(tree[id << 1 | 1].lazy, tree[id].lazy);
        tree[id].lazy = 0;
    }

    int mid((tree[id].l + tree[id].r) >> 1);

    if (l <= mid)
        update(id << 1, l, r, w);
    if (r > mid)
        update(id << 1 | 1, l, r, w);

    tree[id].data = merge(tree[id << 1].data, tree[id << 1 | 1].data);
}

int query(int id, int pos) {
    if (tree[id].l == tree[id].r)
        return tree[id].data.without;

    if (tree[id].lazy) {
        tree[id << 1].data.without = max(tree[id << 1].data.without, tree[id].lazy);
        tree[id << 1].lazy = max(tree[id << 1].lazy, tree[id].lazy);
        tree[id << 1 | 1].data.without = max(tree[id << 1 | 1].data.without, tree[id].lazy);
        tree[id << 1 | 1].lazy = max(tree[id << 1 | 1].lazy, tree[id].lazy);
        tree[id].lazy = 0;
    }

    int mid((tree[id].l + tree[id].r) >> 1);

    if (pos <= mid)
        return query(id << 1, pos);
    else
        return query(id << 1 | 1, pos);
}

NODE query(int id, int l, int r) {
    if (l <= tree[id].l && tree[id].r <= r)
        return tree[id].data;

    if (tree[id].lazy) {
        tree[id << 1].data.without = max(tree[id << 1].data.without, tree[id].lazy);
        tree[id << 1].lazy = max(tree[id << 1].lazy, tree[id].lazy);
        tree[id << 1 | 1].data.without = max(tree[id << 1 | 1].data.without, tree[id].lazy);
        tree[id << 1 | 1].lazy = max(tree[id << 1 | 1].lazy, tree[id].lazy);
        tree[id].lazy = 0;
    }

    int mid((tree[id].l + tree[id].r) >> 1);

    if (r <= mid)
        return query(id << 1, l, r);
    else if (l > mid)
        return query(id << 1 | 1, l, r);
    else
        return merge(query(id << 1, l, r), query(id << 1 | 1, l, r));
}

bool NODE::EDGE::operator<(const NODE::EDGE &object) const {
    return this->weight < object.weight;
}

const int &SEGMENT::l() const {
    return this->_l_;
}

const int &SEGMENT::r() const {
    return this->_r_;
}

bool SEGMENT::operator<(const SEGMENT &object) const {
    return this->_l_ < object._l_;
}

void DFS::operator()(int x, int TOP) {
    dfn[x] = ++_cnt_;
    top[x] = x;
    nodeId[_cnt_] = x;

    if (!son[x])
        return;

    this->operator()(son[x], TOP);

    for (int i = head[x]; i != -1; i = edge[i].next)
        if (edge[i].to != father[x] && edge[i].to != son[x])
            this->operator()(edge[i].to, edge[i].to);
}
