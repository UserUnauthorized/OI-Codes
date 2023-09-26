#include <bits/stdc++.h>

typedef long long valueType;
typedef std::vector<valueType> ValueVector;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    valueType N;

    std::cin >> N;

    ValueVector A(N);

    for (auto &iter: A)
        std::cin >> iter;

    std::sort(A.begin(), A.end(), std::greater<>());

    ValueVector B(N);

    for (valueType i = 0; i < N; i += 2) {
        B[i] = A.back();

        A.pop_back();
    }

    for (valueType i = 1; i < N; i += 2) {
        B[i] = A.back();

        A.pop_back();
    }

    for (valueType i = 1; i < N; i += 2) {
        if (B[i - 1] >= B[i] || B[i + 1] >= B[i]) {
            std::cout << "No" << std::endl;

            return 0;
        }
    }

    std::cout << "Yes" << std::endl;

    return 0;
}