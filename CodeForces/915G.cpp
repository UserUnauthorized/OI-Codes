//Codeforces - 915G
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
    container Mobius, Power;
    ValueMatrix Factor;

public:
    LineSieve(valueType n, valueType m) : N(n), M(m), prime(), isPrime(n + 1, true), Mobius(n + 1, 1), Factor(n + 1),
                                          Power(n + 1, 1) {
        isPrime[0] = isPrime[1] = false;
        Mobius[1] = 1;
        Power[1] = 1;

        for (valueType i = 2; i <= N; ++i) {
            if (isPrime[i]) {
                prime.push_back(i);

                Mobius[i] = -1;

                Power[i] = ::pow(i, M);
            }

            for (auto const &iter: prime) {
                valueType const t = i * iter;

                if (t > N)
                    break;

                isPrime[t] = false;

                Power[t] = mul(Power[i], Power[iter]);

                if (i % iter == 0) {
                    Mobius[t] = 0;

                    break;
                } else {
                    Mobius[t] = -Mobius[i];
                }
            }

            if (Mobius[i] < 0)
                Mobius[i] += MOD;
        }

        for (valueType i = 1; i <= N; ++i)
            for (valueType j = i; j <= N; j += i)
                Factor[j].push_back(i);
    }

    valueType operator()(valueType n) const {
        return Mobius[n];
    }

    valueType pow(valueType n) const {
        return Power[n];
    }

    const ValueVector &fact(valueType n) const {
        return Factor[n];
    }
};

int main() {
    valueType N, K;

    std::cin >> N >> K;

    LineSieve const sieve(K, N);

    ValueVector ans(K + 1, 0), F(K + 1, 0);

    for (valueType i = 1; i <= K; ++i) {
        ans[i] = ans[i - 1];

        for (auto const &iter: sieve.fact(i)) {
            Inc(ans[i], mul(sieve(iter), sub(sieve.pow(i / iter), sieve.pow(i / iter - 1))));

            Inc(F[i / iter], sub(sieve.pow(i / iter), sieve.pow(i / iter - 1)));
        }

        F[i] = sieve(i);

        Inc(ans[i], F[i]);
    }

    valueType result = 0;

    for (valueType i = 1; i <= K; ++i)
        Inc(result, ans[i] ^ i);

    std::cout << result << std::endl;
}