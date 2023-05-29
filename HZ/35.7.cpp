//HZ - 35.7
//Luogu - P1297
#include<bits/stdc++.h>

typedef long double realType;
typedef int valueType;

int main() {
	valueType N, A, B, C;
	
	std::cin >> N >> A >> B >> C;
	
	std::vector<valueType> source(N + 1, 0);
	
	std::cin >> source[1];
	
	for (int i = 2; i <= N; ++i)
		source[i] = ((long long) source[i - 1] * A + B) % 100000001;
	
	for (int i = 1; i <= N; ++i)
		source[i] = source[i] % C + 1;
		
	source[0] = source[N];
	
	realType ans = 0;
	
	for(int i = 1; i <= N; ++i)
		ans += std::min<realType>((realType)1, (realType)source[i] / (realType)source[i - 1]) * (realType)1 / (realType)(source[i]);
		
	std::cout << std::setprecision(3) << std::fixed << ans << std::flush;
	
	return 0;
}
