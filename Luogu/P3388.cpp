//Luogu - P3388
#include<bits/stdc++.h>

using namespace std;

constexpr int maxN = 2e4 + 5, maxM = 1e5 + 5;

struct EDGE {
    int next;
    int to;

    EDGE() : next(-1), to(-1) {};

    EDGE(int _next_, int _to_) : next(_next_), to(_to_) {};
};

array<EDGE, maxM << 1> edge;
array<int, maxN> head, dfn, low;
array<bool, maxN> cut;

void init();

void tarjan(int x, int from);

int N, M;

int main() {
    init();

    for (int i = 1; i <= N; ++i)
        if (dfn[i] == 0)
            tarjan(i, 0);

    int ans = 0;
    queue<int> que;

    for (int i = 1; i <= N; ++i) {
        if (cut[i]) {
            ++ans;
            que.push(i);
        }
    }

    cout << ans << '\n';

    while (!que.empty()) {
        cout << que.front() << ' ';
        que.pop();
    }

    return 0;
}

void init() {
    cin >> N >> M;

    for (int i = 1; i <= M; ++i) {
        int x, y;
        cin >> x >> y;

        edge[i << 1] = EDGE(head[x], y);
        edge[i << 1 | 1] = EDGE(head[y], x);

        head[x] = i << 1;
        head[y] = i << 1 | 1;
    }
}

void tarjan(int x, int from) {
    static int cnt = 0;

    dfn[x] = low[x] = ++cnt;

    int son = 0;
    bool first = true;

    for (int i = head[x]; i != 0; i = edge[i].next) {
        int const to = edge[i].to;

        if (first && to == from) {
            first = false;
            continue;
        }

        if (!dfn[to]) {
            ++son;
            tarjan(to, x);
            low[x] = min(low[x], low[to]);

            if (dfn[x] <= low[to] && (from > 0 || son > 1))
                cut[x] = true;

        } else {
            low[x] = min(low[x], dfn[to]);
        }
    }
}
