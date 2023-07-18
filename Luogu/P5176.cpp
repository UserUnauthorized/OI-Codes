//Luogu - P5176
#include<bits/stdc++.h>

typedef long long valueType;
constexpr valueType maxN = 2e7 + 5;
constexpr valueType MOD = 1e9 + 7;

class LineSieve {
public:
    typedef std::vector<valueType> container;
    typedef std::vector<bool> bitset;

private:
    valueType size;
    bitset isPrime;
    container primeList;
    container data;

public:
    LineSieve(valueType _size_) : size(_size_), isPrime(_size_ + 1, true),
                                               data(_size_ + 1, 0) {
        primeList.reserve((size_t) std::floor(std::log((long double) (_size_ + 1))));
        data[1] = 1;
        for (valueType i = 2; i <= size; ++i) {
            if (isPrime[i]) {
                primeList.push_back(i);
                data[i] = (i * i - 1) % MOD;
            }

            for (auto const &iter: primeList) {
                valueType const t = i * iter;

                if (t > size)
                    break;

                isPrime[t] = false;

                if (i % iter == 0) {
                    data[t] = data[i] * iter % MOD * iter % MOD;
					
                    break;
                } else {
					data[t] = data[i] * data[iter] % MOD;
                }
            }
        }

        typedef std::function<valueType(const valueType &, const valueType &)> ModPlus;

        ModPlus Op = [](const valueType &a, const valueType &b) -> valueType {
            return (a + b) % MOD;
        };
		
        std::partial_sum(data.begin(), data.end(), data.begin(), Op);
    }
	
	
	
    valueType Ans(valueType x) const {
        if (x > size)
            throw std::range_error("Larger than Size.");

        if (x < 0)
            throw std::range_error("Too small.");

        return data[x];
    }
};

int main() {
    valueType T;

    std::cin >> T;

    LineSieve Euler(maxN);

    typedef std::function<valueType(valueType, valueType)> solveFunction;

    solveFunction solve = [&Euler](valueType N, valueType M) -> valueType {
        if (N > M)
            std::swap(N, M);

        valueType result = 0;

        valueType l = 1, r;

        while (l <= N) {
            r = std::min(N / (N / l), M / (M / l));

            result = (result + (Euler.Ans(r) - Euler.Ans(l - 1)) * (N / l) % MOD * (M / l) % MOD) % MOD;

            l = r + 1;
        }

        return result;
    };

    for (int i = 0; i < T; ++i) {
        valueType N, M, P;

        std::cin >> N >> M >> P;

		valueType const result = ((N * solve(M, P) + M * solve(N, P) + P * solve(N, M)) % MOD + MOD) % MOD;

        std::cout << result << '\n';
    }

    std::cout << std::flush;

    return 0;
}
