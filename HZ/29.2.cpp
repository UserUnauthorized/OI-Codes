//HZ - 29.2
//Luogu - P1516

#include<bits/stdc++.h>

using namespace std;

long long exGcd(long long a, long long b, long long &x, long long &y);

int main() {
    long long x(0), y(0), m(0), n(0), L(0);
    cin >> x >> y >> m >> n >> L;
    if (m > n) {
        swap(x, y);
        swap(m, n);
    }
    long long const a = n - m, b = L, c = x - y;
    long long x0(0), y0(0), gcd = exGcd(a, b, x0, y0);

    if (c % gcd != 0) {
        cout << "Impossible" << endl;
        return 0;
    }

    long long const k = c / gcd;
    x0 *= k;

    long long const k1 = b / gcd;

    cout << (x0 % k1 + k1) % k1 << endl;
    return 0;
}

long long exGcd(long long a, long long b, long long &x, long long &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    long long const d = exGcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}