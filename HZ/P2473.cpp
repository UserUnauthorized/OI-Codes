//HZ - 35.12
//Luogu - P2473
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
typedef unsigned int bitType;
typedef long double realType;
typedef std::vector<valueType> ValueVector;
typedef std::vector<bitType> BitVector;
typedef std::vector<realType> RealVector;
typedef std::vector<RealVector> RealMatrix;

constexpr realType INF = INFINITY;

int main() {
    int N, K;

    std::cin >> K >> N;

    bitType const S = 1 << N;

    ValueVector P(N + 1, 0);

    BitVector limit(N + 1, 0);

    for (int i = 1; i <= N; ++i) {
        std::cin >> P[i];

        int t;

        std::cin >> t;

        while (t != 0) {
            limit[i] |= 1 << (t - 1);

            std::cin >> t;
        }
    }

    std::function<bool(bitType, bitType)> check = [](bitType limit, bitType status) {
        return (~status & ~limit) == (~status);
    };

    RealMatrix dp(K + 2);

    for (int i = 1; i <= K + 1; ++i)
        dp[i].resize(S, 0);

    for (int i = K; i >= 1; --i) {
        for (bitType j = 0; j < S; ++j) {
            for (int k = 1; k <= N; ++k) {
                if (check(limit[k], j))
                    dp[i][j] += std::max(dp[i + 1][j], dp[i + 1][j | 1 << (k - 1)] + P[k]);
                else
                    dp[i][j] += dp[i + 1][j];
            }

            dp[i][j] /= N;
        }
    }

    std::cout << std::setprecision(6) << std::fixed << (dp[1][0]) << std::flush;

    return 0;
}
