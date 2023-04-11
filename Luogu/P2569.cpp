//HZ -  32.2
//Luogu - P2569
#include <bits/stdc++.h>

constexpr int maxN = 2023;

typedef int valueType;

constexpr valueType MIN = INT_MIN >> 1, MAX = INT_MAX >> 1;

valueType T_, MaxP_, W_, ans_ = INT_MIN;
valueType const &T = T_, &MaxP = MaxP_, &W = W_, &ans = ans_;

struct STATUS {
	int pos;
	valueType value;
	
	STATUS():pos(0), value(MIN){};
	STATUS(int _pos_, valueType _value_):pos(_pos_), value(_value_){};
};

typedef std::deque<STATUS> QUE;

std::array<valueType, maxN> maxS, dp;

std::array<QUE, maxN> out;

int main() {
	std::cin >> T_ >> MaxP_ >> W_;
	
	maxS.fill(MIN);
	dp.fill(MIN);
	
	maxS[0] = dp[0] = 0;
	
	for(int i = 1; i <= T; ++i) {
		valueType AP_, BP_, AS_, BS_;
		valueType const &AP = AP_, &BP = BP_, &AS = AS_, &BS = BS_;
		
		std::cin >> AP_ >> BP_ >> AS_ >> BS_;
		
		for(int j = 0; j <= MaxP; ++j) {
			while(!out[j].empty() && out[j].front().pos < i - W){
                maxS[j] = out[j].front().value;
                out[j].pop_front();
            }
		}
		
		QUE queA, queB;
		
		for(int j = 0; j <= MaxP; ++j) {
			valueType const tempA = maxS[j] + AP * j;
			
			while(!queA.empty() && queA.back().value < tempA)
				queA.pop_back();
			
			queA.emplace_back(j, tempA);
			
			while(!queA.empty() && queA.front().pos < j - AS)
				queA.pop_front();
			
			if(queA.empty())
				continue;
				
			valueType const tempOut = queA.front().value - AP * j;

			ans_ = std::max(ans, tempOut);
			
			if(maxS[j] < tempOut && (out[j].empty() || out[j].back().value < tempOut))
				out[j].emplace_back(i, tempOut);
		}
		
		for(int j = MaxP; j >= 0; --j) {
			valueType const tempB = maxS[j] + BP * j;
			
			while(!queB.empty() && queB.back().value < tempB)
				queB.pop_back();
			
			queB.emplace_back(j, tempB);
			
			while(!queB.empty() && queB.front().pos > j + BS)
				queB.pop_front();
			
			if(queB.empty())
				continue;
			
			valueType const tempOut = queB.front().value - BP * j;

			ans_ = std::max(ans, tempOut);
			
			if(maxS[j] < tempOut && (out[j].empty() || out[j].back().value < tempOut))
				out[j].emplace_back(i, tempOut);
		}
	}
	
	std::cout << ans;
	
	return 0;
}
