//HZ - 35.4
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

typedef double realType;
typedef size_t sizeType;

constexpr sizeType maxN = 5005;
constexpr realType empty = -INFINITY;

typedef std::vector<std::vector<realType>> Matrix;

Matrix memory;

realType ans(int Red, int Black);

int main() {
    int R, B;

    std::cin >> R >> B;

    memory.resize(R + 100);

    for (int i = 0; i <= R; ++i)
        memory[i].resize(B + 100, empty);

    realType result = ans(R, B);

    result = (realType) std::floor(result * 1e6) / 1e6;

    std::cout << std::setprecision(6) << std::fixed << result << std::flush;

    return 0;
}

realType ans(int i, int j) {
    if (memory[i][j] != empty)
        return memory[i][j];

    if (j == 0)
        return memory[i][j] = i;

    if (i == 0)
        return memory[i][j] = 0;

    memory[i][j] = realType(
            realType(i) * realType(ans(i - 1, j) + (realType) 1) + j * realType(ans(i, j - 1) - (realType) 1)) /
                   realType(i + j);

    memory[i][j] = std::max((realType) 0, memory[i][j]);

    return memory[i][j];
}
