//HZ -  32.2
//Luogu - P2569
#include<bits/stdc++.h>

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
		
		QUE que;
		
		for(int j = 0; j < BS; ++j) {
			valueType const temp = maxS[j] + BP * j;
			
			while(!que.empty() && que.back().value < temp)
				que.pop_back();
			
			que.emplace_back(j, temp);
		}
		
		for(int j = BS; j <= MaxP; ++j) {
			int const t = j - BS;
			
			while(!que.empty() && que.front().pos < t - AS)
				que.pop_front();
				
			valueType const tempOut = que.front().value - AP * t;
			valueType const temp = maxS[j] + BP * j;
			
			ans_ = std::max(ans, tempOut);
			
			if(maxS[t] < tempOut && (out[t].empty() || out[t].back().value < tempOut))
				out[t].emplace_back(i, tempOut);
				
			while(!que.empty() && que.back().value < temp)
				que.pop_back();
			
			que.emplace_back(j, temp);
		}
	}
	
	std::cout << ans;
	
	return 0;
}
