//HZ - 35.13
//Luogu - P4284
#include<bits/stdc++.h>

typedef long double realType;
typedef int valueType;
typedef std::vector<realType> realVector;
typedef std::vector<valueType> valueVector;
typedef std::pair<valueType, realType> EdgeType;
typedef std::list<EdgeType> EdgeList;
typedef std::vector<EdgeList> EdgeMatrix;

int main() {
    int N;

    std::cin >> N;

    realVector P(N + 1, 0), dp(N + 1, 0), ans(N + 1, 0);
    EdgeMatrix edge(N + 1);

    std::function<void(valueType, valueType, realType)> addEdge = [&edge](valueType a, valueType b,
                                                                          realType p) mutable {
        edge[a].emplace_back(b, p);
        edge[b].emplace_back(a, p);
    };

    for (int i = 1; i < N; ++i) {
        int a, b, p;

        std::cin >> a >> b >> p;

        addEdge(a, b, (realType) p / 100);
    }

    for (int i = 1; i <= N; ++i) {
        int p;

        std::cin >> p;

        P[i] = (realType) p / 100;
    }

    typedef std::function<void(int, int)> DfsFunction;

    DfsFunction dfs = [&edge, &P, &dp, &dfs](int x, int from) mutable {
        dp[x] = 1 - P[x];

        for (auto const &iter: edge[x]) {
            int const to = iter.first;

            if (to == from)
                continue;

            dfs(to, x);

            P[to] = dp[to] + (1 - dp[to]) * (1 - iter.second);

            dp[x] *= P[to];
        }
    };

    DfsFunction calc = [&edge, &P, &dp, &ans, &calc](int x, int from) mutable {
        for (auto const &iter: edge[x]) {
            int const to = iter.first;

            if (to == from)
                continue;

            if (P[to] == 0)
                P[to] = 1;

            realType const t = ans[x] / P[to];

            ans[to] = dp[to] * (t + (1 - t) * (1 - iter.second));

            calc(to, x);
        }
    };

    dfs(1, 0);

    ans[1] = dp[1];

    calc(1, 0);

    realType result = 0;

    for (int i = 1; i <= N; ++i)
        result += ans[i];

    result = N - result;

    std::cout << std::setprecision(6) << std::fixed << result << std::flush;

    return 0;
}
