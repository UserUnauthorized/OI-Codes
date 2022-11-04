//Luogu - P6348
#include <bits/stdc++.h>

using namespace std;
constexpr int maxn = 500005;

inline int read();

struct TREE {
    int l, r;
} inTree[maxn << 2], outTree[maxn << 2];

struct EDGE {
    int next;
    int to;
    int weight;

    EDGE() : next(-1), to(-1), weight(-1) {};

    EDGE(int _next, int _to, int _weight) : next(_next), to(_to), weight(_weight) {};
} edge[maxn << 4];

int n, m, P, cnt, edgeCount(0), inRoot, outRoot, dis[maxn << 4], head[maxn << 4], leftSon[maxn << 4], rightSon[
        maxn << 4];

void init();

void build(int &inId, int &outId, int l, int r);

void line2Point(int inId, int outId, int l, int r, int to, int weight);

void point2Line(int inId, int outId, int l, int r, int pos, int weight);

int main() {
    init();
}

void init() {
    memset(head, 0xff, sizeof(head));

    cnt = n = read();
    m = read();
    P = read();


    build(inRoot, outRoot, 1, n);
}

inline int read(/*ONLY FOR POSITIVE NUMBER*/) {
    int result(0), ch(getchar());
    while (ch < '0' || ch > '9')
        ch = getchar();
    while (ch >= '0' && ch <= '9') {
        result = (result << 3) + (result << 1) + (ch ^ 48);
        ch = getchar();
    }
    return result;
}

void build(int &inId, int &outId, int l, int r) {
    inId = ++cnt;
    outId = ++cnt;

    edge[++edgeCount] = EDGE(head[inId], outId, 0);
    head[inId] = edgeCount;

    inTree[inId].l = outTree[outId].l = l;
    inTree[inId].r = outTree[outId].r = r;

    if (l == r)
        return;

    int mid((l + r) >> 1);
    build(leftSon[inId], leftSon[outId], l, mid);
    build(rightSon[inId], rightSon[outId], mid + 1, r);

    edge[++edgeCount] = EDGE(head[outId],leftSon[outId],0);
    head[outId] = edgeCount;
    edge[++edgeCount] = EDGE(head[outId],rightSon[outId],0);
    head[outId] = edgeCount;

    edge[++edgeCount] = EDGE(head[leftSon[inId]],inId,0);
    head[leftSon[inId]] = edgeCount;
    edge[++edgeCount] = EDGE(head[rightSon[inId]],inId,0);
    head[rightSon[inId]] = edgeCount;
}
