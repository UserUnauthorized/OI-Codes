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
	
	void addEdge(int a, int b) {
		edge[a].emplace_back(b);
		edge[b].emplace_back(a);
	}
	
	void shuffle() {
		for(sizeType i = 1; i <= N; ++i)
			shuffle(edge[i]);
	}
	
	void calcDistance() {
		for(sizeType i = 1; i <= N; ++i)
			calcDistance(i, dis[i]);
	}
	
	valueType distance(int a, int b) const {
		return dis[a][b];
	}
	
	const EdgeSet &data() const {
		return edge;
	}
	
private:
	static void shuffle(OutEdgeList &list) {
		std::mt19937 engine(std::chrono::steady_clock::now().time_since_epoch().count());
		
		std::vector<int> bak(list.begin(), list.end());
		
		std::shuffle(bak.begin(), bak.end(), engine);
		
		list.assign(bak.begin(), bak.end());
	}
	
	void calcDistance(sizeType u, distanceArray &dist) {
		typedef std::pair<valueType, int> Status;
		
		std::vector<bool> visited(N + 1, false);
		
		std::fill(dist.begin(), dist.end(), MAX);
		
		dist[u] = 0;
		visited[u] = true;
		
		std::priority_queue<Status, std::vector<Status>, std::greater<Status>> que;
		
		que.emplace(0, u);
		
		while(!que.empty()) {
			Status const top = que.top();
			que.pop();
			
			int const x = top.second;
			
			if(visited[x])
				continue;
			
			visited[x] = true;
			
			for(auto &iter : edge[x]) {
				if(dist[iter] > dist[x] + 1) {
					dist[iter] = dist[x] + 1;
					
					if(!visited[iter])
						que.emplace(dist[iter], iter);
				}
			}
		}
	}
};

typedef std::function<valueType(int, int)> DistanceFunction;
typedef Graph::EdgeSet EdgeSet; 

std::vector<std::vector<int>> path;

std::vector<std::vector<realType>> memory;

realType dfs(sizeType c, sizeType m, const DistanceFunction &distance);

void calcPath(int c, int m, const DistanceFunction &distance, const EdgeSet &edge);

int main() {
	int N, E, C, M;
	
	std::cin >> N >> E >> C >> M;
	
	memory.resize(N + 1);
	
	for(int i = 1; i <= N; ++i)
		memory[i].resize(N + 1, INF);
	
	Graph G(N);
	
	for(int i = 0; i < E; ++i) {
		int a, b;
		
		std::cin >> a >> b;
		
		G.addEdge(a, b);
	}
	
	G.shuffle();
	
	G.calcDistance();
	
	DistanceFunction distance = [&G] (int a, int b) -> valueType {
		return G.distance(a, b);
	};
	
	realType const ans = dfs(C, M, distance);
}

realType dfs(sizeType c, sizeType m, const DistanceFunction &distance) {
	if(memory[c][m] != INF)
		return memory[c][m];
		
	if(c == m)
		return memory[c][m] = 0;
		
	if(distance(c, m) <= 2)
		return memory[c][m] = 1;
		
	
}

void calcPath(int c, int m, const DistanceFunction &distance, const EdgeSet &edge) {
	if(c == m)
		return;
		
	if(distance(c, m) <= 2)
		return;
		
	int to1 = 0;
	
	
}
