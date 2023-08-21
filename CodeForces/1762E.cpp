//Codeforces - 1762E
#include <bits/stdc++.h>

typedef long long valueType;
typedef std::vector<valueType> ValueVector;

constexpr valueType MOD = 998244353;

bool ModOperSafeModOption = false;

template<typename T1, typename T2, typename T3 = valueType>
void Inc(T1 &a, T2 b, const T3 &mod = MOD) {
    if (ModOperSafeModOption) {
        a %= mod;
        b %= mod;

        if (a < 0)
            a += mod;

        if (b < 0)
            b += mod;
    }

    a = a + b;

    if (a >= mod)
        a -= mod;
}

template<typename T1, typename T2, typename T3 = valueType>
void Dec(T1 &a, T2 b, const T3 &mod = MOD) {
    if (ModOperSafeModOption) {
        a %= mod;
        b %= mod;

        if (a < 0)
            a += mod;

        if (b < 0)
            b += mod;
    }

    a = a - b;

    if (a < 0)
        a += mod;
}

template<typename T1, typename T2, typename T3 = valueType>
T1 sum(T1 a, T2 b, const T3 &mod = MOD) {
    if (ModOperSafeModOption) {
        a %= mod;
        b %= mod;

        if (a < 0)
            a += mod;

        if (b < 0)
            b += mod;
    }

    return a + b >= mod ? a + b - mod : a + b;
}

template<typename T1, typename T2, typename T3 = valueType>
T1 sub(T1 a, T2 b, const T3 &mod = MOD) {
    if (ModOperSafeModOption) {
        a %= mod;
        b %= mod;

        if (a < 0)
            a += mod;

        if (b < 0)
            b += mod;
    }

    return a - b < 0 ? a - b + mod : a - b;
}

template<typename T1, typename T2, typename T3 = valueType>
T1 mul(T1 a, T2 b, const T3 &mod = MOD) {
    if (ModOperSafeModOption) {
        a %= mod;
        b %= mod;

        if (a < 0)
            a += mod;

        if (b < 0)
            b += mod;
    }

    return (long long) a * b % mod;
}

template<typename T1, typename T2, typename T3 = valueType>
void Mul(T1 &a, T2 b, const T3 &mod = MOD) {
    if (ModOperSafeModOption) {
        a %= mod;
        b %= mod;

        if (a < 0)
            a += mod;

        if (b < 0)
            b += mod;
    }

    a = (long long) a * b % mod;
}

template<typename T1, typename T2, typename T3 = valueType>
T1 pow(T1 a, T2 b, const T3 &mod = MOD) {
    if (ModOperSafeModOption) {
        a %= mod;
        b %= mod - 1;

        if (a < 0)
            a += mod;

        if (b < 0)
            b += mod - 1;
    }

    T1 result = 1;

    while (b > 0) {
        if (b & 1)
            Mul(result, a, mod);

        Mul(a, a, mod);
        b = b >> 1;
    }

    return result;
}

class Inverse {
public:
    typedef ValueVector container;

private:
    valueType size;
    container data;
public:
    explicit Inverse(valueType n) : size(n), data(size + 1, 0) {
        data[1] = 1;

        for (valueType i = 2; i <= size; ++i)
            data[i] = mul((MOD - MOD / i), data[MOD % i]);
    }

    valueType operator()(valueType n) const {
        return data[n];
    }
};

int main() {
    valueType N;

    std::cin >> N;

    Inverse Inv(N);

    ValueVector Fact(N + 1, 1), InvFact(N + 1, 1);

    Fact[0] = 1;
    InvFact[0] = 1;
    for (valueType i = 1; i <= N; ++i) {
        Fact[i] = mul(Fact[i - 1], i);
        InvFact[i] = mul(InvFact[i - 1], Inv(i));
    }

    typedef std::function<valueType(valueType, valueType)> CalcFunction;

    CalcFunction C = [&Fact, &InvFact](valueType n, valueType m) -> valueType {
        if (n < 0 || m < 0 || n < m)
            return 0;

        return mul(Fact[n], mul(InvFact[m], InvFact[n - m]));
    };

    valueType ans = 0;

    for(valueType i = 1; i < N; ++i) {
        valueType sum = 1;

        Mul(sum, C(N - 2, i - 1));
        Mul(sum, mul(i, N - i));
        Mul(sum, mul(pow(i, i - 2), pow(N - i, N - i - 2)));

        if (i & 1)
            Dec(ans, sum);
        else
            Inc(ans, sum);
    }

    std::cout << ans << std::endl;

    return 0;
}