//Codeforces - 1575G
#include <bits/stdc++.h>

typedef long long valueType;
typedef std::vector<valueType> ValueVector;
typedef std::vector<ValueVector> ValueMatrix;
typedef std::vector<bool> bitset;

constexpr valueType MOD = 1e9 + 7;

template<typename T1, typename T2, typename T3 = valueType>
void Inc(T1 &a, T2 b, const T3 &mod = MOD) {
    a = a + b;

    if (a >= mod)
        a -= mod;
}

template<typename T1, typename T2, typename T3 = valueType>
T1 mul(T1 a, T2 b, const T3 &mod = MOD) {
    return (long long) a * b % MOD;
}

class LineSieve {
public:
    typedef std::vector<valueType> container;

private:
    valueType size;
    bitset isPrime;
    container primeList, phi;
    ValueMatrix fact;

public:
    explicit LineSieve(valueType _size_) : size(_size_), isPrime(_size_ + 1, true), phi(_size_ + 1), fact(_size_ + 1) {
        phi[1] = 1;

        for (valueType i = 2; i <= size; ++i) {
            if (isPrime[i]) {
                primeList.push_back(i);
                phi[i] = i - 1;
            }

            for (auto const &iter: primeList) {
                valueType const t = i * iter;

                if (t > size)
                    break;

                isPrime[t] = false;

                if (i % iter == 0) {
                    phi[t] = phi[i] * iter;

                    break;
                } else {
                    phi[t] = phi[i] * (iter - 1);
                }
            }
        }

        for (valueType i = 1; i <= size; ++i) {
            for (valueType j = i; j <= size; j += i) {
                fact[j].push_back(i);
            }
        }
    }

    const container &Prime() const {
        return primeList;
    }

    valueType Phi(valueType x) const {
        if (x > size)
            throw std::range_error("Larger than Size.");

        if (x < 1)
            throw std::range_error("Too small.");

        return phi[x];
    }

    const container &Factor(valueType x) const {
        if (x > size)
            throw std::range_error("Larger than Size.");

        if (x < 1)
            throw std::range_error("Too small.");

        return fact[x];
    }
};

constexpr valueType V = 1e5 + 5;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    LineSieve const sieve(V);

    valueType N;

    std::cin >> N;

    ValueVector source(N + 1, 0);

    for (valueType i = 1; i <= N; ++i)
        std::cin >> source[i];

    valueType ans = 0;
    ValueVector count(V, 0);

    for (valueType d = 1; d <= N; ++d) {
        for (valueType i = d; i <= N; i += d)
            for (auto const &iter: sieve.Factor(source[i]))
                ++count[iter];

        valueType sum = 0;

        for (valueType i = d; i <= N; i += d) {
            for (auto const &iter: sieve.Factor(source[i])) {
                if (count[iter] > 0) {
                    Inc(sum, mul(mul(count[iter], count[iter]), sieve.Phi(iter)));

                    count[iter] = 0;
                }
            }
        }

        Inc(ans, mul(sum, sieve.Phi(d)));
    }

    std::cout << ans << std::endl;


    return 0;
}