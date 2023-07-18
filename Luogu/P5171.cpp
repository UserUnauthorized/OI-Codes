//Luogu - P5171
#include <bits/stdc++.h>

typedef long long valueType;

int main() {
	typedef std::function<valueType(valueType, valueType, valueType, valueType)> solveFunction;

    solveFunction solve = [&solve](valueType a, valueType b, valueType c, valueType n) -> valueType {
        auto const m = (valueType) (((__int128) a * n + b) / c);

		valueType result;

        if (a == 0) {
            result = (n + 1) * (b / c);

            return result;
        }

        if (a >= c || b >= c) {
            valueType const lastAns = solve(a % c, b % c, c, n);

            result = lastAns + n * (n + 1) / 2 * (a / c) + (n + 1) * (b / c);

            return result;
        }

        valueType const lastAns = solve(c, c - b - 1, a, m - 1);

        result = n * m - lastAns;

        return result;
    };

    valueType a, b, c;
    
    std::cin >> a >> b >> c;
    
    if(a > b)
    	std::swap(a, b);
    
    valueType const n = c / a;
    
    valueType const result = solve(b - a, c, b, c / a) - n * (n + 1) / 2 + n + 1;
    
    std::cout << result << std::endl;

    return 0;
}
