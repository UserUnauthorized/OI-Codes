//HZ - 28.5
//Luogu - P2921
#include<bits/stdc++.h>

using namespace std;

constexpr int maxn = 100005;

struct EDGE {
    int next;
    int to;
} edge[maxn];

int n, cnt = 0, sccnum = 0, to[maxn], head[maxn], low[maxn], dfn[maxn], belong[maxn], size[maxn], dis[maxn];

bool vis[maxn];

stack<int> st;

void init();
void tarjan(int);
void build();
void addEdge(int, int);
void depthFirstSearch(int);

int main() {
    init();
    for (int i = 1; i <= n; ++i) {
        if (!dfn[i]) {
            tarjan(i);
        }
    }
    build();
    for (int i = 1; i <= sccnum; ++i) {
        if (!dis[i]) {
            depthFirstSearch(i);
        }
    }
    for (int i = 1; i <= n; ++i) {
        printf("%d\n", dis[belong[i]]);
    }
    return 0;
}

void init() {
    memset(edge, 0, sizeof(edge));
    memset(to, 0, sizeof(to));
    memset(head, 0, sizeof(head));
    memset(low, 0, sizeof(low));
    memset(dfn, 0, sizeof(dfn));
    memset(belong, 0, sizeof(belong));
    memset(size, 0, sizeof(size));
    memset(dis, 0, sizeof(dis));
    memset(vis, 0, sizeof(vis));

    scanf("%d", &n);

    for (int i = 1; i <= n; ++i) {
        scanf("%d", to + i);
    }
}

void tarjan(int x) {
    dfn[x] = low[x] = ++cnt;
    vis[x] = true;
    st.push(x);
    if (!dfn[to[x]]) {
        tarjan(to[x]);
        low[x] = min(low[x], low[to[x]]);
    } else if (vis[to[x]]) {
        low[x] = min(low[x], dfn[to[x]]);
    }

    if (low[x] == dfn[x]) {
        int y;
        ++sccnum;
        do {
            y = st.top();
            st.pop();
            vis[y] = false;
            belong[y] = sccnum;
            ++size[sccnum];
        } while (y != x);
    }
}

void build() {
    cnt = 0;
    for (int i = 1; i <= n; ++i) {
        if (belong[i] != belong[to[i]]) {
            addEdge(belong[i], belong[to[i]]);
        }
    }
}

void addEdge(int u, int v) {
    edge[++cnt].next = head[u];
    head[u] = cnt;
    edge[cnt].to = v;
}

void depthFirstSearch(int x) {
    dis[x] = size[x];
    for (int i = head[x]; i; i = edge[i].next) {
        if (!dis[edge[i].to]) {
            depthFirstSearch(edge[i].to);
        }
        dis[x] += dis[edge[i].to];
    }
}
