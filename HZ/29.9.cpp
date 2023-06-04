//HZ - 29.9
//Luogu - P2155;
#include<bits/stdc++.h>

namespace DEBUG {
    template<typename T>
    inline void _debug(const char *format, T t) {
        std::cerr << format << '=' << t << std::endl;
    }

    template<class First, class... Rest>
    inline void _debug(const char *format, First first, Rest... rest) {
        while (*format != ',') std::cerr << *format++;
        std::cerr << '=' << first << ",";
        _debug(format + 1, rest...);
    }

    template<typename T>
    std::ostream &operator<<(std::ostream &os, const std::vector<T> &V) {
        os << "[ ";
        for (const auto &vv: V) os << vv << ", ";
        os << "]";
        return os;
    }

    std::ostream &operator<<(std::ostream &os, __int128 V) {
        if (V < 0) {
            os << '-';
            V = -V;
        }

        if (V > 9)
            os << V / 10;

        os << (int) (V % 10);

        return os;
    }

#define debug(...) _debug(#__VA_ARGS__, __VA_ARGS__)
}  // namespace DEBUG

using namespace DEBUG;

typedef int valueType;

constexpr valueType maxN = 1e7 + 3;
valueType MOD_;
valueType const &MOD = MOD_;

class LineSieve {
public:
    typedef LineSieve self;
    typedef std::vector<valueType> container;
    typedef std::vector<bool> bitset;

private:
    valueType size;
    bitset isPrime;

public:
    explicit LineSieve(valueType _size_) : size(_size_), isPrime(_size_ + 1, true) {
        container primeList;

        for (valueType i = 2; i <= size; ++i) {
            if (isPrime[i])
                primeList.push_back(i);

            for (auto const &iter: primeList) {
                valueType const t = i * iter;

                if (t > size)
                    break;

                isPrime[t] = false;

                if (i % iter == 0)
                    break;
            }
        }
    }

    bool check(valueType x) const {
        return isPrime[x];
    }
};

class Inverse {
public:
    typedef Inverse self;
    typedef std::vector<valueType> container;

private:
    valueType size;
    valueType mod;
    container data;

public:
    Inverse(valueType _size_, valueType _mod_) : size(_size_), mod(_mod_), data(_size_ + 1) {
        data[0] = 1;
        data[1] = 1;

        for (int i = 2; i <= size; ++i)
            data[i] = (long long) (mod - mod / i) * data[mod % i] % mod;
    }

    valueType operator[](valueType i) const {
        return data.at(i % mod);
    }
};

int main() {
    int T;

    std::cin >> T >> MOD_;

    Inverse inv(std::min(MOD, maxN + 3), MOD);
    LineSieve Euler(maxN + 3);

    typedef std::vector<valueType> Vector;

    Vector factorial(maxN, 1), prime(maxN, 1);

    for (int i = 2; i < maxN; ++i) {
        if (i == MOD) {
            factorial[i] = factorial[i - 1];
            prime[i] = (long long) prime[i - 1] * (MOD - 1) % MOD;
            continue;
        }

        factorial[i] = (long long) i * factorial[i - 1] % MOD;

        if (Euler.check(i))
            prime[i] = (__int128) prime[i - 1] * inv[i] * (i - 1) % MOD;
        else
            prime[i] = prime[i - 1];
    }

    for (int i = 1; i <= T; ++i) {
        valueType n, m;

        std::cin >> n >> m;

        valueType const result = (long long) factorial[n] * prime[m] % MOD;

        if (n >= MOD && m < MOD)
            std::cout << 0 << std::endl;
        else
            std::cout << result << std::endl;
    }

    return 0;
}
