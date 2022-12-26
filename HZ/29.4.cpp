//HZ - 29.4
//Luogu - P3811

#include <bits/stdc++.h>

using namespace std;
constexpr int maxn = 3e6 + 5;
int n, p;
int inv[maxn];

int main() {
    cin >> n >> p;
    inv[1] = 1;
    for (int i = 2; i <= n; ++i) {
        inv[i] = (int) ((long long) (p - p / i) * (long long) inv[p % i] % p);
    }

    for (int i = 1; i <= n; ++i) {
        cout << inv[i];
        putchar('\n');
    }
    return 0;
}