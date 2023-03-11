//HZ - 40.2
//Luogu - P2486
#include <bits/stdc++.h>

#ifdef LOCAL

//#include<debug.h>

#else
#define debug(...)
#endif

using namespace std;
constexpr int maxn = 1e5 + 5;
typedef int colorType;

struct NODE {
    int count;
    colorType leftColor, rightColor;

    NODE() : count(0), leftColor(-1), rightColor(-1) {};

    NODE(colorType _color) : count(1), leftColor(_color), rightColor(_color) {};

    NODE(int _count, colorType _leftColor, colorType _rightColor) : count(_count), leftColor(_leftColor),
                                                                    rightColor(_rightColor) {};

    inline void reverse() {
        std::swap(this->leftColor, this->rightColor);
    }

    inline friend NODE merge(const NODE &left, const NODE &right) {
        return {left.count + right.count - (int) (left.rightColor == right.leftColor && left.rightColor != -1),
                left.leftColor, right.rightColor};
    }
};

struct TREE {
    int l, r;
    NODE data;
    colorType lazy;

    TREE() : l(-1), r(-1), data(), lazy(-1) {};
} tree[maxn << 2];

inline int read();

void init();

void initDfs(int x, int from);

void dfs(int x, int TOP);

void build(int id, int l, int r);

void update(int id, int pos, colorType key);

void update(int id, int l, int r, colorType key);

NODE query(int id, int l, int r);

int n, m, cnt(0);
int dfn[maxn], dep[maxn], top[maxn], nodeId[maxn], size[maxn], son[maxn], father[maxn];
colorType initColor[maxn];
vector<int> edge[maxn];

int main() {
    init();
    initDfs(1, 1);
    dfs(1, 1);
    build(1, 1, n);
    while (m--) {
        int order(getchar());
        while (order != 'C' && order != 'Q')
            order = getchar();

        if (order == 'C') {
            int x(read()), y(read());
            colorType key(read());

            while (top[x] != top[y]) {
                if (dep[top[x]] < dep[top[y]])
                    swap(x, y);
                update(1, dfn[top[x]], dfn[x], key);
                x = father[top[x]];
            }

            if (dfn[x] > dfn[y])
                swap(x, y);
            update(1, dfn[x], dfn[y], key);
        } else {
            int x(read()), y(read());
            NODE resultX, resultY;

            while (top[x] != top[y]) {
                if (dep[top[x]] < dep[top[y]]) {
                    swap(x, y);
                    swap(resultX, resultY);
                }
                resultX = merge(query(1, dfn[top[x]], dfn[x]), resultX);
                x = father[top[x]];
            }

            if (dfn[x] > dfn[y]) {
                swap(x, y);
                swap(resultX, resultY);
            }

            resultY = merge(query(1, dfn[x], dfn[y]), resultY);

            resultY.reverse();

            printf("%d\n", merge(resultY, resultX).count);
        }
    }
}

void init() {
    ::n = read();
    ::m = read();

    for (int i = 1; i <= n; ++i)
        initColor[i] = read();

    for (int i = 1; i < n; ++i) {
        int a(read()), b(read());
        edge[a].emplace_back(b);
        edge[b].emplace_back(a);
    }
}

int read() {
    int result(0), input(getchar());

    while (input < '0' || input > '9')
        input = getchar();

    while (input >= '0' && input <= '9') {
        result = (result << 3) + (result << 1) + (input & 15);
        input = getchar();
    }

    return result;
}

void initDfs(int x, int from) {
    father[x] = from;
    dep[x] = dep[from] + 1;
    size[x] = true;

    for (const int &iter: edge[x]) {
        if (iter == from)
            continue;

        initDfs(iter, x);
        size[x] += size[iter];

        if (size[iter] > size[son[x]])
            son[x] = iter;
    }
}

void dfs(int x, int TOP) {
    top[x] = TOP;
    dfn[x] = ++cnt;
    nodeId[cnt] = x;

    if (!son[x])
        return;

    dfs(son[x], TOP);

    for (const int &iter: edge[x])
        if (iter != father[x] && iter != son[x])
            dfs(iter, iter);
}

void build(int id, int l, int r) {
    tree[id].l = l;
    tree[id].r = r;
    if (l == r) {
        tree[id].data = NODE(initColor[nodeId[r]]);
        return;
    }

    int mid((l + r) >> 1);

    build(id << 1, l, mid);
    build(id << 1 | 1, mid + 1, r);

    tree[id].data = merge(tree[id << 1].data, tree[id << 1 | 1].data);
}

void update(int id, int pos, colorType key) {
    if (tree[id].l == tree[id].r) {
        tree[id].data = NODE(key);
        return;
    }

    if (tree[id].lazy != -1) {
        tree[id << 1].data = tree[id << 1 | 1].data = NODE(tree[id].lazy);
        tree[id << 1].lazy = tree[id << 1 | 1].lazy = tree[id].lazy;
        tree[id].lazy = -1;
    }

    int mid((tree[id].l + tree[id].r) >> 1);

    if (pos <= mid)
        update(id << 1, pos, key);
    else
        update(id << 1 | 1, pos, key);

    tree[id].data = merge(tree[id << 1].data, tree[id << 1 | 1].data);
}

void update(int id, int l, int r, colorType key) {
    if (l <= tree[id].l && tree[id].r <= r) {
        tree[id].data = NODE(key);
        tree[id].lazy = key;
        return;
    }

    if (tree[id].lazy != -1) {
        tree[id << 1].data = tree[id << 1 | 1].data = NODE(tree[id].lazy);
        tree[id << 1].lazy = tree[id << 1 | 1].lazy = tree[id].lazy;
        tree[id].lazy = -1;
    }

    int mid((tree[id].l + tree[id].r) >> 1);

    if (l <= mid)
        update(id << 1, l, r, key);
    if (r > mid)
        update(id << 1 | 1, l, r, key);

    tree[id].data = merge(tree[id << 1].data, tree[id << 1 | 1].data);
}

NODE query(int id, int l, int r) {
    if (l <= tree[id].l && tree[id].r <= r)
        return tree[id].data;

    if (tree[id].lazy != -1) {
        tree[id << 1].data = tree[id << 1 | 1].data = NODE(tree[id].lazy);
        tree[id << 1].lazy = tree[id << 1 | 1].lazy = tree[id].lazy;
        tree[id].lazy = -1;
    }

    int mid((tree[id].l + tree[id].r) >> 1);

    if (r <= mid)
        return query(id << 1, l, r);
    else if (l > mid)
        return query(id << 1 | 1, l, r);
    else
        return merge(query(id << 1, l, r), query(id << 1 | 1, l, r));
}
