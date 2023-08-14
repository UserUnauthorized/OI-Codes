//CodeForces - 1779C
#include <bits/stdc++.h>

typedef long long valueType;
typedef std::vector<valueType> ValueVector;

int main() {
    valueType T;

    std::cin >> T;

    for (int testcase = 0; testcase < T; ++testcase) {
        valueType N, M, ans = 0;

        std::cin >> N >> M;

        ValueVector source(N + 1);

        for (valueType i = 1; i <= N; ++i)
            std::cin >> source[i];

        std::priority_queue<valueType, std::vector<valueType>, std::greater<>> afterQueue;

        valueType afterSum = 0;

        for (valueType i = M + 1; i <= N; ++i) {
            afterQueue.push(source[i]);

            afterSum += source[i];

            while (afterSum < 0) {
                ++ans;

                afterSum -= 2 * afterQueue.top();

                afterQueue.pop();
            }
        }

        std::priority_queue<valueType> beforeQueue;

        valueType beforeSum = 0;

        for (valueType i = M; i > 1; --i) {
            beforeQueue.push(source[i]);

            beforeSum += source[i];

            while (beforeSum > 0) {
                ++ans;

                beforeSum -= 2 * beforeQueue.top();

                beforeQueue.pop();
            }
        }

        std::cout << ans << '\n';
    }

    std::cout << std::flush;

    return 0;
}