//Codeforces - 1469D
#include <bits/stdc++.h>

typedef int valueType;

int main() {
    valueType T;

    std::cin >> T;

    for (valueType testcase = 0; testcase < T; ++testcase) {
        valueType N;

        std::cin >> N;

        if (N == 3) {
            std::cout << "2\n3 2\n3 2\n";

            continue;
        }

        std::cout << N - 1 << '\n';

        for (valueType i = N; i > 2; --i) {
            std::cout << i << ' ' << i / 2 + 1 << '\n';
        }

        std::cout << "3 2\n";
    }

    std::cout << std::flush;

    return 0;
}