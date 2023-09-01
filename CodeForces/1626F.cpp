//Codeforces - 1626F
#include <bits/stdc++.h>

typedef long long valueType;
typedef std::vector<valueType> ValueVector;
typedef std::vector<ValueVector> ValueMatrix;

constexpr valueType MOD = 998244353;

template<typename T1, typename T2, typename T3 = valueType>
void Inc(T1 &a, T2 b, const T3 &mod = MOD) {
    a = a + b;

    if (a >= mod)
        a -= mod;
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

valueType lcm(valueType a, valueType b) {
    return a / std::__gcd(a, b) * b;
}

int main() {
    valueType N, A0, X, Y, K, M;

    std::cin >> N >> A0 >> X >> Y >> K >> M;

    ValueVector source(N);

    source[0] = A0;

    for (valueType i = 1; i < N; ++i)
        source[i] = (source[i - 1] * X + Y) % M;

    valueType P = 1;

    for (valueType i = 2; i < K; ++i)
        P = lcm(P, i);

    ValueMatrix F(K, ValueVector(P, 0));

    for (auto const &iter: source)
        ++F[0][iter % P];

    valueType const InvN = pow(N, MOD - 2), reverseN = sub(1, InvN);

    for (valueType k = 1; k < K; ++k) {
        for (valueType i = 0; i < P; ++i) {
            Inc(F[k][i - i % k], mul(F[k - 1][i], InvN));
            Inc(F[k][i], mul(F[k - 1][i], reverseN));
        }
    }

    valueType ans = 0;

    for (valueType k = 0; k < K; ++k)
        for (valueType i = 0; i < P; ++i)
            Inc(ans, mul(F[k][i], i));

    for (auto const &iter: source)
        Inc(ans, mul(iter / P * P, K));

    Mul(ans, InvN);

    Mul(ans, pow(N, K));

    std::cout << ans << std::endl;

    return 0;
}