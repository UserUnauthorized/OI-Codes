//Luogu - UVA10656
#include<bits/stdc++.h>

typedef int valueType;
typedef std::vector<valueType> ValueVector;

int main() {
	valueType N;
	for(std::cin >> N; N > 0; std::cin >> N) {
		ValueVector result;
		
		for(int i = 0; i < N; ++i) {
			valueType v;
			
			std::cin >> v;
			
			if(v > 0)
				result.push_back(v);
		}
		
		if(result.empty())
			result.push_back(0);
			
		for(auto iter = result.begin(); iter != result.end(); ++iter)
			std::cout << *iter << " \n"[std::next(iter) == result.end()];
	}
	
	std::cout << std::flush;
	
	return 0;
}
