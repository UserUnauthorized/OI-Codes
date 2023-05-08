//Luogu - P9118
#include <bits/stdc++.h>

class LineSieve {
public:
    typedef LineSieve self;
    typedef long long valueType;
    typedef std::vector<valueType> container;

private:
    valueType size;
    container minFactorList;
    container primeList;

public:
    explicit LineSieve(valueType _size_) : size(_size_), minFactorList(_size_ + 1) {
        for (valueType i = 2; i <= size; ++i) {
            if (minFactorList[i] == 0)
                primeList.push_back(i);

            for (auto const &iter: primeList) {
                valueType const t = i * iter;

                if (t > size)
                    break;

                minFactorList[t] = iter;

                if (i % iter == 0)
                    break;
            }
        }
    }

    valueType minFactor(valueType x) const {
        if (x > size)
            throw std::range_error("Larger than Size.");

        if (x < 1)
            throw std::range_error("Too small.");

        return minFactorList[x];
    }

    bool isPrime(valueType x) const {
        if (x > size)
            throw std::range_error("Larger than Size.");

        if (x < 1)
            throw std::range_error("Too small.");

        return minFactorList[x] == 0;
    }

    valueType maxFactor(valueType x) const {
        if (x > size)
            throw std::range_error("Larger than Size.");

        if (x < 1)
            throw std::range_error("Too small.");

        return isPrime(x) ? x : x / minFactorList[x];
    }

    const container &getPrime() const {
        return primeList;
    }
};

typedef long long valueType;
constexpr valueType maxS = 80;
constexpr long double eps = 1e-9;

valueType log(valueType x, valueType y); 

int main() {
    int n, k;

    std::cin >> n >> k;

    if (k == 1) {
        std::cout << n << std::flush;
        return 0;
    }

    int const s = std::ceil(std::log2(n));

    LineSieve euler(s);

    valueType ans = 1;

    for(int i = std::max(k, 2); i <= s; ++i) {
        if (!euler.isPrime(i) && euler.maxFactor(i) >= k)
            continue;
//        std::cerr << i << '\t' << log(i, n) - 1 << std::endl;
        ans += std::floor(std::pow<long double>((long double)n, (long double)1 / (long double)i + eps)) - 1;
    }

    std::cout << ans << std::flush;

    return 0;
}

valueType log(valueType x, valueType y) {
	valueType result = 0, base = x;
	
	while(base <= y) {
		++result;
		base *= x;
	}
	
	return result;
}
