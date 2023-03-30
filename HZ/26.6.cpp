//HZ - 26.6
#include<bits/stdc++.h>

constexpr int maxN = 305, maxK = 505;
constexpr int maxM = maxN * maxK;

typedef std::list<int> LIST;

int A_, B_, K_;
int const &A = A_, &B = B_, &K = K_;

std::array<LIST, maxK> edge;
std::array<int, maxK> match;
std::bitset<maxK> visited;
std::array<LIST, maxN> likeC, likeD, dislikeC, dislikeD;

bool dfs(int x);

void init();

int main(){
	init();
	
	int ans = 0;
	
	for(int i = 1; i <= K; ++i){
		visited.reset();
		
		if(dfs(i))
			++ans;
	}
	
	std::cout << ans;
}

void init(){
	std::cin >> A_ >> B_ >> K_;
	
	for(int i = 1; i <= K; ++i) {
		char likeChar, dislikeChar;
		int likeN, dislikeN;
		
		std::cin >> likeChar >> likeN >> dislikeChar >> dislikeN;
		
		if(likeChar == 'C') {
			likeC[likeN].emplace_back(i);
			dislikeD[dislikeN].emplace_back(i);
		} else {
			likeD[likeN].emplace_back(i);
			dislikeC[dislikeN].emplace_back(i);
		}
	}
	
	for(int i = 1; i <= A; ++i)
		for(auto like : likeC[i])
			for(auto dislike : dislikeC[i])
				edge[like].emplace_back(dislike);
				
				
	for(int i = 1; i <= B; ++i)
		for(auto like : likeD[i])
			for(auto dislike : dislikeD[i])
				edge[like].emplace_back(dislike);
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
