//CF - 896B
#include <bits/stdc++.h>

typedef int valueType;
typedef std::vector<valueType> ValueVector;
typedef std::vector<bool> bitset;

int main() {
    valueType N, M, C;

    std::cin >> N >> M >> C;

    ValueVector A(N + 1, -1), leftBound(C + 1, 0), rightBound(C + 1, 0), count(C + 1, 0);
    bitset full(N + 1, false);

    valueType const block = N / C;

    if (block == 0) {
        double const K = (double )N / C;

        leftBound[1] = rightBound[1] = 1;

        for(valueType i = 1; i <= C; ++i) {
            leftBound[i] = rightBound[i] = std::ceil(i * K);
        }

        leftBound[C] = rightBound[C] = N;
    } else {
        for (valueType i = 1; i <= C; ++i)
            leftBound[i] = (rightBound[i - 1] = (i - 1) * block) + 1;

        rightBound[C] = N;
    }

    for (valueType i = 0; i < M; ++i) {
        valueType p;

        std::cin >> p;

        ++count[p];

        if (!full[p]) {
            valueType const mid = (leftBound[p] + rightBound[p]) >> 1;

            int j = 0;

            while (true) {
                if (mid + j <= N && A[mid + j] == -1) {
                    std::cout << mid + j << std::endl;
                    A[mid + j] = p;
                    break;
                }

                if (mid - j >= 1 && A[mid - j] == -1) {
                    std::cout << mid - j << std::endl;
                    A[mid - j] = p;
                    break;
                }

                ++j;
            }

            if (count[p] == rightBound[p] - leftBound[p] + 1)
                full[p] = true;
        } else {
            if (rightBound[p] + 1 <= N && A[rightBound[p] + 1] == -1) {
                std::cout << rightBound[p] + 1 << std::endl;
                A[rightBound[p] + 1] = p;
                ++rightBound[p];
            } else if (leftBound[p] - 1 >= 1 && A[leftBound[p] - 1] == -1) {
                std::cout << leftBound[p] - 1 << std::endl;
                A[leftBound[p] - 1] = p;
                --leftBound[p];
            } else if (rightBound[p] + 1 <= N) {
                std::cout << rightBound[p] + 1 << std::endl;
                A[rightBound[p] + 1] = p;
                ++rightBound[p];

                if (p == C)
                    continue;

                ++leftBound[p + 1];
            } else {
                std::cout << leftBound[p] - 1 << std::endl;
                A[leftBound[p] - 1] = p;
                --leftBound[p];

                if (p == 1)
                    continue;

                --rightBound[p - 1];
            }
        }

        if (std::find(A.begin() + 1, A.end(), -1) == A.end() && std::is_sorted(A.begin() + 1, A.end()))
            break;
    }

    return 0;
}