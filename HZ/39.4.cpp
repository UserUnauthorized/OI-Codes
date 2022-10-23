//HZ - 39.4
#include <bits/stdc++.h>

using namespace std;

constexpr int maxn = 250004;

struct EDGE {
    int next;
    int to;
} edge[maxn];

int n, m, cnt = 0, tree[maxn << 1], head[maxn], in[maxn], out[maxn];

void init();
int lowbit(int);
void insert(int, int);
int query(int);
void dfs(int);
void addEdge(const int &, const int &);

int main() {
    init();
    dfs(1);
    insert(in[1], -1);
    insert(out[1], 1);
    for (int i = 1; i < n + m; ++i) {
        char order = getchar();
        while (order != 'A' && order != 'W')order = getchar();
        if (order == 'A') {
            int a, b;
            scanf("%d%d", &a, &b);
            a = max(a, b);
            insert(in[a], -1);
            insert(out[a], 1);
        } else {
            int a;
            scanf("%d", &a);
            printf("%d\n", query(in[a]));
        }
    }
    return 0;
}

void init() {
    memset(in, 0, sizeof(in));
    memset(out, 0, sizeof(out));
    memset(tree, 0, sizeof(tree));
    memset(edge, 0, sizeof(edge));
    memset(head, 0, sizeof(head));

    scanf("%d", &n);

    int u, v;
    for (int i = 1; i < n; ++i) {
        scanf("%d%d", &u, &v);
        addEdge(u, v);
    }

    scanf("%d", &m);

    cnt = 0;
}

void addEdge(const int &u, const int &v) {
    edge[++cnt].next = head[u];
    edge[cnt].to = v;
    head[u] = cnt;
};

void dfs(int x) {
    in[x] = ++cnt;
    insert(cnt, 1);

    for (int i = head[x]; i; i = edge[i].next) {
        dfs(edge[i].to);
    }

    out[x] = ++cnt;
    insert(cnt, -1);
}

int lowbit(int x) {
    return x & -x;
}

void insert(int pos, int key) {
    while (pos <= (n << 1)) {
        tree[pos] += key;
        pos += lowbit(pos);
    }
}

int query(int pos) {
    int result(0);
    while (pos > 0) {
        result += tree[pos];
        pos -= lowbit(pos);
    }
    return result;
}