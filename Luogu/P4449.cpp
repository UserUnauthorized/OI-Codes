//HZ - 48.6
//Luogu - P4449
#include <bits/stdc++.h>

typedef long long valueType;
constexpr valueType maxN = 5e6 + 5;
constexpr valueType MOD = 1e9 + 7;

class LineSieve {
public:
    typedef std::vector<valueType> container;

private:
    valueType size, K;
    container minFactorList;
    container primeList;
    container mobius, data;

private:
    static valueType pow(valueType a, valueType b) {
        valueType result = 1;

        while (b > 0) {
            if (b & 1)
                result = result * a % MOD;

            a = a * a % MOD;
            b = b >> 1;
        }

        return result;
    }

public:
    LineSieve(valueType _size_, valueType k) : size(_size_), K(k), minFactorList(_size_ + 1),
                                               mobius(_size_ + 1), data(_size_ + 1) {
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

        std::fill(data.begin(), data.end(), 0);

        for (valueType i = 1; i <= size; ++i) {
            valueType const t = pow(i, K);

            for (valueType j = 1; i * j <= size; ++j)
                data[i * j] = (data[i * j] + t * mobius[j]) % MOD;

            data[i] = (data[i] + MOD) % MOD;
        }

        std::partial_sum(data.begin(), data.end(), data.begin());
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
    valueType T, K;

    std::cin >> T >> K;

    LineSieve Euler(maxN, K);

    typedef std::function<valueType(valueType, valueType)> solveFunction;

    solveFunction solve = [&Euler](valueType N, valueType M) -> valueType {
        if (N > M)
            std::swap(N, M);

        __int128 result = 0;

        valueType l = 1, r;

        while (l <= N) {
            r = std::min(N / (N / l), M / (M / l));

            result = (result + (__int128) (Euler.Ans(r) - Euler.Ans(l - 1)) * (N / l) * (M / l) % MOD) % MOD;

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