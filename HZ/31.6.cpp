//HZ - 31.6
//Luogu - P3622
#include<bits/stdc++.h>
using namespace std;
typedef unsigned int bitType;
typedef pair<int,bitType> dpType;
constexpr int maxN = 1e4 + 5, maxC = 5e4 + 5, STEP = 5;
constexpr bitType S = 1 << 5;
int N,C;
dpType dp[3][S];
int E[maxN], like[maxN], hate[maxN];
inline bitType intercept(bitType x, int l, int r);
inline bool check(bitType x, bitType likeCode, bitType hateCode);

void init();

int main(){
	init();
	
	const int K = ceil((double)N / (double)STEP);
	
	for(bitType i = 0; i < S; ++i){
		for(bitType x = 0; x < S; ++x){
			const int line = N - 4;
			int result(0);
				
			for(int j = C - 1; E[j] > line; --j)
				if (check(i, intercept(like[j], N + 2 - E[j], 5), intercept(hate[j], N + 2 - E[j], 5)) &&
					check(x, intercept(like[j], 0, N + 1 - E[j]), intercept(hate[j], 0, N + 1 - E[j])))
					++result;
				
		
			for(int j = 0; E[j] == 1; ++j)
				if(check(i, like[j], hate[j]))
					++result;
					
			if(result > dp[1][i]){
				dp[1][i].second = x;
				dp[1][i].first = result;
			}
		}
	}
	
	for(int k = 1; k < K; ++k){
		fill(&dp[k & 1][0][0], &dp[k & 1 + 1][0][0], 0);
		const int e = k * 5 + 1;
		const int start = distance(upper_bound(E, E + N, e - 5),E);
		const int likeCodePre = intercept(like[j], E[j] + 5 - e, 5);
		const int hateCodePre = intercept(hate[j], E[j] + 5 - e, 5));
		const int likeCodeNow = intercept(like[j], 0, e + 5 - E[j]);
		const int likeCodeNow = intercept(hate[j], 0, e + 5 - E[j]);
		for(bitType i = 0; i < S; ++i){
			for(bitType x = 0; x < S; ++x){
				for(int j = start; E[j] <= e; ++j){
					if(E[j] < e){
						if (check(i, intercept(like[j], E[j] + 5 - e, 5), intercept(hate[j], E[j] + 5 - e, 5)) &&
							check(x, intercept(like[j], 0, e + 5 - E[j]), intercept(hate[j], 0, e + 5 - E[j]))){
							
						}
					}
				}
			}
		}
	}
}

void init(){
	memset(dp, 0, sizeof(dp));
	memset(E, 0, sizeof(E));
	memset(like, 0, sizeof(like));
	memset(hate, 0, sizeof(hate));
	
	cin >> N >> C;
	
	for(int i = 0; i < C; ++i){
		cin >> E[i];
		int f, l;
		cin >> f >> l;
		
		while(f--){
			int t;
			cin >> t;
			like[i] |= 1 << (t - E[i]);
		}
		
		while(l--){
			int t;
			cin >> t;
			hate[i] |= 1 << (t - E[i]);
		}
	}
}

inline bitType intercept(bitType x, int l, int r){
	return (x ^ (x >> l << l) >> (r - 1));
}

inline bool check(bitType x, bitType likeCode, bitType hateCode){
	return ((likeCode & x) > 0) && ((hateCode & x) != hateCode);
}
