//HZ - 31.6
//Luogu - P3622
#include<bits/stdc++.h>
using namespace std;
typedef unsigned int bitType;
constexpr int maxN = 1e4 + 5, maxC = 5e4 + 5;
constexpr bitType S = 1 << 5;
int N,C,ans(0);
int dp[maxN][S], sum[maxN][S];

void init();

int main(){
	init();
	
	for(bitType st = 0; st < S; ++st){
		memset(dp[0],128,sizeof(dp[0]));
		
		dp[0][st] = 0;
		
		for(int i = 1; i <= N; ++i)
			for(bitType s = 0; s < S; ++s)
				dp[i][s] = max(dp[i - 1][(s & 15) << 1], dp[i - 1][(s & 15) << 1|1]) + sum[i][s];
		
		ans = max(ans, dp[N][st]);
	}
		
	cout << ans;
	return 0;
}

void init(){
	memset(sum,0,sizeof(sum));
	
	cin >> N >> C;
	
	for(int i = 0; i < C; ++i){
		int e(0),f(0),l(0);
		bitType like(0),hate(0);
		cin >> e >> f >> l;
		
		while(f--){
			int t;
			cin >> t;
			like |= 1 << ((t - e + N) % N);
		}
		
		while(l--){
			int t;
			cin >> t;
			hate |= 1 << ((t - e + N) % N);
		}
		
		for(bitType s = 0; s < S; ++s)
			if(like & s || hate & ~s)
				++sum[e][s];
	}
}
