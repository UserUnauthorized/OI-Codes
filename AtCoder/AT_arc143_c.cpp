//AT_arc143_c
#include <bits/stdc++.h>

typedef int valueType;
typedef std::vector<valueType> ValueVector;

int main() {
    valueType N, X, Y;

    std::cin >> N >> X >> Y;

    ValueVector source(N);

    bool allLessThanX = true;

    for (auto &iter: source) {
        std::cin >> iter;

        iter %= X + Y;

        if (iter >= X)
            allLessThanX = false;
    }

    if (allLessThanX) {
        std::cout << "Second" << std::endl;
    } else if (X <= Y) {
        std::cout << "First" << std::endl;
    } else {
        bool flag = false;

        for (auto const &iter: source)
            if (iter < X && iter >= Y)
                flag = true;

        std::cout << (flag ? "Second" : "First") << std::endl;
    }
}