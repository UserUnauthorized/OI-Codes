//HZ - 35.2
//Luogu - P4206
#include<bits/stdc++.h>

namespace DEBUG {
    template<typename T>
    inline void _debug(const char *format, T t) {
        std::cerr << format << '=' << t << std::endl;
    }

    template<class First, class... Rest>
    inline void _debug(const char *format, First first, Rest... rest) {
        while (*format != ',') std::cerr << *format++;
        std::cerr << '=' << first << ",";
        _debug(format + 1, rest...);
    }

    template<typename T>
    std::ostream &operator<<(std::ostream &os, const std::vector<T> &V) {
        os << "[ ";
        for (const auto &vv: V) os << vv << ", ";
        os << "]";
        return os;
    }

    std::ostream &operator<<(std::ostream &os, __int128 V) {
        if (V < 0) {
            os << '-';
            V = -V;
        }

        if (V > 9)
            os << V / 10;

        os << (int) (V % 10);

        return os;
    }

#define debug(...) _debug(#__VA_ARGS__, __VA_ARGS__)
}  // namespace DEBUG

using namespace DEBUG;

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
	Graph(sizeType _N_): N(_N_), edge(_N_ + 1), dis(_N_ + 1) {
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
			calcDis(i, dis[i]);
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
	
	void calcDis(sizeType u, distanceArray &dist) {
		typedef std::pair<valueType, int> Status;
		
		std::vector<bool> visited(N + 1, false);
		
		std::fill(dist.begin(), dist.end(), MAX);
		
		dist[u] = 0;
		
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

typedef Graph::EdgeSet EdgeSet; 
typedef const Graph::OutEdgeList& EdgeReference;
typedef std::function<valueType(int, int)> DistanceFunction;
typedef std::function<EdgeReference(int)> EdgeFunction;

std::vector<std::vector<int>> path;

std::vector<std::vector<realType>> memory;

realType dfs(sizeType c, sizeType m, const DistanceFunction &distance, const EdgeFunction &edge);

void calcPath(int c, int m, const DistanceFunction &distance, const EdgeSet &edge);

int main() {
	int N, E, C, M;
	
	std::cin >> N >> E >> C >> M;
	
	memory.resize(N + 1);
	path.resize(N + 1);
	
	for(int i = 1; i <= N; ++i) {
		memory[i].resize(N + 1, INF);
		path[i].resize(N + 1, 0);
	}

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
	
	EdgeFunction edge = [&G] (int u) -> EdgeReference {
		return G.data()[u];
	};
	
	for(int i = 1; i <= N; ++i)
		for(int j = 1; j <= N; ++j)
			calcPath(i, j, distance, G.data());
			
	realType const ans = dfs(C, M, distance, edge);
	
	std::cout << std::setprecision(3) << std::fixed << ans << std::flush;
	
	return 0;
}

realType dfs(sizeType c, sizeType m, const DistanceFunction &distance, const EdgeFunction &edge) {
	if(memory[c][m] != INF)
		return memory[c][m];

	if(c == m)
		return memory[c][m] = 0;

	if(distance(c, m) <= 2)
		return memory[c][m] = 1;
		
	realType result = 0;

	int const degree = edge(m).size();
	int const x = path[c][m];
	
	for(auto iter : edge(m))
		result += dfs(x, iter, distance, edge) + (realType)1;
		
	result /= (realType)degree;
	
	return memory[c][m] = result;
}

void calcPath(int c, int m, const DistanceFunction &distance, const EdgeSet &edge) {
	if(c == m)
		return;
		
	if(distance(c, m) <= 2)
		return;
		
	int to1 = 0;
	
	for(auto iter : edge[c]) {
		if(to1 == 0 || distance(to1, m) > distance(iter, m) || (distance(to1, m) == distance(iter, m) && iter < to1))
			to1 = iter;
	}
	
	int to2 = 0;
	
	for(auto iter : edge[to1]) {
		if(to2 == 0 || distance(to2, m) > distance(iter, m) || (distance(to2, m) == distance(iter, m) && iter < to2))
			to2 = iter;
	}
	
	path[c][m] = to2;
}
