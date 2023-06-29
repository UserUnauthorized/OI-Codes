//Luogu - P1829
#include <bits/stdc++.h>

typedef long long valueType;
typedef std::vector<valueType> ValueVector;
constexpr valueType maxN = 1e7 + 5;
constexpr valueType MOD = 20101009;

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

class LineSieve {
public:
    typedef std::vector<valueType> container;

private:
    valueType size;
    container minFactorList;
    container primeList;
    container mobius, data;

public:
    explicit LineSieve(valueType _size_) : size(_size_), minFactorList(_size_ + 1), mobius(_size_ + 1),
                                           data(_size_ + 1) {
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

            data[i] = mobius[i] * i * i % MOD;
        }

        data[1] = 1;
        for (valueType i = 2; i <= size; ++i)
            data[i] = (data[i] + data[i - 1]) % MOD;
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
    Inverse Inv(10);
    LineSieve Euler(maxN);

    typedef std::function<valueType(valueType, valueType)> solveFunction;

    solveFunction calc = [&Inv](valueType N, valueType M) -> valueType {
        return N * (N + 1) % MOD * Inv(2) % MOD * M % MOD * (M + 1) % MOD * Inv(2) % MOD;
    };

    solveFunction Func = [&Euler, &calc](valueType N, valueType M) -> valueType {
        if (N > M)
            std::swap(N, M);

        __int128 result = 0;

        valueType l = 1, r;

        while (l <= N) {
            r = std::min(N / (N / l), M / (M / l));

            result = (result + (Euler.Ans(r) - Euler.Ans(l - 1)) * calc(N / l, M / l)) % MOD;

            l = r + 1;
        }

        return (valueType) ((result % MOD + MOD) % MOD);
    };

    solveFunction solve = [&calc, &Func](valueType N, valueType M) -> valueType {
        if (N > M)
            std::swap(N, M);

        __int128 result = 0;

        valueType l = 1, r;

        while (l <= N) {
            r = std::min(N / (N / l), M / (M / l));

            result = (result + ((calc(1, r) - calc(1, l - 1)) * Func(N / l, M / l)) % MOD) % MOD;

            l = r + 1;
        }

        return (valueType) ((result % MOD + MOD) % MOD);
    };


    valueType N, M;

    std::cin >> N >> M;

    std::cout << solve(N, M) << '\n';

    std::cout << std::flush;

    return 0;
}