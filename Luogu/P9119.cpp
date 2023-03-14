//P9119
#include<bits/stdc++.h>
//using namespace std;
typedef long double valueType;
typedef unsigned int bitType;
constexpr int maxN = 20;
constexpr bitType maxS = (1 << 18) | 3;
constexpr double DMAX = 1e10;
typedef std::array<valueType, maxN> DoubleArray;
typedef std::array<valueType, maxS> DPArray;
typedef std::array<DoubleArray, maxN> DoubleMaritx;
typedef std::array<bitType, maxS> intArray;
typedef std::array<intArray, maxN> pathArray;


valueType distance(int a, int b);

int N_;
const int &N = N_;
DoubleArray X, Y;
DoubleMaritx weight;
pathArray path;
std::array<DPArray, maxN> dp;

int main(){
	std::cin >> N_;
	int K_ = 0;
	const int &K = K_;
	Y[0] = -DMAX; 
	
	for(int i = 1; i <= N; ++i){
		std::cin >> X[i] >> Y[i];
		
		if(Y[i] > Y[K])
			K_ = i;
	}
	
	for(int i = 1; i <= N; ++i){
		weight[i][i] = DMAX;
		
		for(int j = 1; j < i; ++j)
			weight[i][j] = weight[j][i] = distance(i, j);
	}
	
	for(int i = 1; i <= N; ++i)
		dp[i].fill(DMAX);
		
	dp[K][1 << (K - 1)] = 0;
	
	bitType const S = 1 << N;
	
	for (bitType i = 1; i < S; ++i) {
        for (int k = 1; k <= N; ++k) {
            if (~i & 1 << (k - 1)) continue;
            for (int x = 1; x <= N; ++x) {
                if ((x == k) || (~i & 1 << (x - 1))) continue;
                if(dp[k][i] > dp[x][i ^ (1 << (k - 1))] + weight[k][x]){
                	dp[k][i] = dp[x][i ^ (1 << (k - 1))] + weight[k][x];
                	path[k][i] = x;
				}
            }
        }
    }
    
    std::stack<int> out;
    
    std::pair<int, bitType> ans;
    valueType max = DMAX;
    
    ans.second = S - 1;
    
    for(int i = 1; i <= N; ++i)
    	if(dp[i][S - 1] < max)
    		max = dp[(ans.first = i)][S - 1];
    		
    for(int i = 0; i < N; ++i){
    	out.push(ans.first);
    	int now = ans.first;
    	ans.first = path[ans.first][ans.second];
    	ans.second ^= 1 << (now - 1);
	}
	
	while(!out.empty()){
		std::cout << out.top() << ' ';
		out.pop();
	}
	
	return 0;
}

valueType distance(int a, int b){
	return sqrt((X[a] - X[b]) * (X[a] - X[b]) + (Y[a] - Y[b]) * (Y[a] - Y[b]));
}
