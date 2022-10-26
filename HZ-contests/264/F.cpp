//HZ - 264.6
#include <bits/stdc++.h>

using namespace std;
const int maxn = 1000006;

inline int read();

inline void write(int *);

inline void init();

inline void primeInit();

inline void getPrimeFactor(int);

int n, source[maxn], minPrime[maxn], minFactor[maxn];
int minP;
unsigned long long ans(0);
vector<int> prime;

int main() {
    freopen("huan.in", "r", stdin);
    freopen("huan.out", "w", stdout);
    init();
    primeInit();
    minP = __gcd(source[1], source[2]);
    for (int i = 3; i <= n; ++i)
        minP = __gcd(minP, source[i]);

    for (int i = 1; i <= n; ++i)
        source[i] /= minP;

    for (int i = 1; i <= n; ++i)
        getPrimeFactor(source[i]);

    printf("%llu", ans);
    fclose(stdin);
    fclose(stdout);
    return 0;
}

inline void init() {
    memset(source, 0, sizeof(source));
    memset(minPrime, 0xff, sizeof(minPrime));
    memset(minFactor, 0x7f, sizeof(minFactor));

    n = read();

    for (int i = 1; i <= n; ++i)
        write(source + i);
}

inline int read() {
    int result(0), ch(getchar());
    while (ch < '0' || ch > '9')
        ch = getchar();
    while (ch >= '0' && ch <= '9') {
        result = (result << 3) + (result << 1) + (ch ^ 48);
        ch = getchar();
    }
    return result;
}

inline void write(int *result) {
    int ch(getchar());
    while (ch < '0' || ch > '9')
        ch = getchar();
    while (ch >= '0' && ch <= '9') {
        *result = (*result << 3) + (*result << 1) + (ch ^ 48);
        ch = getchar();
    }
}

inline void primeInit() {
    for (int i = 2; i < maxn; ++i) {
        if (minPrime[i] == -1) {
            prime.push_back(i);
            for (int j = i; j < maxn; j += i) {
                if (minPrime[j] == -1) {
                    minPrime[j] = i;
                }
            }
        }
    }
}

inline void getPrimeFactor(int x) {
    if (x == 1)
        return;
    if (minPrime[x] == x) {
        ++ans;
    } else {
        for (int i = x; i > 1; i /= minPrime[i]) {
            ++ans;
        }
    }
}