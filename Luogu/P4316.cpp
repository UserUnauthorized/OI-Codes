//HZ - 35.1
//Luogu - P4316
#include <bits/stdc++.h>

typedef std::pair<int, int> EDGE;

int main() {
	int N, M;
	
	std::cin >> N >> M;
	
	std::vector<std::list<EDGE>> edge(N + 1);
	std::vector<int> degree(N + 1, 0);
	
	std::function<void(int, int, int)> addEdge = [&edge, &degree](int u, int v, int w) mutable {
		edge[v].emplace_back(u, w);
		++degree[u];
	};
	
	for(int i = 0; i < M; ++i) {
		int u, v, w;
		
		std::cin >> u >> v >> w;
		
		addEdge(u, v, w);
	}
}
