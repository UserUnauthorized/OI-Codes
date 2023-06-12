//Luogu - P1192
#include<bits/stdc++.h>

typedef long long valueType;
constexpr valueType MOD = 100003;

typedef std::vector<valueType> ValueVector;

int main() {
	valueType N, K;
	
	std::cin >> N >> K;
	
	ValueVector dp(N + 300, 0);
	
	dp[0] = 1;
	
	for(int i = 1; i < K; ++i)
		for(int j = 0; j < i; ++j)
			dp[i] = (dp[i] + dp[j]) % MOD;

	for(int i = K; i <= N; ++i)
		for(int j = 1; j <= K; ++j)
			dp[i] = (dp[i] + dp[i - j]) % MOD;
			
	std::cout << dp[N] << std::flush;
	
	return 0;
}
