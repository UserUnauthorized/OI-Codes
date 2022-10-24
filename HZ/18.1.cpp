//HZ - 18.1
#include<bits/stdc++.h>

#define lid (id<<1)
#define rid (id<<1|1)
using namespace std;

const int MAXN = 100002;

struct Tree {
    int l, r;
    int sum;
} tree[MAXN << 2];

int n, m, a[MAXN];

void build(int, int, int);

void update(int, int, int);

int query(int, int, int);

void init();

int main() {
    init();
    if (n == 0) {
        return 0;
    }
    for (int i = 0; i < m; ++i) {
        char order(getchar());
        while (order != 'A' && order != 'S')order = getchar();
        getchar();
        getchar();
        if (order == 'A') {
            int k, d;
            scanf("%d%d", &k, &d);
            update(1, k, d);
        } else {
            int l, r;
            scanf("%d%d", &l, &r);
            printf("%d\n", query(1, l, r));
        }
    }
    return 0;
}

void init() {
    memset(tree, 0, sizeof(tree));
    memset(a, 0, sizeof(a));
    scanf("%d", &n);
    if (n == 0) {
        return;
    }
    for (int i = 1; i <= n; ++i)
        scanf("%d", a + i);
    build(1, 1, n);
    scanf("%d", &m);
}

void build(int id, int l, int r) {
    tree[id].l = l;
    tree[id].r = r;

    if (l == r) {
        tree[id].sum = a[l];
        return;
    }

    int mid = (l + r) >> 1;
    build(lid, l, mid);
    build(rid, mid + 1, r);

    tree[id].sum = tree[lid].sum + tree[rid].sum;
}

void update(int id, int pos, int key) {
    if (tree[id].l == tree[id].r) {
        tree[id].sum += key;
        return;
    }

    int mid = (tree[id].l + tree[id].r) >> 1;
    if (pos <= mid) update(lid, pos, key);
    else update(rid, pos, key);

    tree[id].sum = tree[lid].sum + tree[rid].sum;
}

int query(int id, int l, int r) {
    if (l <= tree[id].l && tree[id].r <= r)
        return tree[id].sum;

    int mid = (tree[id].l + tree[id].r) >> 1;
    if (r <= mid)return query(lid, l, r);
    else if (l > mid)return query(rid, l, r);
    else return query(lid, l, r) + query(rid, l, r);
}
