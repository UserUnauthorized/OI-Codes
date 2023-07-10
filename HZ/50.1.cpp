//HZ - 50.1
//Luogu - P3172
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
    container primeList;
    container mobius;

public:
    explicit LineSieve(valueType _size_) : size(_size_), isPrime(_size_ + 1, true), mobius(_size_ + 1, 0){
        primeList.reserve((size_t) std::floor(std::log((long double) (_size_ + 1))));
        mobius[1] = 1;
        for (valueType i = 2; i <= size; ++i) {
            if (isPrime[i]) {
                primeList.push_back(i);
                mobius[i] = -1;
            }

            for (auto const &iter: primeList) {
                valueType const t = i * iter;

                if (t > size)
                    break;

                isPrime[t] = false;

                if (__builtin_expect(i % iter == 0, false)) {
                    mobius[t] = 0;

                    break;
                } else {
                    mobius[t] = -mobius[i];
                }
            }
        }

        std::partial_sum(mobius.begin(), mobius.end(), mobius.begin());
    }

    valueType Mobius(valueType n) const {
        if (n > size)
            throw std::range_error("Larger than Size.");

        if (n < 0)
            throw std::range_error("Too small.");

        return mobius[n];
    }
};

class Sum {
public:
    typedef LineSieve sieve;
    typedef std::unordered_map<valueType, valueType> memory;

private:
    valueType size, preSize;
    sieve preWork;
    memory mobiusMemory;

public:
    explicit Sum(valueType _size_) : size(_size_),
                                     preSize(std::ceil(std::pow<long double>((long double) size, (long double) 2 / 3))),
                                     preWork(preSize + 1) {};

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
};

int main() {
    valueType A, B, N, K;

    std::cin >> N >> K >> A >> B;

    valueType const L = (A - 1) / K, R = B / K;

    typedef std::function<valueType(const valueType &, const valueType &)> Calc;

    Calc pow = [](valueType a, valueType b) -> valueType {
        valueType result = 1;

        while(b > 0) {
            if(b & 1)
                result = result * a % MOD;

            a = a * a % MOD;

            b = b >> 1;
        }

        return result;
    };

    Sum sum(R);

    valueType result = 0;

    valueType  l = 1, r;

    while(l <= R) {
        r = L / l == 0 ? R / (R / l) : std::min( L / (L / l), R / (R / l));

        result = (result + (sum.Mobius(r) - sum.Mobius(l - 1)) * pow((R / l) - (L / l), N)) % MOD;

        l = r + 1;
    }

    result = (result + MOD) % MOD;

    std::cout << result << std::endl;
}