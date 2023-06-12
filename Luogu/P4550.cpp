//Luogu - P4550
#include<bits/stdc++.h>

typedef long double realType;
typedef std::vector<realType> realVector;

int main() {
	int N;
	
	std::cin >> N;
	
	realVector F(N + 1, 0), G(N + 1, 0);
	
	F[N] = 0;
	G[N] = 0;
	
	for(int i = N - 1; i >= 0; --i) {
		F[i] = F[i + 1] + (realType) N / (N - i);
		G[i] = (realType) i / (N - i) * F[i] + G[i + 1] + F[i + 1] + (realType) N / (N - i);
	}
	
	std::cout << std::setprecision(2) << std::fixed << G[0] << std::flush;
	
	return 0;
}
