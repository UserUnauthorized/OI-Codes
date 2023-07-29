//Luogu - SP20173
#include <bits/stdc++.h>

typedef unsigned long long valueType;
typedef std::vector<valueType> ValueVector;

valueType pow(valueType a, valueType b) {
    valueType result = 1;

    while (b > 0) {
        if (b & 1)
            result *= a;

        a *= a;
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
    valueType N, K, limit;

    Identity ID;

    valueType size, primeCount;
    container prime, primeSum, lpf;
    container F_prime;

    void sieve(valueType n) {
        prime.push_back(0);
        primeSum.push_back(0);

        for (valueType i = 2; i <= n; ++i) {
            if (lpf[i] == 0) {
                prime.emplace_back(i);
                primeSum.emplace_back(primeSum.back() + i);
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
        return n * (n + 1) / 2;
    }

public:
    Min_25(valueType n, valueType k) : N(n), K(k), limit(std::floor(std::sqrt((long double) N))), ID(n),
                                       size(ID.size()), primeCount(0), lpf(size + 1, 0), F_prime(size + 1, 0) {
        sieve(limit);

        for (valueType i = 1; i < size; ++i) {
            F_prime[i] = sum1(ID[i]) * (K + 1) - K;
        }

        //calc F_prime
        for (valueType i = 1; i <= primeCount; ++i) {
            valueType const p = prime[i];
            valueType const p2 = p * p;

            for (valueType j = 1; ID[j] >= p2; ++j) {
                valueType const id = ID(ID[j] / p);

                F_prime[j] -= (K + 1) * (F_prime[id] - (K + 1) * (primeSum[i - 1]) - 1);
            }
        }
    }

private:
    valueType F_p(valueType p, valueType c) const {
        return (c * K + 1);
    }

public:
    valueType F(valueType k, valueType n) {
        if ((k < prime.size() && n < prime[k]) || n <= 1)
            return 0;

        valueType const id = ID(n);

        valueType result = F_prime[id] - (K + 1) * primeSum[k - 1];

        for (valueType i = k; i <= primeCount && prime[i] * prime[i] <= n; ++i) {
            valueType const p = prime[i];

            for (valueType p1 = p, p2 = p * p, c = 1; p2 <= n; ++c, p1 *= p, p2 *= p)
                result += F_p(p, c) * F(i + 1, n / p1) + F_p(p, c + 1);
        }

        return result;
    }
};

int main() {
    valueType T;

    std::cin >> T;

    for (valueType i = 0; i < T; ++i) {
        valueType N, K;

        std::cin >> N >> K;

        Min_25 min_25(N, K);

        std::cout << (min_25.F(1, N) + 1) << '\n';
    }
}