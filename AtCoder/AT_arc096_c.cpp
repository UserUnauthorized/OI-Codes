//AT_agc096_c
#include <bits/stdc++.h>

typedef int valueType;
typedef std::vector<valueType> ValueVector;
typedef std::vector<ValueVector> ValueMatrix;

valueType MOD_;
valueType const &MOD = MOD_;

template<typename T1, typename T2, typename T3 = valueType>
void Inc(T1 &a, const T2 &b, const T3 &mod = MOD) {
    a = a + b;

    if (a > mod)
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

    std::cin >> N >> MOD_;

    // ======================================== preWork - BEGIN ========================================
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

    CalcFunction A = [&Fact, &InvFact](valueType n, valueType m) -> valueType {
        if (n < 0 || m < 0 || n < m)
            return 0;

        return mul(Fact[n], InvFact[n - m]);
    };

    // ========================================= preWork - END =========================================

    ValueMatrix G(N + 1, ValueVector(N + 1, 0));

    G[0][0] = 1;
    for (valueType i = 1; i <= N; ++i) {
        G[i][0] = 1;

        for (valueType j = 1; j <= N; ++j)
            G[i][j] = sum(mul(j + 1, G[i - 1][j]), G[i - 1][j - 1]);

    }

    valueType ans = 0;

    for (valueType i = 0; i <= N; ++i) {
        valueType const Pow2 = mul(Pow(2, Pow(2, N - i, MOD - 1), MOD), C(N, i));

        valueType const pre = (i & 1 ? MOD - Pow2 : Pow2);

        valueType const PowN = Pow(2, N - i, MOD);
        valueType PowJ = 1;

        for (valueType j = 0; j <= i; ++j, Mul(PowJ, PowN))
            Inc(ans, mul(pre, mul(PowJ, G[i][j])));
    }

    std::cout << ans << std::endl;

    return 0;
}