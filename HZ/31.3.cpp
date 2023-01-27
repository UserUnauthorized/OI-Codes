//HZ - 31.3
//Luogu - P2704
#include<bits/stdc++.h>
using namespace std;
constexpr int maxN = 102, maxS = 1 << 10, maxA = maxN << 2;

int n,m,cnt(0),zeroId(0);
unsigned long long ans(0);
bool dp[4][maxS][maxN * maxN];
const bool emptyDp[maxS][maxN * maxN]{};
unsigned int bit[maxS], sum[maxS], limit[maxS];

inline void init();
inline bool compatible(int x, int row);
inline bool compatible(int x, int y, int z);
inline bool check(unsigned int a,unsigned int b);
void dfs(int x, int num, int current);

int main(){
	init();

	for(int j = 1; j <= cnt; ++j) dp[1][j][sum[j]] = true;
	dp[0][zeroId][0] = true;
	
	for(int i = 2; i <= n; ++i){
		memset(dp[i % 3],0,sizeof(emptyDp));
		for(int j = 1; j<= cnt; ++j){
			if(!compatible(j, i)) continue;
			/*for(int x = 1; x <= cnt; ++x){
				for(int y = 1; y <= cnt; ++y){
					if(compatible(j,x,y)){
						for(int k = sum[j] + sum[x]; k <= maxA; ++k){
							dp[i % 3][j][k] |= dp[(i - 1) % 3][x][k - sum[j]] && dp[(i - 2) % 3][y][k - sum[j] - sum[x]];
						}
					}
				}
			}*/
			for(int x = 1; x <= cnt; ++x){
				if(!check(bit[j], bit[x])) continue;
				for(int k = sum[j] + sum[x]; k <= (i << 2); ++k){
					if(!dp[(i - 1) % 3][x][k - sum[j]]) continue;
					for(int y = 1; y <= cnt; ++y){
						if(compatible(j,x,y) && dp[(i - 2) % 3][y][k - sum[j] - sum[x]]){
							dp[i % 3][j][k] = true;
							break;
						}
					}
				}
			}
		}
	}
	
	for(int i = maxA; i >= 0; --i){
		for(int j = 1; j <= cnt; ++j){
			if(dp[n % 3][j][i]){
				cout << i;
				return 0;
			}
		}
	}
	return 0;			
}

void init(){
	memset(dp,0,sizeof(dp));
	memset(bit,0,sizeof(bit));
	memset(sum,0,sizeof(sum));
	memset(limit,0,sizeof(limit));

	cin >> n >> m;

	for(int i = 1; i <= n; ++i){
		for(int j = 0; j < m; ++j){
			char ch;
			cin >> ch;
			if(ch == 'P')
				limit[i] += 1 << j;
		}
	}

	dfs(0,0,0);
}

void dfs(int x,int num,int current){
	if(current >= m){
		bit[++cnt] = x;
		sum[cnt] = num;
		if(num == 0)
			zeroId = cnt;
		return;
	}
	
	dfs(x + (1 << current), num + 1, current + 3);
	dfs(x, num, current + 1);
	dfs(x, num, current + 2);
}

bool compatible(int x, int row){
	return check(bit[x], limit[row]);
}

bool compatible(int x, int y, int z){
	return check(bit[z], bit[y]) && check(bit[z], bit[x]);
}

bool check(unsigned int a,unsigned int b){
	return (a & (~b)) == a;
}
