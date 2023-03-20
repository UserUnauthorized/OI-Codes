//Luogu - P2633
#include<bits/stdc++.h>

#ifdef CLION

#include<debug.h>

#else
#define debug(...)
#endif

typedef int valueType;
constexpr int maxN = 1e5 + 5, maxK = 20;
typedef std::array<valueType, maxN> ARRAY;
typedef std::array<ARRAY, maxK> STArray;
typedef std::vector<valueType> VECTOR;

int L_, R_, N_, M_, K_;
const int &L = L_, &R = R_, &N = N_, &M = M_, &K = K_;

struct SEGNODE {
    typedef SEGNODE self;
    typedef self *pointer;
    typedef ::valueType valueType;

    pointer leftSon, rightSon;
    self::valueType count;

    SEGNODE() : leftSon(nullptr), rightSon(nullptr), count(0) {};

    void update() {
        this->count = 0;

        if (this->leftSon != nullptr)
            this->count += this->leftSon->count;

        if (this->rightSon != nullptr)
            this->count += this->rightSon->count;
    }
};

struct EDGE {
    int next;
    int to;

    EDGE() : next(0), to(0) {};

    EDGE(int _next_, int _to_) : next(_next_), to(_to_) {}
};

typedef std::array<EDGE, maxN << 1> EdgeArray;
typedef SEGNODE::pointer pointer;
typedef std::array<pointer, maxN> PointerArray;

pointer newNode();

pointer build(valueType l, valueType r);

pointer insert(const pointer &current, valueType nodeL, valueType nodeR, valueType pos);

valueType
query(pointer xNode, pointer yNode, pointer lcaNode, pointer lcaFatherNode, valueType l, valueType r, valueType k);

valueType query(valueType x, valueType y, valueType k);

ARRAY source, father, head, depth;
STArray st;
PointerArray tree;
EdgeArray edge;
VECTOR point;

void init();

void dfs(int x, int from);

valueType lca(valueType x, valueType y);

int main() {
    init();

    dfs(1, 0);

    int lastAns = 0;
    for (int i = 0; i < M; ++i) {
        int x = 0, y = 0, k = 0;
        std::cin >> x >> y >> k;
        debug(x, y, k, lastAns);
        std::cout << (lastAns = point[query(x ^ lastAns, y, k)]) << '\n';
    }

    return 0;
}

void init() {
    std::cin >> N_ >> M_;

    K_ = ceil(log2(N));

    for (int i = 1; i <= N; ++i)
        std::cin >> source[i];

    for (int i = 1; i < N; ++i) {
        int a = 0, b = 0;
        std::cin >> a >> b;
        debug(i, a, b);
        edge[i << 1] = EDGE(head[a], b);
        edge[i << 1 | 1] = EDGE(head[b], a);
        head[a] = i << 1;
        head[b] = i << 1 | 1;
    }

    point.assign(source.begin() + 1, source.begin() + N + 1);
    point.push_back(INT_MIN);
    sort(point.begin(), point.end());
    point.erase(unique(point.begin(), point.end()), point.end());

    L_ = 1;
    R_ = (int) point.size() - 1;

    for (int i = 1; i <= N; ++i)
        source[i] = (int) distance(point.begin(), lower_bound(point.begin(), point.end(), source[i]));

    tree[0] = build(L, R);
}

pointer build(valueType l, valueType r) {
    pointer current = newNode();

    current->count = 0;

    if (l == r)
        return current;

    int const mid = (l + r) >> 1;

    current->leftSon = build(l, mid);
    current->rightSon = build(mid + 1, r);

    return current;
}

pointer insert(const pointer &current, valueType nodeL, valueType nodeR, valueType pos) {
    pointer result = newNode();
    *result = *current;

    if (nodeL == nodeR) {
        ++result->count;
        return result;
    }

    int const mid = (nodeL + nodeR) >> 1;

    if (pos <= mid)
        result->leftSon = insert(current->leftSon, nodeL, mid, pos);
    else
        result->rightSon = insert(current->rightSon, mid + 1, nodeR, pos);

    result->update();

    return result;
}

valueType query(valueType x, valueType y, valueType k) {
    valueType const LCA = lca(x, y);
    debug(x, y, LCA);
    return query(tree[x], tree[y], tree[LCA], tree[father[LCA]], L, R, k);
}

valueType
query(pointer xNode, pointer yNode, pointer lcaNode, pointer lcaFatherNode, valueType l, valueType r, valueType k) {
    if (l == r)
        return r;

    int const mid = (l + r) >> 1;

    int const preCount = xNode->count + yNode->count - lcaNode->count - lcaFatherNode->count;
    debug(xNode->count, yNode->count, lcaNode->count, lcaFatherNode->count, preCount, l, r, k);
    if (k <= preCount)
        return query(xNode->leftSon, yNode->leftSon, lcaNode->leftSon, lcaFatherNode->leftSon, l, mid, k);
    else
        return query(xNode->rightSon, yNode->rightSon, lcaNode->rightSon, lcaFatherNode->rightSon, mid + 1, r,
                     k - preCount);
}

pointer newNode() {
    static SEGNODE pool[maxN << 5], *allocp = pool - 1;
    return ++allocp;
}

void dfs(int x, int from) {
    depth[x] = depth[from] + 1;
    st[0][x] = father[x] = from;
    tree[x] = insert(tree[from], L, R, source[x]);

    for (int i = 1; i <= K; ++i)
        st[i][x] = st[i - 1][st[i - 1][x]];

    for (int i = head[x]; i; i = edge[i].next) {
        int const to = edge[i].to;

        if (to == from) continue;

        dfs(to, x);
    }
}

valueType lca(valueType x, valueType y) {
    if (depth[x] < depth[y])
        std::swap(x, y);

    for (int i = K; i >= 0; --i)
        if (depth[st[i][x]] >= depth[y])
            x = st[i][x];

    if (x == y)
        return x;

    for (int i = K; i >= 0; --i)
        if (st[i][x] != st[i][y])
            x = st[i][x], y = st[i][y];

    return father[x];
}
