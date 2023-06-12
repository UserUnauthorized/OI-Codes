//Luogu - P7337
#include<bits/stdc++.h>

constexpr int maxN = 105;

std::bitset<maxN> A, B, C;

int main() {
	int N, M, type;
	
	std::cin >> N >> M >> type;
	
	for(int i = 1; i <= N; ++i) {
		int t;
		
		std::cin >> t;
		
		A[i] = t == 1;
	}
	
	for(int i = 1; i <= N; ++i) {
		int t;
		
		std::cin >> t;
		
		B[i] = t == 1;
	}
	
	C = A & B;
	
	int result = std::min(C.count(), (size_t)M);
	
	for(int i = 1; i <= N; ++i)
		if(!C[i])
			++result;
	
	std::cout << result << std::flush;
	
	return 0;
}
