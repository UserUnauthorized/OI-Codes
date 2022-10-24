//HZ - 265.4
#include <bits/stdc++.h>

using namespace std;
const int maxn = 100005;

struct EDGE {
    int next;
    int to;
    int weight;

    EDGE() : next(-1), to(-1), weight(-1) {};

    EDGE(int _next, int _to, int _weight) : next(_next), to(_to), weight(_weight) {};
} edge[maxn << 1];

int n, m, head[maxn], require[maxn], dis[maxn], ans[20004], h;
bool vis[maxn];

void insert(int, int);

int getPos(int);

void SPFA(int);

void init();

void carry(int);

int main() {
    init();
    SPFA(1);
    for (int i = 1; i <= n; ++i)
        insert(getPos(-dis[i]), require[i]);
    for (int i = 0; i <= 20000; ++i)
        carry(i);
    while (ans[h + 1] != 0)
        ++h;
    for (int i = h; i >= 0; --i)
        printf("%d", ans[i]);
    putchar('.');
    if (ans[10007] > 4)
        ++ans[10006];
    for (int i = 10001; i <= 10006; ++i)
        printf("%d", ans[i]);
    return 0;
}

void init() {
    memset(head, 0xff, sizeof(head));
    memset(ans, 0, sizeof(ans));
    memset(require, 0, sizeof(require));
    memset(vis, 0, sizeof(vis));

    scanf("%d%d", &n, &m);

    fill(dis + 1, dis + n + 1, INT_MIN);

    for (int i = 1; i <= n; ++i)
        scanf("%d", require + i);

    for (int i = 0; i < m; ++i) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        edge[i] = EDGE(head[u], v, w);
        head[u] = i;
    }
}

void SPFA(int x) {
    queue<int> que;
    dis[x] = 0;
    vis[x] = true;
    que.push(x);

    while (!que.empty()) {
        int k = que.front();
        for (int i = head[k]; i != -1; i = edge[i].next) {
            EDGE &e = edge[i];
            if (dis[e.to] < e.weight + dis[k]) {
                dis[e.to] = e.weight + dis[k];
                if (!vis[e.to]) {
                    que.push(e.to);
                    vis[e.to] = true;
                }
            }
        }
        que.pop();
        vis[k] = false;
    }
};

int getPos(int x) {
    if (x >= 0)return x;
    else return 10000 + (-x);
}

void insert(int pos, int key) {
    ans[pos] += key;
    if (pos > 10000) {
        for (; ans[pos] > 9 && pos > 10001; --pos) {
            ans[pos - 1] += ans[pos] / 10;
            ans[pos] %= 10;
        }
        if (pos == 10001) {
            ans[0] += ans[pos] / 10;
            ans[pos] %= 10;
            pos = 0;
        }
    }
    for (; ans[pos] > 9; ++pos) {
        ans[pos + 1] += ans[pos] / 10;
        ans[pos] %= 10;
        h = max(h, pos + 1);
    }
}

void carry(int pos) {
    if (pos > 10000) {
        for (; ans[pos] > 9 && pos > 10001; --pos) {
            ans[pos - 1] += ans[pos] / 10;
            ans[pos] %= 10;
        }
        if (pos == 10001) {
            ans[0] += ans[pos] / 10;
            ans[pos] %= 10;
            pos = 0;
        }
    }
    for (; ans[pos] > 9; ++pos) {
        ans[pos + 1] += ans[pos] / 10;
        ans[pos] %= 10;
        h = max(h, pos + 1);
    }
}