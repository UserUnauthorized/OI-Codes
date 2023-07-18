//Luogu - P5221
#include<bits/stdc++.h>

typedef long long valueType;
typedef std::vector<valueType> ValueVector;

constexpr valueType MOD = 104857601;

class LineSieve {
public:
    typedef std::vector<valueType> container;
    typedef std::vector<bool> bitset;

private:
    valueType size;
    bitset isPrime;
    container primeList;
    container mobius;

public:
    explicit LineSieve(valueType _size_) : size(_size_), isPrime(_size_ + 1, true), mobius(_size_ + 1, 0){
        primeList.reserve((size_t) std::floor(std::log((long double) (_size_ + 1))));
        mobius[1] = 1;
        for (valueType i = 2; i <= size; ++i) {
            if (isPrime[i]) {
                primeList.push_back(i);
                mobius[i] = -1;
            }

            for (auto const &iter: primeList) {
                valueType const t = i * iter;

                if (t > size)
                    break;

                isPrime[t] = false;

                if (__builtin_expect(i % iter == 0, false)) {
                    mobius[t] = 0;

                    break;
                } else {
                    mobius[t] = -mobius[i];
                }
            }
        }

        std::partial_sum(mobius.begin(), mobius.end(), mobius.begin());
    }

    valueType Mobius(valueType n) const {
        if (n > size)
            throw std::range_error("Larger than Size.");

        if (n < 0)
            throw std::range_error("Too small.");

        return mobius[n];
    }
};

class Sum {
public:
    typedef LineSieve sieve;
    typedef std::unordered_map<valueType, valueType> memory;

private:
    valueType size, preSize;
    sieve preWork;
    memory mobiusMemory;

public:
    explicit Sum(valueType _size_) : size(_size_),
                                     preSize(std::ceil(std::pow<long double>((long double) size, (long double) 2 / 3))),
                                     preWork(preSize + 1) {};

    valueType Mobius(valueType n) {
        if (n <= preSize)
            return preWork.Mobius(n);

        if (mobiusMemory.find(n) != mobiusMemory.end())
            return mobiusMemory[n];

        valueType &ans = mobiusMemory[n];
        ans = 1;

        valueType l = 2, r;

        while (l <= n) {
            r = n / (n / l);

            ans -= (r - l + 1) * Mobius(n / l);

            l = r + 1;
        }

        return ans;
    }
};

int main() {
	valueType N;
	
	std::cin >> N;
	
	Sum Euler(N);
	
	typedef std::function<valueType(valueType, valueType)> powFunction;
	
	powFunction pow = [](valueType a, valueType b) -> valueType {
        valueType result = 1;

        while(b > 0) {
            if(b & 1)
                result = result * a % MOD;

            a = a * a % MOD;

            b = b >> 1;
        }

        return result;
    };
	
	typedef std::function<valueType(valueType)> solveFunction;
	
	solveFunction Inv = [&Inv](valueType n) -> valueType {
		if(__builtin_expect(n == 1, false))
			return 1;
			
		return (MOD - MOD / n) * Inv(MOD % n) % MOD;
	};
	
	solveFunction Func = [&Euler, &pow](valueType n) -> valueType {
		valueType result = 0, l = 1, r;
		
		while(l <= n) {
			r = n / (n / l);
			
			result = (result + (Euler.Mobius(r) - Euler.Mobius(l - 1)) * (n / l) % (MOD - 1) * (n / l)) % (MOD - 1);
			
			l = r + 1;
		}
		
		return result;
	};
	
	solveFunction solve = [&Func, &pow, &Inv](valueType n) -> valueType {
		valueType result = 1, l = 1, r;
		
		while(l <= n) {
			r = n / (n / l);
			
			valueType base = 1;
			
			for(valueType i = l; i <= r; ++i)
				base = base * i % MOD;
			
			result = result * pow(base,2 * (n - Func(n / l) + MOD - 1) % (MOD - 1)) % MOD;
			
			l = r + 1;
		}
		
		return (result % MOD + MOD) % MOD;
	};
	
	std::cout << solve(N) << std::endl;
	
	return 0;	
}
