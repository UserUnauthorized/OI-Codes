//Luogu - P7486
#include <bits/stdc++.h>

typedef long long valueType;
typedef std::vector<valueType> ValueVector;

constexpr valueType MOD = 32465177;

template<typename T1, typename T2, typename T3 = valueType>
void Inc(T1 &a, T2 b, const T3 &mod = MOD) {
    a = a + b;

    if (a >= mod)
        a -= mod;
}

template<typename T1, typename T2, typename T3 = valueType>
void Dec(T1 &a, T2 b, const T3 &mod = MOD) {
    a = a - b;

    if (a < 0)
        a += mod;
}

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

class LineSieve {
public:
    typedef std::vector<valueType> container;
    typedef std::vector<bool> bitset;

private:
    valueType N;
    bitset isPrime;
    container primeList;
    container mobius, g, h, w;

public:
    explicit LineSieve(valueType _size_) : N(_size_), isPrime(N + 1, true), mobius(N + 1), g(N + 1, 0), h(N + 1, 1),
                                           w(N + 1, 1) {
        primeList.reserve((size_t) std::ceil(std::log((long double) (_size_ + 1))));
        mobius[1] = 1;
        for (valueType i = 2; i <= N; ++i) {
            if (isPrime[i]) {
                primeList.push_back(i);
                mobius[i] = -1;
            }

            for (auto const &iter: primeList) {
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
        }

        for (valueType i = 1; i <= N; ++i) {
            for (valueType j = i; j <= N; j += i) {
                Inc(g[j], mul(i, mobius[i] + (MOD - 1), MOD - 1), MOD - 1);
                Mul(h[j], pow(mul(i, j), mul(mobius[i] + (MOD - 1), i, MOD - 1), MOD));
            }

            Mul(g[i], i, MOD - 1);

            h[i] = pow(h[i], i);

            Mul(h[i], h[i - 1]);
            Inc(g[i], g[i - 1], MOD - 1);

            w[i] = pow(i, i);
            Mul(w[i], w[i - 1]);
        }
    }

    valueType G(valueType n) const {
        return g[n];
    }

    valueType H(valueType n) const {
        return h[n];
    }

    valueType W(valueType n) const {
        return w[n];
    }
};

class Inverse {
private:
    valueType size, mod;

    ValueVector data;

public:
    explicit Inverse(valueType N, valueType mod = MOD) : size(N), mod(mod), data(N + 1, 0) {
        data[1] = 1;

        for (valueType i = 2; i <= N; ++i)
            data[i] = mul((mod - mod / i), data[mod % i], mod);
    }

    valueType operator()(valueType i) const {
        i %= mod;

        if (i <= size)
            return data[i];

        return mul((mod - mod / i), operator()(mod % i), mod);
    }
};

constexpr valueType V = 1e6 + 5;

LineSieve sieve(V);
Inverse Inv(V, MOD);


valueType S(valueType n, valueType mod = MOD) {
    return (long long) n * (n + 1) / 2 % mod;
}

valueType G(valueType n, valueType m) {
    return mul(pow(sieve.W(n), S(m, MOD - 1)), pow(sieve.W(m), S(n, MOD - 1)));
}

valueType F(valueType n, valueType m) {
    if (n > m)
        std::swap(n, m);

    valueType result = 1;

    valueType l = 1, r;

    while (l <= n) {
        r = std::min(n / (n / l), m / (m / l));

        Mul(result, pow(G(n / l, m / l), sub(sieve.G(r), sieve.G(l - 1), MOD - 1)));

        Mul(result, pow(mul(sieve.H(r), Inv(sieve.H(l - 1))), mul(S(n / l, MOD - 1), S(m / l, MOD - 1), MOD - 1)));

        l = r + 1;
    }

    return result;
}

int main() {
    valueType T, N;

    std::cin >> T >> N;

    for (valueType i = 0; i < T; ++i) {
        valueType l, r;

        std::cin >> l >> r;

        valueType const result = mul(mul(F(l - 1, l - 1), F(r, r)), Inv(mul(F(l - 1, r), F(r, l - 1))));

        std::cout << result << std::endl;
    }

    return 0;
}