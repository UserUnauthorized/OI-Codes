//HZ - 265.3
#include <bits/stdc++.h>

using namespace std;
const long long p = 998244353;
long long ans = 0;
int n, m, k;
vector<pair<int, int>> factors;

void init();

void getFactors();

int main() {
    scanf("%d%d%d", &n, &m, &k);
    getFactors();
    for (auto iter = factors.begin(); iter != factors.end(); ++iter) {
        pair<int, int> &fact = *iter;
        if (n >= fact.first - 1 && m >= fact.second - 1)
            ans += (n - fact.first + 2) * (m - fact.second + 2);
        if (m >= fact.first - 1 && n >= fact.second - 1 && fact.first != fact.second)
            ans += (m - fact.first + 2) * (n - fact.second + 2);
        if (n >= fact.first - 1 && m >= fact.second)
            ans += (n - fact.first + 2) * (m - fact.second + 1);
        if (m >= fact.first - 1 && n >= fact.second)
            ans += (m - fact.first + 2) * (n - fact.second + 1);
        if (n >= fact.first && m >= fact.second)
            ans += (n - fact.first + 1) * (m - fact.second + 1);
        if (m >= fact.first && n >= fact.second && fact.first != fact.second)
            ans += (m - fact.first + 1) * (n - fact.second + 1);
        ans %= p;
    }
    printf("%lld", ans);
    return 0;
}

void getFactors() {
    for (int i = 1; i <= sqrt(k); ++i)
        if (k % i == 0)
            factors.emplace_back(i << 1, k / i << 1);
}