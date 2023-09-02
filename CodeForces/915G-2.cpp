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
    container Mobius, Power, Func, minFact;

public:
    LineSieve(valueType n, valueType m) : N(n), M(m), prime(), isPrime(n + 1, true), Mobius(n + 1, 1), Power(n + 1),
                                          Func(n + 1), minFact(n + 1) {
        Mobius[1] = 1;
        Power[0] = 0;
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

            Power[i] = sub(Power[i], Power[i - 1]);
        }

        Func[1] = 1;
        minFact[1] = 1;

        for (valueType i = 2; i <= N; ++i) {
            if (isPrime[i]) {
                Func[i] = sub(Power[i], 1);
                minFact[i] = i;
            }

            for (auto const &iter: prime) {
                valueType const t = i * iter;

                if (t > N || iter > i)
                    break;

                if (i % iter == 0) {
                    minFact[t] = iter * minFact[i];

                    if (minFact[i] == i) {
                        Func[t] = sub(Power[t], Power[i]);
                    } else {
                        Func[t] = mul(Func[minFact[t]], Func[t / minFact[t]]);
                    }
                } else {
                    Func[t] = mul(Func[i], Func[iter]);
                    minFact[t] = iter;
                }
            }
        }
    }

    valueType operator()(valueType n) const {
        return Func[n];
    }

    valueType pow(valueType n) const {
        return Power[n];
    }
};

int main() {
    valueType N, K;

    std::cin >> N >> K;

    LineSieve const sieve(K, N);

    ValueVector ans(K + 1, 0);

    for (valueType i = 1; i <= K; ++i) {
        ans[i] = ans[i - 1];

        Inc(ans[i], sieve(i));
    }

    valueType result = 0;

    for (valueType i = 1; i <= K; ++i)
        Inc(result, ans[i] ^ i);

    std::cout << result << std::endl;
}