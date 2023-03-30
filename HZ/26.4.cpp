//HZ - 26.4
#include<bits/stdc++.h>

constexpr int maxN = 50;
constexpr int maxM = maxN * maxN;

typedef std::list<int> LIST;

int N_, T_;
int const &N = N_, &T = T_;

std::array<LIST, maxN << 1> edge;
std::array<int, maxN << 1> match;
std::bitset<maxN << 1> visited, nowClass, preClass;

bool dfs(int x);

void init();

int main(){
	std::cin >> T_;
	
	for(int i = 0; i < T; ++i){
		init();
	
		bool success = true;
	
		for(int i = 1; i <= N; ++i){
			if(!nowClass[i])
				continue;
			
			visited.reset();
		
			if(!dfs(i)){
				success = false;
				break;
			}
		}
	
		if(success)
			std::cout << "^_^\n";
		else
			std::cout << "T_T\n";
	}
}

void init(){
	std::cin >> N_;
	
	for(auto &iter : edge)
		iter.clear();
	
	match.fill(0);
	visited.reset();
	nowClass.reset();
	preClass.reset();
	
	for(int i = 1; i <= N; ++i){
		int t;
		
		std::cin >> t;
		
		preClass[i] = t > 0;
	}
	
	for(int i = 1; i <= N; ++i){
		int t;
		
		std::cin >> t;
		
		if(preClass[i])
			nowClass[i] = (t == 0);
		else
			nowClass[i] = true;
	}
	
	for(int i = 1; i <= N; ++i){
		if(nowClass[i] && preClass[i])
			edge[i].emplace_back(i);
		
		for(int j = 1; j <= N; ++j){
			int t;
			
			std::cin >> t;
			
			if(t == 1){
				if(nowClass[i] && preClass[j])
					edge[i].emplace_back(j);
				if(nowClass[j] && preClass[i])
					edge[j].emplace_back(i);
			}
		}
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
