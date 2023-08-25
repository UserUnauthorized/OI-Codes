//AT_agc030_d
#include <bits/stdc++.h>

typedef long long valueType;
typedef std::vector<valueType> ValueVector;
typedef std::vector<ValueVector> ValueMatrix;

constexpr valueType MOD = 1e9 + 7;

template<typename T1, typename T2, typename T3 = valueType>
void Inc(T1 &a, T2 b, const T3 &mod = MOD) {
    a = a + b;

    if (a >= mod)
        a -= mod;
}

template<typename T1, typename T2, typename T3 = valueType>
void Dec(T1 &a, T2 b, const T3 &mod = MOD) {
    a = a - b;

    if (a < 0)
        a += mod;
}

template<typename T1, typename T2, typename T3 = valueType>
T1 sum(T1 a, T2 b, const T3 &mod = MOD) {
    return a + b >= mod ? a + b - mod : a + b;
}

template<typename T1, typename T2, typename T3 = valueType>
T1 sub(T1 a, T2 b, const T3 &mod = MOD) {
    return a - b < 0 ? a - b + mod : a - b;
}

template<typename T1, typename T2, typename T3 = valueType>
T1 mul(T1 a, T2 b, const T3 &mod = MOD) {
    return (long long) a * b % mod;
}

template<typename T1, typename T2, typename T3 = valueType>
void Mul(T1 &a, T2 b, const T3 &mod = MOD) {
    a = (long long) a * b % mod;
}

template<typename T1, typename T2, typename T3 = valueType>
T1 pow(T1 a, T2 b, const T3 &mod = MOD) {
    T1 result = 1;

    while (b > 0) {
        if (b & 1)
            Mul(result, a, mod);

        Mul(a, a, mod);
        b = b >> 1;
    }

    return result;
}

constexpr valueType Inv2 = 500000004;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    valueType N, M;

    std::cin >> N >> M;

    ValueVector source(N + 1);
    ValueMatrix F(N + 1, ValueVector(N + 1, 0));

    for (valueType i = 1; i <= N; ++i)
        std::cin >> source[i];

    for (valueType i = 1; i <= N; ++i)
        for (valueType j = 1; j <= N; ++j)
            if (source[i] > source[j])
                F[i][j] = 1;

    for (valueType t = 0; t < M; ++t) {
        valueType a, b;

        std::cin >> a >> b;

        for (valueType i = 1; i <= N; ++i) {
            if (i == a || i == b)
                continue;

            F[i][a] = F[i][b] = mul(sum(F[i][a], F[i][b]), Inv2);
            F[a][i] = F[b][i] = mul(sum(F[a][i], F[b][i]), Inv2);
        }

        F[a][b] = F[b][a] = mul(sum(F[a][b], F[b][a]), Inv2);
    }

    valueType ans = 0;

    for (valueType i = 1; i <= N; ++i) {
        for (valueType j = i + 1; j <= N; ++j) {
            Inc(ans, F[i][j]);
        }
    }


    Mul(ans, pow(2, M));

    std::cout << ans << std::endl;

    return 0;
}