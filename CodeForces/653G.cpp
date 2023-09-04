//Codeforces - 653G
#include <bits/stdc++.h>

typedef int valueType;
typedef std::vector<valueType> ValueVector;
typedef std::vector<bool> bitset;

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

class LineSieve {
public:
    typedef std::vector<valueType> container;

private:
    valueType N;
    container prime;
    bitset isPrime;
    container mobius;

public:
    explicit LineSieve(valueType n) : N(n), prime(), isPrime(n + 1, true), mobius(n + 1, 1) {
        mobius[1] = 1;

        for (valueType i = 2; i <= N; ++i) {
            if (isPrime[i]) {
                prime.push_back(i);

                mobius[i] = -1;
            }

            for (auto const &iter: prime) {
                valueType const t = i * iter;

                if (t > N)
                    break;

                isPrime[t] = false;

                if (i % iter == 0) {
                    mobius[t] = 0;

                    break;
                } else {
                    mobius[t] = -mobius[i];
                }
            }

            if (mobius[i] < 0)
                mobius[i] += MOD;
        }
    }

    valueType operator()(valueType n) const {
        return mobius[n];
    }

    const container &Prime() const {
        return prime;
    }
};

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

constexpr valueType V = 3e5;

int main() {
    valueType N;

    std::cin >> N;

    Inverse const Inv(N);

    ValueVector Fact(N + 1, 1), InvFact(N + 1, 1);

    for (valueType i = 1; i <= N; ++i) {
        Fact[i] = mul(Fact[i - 1], i);
        InvFact[i] = mul(InvFact[i - 1], Inv(i));
    }

    auto C = [&Fact, &InvFact](valueType n, valueType m) -> valueType {
        if (n < 0 || m < 0 || n < m)
            return 0;

        return mul(Fact[n], mul(InvFact[m], InvFact[n - m]));
    };

    LineSieve const sieve(V);

    ValueVector bucket(V + 1, 0);

    for (valueType i = 0; i < N; ++i) {
        valueType x;

        std::cin >> x;

        ++bucket[x];
    }

    ValueVector F(N + 1, 0), S(N + 1, 0);

    S[0] = 1;
    for (valueType i = 1; i < N; ++i)
        S[i] = sum(C(N - 1, i), S[i - 1]);

    for (valueType i = 1; i <= N; ++i) {
        F[i] = sub(S[N - 1], sum(S[i - 1], S[i - 2]));

        Inc(F[i], F[i - 1]);
    }

    valueType ans = 0;

    ValueVector const &P = sieve.Prime();

    for (auto const &iter: P) {
        ValueVector count(std::ceil(std::log(V) / std::log(iter) + 1), 0);
        ValueVector sum(std::ceil(std::log(V) / std::log(iter) + 1), 0);

        count[0] = N;

        for (valueType k = iter, c = 1; k <= V; k *= iter, ++c)
            for (valueType i = 1; i <= V / k; ++i)
                count[c] += bucket[i * k];

        for (valueType i = 0; i + 1 < count.size(); ++i)
            Inc(ans, mul(i, sub(F[count[i]], F[count[i + 1]])));
    }

    std::cout << ans << std::endl;
}