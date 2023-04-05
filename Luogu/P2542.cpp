//line
//HZ - 657.2
//Luogu - P2542
#include<bits/stdc++.h>

namespace DEBUG {
    template<typename T>
    inline void _debug(const char *format, T t) {
        std::cerr << format << '=' << t << std::endl;
    }

    template<class First, class... Rest>
    inline void _debug(const char *format, First first, Rest... rest) {
        while (*format != ',') std::cerr << *format++;
        std::cerr << '=' << first << ",";
        _debug(format + 1, rest...);
    }

    template<typename T>
    std::ostream &operator<<(std::ostream &os, const std::vector<T> &V) {
        os << "[ ";
        for (const auto &vv: V) os << vv << ", ";
        os << "]";
        return os;
    }

    std::ostream &operator<<(std::ostream &os, __int128 V) {
        if (V < 0) {
            os << '-';
            V = -V;
        }

        if (V > 9)
            os << V / 10;

        os << (int) (V % 10);

        return os;
    }

#define debug(...) _debug(#__VA_ARGS__, __VA_ARGS__)
}  // namespace DEBUG

using namespace DEBUG;

constexpr int maxN = 3e4 + 5, maxM = 1e5 + 5, maxQ = 4e4 + 5;

struct EDGE {
    int next;
    int to;
    bool exist;

    EDGE() : next(0), to(0), exist(true) {};

    EDGE(int _next_, int _to_) : next(_next_), to(_to_), exist(true) {};
};

struct SEGNODE {
    int l, r;
    int count;
    int lazy;

    SEGNODE() : l(0), r(0), count(0), lazy(-1) {};
};

struct OPERATOR {
    bool type;
    int a;
    int b;

    OPERATOR() : type(0), a(0), b(0) {};

    OPERATOR(int _type_, int _a_, int _b_) : type(_type_), a(_a_), b(_b_) {};
};

int N_, M_, Q_ = 0, sccnum_, ROOT_;
int const &N = N_, &M = M_, &Q = Q_, &sccnum = sccnum_, &ROOT = ROOT_;

typedef std::pair<int, int> PAIR;

std::array<EDGE, maxM << 1> sourceEdge, treeEdge;
std::array<SEGNODE, maxN << 2> tree;
std::bitset<maxM << 1> cut;
std::bitset<maxN> vis;
std::array<int, maxN> weight, dfn, top, size, son, depth, belong, low, father, sourceHead, treeHead;
std::array<OPERATOR, maxQ> oper;
std::stack<int> st, ans;
std::map<PAIR, int> edgeMap;

void init();

void tarjan(int x, int from);

void build();

void build(int id, int l, int r);

void update(int id, int l, int r, int key);

int query(int id, int l, int r);

void initDfs(int x, int from);

void dfs(int x, int TOP);

int main() {
//	freopen("line.in", "r", stdin);
//	freopen("line.out", "w", stdout);

    init();

    tarjan(1, 0);

    dfn.fill(0);

    build();

    initDfs(1, 0);

    dfs(1, 1);

    build(1, 1, sccnum);

    for (int i = Q; i > 0; --i) {
        if (oper[i].type) {
            int x = belong[oper[i].a], y = belong[oper[i].b];

            int result = 0;

            while (top[x] != top[y]) {
                if (depth[top[x]] < depth[top[y]])
                    std::swap(x, y);

                result = result + query(1, dfn[top[x]], dfn[x]);
                debug(x, y, result);
                x = father[top[x]];
            }

            if (dfn[x] > dfn[y])
                std::swap(x, y);

            if (dfn[x] < dfn[y])
                result = result + query(1, dfn[x] + 1, dfn[y]);

            ans.push(result);
        } else {
            int x = belong[oper[i].a], y = belong[oper[i].b];

            while (top[x] != top[y]) {
                if (depth[top[x]] < depth[top[y]])
                    std::swap(x, y);

                update(1, dfn[top[x]], dfn[x], 0);
                x = father[top[x]];
            }

            if (dfn[x] > dfn[y])
                std::swap(x, y);

            if (dfn[x] < dfn[y])
                update(1, dfn[x] + 1, dfn[y], 0);
        }
    }

    while (!ans.empty()) {
        std::cout << ans.top() << '\n';
        ans.pop();
    }

    return 0;
}

void init() {
    std::cin >> N_ >> M_;

    for (int i = 1; i <= M; ++i) {
        int a, b;
        std::cin >> a >> b;

        if (a > b)
            std::swap(a, b);

        PAIR const t = std::make_pair(a, b);

        edgeMap[t] = i;

        sourceEdge[i << 1] = EDGE(sourceHead[a], b);
        sourceEdge[i << 1 | 1] = EDGE(sourceHead[b], a);

        sourceHead[a] = i << 1;
        sourceHead[b] = i << 1 | 1;
    }

    int c = 0;
    while (c != -1) {
        int a, b;
        std::cin >> c;

        if (c == -1)
            break;

        std::cin >> a >> b;

        oper[++Q_] = OPERATOR((c == 1), a, b);

        if (c == 0) {
            if (a > b)
                std::swap(a, b);

            PAIR const t = std::make_pair(a, b);

            int const i = edgeMap[t];

            sourceEdge[i << 1].exist = sourceEdge[i << 1 | 1].exist = false;
        }
    }
}

void tarjan(int x, int from) {
    static int cnt = 0;

    dfn[x] = low[x] = ++cnt;

    st.push(x);
    vis[x] = true;

    for (int i = sourceHead[x]; i != 0; i = sourceEdge[i].next) {
        if (!sourceEdge[i].exist) continue;

        int const to = sourceEdge[i].to;

        if (to == from)
            continue;

        if (!dfn[to]) {
            tarjan(to, x);

            low[x] = std::min(low[x], low[to]);

        } else if (vis[to]) {
            low[x] = std::min(low[x], dfn[to]);
        }
    }

    if (dfn[x] == low[x]) {
        ++sccnum_;
        int y;
        do {
            y = st.top();
            st.pop();
            belong[y] = sccnum;
        } while (y != x);
    }
}

void build() {
    int cnt = 0;

    for (int x = 1; x <= N; ++x) {
        for (int i = sourceHead[x]; i != 0; i = sourceEdge[i].next) {
            if (!sourceEdge[i].exist) continue;

            int const to = sourceEdge[i].to;

            if (belong[x] == belong[to]) continue;

            int const a = belong[x], b = belong[to];

            treeEdge[++cnt] = EDGE(treeHead[a], b);
            treeHead[a] = cnt;
        }
    }
}

void initDfs(int x, int from) {
    depth[x] = depth[from] + 1;

    father[x] = from;

    size[x] = 1;

    for (int i = treeHead[x]; i != 0; i = treeEdge[i].next) {
        int const to = treeEdge[i].to;

        if (to == from)
            continue;

        initDfs(to, x);

        size[x] += size[to];

        if (size[to] > size[son[x]])
            son[x] = to;
    }
}

void dfs(int x, int TOP) {
    static int cnt = 0;

    top[x] = TOP;

    dfn[x] = ++cnt;

    if (!son[x])
        return;

    dfs(son[x], TOP);

    for (int i = treeHead[x]; i != 0; i = treeEdge[i].next) {
        int const to = treeEdge[i].to;

        if (to != son[x] && to != father[x])
            dfs(to, to);
    }
}

void build(int id, int l, int r) {
    tree[id].l = l;
    tree[id].r = r;

    if (l == r) {
        tree[id].count = (r > 1);
        return;
    }

    int const mid = (l + r) >> 1;

    build(id << 1, l, mid);
    build(id << 1 | 1, mid + 1, r);

    tree[id].count = tree[id << 1].count + tree[id << 1 | 1].count;
}

void update(int id, int l, int r, int key) {
    if (l <= tree[id].l && tree[id].r <= r) {
        tree[id].count = (tree[id].r - tree[id].l + 1) * key;
        tree[id].lazy = key;
        return;
    }

    if (tree[id].lazy != -1) {
        tree[id << 1].count = (tree[id << 1].r - tree[id << 1].l + 1) * tree[id].lazy;
        tree[id << 1 | 1].count = (tree[id << 1 | 1].r - tree[id << 1 | 1].l + 1) * tree[id].lazy;
        tree[id << 1].lazy = tree[id].lazy;
        tree[id << 1 | 1].lazy = tree[id].lazy;
        tree[id].lazy = -1;
    }

    int const mid = (tree[id].l + tree[id].r) >> 1;

    if (l <= mid)
        update(id << 1, l, r, key);
    if (r > mid)
        update(id << 1 | 1, l, r, key);

    tree[id].count = tree[id << 1].count + tree[id << 1 | 1].count;
}

int query(int id, int l, int r) {
    if (l <= tree[id].l && tree[id].r <= r)
        return tree[id].count;

    if (tree[id].lazy != -1) {
        tree[id << 1].count = (tree[id << 1].r - tree[id << 1].l + 1) * tree[id].lazy;
        tree[id << 1 | 1].count = (tree[id << 1 | 1].r - tree[id << 1 | 1].l + 1) * tree[id].lazy;
        tree[id << 1].lazy = tree[id].lazy;
        tree[id << 1 | 1].lazy = tree[id].lazy;
        tree[id].lazy = -1;
    }

    int const mid = (tree[id].l + tree[id].r) >> 1;

    if (r <= mid)
        return query(id << 1, l, r);
    else if (l > mid)
        return query(id << 1 | 1, l, r);
    else
        return query(id << 1, l, r) + query(id << 1 | 1, l, r);
}
