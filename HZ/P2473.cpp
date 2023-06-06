//HZ - 35.12
//Luogu - P2473
#include<bits/stdc++.h>

typedef int valueType;
typedef unsigned int bitType;
typedef long double realType;
typedef std::vector<valueType> ValueVector;
typedef std::vector<bitType> BitVector;
typedef std::vector<realType> RealVector;
typedef std::vector<RealVector> RealMatrix;

constexpr realType INF = INFINITY;

int main() {
	int N, K;

	std::cin >> K >> N;
	
	bitType const S = 1 << N;
	
	ValueVector P(N + 1, 0);
	
	BitVector limit(N + 1, 0);
	
	for(int i = 1; i <= N; ++i) {
		std::cin >> P[i];
		
		int t;
		
		std::cin >> t;
		
		while(t != 0) {
			limit[i] |= 1 << (t - 1);
			
			std::cin >> t;
		}
	}
	
	std::function<bool(bitType, bitType)> check = [] (bitType limit, bitType status) {
		return 	(~status & ~limit) == (~status);
	};
	
	RealMatrix dp(K + 2);
	
	for(int i = 1; i <= K + 1; ++i)
		dp[i].resize(S, 0);
	
	for(int i = K; i >= 1; --i)
		for(bitType j = 0; j < S; ++j)
			for(int k = 1; k <= N; ++k)
				if(check(limit[i], j))
					dp[i][j] += std::max(dp[i + 1][j], dp[i + 1][j | 1 << (k - 1)] + P[k]);
				else
					dp[i][j] += dp[i + 1][j];
					
	std::cout << std::setprecision(6) << std::fixed << (dp[1][0] / N) << std::flush;
	
	return 0;
}
