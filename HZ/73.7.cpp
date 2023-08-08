//Luogu - P4827
#include <bits/stdc++.h>

typedef int valueType;
typedef std::vector<valueType> ValueVector;
typedef std::vector<ValueVector> ValueMatrix;

constexpr valueType MOD = 10007;

template<typename T1, typename T2, typename T3 = valueType>
void Inc(T1 &a, const T2 &b, const T3 &mod = MOD) {
    a = a + b;

    if (a >= mod)
        a -= mod;
}

template<typename T1, typename T2, typename T3 = valueType>
void Dec(T1 &a, const T2 &b, const T3 &mod = MOD) {
    a = a - b;

    if (a < 0)
        a += mod;
}

template<typename T1, typename T2, typename T3 = valueType>
T1 sum(const T1 &a, const T2 &b, const T3 &mod = MOD) {
    return a + b >= mod ? a + b - mod : a + b;
}

template<typename T1, typename T2, typename T3 = valueType>
T1 sub(const T1 &a, const T2 &b, const T3 &mod = MOD) {
    return a - b < 0 ? a - b + mod : a - b;
}

template<typename T1, typename T2, typename T3 = valueType>
T1 mul(const T1 &a, const T2 &b, const T3 &mod = MOD) {
    return (long long) a * b % mod;
}

template<typename T1, typename T2, typename T3 = valueType>
void Mul(T1 &a, const T2 &b, const T3 &mod = MOD) {
    a = (long long) a * b % mod;
}

template<typename T1, typename T2, typename T3 = valueType>
T1 Pow(T1 a, T2 b, const T3 &mod = MOD) {
    T1 result = 1;

    while (b > 0) {
        if (b & 1)
            Mul(result, a, mod);

        Mul(a, a, mod);
        b = b >> 1;
    }

    return result;
}

typedef std::list<valueType> EdgeList;
typedef std::vector<EdgeList> EdgeSet;

void Uncompress(std::istream &is, std::stringstream &os) {
    int N, k, L, i, now, A, B, Q, tmp;
    is >> N >> k >> L;
    os << N << " " << k << "\n";
    is >> now >> A >> B >> Q;
    for (i = 1; i < N; i++) {
        now = (now * A + B) % Q;
        tmp = (i < L) ? i : L;
        os << i - now % tmp << " " << i + 1 << "\n";
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    std::stringstream ss;
    Uncompress(std::cin, ss);
    std::cin.rdbuf(ss.rdbuf());

    valueType N, K;

    std::cin >> N >> K;

    valueType const M = K;

    // ======================================== preWork - BEGIN ========================================

    ValueVector Fact(M + 1, 1);

    Fact[0] = 1;
    for (valueType i = 1; i <= M; ++i)
        Fact[i] = mul(Fact[i - 1], i);

    ValueMatrix Stirling(M + 1, ValueVector(M + 1, 0));

    Stirling[0][0] = 1;
    for (valueType i = 1; i <= M; ++i)
        for (valueType j = 1; j <= i; ++j)
            Stirling[i][j] = sum(Stirling[i - 1][j - 1], mul(j, Stirling[i - 1][j]));

    // ========================================= preWork - END =========================================

    EdgeSet G(N + 1);

    for (valueType i = 1; i < N; ++i) {
        valueType u, v;

        std::cin >> u >> v;

        G[u].emplace_back(v);
        G[v].emplace_back(u);
    }

    ValueMatrix F(N + 1, ValueVector(K + 1, 0));

    typedef std::function<void(valueType, valueType)> DfsFunction;

    DfsFunction dfs = [&](valueType x, valueType from) {
        F[x][0] = 1;

        for (auto const &iter: G[x]) {
            if (iter == from)
                continue;

            dfs(iter, x);

            Inc(F[x][0], F[iter][0]);

            for (valueType i = 1; i <= K; ++i)
                Inc(F[x][i], sum(F[iter][i], F[iter][i - 1]));
        }
    };

    DfsFunction calc = [&](valueType x, valueType from) {
        if (from != 0) {
            for (valueType i = K; i >= 0; --i) {
                F[x][i] = F[from][i];

                if (i > 0) {
                    Inc(F[x][i], F[from][i - 1]);
                    Dec(F[x][i], mul(F[x][i - 1], 2));
                }

                if (i > 1)
                    Dec(F[x][i], F[x][i - 2]);
            }
        }

        for (auto const &iter: G[x]) {
            if (iter == from)
                continue;

            calc(iter, x);
        }
    };

    dfs(1, 0);
    calc(1, 0);

    typedef std::function<valueType(valueType)> SolveFunction;

    SolveFunction solve = [&](valueType n) {
        valueType result = 0;

        for (valueType i = 1; i <= K; ++i)
            Inc(result, mul(F[n][i], mul(Fact[i], Stirling[K][i])));

        return result;
    };

    for (valueType i = 1; i <= N; ++i)
        std::cout << solve(i) << '\n';

    std::cout << std::flush;

    return 0;
}