//HZ - 29.6
//Luogu - P2054
/*
 * @method: exGcd
 */
#include<bits/stdc++.h>

using namespace std;
typedef __int128 valueType;
typedef long long IOType;

inline valueType binPow(valueType a, valueType b, valueType mod);

valueType exGcd(valueType a, valueType b, valueType &x, valueType &y);

int main() {
    IOType _n_(0), _m_(0), _l_(0);
    cin >> _n_ >> _m_ >> _l_;
    valueType n(_n_), m(_m_), l(_l_);
    valueType a(binPow((valueType) 2, m, n + 1)), b(n + 1), c(l), x(0), y(0);
    valueType const gcd = exGcd(a, b, x, y);
    x *= c / gcd;
    b /= b > 0 ? gcd : -gcd;
    x = (x % b + b) % b;
    cout << (IOType) x;
    return 0;
}

valueType exGcd(valueType a, valueType b, valueType &x, valueType &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    valueType const d = exGcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}

valueType binPow(valueType a, valueType b, valueType mod) {
    valueType result = 1;
    while (b) {
        if (b & 1)
            result = result * a % (valueType) mod;
        a = a * a % (valueType) mod;
        b >>= 1;
    }
    return result;
}