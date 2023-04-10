//HZ -  32.2
//Luogu - P2569
#include<bits/stdc++.h>

namespace DEBUG {
    template<typename T>
    inline void _debug(const char *format, T t) {
        std::cerr << format << '=' << t << std::endl;
    }

    template<class First, class... Rest>
    inline void _debug(const char *format, First first, Rest... rest) {
        while (*format != ',') std::cerr << *format++;
        std::cerr << '=' << first << ",";
        _debug(format + 1, rest...);
    }

    template<typename T>
    std::ostream &operator<<(std::ostream &os, const std::vector<T> &V) {
        os << "[ ";
        for (const auto &vv: V) os << vv << ", ";
        os << "]";
        return os;
    }
    
    std::ostream &operator<<(std::ostream &os, __int128 V) {
        if(V < 0){
        	os << '-';
        	V = -V;
		}
		
		if(V > 9)	
			os << V / 10;
		
		os << (int)(V % 10);
		
        return os;
    }

#define debug(...) _debug(#__VA_ARGS__, __VA_ARGS__)
}  // namespace DEBUG

using namespace DEBUG;

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
//	freopen("business.in", "r", stdin);
//	freopen("business.out", "w", stdout);
	
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
		
		for(int j = 0; j < BS; ++j) {
			valueType const tempA = maxS[j] + AP * j;
			valueType const tempB = maxS[j] + BP * j;
			
			while(!queA.empty() && queA.back().value < tempA)
				queA.pop_back();
			
			queA.emplace_back(j, tempA);
			
			while(!queB.empty() && queB.back().value < tempB)
				queB.pop_back();
			
			queB.emplace_back(j, tempB);
		}
		
		for(int j = BS; j <= MaxP; ++j) {
			valueType const tempA = maxS[j] + AP * j;
			
			while(!queA.empty() && queA.back().value < tempA)
				queA.pop_back();
			
			queA.emplace_back(j, tempA);
			
			int const t = j - BS;
			
			while(!queA.empty() && queA.front().pos < t - AS)
				queA.pop_front();
			
			valueType const tempOut = queA.front().value - AP * t;

			ans_ = std::max(ans, tempOut);
			
			if(maxS[t] < tempOut && (out[t].empty() || out[t].back().value < tempOut))
				out[t].emplace_back(i, tempOut);
		}
		
		for(int j = MaxP + 1; j <= MaxP + BS; ++j) {
			int const t = j - BS;
			
			while(!queA.empty() && queA.front().pos < t - AS)
				queA.pop_front();
			
			valueType const tempOut = queA.front().value - AP * t;

			ans_ = std::max(ans, tempOut);
			
			if(maxS[t] < tempOut && (out[t].empty() || out[t].back().value < tempOut))
				out[t].emplace_back(i, tempOut);
		}
		
		for(int j = MaxP + Bs; j > MaxP; --j) {
			int const t = j - BS;
			
			while(!queB.empty() && queB.front().pos <= t)
				queB.pop_front();
				
			valueType const tempOut = queB.front().value - BP * t;

			ans_ = std::max(ans, tempOut);
			
			if(maxS[t] < tempOut && (out[t].empty() || out[t].back().value < tempOut))
				out[t].emplace_back(i, tempOut);
		}
		
		for(int j = MaxP; j >= BS; --j) {
			valueType const tempB = maxS[j] + BP * j;
			
			while(!queB.empty() && queB.back().value < tempB)
				queB.pop_back();
			
			queB.emplace_back(j, tempB);
			
			int const t = j - BS;
			
			while(!queB.empty() && queB.front().pos <= t)
				queB.pop_front();
				
			valueType const tempOut = queB.front().value - BP * t;

			ans_ = std::max(ans, tempOut);
			
			if(maxS[t] < tempOut && (out[t].empty() || out[t].back().value < tempOut))
				out[t].emplace_back(i, tempOut);
		}
	}
	
	std::cout << ans;
	
	return 0;
}
