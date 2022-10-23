//HZ - 39.8
//Luogu - P2912
#include <bits/stdc++.h>

constexpr int maxn = 1003, maxp = 12;

struct EDGE {
    int next;
    int to;
    int weight;
    int LCA;

    EDGE() : next(-1), to(-1), weight(-1), LCA(-1) {};

    EDGE(int _next, int _to) : next(_next), to(_to) {};

    EDGE(int _next, int _to, int _weight) : next(_next), to(_to), weight(_weight) {};
} edge[maxn << 1], queryEdge[maxn << 1];

int n, Q, p, head[maxn], queryHead[maxn], parent[maxn], deep[maxn], father[maxp][maxn], way[maxp][maxn];

bool visited[maxn];

void init();
void dfs(int, int);
void tarjan(int);
int getWay(int, int);
int find(int);

int main() {
    init();
    dfs(1, 0);
    for (int i = 1; i <= p; ++i)
        for (int j = 1; j <= n; ++j)
            way[i][j] = way[i - 1][j] + way[i - 1][father[i - 1][j]];
    tarjan(1);
    for (int i = 0; i < Q; ++i)
        printf("%d\n", getWay(queryEdge[i << 1].LCA, queryEdge[i << 1].to) + getWay(queryEdge[i << 1 | 1].LCA,
                                                                                    queryEdge[i << 1 | 1].to));
    return 0;
}

void init() {
    memset(head, 0xff, sizeof(head));
    memset(queryHead, 0xff, sizeof(queryHead));
    memset(visited, 0, sizeof(visited));
    memset(parent, 0, sizeof(parent));
    memset(deep, 0, sizeof(deep));

    scanf("%d%d", &n, &Q);
    p = (int) log2(n);

    for (int i = 1; i < n; ++i) {
        int a, b, l;
        scanf("%d%d%d", &a, &b, &l);
        edge[i << 1] = EDGE(head[a], b, l);
        head[a] = i << 1;

        edge[i << 1 | 1] = EDGE(head[b], a, l);
        head[b] = i << 1 | 1;
    }
    for (int i = 0; i < Q; ++i) {
        int a, b;
        scanf("%d%d", &a, &b);
        queryEdge[i << 1] = EDGE(queryHead[a], b);
        queryHead[a] = i << 1;

        queryEdge[i << 1 | 1] = EDGE(queryHead[b], a);
        queryHead[b] = i << 1 | 1;
    }
}

void dfs(int x, int from) {
    deep[x] = deep[from] + 1;
    father[0][x] = from;
    for (int i = 1; i <= p; ++i)
        father[i][x] = father[i - 1][father[i - 1][x]];
    for (int i = head[x]; i != -1; i = edge[i].next) {
        EDGE &e = edge[i];
        if (e.to == from)
            continue;
        way[0][e.to] = e.weight;
        dfs(e.to, x);
    }
}

int find(int x) {
    if (parent[x] == x)
        return x;
    else
        return parent[x] = find(parent[x]);

}

void tarjan(int x) {
    parent[x] = x;
    visited[x] = true;

    for (int i = head[x]; i != -1; i = edge[i].next) {
        EDGE &e = edge[i];
        if (visited[e.to])
            continue;
        tarjan(e.to);
        parent[e.to] = x;
    }

    for (int i = queryHead[x]; i != -1; i = queryEdge[i].next)
        if (visited[queryEdge[i].to])
            queryEdge[i ^ 1].LCA = queryEdge[i].LCA = find(queryEdge[i].to);
}

int getWay(int up, int down) {
    if (deep[up] >= deep[down])
        return 0;
    int k = (int) log2(deep[down] - deep[up]);
    return way[k][down] + getWay(up, father[k][down]);
}