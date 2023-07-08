//HZ - 50.2
#include <bits/stdc++.h>

typedef long long valueType;

constexpr valueType MOD = 1e9 + 7;

class LineSieve {
public:
    typedef std::vector<valueType> container;
    typedef std::vector<bool> bitset;

private:
    valueType size;
    bitset isPrime;
    container Factor;
    container primeList;
    container data;

public:
    explicit LineSieve(valueType _size_) : size(_size_), isPrime(size + 1, true), Factor(size + 1, 0),
                                           data(size + 1, 0) {
        primeList.reserve((size_t) std::floor(std::log((long double) (_size_ + 1))));
        data[1] = 1;
        for (valueType i = 2; i <= size; ++i) {
            if (isPrime[i]) {
                primeList.push_back(i);
                Factor[i] = i;
                data[i] = i * (i - 1) % MOD;
            }

            for (auto const &iter: primeList) {
                valueType const t = i * iter;

                if (t > size)
                    break;

                isPrime[t] = false;

                if (__builtin_expect(i % iter == 0, false)) {
                    Factor[t] = Factor[i] * iter;

                    if (Factor[t] == t) {
                        data[t] = t * t / iter * (iter - 1) % MOD;
                    } else {
                        data[t] = data[i / Factor[i]] * data[Factor[t]] % MOD;
                    }
                } else {
                    Factor[t] = iter;

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

    valueType Data(valueType n) const {
        if (n > size)
            throw std::range_error("Larger than Size.");

        if (n < 0)
            throw std::range_error("Too small.");

        return data[n];
    }
};

class Sum {
public:
    typedef LineSieve sieve;
    typedef std::unordered_map<valueType, valueType> memory;

private:
    valueType size, preSize;
    sieve preWork;
    memory dataMemory;

public:
    explicit Sum(valueType _size_) : size(_size_),
                                     preSize(std::ceil(std::pow<long double>((long double) size, (long double) 2 / 3))),
                                     preWork(preSize + 5), dataMemory() {};

    valueType Data(valueType n) {
        if (n <= preSize)
            return preWork.Data(n);

        if (dataMemory.find(n) != dataMemory.end())
            return dataMemory[n];

        valueType &ans = dataMemory[n];

        ans = (valueType)((__int128) (n * 2 + 1) * (n + 1) * n / 6 % MOD);

        valueType l = 2, r;

        while (l <= n) {
            r = n / (n / l);

            ans -= ((r + 1) * r / 2 - (l - 1) * l / 2) % MOD * Data(n / l) % MOD;

            l = r + 1;
        }

        ans = (ans % MOD + MOD) % MOD;

        return ans;
    }
};

int main() {
    valueType N;

    std::cin >> N;

    Sum sum(N);

    std::cout << 1 << std::endl << sum.Data(N) << std::endl;

    return 0;
}