//Luogu - P5172
#include<bits/stdc++.h>

typedef long long valueType;
typedef long double realType;

int main() {
	typedef std::function<valueType(valueType, valueType, valueType, valueType, valueType)> solveFunction;

    solveFunction solve = [&solve](valueType a, valueType b, valueType c, valueType n, valueType r) -> valueType {
        valueType const gcd = std::__gcd(a, std::__gcd(b, c));
		
		if(gcd > 1) {
			a /= gcd;
			b /= gcd;
			c /= gcd;
		}
		
		realType const t = ((realType)a * std::sqrt((realType)r) + b) / (realType)c;

        if (n == 0)
            return 0;

        if(t > 1) {
        	valueType const alpha = std::floor(t);
        	
        	valueType const result = n * (n + 1) / 2 * alpha + solve(a, b - c * alpha, c, n, r);
        	
        	return result;
		} else {
			valueType const m = std::floor((realType)n * t);
			
			valueType const result = n * m - solve(c * a, -c * b, a * a * r - b * b, m, r);
			
			return result;
		}
    };
    
    valueType T;
    
    std::cin >> T;
    
    for(valueType i = 0; i < T; ++i) {
    	valueType N, R;
    	
    	std::cin >> N >> R;
    	
    	valueType const x = std::floor(std::sqrt((realType)R));

    	if(x * x == R) {
    		if(x & 1) {
    			if(N & 1) {
    				std::cout << -1 << '\n';
				} else {
					std::cout << 0 << '\n';
				}
			} else {
				std::cout << N << '\n';
			}
		} else {
			valueType const result = N - 2 * solve(1, 0, 1, N, R) + 4 * solve(1, 0, 2, N, R);
			
			std::cout << result << '\n';
		}
	}
}
