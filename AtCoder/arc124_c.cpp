#include <bits/stdc++.h>

typedef long long valueType;
typedef std::vector<valueType> ValueVector;
typedef std::pair<valueType, valueType> ValuePair;
typedef std::vector<ValuePair> PairVector;

valueType lcm(valueType a, valueType b) {
    return a / std::__gcd(a, b) * b;
}

ValueVector divisor(valueType n) {
    ValueVector result;

    for (valueType i = 1; i * i <= n; ++i) {
        if (n % i == 0) {
            result.push_back(i);

            if (i * i != n)
                result.push_back(n / i);
        }
    }

    std::sort(result.begin(), result.end());

    return result;
}

bool check(valueType a, valueType b, PairVector const &data) {
    return std::all_of(data.begin(), data.end(), [a, b](ValuePair const &iter) {
        return (iter.first % a == 0 && iter.second % b == 0) || (iter.second % a == 0 && iter.first % b == 0);
    });
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    valueType N;

    std::cin >> N;

    PairVector data(N);

    for (auto &iter: data)
        std::cin >> iter.first >> iter.second;

    ValueVector const A = divisor(data[0].first), B = divisor(data[0].second);

    valueType ans = 0;

    for (auto const &a: A)
        for (auto const &b: B)
            if (check(a, b, data))
                ans = std::max(ans, lcm(a, b));

    std::cout << ans << std::endl;

    return 0;
}