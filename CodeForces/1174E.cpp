//Codeforces - 1174E
#include <bits/stdc++.h>

typedef int valueType;
typedef std::vector<valueType> ValueVector;

typedef std::array<valueType, 2> Data;
typedef std::vector<Data> DataVector;
typedef std::vector<DataVector> DataMatrix;

constexpr valueType MOD = 1e9 + 7;


#define ModOperSafeModOption false

template<typename T1, typename T2, typename T3 = valueType>
void Inc(T1 &a, T2 b, const T3 &mod = MOD) {
#if ModOperSafeModOption
    a %= mod;
    b %= mod;

    if (a < 0)
        a += mod;

    if (b < 0)
        b += mod;
#endif // ModOperSafeModOption

    a = a + b;

    if (a >= mod)
        a -= mod;
}

template<typename T1, typename T2, typename T3 = valueType>
void Dec(T1 &a, T2 b, const T3 &mod = MOD) {
#if ModOperSafeModOption
    a %= mod;
    b %= mod;

    if (a < 0)
        a += mod;

    if (b < 0)
        b += mod;
#endif // ModOperSafeModOption

    a = a - b;

    if (a < 0)
        a += mod;
}

template<typename T1, typename T2, typename T3 = valueType>
T1 sum(T1 a, T2 b, const T3 &mod = MOD) {
#if ModOperSafeModOption
    a %= mod;
    b %= mod;

    if (a < 0)
        a += mod;

    if (b < 0)
        b += mod;
#endif // ModOperSafeModOption

    return a + b >= mod ? a + b - mod : a + b;
}

template<typename T1, typename T2, typename T3 = valueType>
T1 sub(T1 a, T2 b, const T3 &mod = MOD) {
#if ModOperSafeModOption
    a %= mod;
    b %= mod;

    if (a < 0)
        a += mod;

    if (b < 0)
        b += mod;
#endif // ModOperSafeModOption

    return a - b < 0 ? a - b + mod : a - b;
}

template<typename T1, typename T2, typename T3 = valueType>
T1 mul(T1 a, T2 b, const T3 &mod = MOD) {
#if ModOperSafeModOption
    a %= mod;
    b %= mod;

    if (a < 0)
        a += mod;

    if (b < 0)
        b += mod;
#endif // ModOperSafeModOption

    return (long long) a * b % mod;
}

template<typename T1, typename T2, typename T3 = valueType>
void Mul(T1 &a, T2 b, const T3 &mod = MOD) {
#if ModOperSafeModOption
    a %= mod;
    b %= mod;

    if (a < 0)
        a += mod;

    if (b < 0)
        b += mod;
#endif // ModOperSafeModOption

    a = (long long) a * b % mod;
}

template<typename T1, typename T2, typename T3 = valueType>
T1 pow(T1 a, T2 b, const T3 &mod = MOD) {
#if ModOperSafeModOption
    a %= mod;
    b %= mod;

    if (a < 0)
        a += mod;

    if (b < 0)
        b += mod;
#endif // ModOperSafeModOption

    T1 result = 1;

    while (b > 0) {
        if (b & 1)
            Mul(result, a, mod);

        Mul(a, a, mod);
        b = b >> 1;
    }

    return result;
}

int main() {
    valueType N;

    std::cin >> N;

    auto const count = [N](valueType x) {
        return N / x;
    };

    auto const G = [](valueType i2, valueType i3) {
        return (1 << i2) * (i3 == 1 ? 3 : 1);
    };

    valueType M = std::floor(std::log2((long double) N));

    DataMatrix F(N + 1, DataVector(M + 1));

    F[1][M][0] = 1;

    if ((1 << (M - 1)) * 3 <= N)
        F[1][M - 1][1] = 1;

    for (valueType j = M - 1; j >= 0; --j) {
        for (valueType i = 2; i <= N; ++i) {
            Inc(F[i][j][0], mul(F[i - 1][j][0], count(G(j, 0)) - (i - 1)));
            Inc(F[i][j][1], mul(F[i - 1][j][1], count(G(j, 1)) - (i - 1)));

            Inc(F[i][j][0], mul(F[i - 1][j + 1][0], count(G(j, 0)) - count(G(j + 1, 0))));
            Inc(F[i][j][1], mul(F[i - 1][j + 1][1], count(G(j, 1)) - count(G(j + 1, 1))));

            Inc(F[i][j][0], mul(F[i - 1][j][1], count(G(j, 0)) - count(G(j, 1))));
        }
    }

    std::cout << F[N][0][0] << std::endl;

    return 0;
}