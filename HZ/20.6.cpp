//HZ - 20.6
//Luogu - P3503
#include<bits/stdc++.h>

using namespace std;

int n, m, a[1000005], k, ans;

long long sum[1000005];

void init();
void solve();

int main() {
    init();
    for (int i = 1; i <= m; ++i) {
        scanf("%d", &k);
        solve();
        printf("%d ", ans);
    }
    return 0;
}

void init() {
    memset(a, 0, sizeof(a));
    memset(sum, 0, sizeof(sum));
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
        scanf("%d", a + i);
}

void solve() {
    deque<int> que;
    ans = 0;

    for (int i = 1; i <= n; ++i)
        sum[i] = a[i] - k;
    for (int i = 2; i <= n; ++i)
        sum[i] += sum[i - 1];
    for (int i = 1; i <= n; ++i)
        if (que.empty() || sum[que.back()] > sum[i])
            que.push_back(i);
    for (int i(n), j(n); i >= 1; --i) {
        if (sum[i] >= 0) ans = max(ans, i);
        if (i == n || sum[i] > sum[j]) {
            while (!que.empty() && sum[i] >= sum[que.back()]) {
                ans = max(ans, i - que.back());
                que.pop_back();
            }
            j = i;
        }
    }
}
