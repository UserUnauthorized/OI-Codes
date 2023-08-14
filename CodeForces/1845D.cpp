//CodeForces - 1845D
#include <bits/stdc++.h>

typedef long long valueType;
typedef std::vector<valueType> ValueVector;
typedef std::pair<valueType, valueType> ValuePair;

int main() {
    valueType T;

    std::cin >> T;

    for (int testcase = 0; testcase < T; ++testcase) {
        valueType N;

        std::cin >> N;

        ValueVector source(N);

        for (auto &iter: source)
            std::cin >> iter;

        std::partial_sum(source.begin(), source.end(), source.begin());

        ValuePair ans(0, 0);

        valueType maxSum = 0;

        for (auto const &iter: source) {
            ans = std::min(ans, std::make_pair(iter - maxSum, maxSum));

            maxSum = std::max(maxSum, iter);
        }

        std::cout << ans.second << '\n';
    }
}