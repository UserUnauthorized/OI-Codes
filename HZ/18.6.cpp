//HZ - 18.6
#include<bits/stdc++.h>

using namespace std;

const int MAXN = 100005;

struct Tree {
    int l, r, sum;
    int ml, mr, ms;
    int ln, ls;
    int rn, rs;
} tree[MAXN << 2];

Tree None;

int n, m, a[MAXN];

void init();
void build(int, int, int);
Tree query(int, int, int);
void pushUp(int);

int main() {
    //None.ln=n;
    //None.rn=n;
    init();
    build(1, 1, n);
    for (int i = 0; i < m; ++i) {
        int x, y;
        scanf("%d%d", &x, &y);
        Tree ans = query(1, x, y);
        printf("%d %d %d\n", ans.ml, ans.mr, ans.ms);
    }
    return 0;
}

void init() {
    memset(tree, 0, sizeof(tree));
    memset(a, 0, sizeof(a));
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", a + i);
    }
}

void build(int id, int l, int r) {
    tree[id].l = l;
    tree[id].r = r;

    if (l == r) {
        tree[id].sum = tree[id].ls = tree[id].rs = tree[id].ms = a[r];
        tree[id].ln = tree[id].rn = tree[id].ml = tree[id].mr = l;
        return;
    }

    int mid = (l + r) >> 1;
    build(id << 1, l, mid);
    build(id << 1 | 1, mid + 1, r);

    pushUp(id);
}

void pushUp(int id) {
    tree[id].sum = tree[id << 1].sum + tree[id << 1 | 1].sum;

    if (tree[id << 1].ls >= tree[id << 1].sum + tree[id << 1 | 1].ls) {
        tree[id].ls = tree[id << 1].ls;
        tree[id].ln = tree[id << 1].ln;
    } else {
        tree[id].ls = tree[id << 1].sum + tree[id << 1 | 1].ls;
        tree[id].ln = tree[id << 1 | 1].ln;
    }

    if (tree[id << 1 | 1].rs > tree[id << 1 | 1].sum + tree[id << 1].rs) {
        tree[id].rs = tree[id << 1 | 1].rs;
        tree[id].rn = tree[id << 1 | 1].rn;
    } else {
        tree[id].rs = tree[id << 1 | 1].sum + tree[id << 1].rs;
        tree[id].rn = tree[id << 1].rn;
    }

    if (tree[id << 1].ms >= tree[id << 1 | 1].ms) {
        tree[id].ms = tree[id << 1].ms;
        tree[id].ml = tree[id << 1].ml;
        tree[id].mr = tree[id << 1].mr;
    } else {
        tree[id].ms = tree[id << 1 | 1].ms;
        tree[id].ml = tree[id << 1 | 1].ml;
        tree[id].mr = tree[id << 1 | 1].mr;
    }

    if (tree[id].ms > tree[id << 1].rs + tree[id << 1 | 1].ls) return;
    if (tree[id].ms < tree[id << 1].rs + tree[id << 1 | 1].ls) {
        tree[id].ms = tree[id << 1].rs + tree[id << 1 | 1].ls;
        tree[id].ml = tree[id << 1].rn;
        tree[id].mr = tree[id << 1 | 1].ln;
        return;
    }

    if (tree[id].ml < tree[id << 1].rn) return;
    if (tree[id].ml > tree[id << 1].rn) {
        tree[id].ml = tree[id << 1].rn;
        tree[id].mr = tree[id << 1 | 1].ln;
        return;
    }

    tree[id].mr = min(tree[id].mr, tree[id << 1 | 1].ln);
}

Tree query(int id, int l, int r) {
    if (l <= tree[id].l && tree[id].r <= r) {
        return tree[id];
    }

    int mid = (tree[id].l + tree[id].r) >> 1;
    if (r <= mid) return query(id << 1, l, r);
    if (l > mid) return query(id << 1 | 1, l, r);

    Tree x, y, z;
    x = query(id << 1, l, r);
    y = query(id << 1 | 1, l, r);

    z.l = x.l;
    z.r = y.r;
    z.sum = x.sum + y.sum;
    if (x.ls >= x.sum + y.ls) {
        z.ls = x.ls;
        z.ln = x.ln;
    } else {
        z.ls = x.sum + y.ls;
        z.ln = y.ln;
    }

    if (y.rs >= y.sum + x.rs) {
        z.rs = y.rs;
        z.rn = y.rn;
    } else {
        z.rs = y.sum + x.rs;
        z.rn = x.rn;
    }

    if (x.ms >= y.ms) {
        z.ms = x.ms;
        z.ml = x.ml;
        z.mr = x.mr;
    } else {
        z.ms = y.ms;
        z.ml = y.ml;
        z.mr = y.mr;
    }

    if (z.ms > x.rs + y.ls) return z;
    if (z.ms < x.rs + y.ls) {
        z.ms = x.rs + y.ls;
        z.ml = x.rn;
        z.mr = y.ln;
        return z;
    }

    if (z.ml < x.rn) return z;
    if (z.ml > x.rn) {
        z.ml = x.rn;
        z.mr = y.ln;
        return z;
    }

    z.mr = min(z.mr, y.ln);
    return z;
}
