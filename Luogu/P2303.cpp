//HZ - 29.8
//Luogu - P2303
#include <bits/stdc++.h>

using namespace std;
constexpr long long maxN = ((long long) 1 << 32);
constexpr long long maxM = (1 << 16) + 5;

template<typename T>
class Euler {
public:
    typedef T value_type;

    value_type operator[](value_type _n_) const;
};

int main() {
    long long n(0);
    cin >> n;
    Euler<long long> const euler;
    long long ans(0);
    for (long long i = 1; i * i <= n; ++i) {
        if (n % i == 0) {
            ans += euler[n / i] * i;
            if (i * i != n) {
                ans += euler[i] * (n / i);
            }
        }
    }
    cout << ans;
    return 0;
}

template<typename T>
typename Euler<T>::value_type Euler<T>::operator[](value_type _n_) const {
    value_type result = _n_;
    for (value_type i = 2; i * i <= _n_; ++i) {
        if (_n_ % i == 0) {
            result = result / i * (i - 1);
            while (_n_ % i == 0) {
                _n_ /= i;
            }
        }
    }
    if (_n_ > 1) {
        result = result / _n_ * (_n_ - 1);
    }
    return result;
}
