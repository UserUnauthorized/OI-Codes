//HZ - 73.4
//Luogu - P4859
#include <bits/stdc++.h>

typedef long long valueType;
typedef std::vector<valueType> ValueVector;
typedef std::vector<ValueVector> ValueMatrix;

constexpr valueType MOD = 1e9 + 9;

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
    if (b < 0)
        b = (b % (MOD - 1) + (MOD - 1)) % (MOD - 1);

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
    valueType N;
    container data;
public:
    explicit Inverse(valueType n) : N(n), data(N + 1, 0) {
        data[1] = 1;

        for (valueType i = 2; i <= N; ++i)
            data[i] = mul((MOD - MOD / i), data[MOD % i]);
    }

    valueType operator()(valueType n) const {
        return data[n];
    }
};

int main() {
    valueType N, K;

    std::cin >> N >> K;

    if ((N - K) & 1) {
        std::cout << 0 << std::endl;

        return 0;
    }

    valueType const M = (N + K) >> 1;

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

    ValueVector sourceA(N + 1, 0), sourceB(N + 1, 0);

    for (valueType i = 1; i <= N; ++i)
        std::cin >> sourceA[i];

    for (valueType i = 1; i <= N; ++i)
        std::cin >> sourceB[i];

    std::sort(sourceA.begin() + 1, sourceA.end());
    std::sort(sourceB.begin() + 1, sourceB.end());

    ValueMatrix dp(N + 1, ValueVector(N + 1, 0));

    dp[0][0] = 1;
    valueType lessCount = 0;

    for (valueType i = 1; i <= N; ++i) {
        while (lessCount < N && sourceA[i] > sourceB[lessCount + 1])
            ++lessCount;

        dp[i][0] = 1;

        for (valueType j = 1; j <= lessCount; ++j) {
            Inc(dp[i][j], dp[i - 1][j]);
            Inc(dp[i][j], mul(dp[i - 1][j - 1], sub(lessCount, j - 1)));
        }
    }

    ValueVector F(N + 1, 0);

    for (valueType i = 0; i <= N; ++i)
        F[i] = mul(A(N - i, N - i), dp[N][i]);

    valueType ans = 0;

    for (valueType i = M; i <= N; ++i) {
        if ((i - M) & 1)
            Dec(ans, mul(C(i, M), F[i]));
        else
            Inc(ans, mul(C(i, M), F[i]));
    }

    std::cout << ans << std::endl;

    return 0;
}