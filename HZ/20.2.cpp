//HZ - 20.2
#include<bits/stdc++.h>

using namespace std;

deque<int> que, empty;

int h[400005], n, l[400005], r[400005];

long long ans;

void init();
void getR();
void getL();
void getA();

int main() {
    init();
    getR();
    getL();
    getA();
    printf("%lld", ans);
    return 0;
}

void init() {
    memset(h, 0, sizeof(h));
    memset(l, 0, sizeof(l));
    memset(r, 0, sizeof(r));
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", h + i);
    }
    h[0] = h[n + 1] = 0;
}

void getR() {
    for (int i = 1; i <= n + 1; ++i) {
        while (!que.empty() && h[que.back()] > h[i]) {
            r[que.back()] = i;
            que.pop_back();
        }
        que.push_back(i);
    }
}

void getL() {
    for (int i = n; i >= 0; --i) {
        while (!que.empty() && h[que.back()] > h[i]) {
            l[que.back()] = i;
            que.pop_back();
        }
        que.push_back(i);
    }
}

void getA() {
    ans = 0;
    for (int i = 1; i <= n; ++i) {
        ans = max(ans, (long long) (r[i] - l[i] - 1) * h[i]);
    }
}
