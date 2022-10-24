//HZ - 265.2
#include<bits/stdc++.h>

using namespace std;

const int maxn = 10000007;

int n, A, B, ans = INT_MAX, source[maxn], dpA[maxn], dpB[maxn], white[maxn];

deque<int> que;

void init();
void dp();

int main() {
    init();
    dp();
    partial_sum(white, white + n + 1, white);
    for (int i = 1; i <= n; ++i)
        if (dpA[i] == -1 || dpB[i] == -1)
            continue;
        else
            ans = min(ans, white[i] - white[min(dpA[i], dpB[i])]);
    printf("%d", ans);
    return 0;
}

void init() {
    memset(source, 0, sizeof(source));
    memset(dpA, 0, sizeof(dpA));
    memset(dpB, 0, sizeof(dpB));
    memset(white, 0, sizeof(white));

    scanf("%d%d%d", &n, &A, &B);

    for (int i = 1; i <= n; ++i)
        scanf("%d", source + i);
}

void dp() {
    //A
    for (int i = 1; i <= n; ++i) {
        if (source[i] == 1)
            que.push_back(i);
        while (!que.empty() && que.size() > A) {
            que.pop_front();
        }
        if (!que.empty() && que.size() == A)
            dpA[i] = que.front();
        else
            dpA[i] = -1;
    }

    que.clear();

    //B
    for (int i = 1; i <= n; ++i) {
        if (source[i] == 2)
            que.push_back(i);
        while (!que.empty() && que.size() > B)
            que.pop_front();
        if (!que.empty() && que.size() == B)
            dpB[i] = que.front();
        else
            dpB[i] = -1;
    }

    //white
    for (int i = 1; i <= n; ++i)
        if (source[i] == 0)
            white[i] = 1;
}