//HZ - 18.2
#include<bits/stdc++.h>

using namespace std;

const int MAXN = 1000005;

struct Tree {
    int l, r;
    int max;
} tree[MAXN << 2];

int n, q, mount[MAXN];

void init();

void build(int, int, int);

int query(int, int, int);

int main() {
    init();
    build(1, 0, n);
    for (int i = 0; i < q; ++i) {
        int l, r;
        scanf("%d%d", &l, &r);
        printf("%d\n", query(1, l, r));
    }
    return 0;
}

void init() {
    memset(tree, 0, sizeof(tree));
    memset(mount, 0, sizeof(mount));
    scanf("%d", &n);
    for (int i = 0; i <= n; ++i) {
        scanf("%d", mount + i);
    }
    scanf("%d", &q);
}

void build(int id, int l, int r) {
    tree[id].l = l;
    tree[id].r = r;

    if (l == r) {
        tree[id].max = mount[tree[id].l];
        return;
    }

    int mid = (tree[id].l + tree[id].r) >> 1;
    build(id << 1, l, mid);
    build(id << 1 | 1, mid + 1, r);

    tree[id].max = max(tree[id << 1].max, tree[id << 1 | 1].max);
}

int query(int id, int l, int r) {
    if (tree[id].l >= l && tree[id].r <= r) {
        return tree[id].max;
    }

    int mid = (tree[id].l + tree[id].r) >> 1;
    if (r <= mid)return query(id << 1, l, r);
    else if (l > mid)return query(id << 1 | 1, l, r);
    else return max(query(id << 1, l, r), query(id << 1 | 1, l, r));
}
