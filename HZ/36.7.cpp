//HZ - 36.7
#include<bits/stdc++.h>
using namespace std;
constexpr int maxN = 5e4 + 5, maxM = 2e4 + 5, maxK = sqrt(maxN) + 5;
typedef int valueType;
array<valueType, maxN> belong, source;
array<array<valueType, maxM>, maxK> sum;
array<valueType, maxK> leftBound, rightBound;

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
inline bool check(int l, int r, int color);

int main(){
	init();
}

void init(){
	cin >> N_ >> M_ >> Q;
	
	block_ = sqrt(N);
	K_ = ceil((double)N / (double)block);
	
	for(int i = 0/* TAG:ÏÂ±ê0¿ª */; i < N; ++i){
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
}

Query decode(Query Object, int lastAns){
	return Query(Object.l ^ lastAns, Object.r ^ lastAns, Object.a ^ lastAns, Object.b ^ lastAns);
}

valueType query(Query x){
	int const &l = x.l, &r = x.r, &a = x.a, &b = x.b;
	int ans(0);
	
	if(belong[r] - belong[l] < 2){
		for(int c = a; i <= b; ++i){
			if(!check(l, r, c)) 
				continue;
			
			int cnt(0);
			for(int i = l; i <= r; ++i){
				if(source[i] == c)
					++cnt;
			}
			
			ans += cnt * cnt;
		}
	}
}

inline bool check(int l, int r, int color){
	return (sum[belong[r]][color] - sum[max(belong[l] - 1, 0)][color]) > 0;
}
