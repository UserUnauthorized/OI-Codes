//Luogu - P5170
#include <bits/stdc++.h>

typedef long long valueType;
typedef std::vector<valueType> ValueVector;

constexpr valueType MOD = 998244353;

class Inverse {
private:
    valueType size;

    ValueVector data;

public:
    explicit Inverse(valueType N) : size(N), data(N, 0) {
        data[1] = 1;

        for (valueType i = 2; i < N; ++i)
            data[i] = (long long) (MOD - MOD / i) * data[MOD % i] % MOD;
    }

    valueType operator()(valueType i) const {
        i %= MOD;

        if (i < size)
            return data[i];

        return (MOD - MOD / i) * operator()(MOD % i) % MOD;
    }
};

struct Result {
    valueType f, g, h;

    Result() : f(0), g(0), h(0) {};

    Result(valueType _f_, valueType _g_, valueType _h_) : f(_f_), g(_g_), h(_h_) {};
};

int main() {
    valueType T;

    std::cin >> T;

    Inverse Inv(10);

    typedef std::function<Result(valueType, valueType, valueType, valueType)> solveFunction;

    solveFunction solve = [&Inv, &solve](valueType a, valueType b, valueType c, valueType n) -> Result {
        auto const m = (valueType) (((__int128) a * n + b) / c);

        Result result;

        if (a == 0) {
            result.f = (n + 1) * (b / c) % MOD;

            result.g = n * (n + 1) % MOD * Inv(2) % MOD * (b / c) % MOD;

            result.h = (n + 1) * (b / c) % MOD * (b / c) % MOD;

            result.f = (result.f + MOD) % MOD;

            result.g = (result.g + MOD) % MOD;

            result.h = (result.h + MOD) % MOD;

            return result;
        }

        if (a >= c || b >= c) {
            auto const lastAns = solve(a % c, b % c, c, n);

            result.f = (lastAns.f + n * (n + 1) % MOD * Inv(2) % MOD * (a / c) % MOD + (n + 1) * (b / c) % MOD) % MOD;

            result.g = (lastAns.g + n * (n + 1) % MOD * (2 * n + 1) % MOD * Inv(6) % MOD * (a / c) % MOD +
                        n * (n + 1) % MOD * Inv(2) % MOD * (b / c) % MOD) % MOD;

            result.h =
                    (lastAns.h + n * (n + 1) % MOD * (2 * n + 1) % MOD * Inv(6) % MOD * (a / c) % MOD * (a / c) % MOD +
                     (n + 1) * (b / c) % MOD * (b / c) % MOD + n * (n + 1) % MOD * (a / c) % MOD * (b / c) % MOD +
                     2 * (a / c) * lastAns.g % MOD + 2 * (b / c) * lastAns.f % MOD) % MOD;

            result.f = (result.f + MOD) % MOD;

            result.g = (result.g + MOD) % MOD;

            result.h = (result.h + MOD) % MOD;

            return result;
        }

        auto const lastAns = solve(c, c - b - 1, a, m - 1);

        result.f = (n * m % MOD - lastAns.f) % MOD;

        result.g = (n * (n + 1) % MOD * m % MOD - lastAns.h - lastAns.f) % MOD * Inv(2) % MOD;

        result.h = (n * m % MOD * (m + 1) % MOD - 2 * lastAns.g - 2 * lastAns.f - result.f) % MOD;

        result.f = (result.f + MOD) % MOD;

        result.g = (result.g + MOD) % MOD;

        result.h = (result.h + MOD) % MOD;

        return result;
    };

    for (valueType i = 0; i < T; ++i) {
        valueType n, a, b, c;

        std::cin >> n >> a >> b >> c;

        auto const result = solve(a, b, c, n);

        std::cout << result.f << ' ' << result.h << ' ' << result.g << '\n';
    }

    std::cout << std::flush;

    return 0;
}