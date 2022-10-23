//HZ - 20.5
//Luogu - P2947
#include<bits/stdc++.h>

using namespace std;

int n, h[100005], up[100005];

deque<int> que;

void init();

int main() {
    init();
    for (int i = n; i >= 1; --i) {
        while (!que.empty() && h[que.back()] <= h[i]) que.pop_back();
        if (!que.empty()) up[i] = que.back();
        que.push_back(i);
    }
    for (int i = 1; i <= n; ++i)
        printf("%d\n", up[i]);
    return 0;
}

void init() {
    memset(h, 0, sizeof(h));
    memset(up, 0, sizeof(up));
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        scanf("%d", h + i);
}
