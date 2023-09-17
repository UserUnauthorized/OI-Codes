#include <bits/stdc++.h>

typedef long long valueType;
typedef std::vector<valueType> ValueVector;

constexpr valueType V = 10000;

int main() {
    valueType N;

    std::cin >> N;

    ValueVector ans;

    ans.reserve(N);

    ans.push_back(2 * 3);
    ans.push_back(2 * 5);
    ans.push_back(3 * 5);

    for (valueType i = 12; i <= V; i += 6)
        if (i % 5 == 0)
            continue;
        else
            ans.push_back(i);

    for (valueType i = 20; i <= V; i += 10)
        if (i % 3 == 0)
            continue;
        else
            ans.push_back(i);

    for (valueType i = 30; i <= V; i += 15)
        if (i % 2 == 0)
            continue;
        else
            ans.push_back(i);

    for (auto const &iter: ans)
        std::cout << iter << ' ';

    std::cout << std::endl;

    return 0;
}