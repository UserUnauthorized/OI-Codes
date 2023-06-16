//HZ - 35.18
#include<bits/stdc++.h>

namespace DEBUG {
    template<typename T>
    inline void _debug(const char *format, T t) {
        std::cerr << format << '=' << t << std::endl;
    }

    template<class First, class... Rest>
    inline void _debug(const char *format, First first, Rest... rest) {
        while (*format != ',') std::cerr << *format++;
        std::cerr << '=' << first << ",";
        _debug(format + 1, rest...);
    }

    template<typename T>
    std::ostream &operator<<(std::ostream &os, const std::vector<T> &V) {
        os << "[ ";
        for (const auto &vv: V) os << vv << ", ";
        os << "]";
        return os;
    }

    std::ostream &operator<<(std::ostream &os, __int128 V) {
        if (V < 0) {
            os << '-';
            V = -V;
        }

        if (V > 9)
            os << V / 10;

        os << (int) (V % 10);

        return os;
    }

#define debug(...) _debug(#__VA_ARGS__, __VA_ARGS__)
}  // namespace DEBUG

using namespace DEBUG;

typedef int valueType;
constexpr valueType MOD = 1e9 + 7;

typedef std::vector<int> Vector;
typedef std::array<Vector, 2> PairVector;
typedef std::vector<Vector> Matrix;
typedef std::array<Matrix, 2> PairMatrix;
typedef std::list<int> OutEdgeList;
typedef std::vector<OutEdgeList> EdgeSet;
typedef std::function<void(int, int)> VoidFunction;
typedef std::function<valueType(int, int)> ValueFunction;
typedef std::function<valueType(int, int, const Matrix &)> CalcFunction;

int main() {
    int N, Q;

    std::cin >> N >> Q;

    EdgeSet edge(N + 1);

    VoidFunction addEdge = [&edge](int a, int b) mutable {
        edge[a].emplace_back(b);
        edge[b].emplace_back(a);
    };

    for (int i = 1; i < N; ++i) {
        int a, b;

        std::cin >> a >> b;

        addEdge(a, b);
    }

    Vector depth(N + 1, 0);
    PairVector dp;

    dp[0].resize(N + 1, 0);
    dp[1].resize(N + 1, 0);

    valueType const S = std::floor(std::log2(N) + 1);

    Matrix father(S);
    PairMatrix distance;

    distance[0].resize(S);
    distance[1].resize(S);

    for (int i = 0; i < S; ++i) {
        distance[0][i].resize(N + 1, 0);
        distance[1][i].resize(N + 1, 0);
        father[i].resize(N + 1, 0);
    }

    VoidFunction dfs = [&](int x, int from) mutable {
        bool isLeaf = true;

        for (auto const &iter: edge[x]) {
            if (iter == from)
                continue;

            isLeaf = false;

            dfs(iter, x);

            dp[0][x] = ((long long) dp[0][x] + dp[0][iter]) % MOD;
        }

        dp[0][x] = ((long long) dp[0][x] + edge[x].size()) % MOD;

        if (isLeaf)
            dp[0][x] = 1;
    };

    VoidFunction calc = [&](int x, int from) mutable {
        dp[1][x] = ((long long) dp[1][from] + dp[0][from] - dp[0][x]) % MOD;

        if (from == 0)
            dp[1][x] = 0;

        depth[x] = depth[from] + 1;
        father[0][x] = from;
        distance[0][0][x] = dp[0][x];
        distance[1][0][x] = dp[1][x];

        for (int i = 1; i < S; ++i) {
            father[i][x] = father[i - 1][father[i - 1][x]];
            distance[0][i][x] = ((long long) distance[0][i - 1][x] + distance[0][i - 1][father[i - 1][x]]) % MOD;
            distance[1][i][x] = ((long long) distance[1][i - 1][x] + distance[1][i - 1][father[i - 1][x]]) % MOD;
        }

        for (auto const &iter: edge[x]) {
            if (iter == from)
                continue;

            calc(iter, x);
        }
    };

    dfs(1, 0);
    calc(1, 0);

    ValueFunction LCA = [&depth, &father, S](int x, int y) {
        if (depth[x] > depth[y])
            std::swap(x, y);

        int difference = depth[y] - depth[x];

        for (int i = 0; difference > 0; ++i, difference >>= 1)
            if (difference & 1)
                y = father[i][y];

        if (x == y)
            return x;

        for (int i = S - 1; i >= 0; --i) {
            if (father[i][x] != father[i][y]) {
                x = father[i][x];
                y = father[i][y];
            }
        }

        return father[0][x];
    };

    CalcFunction weight = [&depth, &father, S](int from, int to, const Matrix &distance) {
        valueType result = 0;

        int difference = depth[from] - depth[to];

        for (int i = 0; difference > 0; ++i, difference >>= 1) {
            if (difference & 1) {
                result = ((long long) result + distance[i][from]) % MOD;
                from = father[i][from];
            }
        }

        if (from == to)
            return result;

        throw std::range_error("");
    };

    ValueFunction ans = [&](int a, int b) {
        int const lca = LCA(a, b);

        return ((long long) weight(a, lca, distance[0]) + weight(b, lca, distance[1]));
    };

    for (int i = 0; i < Q; ++i) {
        int a, b;

        std::cin >> a >> b;

        std::cout << ans(a, b) << '\n';
    }

    std::cout << std::flush;

    return 0;
}
