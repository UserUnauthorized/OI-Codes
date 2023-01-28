//HZ - 31.3
//Luogu - P2704
#include<bits/stdc++.h>
using namespace std;
constexpr int maxN = 102, maxS = 63;

struct STATUS{
	int id;
	unsigned int bit;
	unsigned int sum;
	
	STATUS():id(0),bit(0),sum(0){};
	STATUS(int _id_, unsigned int _bit_):id(_id_),bit(_bit_),sum(0){
		while(_bit_ > 0){
			if(_bit_ & 1)
				++this->sum;
			_bit_ >>= 1;
		}
	};
	
	bool operator&(const STATUS &Object) const{
		return (this->bit & Object.bit) == 0;
	}
};

vector<STATUS> status;

int n,m,cnt(0);
unsigned int ans(0);
unsigned int dp[4][maxS][maxS];
unsigned int limit[maxN];

inline void init();
inline bool check(unsigned int x, int row);

int main(){
	init();
	
	for(STATUS const &j : status)
		if(check(j.bit, 1))
			dp[1][j.id][0] = j.sum;
			
	for(STATUS const &j : status)
		if(check(j.bit, 2))
			for(STATUS const &x : status)
				if(check(x.bit, 1) && (x & j))
					dp[2][j.id][x.id] = max(dp[2][j.id][x.id], dp[1][x.id][0] + j.sum);
				
	
	for(int i = 3; i <= n; ++i){
		fill(&dp[i % 3][0][0], &dp[i % 3 + 1][0][0],0);
		for(STATUS const &j : status)
			if(check(j.bit, i))
				for(STATUS const &x : status)
					if((j & x) && check(x.bit, i - 1))
						for(STATUS const &y : status)
							if((x & y) && (j & y))
								dp[i % 3][j.id][x.id] = max(dp[i % 3][j.id][x.id], dp[(i - 1) % 3][x.id][y.id] + j.sum);
	}
			
	for(STATUS const &j : status)
		for(STATUS const &x : status)
			ans = max(ans, dp[n % 3][j.id][x.id]);
			
	cout << ans;
	return 0;	
}

void init(){
	memset(dp,0,sizeof(dp));
	memset(limit,0,sizeof(limit));

	cin >> n >> m;

	for(int i = 1; i <= n; ++i){
		for(int j = 0; j < m; ++j){
			char ch;
			cin >> ch;
			if(ch == 'H')
				limit[i] += 1 << j;
		}
	}
	
	const int S = 1 << m;
	for(int i = 0; i < S; ++i){
		if((i & (i << 2))||(i & (i << 1))) continue;
		status.emplace_back(cnt++,i);
	}
}

bool check(unsigned int x, int row) const {
	return (x & limit[row]) == 0;
}
