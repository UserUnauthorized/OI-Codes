//HZ - 26.3
#include<bits/stdc++.h>

constexpr int maxN = 1020;
constexpr int maxM = maxN;

typedef std::list<int> LIST;

int N_, M_, T_;
int const &N = N_, &M = M_, &T = T_;

std::array<LIST, maxN> edge;
std::array<int, maxM> match;
std::bitset<maxN> visited;
std::array<long double, maxN> transferX, transferY, peopleX, peopleY, speed;

bool dfs(int x);

void init();

long double distance(int people, int transfer);

int main(){
	init();
	
	int ans = 0;
	
	for(int i = 1; i <= N; ++i){
		visited.reset();
		
		if(dfs(i))
			++ans;
	}
	
	std::cout << ans << '\n';
	
	return 0;
}

void init(){
	std::cin >> N_ >> M_ >> T_;
	
	for(int i = 1; i <= M; ++i)
		std::cin >> transferX[i] >> transferY[i];
	
	for(int i = 1; i <= N; ++i){
		std::cin >> peopleX[i] >> peopleY[i] >> speed[i];
		
		for(int j = 1; j <= M; ++j)
			if(distance(i, j) <= speed[i] * (long double)T)
				edge[i].emplace_back(j);
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

long double distance(int people, int transfer){
	return std::sqrt(std::pow(transferX[transfer] - peopleX[people], 2) + std::pow(transferY[transfer] - peopleY[people], 2));
}
