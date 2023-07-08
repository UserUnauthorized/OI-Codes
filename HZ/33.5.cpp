//HZ - 33.5
#include <bits/stdc++.h>

#ifdef CLION

#include<debug.h>

#else
#define debug(...)
#endif

typedef long long valueType;
typedef std::vector<valueType> ValueVector;

constexpr valueType MOD = 1e9 + 7;

class Inverse {
private:
    valueType size;

    ValueVector inv;

public:
    explicit Inverse(valueType N) : size(N), inv(N + 1, 1) {
        inv[0] = inv[1] = 1;

        for (valueType i = 2; i <= N; ++i)
            inv[i] = (long long) (MOD - MOD / i) * inv[MOD % i] % MOD;
    }

    valueType operator()(valueType i) const {
        i %= MOD;

        if (__builtin_expect(i > size, false))
            throw std::out_of_range("Too Large.");

        return inv[i];
    }

    const ValueVector &data() const {
        return inv;
    }
};

int main() {
    valueType N, K;

    std::cin >> N >> K;

    valueType const M = N - K;

    Inverse Inv(N);

    typedef std::function<valueType(const valueType &, const valueType &)> ModCalc;

    ModCalc Op = [](const valueType &a, const valueType &b) -> valueType {
        return (a * b) % MOD;
    };

    ValueVector factorial(N + 1);

    std::iota(factorial.begin(), factorial.end(), 0);
    factorial[0] = 1;

    std::partial_sum(factorial.begin(), factorial.end(), factorial.begin(), Op);

    ValueVector inverseFactorial = Inv.data();

    std::partial_sum(inverseFactorial.begin(), inverseFactorial.end(), inverseFactorial.begin(), Op);

    typedef std::function<valueType(const valueType &, const valueType &)> Calc;

    Calc C = [&factorial, &inverseFactorial](const valueType &n, const valueType &m) -> valueType {
        if (n < m)
            return 0;

        return factorial[n] * inverseFactorial[m] % MOD * inverseFactorial[n - m] % MOD;
    };

    ValueVector power(N + 1, 0);

    power[0] = 1;
    for(valueType i = 1; i <= N; ++i)
        power[i] = power[i - 1] * 2 % (MOD - 1);

    Calc pow = [](valueType a, valueType b) -> valueType {
        valueType result = 1;

        while(b > 0) {
            if(b & 1)
                result = result * a % MOD;

            a = a * a % MOD;

            b = b >> 1;
        }

        return result;
    };

    valueType ans = 0;

    for(valueType i = 0; i <= M; ++i) {
        valueType const t = C(M, i) * pow(2, power[M - i]) % MOD;

        if(i & 1)
            ans = (ans - t + MOD) % MOD;
        else
            ans = (ans + t) % MOD;
    }

    ans = ans * C(N, K) % MOD;

    std::cout << ans << std::endl;

    return 0;
}