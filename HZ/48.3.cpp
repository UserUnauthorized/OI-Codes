//HZ - 48.3
#include <bits/stdc++.h>

typedef long long valueType;
constexpr valueType maxN = 1e7 + 5;

class LineSieve {
public:
    typedef long long valueType;
    typedef std::vector<valueType> container;

private:
    valueType size;
    container minFactorList;
    container primeList;
    container preCount, nowCount, factorCount, data, sum;

public:
    explicit LineSieve(valueType _size_) : size(_size_), minFactorList(_size_ + 1), preCount(_size_ + 1, 0),
                                           nowCount(_size_ + 1, 0), factorCount(_size_ + 1), data(_size_ + 1),
                                           sum(_size_ + 1) {
        primeList.reserve((size_t) std::floor(std::log((long double) (_size_ + 1))));

        for (valueType i = 2; i <= size; ++i) {
            if (minFactorList[i] == 0) {
                primeList.push_back(i);
                minFactorList[i] = i;
                nowCount[i] = 1;
                preCount[i] = 0;
                factorCount[i] = 1;
                data[i] = 1;
            }

            for (auto const &iter: primeList) {
                valueType const t = i * iter;

                if (t > size)
                    break;

                minFactorList[t] = iter;

                if (i % iter == 0) {
                    nowCount[t] = nowCount[i] + 1;
                    preCount[t] = preCount[i];
                    factorCount[t] = factorCount[i];

                    break;
                } else {
                    nowCount[t] = 1;
                    preCount[t] = (nowCount[i] == preCount[i] || preCount[i] == 0) ? nowCount[i] : -1;
                    factorCount[t] = factorCount[i] + 1;
                }
            }
        }

        for (int i = 2; i <= size; ++i)
            if (nowCount[i] == preCount[i] || preCount[i] == 0)
                data[i] = (factorCount[i] & 1) == 1 ? 1 : -1;
            else
                data[i] = 0;

        std::partial_sum(data.begin(), data.end(), sum.begin());
    }

    valueType ans(valueType x) const {
        if (x > size)
            throw std::range_error("Larger than Size.");

        if (x < 0)
            throw std::range_error("Too small.");

        return sum[x];
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

            result += (Euler.ans(r) - Euler.ans(l - 1)) * (N / l) * (M / l);

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