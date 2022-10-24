//HZ - 265.3
#include <bits/stdc++.h>

using namespace std;
const unsigned long long p = 998244353;
unsigned long long ans = 0;
unsigned long long n, m, k;
vector<pair<unsigned long long, unsigned long long>> factors;

void init();

void getFactors();

int main() {
    scanf("%d%d%llu", &n, &m, &k);
    getFactors();
    for (auto iter = factors.begin(); iter != factors.end(); ++iter) {
        pair<unsigned long long, unsigned long long> &fact = *iter;
        if (n >= fact.first - 1 && m >= fact.second - 1)
            ans += (n - fact.first + 1 + 1) * (m - fact.second + 1 + 1);
        ans %= p;
        if (m >= fact.first - 1 && n >= fact.second - 1 && fact.first != fact.second)
            ans += (m - fact.first + 1 + 1) * (n - fact.second + 1 + 1);
        ans %= p;
        if (n >= fact.first - 1 && m >= fact.second)
            ans += (n - fact.first + 1 + 1) * (m - fact.second + 1);
        ans %= p;
        if (m >= fact.first - 1 && n >= fact.second)
            ans += (m - fact.first + 1 + 1) * (n - fact.second + 1);
        ans %= p;
        if (n >= fact.first && m >= fact.second - 1)
            ans += (n - fact.first + 1) * (m - fact.second + 1 + 1);
        ans %= p;
        if (m >= fact.first && n >= fact.second - 1)
            ans += (m - fact.first + 1) * (n - fact.second + 1 + 1);
        ans %= p;
        if (n >= fact.first && m >= fact.second)
            ans += (n - fact.first + 1) * (m - fact.second + 1);
        ans %= p;
        if (m >= fact.first && n >= fact.second && fact.first != fact.second)
            ans += (m - fact.first + 1) * (n - fact.second + 1);
        ans %= p;
    }
    printf("%llu", ans % p);
    return 0;
}

void getFactors() {
    for (int i = 1; i <= min((unsigned long long) sqrt(k), max(n, m)); ++i)
        if (k % i == 0)
            factors.emplace_back(i << 1, k / i << 1);
}