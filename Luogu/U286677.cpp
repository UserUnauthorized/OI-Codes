#include <bits/stdc++.h>

typedef long long valueType;

constexpr valueType maxN = 1e18 + 5, maxK = 105;

typedef std::array<valueType, maxK> ARRAY;
typedef std::bitset<maxK> BitArray;

valueType N_, M_, K_, primeCount_;
valueType const &N = N_, &M = M_, &K = K_, &primeCount = primeCount_;
ARRAY prime;

valueType check(valueType l, valueType r, valueType k);

void init();

int main() {
    init();

    for (int i = 0; i < M; ++i) {
        valueType l = 0, r = 0, ans = 0;
        std::cin >> l >> r;

        for (int j = 1; j <= primeCount; ++j)
            ans += check(l, r, prime[j]);

        std::cout << ans << std::endl;
    }

    return 0;
}

void init() {
    std::cin >> N_ >> M_ >> K_;

    BitArray isPrime;
    isPrime.set();

    for (int i = 2; i <= K; ++i) {
        if (isPrime[i]) {
            prime[++primeCount_] = i;
        }

        for (int j = 1; j <= primeCount && i * prime[j] <= K; ++j) {
            isPrime[i * prime[j]] = false;
            if (i % prime[j] == 0) {
                break;
            }
        }
    }
}

valueType check(valueType l, valueType r, valueType k) {
    if (l > r)
        return 0;

    valueType result = 0, kPower = 1;
    valueType const base = k;

    while (k <= r) {
        if (k >= l && kPower % base != 0 && k <= r)
            ++result;

        ++kPower;
        k *= base;
    }

    return result;
}