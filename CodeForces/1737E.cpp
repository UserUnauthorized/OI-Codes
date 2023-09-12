//Codeforces - 1737E
#include <bits/stdc++.h>

typedef long long valueType;
typedef std::vector<valueType> ValueVector;

constexpr valueType MOD = 1e9 + 7;
constexpr valueType Inv2 = 500000004;

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

int main() {
    valueType T;

    std::cin >> T;

    for (int testcase = 0; testcase < T; ++testcase) {
        valueType N;

        std::cin >> N;

        ValueVector Pow2(N + 1, 0);

        Pow2[0] = 1;
        for (valueType i = 1; i <= N; ++i)
            Pow2[i] = mul(Pow2[i - 1], Inv2);

        ValueVector F(N + 1, 0), G(N + 1, 0);

        F[N] = G[N] = Pow2[(N + 1) / 2 - 1];

        for (valueType i = N - 1; i >= 1; --i) {
            F[i] = Pow2[(i + 1) / 2];

            if (2 * i <= N)
                Mul(F[i], sub(1, G[2 * i]));

            if (i < N)
                G[i] = sum(G[i + 1], F[i]);
        }

        for (valueType i = 1; i <= N; ++i)
            std::cout << F[i] << '\n';

        std::cout << std::flush;
    }

    std::cout << std::flush;

    return 0;
}