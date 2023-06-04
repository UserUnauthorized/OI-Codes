//HZ - 35.6
//Luogu - P1365
#include<bits/stdc++.h>

typedef long double realType;
typedef size_t sizeType;

int main() {
    sizeType N;

    std::cin >> N;

    std::string data;

    std::cin >> data;

    std::function<realType(sizeType)> P = [&data](sizeType i) {
        --i;

        if (data[i] == 'o')
            return (realType) 1;

        if (data[i] == 'x')
            return (realType) 0;

        if (data[i] == '?')
            return (realType) 1 / 2;

        return (realType) INFINITY;
    };

    std::vector<realType> x1(N + 1, 0), ans(N + 1, 0);

    for (sizeType i = 1; i <= N; ++i) {
        x1[i] = (x1[i - 1] + 1) * P(i);

        ans[i] = ans[i - 1] + (2 * x1[i - 1] + 1) * P(i);
    }

    std::cout << std::setprecision(4) << std::fixed << ans[N] << std::flush;

    return 0;
}
