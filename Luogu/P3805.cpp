//Luogu - P3805
#include <bits/stdc++.h>

typedef int valueType;
typedef std::vector<valueType> ValueVector;
typedef std::pair<ValueVector, ValueVector> VectorPair;

VectorPair manacher(const std::string &data) {
    valueType const size = data.size();

    ValueVector odd(size, 0), even(size, 0);

    for (valueType i = 0, l = 0, r = -1; i < size; ++i) {
        valueType k = (i > r) ? 1 : std::min(odd[l + r - i], r - i + 1);

        while (i - k >= 0 && i + k < size && data[i - k] == data[i + k])
            ++k;

        odd[i] = k--;

        if (i + k > r) {
            l = i - k;
            r = i + k;
        }
    }

    for (valueType i = 0, l = 0, r = -1; i < size; ++i) {
        valueType k = (i > r) ? 0 : std::min(even[l + r - i + 1], r - i + 1);

        while (i - k - 1 >= 0 && i + k < size && data[i - k - 1] == data[i + k])
            ++k;

        even[i] = k--;

        if (i + k > r) {
            l = i - k - 1;
            r = i + k;
        }
    }

    return std::make_pair(odd, even);
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string data;
    std::cin >> data;

    auto const result = manacher(data);

    valueType max = 0;

    for (valueType i = 0; i < data.size(); ++i)
        max = std::max(max, result.first[i] * 2 - 1);

    for (valueType i = 0; i < data.size(); ++i)
        max = std::max(max, result.second[i] * 2);

    std::cout << max << '\n';

    return 0;
}