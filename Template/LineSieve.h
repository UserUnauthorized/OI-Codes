#ifndef OI_CODES_LINESIEVE_H
#define OI_CODES_LINESIEVE_H

#include <vector>
#include <exception>
#include <stdexcept>

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
            if (minFactorList[i] == 0) {
                primeList.push_back(i);
                minFactorList[i] = i;
            }

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

        return minFactorList[x] == x;
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

#endif //OI_CODES_LINESIEVE_H
