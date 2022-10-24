//HZ - 39.9
#include <bits/stdc++.h>

using namespace std;

constexpr int maxn = 100005, maxm = 300005, maxQ = 100005, maxp = 20;

struct EDGE {
    int from;
    int next;
    int to;
    int weight;
    int LCA;

    EDGE() : LCA(-1) {};

    EDGE(int _next, int _from, int _to) : next(_next), from(_from), to(_to), LCA(-1) {};

    EDGE(int _next, int _from, int _to, int _weight) : next(_next), from(_from), to(_to), weight(_weight), LCA(-1) {};

    bool operator<(const EDGE &object) {
        return this->weight < object.weight;
    }
} edge[maxn << 1], sourceEdge[maxm << 1], queryEdge[maxQ << 1];

int n, m, Q, p, cnt = 0, head[maxn], deep[maxn], queryHead[maxn], root[maxn], father[maxn], fa[maxp][maxn], way[maxp][maxn];

bool visited[maxn];

void init();

void build();

void tarjan(int);

void dfs(int, int, const int &);

int find(int);

int maxWeight(int, int);

int main() {
    init();
    for (int i = 1; i <= n; ++i)
        if (!visited[i])
            dfs(i, 0, i);
    memset(visited, 0, sizeof(visited));

    for (int i = 1; i <= p; ++i)
        for (int j = 1; j <= n; ++j)
            way[i][j] = max(way[i - 1][j], way[i - 1][fa[i - 1][j]]);

    for (int i = 1; i <= n; ++i)
        if (!visited[i])
            tarjan(i);

    for (int i = 1; i <= Q; ++i) {
        if (queryEdge[i << 1].LCA == -1)
            printf("impossible\n");
        else
            printf("%d\n", max(maxWeight(queryEdge[i << 1].LCA, queryEdge[i << 1].from),
                               maxWeight(queryEdge[i << 1].LCA, queryEdge[i << 1].to)));
    }
    return 0;
}

void init() {
    memset(edge, 0, sizeof(edge));
    memset(queryEdge, 0, sizeof(queryEdge));
    memset(head, 0, sizeof(head));
    memset(father, 0, sizeof(father));
    memset(way, 0, sizeof(way));
    memset(visited, 0, sizeof(visited));
    memset(fa, 0, sizeof(fa));
    memset(root, 0, sizeof(root));
    memset(queryHead, 0, sizeof(queryHead));
    memset(deep, 0, sizeof(deep));

    scanf("%d%d", &n, &m);
    ::p = (int) log2(n);

    for (int i = 0; i < m; ++i) {
        int a, b, weight;
        scanf("%d%d%d", &a, &b, &weight);
        sourceEdge[++cnt] = EDGE(0, a, b, weight);
    }

    build();
    memset(father, 0, sizeof(father));

    scanf("%d", &Q);
    for (int i = 1; i <= Q; ++i) {
        int a, b;
        scanf("%d%d", &a, &b);
        queryEdge[i << 1] = EDGE(queryHead[a], a, b);
        queryHead[a] = i << 1;

        queryEdge[i << 1 | 1] = EDGE(queryHead[b], b, a);
        queryHead[b] = i << 1 | 1;
    }
}

int find(int x) {
    if (father[x] == x)return x;
    else return father[x] = find(father[x]);
}

void dfs(int x, int from, const int &Root) {
    visited[x] = true;
    root[x] = Root;
    deep[x] = deep[from] + 1;
    fa[0][x] = from;
    for (int i = 1; i <= p; ++i)
        fa[i][x] = fa[i - 1][fa[i - 1][x]];
    for (int i = head[x]; i; i = edge[i].next) {
        int to(edge[i].to);
        if (visited[to])
            continue;
        way[0][to] = edge[i].weight;
        dfs(to, x, Root);
    }
}

void tarjan(int x) {
    father[x] = x;
    visited[x] = true;

    for (int i = head[x]; i; i = edge[i].next) {
        int to(edge[i].to);
        if (!visited[to]) {
            tarjan(to);
            father[to] = x;
        }
    }

    for (int i = queryHead[x]; i; i = queryEdge[i].next) {
        if (root[queryEdge[i].to] != root[x]) {
            queryEdge[i ^ 1].LCA = queryEdge[i].LCA = -1;
        } else if (visited[queryEdge[i].to]) {
            queryEdge[i ^ 1].LCA = queryEdge[i].LCA = find(queryEdge[i].to);
        }
    }
}

int maxWeight(int up, int down) {
    if (deep[up] >= deep[down])
        return INT_MIN;
    int tk = log2(deep[down] - deep[up]);
    return max(way[tk][down], maxWeight(up, fa[tk][down]));
}

void build() {
    for (int i = 1; i <= n; ++i)
        father[i] = i;
    const int count = cnt;
    cnt = 0;
    sort(sourceEdge + 1, sourceEdge + count + 1);
    for (int i = 1; i <= count; ++i) {
        if (find(sourceEdge[i].from) != find(sourceEdge[i].to)) {
            edge[++cnt] = EDGE(head[sourceEdge[i].from], sourceEdge[i].from, sourceEdge[i].to, sourceEdge[i].weight);
            head[sourceEdge[i].from] = cnt;

            edge[++cnt] = EDGE(head[sourceEdge[i].to], sourceEdge[i].to, sourceEdge[i].from, sourceEdge[i].weight);
            head[sourceEdge[i].to] = cnt;

            if (cnt >> 1 == n - 1)break;

            father[find(sourceEdge[i].from)] = find(sourceEdge[i].to);
        }
    }
}