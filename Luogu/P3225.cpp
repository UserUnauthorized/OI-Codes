//HZ - 28.8
//HZ - 28.9
//Luogu - P3225
//Luogu - SP16185
//Luogu - UVA1108
#include<bits/stdc++.h>

using namespace std;

constexpr int maxn = 50002;

struct EDGE {
    int next;
    int to;
} edge[maxn << 2];

int n, m, t = 0, dccnum, ansnum, cnt, head[maxn << 1], dfn[maxn << 1], low[maxn << 1];

bool vis[maxn << 1], cut[maxn << 1];

vector<int> dcc[maxn << 1];

vector<unsigned long long> ans;

stack<int> st;

bool init();

void addEdge(int, int);

void tarjan(int, int);

void out();

int main() {
    while (init()) {
        for (int i = 1; i <= m; ++i) {
            if (!dfn[i])
                tarjan(i, -1);
        }
        out();
        
        unsigned long long result(1);
        for (unsigned long long t: ans) {
            result *= t;
        }
        
        printf("Case %d: %d %lld\n", t, ansnum, result);
    }
    return 0;
}

bool init() {
    ++t;

    memset(edge, 0, sizeof(edge));
    memset(dfn, 0, sizeof(dfn));
    memset(low, 0, sizeof(low));
    memset(vis, 0, sizeof(vis));
    memset(cut, 0, sizeof(cut));
    memset(dcc, 0, sizeof(dcc));
    memset(head, 0, sizeof(head));
    
    while (!ans.empty()) ans.pop_back();
    while (!st.empty()) st.pop();
    
    m = dccnum = cnt = ansnum = 0;

    scanf("%d", &n);
    if (!n) return false;

    int a, b;
    for (int i = 0; i < n; ++i) {
        scanf("%d%d", &a, &b);
        m = max({m, a, b});
        addEdge(a, b);
    }

    cnt = 0;
    return true;
}

void addEdge(int a, int b) {
    edge[++cnt].next = head[a];
    edge[cnt].to = b;
    head[a] = cnt;

    edge[++cnt].next = head[b];
    edge[cnt].to = a;
    head[b] = cnt;
}

void tarjan(int x, int fa) {
    dfn[x] = low[x] = ++cnt;
    vis[x] = true;
    st.push(x);
    bool first(true);
    int son = 0;
    for (int i = head[x]; i; i = edge[i].next) {
        int to = edge[i].to;
        if (first && to == fa) {
            first = false;
            continue;
        }

        if (!dfn[to]) {
            ++son;
            tarjan(to, x);
            low[x] = min(low[x], low[to]);

            if (dfn[x] <= low[to]) {
                cut[x] = true;
                dcc[++dccnum].push_back(x);

                int y;
                do {
                    y = st.top();
                    st.pop();
                    dcc[dccnum].push_back(y);
                } while (y != to);
            }
        } else {
            low[x] = min(low[x], dfn[to]);
        }
    }
    if (fa == -1 && son == 1)cut[x] = false;
}

void out() {
    for (int i = 1; i <= dccnum; ++i) {
        int cutnum = 0;
        for (int node: dcc[i])
            if (cut[node])
                ++cutnum;
        if (!cutnum) {
            ans.push_back((unsigned long long) dcc[i].size() * (dcc[i].size() - 1) / 2);
            ansnum += 2;
        } else if (cutnum == 1) {
            ans.push_back((unsigned long long) dcc[i].size() - 1);
            ++ansnum;
        }
    }
}
