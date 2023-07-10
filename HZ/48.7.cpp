//HZ - 48.7
#include <bits/stdc++.h>

typedef long long valueType;
typedef std::vector<valueType> ValueVector;
constexpr valueType maxN = 1e7 + 5;
constexpr valueType MOD = 1e8 + 9;

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
    typedef std::vector<bool> bitset;

private:
    valueType size;
    bitset isPrime;
    container primeList;
    container data;

public:
    explicit LineSieve(valueType _size_) : size(_size_), isPrime(_size_ + 1, true),data(_size_ + 1) {
        primeList.reserve((size_t) std::floor(std::log((long double) (_size_ + 1))));
        data[1] = 1;
        for (valueType i = 2; i <= size; ++i) {
            if (isPrime[i]) {
                primeList.push_back(i);
                data[i] = (i - i * i) % MOD + MOD;
            }

            for (auto const &iter: primeList) {
                valueType const t = i * iter;

                if (t > size)
                    break;

                isPrime[t] = false;

                if (i % iter == 0) {
                    data[t] = data[i] * iter % MOD;

                    break;
                } else {
                    data[t] = data[i] * data[iter] % MOD;
                }
            }
        }

        typedef std::function<valueType(const valueType &, const valueType &)> ModPlus;

        ModPlus Op = [](const valueType &a, const valueType &b) -> valueType {
            return (a + b) % MOD;
        };

        std::partial_sum(data.begin(), data.end(), data.begin(), Op);
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

    Inverse Inv(10);
    LineSieve Euler(maxN);

    typedef std::function<valueType(valueType, valueType)> solveFunction;

    solveFunction calc = [&Inv](valueType N, valueType M) -> valueType {
        return (valueType)((__int128)N * (N + 1) * Inv(2) * M % MOD * (M + 1) * Inv(2) % MOD);
    };

    solveFunction solve = [&Euler, &calc](valueType N, valueType M) -> valueType {
        if (N > M)
            std::swap(N, M);

        __int128 result = 0;

        valueType l = 1, r;

        while (l <= N) {
            r = std::min(N / (N / l), M / (M / l));

            result = (result + (Euler.Ans(r) - Euler.Ans(l - 1)) * calc(N / l, M / l)) % MOD;

            l = r + 1;
        }

        return (valueType) ((result % MOD) + MOD) % MOD;
    };

    for (int i = 1; i <= T; ++i) {
        valueType N, M;

        std::cin >> N >> M;

        std::cout << solve(N, M) << '\n';
    }

    std::cout << std::flush;

    return 0;
}