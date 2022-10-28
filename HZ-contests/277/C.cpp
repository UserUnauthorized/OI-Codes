//HZ - 277.3
#include<bits/stdc++.h>
using namespace std;
const int maxn = 50004,maxm = 54;
inline int read();
inline void write(int *);
inline int F(const int);
inline void init();
int T,n,m,dp[maxn][maxm],score[maxn],minScore[maxn];

int main() {
	T = read();
	while(T--) {
		init();
		for(int i = 1; i <=n - 4 * m ; ++i)
			dp[i][0] = dp[i - 1][0] + score[i] * (1 + F(i-1));
		for(int M = 1; M <= m; ++M) {
			for(int i = 4 * M - 1; i <= n - 4 * (m - M); ++i) {
				for(int j = 4 * (M - 1) - 1; j <= i; ++j) {
					int t;
					for(int k = j; k<=i; ++j) {
						
					}
				}
			}
		}
	}
}

inline int read() {
	int result(0),ch(getchar());
	bool positive(true);
	while((ch < '0' || ch > '9') && ch != '-')
		ch = getchar();
	if(ch == '-') {
		positive = false;
		ch = getchar();
	}
	while(ch >= '0' && ch <= '9') {
		result = (result << 3) + (result << 1) + (ch ^ 48);
		ch = getchar();
	}
	if(positive)
		return result;
	else
		return -result;
}

inline void write(int *) {
	int ch(getchar());
	bool positive(true);
	while((ch < '0' || ch > '9') && ch != '-')
		ch = getchar();
	if(ch == '-') {
		positive = false;
		ch = getchar();
	}
	while(ch >= '0' && ch <= '9') {
		*result = (*result << 3) + (*result << 1) + (ch ^ 48);
		ch = getchar();
	}
	if(!positive)
		*result = -*result;
}

inline int F(const int x) {
	if(x == 0)
		return 0;
	else if(x == 1)
		return 1;
	else if(x == 2)
		return 2;
	else if(x == 3)
		return 3;
	else
		return 8;
}
inline void init() {
	memset(dp,0,sizeof(dp));
	memset(score,0,sizeof(score));
	memset(minScore,0x7f,sizeof(minScore));

	n = read();
	m = read();

	for(int i=1; i<=n; ++i) {
		int k;
		k = read();
		for(int j=0; j<k; ++j) {
			int t(read());
			score[i] += t;
			minScore[i] = min(minScore[i],t);
		}
	}
}
