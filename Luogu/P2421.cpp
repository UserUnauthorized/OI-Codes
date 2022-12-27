//HZ - 29.5
//Luogu - P2421
#include<bits/stdc++.h>

using namespace std;

constexpr int maxN = 20;

int n, m(0);
array<int, maxN> C, P, L;

int exGcd(int a, int b, int &x, int &y);

bool check(int M_);

int main() {
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> C[i] >> P[i] >> L[i];
        m = max(m, C[i]);
    }
    for (int i = m;; ++i) {
        if (check(i)) {
            cout << i;
            return 0;
        }
    }
}

int exGcd(int a, int b, int &x, int &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    int const d = exGcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}

bool check(int M_) {
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            int a = P[i] - P[j], b = M_, c = C[j] - C[i], x(0), y(0);
            int const gcd = exGcd(a, b, x, y);
            if (c % gcd != 0)
                continue;
            x *= c / gcd;
            b /= (b / gcd) > 0 ? gcd : -gcd;
            x = (x % b + b) % b;
            if (x <= L[i] && x <= L[j])
                return false;
        }
    }
    return true;
}