//Luogu - P9390
#include<bits/stdc++.h>

constexpr long long N = 1e6, M = 1e11;

int main() {
	long long Y, Z;
	
	std::cin >> Y >> Z;
	
	if(Z >= M) {
		Z %= N;
	
		std::cout << std::min(std::abs(Y - Z), std::abs(N - Y + Z)) << std::flush;
	} else {
		std::cout << M - Z + Y << std::flush;
	}

	return 0;
}
