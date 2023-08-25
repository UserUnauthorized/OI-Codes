//Codeforces - 1815D
#include <bits/stdc++.h>

typedef long long valueType;
typedef std::pair<valueType, valueType> ValuePair;

constexpr valueType MOD = 998244353;

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

ValuePair solve(valueType n) {
    if (n == 0)
        return std::make_pair(0, 1);

    if (n == 1)
        return std::make_pair(1, 1);

    if (n & 1) {
        auto const result = solve(n >> 1);

        return std::make_pair(sum(mul(result.first, 2), result.second), result.second);
    } else {
        auto const A = solve(n / 2), B = solve(n / 2 - 1);

        return std::make_pair(mul(sum(A.first, B.first), 2), sum(A.second, B.second));
    }
}

constexpr valueType Inv2 = 499122177;

int main() {
    valueType T;

    std::cin >> T;

    for (valueType testcase = 0; testcase < T; ++testcase) {
        valueType N, M;

        std::cin >> N >> M;

        if (N == 0) {
            std::cout << 0 << '\n';
        } else if (M == 1) {
            std::cout << (N % MOD) << '\n';
        } else if (M == 2) {
            std::cout << (solve(N).first % MOD) << '\n';
        } else {
            if (N & 1) {
                std::cout << (mul((N + 1) % MOD, mul(((N + 1) / 2) % MOD, Inv2))) << '\n';
            } else {
                std::cout << (mul((N + 2) % MOD, mul((N / 2) % MOD, Inv2))) << '\n';
            }
        }
    }

    std::cout << std::flush;

    return 0;
}