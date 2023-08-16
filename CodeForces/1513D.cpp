//CodeForces - 1513D
#include <bits/stdc++.h>

typedef long long valueType;
typedef std::vector<valueType> ValueVector;
typedef std::pair<valueType, valueType> ValuePair;
typedef std::vector<ValuePair> PairVector;
typedef std::vector<bool> bitset;

int main() {
    valueType T;

    std::cin >> T;

    for (int testcase = 0; testcase < T; ++testcase) {
        valueType N, P;

        std::cin >> N >> P;

        ValueVector source(N);
        PairVector map(N);

        for (valueType i = 0; i < N; ++i) {
            std::cin >> source[i];

            map[i] = std::make_pair(source[i], i);
        }

        std::sort(map.begin(), map.end());

        bitset visited(N, false);

        valueType ans = 0, count = 0;

        for (auto const &value: map) {
            if (value.first >= P)
                break;

            valueType const index = value.second;

            if (visited[index])
                continue;

            visited[index] = true;

            valueType leftBound = index, rightBound = index;

            while (leftBound > 0 && source[leftBound - 1] % source[index] == 0) {
                --leftBound;

                if (visited[leftBound])
                    break;

                visited[leftBound] = true;
            }

            while (rightBound < N - 1 && source[rightBound + 1] % source[index] == 0) {
                ++rightBound;

                if (visited[rightBound])
                    break;

                visited[rightBound] = true;
            }

            count += rightBound - leftBound;

            ans += source[index] * (rightBound - leftBound);
        }

        ans += (N - 1 - count) * P;

        std::cout << ans << '\n';
    }

    std::cout << std::flush;

    return 0;
}