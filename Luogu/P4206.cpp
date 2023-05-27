//HZ - 35.2
//Luogu - P4206
#include<bits/stdc++.h>

typedef long double realType;
typedef size_t sizeType;
typedef int valueType;

constexpr sizeType maxN = 1005;
constexpr realType INF = -INFINITY;
constexpr valueType MAX = INT_MAX >> 1;

class Graph{
public:
	typedef std::list<int> OutEdgeList;
	typedef std::vector<OutEdgeList> EdgeSet;
	typedef std::vector<valueType> distanceArray;
	typedef std::vector<distanceArray> distanceMatrix;

protected:
	sizeType N;
	EdgeSet edge;
	distanceMatrix dis;
	
public:
	Graph(sizeType _N_): N(_N_), edge(N + 1), dis(N + 1) {
		for(sizeType i = 1; i <= N; ++i)
			dis[i].resize(N + 1);
	};
	
	void addEdge(int u, int v) {
		edge[u].emplace_back(v);
	}
	
	void shuffle() {
		for(sizeType i = 1; i <= N; ++i)
			shuffle(edge[i]);
	}
	
	void calcDistance();
	
	valueType distance(int a, int b) const;
	
private:
	static void shuffle(OutEdgeList &list) {
		std::mt19937 engine(std::chrono::steady_clock::now().time_since_epoch().count());
		
		std::vector<int> bak(list.begin(), list.end());
		
		std::shuffle(bak.begin(), bak.end(), engine);
		
		list.assign(bak.begin(), bak.end());
	}
	
	static void calcDistance(sizeType u, distanceArray &dist) {
		typedef std::pair<valueType, int> Status;
		
		std::fill(dist.begin(), dist.end(), MAX);
		
		dist[u] = 0;
		
		std::priority_queue<Status, std::vector<Status>, std::greater<Status>> que;
		
		que.emplace(0, u);
		
		while(!que.empty()) {
			Status const top = que.top();
			que.pop();
			
			int const x = top.second;
			
		}
	}
};
