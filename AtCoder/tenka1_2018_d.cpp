#include<bits/stdc++.h>

typedef int valueType;
typedef std::vector<valueType> ValueVector;
typedef std::vector<ValueVector> ValueMatrix;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    valueType N;

    std::cin >> N;

    valueType M = 0;

    while (M * (M - 1) / 2 < N)
        ++M;

    if (M * (M - 1) / 2 != N) {
        std::cout << "No" << std::endl;

        return 0;
    }

    std::cout << "Yes" << std::endl;

    ValueMatrix ans(M);

    valueType pointer = 0;

    for (valueType i = 0; i < M; ++i) {
        for (valueType j = i + 1; j < M; ++j) {
            ++pointer;

            ans[i].push_back(pointer);
            ans[j].push_back(pointer);
        }
    }

    std::cout << M << std::endl;
}