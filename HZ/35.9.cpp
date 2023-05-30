//HZ - 35.9
#include<bits/stdc++.h>

typedef long double realType;
typedef int valueType;

int main() {
	valueType K, W, H;
	
	std::cin >> K >> W >> H;
	
	std::function<realType(valueType, valueType)> P = [W, H] (valueType i, valueType j) -> realType {
		valueType result = 0;
		
		valueType const base = W * H * W * H;
		
		result += 4 * (i - 1) * (j - 1) * (W - i) * (H - j);
	
		result += 4 * W * H;
		
		result += 2 * (i - 1) * (W - i);
		
		result += 2 * (j - 1) * (H - j);
		
		result -= 3;
		
		return (realType)result / base;
	};
	
	realType ans = 0;
	
	for(int i = 1; i <= W; ++i)
		for(int j = 1; j <= H; ++j)
			ans += std::pow<realType>(1 - P(i, j), K);
	
	ans = (realType)(W * H) - ans;
	
	std::cout << std::setprecision(0) << std::fixed << ans << std::flush;
	
	return 0;
}
