//Codeforces - 915G - 2
#include <bits/stdc++.h>

typedef int valueType;
typedef std::vector<valueType> ValueVector;
typedef std::vector<ValueVector> ValueMatrix;
typedef std::vector<bool> bitset;

constexpr valueType MOD = 1e9 + 7;

template<typename T1, typename T2, typename T3 = valueType>
void Inc(T1 &a, T2 b, const T3 &mod = MOD) {
    a = a + b;

    if (a >= mod)
        a -= mod;
}

template<typename T1, typename T2, typename T3 = valueType>
void Dec(T1 &a, T2 b, const T3 &mod = MOD) {
    a = a - b;

    if (a < 0)
        a += mod;
}

template<typename T1, typename T2, typename T3 = valueType>
T1 sub(T1 a, T2 b, const T3 &mod = MOD) {
    return a - b < 0 ? a - b + mod : a - b;
}

template<typename T1, typename T2, typename T3 = valueType>
T1 mul(T1 a, T2 b, const T3 &mod = MOD) {
    return (long long) a * b % mod;
}

template<typename T1, typename T2, typename T3 = valueType>
void Mul(T1 &a, T2 b, const T3 &mod = MOD) {
    a = (long long) a * b % mod;
}

template<typename T1, typename T2, typename T3 = valueType>
T1 pow(T1 a, T2 b, const T3 &mod = MOD) {
    T1 result = 1;

    while (b > 0) {
        if (b & 1)
            Mul(result, a, mod);

        Mul(a, a, mod);
        b = b >> 1;
    }

    return result;
}

class LineSieve {
public:
    typedef std::vector<valueType> container;

private:
    valueType N, M;
    container prime;
    bitset isPrime;
    container Power;

public:
    LineSieve(valueType n, valueType m) : N(n), M(m), prime(), isPrime(n + 1, true), Power(n + 1) {
        prime.reserve(n / 10);
        Power[0] = 0;
        Power[1] = 1;

        for (valueType i = 2; i <= N; ++i) {
            if (isPrime[i]) {
                prime.push_back(i);

                Power[i] = ::pow(i, M);
            }

            for (auto const &iter: prime) {
                valueType const t = i * iter;

                if (t > N)
                    break;

                isPrime[t] = false;

                Power[t] = mul(Power[i], Power[iter]);

                if (i % iter == 0)
                    break;
            }
        }
    }

    valueType pow(valueType n) const {
        return Power[n];
    }

    const container &Prime() const {
        return prime;
    }
};

int main() {
    valueType N, K;

    std::cin >> N >> K;

    LineSieve const sieve(K, N);

    ValueVector const &P = sieve.Prime();

    ValueVector F(K + 1, 0);

    for (valueType i = 1; i <= K; ++i)
        F[i] = sub(sieve.pow(i), sieve.pow(i - 1));

    for (auto const &iter: P)
        for (valueType i = K / iter; i >= 1; --i)
            Dec(F[i * iter], F[i]);

    for (valueType i = 1; i <= K; ++i)
        Inc(F[i], F[i - 1]);

    valueType result = 0;

    for (valueType i = 1; i <= K; ++i)
        Inc(result, F[i] ^ i);

    std::cout << result << std::endl;
}