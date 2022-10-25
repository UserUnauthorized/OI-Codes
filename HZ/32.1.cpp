//HZ - 32.1
#include <bits/stdc++.h>

using namespace std;
constexpr int maxn = 200005;

inline int read();

int n(read()), m(read()), ans, source[maxn], sum[maxn];

void init();

int main() {
    init();
    deque<int> que;
    ans = source[1];
    for (int i = 1; i <= n; ++i) {
        while (!que.empty() && sum[que.back()] >= sum[i - 1])
            que.pop_back();
        que.push_back(i - 1);
        while (!que.empty() && que.front() < i - m)
            que.pop_front();
        ans = max(ans, sum[i] - sum[que.front()]);
    }
    printf("%d", ans);
    return 0;
}

void init() {
    memset(source, 0, sizeof(source));
    memset(sum, 0, sizeof(sum));

    for (int i = 1; i <= n; ++i)
        scanf("%d", source + i);

    partial_sum(source + 1, source + n + 1, sum + 1);
}

inline int read() {
    int result(0);
    char ch(getchar());
    while (ch < '0' || ch > '9')
        ch = getchar();
    while (ch >= '0' && ch <= '9') {
        result = (result << 3) + (result << 1) + (ch ^ 48);
        ch = getchar();
    }
    return result;
}