//Codeforces - 1834E
#include <bits/stdc++.h>

typedef long long valueType;
typedef std::set<valueType> ValueSet;
typedef std::vector<valueType> ValueVector;

constexpr valueType limit = 5e6;

valueType lcm(valueType a, valueType b) {
    valueType const result = a / std::__gcd(a, b) * b;

    return result < limit ? result : limit;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    valueType T;

    std::cin >> T;

    for (valueType testcase = 0; testcase < T; ++testcase) {
        valueType N;

        std::cin >> N;

        ValueSet set, total;

        ValueVector source(N);

        for (valueType i = 0; i < N; ++i) {
            std::cin >> source[i];

            ValueSet newSet;

            newSet.insert(source[i]);
            total.insert(source[i]);

            for (auto const &iter: set) {
                total.insert(lcm(iter, source[i]));
                newSet.insert(lcm(iter, source[i]));
            }

            set.swap(newSet);
        }

        valueType ans = 1;

        for (auto iter = total.begin(); iter != total.end() && *iter == ans; ++iter, ++ans) {
            if (*iter != ans)
                break;
        }

        std::cout << ans << '\n';
    }

    std::cout << std::flush;

    return 0;
}