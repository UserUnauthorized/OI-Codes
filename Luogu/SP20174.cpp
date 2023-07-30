//Luogu - SP20173
#include <bits/stdc++.h>

namespace DEBUG {
    template<typename T>
    inline void _debug(const char *format, T t) {
        std::cerr << format << '=' << t << std::endl;
    }

    template<class First, class... Rest>
    inline void _debug(const char *format, First first, Rest... rest) {
        while (*format != ',') std::cerr << *format++;
        std::cerr << '=' << first << ",";
        _debug(format + 1, rest...);
    }

    template<typename T>
    std::ostream &operator<<(std::ostream &os, const std::vector<T> &V) {
        os << "[ ";
        for (const auto &vv: V) os << vv << ", ";
        os << "]";
        return os;
    }

    std::ostream &operator<<(std::ostream &os, __int128 V) {
        if (V < 0) {
            os << '-';
            V = -V;
        }

        if (V > 9)
            os << V / 10;

        os << (int) (V % 10);

        return os;
    }

#define debug(...) _debug(#__VA_ARGS__, __VA_ARGS__)
}  // namespace DEBUG

using namespace DEBUG;
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
    container G, F_prime;

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

public:
    Min_25(valueType n, valueType k) : N(n), K(k), limit(std::floor(std::sqrt((long double) N))), ID(n),
                                       size(ID.size()), primeCount(0), lpf(size + 1, 0), G(size + 1, 0),
                                       F_prime(size + 1, 0) {
        sieve(limit);

        for (valueType i = 1; i < size; ++i) {
            G[i] = ID[i] - 1;
        }

        //calc F_prime
        for (valueType i = 1; i <= primeCount; ++i) {
            valueType const p = prime[i];
            valueType const p2 = p * p;

            for (valueType j = 1; ID[j] >= p2; ++j) {
                valueType const id = ID(ID[j] / p);

                G[j] -= (G[id] - (i - 1));
            }
        }

        for (valueType i = 1; i < size; ++i)
            F_prime[i] = G[i] * (K + 1);
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

        valueType result = F_prime[id] - (K + 1) * (k - 1);

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
        valueType N, K = 3;

        std::cin >> N;

        Min_25 min_25(N, K);

        std::cout << (min_25.F(1, N) + 1) << '\n';
    }
}