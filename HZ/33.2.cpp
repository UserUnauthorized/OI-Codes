//HZ - 33.2
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

typedef long long valueType;

constexpr valueType MOD = 10007;

class Inverse {
public:
    typedef Inverse self;
    typedef std::vector<valueType> container;

private:
    valueType size;
    valueType mod;
    container data;

public:
    Inverse(valueType _size_, valueType _mod_ = MOD) : size(_size_), mod(_mod_), data(_size_ + 1) {
        data[0] = 1;
        data[1] = 1;

        for (int i = 2; i <= size; ++i)
            data[i] = (long long) (mod - mod / i) * data[mod % i] % mod;
    }

    valueType operator[](valueType i) const {
        return data.at(i % mod);
    }
};

const Inverse Inv(MOD);

int main() {
    typedef std::function<valueType(valueType, valueType)> Function;

    std::vector<valueType> factorial(MOD + 1, 0);

    factorial[0] = 1;

    for (int i = 1; i <= MOD; ++i)
        factorial[i] = factorial[i - 1] * i % MOD;

    Function C = [&factorial](valueType n, valueType m) -> valueType {
        if (m == 0)
            return 1;

        return factorial[n] * Inv[factorial[m] * factorial[n - m] % MOD] % MOD;
    };

    Function Lucas = [&C, &Lucas](valueType n, valueType m) -> valueType {
        debug(n, m);

        if (m == 0)
            return 1;

        if (n >= MOD && m < MOD)
            return 0;

        return C(n % MOD, m % MOD) * Lucas(n / MOD, m / MOD) % MOD;
    };

    int T;

    std::cin >> T;

    for (int i = 1; i <= T; ++i) {
        int N, M;

        std::cin >> N >> M;

        std::cout << Lucas(N, M) << std::endl;
    }

    return 0;
}
