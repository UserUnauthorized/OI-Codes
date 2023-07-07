//HZ - 50.3
#include <bits/stdc++.h>

#ifdef CLION

#include<debug.h>

#else
#define debug(...)
#endif

typedef long long valueType;
typedef std::unordered_map<valueType, valueType> Memory;
typedef std::vector<Memory> MemoryVector;

constexpr valueType MOD = 1e9 + 7;
constexpr valueType maxN = 1e9 + 5;

class LineSieve {
public:
    typedef std::vector<valueType> container;
    typedef std::vector<bool> bitset;

private:
    valueType size;
    bitset isPrime;
    container Factor;
    container primeList;
    container phi;

public:
    explicit LineSieve(valueType _size_) : size(_size_), isPrime(size + 1, true), Factor(size + 1, 0),
                                           phi(size + 1, 0) {
        primeList.reserve((size_t) std::floor(std::log((long double) (_size_ + 1))));
        phi[1] = 1;
        for (valueType i = 2; i <= size; ++i) {
            if (isPrime[i]) {
                primeList.push_back(i);
                Factor[i] = i;
                phi[i] = i - 1;
            }

            bool flag = false;

            for (auto const &iter: primeList) {
                valueType const t = i * iter;

                if (t > size)
                    break;

                Factor[t] = iter;

                if (flag)
                    continue;

                isPrime[t] = false;

                if (__builtin_expect(i % iter == 0, false)) {
                    phi[t] = phi[i] * iter;

                    flag = true;
                } else {
                    phi[t] = phi[i] * (iter - 1);
                }
            }
        }
        typedef std::function<valueType(const valueType &, const valueType &)> ModPlus;

        ModPlus Op = [](const valueType &a, const valueType &b) -> valueType {
            return (a + b) % MOD;
        };

        std::partial_sum(phi.begin(), phi.end(), phi.begin(), Op);
    }

    valueType Phi(valueType n) const {
        if (n > size)
            throw std::range_error("Larger than Size.");

        if (n < 0)
            throw std::range_error("Too small.");

        return phi[n];
    }

    valueType maxFactor(valueType n) const {
        if (__builtin_expect(n > size, false))
            throw std::range_error("Larger than Size.");

        if (__builtin_expect(n < 0, false))
            throw std::range_error("Too small.");

        return Factor[n];
    }
};

class Sum {
public:
    typedef LineSieve sieve;
    typedef std::unordered_map<valueType, valueType> memory;

private:
    valueType size, preSize;
    sieve preWork;
    memory phiMemory;

public:
    explicit Sum(valueType _size_) : size(_size_),
                                     preSize(std::ceil(std::pow<long double>((long double) size, (long double) 2 / 3))),
                                     preWork(preSize + 5), phiMemory() {};

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

        ans = ans % MOD;

        return ans;
    }

    valueType maxFactor(valueType n) const {
        return preWork.maxFactor(n);
    }
};

int main() {
    valueType N, M;

    std::cin >> N >> M;

    Sum sum(maxN);

    typedef std::function<valueType(valueType, valueType)> solveFunction;

    if (N > M)
        std::swap(N, M);

    MemoryVector memory(N + 1);

    solveFunction F = [&sum, &memory, &F](valueType n, valueType m) -> valueType {
        if (memory[n].find(m) != memory[n].end())
            return memory[n][m];

        if (n == 0 || m == 0)
            return 0;

        if (n == 1 && m == 1)
            return 1;

        if (n == 1)
            return sum.Phi(m);

//        valueType &ans = memory[n][m];

//        if (m == 1)
//            return memory[n][m] = sum.Phi(n) - sum.Phi(n - 1);

        valueType const p = sum.maxFactor(n);

        if (n % (p * p) == 0) {
            memory[n][m] = F(n / p, m) * p % MOD;
        } else {
            memory[n][m] = (F(n / p, m) * (p - 1) + F(n, m / p)) % MOD;
        }

        return memory[n][m];
    };

    valueType result = 0;

    for (valueType i = 1; i <= N; ++i)
        result += F(i, M);

    result = (result % MOD + MOD) % MOD;

    std::cout << result << std::endl;

    return 0;
}