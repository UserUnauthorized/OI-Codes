//Luogu - P5174
#include<bits/stdc++.h>

typedef long long valueType;
typedef std::vector<valueType> ValueVector;

constexpr valueType MOD = 1e9 + 7;

class Inverse {
private:
    valueType size;

    ValueVector data;

public:
    explicit Inverse(valueType N) : size(N), data(N, 0) {
        data[1] = 1;

        for (valueType i = 2; i < N; ++i)
            data[i] = (long long) (MOD - MOD / i) * data[MOD % i] % MOD;
    }

    valueType operator()(valueType i) const {
        i %= MOD;

        if (i < size)
            return data[i];

        return (MOD - MOD / i) * operator()(MOD % i) % MOD;
    }
};

int main() {
	valueType R;
	
	std::cin >> R;
	
	valueType const N = std::floor(std::sqrt((long double)R));
	
	Inverse Inv(10);
	
	typedef std::function<valueType(valueType)> solveFunction;
	
	solveFunction sum = [&Inv](valueType n) -> valueType {
		return n * (n + 1) % MOD * (2 * n + 1) % MOD * Inv(6) % MOD;
	};
		
	valueType result = sum(N);
		
	for(valueType x = 1; x <= N; ++x) {
		valueType const T = std::floor(std::sqrt(R - x * x));
		
		result = (result + T * x % MOD * x % MOD + sum(T)) % MOD;
	}
	
	result = result * 4 % MOD;
	
	std::cout << result << std::endl;
	
	return 0;
}
