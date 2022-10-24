//HZ - 265.3
#include <bits/stdc++.h>

unsigned long long ans;
unsigned long long n, m, k;
std::vector<std::pair<unsigned long long, unsigned long long>> factors;

int main() {
    char ch(0);
    while (ch < '0' || ch > '9')ch = getchar();
    while (ch >= '0' && ch <= '9') {
        n = (n << 3) + (n << 1) + (ch ^ 48);
        ch = getchar();
    }

    while (ch < '0' || ch > '9')ch = getchar();
    while (ch >= '0' && ch <= '9') {
        m = (m << 3) + (m << 1) + (ch ^ 48);
        ch = getchar();
    }

    while (ch < '0' || ch > '9')ch = getchar();
    while (ch >= '0' && ch <= '9') {
        k = (k << 3) + (k << 1) + (ch ^ 48);
        ch = getchar();
    }

    for (int i = 1; i <= sqrt(k); ++i)
        if (k % i == 0)
            factors.emplace_back(i << 1, k / i << 1);

    for (auto iter = factors.begin(); iter != factors.end(); ++iter) {
        if (n >= iter->first - 1 && m >= iter->second - 1)
            ans += (n - iter->first + 2) * (m - iter->second + 2);
        if (n >= iter->first - 1 && m >= iter->second)
            ans += (n - iter->first + 2) * (m - iter->second + 1);
        if (n >= iter->first && m >= iter->second - 1)
            ans += (n - iter->first + 1) * (m - iter->second + 2);
        if (n >= iter->first && m >= iter->second)
            ans += (n - iter->first + 1) * (m - iter->second + 1);
        if (iter->first == iter->second)
            continue;
        if (m >= iter->first && n >= iter->second - 1)
            ans += (m - iter->first + 1) * (n - iter->second + 2);
        if (m >= iter->first - 1 && n >= iter->second - 1)
            ans += (m - iter->first + 2) * (n - iter->second + 2);
        if (m >= iter->first - 1 && n >= iter->second)
            ans += (m - iter->first + 2) * (n - iter->second + 1);
        if (m >= iter->first && n >= iter->second)
            ans += (m - iter->first + 1) * (n - iter->second + 1);
        ans %= 998244353;
    }
    printf("%llu", ans);
    return 0;
}