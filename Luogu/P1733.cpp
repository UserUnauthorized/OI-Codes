//Luogu - P1733
#include<bits/stdc++.h>

int main() {
	int L = 1, R = 1e9;
	
	while(L <= R) {
		int const mid = (L + R) >> 1;
		
		std::cout << mid << std::endl;
		
		int result;
		
		std::cin >> result;
		
		if(result == 0)
			return 0;
		else if(result == 1)
			R = mid - 1;
		else if(result == -1)
			L = mid + 1;
	}
}
