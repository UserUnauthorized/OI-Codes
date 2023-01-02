//HZ - 29.7
//Luogu - P2158
#include <bits/stdc++.h>

using namespace std;
constexpr int maxN = 4e4 + 5;

class Euler {
private:
    int n;
    array<int, maxN> prime, phi, partialSum;
    array<bool, maxN> isPrime;
    int cnt;
public:
    Euler() : n(), prime(), phi(), partialSum(), isPrime(), cnt() {};

    Euler(int _n_);

    int operator[](int t) const {
        return phi[t];
    }

    int getPartialSum(int t) const {
        return partialSum[t];
    }
};

int main() {
    int n(0);
    cin >> n;
    Euler const euler(n);
    cout << (n == 1 ? 0 : euler.getPartialSum(n - 1) << 1 | 1) << endl;
    return 0;
}

Euler::Euler(int _n_) : n(_n_), prime(), phi(), partialSum(), isPrime(), cnt(0) {
    fill(isPrime.begin(), isPrime.end(), true);
    isPrime[1] = false;
    phi[1] = 1;
    for (int i = 2; i <= n; ++i) {
        if (isPrime[i]) {
            prime[++cnt] = i;
            phi[i] = i - 1;
        }
        for (int j = 1; j <= cnt && i * prime[j] <= n; ++j) {
            isPrime[(size_t) i * prime[j]] = false;
            if (i % prime[j] == 0) {
                phi[(size_t) i * prime[j]] = phi[i] * prime[j];
                break;
            } else {
                phi[(size_t) i * prime[j]] = phi[i] * (prime[j] - 1);
            }
        }
    }

    for (int i = 1; i <= n; ++i) {
        partialSum[i] = partialSum[i - 1] + phi[i];
    }
}