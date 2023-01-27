//HZ - 31.1
#include<bits/stdc++.h>
using namespace std;
constexpr int maxn = 22,maxs = 1 << 20 | 3;

int n,m;
array<int,maxn> allow;
array<unsigned long long,maxs> dp;

void init();
inline int lowBit(int x);
inline int getSum(int x);

int main(){
	init();
	
	const int S = 1 << n;
	
	for(int i = 1; i < S; ++i){
		const int limit = allow[getSum(i)];
		for(int j = i; j; j -= lowBit(j))
			if(!(limit & lowBit(j)))
				dp[i] += dp[i ^ lowBit(j)];
	}
	
	cout << dp[S - 1];
	return 0;
}

void init(){
	cin >> n >> m;
	
	while(m--){
		int x,y;
		cin >> x >> y;
		allow[x] |= 1 << (y - 1);
	}
	
	dp[0] = 1;
}

inline int lowBit(int x){
	return x & -x;	
}

inline int getSum(int x){
	int result(0);
	for(int i = x; i; i -= lowBit(i))
		++result;
	return result;
}
