//HZ - 29.3
//Luogu - P1292
#include<bits/stdc++.h>

using namespace std;

long long exGcd(long long a, long long b, long long &x, long long &y);

int main() {
    long long a(0), b(0);
    cin >> a >> b;

    long long x(0), y(0), gcd = exGcd(a, b, x, y);
    cout << gcd << "\n";
    x = -x;
    a = -a;
    long long const k1 = b / gcd, k2 = a / gcd;;
    int const lowerS = ceil((double) -x / (double) k1);
    cout << x + k1 * lowerS << ' ' << y - k2 * lowerS << '\n';
    /*while (x < 0) {
        x += k1;
        y -= k2;
    }
    while (y < 0) {
        x -= k1;
        y += k2;
    }
    cout << x << ' ' << y << '\n';*/
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