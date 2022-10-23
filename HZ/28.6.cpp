//HZ - 28.6
//Luogu - P3469
#include<bits/stdc++.h>

using namespace std;

constexpr int maxn = 100005;

struct EDGE {
    int next;
    int to;
} edge[1000006];

long long n, m, root, cnt = 0, ans[maxn], head[maxn], dfn[maxn], low[maxn], node[maxn], son[maxn];

bool cut[maxn];

void init();
void tarjan(int);
inline void addEdge(int, int);

int main() {
    init();
    for (int i = 1; i <= n; ++i) {
        if (!dfn[i]) {
            root = i;
            tarjan(i);
        }
    }
    for (int i = 1; i <= n; ++i) {
        printf("%lld\n", ans[i]);
    }
    return 0;
}

void init() {
    memset(edge, 0, sizeof(edge));
    memset(ans, 0, sizeof(ans));
    memset(head, 0, sizeof(head));
    memset(dfn, 0, sizeof(dfn));
    memset(low, 0, sizeof(low));
    memset(node, 0, sizeof(node));
    memset(cut, 0, sizeof(cut));
    memset(son, 0, sizeof(son));

    scanf("%lld%lld", &n, &m);

    int a, b;
    for (int i = 0; i < m; ++i) {
        scanf("%d%d", &a, &b);
        addEdge(a, b);
    }

    cnt = 0;
}

inline void addEdge(int a, int b) {
    edge[++cnt].next = head[a];
    head[a] = cnt;
    edge[cnt].to = b;

    edge[++cnt].next = head[b];
    head[b] = cnt;
    edge[cnt].to = a;
}

void tarjan(int x) {
    dfn[x] = low[x] = ++cnt;
    node[x] = 1;
    int sum(0);
    for (int i = head[x]; i; i = edge[i].next) {
        if (!dfn[edge[i].to]) {
            ++son[x];
            tarjan(edge[i].to);
            low[x] = min(low[x], low[edge[i].to]);
            node[x] += node[edge[i].to];
            if (dfn[x] <= low[edge[i].to]) {
                ans[x] += (long long) node[edge[i].to] * (n - node[edge[i].to]);
                sum += node[edge[i].to];
                if (x != root || son[x] > 1) {
                    cut[x] = true;
                }
            }
        } else {
            low[x] = min(low[x], dfn[edge[i].to]);
        }
    }
    if (!cut[x]) ans[x] = 2 * (n - 1);
    else ans[x] += (long long) (n - sum - 1) * (sum + 1) + (n - 1);
}
