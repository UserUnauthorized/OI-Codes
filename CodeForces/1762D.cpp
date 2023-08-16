//Codeforces - 1762D
#include <bits/stdc++.h>

typedef int valueType;
typedef std::vector<valueType> ValueVector;

int main() {
    valueType T;

    std::cin >> T;

    for (int testcase = 0; testcase < T; ++testcase) {
        valueType N;

        std::cin >> N;

        if (N == 2) {
            std::cout << "! 1 2" << std::endl;

            valueType result;

            std::cin >> result;

            if (result == -1)
                return 0;

            continue;
        }

        ValueVector source(N);

        std::iota(source.begin(), source.end(), 1);

        while (source.size() >= 3) {
            std::cout << "? " << source[0] << ' ' << source[1] << std::endl;

            valueType result_0_1;

            std::cin >> result_0_1;

            std::cout << "? " << source[0] << ' ' << source[2] << std::endl;

            valueType result_0_2;

            std::cin >> result_0_2;

            if (result_0_1 == result_0_2) {
                source.erase(source.begin());
            } else if(result_0_1 > result_0_2) {
                source.erase(source.begin() + 2);
            } else {
                source.erase(source.begin() + 1);
            }
        }

        std::cout << "! " << source.front() << ' ' << source.back() << std::endl;

        valueType result;

        std::cin >> result;

        if (result == -1)
            return 0;
    }

    return 0;
}