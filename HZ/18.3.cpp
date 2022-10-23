//HZ - 18.3
//Luogu - P1816 
#include<bits/stdc++.h>

using namespace std;

const int MAXN = 100005;

struct Tree {
    int l, r;
    int min;
} tree[MAXN << 2];

int n, m, mount[MAXN];

void init();
void build(int, int, int);
int query(int, int, int);

int main() {
    init();
    build(1, 1, m);
    for (int i = 0; i < n; ++i) {
        int l, r;
        scanf("%d%d", &l, &r);
        printf("%d ", query(1, l, r));
    }
    return 0;
}

void init() {
    memset(tree, 0, sizeof(tree));
    memset(mount, 0, sizeof(mount));
    scanf("%d%d", &m, &n);
    for (int i = 1; i <= m; ++i) {
        scanf("%d", mount + i);
    }
}

void build(int id, int l, int r) {
    tree[id].l = l;
    tree[id].r = r;

    if (l == r) {
        tree[id].min = mount[tree[id].l];
        return;
    }

    int mid = (tree[id].l + tree[id].r) >> 1;
    build(id << 1, l, mid);
    build(id << 1 | 1, mid + 1, r);

    tree[id].min = min(tree[id << 1].min, tree[id << 1 | 1].min);
}

int query(int id, int l, int r) {
    if (tree[id].l >= l && tree[id].r <= r) {
        return tree[id].min;
    }

    int mid = (tree[id].l + tree[id].r) >> 1;
    if (r <= mid)return query(id << 1, l, r);
    else if (l > mid)return query(id << 1 | 1, l, r);
    else return min(query(id << 1, l, r), query(id << 1 | 1, l, r));
}
