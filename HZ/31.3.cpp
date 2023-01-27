//HZ - 31.3
//Luogu - P2704
#include<bits/stdc++.h>
using namespace std;
constexpr int maxN = 102, maxS = 100;

struct STATUS{
	int id;
	unsigned int bit;
	unsigned int sum;
	
	STATUS():id(0),bit(0),sum(0){};
	STATUS(int _id_, unsigned int _bit_):id(_id_),bit(_bit_),sum(0){
		while(_bit_ > 0){
			if(_bit_ & 1)
				++this->sum;
		}
	};
	
	bool operator&(const STATUS &Object) const{
		return this->bit & Object.bit == 0;
	}
};

vector<STATUS> status;

int n,m,cnt(0);
unsigned int ans(0);
unsigned int dp[4][maxS][maxS];
const bool emptyDp[maxS][maxS]{};
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
				dp[2][x.id][j.id] = (j & x) ? j.sum + x.sum : 0;
	
	for(int i = 3; i <= n; ++i){ 
		memset(dp[i % 3],0,sizeof(emptyDp));
		
		for(STATUS const &j : status)
			if(check(j.bit, i))
				for(STATUS const &x : status)
					if(j & x)
						for(STATUS const &y : status)
							if(x & y && j & y)
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
		if((i & (i << 2))||(i & (i << 1))||(i & (i >> 1))||(i & (i >> 2))) continue;
		status.emplace_back(i,cnt++);
	}
}

bool check(unsigned int x, int row){
	return (x & limit[row]) == 0;
}
