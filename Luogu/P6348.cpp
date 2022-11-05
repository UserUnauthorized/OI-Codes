//Luogu - P6348
#include <bits/stdc++.h>

using namespace std;
constexpr int maxn = 5e5 + 10;
typedef pair<int, int> P;

struct EDGE {
    int to;
    int weight;

    EDGE(int _to, int _weight) : to(_to), weight(_weight) {};
};

class TREE {
public:
    int num[::maxn << 2];

    void build(int id, int l, int r, const bool &isInTree);

    void build(int id, int nodeL, int nodeR, const int &l, const int &r, const int &superNode, const bool &isInTree);

    void out(int id, int l, int r);
} inTree, outTree;

vector<EDGE> edge[(maxn << 3) + (maxn << 1)];
priority_queue<P, vector<P>, greater<P>> que;
pair<int, int> pos;
vector<int> dis;
bitset<maxn> vis;

inline int read();

void init();

void dijkstra(int x);

void connect(int id, int l, int r);

int n, m, p, cnt(0);

int main() {
    init();
    connect(1, 1, n);
    edge[pos.second].emplace_back(pos.first, 0);
    dijkstra(pos.second);
    inTree.out(1, 1, n);
    return 0;
}

void TREE::build(int id, int l, int r, const bool &isInTree) {
    num[id] = ++cnt;

    if (l == r) {
        if (r == ::p)
            isInTree ? pos.first = num[id] : pos.second = num[id];
        return;
    }


    int mid((l + r) >> 1);
    build(id << 1, l, mid, isInTree);
    build(id << 1 | 1, mid + 1, r, isInTree);

    isInTree ? edge[num[id]].emplace_back(num[id << 1], 0), edge[num[id]].emplace_back(num[id << 1 | 1], 0)
             : edge[num[id << 1]].emplace_back(num[id], 0), edge[num[id << 1 | 1]].emplace_back(num[id], 0);
}

void TREE::build(int id, int nodeL, int nodeR, const int &l, const int &r, const int &superNode,
                 const bool &isInTree) {
    if (l <= nodeL && nodeR <= r) {
        isInTree ? edge[superNode].emplace_back(num[id], 1) : edge[num[id]].emplace_back(superNode, 0);
        return;
    }

    int mid((nodeL + nodeR) >> 1);
    if (l <= mid)
        build(id << 1, nodeL, mid, l, r, superNode, isInTree);
    if (r > mid)
        build(id << 1 | 1, mid + 1, nodeR, l, r, superNode, isInTree);
}

void TREE::out(int id, int l, int r) {
    if (l == r) {
        printf("%d\n", dis.at(this->num[id]));
        return;
    }

    int mid((l + r) >> 1);
    out(id << 1, l, mid);
    out(id << 1 | 1, mid + 1, r);
}

void connect(int id, int l, int r) {
    edge[inTree.num[id]].emplace_back(outTree.num[id], 0);

    if (l == r)
        return;

    int mid((l + r) >> 1);

    connect(id << 1, l, mid);
    connect(id << 1 | 1, mid + 1, r);
}

void init() {
    n = read();
    m = read();
    p = read();

    inTree.build(1, 1, n, true);
    outTree.build(1, 1, n, false);

    while (m--) {
        int a(read()), b(read()), c(read()), d(read());
        inTree.build(1, 1, n, a, b, ++cnt, true);
        outTree.build(1, 1, n, c, d, cnt, false);

        inTree.build(1, 1, n, c, d, ++cnt, true);
        outTree.build(1, 1, n, a, b, cnt, false);
    }
}

inline int read() {
    int result(0), ch(getchar());
    while (ch < '0' || ch > '9')
        ch = getchar();
    while (ch >= '0' && ch <= '9') {
        result = (result << 3) + (result << 1) + (ch ^ 48);
        ch = getchar();
    }
    return result;
}

void dijkstra(int x) {
    dis.resize(cnt + 1, INT_MAX);
    dis.at(x) = 0;
    que.emplace(0, x);

    while (!que.empty()) {
        const P t(que.top());
        const int &k(t.second);
        que.pop();

        if (vis.test(k))
            continue;

        vis.set(k);

        for (const EDGE &e: edge[k]) {
            if (!vis.test(e.to) && dis.at(e.to) > dis.at(k) + e.weight) {
                dis.at(e.to) = dis.at(k) + e.weight;
                que.emplace(dis.at(e.to), e.to);
            }
        }
    }
}
