//Luogu - P3383
#include <bits/stdc++.h>

class LineSieve {
public:
    typedef LineSieve self;
    typedef int valueType;
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

int main() {
    std::ios::sync_with_stdio(false);

    int n, q;

    std::cin >> n >> q;

    LineSieve euler(n);

    LineSieve::container const &prime = euler.getPrime();

    for (int i = 0; i < q; ++i) {
        int t;
        std::cin >> t;
        std::cout << prime[t - 1] << '\n';
    }

    std::cout << std::flush;

    return 0;
}