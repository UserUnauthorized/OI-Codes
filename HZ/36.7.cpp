//HZ - 36.7
#include<bits/stdc++.h>
using namespace std;
constexpr int maxN = 5e4 + 5, maxM = 2e4 + 5, maxK = sqrt(maxN) + 5;
typedef int valueType;

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

#define debug(...) _debug(#__VA_ARGS__, __VA_ARGS__)
}  // namespace DEBUG

using namespace DEBUG;

array<valueType, maxN> belong, source;
array<array<valueType, maxM>, maxK> sum;
array<valueType, maxK> leftBound, rightBound;
array<valueType, maxM> cnt;
array<array<valueType, maxK>, maxM> preAns;

struct Query{
	int l;
	int r;
	int a;
	int b;
	
	Query():l(-1), r(-1), a(-1), b(-1){};
	Query(int _l_, int _r_, int _a_, int _b_):l(_l_), r(_r_), a(_a_), b(_b_){};
};

int N_, M_, block_, K_, Q;
const int &N = N_, &M = M_, &block = block_, &K = K_;

void init();
Query decode(Query Object, int lastAns);
valueType query(Query x);

int main(){
	init();
	int lastAns(0);
	while(Q--){
		int l, r, a, b;
		cin >> l >> r >> a >> b;
		cout << (lastAns = query(decode(Query(l, r, a, b), lastAns))) << '\n';
	} 
	return 0;
}

void init(){
	cin >> N_ >> M_ >> Q;
	
	block_ = sqrt(N);
	K_ = ceil((double)N / (double)block);
	
	for(int i = 0; i < N; ++i){
		cin >> source[i];
		belong[i] = i / block;
	}
	
	for(int k = 0 ; k < K; ++k)
		rightBound[k] = (leftBound[k] = k * block) + block;
		
	rightBound[K - 1] = N;
	
	for(int k = 0; k < K; ++k){
		if(k > 0)
			sum[k] = sum[k - 1];
			
		for(int i = leftBound[k]; i < rightBound[k]; ++i)
			++sum[k][source[i]];
	}
	
	for(int k = 0; k < K; ++k)
		for(int color = 1; color <= M; ++color)
			preAns[k][color] = preAns[k][color - 1] + sum[k][color] * sum[k][color];
}

Query decode(Query Object, int lastAns){
	return Query((Object.l ^ lastAns) - 1, (Object.r ^ lastAns) - 1, Object.a ^ lastAns, Object.b ^ lastAns);
}

valueType query(Query x){
	int const &l = x.l, &r = x.r, &a = x.a, &b = x.b;
	debug(l, r, a, b);
	int ans(0);
	cnt.fill(0);
	
	if(belong[r] - belong[l] < 2){
		for(int i = l; i <= r; ++i)
			if(a <= source[i] && source[i] <= b)
				++ans += 2 * cnt[source[i]]++;
	} else {
		int ansR = (preAns[belong[r] - 1][b] - preAns[belong[r] - 1][a - 1]) * (preAns[belong[r] - 1][b] + preAns[belong[r] - 1][a - 1]);
		int ansL = (preAns[belong[l]][b] - preAns[belong[l]][a - 1]) * (preAns[belong[l]][b] + preAns[belong[l]][a - 1]);
		ans = (ansL + ansR) * (ansR - ansL);

		for(int i = l; i < rightBound[belong[l]]; ++i)
			if(a <= source[i] && source[i] <= b)
				++ans += 2 * (sum[belong[r] - 1][source[i]] - sum[belong[l]][source[i]] + cnt[source[i]]++);
				
		for(int i = leftBound[belong[r]]; i <= r; ++i)
			if(a <= source[i] && source[i] <= b)
				++ans += 2 * (sum[belong[r] - 1][source[i]] - sum[belong[l]][source[i]] + cnt[source[i]]++);
	}
	
	return ans;
}
