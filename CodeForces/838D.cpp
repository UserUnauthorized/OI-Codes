//Codeforces - 838D
#include <bits/stdc++.h>

typedef long long valueType;

constexpr valueType MOD = 1e9 + 7;

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

int main() {
    valueType N, M;

    std::cin >> N >> M;

    valueType const ans = mul(mul(N + 1 - M, pow(N + 1, MOD - 2)), pow(2 * (N + 1), M));

    std::cout << ans << std::endl;
}