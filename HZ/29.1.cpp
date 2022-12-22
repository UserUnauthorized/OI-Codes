//HZ - 29.1
//Luogu - P1082
#include <bits/stdc++.h>

using namespace std;

void exGcd(long long a, long long b, long long &x, long long &y);

long long A, B, X, Y;

int main() {
    scanf("%lld%lld", &::A, &::B);
    exGcd(::A, ::B, ::X, ::Y);
    printf("%lld", (::X % B + B) % B);
    return 0;
}

void exGcd(long long a, long long b, long long &x, long long &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return;
    }
    exGcd(b, a % b, x, y);
    long long t(x);
    x = y;
    y = t - a / b * y;
}