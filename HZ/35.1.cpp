//HZ - 35.1
//Luogu - P4316
#include <bits/stdc++.h>

typedef std::pair<int, int> EDGE;

int main() {
    int N, M;

    std::cin >> N >> M;

    std::vector<std::list<EDGE>> edge(N + 1);
    std::vector<int> degree(N + 1, 0);

    std::function<void(int, int, int)> addEdge = [&edge, &degree](int u, int v, int w) mutable {
        edge[v].emplace_back(u, w);
        ++degree[u];
    };

    for (int i = 0; i < M; ++i) {
        int u, v, w;

        std::cin >> u >> v >> w;

        addEdge(u, v, w);
    }

    std::vector<int> in(degree);
    std::vector<long double> dp(N + 1, 0);

    std::queue<int> que;
    que.push(N);

    while (!que.empty()) {
        int const x = que.front();
        que.pop();

        for (auto const &iter: edge[x]) {
            int const v = iter.first, w = iter.second;

            dp[v] += (dp[x] + w) / degree[v];

            if (--in[v] == 0)
                que.push(v);
        }
    }

    std::cout << std::setprecision(2) << std::fixed << dp[1] << std::flush;

    return 0;
}
