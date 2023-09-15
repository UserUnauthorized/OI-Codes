#include <bits/stdc++.h>

typedef long long valueType;
typedef std::map<valueType, valueType> ValueMap;

constexpr valueType MOD = 998244353;

template<typename T1, typename T2, typename T3 = valueType>
void Inc(T1 &a, T2 b, const T3 &mod = MOD) {
    a = a + b;

    if (a >= mod)
        a -= mod;
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

const valueType Inv5 = pow(5, MOD - 2);

valueType N;
ValueMap memory;

valueType F(valueType n) {
    if (memory.find(n) != memory.end())
        return memory[n];

    if (n == N)
        return memory[n] = 1;

    if (n > N)
        return memory[n] = 0;

    valueType result = 0;

    for (valueType i = 2; i <= 6; ++i)
        Inc(result, F(i * n));

    Mul(result, Inv5);

    return memory[n] = result;
}

int main() {
    std::cin >> N;

    std::cout << F(1) << std::endl;

    return 0;
}