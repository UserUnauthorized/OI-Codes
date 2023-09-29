#include <bits/stdc++.h>

typedef long long valueType;
typedef std::vector<valueType> ValueVector;

valueType gcd(valueType a, valueType b) {
    return std::__gcd(a, b);
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    valueType N;

    std::cin >> N;

    ValueVector A(N);

    for (auto &iter: A)
        std::cin >> iter;

    std::sort(A.begin(), A.end());

    A.erase(std::unique(A.begin(), A.end()), A.end());

    if (A.size() == 1) {
        std::cout << 1 << std::endl;

        return 0;
    }

    valueType G = 0;

    for (valueType i = 1; i < A.size(); ++i)
        G = gcd(G, A[i] - A[i - 1]);

    if (G != 1)
        std::cout << 1 << std::endl;
    else
        std::cout << 2 << std::endl;

    return 0;
}