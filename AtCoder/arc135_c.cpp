#include <bits/stdc++.h>

typedef long long valueType;
typedef std::vector<valueType> ValueVector;

constexpr valueType MAXB = 31;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    valueType N;

    std::cin >> N;

    ValueVector A(N);

    for (auto &iter: A)
        std::cin >> iter;

    ValueVector B(MAXB, 0);

    for (auto const &iter: A) {
        for (valueType i = 0; i < MAXB; ++i) {
            if (iter & (1 << i))
                --B[i];
            else
                ++B[i];
        }
    }

    valueType const base = std::accumulate(A.begin(), A.end(), (valueType) 0);

    valueType ans = base;

    for (auto const &iter: A) {
        valueType sum = 0;

        for (valueType i = 0; i < MAXB; ++i)
            if (iter & (1 << i))
                sum += B[i] * (1 << i);

        ans = std::max(ans, base + sum);
    }

    std::cout << ans << std::endl;

    return 0;
}