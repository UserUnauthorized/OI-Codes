//HZ - 48.1
//Luogu - P2257
#include <bits/stdc++.h>

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

#define debug(...) _debug(#__VA_ARGS__, __VA_ARGS__)
}  // namespace DEBUG

using namespace DEBUG;

typedef long long valueType;
constexpr valueType maxN = 1e7 + 5;

class LineSieve {
public:
    typedef long long valueType;
    typedef std::vector<valueType> container;

private:
    valueType size;
    container minFactorList;
    container primeList;
    container mobius, data, sum;

public:
    explicit LineSieve(valueType _size_) : size(_size_), minFactorList(_size_ + 1), mobius(_size_ + 1, 0),
                                           data(_size_ + 1), sum(_size_ + 1) {
        primeList.reserve((size_t) std::floor(std::log((long double) (_size_ + 1))));
        mobius[1] = 1;

        for (valueType i = 2; i <= size; ++i) {
            if (minFactorList[i] == 0) {
                primeList.push_back(i);
                minFactorList[i] = i;
                mobius[i] = -1;
                data[i] = 1;
            }

            for (auto const &iter: primeList) {
                valueType const t = i * iter;

                if (t > size)
                    break;

                minFactorList[t] = iter;

                if (i % iter == 0) {
                    mobius[t] = 0;
                    data[t] = mobius[i];
                    break;
                }

                mobius[t] = -mobius[i];
                data[t] = -data[i] + mobius[i];
            }
        }

//        for (auto const &i: primeList)
//            for(valueType j = 1; i * j <= size; ++j)
//                data[i * j] += mobius[j];

        std::partial_sum(data.begin(), data.end(), sum.begin());
    }

    valueType ans(valueType x) const {
        if (x > size)
            throw std::range_error("Larger than Size.");

        if (x < 0)
            throw std::range_error("Too small.");

        return sum[x];
    }
};

int main() {
    valueType T;

    std::cin >> T;

    LineSieve Euler(maxN);

    typedef std::function<valueType(valueType, valueType)> solveFunction;

    solveFunction solve = [&Euler](valueType N, valueType M) -> valueType {
        if (N > M)
            std::swap(N, M);

        valueType result = 0;

        valueType l = 1, r;

        while (l <= N) {
            r = std::min(N / (N / l), M / (M / l));

            result += (Euler.ans(r) - Euler.ans(l - 1)) * (N / l) * (M / l);

            l = r + 1;
        }

        return result;
    };

    for (int i = 1; i <= T; ++i) {
        valueType N, M;

        std::cin >> N >> M;

        std::cout << solve(N, M) << '\n';
    }

    std::cout << std::flush;

    return 0;
}