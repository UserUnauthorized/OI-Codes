//HZ - 50.5
//Luogu - P4213
#include <bits/stdc++.h>

typedef long long valueType;
typedef std::vector<valueType> ValueVector;

constexpr valueType maxN = (valueType) 1 << 31 | 5;

class LineSieve {
public:
    typedef std::vector<valueType> container;
    typedef std::vector<bool> bitset;

private:
    valueType size;
    bitset isPrime;
    container primeList;
    container mobius, phi;

public:
    explicit LineSieve(valueType _size_) : size(_size_), isPrime(_size_ + 1, true), mobius(_size_ + 1, 0),
                                           phi(_size_ + 1, 0) {
        primeList.reserve((size_t) std::floor(std::log((long double) (_size_ + 1))));
        mobius[1] = 1;
        phi[1] = 1;
        for (valueType i = 2; i <= size; ++i) {
            if (isPrime[i]) {
                primeList.push_back(i);
                mobius[i] = -1;
                phi[i] = i - 1;
            }

            for (auto const &iter: primeList) {
                valueType const t = i * iter;

                if (t > size)
                    break;

                isPrime[t] = false;

                if (__builtin_expect(i % iter == 0, false)) {
                    mobius[t] = 0;

                    phi[t] = phi[i] * iter;

                    break;
                } else {
                    mobius[t] = -mobius[i];

                    phi[t] = phi[i] * (iter - 1);
                }
            }
        }

        std::partial_sum(mobius.begin(), mobius.end(), mobius.begin());
        std::partial_sum(phi.begin(), phi.end(), phi.begin());
    }

    valueType Mobius(valueType n) const {
        if (n > size)
            throw std::range_error("Larger than Size.");

        if (n < 0)
            throw std::range_error("Too small.");

        return mobius[n];
    }

    valueType Phi(valueType n) const {
        if (n > size)
            throw std::range_error("Larger than Size.");

        if (n < 0)
            throw std::range_error("Too small.");

        return phi[n];
    }
};

class Sum {
public:
    typedef LineSieve sieve;
    typedef std::unordered_map<valueType, valueType> memory;

private:
    valueType size, preSize;
    sieve preWork;
    memory phiMemory, mobiusMemory;

public:
    explicit Sum(valueType _size_) : size(_size_),
                                     preSize(std::ceil(std::pow<long double>((long double) size, (long double) 2 / 3))),
                                     preWork(preSize + 1) {};

    valueType Phi(valueType n) {
        if (n <= preSize)
            return preWork.Phi(n);

        if (phiMemory.find(n) != phiMemory.end())
            return phiMemory[n];

        valueType &ans = phiMemory[n];
        ans = n * (n + 1) / 2;


        valueType l = 2, r;

        while (l <= n) {
            r = n / (n / l);

            ans -= (r - l + 1) * Phi(n / l);

            l = r + 1;
        }

        return ans;
    }

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
    valueType T;

    std::cin >> T;

    Sum sum(maxN);

    for (int i = 0; i < T; ++i) {
        valueType N;

        std::cin >> N;

        std::cout << sum.Phi(N) << ' ' << sum.Mobius(N) << '\n';
    }

    std::cout << std::flush;

    return 0;
}