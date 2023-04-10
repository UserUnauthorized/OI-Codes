//HZ -  32.2
//Luogu - P2569
#include<bits/stdc++.h>

constexpr int maxN = 2023;

typedef int valueType;

constexpr valueType MIN = INT_MIN >> 1, MAX = INT_MAX >> 1;

valueType T_, MaxP_, W_;
valueType const &T = T_, &MaxP = MaxP_, &W = W_;

struct STATUS {
	int pos;
	valueType value;
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
		valueType AP_, BP_, AS_, BS_, len_;
		valueType const &AP = AP_, &BP = BP_, &AS = AS_, &BS = BS_, &len = len_;
		
		std::cin >> AP_ >> BP_ >> AS_ >> BS_;
		
		len_ = AS + BS;
		
		for(int j = 0; j <= MaxP; ++j) {
			while(!out[j].empty() && out[j].front().pos < i - W){
                maxS[j] = out[j].front().value;
                out[j].pop_front();
            }
		}
		
		QUE que;
		
		for(int j = 0; j <= MaxP; ++j) {
			while(!que.empty() && que.front().pos < j - AS)
				que.pop_front();
			
			
		}
	}
}
