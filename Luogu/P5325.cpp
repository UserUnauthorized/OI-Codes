//Luogu - P5325
#include <bits/stdc++.h>

typedef long long valueType;
typedef std::vector<valueType> ValueVector;

constexpr valueType MOD = 1e9 + 7;

template<typename T1, typename T2>
void Inc(T1 &a, const T2 &b) {
    a = a + b;

    if (a > MOD)
        a -= MOD;
}

template<typename T1, typename T2>
void Dec(T1 &a, const T2 &b) {
    a = a - b;

    if (a < 0)
        a += MOD;
}

template<typename T1, typename T2>
T1 sum(const T1 &a, const T2 &b) {
    return a + b >= MOD ? a + b - MOD : a + b;
}

template<typename T1, typename T2>
T1 sub(const T1 &a, const T2 &b) {
    return a - b < 0 ? a - b + MOD : a - b;
}

template<typename T1, typename T2>
T1 mul(const T1 &a, const T2 &b) {
    return (long long) (a % MOD) * (b % MOD) % MOD;
}

template<typename T1, typename T2>
void Mul(T1 &a, const T2 &b) {
    a = (long long) (a % MOD) * (b % MOD) % MOD;
}

template<typename T1, typename T2>
T1 pow(T1 a, T2 b) {
    T1 result = 1;

    while (b > 0) {
        if (b & 1)
            Mul(result, a);

        Mul(a, a);
        b = b >> 1;
    }

    return result;
}

class Identity {
public:
    typedef ValueVector container;

private:
    valueType N, limit;
    container less, great, data;

public:
    explicit Identity(valueType n) : N(n), limit(std::floor(std::sqrt((long double) N))), less(limit + 1, 0),
                                     great(limit + 1, 0), data(2 * limit + 1, 0) {
        valueType count = 0;

        for (valueType l = 1, r; l <= N; l = n / r + 1) {
            r = N / l;
            data[++count] = r;
            (r <= limit ? less[r] : great[N / r]) = count;
        }
    };

    valueType operator()(valueType n) const {
        return n <= limit ? less[n] : great[N / n];
    };

    valueType operator[](valueType n) const {
        return data[n];
    };

    valueType size() const {
        return (valueType) data.size() - 1;
    };
};

class Min_25 {
public:
    typedef ValueVector container;

private:
    valueType N, limit;

    Identity ID;

    valueType size, primeCount;
    container prime, primeSum, primeSum2, lpf;
    container G_0, G_k, F_prime;

    void sieve(valueType n) {
        prime.push_back(0);
        primeSum.push_back(0);
        primeSum2.push_back(0);

        for (valueType i = 2; i <= n; ++i) {
            if (lpf[i] == 0) {
                prime.emplace_back(i);
                primeSum.emplace_back(sum(primeSum.back(), i));
                primeSum2.emplace_back(sum(primeSum2.back(), mul(i, i)));
                lpf[i] = i;
            }

            for (auto iter = prime.begin() + 1; iter != prime.end(); ++iter) {
                if (*iter > lpf[i] || i * *iter > n)
                    break;

                lpf[i * *iter] = *iter;
            }
        }

        primeCount = (valueType) prime.size() - 1;
    }

    static valueType sum1(valueType n) {
        static valueType constexpr Inv2 = 500000004;

        return mul(mul(n, n + 1), Inv2);
    }

    static valueType sum2(valueType n) {
        static valueType constexpr Inv6 = 166666668;

        return mul(mul(n, n + 1), mul(2 * n + 1, Inv6));
    }

public:
    explicit Min_25(valueType n) : N(n), limit(std::floor(std::sqrt((long double) N))), ID(n), size(ID.size()),
                                   primeCount(0), lpf(size + 1, 0), G_0(size + 1, 0), G_k(size + 1, 0),
                                   F_prime(size + 1, 0) {
        sieve(limit);

        for (valueType i = 1; i < size; ++i) {
            G_0[i] = sum1(ID[i]);
            G_k[i] = sum2(ID[i]);
        }

        //calc F_prime
        for (valueType k = 1; k <= primeCount; ++k) {
            valueType const p = prime[k];
            valueType const p2 = p * p;

            for (valueType i = 1; ID[i] >= p2; ++i) {
                valueType const id = ID(ID[i] / p);

                Dec(G_0[i], mul(p, sub(G_0[id], primeSum[k - 1] + 1)));
                Dec(G_k[i], mul(mul(p, p), sub(G_k[id], primeSum2[k - 1] + 1)));
            }
        }

        for (valueType i = 1; i <= size; ++i)
            F_prime[i] = sub(G_k[i], G_0[i]);
    }

private:
    static valueType F_p(valueType n) {
        return mul(n, sub(n, 1));
    }

public:
    valueType F(valueType k, valueType n) {
        if ((k < prime.size() && n < prime[k]) || n <= 1)
            return 0;

        valueType const id = ID(n);

        valueType result = sub(F_prime[id], sub(primeSum2[k - 1], primeSum[k - 1]));

        for (valueType i = k; i <= primeCount && prime[i] * prime[i] <= n; ++i) {
            valueType const p = prime[i];

            for (valueType p1 = p, p2 = p * p; p2 <= n; p1 *= p, p2 *= p)
                Inc(result, sum(mul(F_p(p1), F(i + 1, n / p1)), F_p(p2)));
        }

        return result;
    }
};

int main() {
    valueType N;

    std::cin >> N;

    Min_25 min_25(N);

    std::cout << sum(min_25.F(1, N), 1) << std::endl;
}