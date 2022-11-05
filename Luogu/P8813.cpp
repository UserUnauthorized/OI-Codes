//Luogu - P8813
//CSP-J 2022 T1
#include <bits/stdc++.h>

using namespace std;
namespace P8813 {
    constexpr int maxn = 1e9;
    unsigned long long a, b;

    void init();

    int pow(unsigned long long base, unsigned long long index) {
        unsigned long long result(1);
        for (; index > 0; index >>= 1) {
            if (base > P8813::maxn)
                return -1;

            if (index & 1)
                result *= base;

            if (result > P8813::maxn)
                return -1;

            base *= base;
        }
        return (int) result;
    }
}

int main() {
    scanf("%llu%llu", &P8813::a, &P8813::b);
    printf("%d", P8813::pow(P8813::a, P8813::b));
    return 0;
}