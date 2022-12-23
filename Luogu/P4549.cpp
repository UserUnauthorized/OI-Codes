//Luogu - P4549
#include<bits/stdc++.h>

using namespace std;

long long gcd(long long a, long long b);

int main() {
    long long ans(0), n(0);
    cin >> n;
    for (long long i = 1; i <= n; ++i) {
        long long t(0);
        cin >> t;
        ans = gcd(ans, t > 0 ? t : -t);
    }
    cout << ans;
}

long long gcd(long long a, long long b) {
    return b == 0 ? a : gcd(b, a % b);
}