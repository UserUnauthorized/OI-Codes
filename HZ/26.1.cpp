//HZ - 26.1
//Luogu - P7368
#include<bits/stdc++.h>

constexpr int maxN = 505;
constexpr int maxM = maxN * maxN;

typedef std::list<int> LIST;

int N_, K_;
int const &N = N_, &K = K_;

std::array<LIST, maxN << 1> edge;
std::array<int, maxN << 1> match;
std::bitset<maxN << 1> visited;

bool dfs(int x);

void init();

int main(){
	init();
	
	int ans = 0;
	
	for(int i = 1; i <= N; ++i){
		visited.reset();
		
		if(dfs(i))
			++ans;
	}
	
	std::cout << ans;
}

void init(){
	std::cin >> N_ >> K_;
	
	for(int i = 0; i < K; ++i){
		int x, y;
		
		std::cin >> x >> y;
		
		edge[x].emplace_back(y + N);
		edge[y + N].emplace_back(x);
	}
}

bool dfs(int x){
	for(auto iter : edge[x]){
		if(!visited[iter]){
			visited[iter] = true;
			
			if(!match[iter] || dfs(match[iter])){
				match[iter] = x;
				return true;
			}
		}
	}
	
	return false;
}
