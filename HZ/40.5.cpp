//HZ - 40.5
//Luogu - P1967
/* UTF-8 : 树链剖分做法 */
#include <bits/stdc++.h>

#ifdef LOCAL

#include<debug.h>

#else
#define debug(...)
#endif
using namespace std;
constexpr int maxn = 1e4 + 5, maxm = 5e4 + 5, maxP = 12;

struct EDGE {
    int next;
    int to;
    int weight;

    EDGE() : next(0), to(-1), weight(-1) {};

    EDGE(int _next, int _to, int _weight) : next(_next), to(_to), weight(_weight) {};
} edge[maxn << 1];

struct sourceEDGE {
    int from;
    int to;
    int weight;

    sourceEDGE() : from(-1), to(-1), weight(-1) {};

    sourceEDGE(int _weight, int _to, int _from) : from(_from), to(_to), weight(_weight) {};

    inline bool operator<(const sourceEDGE &object) const {
        return this->weight > object.weight;
    }
} sourceEdge[maxm];

inline int read();

int find(int x);

void init();

void build();

void dfs(int x, int from, const int &_root);

void initST();

void dfs(int x, int _top);

int query(int l, int r);

int n, m, Q, p, cnt(0);
int dfn[maxn], head[maxn], sourceHead[maxn], nodeId[maxn], father[maxn], dep[maxn], son[maxn], top[maxn], size[maxn], st[maxP][maxn], source[maxn], root[maxn];

int main() {
    init();
    build();

    for (int i = 1; i <= n; ++i) {
        if (!root[i]) {
            dfs(i, i, i);
            dfs(i, i);
            source[i] = 1e7;
        }
    }

    initST();

    while (Q--) {
        int x(read()), y(read());
        if (root[x] != root[y]) {
            printf("%d\n", -1);
            continue;
        }

        int result(1e7);

        while (top[x] != top[y]) {
            if (dep[top[x]] < dep[top[y]])
                swap(x, y);
            result = min(result, query(dfn[top[x]], dfn[x]));
            x = father[top[x]];
        }

        if (dfn[x] > dfn[y])
            swap(x, y);

        if (x != y)
            result = min(result, query(dfn[x] + 1, dfn[y]));

        printf("%d\n", result);
    }
}

int read() {
    int result(0), input(getchar());

    while (input < '0' || input > '9')
        input = getchar();

    while (input >= '0' && input <= '9') {
        result = (result << 3) + (result << 1) + (input & 15);
        input = getchar();
    }

    return result;
}

void init() {
    memset(sourceHead, 0xff, sizeof(sourceHead));
    memset(head, 0xff, sizeof(head));
    memset(source, 0xff, sizeof(source));
    memset(st, 0x7f, sizeof(st));

    ::n = read(), ::m = read();
    ::p = (int) log2(n);

    for (int i = 0; i < m; ++i)
        sourceEdge[i] = sourceEDGE(read(), read(), read());

    for (int i = 1; i <= n; ++i)
        father[i] = i;

    Q = read();
}

void dfs(int x, int from, const int &_root) {
    root[x] = _root;
    father[x] = from;
    dep[x] = dep[from] + 1;
    size[x] = 1;

    for (int i = head[x]; i != -1; i = edge[i].next) {
        const EDGE &e = edge[i];

        if (e.to == from)
            continue;

        source[e.to] = e.weight;
        dfs(e.to, x, _root);

        size[x] += size[e.to];

        if (size[e.to] > size[son[x]])
            son[x] = e.to;
    }
}

void dfs(int x, int _top) {
    top[x] = _top;
    dfn[x] = ++cnt;
    nodeId[cnt] = x;

    if (!son[x])
        return;

    dfs(son[x], _top);

    for (int i = head[x]; i != -1; i = edge[i].next)
        if (!dfn[edge[i].to])
            dfs(edge[i].to, edge[i].to);
}

void initST() {
    for (int i = 1; i <= n; ++i)
        st[0][i] = source[nodeId[i]];

    for (int j = 1; j < p; ++j)
        for (int i = 1; i + (1 << (j - 1)) <= n; ++i)
            st[j][i] = min(st[j - 1][i], st[j - 1][i + (1 << (j - 1))]);
}

int query(int l, int r) {
    int _p = (int) log2(r - l + 1);
    return min(st[_p][l], st[_p][r - (1 << _p) + 1]);
}

void build() {
    int count(0);
    sort(sourceEdge, sourceEdge + m);

    for (int i = 0; i < m; ++i) {
        if (find(sourceEdge[i].from) != find(sourceEdge[i].to)) {
            edge[++count] = EDGE(head[sourceEdge[i].from], sourceEdge[i].to, sourceEdge[i].weight);
            head[sourceEdge[i].from] = count;

            edge[++count] = EDGE(head[sourceEdge[i].to], sourceEdge[i].from, sourceEdge[i].weight);
            head[sourceEdge[i].to] = count;

            if (cnt >> 1 == n - 1)
                break;

            father[find(sourceEdge[i].from)] = find(sourceEdge[i].to);
        }
    }
}

int find(int x) {
    if (father[x] == x)return x;
    else return father[x] = find(father[x]);
}
