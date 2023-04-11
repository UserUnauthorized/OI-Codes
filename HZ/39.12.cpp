//HZ - 39.12
//Luogu - P3258
#include<bits/stdc++.h>

constexpr int maxN = 3e5 + 5;

struct QUERYEDGE{
	int from;
	int to;
	int next;
	int LCA;
	
	QUERYEDGE():from(0), to(0), next(0), LCA(-1){};
	
	QUERYEDGE(int _from_, int _to_, int _next_):from(_from_), to(_to_), next(_next_){};
};

typedef std::list<int> EDGE;

int N_;
int const &N = N_;

std::array<int, maxN> ans, father, source, queryHead, parent;
std::array<EDGE, maxN> edge;
std::array<QUERYEDGE, maxN << 1> queryEdge;
std::bitset<maxN> visited;

void init();
void tarjan(int x);
void calc(int x);
int find(int x);

int main() {
	init();
	
	tarjan(1);
	
	for(int i = 2; i <= N; ++i){
		++ans[source[i - 1]];
		++ans[source[i]];
		--ans[queryEdge[i << 1].LCA];
		--ans[father[queryEdge[i << 1].LCA]];
	}
	
	calc(1);
	
	for(int i = 2; i <= N; ++i)
		--ans[source[i]];
		
	for(int i = 1; i <= N; ++i)
		std::cout << ans[i] << " \n"[i != N];
		
	return 0;
}

void init() {
	std::cin >> N_;
	
	std::cin >> source[1];
	for(int i = 2; i <= N; ++i){
		std::cin >> source[i];
		
		int const a = source[i - 1], b = source[i];
		
		queryEdge[i << 1] = QUERYEDGE(a, b, queryHead[a]);
		queryEdge[i << 1|1] = QUERYEDGE(b, a, queryHead[b]);
		
		queryHead[a] = i << 1;
		queryHead[b] = i << 1|1;
	}
	
	for(int i = 1; i < N; ++i){
		int a, b;
		std::cin >> a >> b;
		
		edge[a].emplace_back(b);
		edge[b].emplace_back(a);
	}
}

void tarjan(int x) {
	parent[x] = x;
	visited[x] = true;
	
	for(auto iter : edge[x]) {
		if(!visited[iter]) {
			tarjan(iter);
			father[iter] = parent[iter] = x;
		}
	}
	
	
	for (int i = queryHead[x]; i; i = queryEdge[i].next) {
        if (visited[queryEdge[i].to]) {
            queryEdge[i ^ 1].LCA = queryEdge[i].LCA = find(queryEdge[i].to);
        }
    }
}

void calc(int x) {
	for(auto iter : edge[x]) {
		if(iter == father[x])
			continue;
			
		calc(iter);
		
		ans[x] += ans[iter];
	}
}

int find(int x) {
	if(parent[x] == x)	return x;
	else return parent[x] = find(parent[x]);
}
