//HZ - 50.4
#include <bits/stdc++.h>

typedef long long valueType;

constexpr valueType MOD = 1e9 + 7;
constexpr valueType maxN = 1e9 + 5;

class LineSieve {
public:
    typedef std::vector<valueType> container;
    typedef std::vector<bool> bitset;

private:
    valueType size;
    bitset isPrime;
    container primeList, minFactor;
    container mobius, Func;

public:
    explicit LineSieve(valueType _size_) : size(_size_), isPrime(size + 1, true), minFactor(size + 1, 0),
                                           mobius(size + 1, 0), Func(size, 0) {
        primeList.reserve((size_t) std::floor(std::log((long double) (_size_ + 1))));
        minFactor[1] = 1;
        mobius[1] = 1;
        Func[1] = 1;
        for (valueType i = 2; i <= size; ++i) {
            if (isPrime[i]) {
                primeList.push_back(i);
                minFactor[i] = i;
                mobius[i] = -1;
                Func[i] = 2;
            }

            for (auto const &iter: primeList) {
                valueType const t = i * iter;

                if (t > size)
                    break;

                isPrime[t] = false;

                if (__builtin_expect(i % iter == 0, false)) {
                    mobius[t] = 0;

                    minFactor[t] = minFactor[i] * iter;

                    if (minFactor[t] == t) {
                        Func[t] = Func[i] + 1;
                    } else {
                        Func[t] = Func[i / minFactor[i]] * Func[minFactor[t]] % MOD;
                    }

                    break;
                } else {
                    mobius[t] = -mobius[i];

                    minFactor[t] = iter;

                    Func[t] = Func[i] * 2 % MOD;
                }
            }
        }

        std::partial_sum(mobius.begin(), mobius.end(), mobius.begin());

        typedef std::function<valueType(const valueType &, const valueType &)> ModPlus;

        ModPlus Op = [](const valueType &a, const valueType &b) -> valueType {
            return (a + b) % MOD;
        };

        std::partial_sum(Func.begin(), Func.end(), Func.begin(), Op);

        typedef std::function<void(valueType &)> CheckFunc;

        CheckFunc check = [](valueType &value) -> void {
            if (value < 0)
                value = value + MOD;
        };

        std::for_each(Func.begin(), Func.end(), check);
    }

    valueType Mobius(valueType n) const {
        if (n > size)
            throw std::range_error("Larger than Size.");

        if (n < 0)
            throw std::range_error("Too small.");

        return mobius[n];
    }

    valueType F(valueType n) const {
        if (n > size)
            throw std::range_error("Larger than Size.");

        if (n < 0)
            throw std::range_error("Too small.");

        return Func[n];
    }
};

class Sum {
public:
    typedef LineSieve sieve;
    typedef std::unordered_map<valueType, valueType> memory;

private:
    valueType size, preSize;
    sieve preWork;
    memory phiMemory, mobiusMemory, funcMemory;

public:
    explicit Sum(valueType _size_) : size(_size_),
                                     preSize(std::ceil(std::pow<long double>((long double) size, (long double) 2 / 3))),
                                     preWork(preSize + 5), phiMemory(), mobiusMemory(), funcMemory() {};

    valueType Mobius(valueType n) {
        if (n <= preSize)
            return preWork.Mobius(n);

        if (mobiusMemory.find(n) != mobiusMemory.end())
            return mobiusMemory[n];

        valueType &ans = mobiusMemory[n];
        ans = 1;

        valueType l = 2, r;

        while (l <= n) {
            r = n / (n / l);

            ans -= (r - l + 1) * Mobius(n / l);

            l = r + 1;
        }

        return ans;
    }

    valueType F(valueType n) {
        if (n <= preSize)
            return preWork.F(n);

        if (funcMemory.find(n) != funcMemory.end())
            return funcMemory[n];

        valueType &ans = funcMemory[n];
        ans = n;

        valueType l = 2, r;

        while (l <= n) {
            r = n / (n / l);

            ans -= (Mobius(r) - Mobius(l - 1)) * F(n / l) % MOD;

            l = r + 1;
        }

        ans = (ans % MOD + MOD) % MOD;

        return ans;
    }
};

int main() {
    valueType N;

    std::cin >> N;

    Sum sum(maxN);

    sum.Mobius(N);
    sum.F(N);

    valueType result = 0;

    valueType l = 1, r;

    while (l <= N) {
        r = N / (N / l);

        result = (result + ((sum.Mobius(r) - sum.Mobius(l - 1)) * sum.F(N / l) % MOD * sum.F(N / l))) % MOD;

        l = r + 1;
    }

    result = (result % MOD + MOD) % MOD;

    std::cout << result << std::endl;

    return 0;
}