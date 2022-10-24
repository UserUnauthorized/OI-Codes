//HZ - 17.4
#include<bits/stdc++.h>

using namespace std;

int n, m, cl[50005], cr[50005];

void init();

int lowbit(int);

int sum_l(int);

void insert_l(int);

int sum_r(int);

void insert_r(int);

int main() {
    init();
    for (int i = 0; i < m; ++i) {
        int k, l, r;
        scanf("%d%d%d", &k, &l, &r);
        if (k == 1) {
            insert_l(l);
            insert_r(r);
        }
        if (k == 2) {
            printf("%d\n", sum_l(r) - sum_r(l - 1));
        }
    }
}

void init() {
    memset(cl, 0, sizeof(cl));
    memset(cr, 0, sizeof(cr));
    scanf("%d%d", &n, &m);
}

int lowbit(int x) {
    return (x & (-x));
}

int sum_l(int x) {
    int result(0);
    while (x > 0) {
        result += cl[x];
        x -= lowbit(x);
    }
    return result;
}

void insert_l(int x) {
    while (x <= n) {
        ++cl[x];
        x += lowbit(x);
    }
}

int sum_r(int x) {
    int result(0);
    while (x > 0) {
        result += cr[x];
        x -= lowbit(x);
    }
    return result;
}

void insert_r(int x) {
    while (x <= n) {
        ++cr[x];
        x += lowbit(x);
    }
}
