//HZ - 48.5
//Luogu - P3704
#include <bits/stdc++.h>

typedef long long valueType;
typedef std::vector<valueType> ValueVector;
constexpr valueType maxN = 1e6 + 5;
constexpr valueType MOD = 1e9 + 7;

class Inverse {
private:
    valueType size;

    ValueVector data;

public:
    explicit Inverse(valueType N) : size(N), data(N, 0) {
        data[1] = 1;

        for (valueType i = 2; i < N; ++i)
            data[i] = (long long) (MOD - MOD / i) * data[MOD % i] % MOD;
    }

    valueType operator()(valueType i) const {
        i %= MOD;

        if (i < size)
            return data[i];

        return (MOD - MOD / i) * operator()(MOD % i) % MOD;
    }
};

valueType pow(valueType a, valueType b) {
    valueType result = 1;

    while (b > 0) {
        if (b & 1)
            result = result * a % MOD;

        a = a * a % MOD;
        b = b >> 1;
    }

    return result;
}

class LineSieve {
public:
    typedef std::vector<valueType> container;

private:
    valueType size;
    container minFactorList;
    container primeList;
    container mobius, data, Fibonacci;
    const Inverse &Inv;

public:
    LineSieve(valueType _size_, const Inverse &inv) : size(_size_), minFactorList(_size_ + 1), mobius(_size_ + 1),
                                                      data(_size_ + 1), Fibonacci(_size_ + 1), Inv(inv) {
        primeList.reserve((size_t) std::floor(std::log((long double) (_size_ + 1))));
        mobius[1] = 1;
        for (valueType i = 2; i <= size; ++i) {
            if (minFactorList[i] == 0) {
                primeList.push_back(i);
                minFactorList[i] = i;
                mobius[i] = -1;
            }

            for (auto const &iter: primeList) {
                valueType const t = i * iter;

                if (t > size)
                    break;

                minFactorList[t] = iter;

                if (i % iter == 0) {
                    mobius[t] = 0;

                    break;
                } else {
                    mobius[t] = -mobius[i];
                }
            }
        }

        Fibonacci[1] = Fibonacci[2] = 1;

        for (int i = 3; i <= size; ++i)
            Fibonacci[i] = (Fibonacci[i - 1] + Fibonacci[i - 2]) % MOD;

        std::fill(data.begin(), data.end(), 1);
        for (valueType i = 1; i <= size; ++i) {
            valueType const inverse = Inv(Fibonacci[i]);
            valueType const value = Fibonacci[i];

            for (valueType j = 1; i * j <= size; ++j)
                if (mobius[j] == 1)
                    data[i * j] = data[i * j] * value % MOD;
                else if (mobius[j] == -1)
                    data[i * j] = data[i * j] * inverse % MOD;

            data[i] = data[i - 1] * data[i] % MOD;
        }
    }

    valueType Ans(valueType x) const {
        if (x > size)
            throw std::range_error("Larger than Size.");

        if (x < 0)
            throw std::range_error("Too small.");

        return data[x];
    }
};

int main() {
    valueType T;

    std::cin >> T;

    Inverse Inv(maxN);
    LineSieve Euler(maxN, Inv);

    typedef std::function<valueType(valueType, valueType)> solveFunction;

    solveFunction solve = [&Inv, &Euler](valueType N, valueType M) -> valueType {
        if (N > M)
            std::swap(N, M);

        __int128 result = 1;

        valueType l = 1, r;

        while (l <= N) {
            r = std::min(N / (N / l), M / (M / l));

            result = result * pow(Euler.Ans(r) * Inv(Euler.Ans(l - 1)) % MOD, (N / l) * (M / l) % (MOD - 1)) % MOD;

            l = r + 1;
        }

        return (valueType) (result % MOD);
    };

    for (int i = 1; i <= T; ++i) {
        valueType N, M;

        std::cin >> N >> M;

        std::cout << solve(N, M) << '\n';
    }

    std::cout << std::flush;

    return 0;
}