//Codeforces - 1823F
#include <bits/stdc++.h>

typedef long long valueType;
typedef std::vector<valueType> ValueVector;
typedef std::vector<ValueVector> ValueMatrix;

constexpr valueType MOD = 998244353;

template<typename T1, typename T2, typename T3 = valueType>
T1 mul(T1 a, T2 b, const T3 &mod = MOD) {
    return (long long) a * b % mod;
}

valueType N, S, T;
ValueVector ans, distance;
ValueMatrix G;

void dfs(valueType x, valueType from) {
    if (x == T) {
        distance[x] = 0;

        return;
    }

    for (auto const &iter: G[x]) {
        if (iter == from)
            continue;

        dfs(iter, x);

        if (distance[iter] != -1) {
            distance[x] = distance[iter] + 1;

            return;
        }
    }
}

void calc(valueType x, valueType from, valueType k) {
    ans[x] = mul(k, G[x].size());

    for (auto const &iter: G[x]) {
        if (iter == from)
            continue;

        calc(iter, x, k);
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    std::cin >> N >> S >> T;

    ans.resize(N + 1, 0);
    distance.resize(N + 1, -1);
    G.resize(N + 1);

    for (valueType i = 1; i < N; ++i) {
        valueType u, v;

        std::cin >> u >> v;

        G[u].push_back(v);
        G[v].push_back(u);
    }

    dfs(S, 0);

    for (valueType i = 1; i <= N; ++i) {
        if (distance[i] != -1) {
            ans[i] = mul(distance[i], G[i].size());

            for (auto const &iter: G[i])
                if (distance[iter] == -1)
                    calc(iter, i, distance[i]);
        }
    }

    ans[T] = 1;

    for (valueType i = 1; i <= N; ++i)
        std::cout << ans[i] << ' ';

    std::cout << std::endl;

    return 0;
}