//Luogu - P5174
#include<bits/stdc++.h>

typedef long long valueType;
typedef std::vector<valueType> ValueVector;

constexpr valueType MOD = 1e9 + 7;

int main() {
	valueType R;
	
	std::cin >> R;
	
	valueType const N = std::floor(std::sqrt((long double)R));
	
	typedef std::function<valueType(valueType)> solveFunction;
	
	solveFunction sum = [](valueType n) -> valueType {
		static constexpr valueType Inv6 = 166666668;
		
		return n * (n + 1) % MOD * (2 * n + 1) % MOD * Inv6 % MOD;
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
