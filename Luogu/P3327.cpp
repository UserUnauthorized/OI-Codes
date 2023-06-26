//HZ - 48.4
//Luogu - P3327
#include <bits/stdc++.h>

typedef long long valueType;
constexpr valueType maxN = 5e4 + 5;

class LineSieve {
public:
    typedef long long valueType;
    typedef std::vector<valueType> container;

private:
    valueType size;
    container minFactorList;
    container primeList;
    container mobius, minCount, data;

public:
    explicit LineSieve(valueType _size_) : size(_size_), minFactorList(_size_ + 1), mobius(_size_ + 1),
                                           minCount(_size_ + 1), data(_size_ + 1) {
        primeList.reserve((size_t) std::floor(std::log((long double) (_size_ + 1))));
        data[1] = 1;
        mobius[1] = 1;
        for (valueType i = 2; i <= size; ++i) {
            if (minFactorList[i] == 0) {
                primeList.push_back(i);
                minFactorList[i] = i;
                minCount[i] = 1;
                mobius[i] = -1;
                data[i] = 2;
            }

            for (auto const &iter: primeList) {
                valueType const t = i * iter;

                if (t > size)
                    break;

                minFactorList[t] = iter;

                if (i % iter == 0) {
                    mobius[t] = 0;

                    minCount[t] = minCount[i] + 1;

                    data[t] = data[i] / (minCount[i] + 1) * (minCount[t] + 1);

                    break;
                } else {
                    mobius[t] = -mobius[i];

                    minCount[t] = 1;

                    data[t] = data[i] * 2;
                }
            }
        }

        std::partial_sum(data.begin(), data.end(), data.begin());
        std::partial_sum(mobius.begin(), mobius.end(), mobius.begin());
    }

    valueType mu(valueType x) const {
        if (x > size)
            throw std::range_error("Larger than Size.");

        if (x < 0)
            throw std::range_error("Too small.");

        return mobius[x];
    }

    valueType S(valueType x) const {
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

    LineSieve Euler(maxN);

    typedef std::function<valueType(valueType, valueType)> solveFunction;

    solveFunction solve = [&Euler](valueType N, valueType M) -> valueType {
        if (N > M)
            std::swap(N, M);

        valueType result = 0;

        valueType l = 1, r;

        while (l <= N) {
            r = std::min(N / (N / l), M / (M / l));

            result += (Euler.mu(r) - Euler.mu(l - 1)) * Euler.S(N / l) * Euler.S(M / l);

            l = r + 1;
        }

        return result;
    };

    for (int i = 1; i <= T; ++i) {
        valueType N, M;

        std::cin >> N >> M;

        std::cout << solve(N, M) << '\n';
    }

    std::cout << std::flush;

    return 0;
}