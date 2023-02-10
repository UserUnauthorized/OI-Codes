//HZ - 36.7
#include<bits/stdc++.h>
using namespace std;
constexpr int maxN = 5e4 + 5, maxM = 2e4 + 5, maxK = 105;
typedef int valueType;

array<valueType, maxN> belong, source;
array<array<valueType, maxM>, maxK> sum;
array<valueType, maxK> leftBound, rightBound;
array<valueType, maxM> cnt;
array<array<array<valueType, maxM>, maxK>, maxK> preAns;

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
	
	block_ = 1000;
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
	
	for(int j = 0; j < K; ++j)
		for(int color = 1; color <= M; ++color)
			preAns[0][j][color] = preAns[0][j][color - 1] + sum[j][color] * sum[j][color];
			
	for(int k = 1; k < K; ++k){
		for(int j = k; j < K; ++j){
			preAns[k][j] = preAns[k][j - 1];
			
			for(int i = leftBound[j]; i < rightBound[j]; ++i)
				++preAns[k][j][source[i]] += 2 * cnt[source[i]]++;			
		}
		
		for(int i = leftBound[k]; i < N; ++i)
			cnt[source[i]] = 0;
	}
	
	for(int k = 1; k < K; ++k)
		for(int j = k; j < K; ++j)
			for(int color = 2; color <= M; ++color)
				preAns[k][j][color] += preAns[k][j][color - 1];
}

Query decode(Query Object, int lastAns){
	return Query((Object.l ^ lastAns) - 1, (Object.r ^ lastAns) - 1, Object.a ^ lastAns, Object.b ^ lastAns);
}

valueType query(Query x){
	int const &l = x.l, &r = x.r, &a = x.a, &b = x.b;
	int ans(0);
	
	if(belong[r] - belong[l] < 2){
		for(int i = l; i <= r; ++i)
			if(a <= source[i] && source[i] <= b)
				++ans += 2 * cnt[source[i]]++;
				
		for(int i = l; i <= r; ++i)
			cnt[source[i]] = 0;
	} else {
		ans = preAns[belong[l] + 1][belong[r] - 1][b] - preAns[belong[l] + 1][belong[r] - 1][a - 1];

		for(int i = l; i < rightBound[belong[l]]; ++i){
			if(source[i] < a || b < source[i])
				continue;
			
			if(!cnt[source[i]])
				cnt[source[i]] = sum[belong[r] - 1][source[i]] - sum[belong[l]][source[i]];
				
			++ans += 2 * cnt[source[i]]++;
		}
				
		for(int i = leftBound[belong[r]]; i <= r; ++i){
			if(source[i] < a || b < source[i])
				continue;
			
			if(!cnt[source[i]])
				cnt[source[i]] = sum[belong[r] - 1][source[i]] - sum[belong[l]][source[i]];
				
			++ans += 2 * cnt[source[i]]++;
		}
		
		for(int i = l; i < rightBound[belong[l]]; ++i)
			cnt[source[i]] = 0;
		
		for(int i = leftBound[belong[r]]; i <= r; ++i)
			cnt[source[i]] = 0;
	}
	return ans;
}
