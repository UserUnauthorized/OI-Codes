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

    for(valueType i = 16; i <= V && ans.size() < N; ++i)
        if(i % 6 == 0 || i % 10 == 0 || i % 15 == 0)
            ans.push_back(i);

    for (auto const &iter: ans)
        std::cout << iter << ' ';

    std::cout << std::endl;

    return 0;
}