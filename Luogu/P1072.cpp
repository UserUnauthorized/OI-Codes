//Luogu - P1072
#include <bits/stdc++.h>

using namespace std;

int main() {
    int ans(0), n, a0, a1, b0, b1;
    scanf("%d", &n);
    while (n--) {
        ans = 0;
        scanf("%d%d%d%d", &a0, &a1, &b0, &b1);
        for (int i = 1; i <= sqrt(b1); ++i) {
            if (b1 % i == 0) {
                if (i % a1 == 0 && __gcd(i / a1, a0 / a1) == 1 && __gcd(b1 / b0, b1 / i) == 1)
                    ++ans;
                if (b1 / i == i)
                    continue;
                int x = b1 / i;
                if (x % a1 == 0 && __gcd(x / a1, a0 / a1) == 1 && __gcd(b1 / b0, b1 / x) == 1)
                    ++ans;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}