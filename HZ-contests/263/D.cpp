//HZ - 263.4
#include <bits/stdc++.h>

using namespace std;

const int maxn = 1000006;

int n, k, source[maxn], value[maxn];

long long sum;

struct TREE {
    int l, r;//管辖区间
    long long Lmax, Rmax, Pmax;//最长左端，最长右端，最长中间和
    long long Lmin, Rmin, Pmin;
    long long sum;//区间和
    //int ln, rn, pl, pr;

    void pushUp(const TREE &left, const TREE &right) {
        this->sum = left.sum + right.sum; //更新区间和

        //更新左子段和
        /*
        if (left.Lmax < left.sum + right.Lmax) {
            this->Lmax = left.sum + right.Lmax;
            this->ln = right.rn;
        } else {
            this->Lmax = left.Lmax;
            this->ln = left.ln;
        }*/
        this->Lmax = max(left.Lmax, left.sum + right.Lmax);
        this->Lmin = min(left.Lmin, left.sum + right.Lmin);
        //右
        /*
        if (right.Rmax < right.sum + left.Rmax) {
            this->Rmax = right.sum + left.Rmax;
            this->rn = left.rn;
        } else {
            this->Rmax = right.Rmax;
            this->rn = right.rn;
        }
         */
        this->Rmax = max(right.Rmax, right.sum + left.Rmax);
        this->Rmin = min(right.Rmin, right.sum + left.Rmin);

        //子
        this->Pmax = max({left.Pmax, right.Pmax, left.Rmax + right.Lmax});
        this->Pmin = min({left.Pmin, right.Pmin, left.Rmin + right.Lmin});

    }
} tree[maxn << 2];

void init();

void build(int, int, int);

int main() {
    init();
    for (int i = 1; i <= n; ++i) {
        sum += source[i];
        if (source[i] < k - 1)value[i] = 1;
        else value[i] = -k + 1;
    }
    build(1, 1, n);
    printf("%lld", sum + max({tree[1].sum, tree[1].Lmax, tree[1].Rmax, tree[1].Pmax,
                              tree[1].sum - tree[1].Lmin, tree[1].sum - tree[1].Rmin, tree[1].sum - tree[1].Pmin}));
    return 0;
}

void init() {
    memset(source, 0, sizeof(source));
    memset(value, 0, sizeof(value));
    scanf("%d%d", &n, &k);

    for (int i = 1; i <= n; ++i)
        scanf("%d", source + i);
}

void build(int id, int l, int r) {
    tree[id].l = l;
    tree[id].r = r;

    if (l == r) {
        tree[id].sum = tree[id].Lmax = tree[id].Rmax = tree[id].Pmax =
        tree[id].Lmin = tree[id].Rmin = tree[id].Rmin = value[r];
        return;
    }

    int mid = (l + r) >> 1;
    build(id << 1, l, mid);
    build(id << 1 | 1, mid + 1, r);

    tree[id].pushUp(tree[id << 1], tree[id << 1 | 1]);
}
