//ABC313F
#include <bits/stdc++.h>

typedef long long valueType;
typedef long double realType;
typedef std::vector<valueType> ValueVector;
typedef std::vector<ValueVector> ValueMatrix;
typedef std::pair<valueType, valueType> ValuePair;
typedef std::vector<ValuePair> PairVector;
typedef std::vector<bool> bitset;

ValueVector count;

valueType dfs(valueType x, ValueVector const &C, ValueVector const &set, ValueMatrix const &G) {
    if (x == set.size())
        return 0;

    valueType ans = dfs(x + 1, C, set, G);

    valueType sum = C[set[x]];

    for (auto const &iter: G[set[x]]) {
        if (count[iter] == 0)
            sum += C[iter];

        ++count[iter];
    }

    sum += dfs(x + 1, C, set, G);

    for (auto const &iter: G[set[x]])
        --count[iter];

    return std::max(ans, sum);
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    valueType N, M;

    std::cin >> N >> M;

    PairVector edge;

    ValueVector A(N), B(N);

    for (valueType i = 0; i < N; ++i)
        std::cin >> A[i] >> B[i];

    for (valueType i = 0; i < M; ++i) {
        valueType X, Y;

        std::cin >> X >> Y;

        --X;
        --Y;

        if (X == Y) {
            if (A[X] < B[X])
                std::swap(A[X], B[X]);

            continue;
        }

        edge.emplace_back(X, Y);
    }

    valueType const base = std::accumulate(A.begin(), A.end(), (valueType) 0);

    ValueVector C(N);

    for (valueType i = 0; i < N; ++i)
        C[i] = B[i] - A[i];

    bitset exist(N, true);
    ValueMatrix G(N);

    for (auto const &iter: edge) {
        if (C[iter.first] < 0 && C[iter.second] < 0)
            continue;

        if (C[iter.first] >= 0 && C[iter.second] >= 0) {
            exist[iter.first] = false;
            exist[iter.second] = false;

            continue;
        }

        if (!exist[iter.first] || !exist[iter.second])
            continue;

        if (C[iter.first] < 0)
            G[iter.first].push_back(iter.second);
        else
            G[iter.second].push_back(iter.first);
    }

    valueType ans = 0;
    valueType leftCount = 0, rightCount = 0;
    ValueVector rightSet, id(N), node(N);

    for (valueType i = 0; i < N; ++i) {
        if (!exist[i]) {
            ans += C[i];

            continue;
        }

        if (C[i] >= 0) {
            id[i] = leftCount;
            node[leftCount] = i;

            ++leftCount;
        } else {
            for (auto iter = G[i].begin(); iter != G[i].end();)
                if (!exist[*iter])
                    iter = G[i].erase(iter);
                else
                    ++iter;

            if (G[i].empty())
                continue;

            ++rightCount;

            rightSet.push_back(i);
        }
    }

    if (leftCount <= rightCount) {
        valueType const S = 1 << leftCount;

        ValueVector V(S, 0);

        for (valueType j = 0; j < S; ++j)
            for (valueType i = 0; i < leftCount; ++i)
                if (j & (1 << i))
                    V[j] += C[node[i]];

        ValueVector F(S, std::numeric_limits<valueType>::min() >> 1);

        F[0] = 0;

        for (auto const i: rightSet) {
            valueType bit = 0;

            for (auto const &iter: G[i])
                bit |= 1 << id[iter];

            for (valueType j = 0; j < S; ++j)
                F[j | bit] = std::max(F[j | bit], F[j] + C[i]);
        }

        valueType max = std::numeric_limits<valueType>::min();

        for (valueType i = 0; i < S; ++i)
            max = std::max(max, V[i] + F[i]);

        std::cout << std::fixed << std::setprecision(10) << (realType) (2 * base + ans + max) / 2.0 << std::endl;
    } else {
        count.resize(N, 0);

        std::cout << std::fixed << std::setprecision(10) << (realType) (2 * base + ans + dfs(0, C, rightSet, G)) / 2.0
                  << std::endl;
    }
}