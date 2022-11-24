//Luogu - P5025
#include<bits/stdc++.h>

using namespace std;
constexpr int maxn = 5e5 + 5, P = 1e9 + 7;

struct segTree {
    int l, r;

    segTree() : l(-1), r(-1) {};

    segTree(int _l, int _r) : l(_l), r(_r) {};
} tree[maxn << 2];

int n, sccnum(0), cnt(0), nodeCount(INT_MIN);
long long treeId[maxn], dis[maxn << 2], pos[maxn], len[maxn];
int dfn[maxn << 2], low[maxn << 2], belong[maxn << 2], size[maxn << 2], ans[maxn << 2];
bool vis[maxn << 2], leaf[maxn << 2];
stack<int> st;
vector<int> edge[maxn << 2], sccEdge;
vector<vector<int> > scc;

void build(int id, int l, int r);

void link(int id, int l, int r, const int &qL, const int &qR, const int &node);

void tarjan(int x);

void depthFirstSearch(int x);

void init();

int main() {
    init();
    build(1, 1, n);
    for (int i = 1; i <= n; ++i) {
        int _L(lower_bound(pos + 1, pos + n + 1, pos[i] - len[i]) - pos);
        int _R(upper_bound(pos + 1, pos + n + 1, pos[i] + len[i]) - pos);
        link(1, 1, n, _L, _R, treeId[i]);
    }

    for (int i = 1; i <= nodeCount; ++i)
        if (!dfn[i])
            tarjan(i);
    //tarjan(1);

    //return 114514;
    cerr << "P\t" << sccnum << endl;
    for (int i = 0; i < sccnum; ++i)
        if (ans[i] == -1)
            depthFirstSearch(i);

    for (int i = 1; i <= n; ++i)
        printf("%d\n", ans[belong[i]]);

    return 0;
}

void init() {
    memset(vis, 0, sizeof(vis));
    memset(leaf, 0, sizeof(leaf));
    memset(ans, 0xff, sizeof(ans));

    cin >> n;
    for (int i = 1; i <= n; ++i)
        cin >> pos[i] >> len[i];
    pos[n + 1] = LONG_LONG_MAX;
}

void build(int id, int l, int r) {
    cerr << "TREE\t" << id << "\t" << l << "\t" << r << endl;
    if (l == r) {
        treeId[r] = id;
        leaf[id] = true;
        nodeCount = max(nodeCount, id);
        return;
    }


    int mid((l + r) >> 1);

    build(id << 1, l, mid);
    build(id << 1 | 1, mid + 1, r);

    //if(l != mid)
    edge[id].emplace_back(id << 1);
    //if(mid + 1 != r)
    edge[id].emplace_back(id << 1 | 1);
}

void link(int id, int l, int r, const int &qL, const int &qR, const int &node) {
    if (qL <= l && r <= qR) {
        edge[node].emplace_back(id);
        return;
    }

    int mid((l + r) >> 1);

    if (qL <= mid)
        link(id << 1, l, mid, qL, qR, node);
    if (qR > mid)
        link(id << 1 | 1, mid + 1, r, qL, qR, node);
}

void tarjan(int x) {
    dfn[x] = low[x] = ++cnt;
    vis[x] = true;
    st.emplace(x);

    for (const int &iter: edge[x]) {
        if (!dfn[iter]) {
            tarjan(iter);
            low[x] = min(low[x], low[iter]);
        } else if (vis[iter]) {
            low[x] = min(low[x], dfn[iter]);
        }
    }

    if (dfn[x] == low[x]) {
        ++sccnum;
        scc.emplace_back();
        int y;
        do {
            y = st.top();
            st.pop();
            belong[y] = sccnum;
            scc.back().emplace_back(y);
            if (leaf[y])
                ++size[sccnum];
            //cout << "A\t" << y << "\t" << (leaf[y] ? 'Y' : 'N') << endl;
        } while (y != x);
    }
}

void depthFirstSearch(int x) {
    if (ans[x] != -1)
        return;

    ans[x] = size[x];

    cerr << "B\t" << x << "\t" << scc[x].size() << endl;
    for (const int &k: scc[x]) {
        cerr << "A\t" << k << endl;
        for (const int &iter: edge[k]) {
            cerr << "DEBUG\t" << iter << endl;
            if (belong[iter]) {
                depthFirstSearch(belong[iter] - 1);
                ans[x] += ans[belong[iter] - 1];
            }
        }
    }
}
