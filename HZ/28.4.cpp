//HZ - 28.4
#include<bits/stdc++.h>

using namespace std;

int n, root, cnt = 0, head[102], dfn[102], low[102];

struct EDGE {
    int next;
    int to;
} edge[100005];

vector<int> ans;

inline void init();
inline void addEdge(int, int);
void tarjan(int);

int main() {
    init();
    for (int i = 1; i <= n; ++i) {
        if (!dfn[i]) {
            root = i;
            tarjan(i);
        }
    }
    sort(ans.begin(), ans.end());
    ans.erase(unique(ans.begin(), ans.end()), ans.end());
    printf("%d", ans.size());
    if (!ans.empty()) {
        for (auto iter = ans.begin(); iter != ans.end(); ++iter) {
            printf("\n%d", *iter);
        }
    }

    return 0;
}

inline void init() {
    memset(head, 0, sizeof(head));
    memset(low, 0, sizeof(low));
    memset(dfn, 0, sizeof(dfn));

    scanf("%d", &n);
    int a, b;
    while (scanf("%d%d", &a, &b) != EOF) {
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
    int son = 0;
    for (int i = head[x]; i; i = edge[i].next) {
        if (!dfn[edge[i].to]) {
            ++son;
            tarjan(edge[i].to);
            low[x] = min(low[x], low[edge[i].to]);
            if (dfn[x] <= low[edge[i].to]) {
                if (x != root || son > 1) ans.push_back(x);
            }
        } else {
            low[x] = min(low[x], dfn[edge[i].to]);
        }
    }
}
