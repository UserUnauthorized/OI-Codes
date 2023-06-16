//HZ - 35.5
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
typedef std::vector<realType> RealVector;
typedef std::vector<RealVector> RealMatrix;
typedef std::vector<RealMatrix> DPMatrix;


int main() {
    int N, L, K;

    std::cin >> N >> L >> K;

    int const M = N << 1 | 1, shifting = N;

    ValueVector A(N + 1, 0);
    RealVector P(N + 1, 0);

    for (int i = 1; i <= N; ++i)
        std::cin >> P[i];

    for (int i = 1; i <= N; ++i)
        std::cin >> A[i];

    for (int i = 1; i <= N; ++i)
        P[i] = (realType) P[i] / 100;

//	debug(P);

    std::array<RealMatrix, 2> dp;

    dp[0].resize(N + 1);
    dp[1].resize(N + 1);

    for (int i = 0; i <= N; ++i) {
        dp[0][i].resize(M + 1, 0);
        dp[1][i].resize(M + 1, 0);
    }

    K = std::min(K + shifting, M);

    dp[0][0][K] = 1;

    for (int i = 0; i < N; ++i) {
        int const now = i & 1, next = now ^ 1;

        for (int j = 0; j <= N; ++j)
            std::fill(dp[next][j].begin(), dp[next][j].end(), 0);

        for (int j = 0; j <= i; ++j) {
            for (int k = 0; k <= M; ++k) {
                if (dp[now][j][k] == 0)
                    continue;

                dp[next][j + 1][std::min(k + A[i + 1], M)] += dp[now][j][k] * P[i + 1];
                dp[next][j][k] += dp[now][j][k] * (1 - P[i + 1]);
            }
        }
    }

    int const final = N & 1;

    realType result = 0;

    for (int i = L; i <= N; ++i)
        for (int j = shifting; j <= M; ++j)
            result += dp[final][i][j];

    std::cout << std::setprecision(6) << std::fixed << result << std::flush;

    return 0;
}
