//Luogu - P8965
#include <bits/stdc++.h>

typedef int valueType;

typedef std::vector<valueType> ValueVector;

valueType N_, M_;
valueType const &N = N_, &M = M_;

typedef std::pair<int, valueType> EdgePair;
typedef std::list<EdgePair> EdgeList;
typedef std::vector<EdgeList> EdgeSet;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    std::cin >> N_ >> M_;

    EdgeSet edge(N + 1);
    ValueVector value(N + 1, 0);

    std::function<void(int, int, valueType)> addEdge = [&](int u, int v, valueType w) {
        edge[u].emplace_back(v, w);
        edge[v].emplace_back(u, w);
    };

    for (int i = 1; i < N; ++i) {
        int a, b, w;

        std::cin >> a >> b >> w;

        addEdge(a, b, w);
    }

    std::function<void(int, int)> dfs = [&](int x, int from) {
        for (auto const &iter: edge[x]) {
            if (iter.first == from)
                continue;

            value[iter.first] = value[x] ^ iter.second;

            dfs(iter.first, x);
        }
    };

    dfs(1, 0);

    std::function<valueType(valueType, valueType)> XOR = [](valueType a, valueType b) -> valueType {
        return a ^ b;
    };

    ValueVector sum(N + 1);

    std::partial_sum(value.begin(), value.end(), sum.begin(), XOR);

    for (int i = 1; i <= M; ++i) {
        int x, y, l, r;

        std::cin >> x >> y >> l >> r;

        valueType const distance = r - l + 1;

        valueType const result = (distance & 1 ? value[x] ^ value[y] : 0);

        std::cout << result << '\n';
    }

    std::cout << std::flush;

    return 0;
}